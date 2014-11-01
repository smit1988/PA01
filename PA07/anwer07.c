//Noah Smith
//ece264
//October 26,2014

//Much of the structure of this code is taking from page 389 from the book

//Get Cleaup and checkHeader code
Image * Image_load(const char * filename){
  FILE * fptr = NULL;
  ImageHeader header;
  Image * img = NULL;
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
  //data_size is width*height
  img->width = header.width;
  img->height = header.height;
}
