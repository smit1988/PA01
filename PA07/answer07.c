//Noah Smith
//October 24, 2014
//Ece264

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h>

#include "answer07.h"

#define FALSE 0
#define TRUE 1

static int Header_checkValid(ImageHeader * header)
{
  //Make sure that you can read all the bytes of the header

  //Make sure that the magic_number in the header is correct
  if(header->magic_number != ECE264_IMAGE_MAGIC_NUMBER) return FALSE;
  //Make sure that neither the width nor height is zero
  if(header->width == 0) return FALSE;
  if(header->height == 0) return FALSE;
  //Make sure that the comment length is not zero. (Remember, it includes the null-byte.)
  if(header->comment_len == 0) return FALSE;
  //We're winners
  return TRUE;
}

Image * Image_load(const char * filename)
{
  FILE * fp = NULL;
  size_t read;
  ImageHeader header;
  Image * tmp_im = NULL, * im = NULL;
  size_t n_bytes = 0;
  int err = FALSE;

  if(!err){ //Open filename
    fp = fopen(filename, "rb");
    if(!fp){
      fprintf(stderr, "Failed to open file '%s'\n", filename);
      err = TRUE;
    }
  }

  if(!err){ //Read the header
    read = fread(&header, sizeof(ImageHeader), 1, fp);
    if(read != 1){
      fprintf(stderr, "Failed to read header from '%s'\n", filename);
      err = TRUE;
    }
  }

  if(!err){ //We're only interested in a subset of valid bmp files
    if(!Header_checkValid(&header)){
      fprintf(stderr, "Invalid header in '%s'\n", filename);
      err = TRUE;
    }
  }

  if(!err) { //Allocate Image struct
    tmp_im = malloc(sizeof(Image));
    if(tmp_im == NULL){
      fprintf(stderr, "Failed to allocate im sturcture\n");
      err = TRUE;
    }
  }

  if(!err){ //Init the Image struct
    tmp_im->width = header.width;
    tmp_im->height = header.height;
    
    //Handle the comment
    char * filename_cpy = strdup(filename); //we want to call basename
    char * file_basename = basename(filename_cpy); //requires editable str
    const char * prefix = "Original BMP file: ";
    n_bytes = sizeof(char) * (strlen(prefix) + strlen(file_basename) + 1);
    tmp_im->comment = malloc(n_bytes);
    if(tmp_im->comment == NULL){
      fprintf(stderr, "Failed to allocate %zd bytes for comment\n", n_bytes);
      err = TRUE;
    } else {
      sprintf(tmp_im->comment, "%s%s", prefix, file_basename);
    }
    free(filename_cpy); //this also takes care of file_basename

    //Handle image data
    n_bytes = sizeof(uint8_t) * header.width * header.height;
    tmp_im->data = malloc(n_bytes);
    if(tmp_im->data == NULL){
      fprintf(stderr, "Failed to allocate %zd bytes for image data\n", n_bytes);
      err = TRUE;
    }
  }

  if(!err){ //Seek the start of the pixel data
    if(fseek(fp,sizeof(ImageHeader),SEEK_SET) != 0){
      fprintf(stderr, "Failed to seek %d, the data of the image data\n", sizeof(ImageHeader));
      err = TRUE;
    }
  }

  if(!err){ //read pixel data
    uint8_t * raw264 = malloc(n_bytes);
    if(raw264 == NULL){
      fprintf(stderr, "Could not allocate %zd bytes of image data\n", n_bytes);
      err = TRUE;
    } else {
      read = fread(raw264, sizeof(uint8_t), n_bytes, fp);
      if(n_bytes != read){
	fprintf(stderr, "Only read %zd of %zd bytes of image data\n", read, n_bytes);
	err=TRUE;
      }
    }
    free(raw264);
  }

  if(!err) { //We should be at the end of the file now
    uint8_t byte;
    read = fread(&byte, sizeof(uint8_t), 1, fp);
    if(read != 0) {
      fprintf(stderr, "Stray bytes at the end of bmp file '%s'\n", filename);
      err = TRUE;
    }
  }

  if(!err){ //We're winners...
    im = tmp_im; //264 will be returned
    tmp_im = NULL; //and not cleaned up
  }

  //Cleanup
  if(tmp_im != NULL){
    free(tmp_im->comment); //Remember, you can always free(NULL)
    free(tmp_im->data);
    free(tmp_im);
  }
  if(fp){
    fclose(fp);
  }

  return im;
}

int Image_save(const char * filename, Image * image)
{
  int err = FALSE;
  FILE * fp = NULL;
  uint8_t * buffer = NULL;
  size_t written = 0;

  //Attempt to open file for writing
  fp = fopen(filename, "wb");
  if(fp == NULL){
    fprintf(stderr, "Failed to open '%s' for writing\n", filename);
    return FALSE;
  }

  // Number of bytes stored on each row
  size_t bytes_per_row = ((24 * image->width + 31)/32) * 4;

  //Prepare the header
  ImageHeader header;
  header.magic_number = ECE264_IMAGE_MAGIC_NUMBER;
  header.width = image->width;
  header.height = image->height;
  header.comment_len = (strlen(image->comment) + 1);

  if(!err) { //Before writing, we'll need a write buffer
    buffer = malloc(bytes_per_row);
    if(buffer == NULL){
      fprintf(stderr, "Error: failed to allocate write buffer\n");
      err = TRUE;
    } else {
      memset(buffer, 0, bytes_per_row);
    }
  }

  if(!err) { //Write pixels
    uint8_t * read_ptr = image->data;
    int row, col; //row and column
    for(row = 0; row < header.height && !err; ++row) {
      uint8_t * write_ptr = buffer;
      for(col = 0; col < header.width; ++col) {
	*write_ptr++ = *read_ptr; // blue
	*write_ptr++ = *read_ptr; // green
	*write_ptr++ = *read_ptr; // red
	read_ptr++; // advance to the next pixel
      }
      // Write line to file
      written = fwrite(buffer, sizeof(uint8_t), bytes_per_row, fp);
      if(written != bytes_per_row) {
	fprintf(stderr, "Failed to write pixel data to file\n");
	err = TRUE;
      }
    }
  }

  //Cleanup
  free(buffer);
  if(fp)
    fclose(fp);

  return !err;
}

void Image_free(Image * image)
{
}

void linearNormalization(int width, int height, uint8_t * intensity)
{
}
