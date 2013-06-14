
#include "image.h"

using namespace std;

extern int g_image_width;
extern int g_image_height;

extern Image g_image;


// image: [col1, col2, ... ] 

Image init_image(int w, int h) {
	
	Image image;

    image = (Color **) malloc(sizeof(Color *) * w);

    if (image == NULL) {
        perror("init_image: malloc.");
        exit(1);
    }

    for (int x=0; x < w; x++) {
        image[x] = (Color *) malloc(sizeof(Color) * h);

        if (image[x] == NULL) {
            perror("init_image: malloc.");
            exit(1);
        }
    }

    for (int y=0; y < h; y++)
    for (int x=0; x < w;x++) {
        image[x][y] = Color(0, 0, 0);
    }
    
    return image;
}

void free_image(int w, int h, Image image) {
    for (int x=0; x < w; x++) {
        free(image[x]);
    }
    
    free(image);
}



void write_image(Image image, string fname) {
    // ppm
    
    FILE *file = fopen(fname.c_str(), "w+");
    
    if (file == NULL) {
    	perror("error creating output image");
        exit(1);
    }
    
    fprintf(file, "P3\n%d %d\n255\n", g_image_width, g_image_height);
    
    for (int y=0; y < g_image_height; y++) {
    	for (int x=0; x < g_image_width; x++) {
	   	    fprintf(file, "%d %d %d # %d, %d\n",
	   	     image[x][y].r, image[x][y].g, image[x][y].b, x, y);
    	}
    }
    
    fclose(file);
}



/* BMP file loader loads a 24-bit bmp file only */

/*
* getint and getshort are help functions to load the bitmap byte by byte
*/
static unsigned int getint(FILE *fp) {
  int c, c1, c2, c3;
  
  /*  get 4 bytes */ 
  c = getc(fp);  
  c1 = getc(fp);  
  c2 = getc(fp);  
  c3 = getc(fp);
  
  return ((unsigned int) c) +   
    (((unsigned int) c1) << 8) + 
    (((unsigned int) c2) << 16) +
    (((unsigned int) c3) << 24);
}

static unsigned int getshort(FILE *fp){
  int c, c1;
  
  /* get 2 bytes*/
  c = getc(fp);  
  c1 = getc(fp);
  
  return ((unsigned int) c) + (((unsigned int) c1) << 8);
}

/*  quick and dirty bitmap loader...for 24 bit bitmaps with 1 plane only.  */

Image load_image(const char *filename) {
  FILE *file;
  unsigned long size;                 /*  size of the image in bytes. */
  unsigned long i;                    /*  standard counter. */
  unsigned short int planes;          /*  number of planes in image (must be 1)  */
  unsigned short int bpp;             /*  number of bits per pixel (must be 24) */
  
  Image image = NULL;
  
  /*  make sure the file is there. */
  if ((file = fopen(filename, "rb"))==NULL) {
    printf("File Not Found : %s\n",filename);
    return 0;
  }
  
  /*  seek through the bmp header, up to the width height: */
  fseek(file, 18, SEEK_CUR);
  
  /*  No 100% errorchecking anymore!!! */
  
  /*  read the width */
  const int sizeX = getint (file);
  
  /*  read the height */ 
  const int sizeY = getint (file);
  
  image = init_image(sizeX, sizeY);
  
  /*  calculate the size (assuming 24 bits or 3 bytes per pixel). */
  size = sizeX * sizeY * 3;
  
  /*  read the planes */    
  planes = getshort(file);
  if (planes != 1) {
    printf("Planes from %s is not 1: %u\n", filename, planes);
    return 0;
  }
  
  /*  read the bpp */    
  bpp = getshort(file);
  if (bpp != 24) {
    printf("Bpp from %s is not 24: %u\n", filename, bpp);
    return 0;
  }
  
  /*  seek past the rest of the bitmap header. */
  fseek(file, 24, SEEK_CUR);
  
  /*  read the data.  */
  uint8_t *data = (uint8_t *) malloc(size);
  if (data == NULL) {
    printf("Error allocating memory for color-corrected image data");
    return 0; 
  }
  
  if ((i = fread(data, size, 1, file)) != 1) {
    printf("Error reading image data from %s.\n", filename);
    return 0;
  }
  
  for (i=0;i<size/3;i++) { /*  reverse all of the colors. (bgr -> rgb) */
    image[i%sizeX][i/sizeX].r = data[i*3+2]; // red
    image[i%sizeX][i/sizeX].g = data[i*3+1]; // green
    image[i%sizeX][i/sizeX].b = data[i*3]; // blue
  }
  
  free(data);
  
  fclose(file); /* Close the file and release the filedes */
  
  /*  we're done. */
  return image;
}




