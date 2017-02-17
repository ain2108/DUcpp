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

pixel 	t1, t2, t3,
		t4, t5, t6,
		t7, t8, t9;

int 	filt1, filt2, filt3,
			filt4, filt5, filt6,
			filt7, filt8, filt9;

filt1 = filt[0];
filt2 = filt[1];
filt3 = filt[2];
filt4 = filt[3];
filt5 = filt[4];
filt6 = filt[5];
filt7 = filt[6];
filt8 = filt[7];
filt9 = filt[8];

t1 = in[0];
t2 = in[1];
t3 = in[2];
t4 = in[ncols];
t5 = in[ncols + 1];
t6 = in[ncols + 2];
t7 = in[ncols + ncols];
t8 = in[ncols + ncols + 1];
t9 = in[ncols + ncols + 2];
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

		// one less operation here
		
		// Increment the accumulators
		// temp = filt[6];
		sum_R += t7.R * filt7;
		sum_G += t7.G * filt7;
		sum_B += t7.B * filt7;
		


		//  .  .  .
    	//  .  .  .
    	//  .  x  .
		sum_R += t8.R * filt8;
		sum_G += t8.G * filt8;
		sum_B += t8.B * filt8;
		

		//  .  .  .
    	//  .  .  .
    	//  .  .  x
		sum_R += t9.R * filt9;
		sum_G += t9.G * filt9;
		sum_B += t9.B * filt9;

		t7 = t8;
		t8 = t9;
		t9 = in[ncols_sum + ncols + 2];


		//  .  .  .
    	//  x  .  .
    	//  .  .  .
		sum_R += t4.R * filt4;
		sum_G += t4.G * filt4;
		sum_B += t4.B * filt4;

		//  .  .  .
    	//  .  x  .
    	//  .  .  .
		sum_R += t5.R * filt5;
		sum_G += t5.G * filt5;
		sum_B += t5.B * filt5;

		//  .  .  .
    	//  .  .  x
    	//  .  .  .
		sum_R += t6.R * filt6;
		sum_G += t6.G * filt6;
		sum_B += t6.B * filt6;

		t4 = t5;
		t5 = t6;
		t6 = in[ncols_sum + 2];
		

		//  x  .  .
    	//  .  .  .
    	//  .  .  .
		sum_R += t1.R * filt1;
		sum_G += t1.G * filt1;
		sum_B += t1.B * filt1;
		

		//  .  x  .
    	//  .  .  .
    	//  .  .  .
		sum_R += t2.R * filt2;
		sum_G += t2.G * filt2;
		sum_B += t2.B * filt2;
		


		//  .  .  x
    	//  .  .  .
    	//  .  .  .		
		sum_R += t3.R * filt3;
		sum_G += t3.G * filt3;
		sum_B += t3.B * filt3;

		t1 = t2;
		t2 = t3;
		t3 = in[ncols_sum - ncols + 2];
		

		//printf("%d %d\n",ncols*r+c, ncols_sum);
    	//x = ncols_sum;
  

    	out[ncols_sum].R = (float) sum_R / d;
    	out[ncols_sum].G = (float) sum_G / d;
    	out[ncols_sum].B = (float) sum_B / d;
    	//++ncols_sum;
	}
	ncols_sum+=2;

	t1 = in[ncols_sum - ncols - 1];
	t2 = in[ncols_sum - ncols];
	t3 = in[ncols_sum - ncols + 1];

	t4 = in[ncols_sum - 1];
	t5 = in[ncols_sum];
	t6 = in[ncols_sum + 1];

	t7 = in[ncols_sum + ncols - 1];
	t8 = in[ncols_sum + ncols];
	t9 = in[ncols_sum + ncols + 1];	




}
