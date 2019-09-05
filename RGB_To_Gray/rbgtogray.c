
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <math.h>
#include <string.h>

int main()
{
    FILE *fIn;
    fIn = fopen("images/tablet_color.bmp","rb");

    FILE *fGray;
    fGray = fopen("images/tablet_gray.bmp","wb");

    int rows,cols,bitDepth,size;

	//Read Input Image
	ConvertToGray(fIn,fGray,rows,cols,bitDepth);

	return 0;
}

ConvertToGray(fIn,fGray,rows,cols,bitDepth)
FILE *fIn;
FILE *fGray;
int rows,cols,bitDepth;

{

	fIn = fopen("images/tablet_color.bmp","rb");

	fGray = fopen("images/tablet_gray.bmp","wb");

    unsigned char header[54];
    fread(header, sizeof(unsigned char), 54, fIn);
    fwrite(header, sizeof(unsigned char), 54, fGray);

    cols = *(int*)&header[18];
    rows = abs(*(int*)&header[22]);
    bitDepth = *(int*)&header[28];

    int stride = (cols * 3 + 3) & ~3;
    int padding = stride - cols * 3;

    unsigned char pixel[3];
    for (int y = 0; y < rows; ++y)
    {
        for (int x = 0; x < cols; ++x)
        {
            fread(pixel, 3, 1, fIn);
            unsigned char gray = pixel[0] * 0.3 + pixel[1] * 0.58 + pixel[2] * 0.11;
            memset(pixel, gray, sizeof(pixel));
            fwrite(&pixel, 3, 1, fGray);

        }
        fread(pixel , bitDepth, 1, fIn);
        fwrite(pixel, bitDepth, 1, fGray);
    }

	fclose(fIn);
    fclose(fGray);

return 0;

}
