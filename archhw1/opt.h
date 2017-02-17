/*
	List of modifications:
	1) One less operation in calculation of filter element index
	2) Unrolled the loop
	3) temp variable added not to recalculate filt[y] every time

*/

// Fix the top border

const uchar d = filt[FILTER_BYTES-1];
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

           sum_R += in[x].R * filt[y];
           sum_G += in[x].G * filt[y];
           sum_B += in[x].B * filt[y];
         }
       }
     }

     uint x = ncols*r+c;
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
           
           sum_R += in[x].R * filt[y];
           sum_G += in[x].G * filt[y];
           sum_B += in[x].B * filt[y];
         }
       }
     }

     uint x = ncols*r+c;
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

           sum_R += in[x].R * filt[y];
           sum_G += in[x].G * filt[y];
           sum_B += in[x].B * filt[y];
         }
       }
     }

     uint x = ncols*r+c;
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

           sum_R += in[x].R * filt[y];
           sum_G += in[x].G * filt[y];
           sum_B += in[x].B * filt[y];
         }
       }
     }

     uint x = ncols*r+c;
     out[x].R = (float) sum_R / d;
     out[x].G = (float) sum_G / d;
     out[x].B = (float) sum_B / d;

   }
 




























































int temp;

// pixel 	t1, t2, t3,
// 		t4, t5, t6,
// 		t7, t8, t9;

// t1 = in[0];
// t2 = in[1];
// t3 = in[2];
// t4 = in[ncols];
// t5 = in[ncols + 1];
// t6 = in[ncols + 2];
// t7 = in[ncols + ncols];
// t8 = in[ncols + ncols + 1];
// t9 = in[ncols + ncols + 2];
int bound;
int ncols_sum = ncols + 1;
for (int r = 1; r < nrows - 1; r++) {
	bound = ncols_sum + ncols - 2;
	for (; ncols_sum < bound; ncols_sum++) {
    	
    	uint sum_R = 0;
    	uint sum_G = 0;
    	uint sum_B = 0;

    	/* Unrolling the loop */
      	
    	//  .  .  .
    	//  .  .  .
    	//  x  .  .
		uint x = ncols_sum + ncols - 1;

		// one less operation here
		
		// Increment the accumulators
		temp = filt[6];
		sum_R += in[x].R * temp;
		sum_G += in[x].G * temp;
		sum_B += in[x].B * temp;
		


		//  .  .  .
    	//  .  .  .
    	//  .  x  .
		++x;

		temp = filt[7];
		sum_R += in[x].R * temp;
		sum_G += in[x].G * temp;
		sum_B += in[x].B * temp;
		

		//  .  .  .
    	//  .  .  .
    	//  .  .  x
		++x;

		temp = filt[8];
		sum_R += in[x].R * temp;
		sum_G += in[x].G * temp;
		sum_B += in[x].B * temp;



		//  .  .  .
    	//  x  .  .
    	//  .  .  .
		x = ncols_sum -1;

		temp = filt[3];
		sum_R += in[x].R * temp;
		sum_G += in[x].G * temp;
		sum_B += in[x].B * temp;

		//  .  .  .
    	//  .  x  .
    	//  .  .  .
		++x;

		temp = filt[4];
		sum_R += in[x].R * temp;
		sum_G += in[x].G * temp;
		sum_B += in[x].B * temp;

		//  .  .  .
    	//  .  .  x
    	//  .  .  .
		++x;

		temp = filt[5];
		sum_R += in[x].R * temp;
		sum_G += in[x].G * temp;
		sum_B += in[x].B * temp;
		

		//  x  .  .
    	//  .  .  .
    	//  .  .  .
		x = ncols_sum - ncols - 1;

		temp = filt[0];
		sum_R += in[x].R * temp;
		sum_G += in[x].G * temp;
		sum_B += in[x].B * temp;
		

		//  .  x  .
    	//  .  .  .
    	//  .  .  .
		++x;
		temp = filt[1];
		sum_R += in[x].R * temp;
		sum_G += in[x].G * temp;
		sum_B += in[x].B * temp;
		


		//  .  .  x
    	//  .  .  .
    	//  .  .  .		
		++x;
		temp = filt[2];
		sum_R += in[x].R * temp;
		sum_G += in[x].G * temp;
		sum_B += in[x].B * temp;
		

		//printf("%d %d\n",ncols*r+c, ncols_sum);
    	//x = ncols_sum;
  

    	out[ncols_sum].R = (float) sum_R / d;
    	out[ncols_sum].G = (float) sum_G / d;
    	out[ncols_sum].B = (float) sum_B / d;
    	//++ncols_sum;
	}
	ncols_sum+=2;
}
