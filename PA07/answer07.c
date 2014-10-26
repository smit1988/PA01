//Noah Smith
//ece264
//October 26,2014

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
}

Image * cleanUp(FILE * fptr, Image * img)
{
  if(fptr != NULL)
    {
      fclose(fptr);
    }
  if(img != NULL)
    {
      if(img->data != NULL)
	{
	  free(img->data);
	}
      free(img);
    }
  return NULL;
}

//Get Cleaup and checkHeader code
Image * Image_load(const char * filename){
  FILE * fptr = NULL;
  ImageHeader header;
  Image * img = NULL;
  //Make sure you can open the file
  fptr = fopen(filename, "r"); //"rb" unnecessary in Linux
  if(fptr == NULL)
    {
      return cleanUp(fptr, img);
    }
  img =  malloc(sizeof(Image));
  if(img == NULL)
    {
      return cleanUp(fptr, img);
    }
  //read the header
  if(fread(&header, sizeof(ImageHeader), 1, fptr) != 1)
    {
      //fread fails
      return cleanUp(fptr, img);
    }
  //checkHeader and cleanUp may not be things
  if(checkHeader(&header) == 0)
    {
      return cleanUp(fptr, img);
    }
  //Allocate space for the image, comment, and pixels
  //data_size is width*height
  img->data = malloc(header.width * header.height);
  img->comment = malloc(header.comment_len + 1);
  img->width = header.width;
  img->height = header.height;
  //Read the comment
  if((img->comment) == NULL)
    {
      return cleanUp(fptr, img);
    } else {
    if(fread(&(img->comment), sizeof(img->comment), 1, fptr) != 1)
      {
	return cleanUp(fptr, img);
      }
  }
  //Make sure you read the entire comment
  //Make sure the comment ends in a null-byte
  if(img->comment[header.comment_len] != '\0')
    return cleanUp(fptr, img);

  //Read the pixels
  if((img->data) == NULL)
    {
      return cleanUp(fptr, img);
    } else {
    if(fread(&(img->data), sizeof(img->data), 1, fptr) != 1)
      {
        return cleanUp(fptr, img);
      }
  }

  //Make sure you read *all* width*height pixels
  //Make sure you've reached the end of the file
}
