/*
	List of modifications:
	1) One less operation in calculation of filter element index
	2) Unrolled the loop
	3) temp variable added not to recalculate filt[y] every time

*/

// Fix the top border
for (int c = 0; c < ncols; c++) {
   	  int r = 0;
      uint sum_R = 0;
      uint sum_G = 0;
      uint sum_B = 0;

      for (int dc = -1; dc <= 1; dc++) {
       for (int dr = -1; dr <= 1; dr++) {

         // Row and column of convolution sum term 
         int cc = c+dc;
         int rr = r+dr;

         if (rr >= 0 && cc >= 0 && rr < nrows && cc < ncols) {
           
           // The address in the array of the sum term
           uint x = ncols*rr+cc;

           // Address of the multiplier in the filter
           uint y = 3*(dc+1)+(dr+1);
           assert(x < ncols*nrows);
           assert(y < FILTER_BYTES);
           sum_R += in[x].R * filt[y];
           sum_G += in[x].G * filt[y];
           sum_B += in[x].B * filt[y];
         }
       }
     }

     uint x = ncols*r+c;
     uchar d = filt[FILTER_BYTES-1];
     out[x].R = (float) sum_R / d;
     out[x].G = (float) sum_G / d;
     out[x].B = (float) sum_B / d;
 }


// Fix the bottom border
for (int c = 0; c < ncols; c++) {
   	  int r = nrows - 1;
      uint sum_R = 0;
      uint sum_G = 0;
      uint sum_B = 0;

      for (int dc = -1; dc <= 1; dc++) {
       for (int dr = -1; dr <= 1; dr++) {

         // Row and column of convolution sum term 
         int cc = c+dc;
         int rr = r+dr;

         if (rr >= 0 && cc >= 0 && rr < nrows && cc < ncols) {
           
           // The address in the array of the sum term
           uint x = ncols*rr+cc;

           // Address of the multiplier in the filter
           uint y = 3*(dc+1)+(dr+1);
           assert(x < ncols*nrows);
           assert(y < FILTER_BYTES);
           sum_R += in[x].R * filt[y];
           sum_G += in[x].G * filt[y];
           sum_B += in[x].B * filt[y];
         }
       }
     }

     uint x = ncols*r+c;
     uchar d = filt[FILTER_BYTES-1];
     out[x].R = (float) sum_R / d;
     out[x].G = (float) sum_G / d;
     out[x].B = (float) sum_B / d;
 }


int c = 0;
    for (int r = 1; r < nrows - 1; r++) {
      uint sum_R = 0;
      uint sum_G = 0;
      uint sum_B = 0;

      for (int dc = -1; dc <= 1; dc++) {
       for (int dr = -1; dr <= 1; dr++) {

         // Row and column of convolution sum term 
         int cc = c+dc;
         int rr = r+dr;

         if (rr >= 0 && cc >= 0 && rr < nrows && cc < ncols) {
           
           // The address in the array of the sum term
           uint x = ncols*rr+cc;

           // Address of the multiplier in the filter
           uint y = 3*(dc+1)+(dr+1);
           assert(x < ncols*nrows);
           assert(y < FILTER_BYTES);
           sum_R += in[x].R * filt[y];
           sum_G += in[x].G * filt[y];
           sum_B += in[x].B * filt[y];
         }
       }
     }

     uint x = ncols*r+c;
     uchar d = filt[FILTER_BYTES-1];
     out[x].R = (float) sum_R / d;
     out[x].G = (float) sum_G / d;
     out[x].B = (float) sum_B / d;

   }

c = ncols - 1;
    for (int r = 1; r < nrows - 1; r++) {
      uint sum_R = 0;
      uint sum_G = 0;
      uint sum_B = 0;

      for (int dc = -1; dc <= 1; dc++) {
       for (int dr = -1; dr <= 1; dr++) {

         // Row and column of convolution sum term 
         int cc = c+dc;
         int rr = r+dr;

         if (rr >= 0 && cc >= 0 && rr < nrows && cc < ncols) {
           
           // The address in the array of the sum term
           uint x = ncols*rr+cc;

           // Address of the multiplier in the filter
           uint y = 3*(dc+1)+(dr+1);
           assert(x < ncols*nrows);
           assert(y < FILTER_BYTES);
           sum_R += in[x].R * filt[y];
           sum_G += in[x].G * filt[y];
           sum_B += in[x].B * filt[y];
         }
       }
     }

     uint x = ncols*r+c;
     uchar d = filt[FILTER_BYTES-1];
     out[x].R = (float) sum_R / d;
     out[x].G = (float) sum_G / d;
     out[x].B = (float) sum_B / d;

   }
 




























































int temp;
uchar d = filt[FILTER_BYTES-1];
int 	t1, t2, t3,
		t4, t5, t6,
		t7, t8, t9;

t1 = 0;
t1+= (int) in[0].R;
t1+= ((int) in[0].G) << 8;
t1+= ((int) in[0].B) << 16;

t2 = 0;
t2+= (int) in[1].R;
t2+= ((int) in[1].G) << 8;
t2+= ((int) in[1].B) << 16;

t3 = 0;
t3+= (int) in[2].R;
t3+= ((int) in[2].G) << 8;
t3+= ((int) in[2].B) << 16;

t4 = 0;
t4+= (int) in[ncols].R;
t4+= ((int) in[ncols].G) << 8;
t4+= ((int) in[ncols].B) << 16;

t5 = 0;
t5+= (int) in[ncols + 1].R;
t5+= ((int) in[ncols + 1].G) << 8;
t5+= ((int) in[ncols + 1].B) << 16;

t6 = 0;
t6+= (int) in[ncols + 2].R;
t6+= ((int) in[ncols + 2].G) << 8;
t6+= ((int) in[ncols + 2].B) << 16;

t7 = 0;
t7+= (int) in[ncols + ncols].R;
t7+= ((int) in[ncols + ncols].G) << 8;
t7+= ((int) in[ncols + ncols].B) << 16;

t8 = 0;
t8+= (int) in[ncols + ncols + 1].R;
t8+= ((int) in[ncols + ncols + 1].G) << 8;
t8+= ((int) in[ncols + ncols + 1].B) << 16;

t9 = 0;
t9+= (int) in[ncols + ncols + 2].R;
t9+= ((int) in[ncols + ncols + 2].G) << 8;
t9+= ((int) in[ncols + ncols + 2].B) << 16;

// int container = 0;
// unsigned char red = 200;
// unsigned char green = 33;
// unsigned char blue = 7;

// container+= (int) red;
// container+= ((int) green) << 8;
// container+= ((int) blue) << 16;

// unsigned char new_blue = container >> 16;
// unsigned char new_green = container >> 8;
// unsigned char new_red = (container << 24) >> 24;


// t1 = in[0];
// t2 = in[1];
// t3 = in[2];
// t4 = in[ncols];
// t5 = in[ncols + 1];
// t6 = in[ncols + 2];
// t7 = in[ncols + ncols];
// t8 = in[ncols + ncols + 1];
// t9 = in[ncols + ncols + 2];




for (int r = 1; r < nrows - 1; r++) {
	for (int c = 1; c < ncols - 1; c++) {
    	
    	uint sum_R = 0;
    	uint sum_G = 0;
    	uint sum_B = 0;


      	/* Unrolling the loop */
      	
    	//  x  .  .
    	//  .  .  .
    	//  .  .  .
      	int dc = -1;
      	int dr = 1;

      	int cc = c+dc;
		int rr = r+dr;
		uint x = ncols*rr+cc;

		// one less operation here
		uint y = 3*dc+dr+4;
		
		// Increment the accumulators
		temp = filt[y];
		// pix = in[x];
		// sum_R += pix.R * temp;
		// sum_G += pix.G * temp;
		// sum_B += pix.B * temp;
		sum_R += ((unsigned char) ((t7 << 24) >> 24)) * temp;
		sum_G += ((unsigned char)(t7 >> 8)) * temp;
		sum_B += ((unsigned char)(t7 >> 16)) * temp;
		if(in[x].R != ((unsigned char)((t7 << 24) >> 24))){
		printf("x: %d, our index %d\n", x, ncols + ncols);
		printf("%d:%d reds: %d %d, green: %d %d, blue: %d %d\n", r, c,
			in[x].R, ((unsigned char)((t7 << 24) >> 24)),
			in[x].G, ((unsigned char)(t7 >> 8)),
			in[x].B, ((unsigned char)(t7 >> 16)));
		}


		//  .  x  .
    	//  .  .  .
    	//  .  .  .
		dc = 0;
		dr = 1;
		cc = c+dc;
		rr = r+dr;
		x = ncols*rr+cc;
		y = 3*dc+dr+4;
		temp = filt[y];
		// pix = in[x];
		// sum_R += pix.R * temp;
		// sum_G += pix.G * temp;
		// sum_B += pix.B * temp;
		// sum_R += in[x].R * temp;
		// sum_G += in[x].G * temp;
		// sum_B += in[x].B * temp;
		sum_R += ((unsigned char)((t8 << 24) >> 24)) * temp;
		sum_G += ((unsigned char)(t8 >> 8)) * temp;
		sum_B += ((unsigned char)(t8 >> 16)) * temp;

		if(in[x].R != ((unsigned char)((t8 << 24) >> 24))){
		printf("%d:%d reds: %d %d, green: %d %d, blue: %d %d\n", r, c,
			in[x].R, ((unsigned char)((t8 << 24) >> 24)),
			in[x].G, ((unsigned char)(t8 >> 8)),
			in[x].B, ((unsigned char)(t8 >> 16)));
		}

		//  .  .  x
    	//  .  .  .
    	//  .  .  .
		dc = 1;
		dr = 1;
		cc = c+dc;
		rr = r+dr;
		x = ncols*rr+cc;
		y = 3*dc+dr+4;
		temp = filt[y];
		sum_R += ((unsigned char)((t9 << 24) >> 24)) * temp;
		sum_G += ((unsigned char)(t9 >> 8)) * temp;
		sum_B += ((unsigned char)(t9 >> 16)) * temp;
		// pix = in[x];
		// sum_R += pix.R * temp;
		// sum_G += pix.G * temp;
		// sum_B += pix.B * temp;
		// sum_R += in[x].R * temp;
		// sum_G += in[x].G * temp;
		// sum_B += in[x].B * temp;

		// Reassign values
		t7 = t8;
		t8 = t9;
		t9 = 0;
		t9+= (int) in[x + 1].R;
		t9+= ((int) in[x + 1].G) << 8;
		t9+= ((int) in[x + 1].B) << 16;



		//  .  .  .
    	//  x  .  .
    	//  .  .  .
		dc = -1;
		dr = 0;
		cc = c+dc;
		rr = r+dr;
		x = ncols*rr+cc;
		y = 3*dc+dr+4;
		temp = filt[y];
		// pix = in[x];
		// sum_R += pix.R * temp;
		// sum_G += pix.G * temp;
		// sum_B += pix.B * temp;
		sum_R += in[x].R * temp;
		sum_G += in[x].G * temp;
		sum_B += in[x].B * temp;

		//  .  .  .
    	//  .  x  .
    	//  .  .  .
		dc = 0;
		dr = 0;
		cc = c+dc;
		rr = r+dr;
		x = ncols*rr+cc;
		y = 3*dc+dr+4;
		temp = filt[y];
		// pix = in[x];
		// sum_R += pix.R * temp;
		// sum_G += pix.G * temp;
		// sum_B += pix.B * temp;
		sum_R += in[x].R * temp;
		sum_G += in[x].G * temp;
		sum_B += in[x].B * temp;

		//  .  .  .
    	//  .  .  x
    	//  .  .  .
		dc = 1;
		dr = 0;
		cc = c+dc;
		rr = r+dr;
		x = ncols*rr+cc;
		y = 3*dc+dr+4;
		temp = filt[y];
		// pix = in[x];
		// sum_R += pix.R * temp;
		// sum_G += pix.G * temp;
		// sum_B += pix.B * temp;
		sum_R += in[x].R * temp;
		sum_G += in[x].G * temp;
		sum_B += in[x].B * temp;
		

		//  .  .  .
    	//  .  .  .
    	//  x  .  .
		dc = -1;
		dr = -1;
		cc = c+dc;
		rr = r+dr;	
		x = ncols*rr+cc;
		y = 3*dc+dr+4;
		temp = filt[y];
		// pix = in[x];
		// sum_R += pix.R * temp;
		// sum_G += pix.G * temp;
		// sum_B += pix.B * temp;
		sum_R += in[x].R * temp;
		sum_G += in[x].G * temp;
		sum_B += in[x].B * temp;
		

		//  .  .  .
    	//  .  .  .
    	//  .  x  .
		dc = 0;
		dr = -1;
		cc = c+dc;
		rr = r+dr;	
		x = ncols*rr+cc;
		y = 3*dc+dr+4;
		temp = filt[y];
		// pix = in[x];
		// sum_R += pix.R * temp;
		// sum_G += pix.G * temp;
		// sum_B += pix.B * temp;
		sum_R += in[x].R * temp;
		sum_G += in[x].G * temp;
		sum_B += in[x].B * temp;
		


		//  .  .  .
    	//  .  .  .
    	//  .  .  x
		dc = 1;
		dr = -1;
		cc = c+dc;
		rr = r+dr;			
		x = ncols*rr+cc;
		y = 3*dc+dr+4;
		temp = filt[y];
		// pix = in[x];
		// sum_R += pix.R * temp;
		// sum_G += pix.G * temp;
		// sum_B += pix.B * temp;
		sum_R += in[x].R * temp;
		sum_G += in[x].G * temp;
		sum_B += in[x].B * temp;
		


    	x = ncols*r+c;
  
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;
	}

	t7 = 0;
	t7+= (int) in[ncols*r + 2*ncols].R;
	t7+= ((int) in[ncols*r + 2*ncols].G) << 8;
	t7+= ((int) in[ncols*r + 2*ncols].B) << 16;

	t8 = 0;
	t8+= (int) in[ncols*r + 2*ncols + 1].R;
	t8+= ((int) in[ncols*r + 2*ncols + 1].G) << 8;
	t8+= ((int) in[ncols*r + 2*ncols + 1].B) << 16;

	t9 = 0;
	t9+= (int) in[ncols*r + 2*ncols + 2].R;
	t9+= ((int) in[ncols*r + 2*ncols + 2].G) << 8;
	t9+= ((int) in[ncols*r + 2*ncols + 2].B) << 16;


}
