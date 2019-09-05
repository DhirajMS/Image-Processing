     /*******************************************
     *
     *   opening(...
     *
     *   Opening is erosion followed by dilation.
     *   This routine will use the mask erosion
     *   and dilation.  You could use the other
     *   types and you could mix the two types.
     *
     *   The number parameter specifies how
     *   erosions to perform before doing one
     *   dilation.
     *
     *******************************************/

opening(in_name, out_name, the_image, out_image,
        il, ie, ll, le, value, mask_type, number)
   char   in_name[], out_name[];
   int    il, ie, ll, le, number;
   short  the_image[ROWS][COLS],
          out_image[ROWS][COLS],
          mask_type, value;
{
   int    a, b, count, i, j, k;
   short  mask[3][3], max;

      /**************************************
      *
      *   Copy the 3x3 erosion-dilation mask
      *   specified by the mask_type.
      *
      ***************************************/

   switch(mask_type){
      case 1:
         copy_3_x_3(mask, edmask1);
         break;
      case 2:
         copy_3_x_3(mask, edmask2);
         break;
      case 3:
         copy_3_x_3(mask, edmask3);
         break;
      case 4:
         copy_3_x_3(mask, edmask4);
         break;
      default:
         printf("\nInvalid mask type, using mask 4");
         copy_3_x_3(mask, edmask4);
         break;
   }

   create_file_if_needed(in_name, out_name, out_image);

   read_tiff_image(in_name, the_image, il, ie, ll, le);

   mask_erosion(in_name, out_name, the_image,
                out_image, il, ie, ll, le,
                value, mask_type);

   if(number > 1){
      count = 1;
      while(count < number){
         count++;
         mask_erosion(out_name, out_name, the_image,
                       out_image, il, ie, ll, le,
                       value, mask_type);
      }  /* ends while */
   }  /* ends if number > 1 */

   mask_dilation(out_name, out_name, the_image,
                 out_image, il, ie, ll, le,
                 value, mask_type);

   write_array_into_tiff_image(out_name, out_image,
                               il, ie, ll, le);

}  /* ends opening */