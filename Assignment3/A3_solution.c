/* FILE: A3_solutions.c is where you will code your answers for Assignment 3.
 * 
 * Each of the functions below can be considered a start for you. They have 
 * the correct specification and are set up correctly with the header file to
 * be run by the tester programs.  
 *
 * You should leave all of the code as is, especially making sure not to change
 * any return types, function name, or argument lists, as this will break
 * the automated testing. 
 *
 * Your code should only go within the sections surrounded by
 * comments like "REPLACE EVERTHING FROM HERE... TO HERE.
 *
 * The assignment document and the header A3_solutions.h should help
 * to find out how to complete and test the functions. Good luck!
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "A3_provided_functions.h"

unsigned char*
bmp_open( char* bmp_filename,        unsigned int *width, 
          unsigned int *height,      unsigned int *bits_per_pixel, 
          unsigned int *padding,     unsigned int *data_size, 
          unsigned int *data_offset                                  )
{
  unsigned char *img_data=NULL;
  // REPLACE EVERYTHING FROM HERE
  //open a binary bmp file
  FILE* bmpfile = fopen(bmp_filename, "rb");

  //read B and M characters and check if the file is a valid bmp file
  char b, m;
  fread(&b,1,1,bmpfile);
  fread(&m,1,1,bmpfile);
  if(b!='B' || m!='M'){
    printf("This file is not of type bmp\n");
    return img_data;
  }
  rewind(bmpfile);
  fseek(bmpfile,2,SEEK_SET);

  //read the size of whole file
  fread(data_size, 1, sizeof(unsigned int), bmpfile);
  rewind(bmpfile);

  //Allocate memory for img_data
  img_data = (unsigned char*)malloc(*data_size);
  fread(img_data, 1, *data_size, bmpfile);                 

  //Read Image Width and store it at *width
  unsigned int *temp = (unsigned int*)(img_data+18);
  *width = *temp;

  //Read Image Height and store it at *height
  temp = (unsigned int*)(img_data+22);
  *height = *temp;

  //Read Bits per Pixel and store it at *bits_per_pixel
  temp = (unsigned int*)(img_data+28);
  *bits_per_pixel = (unsigned short int) *temp;

  //Calculate padding
  *padding = *width % 4;

  //Read Image Size and store in *data_size
  fread(data_size, 1, sizeof(unsigned int), bmpfile);

  //Read Header Size, calculate offset, and store in *data_offset
  temp = (unsigned int*)(img_data+10);
  *data_offset = *temp;

// TO HERE!  
  return img_data;  
}

void 
bmp_close( unsigned char **img_data )
{
  // REPLACE EVERYTHING FROM HERE
  free (*img_data);
  *img_data = NULL;
  // TO HERE!  
}
unsigned char***  
bmp_scale( unsigned char*** pixel_array, unsigned char* header_data, unsigned int header_size,
           unsigned int* width, unsigned int* height, unsigned int num_colors,
           float scale )
{
  unsigned char*** new_pixel_array = NULL; 
  // REPLACE EVERYTHING FROM HERE
 
  *width = (unsigned int)(*width*scale);
  *height = (unsigned int)(*height*scale);
  unsigned int* heightScaled = (unsigned int*)(header_data+22);
  unsigned int* widthScaled = (unsigned int*)(header_data+18);
  *heightScaled = (unsigned int)(*height);
  *widthScaled = (unsigned int)(*width);

  //allocate memory for new pixel array
  new_pixel_array = (unsigned char***)malloc(sizeof(unsigned char**)*(*height));
  for(unsigned int row=0; row<*height; row++){
    new_pixel_array[row]=(unsigned char**)malloc(sizeof(unsigned char*)*(*width));
    for(unsigned int col=0; col<*width; col++){
      new_pixel_array[row][col]=(unsigned char*)malloc(sizeof(unsigned char)*(num_colors));
    }
  }

  //copy pixel data into new pixel array
  for(int row=0;row<*height;row++){
    for(int col=0;col<*width;col++){
      for(int color=0;color<num_colors;color++){
        new_pixel_array[row][col][color]=pixel_array[(int)(row/scale)][(int)(col/scale)][color];
      }
    }
  }
  
  // TO HERE! 
  return new_pixel_array;
}         

int 
bmp_collage( char* background_image_filename,     char* foreground_image_filename, 
             char* output_collage_image_filename, int row_offset,                  
             int col_offset,                      float scale )
{
  // REPLACE EVERYTHING FROM HERE
  //initialize variables for background image and foreground image
  unsigned char* bg_header_data;
  unsigned char* fg_header_data;
  unsigned int bg_header_size, fg_header_size, bg_width, fg_width, bg_height, fg_height, bg_num_colors, fg_num_colors;
  unsigned char*** bg_pixel_array = NULL;
  unsigned char*** fg_pixel_array = NULL;

  //open background image and foreground image and store their data in a 3D array
  bg_pixel_array = bmp_to_3D_array( background_image_filename,  &bg_header_data,
                                    &bg_header_size,            &bg_width,
                                    &bg_height,                 &bg_num_colors);

  fg_pixel_array = bmp_to_3D_array( foreground_image_filename,  &fg_header_data,
                                    &fg_header_size,            &fg_width,
                                    &fg_height,                 &fg_num_colors);
  
  FILE* background = fopen(background_image_filename, "rb");
  FILE* foreground = fopen(foreground_image_filename, "rb");
  //check if the file exists
  if (background==NULL && foreground==NULL) {
    printf("Background image and foreground image not exist.\n");
    return -1;
  }
  else if (background==NULL) {
    printf("Background image does not exist.\n");
    return -1;
  }
  else if (foreground== NULL) {
    printf("Foreground image does not exist.\n");
    return -1;
  }

  //update the foreground image by using function in q2
  fg_pixel_array = bmp_scale( fg_pixel_array,   fg_header_data,
                              fg_header_size,   &fg_width,
                              &fg_height,       fg_num_colors,  scale );

  //check num_colors for both background image and foreground image
  if (bg_num_colors%4 != 0 || fg_num_colors%4 != 0) {
    printf("The number of colors is not valid.\n");
    return -1;
  }

  //iterate through each pixel of background image and combine foreground image and background image
  for (int r=row_offset; r<row_offset+fg_height; r++) {
    for (int c=col_offset; c<col_offset+fg_width; c++) {
      for (int color=0; color<fg_num_colors; color++) {
        if (color == 0) {
          if (fg_pixel_array[r-row_offset][c-col_offset][0] == 0) {
            break;}
        }else {
          bg_pixel_array[r][c][color] = fg_pixel_array[r-row_offset][c-col_offset][color];
        }
      }
    }
  }

  //check if the collaged bmp file exported successfully
  if ( bmp_from_3D_array( output_collage_image_filename, bg_header_data, bg_header_size,                 
                          bg_pixel_array, bg_width, bg_height, bg_num_colors ) != 0 ){
    printf("Export failed.\n");
    return -1;
  }
  // TO HERE! 
  return 0;
}              

