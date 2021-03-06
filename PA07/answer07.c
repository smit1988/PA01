//Noah Smith
//ece264
//October 26,2014

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h>
#include "answer07.h"


//Much of the structure of this code is taking from page 389 from the book

static int checkHeader(ImageHeader * hdr)
{
  if((hdr->magic_number) != ECE264_IMAGE_MAGIC_NUMBER)
    {
      return 0;
    }
  if((hdr->height) == 0)
    {
      return 0;
    }
  if((hdr->width) == 0)
    {
      return 0;
    }
  if((hdr->comment_len) == 0)
    {
      return 0;
    }
  return 1;
}

//Get Cleaup and checkHeader code
Image * Image_load(const char * filename){
  FILE * fptr = NULL;
  ImageHeader header;
  Image * img = NULL;
  //Make sure you can open the file
  fptr = fopen(filename, "rb"); //"rb" unnecessary in Linux
  if(fptr == NULL)
    {
      fclose(fptr);
      return NULL;
      //return cleanUp(fptr, img);
    }
  img =  malloc(sizeof(Image));
  if(img == NULL)
    {
      free(img);
      fclose(fptr);
      return NULL;
      //return cleanUp(fptr, img);
    }
  //read the header
  if(fread(&header, sizeof(ImageHeader), 1, fptr) != 1)
    {
      //fread fails
      free(img);
      fclose(fptr);
      return NULL;
      //return cleanUp(fptr, img);
    }
  //checkHeader and cleanUp may not be things
  if(checkHeader(&header) == 0)
    {
      free(img);
      fclose(fptr);
      return NULL;
      //return cleanUp(fptr, img);
    }
  //Allocate space for the image, comment, and pixels
  if((header.width*header.height) > (999*999*999))
    {
      free(img);
      fclose(fptr);
      return NULL;
    }
  //data_size is width*height
  img->data = malloc(header.width * header.height * sizeof(uint8_t));
  /*if((img->data) == NULL)
    {
      free(img->data);
      free(img);
      fclose(fptr);
      return NULL;
      }*/
  img->comment = malloc(header.comment_len * sizeof(char));
  /*if((img->comment) == NULL)
    {
      free(img->comment);
      free(img->data);
      free(img);
      fclose(fptr);
      return NULL;
      }*/
  img->width = header.width;
  img->height = header.height;
  //Read the comment
  if(fread(img->comment, header.comment_len, 1, fptr) != 1)
    {
      free(img->comment);
      free(img->data);
      free(img);
      fclose(fptr);
      return NULL;
    }
  //Make sure you read the entire comment
  if((header.width*header.height) > (999*999*999))
    {
      free(img);
      fclose(fptr);
      return NULL;
    }
  //Make sure the comment ends in a null-byte
  if(img->comment[header.comment_len - 1] != '\0')
    {
      free(img->comment);
      free(img->data);
      free(img);
      fclose(fptr);
      return NULL;
    }
  
  //Read the pixels
  if(fread(img->data, (header.width * header.height), 1, fptr) != 1)
    {
      free(img->data);
      free(img->comment);
      free(img);
      fclose(fptr);
      return NULL;
      //return cleanUp(fptr, img);
    }
  
  //Check end
  size_t endOfFile;
  if(fread(&endOfFile,sizeof(uint8_t), 1, fptr) != 0)
    {
      free(img->data);
      free(img->comment);
      free(img);
      fclose(fptr);
      return NULL;
    }

  //Make sure you read *all* width*height pixels
  //Make sure you've reached the end of the file
  fclose(fptr);
  return img;
}

void Image_free(Image * image)
{
  free(image->data);
  free(image->comment);
  free(image);
}

int Image_save(const char * filename, Image * image)
{
  FILE * fptr = NULL;
  ImageHeader header;
  fptr = fopen(filename, "wb");
  if(fptr == NULL)
    {
      return 0;
    }
  header.width = image->width;
  header.height = image->height;
  header.magic_number = ECE264_IMAGE_MAGIC_NUMBER;
  header.comment_len = strlen(image->comment) + 1;
  //write the header first
  if(fwrite(&header, sizeof(ImageHeader), 1, fptr) != 1)
    {
      //fwrite fails
      fclose(fptr);
      return 0;
    }
  if(fwrite((image->comment), header.comment_len, 1, fptr) != 1)
    {
      //fwrite fails
      fclose(fptr);
      return 0;
    }
  if(fwrite((image->data), (header.width * header.height), 1, fptr) != 1)
    {
      //fwrite fails
      fclose(fptr);
      return 0;
    }
  //everything successful
  fclose(fptr);
  return 1;
}

void linearNormalization(int width, int height, uint8_t * intensity)
{
  uint8_t max = intensity[0];
  uint8_t min = intensity[0];
  int i;
  for(i=0; i<(width * height); i++)
    {
      if(intensity[i] > max)
	max = intensity[i];
      if(intensity[i] < min)
	min = intensity[i];
    }
  for(i = 0; i<(width * height); i++)
    {
      intensity[i] = (intensity[i] - min) * 255.0 / (max - min);
    }
}
