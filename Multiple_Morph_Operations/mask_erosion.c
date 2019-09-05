#include <stdio.h>
#include <stdlib.h>  

  /*******************************************
     *
     *   mask_erosion(...
     *
     *   This function performs the erosion
     *   operation using the erosion-dilation
     *   3x3 masks given above.  It works on
     *   0-value images.
     *
     *******************************************/ 

int main()
{
    FILE *fIn;
    fIn = fopen("images/tablet.bmp","rb");

    FILE *fOut;
    fOut = fopen("images/tablet_erosion.bmp","wb");

	if (fIn == (FILE*)0)
	{
	printf("Unable to open Image");
    exit(0);
	}

    int rows,cols,bitDepth,size;

	unsigned char header[54];
	unsigned char colorTable[1024];
	
	for(int i=0; i<54; i++)
	{
		header[i] =  getc(fIn);
	}

     rows = *(int*)&header[18];
	 cols = *(int *)&header[22];
	 bitDepth = *(int *)&header[28];

	if ( bitDepth<=8 )
	{
		fread(colorTable,sizeof(unsigned char),1024, fIn);
	}

	fwrite(header, sizeof(unsigned char),54,fOut);

	unsigned char buf[rows][cols];
	unsigned char out_buf[cols][rows];

	fread (buf,sizeof (unsigned char),(rows * cols), fIn);
	fread (out_buf,sizeof (unsigned char),(rows * cols), fIn);

	if ( bitDepth<=8 )
	{
		fwrite(colorTable,sizeof(unsigned char),1024, fOut);
	}

// Mask Erosion

int i,j,a,b,min;
int value = 255;


short mask[3][3] = {
                           { 1,   1,   1 },

                           { 1,   1,   1 },

                           { 1,   1,   1 },
                     };

int n;

printf("Enter No. Of Erosions You Want \n");
scanf("%d",&n);

for (int m=1; m<n+1; m++)
{
					 
 for(i=1; i<cols-1; i++)
 {  
      for(j=1; j<rows-1; j++)
	  {
         min = value;
         for(a=-1; a<=1; a++)
		 {
             for(b=-1; b<=1; b++)
			 {
                if(mask[a+1][b+1] == 1)
				{
                   if(buf[i+a][j+b] < min)
                      min = buf[i+a][j+b];
                }
             } 
         }
         out_buf[i][j] = min;
      } 
  }  
	//Fix Edges
	for (i = 0; i < cols-1; i++)
	{
	 for (j = 0; j< rows-1; j++)
	   {
		   out_buf[0][j] = out_buf[1][j];
		   out_buf[255][j] = out_buf[254][j];
		   out_buf[i][0] = out_buf[i][1];
		   out_buf[i][255] = out_buf[i][254];
	   }
	}
    
 for (i = 0; i < cols-1; i++)
	{
	 for (j = 0; j< rows-1; j++)
	   {
		   buf[i][j] = out_buf[i][j];
	   }
	}

}




	fwrite(out_buf,sizeof(unsigned char),(rows *cols),fOut);

	fclose(fIn);
	fclose(fOut);

	return 0;
}                                       //End of ThresholdImage

