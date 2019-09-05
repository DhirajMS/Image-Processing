#include <stdio.h>
#include <stdlib.h>

int main()
{

/**********************************************

Input and Output File name and location
rb = Open file for reading.
wb = Truncate to zero length or create file for writing.

***********************************************/

	FILE *fIn;
	fIn = fopen("images/cameraman.bmp","rb");

	FILE *fOut;
	fOut = fopen("images/cameraman_Adaptive_Gaussian.bmp","wb");

/**********************************************

If the Input File doesn't exist or curropted
or unable to read Image then Exit the Program.

***********************************************/

	if (fIn == (FILE*)0)
	{
	printf("Unable to open Image");
    exit(0);
	}

/**************************************************

Read the 54 byte header from fIn
header[18] contains width info.
header[22] contains height info.
header[28] contains bitDepth info.

***************************************************/

	unsigned char header[54];
	unsigned char colorTable[1024];

	for(int i=0; i<54; i++)
	{
		header[i] =  getc(fIn);
	}

	int width = *(int*)&header[18];   	// Extract image height, width and bitDepth from imageHeader
	int height = *(int *)&header[22];
	int bitDepth = *(int *)&header[28];

	if ( bitDepth<=8 )
	{
		fread(colorTable,sizeof(unsigned char),1024, fIn); //Read colortable if exist
	}

	fwrite(header, sizeof(unsigned char),54,fOut);  //write the header back

/*****************************************************

Store Input Image data in buf[width][height]
Store Output Image data in out_buf[width][height]

******************************************************/

	unsigned char buf[width][height];
	unsigned char out_buf[width][height];

	fread (buf,sizeof (unsigned char),(height * width), fIn);
	fread (out_buf,sizeof (unsigned char),(height * width), fIn);

	if ( bitDepth<=8 )
	{
		fwrite(colorTable,sizeof(unsigned char),1024, fOut);
	}


/*****************************************************

Do Image Operations on the array buf[width][height]
and store output in out_buf[width][height]


## High Pass Filter Mask ##

  0   -1/4    0

-1/4   +2   -1/4

  0   -1/4    0

Use: Sharpen our Image

******************************************************/

float kernel[3][3] = {
                           { 0.0,   -1.0/4.0,   0.0 },

                           {-1.0/4.0, 2.0, -1.0/4.0 },

                           { 0.0,  -1.0/4.0,    0.0 },
                     };

int i,j,a,b;
int n = 0;
int convl = 0;

unsigned long hist[256] = { 0 };
unsigned long out_hist[256] = { 0 };

for (i=0; i<256; i++)
	for(j=0; j<256; j++)
	{
      {
	       	n = buf[i][j];
			hist[n] = hist[n] + 1 ;
      }
	}


//convolution

for (i=0; i<256; i++)
  {

//for kernel mask

       for (a=-1; a<2; a++)
         {
           for (b=-1; b<2; b++)
            {
             convl = convl + hist[i]*kernel[a+1][b+1];
            }
         }

            convl = convl/3;

out_hist[i] = convl;

  }

//Print Histogram

         int h=0;
		 int x,y;

	    printf("Enter Min Gray Level limit you wan't to display\n");
        scanf("%d",&x);

        printf("Enter Max Gray Level limit you wan't to display\n");
        scanf("%d",&y);

        for (int a = 0; a < 255; a++)
        {
        if (h <= out_hist[a])
            h = out_hist[a];
        }

        for (int i = h; i >= 0; i--)
        {

        for (int a = x; a < y+1 ; ++a)
          {

           if (out_hist[a] > 25*i)
           {
            printf("|");
           }
            else
           {
            printf(" ");
           }
          }
            printf("\n");
        }

    int k,k1,k3;

	 for (i=0; i<255; i++)
     {
         k = ( out_hist[i] > out_hist[i-1] ? out_hist[i] : out_hist[i-1] ) ;
     }

     for (i=0; i<125; i++)
     {
         k1 = ( out_hist[i] > out_hist[i-1] ? out_hist[i] : out_hist[i-1] ) ;
     }

     for (i=125; i<256; i++)
     {
         k3 = ( out_hist[i] > out_hist[i-1] ? out_hist[i] : out_hist[i-1] ) ;
     }

int k2 = (k1+k3)/2;

  for(i=0; i<256; i++)
    {
    for(j=0; j<256; j++)
      {
       if(buf[i][j] < k2)
        {
            out_buf[i][j] = 0;
        }
		else
			out_buf[i][j] = 255;

      }
    }

	//Fix Edges

	for (i = 0; i < 256; i++)
	{
	 for (j=0; j< 256; j++)
	   {
		   out_buf[0][j] = out_buf[1][j];
		   out_buf[255][j] = out_buf[254][j];
		   out_buf[i][0] = out_buf[i][1];
		   out_buf[i][255] = out_buf[i][254];
	   }
	}

/********************************************************

Write back to the output image with new out_buf.
Close both input and output Image files

*********************************************************/

	fwrite(out_buf,sizeof(unsigned char),(width *height),fOut);

	fclose(fIn);
	fclose(fOut);

	return 0;
}



