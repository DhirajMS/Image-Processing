#include <stdio.h>
#include <stdlib.h>
//#include <graph.h>
#include <io.h>
#include <fcntl.h>
//#include <dos.h>
#include <math.h>
#include <malloc.h>
#include <string.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <time.h>


int main()
{
	FILE *fIn;
    fIn = fopen("images/tablet_color.bmp","rb");
	FILE *fOut;
    fOut = fopen("images/tablet_hsb.bmp","wb");

	if (fIn == (FILE*)0)
	{
	printf("Unable to open Image");
    exit(0);
	}

    int rows,cols,bitDepth,size;
    unsigned char header[54];
    fread(header, sizeof(unsigned char), 54, fIn);
    fwrite(header, sizeof(unsigned char), 54, fOut);

    cols = *(int*)&header[18];
    rows = abs(*(int*)&header[22]);
    bitDepth = *(int*)&header[28];

    int stride = (cols * 3 + 3) & ~3;
    int padding = stride - cols * 3;

    float PI = 3.141592654;

    unsigned char pixel[3];
	double R,G,B ;

	unsigned char out_pixel[3];
	double H,S,I ;

	double temp;

	clock_t start, stop;
	start=clock();                     //timer

    for (int y = 0; y < rows; ++y)
    {
        for (int x = 0; x < cols; ++x)
        {
            fread(pixel, 3, 1, fIn);

			R = pixel[0];
			G = pixel[1];
			B = pixel[2];

			// Intensity
			I = ( R + G + B ) / 3 ;
			out_pixel[0] = I ;

			// Saturation
			temp = R < G ? R : G ;
			temp = G < B ? G : B ;
			S = 1 - (temp/I) ;

			// Hue
			temp = (1.73205)*(G-B)/(2*R-G-B);
			H = atan(temp);
            H = ( H * 180 ) / PI ;

			out_pixel[0] = H ;
			out_pixel[1] = S ;
			out_pixel[2] = I ;

            for (int i=0; i< 3; i++)
            {
                temp = out_pixel[i] ;
                memset(pixel, temp , sizeof(pixel));
            }

            fwrite(&out_pixel, 3, 1, fOut);

        }
        fread(pixel , bitDepth, 1, fIn);
        fwrite(out_pixel, bitDepth, 1, fOut);
    }

	stop = clock();
	printf("Time for SHI segmentation is : %lf ms\n",((double)(stop - start) * 1000.0 )/ CLOCKS_PER_SEC);

	fclose(fIn);
    fclose(fOut);

	return 0;

}
