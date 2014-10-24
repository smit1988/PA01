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
