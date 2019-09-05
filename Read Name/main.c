#include <stdio.h>
#include <stdlib.h>

#include "ImageCopy.c"

void main()
{
		FILE *fIn;
		FILE *fOut;
		
		char* input_image = "images/cameraman.bmp";
		char* output_image = "images/cameraman_copy.bmp";

	fIn = fopen(input_image,"rb");

	fOut = fopen(output_image,"wb");

	image_copy(fIn,fOut);


}
