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
    const char * prefix = "Original ece264 file: ";
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

  
}

int Image_save(const char * filename, Image * image)
{
  return 0;
}

void Image_free(Image * image)
{
}

void linearNormalization(int width, int height, uint8_t * intensity)
{
}
