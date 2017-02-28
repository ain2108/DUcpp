/*
	List of modifications:
	1) One less operation in calculation of filter element index
	2) Unrolled the loop
	3) temp variable added not to recalculate filt[y] every time

*/

// Fix the top border

#define CACHE_SIZE 32768
#define UNROLLING_FACTOR 8

if(filt[4] == 1){
	memcpy(out, in, ncols*nrows*sizeof(pixel));
	return;
}

register int 	filt1, filt2, filt3,
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

const uchar d = filt[FILTER_BYTES-1];


// Fix the bottom border
for (int c = 1; c < ncols - 1; c++) {
   	  int r = nrows - 1;
      uint sum_R = 0;
    	uint sum_G = 0;
    	uint sum_B = 0;


		//  .  .  .
    	//  x  .  .
    	//  .  .  .
		//x = ncols_sum -1;
		uint x = r*ncols + c - 1;
		sum_R += in[x].R * filt4;
		sum_G += in[x].G * filt4;
		sum_B += in[x].B * filt4;

		//  .  .  .
    	//  .  x  .
    	//  .  .  .
		++x;
		sum_R += in[x].R * filt5;
		sum_G += in[x].G * filt5;
		sum_B += in[x].B * filt5;

		//  .  .  .
    	//  .  .  x
    	//  .  .  .
		++x;
		sum_R += in[x].R * filt6;
		sum_G += in[x].G * filt6;
		sum_B += in[x].B * filt6;
		

		//  x  .  .
    	//  .  .  .
    	//  .  .  .
		x = r*ncols - ncols + c - 1;
		//printf("%d\n", x);
		sum_R += in[x].R * filt1;
		sum_G += in[x].G * filt1;
		sum_B += in[x].B * filt1;
		

		//  .  x  .
    	//  .  .  .
    	//  .  .  .
		++x;
		sum_R += in[x].R * filt2;
		sum_G += in[x].G * filt2;
		sum_B += in[x].B * filt2;
		


		//  .  .  x
    	//  .  .  .
    	//  .  .  .		
		++x;
		sum_R += in[x].R * filt3;
		sum_G += in[x].G * filt3;
		sum_B += in[x].B * filt3;
		//printf("c:%d sum:%d \n", c, ncols_sum);

		x = r*ncols + c;
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;
 }




	int c = 0;
    for (int r = 0; r < nrows; r++) {
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
    for (int r = 0; r < nrows; r++) {
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
 
for (int c = 1; c < ncols - 1; c++) {
   	int r = 0;
    uint sum_R = 0;
	uint sum_G = 0;
	uint sum_B = 0;
  	
	//  .  .  .
	//  .  .  .
	//  x  .  .
	//uint x = ncols_sum + ncols - 1;
	uint x = r*ncols + ncols + c - 1;

	// Increment the accumulators
	sum_R += in[x].R * filt7;
	sum_G += in[x].G * filt7;
	sum_B += in[x].B * filt7;
	//printf("%d\n", x);
	
	//  .  .  .
	//  .  .  .
	//  .  x  .
	++x;
	sum_R += in[x].R * filt8;
	sum_G += in[x].G * filt8;
	sum_B += in[x].B * filt8;
	

	//  .  .  .
	//  .  .  .
	//  .  .  x
	++x;
	sum_R += in[x].R * filt9;
	sum_G += in[x].G * filt9;
	sum_B += in[x].B * filt9;



	//  .  .  .
	//  x  .  .
	//  .  .  .
	//x = ncols_sum -1;
	x = r*ncols + c - 1;
	sum_R += in[x].R * filt4;
	sum_G += in[x].G * filt4;
	sum_B += in[x].B * filt4;

	//  .  .  .
	//  .  x  .
	//  .  .  .
	++x;
	sum_R += in[x].R * filt5;
	sum_G += in[x].G * filt5;
	sum_B += in[x].B * filt5;

	//  .  .  .
	//  .  .  x
	//  .  .  .
	++x;
	sum_R += in[x].R * filt6;
	sum_G += in[x].G * filt6;
	sum_B += in[x].B * filt6;

	x = r*ncols + c;
	out[x].R = (float) sum_R / d;
	out[x].G = (float) sum_G / d;
	out[x].B = (float) sum_B / d;
}























/* Now that we calculated the edges, we do not need the 
conditionals inside the loop anymore. */




//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
////////////////////////// EDGE //////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
if(filt[4] == 5){

int ncols_sum = ncols + 1;
int old_ncols_sum = ncols_sum;


int bytes_used = ncols * sizeof(pixel);
int niter = bytes_used / 8192;
int cols_left = 0;

/* If the picture does not fit in the cache */
if(niter != 0){
	cols_left = bytes_used % 8192;

int bound = 0;
int old_bound = 0;
for(int j = 0; j < niter; j++){
	old_bound = bound + 1;
	bound = (j + 1) * 2048 - 1; // so divides evenly


for (int r = 1; r < nrows - 1; r++) {

	for (int c = old_bound; c <= bound; c++) {
    	
    	uint sum_R = 0;
    	uint sum_G = 0;
    	uint sum_B = 0;

    	/* Unrolling the loop */
      
		
		//  .  .  .
    	//  .  .  .
    	//  .  x  .
		uint x = r*ncols + ncols + c;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		

		//  .  .  .
    	//  x  .  .
    	//  .  .  .
		//x = ncols_sum -1;
		x = r*ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;

		//  .  .  .
    	//  .  x  .
    	//  .  .  .
		++x;
		sum_R += in[x].R * 5;
		sum_G += in[x].G * 5;
		sum_B += in[x].B * 5;

		//  .  .  .
    	//  .  .  x
    	//  .  .  .
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;

		

		//  .  x  .
    	//  .  .  .
    	//  .  .  .
		x = r*ncols - ncols + c;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		

		x = r*ncols + c;
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;
	}
}
}

ncols_sum = 0;
for (int r = 1; r < nrows - 1; r++) {
	for (int c = bound; c < ncols - 1; c++) {
    	uint sum_R = 0;
    	uint sum_G = 0;
    	uint sum_B = 0;

    	/* Unrolling the loop */
      
		
		//  .  .  .
    	//  .  .  .
    	//  .  x  .
		uint x = r*ncols + ncols + c;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		

		//  .  .  .
    	//  x  .  .
    	//  .  .  .
		x = r*ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;

		//  .  .  .
    	//  .  x  .
    	//  .  .  .
		++x;
		sum_R += in[x].R * 5;
		sum_G += in[x].G * 5;
		sum_B += in[x].B * 5;

		//  .  .  .
    	//  .  .  x
    	//  .  .  .
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;

		

		//  .  x  .
    	//  .  .  .
    	//  .  .  .
		x = r*ncols - ncols + c;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		

		x = r*ncols + c;
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;
	}
}

}else{
	
	int unrolled_iterations = ((ncols - 2) / UNROLLING_FACTOR) * UNROLLING_FACTOR;
	for (int r = 1; r < nrows - 1; r++) {

	int c;
	for (c = 1; c < unrolled_iterations + 1; c++) {
    	
    	uint sum_R = 0;
    	uint sum_G = 0;
    	uint sum_B = 0;

    	/* Unrolling the loop */
      
		
		//  .  .  .
    	//  .  .  .
    	//  .  x  .
		uint x = r*ncols + ncols + c;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		

		//  .  .  .
    	//  x  .  .
    	//  .  .  .
		//x = ncols_sum -1;
		x = r*ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;

		//  .  .  .
    	//  .  x  .
    	//  .  .  .
		++x;
		sum_R += in[x].R * 5;
		sum_G += in[x].G * 5;
		sum_B += in[x].B * 5;

		//  .  .  .
    	//  .  .  x
    	//  .  .  .
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;

		

		//  .  x  .
    	//  .  .  .
    	//  .  .  .
		x = r*ncols - ncols + c;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		

		x = r*ncols + c;
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;

    	/* UNROLL */
    	c++;
    	sum_R = 0;
    	sum_G = 0;
    	sum_B = 0;
    	x = r*ncols + ncols + c;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R += in[x].R * 5;
		sum_G += in[x].G * 5;
		sum_B += in[x].B * 5;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols - ncols + c;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols + c;
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;
    	/* UNROLL */
    	c++;
    	sum_R = 0;
    	sum_G = 0;
    	sum_B = 0;
    	x = r*ncols + ncols + c;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R += in[x].R * 5;
		sum_G += in[x].G * 5;
		sum_B += in[x].B * 5;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols - ncols + c;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols + c;
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;
    	/* UNROLL */
    	c++;
    	sum_R = 0;
    	sum_G = 0;
    	sum_B = 0;
    	x = r*ncols + ncols + c;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R += in[x].R * 5;
		sum_G += in[x].G * 5;
		sum_B += in[x].B * 5;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols - ncols + c;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols + c;
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;
    	/* UNROLL */
    	c++;
    	sum_R = 0;
    	sum_G = 0;
    	sum_B = 0;
    	x = r*ncols + ncols + c;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R += in[x].R * 5;
		sum_G += in[x].G * 5;
		sum_B += in[x].B * 5;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols - ncols + c;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols + c;
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;
    	/* UNROLL */
    	c++;
    	sum_R = 0;
    	sum_G = 0;
    	sum_B = 0;
    	x = r*ncols + ncols + c;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R += in[x].R * 5;
		sum_G += in[x].G * 5;
		sum_B += in[x].B * 5;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols - ncols + c;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols + c;
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;
    	/* UNROLL */
    	c++;
    	sum_R = 0;
    	sum_G = 0;
    	sum_B = 0;
    	x = r*ncols + ncols + c;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R += in[x].R * 5;
		sum_G += in[x].G * 5;
		sum_B += in[x].B * 5;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols - ncols + c;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols + c;
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;
    	/* UNROLL */
    	c++;
    	sum_R = 0;
    	sum_G = 0;
    	sum_B = 0;
    	x = r*ncols + ncols + c;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R += in[x].R * 5;
		sum_G += in[x].G * 5;
		sum_B += in[x].B * 5;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols - ncols + c;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols + c;
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;

		
	}

	for (int c = unrolled_iterations + 1; c < ncols - 1; c++) {
    	uint sum_R = 0;
    	uint sum_G = 0;
    	uint sum_B = 0;

    	/* Unrolling the loop */
      
		
		//  .  .  .
    	//  .  .  .
    	//  .  x  .
		uint x = r*ncols + ncols + c;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		

		//  .  .  .
    	//  x  .  .
    	//  .  .  .
		x = r*ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;

		//  .  .  .
    	//  .  x  .
    	//  .  .  .
		++x;
		sum_R += in[x].R * 5;
		sum_G += in[x].G * 5;
		sum_B += in[x].B * 5;

		//  .  .  .
    	//  .  .  x
    	//  .  .  .
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;

		

		//  .  x  .
    	//  .  .  .
    	//  .  .  .
		x = r*ncols - ncols + c;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		

		x = r*ncols + c;
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;
	}
}
}
return;


//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
////////////////////////// SHARPEN //////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
/* Sharpen filter optimizatin */
}else if(filt[4] == 8){



int bytes_used = ncols * sizeof(pixel);
int niter = bytes_used / 8192;
int cols_left = 0;

/* If the picture does not fit in the cache */
if(niter != 0){
	cols_left = bytes_used % 8192;

int bound = 0;
int old_bound = 0;
for(int j = 0; j < niter; j++){
	old_bound = bound + 1;
	bound = (j + 1) * 2048 - 1; // so divides evenly

for (int r = 1; r < nrows - 1; r++) {

	for (int c = old_bound; c <= bound; c++) {
    	
    	uint sum_R = 0;
    	uint sum_G = 0;
    	uint sum_B = 0;

    	/* Unrolling the loop */
      	
    	//  .  .  .
    	//  .  .  .
    	//  x  .  .
		//uint x = ncols_sum + ncols - 1;
		uint x = r*ncols + ncols + c - 1;

		// Increment the accumulators
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		
		//  .  .  .
    	//  .  .  .
    	//  .  x  .
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		

		//  .  .  .
    	//  .  .  .
    	//  .  .  x
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;



		//  .  .  .
    	//  x  .  .
    	//  .  .  .
		//x = ncols_sum -1;
		x = r*ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;

		//  .  .  .
    	//  .  x  .
    	//  .  .  .
		++x;
		sum_R += in[x].R * 8;
		sum_G += in[x].G * 8;
		sum_B += in[x].B * 8;

		//  .  .  .
    	//  .  .  x
    	//  .  .  .
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		

		//  x  .  .
    	//  .  .  .
    	//  .  .  .
		x = r*ncols - ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		

		//  .  x  .
    	//  .  .  .
    	//  .  .  .
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		


		//  .  .  x
    	//  .  .  .
    	//  .  .  .		
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;

		x = r*ncols + c;

    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;
	}
}
}

ncols_sum = 0;
for (int r = 1; r < nrows - 1; r++) {
	for (int c = bound; c < ncols - 1; c++) {
    	uint sum_R = 0;
    	uint sum_G = 0;
    	uint sum_B = 0;

    	/* Unrolling the loop */
      	
    	//  .  .  .
    	//  .  .  .
    	//  x  .  .
		//uint x = ncols_sum + ncols - 1;
		uint x = r*ncols + ncols + c - 1;

		// Increment the accumulators
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		
		//  .  .  .
    	//  .  .  .
    	//  .  x  .
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		

		//  .  .  .
    	//  .  .  .
    	//  .  .  x
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;



		//  .  .  .
    	//  x  .  .
    	//  .  .  .
		//x = ncols_sum -1;
		x = r*ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;

		//  .  .  .
    	//  .  x  .
    	//  .  .  .
		++x;
		sum_R += in[x].R * 8;
		sum_G += in[x].G * 8;
		sum_B += in[x].B * 8;

		//  .  .  .
    	//  .  .  x
    	//  .  .  .
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		

		//  x  .  .
    	//  .  .  .
    	//  .  .  .
		x = r*ncols - ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		

		//  .  x  .
    	//  .  .  .
    	//  .  .  .
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		


		//  .  .  x
    	//  .  .  .
    	//  .  .  .		
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;

		x = r*ncols + c;

    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;
	}
}

}else{
	int unrolled_iterations = ((ncols - 2) / UNROLLING_FACTOR) * UNROLLING_FACTOR;
	for (int r = 1; r < nrows - 1; r++) {

	int c;
	for (c = 1; c < unrolled_iterations + 1; c++) {
    	
    	uint sum_R = 0;
    	uint sum_G = 0;
    	uint sum_B = 0;

    	/* Unrolling the loop */
      	
    	//  .  .  .
    	//  .  .  .
    	//  x  .  .
		uint x = r*ncols + ncols + c - 1;

		// Increment the accumulators
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		
		//  .  .  .
    	//  .  .  .
    	//  .  x  .
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		

		//  .  .  .
    	//  .  .  .
    	//  .  .  x
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;



		//  .  .  .
    	//  x  .  .
    	//  .  .  .
		x = r*ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;

		//  .  .  .
    	//  .  x  .
    	//  .  .  .
		++x;
		sum_R += in[x].R * 8;
		sum_G += in[x].G * 8;
		sum_B += in[x].B * 8;

		//  .  .  .
    	//  .  .  x
    	//  .  .  .
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		

		//  x  .  .
    	//  .  .  .
    	//  .  .  .
		x = r*ncols - ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		

		//  .  x  .
    	//  .  .  .
    	//  .  .  .
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		


		//  .  .  x
    	//  .  .  .
    	//  .  .  .		
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;

		x = r*ncols + c;

    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;

    	/* UNROLL */
    	c++;
    	sum_R = 0;
    	sum_G = 0;
    	sum_B = 0;
		x = r*ncols + ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R += in[x].R * 8;
		sum_G += in[x].G * 8;
		sum_B += in[x].B * 8;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols - ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols + c;
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;
    	/* UNROLL */
    	c++;
    	sum_R = 0;
    	sum_G = 0;
    	sum_B = 0;
		x = r*ncols + ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R += in[x].R * 8;
		sum_G += in[x].G * 8;
		sum_B += in[x].B * 8;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols - ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols + c;
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;
    	/* UNROLL */
    	c++;
    	sum_R = 0;
    	sum_G = 0;
    	sum_B = 0;
		x = r*ncols + ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R += in[x].R * 8;
		sum_G += in[x].G * 8;
		sum_B += in[x].B * 8;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols - ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols + c;
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;
    	/* UNROLL */
    	c++;
    	sum_R = 0;
    	sum_G = 0;
    	sum_B = 0;
		x = r*ncols + ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R += in[x].R * 8;
		sum_G += in[x].G * 8;
		sum_B += in[x].B * 8;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols - ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols + c;
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;
    	/* UNROLL */
    	c++;
    	sum_R = 0;
    	sum_G = 0;
    	sum_B = 0;
		x = r*ncols + ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R += in[x].R * 8;
		sum_G += in[x].G * 8;
		sum_B += in[x].B * 8;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols - ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols + c;
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;
    	/* UNROLL */
    	c++;
    	sum_R = 0;
    	sum_G = 0;
    	sum_B = 0;
		x = r*ncols + ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R += in[x].R * 8;
		sum_G += in[x].G * 8;
		sum_B += in[x].B * 8;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols - ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols + c;
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;
    	/* UNROLL */
    	c++;
    	sum_R = 0;
    	sum_G = 0;
    	sum_B = 0;
		x = r*ncols + ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R += in[x].R * 8;
		sum_G += in[x].G * 8;
		sum_B += in[x].B * 8;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols - ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		x = r*ncols + c;
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;
	}

	//printf("c: %d\n", c);
	for (int c = unrolled_iterations + 1; c < ncols - 1; c++) {
    	
    	uint sum_R = 0;
    	uint sum_G = 0;
    	uint sum_B = 0;

    	/* Unrolling the loop */
      	
    	//  .  .  .
    	//  .  .  .
    	//  x  .  .
		//uint x = ncols_sum + ncols - 1;
		uint x = r*ncols + ncols + c - 1;

		// Increment the accumulators
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		
		//  .  .  .
    	//  .  .  .
    	//  .  x  .
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		

		//  .  .  .
    	//  .  .  .
    	//  .  .  x
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;



		//  .  .  .
    	//  x  .  .
    	//  .  .  .
		x = r*ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;

		//  .  .  .
    	//  .  x  .
    	//  .  .  .
		++x;
		sum_R += in[x].R * 8;
		sum_G += in[x].G * 8;
		sum_B += in[x].B * 8;

		//  .  .  .
    	//  .  .  x
    	//  .  .  .
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		

		//  x  .  .
    	//  .  .  .
    	//  .  .  .
		x = r*ncols - ncols + c - 1;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		

		//  .  x  .
    	//  .  .  .
    	//  .  .  .
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;
		


		//  .  .  x
    	//  .  .  .
    	//  .  .  .		
		++x;
		sum_R -= in[x].R;
		sum_G -= in[x].G;
		sum_B -= in[x].B;

		x = r*ncols + c;

    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;
	}
}
}
	return;

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
////////////////////////// GAUSSIAN //////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
}else if(filt[4] == 4){

int ncols_sum = ncols + 1;
int old_ncols_sum = ncols_sum;


int bytes_used = ncols * sizeof(pixel);
int niter = bytes_used / 8192;
int cols_left = 0;

/* If the picture does not fit in the cache */
if(niter != 0){
	cols_left = bytes_used % 8192;

int bound = 0;
int old_bound = 0;
for(int j = 0; j < niter; j++){
	old_bound = bound + 1;
	bound = (j + 1) * 2048 - 1; // so divides evenly

for (int r = 1; r < nrows - 1; r++) {

	for (int c = old_bound; c <= bound; c++) {
    	
    	uint sum_R = 0;
    	uint sum_G = 0;
    	uint sum_B = 0;
      	
    	//  .  .  .
    	//  .  .  .
    	//  x  .  .
		uint x = r*ncols + ncols + c - 1;

		// Increment the accumulators
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;
		
		//  .  .  .
    	//  .  .  .
    	//  .  x  .
		++x;
		sum_R += in[x].R * 2; 
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;
		

		//  .  .  .
    	//  .  .  .
    	//  .  .  x
		++x;
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;



		//  .  .  .
    	//  x  .  .
    	//  .  .  .
		x = r*ncols + c - 1;
		sum_R += in[x].R * 2;
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;

		//  .  .  .
    	//  .  x  .
    	//  .  .  .
		++x;
		sum_R += in[x].R * 4;
		sum_G += in[x].G * 4;
		sum_B += in[x].B * 4;

		//  .  .  .
    	//  .  .  x
    	//  .  .  .
		++x;
		sum_R += in[x].R * 2;
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;
		

		//  x  .  .
    	//  .  .  .
    	//  .  .  .
		x = r*ncols - ncols + c - 1;
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;
		

		//  .  x  .
    	//  .  .  .
    	//  .  .  .
		++x;
		sum_R += in[x].R * 2;
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;
		


		//  .  .  x
    	//  .  .  .
    	//  .  .  .		
		++x;
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;

		x = r*ncols + c;
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;
	}
}
}

ncols_sum = 0;
for (int r = 1; r < nrows - 1; r++) {
	for (int c = bound; c < ncols - 1; c++) {
    	
    uint sum_R = 0;
    	uint sum_G = 0;
    	uint sum_B = 0;

    	/* Unrolling the loop */
      	
    	//  .  .  .
    	//  .  .  .
    	//  x  .  .
		uint x = r*ncols + ncols + c - 1;

		// Increment the accumulators
		sum_R += in[x].R * filt7;
		sum_G += in[x].G * filt7;
		sum_B += in[x].B * filt7;
		
		//  .  .  .
    	//  .  .  .
    	//  .  x  .
		++x;
		sum_R += in[x].R * filt8;
		sum_G += in[x].G * filt8;
		sum_B += in[x].B * filt8;
		

		//  .  .  .
    	//  .  .  .
    	//  .  .  x
		++x;
		sum_R += in[x].R * filt9;
		sum_G += in[x].G * filt9;
		sum_B += in[x].B * filt9;



		//  .  .  .
    	//  x  .  .
    	//  .  .  .
		x = r*ncols + c - 1;
		sum_R += in[x].R * filt4;
		sum_G += in[x].G * filt4;
		sum_B += in[x].B * filt4;

		//  .  .  .
    	//  .  x  .
    	//  .  .  .
		++x;
		sum_R += in[x].R * filt5;
		sum_G += in[x].G * filt5;
		sum_B += in[x].B * filt5;

		//  .  .  .
    	//  .  .  x
    	//  .  .  .
		++x;
		sum_R += in[x].R * filt6;
		sum_G += in[x].G * filt6;
		sum_B += in[x].B * filt6;
		

		//  x  .  .
    	//  .  .  .
    	//  .  .  .
		x = r*ncols - ncols + c - 1;
		sum_R += in[x].R * filt1;
		sum_G += in[x].G * filt1;
		sum_B += in[x].B * filt1;
		

		//  .  x  .
    	//  .  .  .
    	//  .  .  .
		++x;
		sum_R += in[x].R * filt2;
		sum_G += in[x].G * filt2;
		sum_B += in[x].B * filt2;
		


		//  .  .  x
    	//  .  .  .
    	//  .  .  .		
		++x;
		sum_R += in[x].R * filt3;
		sum_G += in[x].G * filt3;
		sum_B += in[x].B * filt3;

		x = r*ncols + c;
		
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;
	}
}

}else{
	
	int unrolled_iterations = ((ncols - 2) / UNROLLING_FACTOR) * UNROLLING_FACTOR;
	for (int r = 1; r < nrows - 1; r++) {

	int c;
	for (c = 1; c < unrolled_iterations + 1; c++) {
    	
    	uint sum_R = 0;
    	uint sum_G = 0;
    	uint sum_B = 0;

    	//  .  .  .
    	//  .  .  .
    	//  x  .  .
		uint x = r*ncols + ncols + c - 1;

		// Increment the accumulators
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;
		
		//  .  .  .
    	//  .  .  .
    	//  .  x  .
		++x;
		sum_R += in[x].R * 2; 
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;
		

		//  .  .  .
    	//  .  .  .
    	//  .  .  x
		++x;
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;



		//  .  .  .
    	//  x  .  .
    	//  .  .  .
		//x = ncols_sum -1;
		x = r*ncols + c - 1;
		sum_R += in[x].R * 2;
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;

		//  .  .  .
    	//  .  x  .
    	//  .  .  .
		++x;
		sum_R += in[x].R * 4;
		sum_G += in[x].G * 4;
		sum_B += in[x].B * 4;

		//  .  .  .
    	//  .  .  x
    	//  .  .  .
		++x;
		sum_R += in[x].R * 2;
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;
		

		//  x  .  .
    	//  .  .  .
    	//  .  .  .
		x = r*ncols - ncols + c - 1;
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;
		

		//  .  x  .
    	//  .  .  .
    	//  .  .  .
		++x;
		sum_R += in[x].R * 2;
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;
		


		//  .  .  x
    	//  .  .  .
    	//  .  .  .		
		++x;
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;

		x = r*ncols + c;
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;

    	/* UNROLL */
    	c++;
    	sum_R = 0;
    	sum_G = 0;
    	sum_B = 0;
    	x = r*ncols + ncols + c - 1;
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;
		++x;
		sum_R += in[x].R * 2; 
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;
		++x;
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;
		x = r*ncols + c - 1;
		sum_R += in[x].R * 2;
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;
		++x;
		sum_R += in[x].R * 4;
		sum_G += in[x].G * 4;
		sum_B += in[x].B * 4;
		++x;
		sum_R += in[x].R * 2;
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;
		x = r*ncols - ncols + c - 1;
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;
		++x;
		sum_R += in[x].R * 2;
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;	
		++x;
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;
		x = r*ncols + c;
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;
    	/* UNROLL */
    	c++;
    	sum_R = 0;
    	sum_G = 0;
    	sum_B = 0;
    	x = r*ncols + ncols + c - 1;
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;
		++x;
		sum_R += in[x].R * 2; 
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;
		++x;
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;
		x = r*ncols + c - 1;
		sum_R += in[x].R * 2;
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;
		++x;
		sum_R += in[x].R * 4;
		sum_G += in[x].G * 4;
		sum_B += in[x].B * 4;
		++x;
		sum_R += in[x].R * 2;
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;
		x = r*ncols - ncols + c - 1;
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;
		++x;
		sum_R += in[x].R * 2;
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;	
		++x;
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;
		x = r*ncols + c;
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;
    	/* UNROLL */
    	c++;
    	sum_R = 0;
    	sum_G = 0;
    	sum_B = 0;
    	x = r*ncols + ncols + c - 1;
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;
		++x;
		sum_R += in[x].R * 2; 
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;
		++x;
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;
		x = r*ncols + c - 1;
		sum_R += in[x].R * 2;
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;
		++x;
		sum_R += in[x].R * 4;
		sum_G += in[x].G * 4;
		sum_B += in[x].B * 4;
		++x;
		sum_R += in[x].R * 2;
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;
		x = r*ncols - ncols + c - 1;
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;
		++x;
		sum_R += in[x].R * 2;
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;	
		++x;
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;
		x = r*ncols + c;
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;
    	/* UNROLL */
    	c++;
    	sum_R = 0;
    	sum_G = 0;
    	sum_B = 0;
    	x = r*ncols + ncols + c - 1;
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;
		++x;
		sum_R += in[x].R * 2; 
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;
		++x;
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;
		x = r*ncols + c - 1;
		sum_R += in[x].R * 2;
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;
		++x;
		sum_R += in[x].R * 4;
		sum_G += in[x].G * 4;
		sum_B += in[x].B * 4;
		++x;
		sum_R += in[x].R * 2;
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;
		x = r*ncols - ncols + c - 1;
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;
		++x;
		sum_R += in[x].R * 2;
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;	
		++x;
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;
		x = r*ncols + c;
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;
    	/* UNROLL */
    	c++;
    	sum_R = 0;
    	sum_G = 0;
    	sum_B = 0;
    	x = r*ncols + ncols + c - 1;
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;
		++x;
		sum_R += in[x].R * 2; 
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;
		++x;
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;
		x = r*ncols + c - 1;
		sum_R += in[x].R * 2;
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;
		++x;
		sum_R += in[x].R * 4;
		sum_G += in[x].G * 4;
		sum_B += in[x].B * 4;
		++x;
		sum_R += in[x].R * 2;
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;
		x = r*ncols - ncols + c - 1;
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;
		++x;
		sum_R += in[x].R * 2;
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;	
		++x;
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;
		x = r*ncols + c;
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;
    	/* UNROLL */
    	c++;
    	sum_R = 0;
    	sum_G = 0;
    	sum_B = 0;
    	x = r*ncols + ncols + c - 1;
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;
		++x;
		sum_R += in[x].R * 2; 
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;
		++x;
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;
		x = r*ncols + c - 1;
		sum_R += in[x].R * 2;
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;
		++x;
		sum_R += in[x].R * 4;
		sum_G += in[x].G * 4;
		sum_B += in[x].B * 4;
		++x;
		sum_R += in[x].R * 2;
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;
		x = r*ncols - ncols + c - 1;
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;
		++x;
		sum_R += in[x].R * 2;
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;	
		++x;
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;
		x = r*ncols + c;
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;
    	/* UNROLL */
    	c++;
    	sum_R = 0;
    	sum_G = 0;
    	sum_B = 0;
    	x = r*ncols + ncols + c - 1;
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;
		++x;
		sum_R += in[x].R * 2; 
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;
		++x;
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;
		x = r*ncols + c - 1;
		sum_R += in[x].R * 2;
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;
		++x;
		sum_R += in[x].R * 4;
		sum_G += in[x].G * 4;
		sum_B += in[x].B * 4;
		++x;
		sum_R += in[x].R * 2;
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;
		x = r*ncols - ncols + c - 1;
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;
		++x;
		sum_R += in[x].R * 2;
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;	
		++x;
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;
		x = r*ncols + c;
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;
	}

	for (int c = unrolled_iterations + 1; c < ncols - 1; c++) {
    	
    	uint sum_R = 0;
    	uint sum_G = 0;
    	uint sum_B = 0;

    	//  .  .  .
    	//  .  .  .
    	//  x  .  .
		uint x = r*ncols + ncols + c - 1;

		// Increment the accumulators
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;
		
		//  .  .  .
    	//  .  .  .
    	//  .  x  .
		++x;
		sum_R += in[x].R * 2; 
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;
		

		//  .  .  .
    	//  .  .  .
    	//  .  .  x
		++x;
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;



		//  .  .  .
    	//  x  .  .
    	//  .  .  .
		//x = ncols_sum -1;
		x = r*ncols + c - 1;
		sum_R += in[x].R * 2;
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;

		//  .  .  .
    	//  .  x  .
    	//  .  .  .
		++x;
		sum_R += in[x].R * 4;
		sum_G += in[x].G * 4;
		sum_B += in[x].B * 4;

		//  .  .  .
    	//  .  .  x
    	//  .  .  .
		++x;
		sum_R += in[x].R * 2;
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;
		

		//  x  .  .
    	//  .  .  .
    	//  .  .  .
		x = r*ncols - ncols + c - 1;
		//printf("%d\n", x);
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;
		

		//  .  x  .
    	//  .  .  .
    	//  .  .  .
		++x;
		sum_R += in[x].R * 2;
		sum_G += in[x].G * 2;
		sum_B += in[x].B * 2;
		


		//  .  .  x
    	//  .  .  .
    	//  .  .  .		
		++x;
		sum_R += in[x].R;
		sum_G += in[x].G;
		sum_B += in[x].B;
		//printf("c:%d sum:%d \n", c, ncols_sum);

		x = r*ncols + c;
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;

	}
}
}
	return;
}












int ncols_sum = ncols + 1;
int old_ncols_sum = ncols_sum;


int bytes_used = ncols * sizeof(pixel);
int niter = bytes_used / 8192;
int cols_left = 0;

/* If the picture does not fit in the cache */
if(niter != 0){
	cols_left = bytes_used % 8192;

int bound = 0;
int old_bound = 0;
for(int j = 0; j < niter; j++){
	old_bound = bound + 1;
	bound = (j + 1) * 2048 - 1; // so divides evenly

for (int r = 1; r < nrows - 1; r++) {

	for (int c = old_bound; c <= bound; c++) {
    	
    	uint sum_R = 0;
    	uint sum_G = 0;
    	uint sum_B = 0;
      	
    	//  .  .  .
    	//  .  .  .
    	//  x  .  .
		uint x = r*ncols + ncols + c - 1;

		// Increment the accumulators
		sum_R += in[x].R * filt7;
		sum_G += in[x].G * filt7;
		sum_B += in[x].B * filt7;
		
		//  .  .  .
    	//  .  .  .
    	//  .  x  .
		++x;
		sum_R += in[x].R * filt8;
		sum_G += in[x].G * filt8;
		sum_B += in[x].B * filt8;
		

		//  .  .  .
    	//  .  .  .
    	//  .  .  x
		++x;
		sum_R += in[x].R * filt9;
		sum_G += in[x].G * filt9;
		sum_B += in[x].B * filt9;



		//  .  .  .
    	//  x  .  .
    	//  .  .  .
		x = r*ncols + c - 1;
		sum_R += in[x].R * filt4;
		sum_G += in[x].G * filt4;
		sum_B += in[x].B * filt4;

		//  .  .  .
    	//  .  x  .
    	//  .  .  .
		++x;
		sum_R += in[x].R * filt5;
		sum_G += in[x].G * filt5;
		sum_B += in[x].B * filt5;

		//  .  .  .
    	//  .  .  x
    	//  .  .  .
		++x;
		sum_R += in[x].R * filt6;
		sum_G += in[x].G * filt6;
		sum_B += in[x].B * filt6;
		

		//  x  .  .
    	//  .  .  .
    	//  .  .  .
		x = r*ncols - ncols + c - 1;
		sum_R += in[x].R * filt1;
		sum_G += in[x].G * filt1;
		sum_B += in[x].B * filt1;
		

		//  .  x  .
    	//  .  .  .
    	//  .  .  .
		++x;
		sum_R += in[x].R * filt2;
		sum_G += in[x].G * filt2;
		sum_B += in[x].B * filt2;
		


		//  .  .  x
    	//  .  .  .
    	//  .  .  .		
		++x;
		sum_R += in[x].R * filt3;
		sum_G += in[x].G * filt3;
		sum_B += in[x].B * filt3;

		x = r*ncols + c;
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;
	}
}
}

ncols_sum = 0;
for (int r = 1; r < nrows - 1; r++) {
	for (int c = bound; c < ncols - 1; c++) {
    	
    uint sum_R = 0;
    	uint sum_G = 0;
    	uint sum_B = 0;

    	/* Unrolling the loop */
      	
    	//  .  .  .
    	//  .  .  .
    	//  x  .  .
		//uint x = ncols_sum + ncols - 1;
		uint x = r*ncols + ncols + c - 1;

		// Increment the accumulators
		sum_R += in[x].R * filt7;
		sum_G += in[x].G * filt7;
		sum_B += in[x].B * filt7;
		
		//  .  .  .
    	//  .  .  .
    	//  .  x  .
		++x;
		sum_R += in[x].R * filt8;
		sum_G += in[x].G * filt8;
		sum_B += in[x].B * filt8;
		

		//  .  .  .
    	//  .  .  .
    	//  .  .  x
		++x;
		sum_R += in[x].R * filt9;
		sum_G += in[x].G * filt9;
		sum_B += in[x].B * filt9;



		//  .  .  .
    	//  x  .  .
    	//  .  .  .
		x = r*ncols + c - 1;
		sum_R += in[x].R * filt4;
		sum_G += in[x].G * filt4;
		sum_B += in[x].B * filt4;

		//  .  .  .
    	//  .  x  .
    	//  .  .  .
		++x;
		sum_R += in[x].R * filt5;
		sum_G += in[x].G * filt5;
		sum_B += in[x].B * filt5;

		//  .  .  .
    	//  .  .  x
    	//  .  .  .
		++x;
		sum_R += in[x].R * filt6;
		sum_G += in[x].G * filt6;
		sum_B += in[x].B * filt6;
		

		//  x  .  .
    	//  .  .  .
    	//  .  .  .
		x = r*ncols - ncols + c - 1;
		sum_R += in[x].R * filt1;
		sum_G += in[x].G * filt1;
		sum_B += in[x].B * filt1;
		

		//  .  x  .
    	//  .  .  .
    	//  .  .  .
		++x;
		sum_R += in[x].R * filt2;
		sum_G += in[x].G * filt2;
		sum_B += in[x].B * filt2;
		


		//  .  .  x
    	//  .  .  .
    	//  .  .  .		
		++x;
		sum_R += in[x].R * filt3;
		sum_G += in[x].G * filt3;
		sum_B += in[x].B * filt3;

		x = r*ncols + c;
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;
	}
}

}else{
	
	int unrolled_iterations = ((ncols - 2) / UNROLLING_FACTOR) * UNROLLING_FACTOR;
	for (int r = 1; r < nrows - 1; r++) {

	int c;
	for (c = 1; c < unrolled_iterations + 1; c++) {
    	
    	uint sum_R = 0;
    	uint sum_G = 0;
    	uint sum_B = 0;

    	/* Unrolling the loop */
      	
    	//  .  .  .
    	//  .  .  .
    	//  x  .  .
		uint x = r*ncols + ncols + c - 1;

		// Increment the accumulators
		sum_R += in[x].R * filt7;
		sum_G += in[x].G * filt7;
		sum_B += in[x].B * filt7;
		
		//  .  .  .
    	//  .  .  .
    	//  .  x  .
		++x;
		sum_R += in[x].R * filt8;
		sum_G += in[x].G * filt8;
		sum_B += in[x].B * filt8;
		

		//  .  .  .
    	//  .  .  .
    	//  .  .  x
		++x;
		sum_R += in[x].R * filt9;
		sum_G += in[x].G * filt9;
		sum_B += in[x].B * filt9;



		//  .  .  .
    	//  x  .  .
    	//  .  .  .
		x = r*ncols + c - 1;
		sum_R += in[x].R * filt4;
		sum_G += in[x].G * filt4;
		sum_B += in[x].B * filt4;

		//  .  .  .
    	//  .  x  .
    	//  .  .  .
		++x;
		sum_R += in[x].R * filt5;
		sum_G += in[x].G * filt5;
		sum_B += in[x].B * filt5;

		//  .  .  .
    	//  .  .  x
    	//  .  .  .
		++x;
		sum_R += in[x].R * filt6;
		sum_G += in[x].G * filt6;
		sum_B += in[x].B * filt6;
		

		//  x  .  .
    	//  .  .  .
    	//  .  .  .
		x = r*ncols - ncols + c - 1;
		sum_R += in[x].R * filt1;
		sum_G += in[x].G * filt1;
		sum_B += in[x].B * filt1;
		

		//  .  x  .
    	//  .  .  .
    	//  .  .  .
		++x;
		sum_R += in[x].R * filt2;
		sum_G += in[x].G * filt2;
		sum_B += in[x].B * filt2;
		


		//  .  .  x
    	//  .  .  .
    	//  .  .  .		
		++x;
		sum_R += in[x].R * filt3;
		sum_G += in[x].G * filt3;
		sum_B += in[x].B * filt3;

		x = r*ncols + c;
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;

    	/* UNROLL */
    	c++;
    	sum_R = 0;
    	sum_G = 0;
    	sum_B = 0;
		x = r*ncols + ncols + c - 1;
		sum_R += in[x].R * filt7;
		sum_G += in[x].G * filt7;
		sum_B += in[x].B * filt7;
		++x;
		sum_R += in[x].R * filt8;
		sum_G += in[x].G * filt8;
		sum_B += in[x].B * filt8;
		++x;
		sum_R += in[x].R * filt9;
		sum_G += in[x].G * filt9;
		sum_B += in[x].B * filt9;
		x = r*ncols + c - 1;
		sum_R += in[x].R * filt4;
		sum_G += in[x].G * filt4;
		sum_B += in[x].B * filt4;
		++x;
		sum_R += in[x].R * filt5;
		sum_G += in[x].G * filt5;
		sum_B += in[x].B * filt5;
		++x;
		sum_R += in[x].R * filt6;
		sum_G += in[x].G * filt6;
		sum_B += in[x].B * filt6;
		x = r*ncols - ncols + c - 1;
		sum_R += in[x].R * filt1;
		sum_G += in[x].G * filt1;
		sum_B += in[x].B * filt1;
		++x;
		sum_R += in[x].R * filt2;
		sum_G += in[x].G * filt2;
		sum_B += in[x].B * filt2;
		++x;
		sum_R += in[x].R * filt3;
		sum_G += in[x].G * filt3;
		sum_B += in[x].B * filt3;
		x = r*ncols + c;
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;

    	/* UNROLL */
    	c++;
    	sum_R = 0;
    	sum_G = 0;
    	sum_B = 0;
		x = r*ncols + ncols + c - 1;
		sum_R += in[x].R * filt7;
		sum_G += in[x].G * filt7;
		sum_B += in[x].B * filt7;
		++x;
		sum_R += in[x].R * filt8;
		sum_G += in[x].G * filt8;
		sum_B += in[x].B * filt8;
		++x;
		sum_R += in[x].R * filt9;
		sum_G += in[x].G * filt9;
		sum_B += in[x].B * filt9;
		x = r*ncols + c - 1;
		sum_R += in[x].R * filt4;
		sum_G += in[x].G * filt4;
		sum_B += in[x].B * filt4;
		++x;
		sum_R += in[x].R * filt5;
		sum_G += in[x].G * filt5;
		sum_B += in[x].B * filt5;
		++x;
		sum_R += in[x].R * filt6;
		sum_G += in[x].G * filt6;
		sum_B += in[x].B * filt6;
		x = r*ncols - ncols + c - 1;
		sum_R += in[x].R * filt1;
		sum_G += in[x].G * filt1;
		sum_B += in[x].B * filt1;
		++x;
		sum_R += in[x].R * filt2;
		sum_G += in[x].G * filt2;
		sum_B += in[x].B * filt2;
		++x;
		sum_R += in[x].R * filt3;
		sum_G += in[x].G * filt3;
		sum_B += in[x].B * filt3;
		x = r*ncols + c;
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;
    	/* UNROLL */
    	c++;
    	sum_R = 0;
    	sum_G = 0;
    	sum_B = 0;
		x = r*ncols + ncols + c - 1;
		sum_R += in[x].R * filt7;
		sum_G += in[x].G * filt7;
		sum_B += in[x].B * filt7;
		++x;
		sum_R += in[x].R * filt8;
		sum_G += in[x].G * filt8;
		sum_B += in[x].B * filt8;
		++x;
		sum_R += in[x].R * filt9;
		sum_G += in[x].G * filt9;
		sum_B += in[x].B * filt9;
		x = r*ncols + c - 1;
		sum_R += in[x].R * filt4;
		sum_G += in[x].G * filt4;
		sum_B += in[x].B * filt4;
		++x;
		sum_R += in[x].R * filt5;
		sum_G += in[x].G * filt5;
		sum_B += in[x].B * filt5;
		++x;
		sum_R += in[x].R * filt6;
		sum_G += in[x].G * filt6;
		sum_B += in[x].B * filt6;
		x = r*ncols - ncols + c - 1;
		sum_R += in[x].R * filt1;
		sum_G += in[x].G * filt1;
		sum_B += in[x].B * filt1;
		++x;
		sum_R += in[x].R * filt2;
		sum_G += in[x].G * filt2;
		sum_B += in[x].B * filt2;
		++x;
		sum_R += in[x].R * filt3;
		sum_G += in[x].G * filt3;
		sum_B += in[x].B * filt3;
		x = r*ncols + c;
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;
    	/* UNROLL */
    	c++;
    	sum_R = 0;
    	sum_G = 0;
    	sum_B = 0;
		x = r*ncols + ncols + c - 1;
		sum_R += in[x].R * filt7;
		sum_G += in[x].G * filt7;
		sum_B += in[x].B * filt7;
		++x;
		sum_R += in[x].R * filt8;
		sum_G += in[x].G * filt8;
		sum_B += in[x].B * filt8;
		++x;
		sum_R += in[x].R * filt9;
		sum_G += in[x].G * filt9;
		sum_B += in[x].B * filt9;
		x = r*ncols + c - 1;
		sum_R += in[x].R * filt4;
		sum_G += in[x].G * filt4;
		sum_B += in[x].B * filt4;
		++x;
		sum_R += in[x].R * filt5;
		sum_G += in[x].G * filt5;
		sum_B += in[x].B * filt5;
		++x;
		sum_R += in[x].R * filt6;
		sum_G += in[x].G * filt6;
		sum_B += in[x].B * filt6;
		x = r*ncols - ncols + c - 1;
		sum_R += in[x].R * filt1;
		sum_G += in[x].G * filt1;
		sum_B += in[x].B * filt1;
		++x;
		sum_R += in[x].R * filt2;
		sum_G += in[x].G * filt2;
		sum_B += in[x].B * filt2;
		++x;
		sum_R += in[x].R * filt3;
		sum_G += in[x].G * filt3;
		sum_B += in[x].B * filt3;
		x = r*ncols + c;
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;
    	/* UNROLL */
    	c++;
    	sum_R = 0;
    	sum_G = 0;
    	sum_B = 0;
		x = r*ncols + ncols + c - 1;
		sum_R += in[x].R * filt7;
		sum_G += in[x].G * filt7;
		sum_B += in[x].B * filt7;
		++x;
		sum_R += in[x].R * filt8;
		sum_G += in[x].G * filt8;
		sum_B += in[x].B * filt8;
		++x;
		sum_R += in[x].R * filt9;
		sum_G += in[x].G * filt9;
		sum_B += in[x].B * filt9;
		x = r*ncols + c - 1;
		sum_R += in[x].R * filt4;
		sum_G += in[x].G * filt4;
		sum_B += in[x].B * filt4;
		++x;
		sum_R += in[x].R * filt5;
		sum_G += in[x].G * filt5;
		sum_B += in[x].B * filt5;
		++x;
		sum_R += in[x].R * filt6;
		sum_G += in[x].G * filt6;
		sum_B += in[x].B * filt6;
		x = r*ncols - ncols + c - 1;
		sum_R += in[x].R * filt1;
		sum_G += in[x].G * filt1;
		sum_B += in[x].B * filt1;
		++x;
		sum_R += in[x].R * filt2;
		sum_G += in[x].G * filt2;
		sum_B += in[x].B * filt2;
		++x;
		sum_R += in[x].R * filt3;
		sum_G += in[x].G * filt3;
		sum_B += in[x].B * filt3;
		x = r*ncols + c;
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;
    	/* UNROLL */
    	c++;
    	sum_R = 0;
    	sum_G = 0;
    	sum_B = 0;
		x = r*ncols + ncols + c - 1;
		sum_R += in[x].R * filt7;
		sum_G += in[x].G * filt7;
		sum_B += in[x].B * filt7;
		++x;
		sum_R += in[x].R * filt8;
		sum_G += in[x].G * filt8;
		sum_B += in[x].B * filt8;
		++x;
		sum_R += in[x].R * filt9;
		sum_G += in[x].G * filt9;
		sum_B += in[x].B * filt9;
		x = r*ncols + c - 1;
		sum_R += in[x].R * filt4;
		sum_G += in[x].G * filt4;
		sum_B += in[x].B * filt4;
		++x;
		sum_R += in[x].R * filt5;
		sum_G += in[x].G * filt5;
		sum_B += in[x].B * filt5;
		++x;
		sum_R += in[x].R * filt6;
		sum_G += in[x].G * filt6;
		sum_B += in[x].B * filt6;
		x = r*ncols - ncols + c - 1;
		sum_R += in[x].R * filt1;
		sum_G += in[x].G * filt1;
		sum_B += in[x].B * filt1;
		++x;
		sum_R += in[x].R * filt2;
		sum_G += in[x].G * filt2;
		sum_B += in[x].B * filt2;
		++x;
		sum_R += in[x].R * filt3;
		sum_G += in[x].G * filt3;
		sum_B += in[x].B * filt3;
		x = r*ncols + c;
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;
    	/* UNROLL */
    	c++;
    	sum_R = 0;
    	sum_G = 0;
    	sum_B = 0;
		x = r*ncols + ncols + c - 1;
		sum_R += in[x].R * filt7;
		sum_G += in[x].G * filt7;
		sum_B += in[x].B * filt7;
		++x;
		sum_R += in[x].R * filt8;
		sum_G += in[x].G * filt8;
		sum_B += in[x].B * filt8;
		++x;
		sum_R += in[x].R * filt9;
		sum_G += in[x].G * filt9;
		sum_B += in[x].B * filt9;
		x = r*ncols + c - 1;
		sum_R += in[x].R * filt4;
		sum_G += in[x].G * filt4;
		sum_B += in[x].B * filt4;
		++x;
		sum_R += in[x].R * filt5;
		sum_G += in[x].G * filt5;
		sum_B += in[x].B * filt5;
		++x;
		sum_R += in[x].R * filt6;
		sum_G += in[x].G * filt6;
		sum_B += in[x].B * filt6;
		x = r*ncols - ncols + c - 1;
		sum_R += in[x].R * filt1;
		sum_G += in[x].G * filt1;
		sum_B += in[x].B * filt1;
		++x;
		sum_R += in[x].R * filt2;
		sum_G += in[x].G * filt2;
		sum_B += in[x].B * filt2;
		++x;
		sum_R += in[x].R * filt3;
		sum_G += in[x].G * filt3;
		sum_B += in[x].B * filt3;
		x = r*ncols + c;
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;
	}

	//printf("c: %d\n", c);
	for (int c = unrolled_iterations + 1; c < ncols - 1; c++) {
    	
    	uint sum_R = 0;
    	uint sum_G = 0;
    	uint sum_B = 0;

    	/* Unrolling the loop */
      	
    	//  .  .  .
    	//  .  .  .
    	//  x  .  .
		//uint x = ncols_sum + ncols - 1;
		uint x = r*ncols + ncols + c - 1;

		// Increment the accumulators
		sum_R += in[x].R * filt7;
		sum_G += in[x].G * filt7;
		sum_B += in[x].B * filt7;
		
		//  .  .  .
    	//  .  .  .
    	//  .  x  .
		++x;
		sum_R += in[x].R * filt8;
		sum_G += in[x].G * filt8;
		sum_B += in[x].B * filt8;
		

		//  .  .  .
    	//  .  .  .
    	//  .  .  x
		++x;
		sum_R += in[x].R * filt9;
		sum_G += in[x].G * filt9;
		sum_B += in[x].B * filt9;



		//  .  .  .
    	//  x  .  .
    	//  .  .  .
		x = r*ncols + c - 1;
		sum_R += in[x].R * filt4;
		sum_G += in[x].G * filt4;
		sum_B += in[x].B * filt4;

		//  .  .  .
    	//  .  x  .
    	//  .  .  .
		++x;
		sum_R += in[x].R * filt5;
		sum_G += in[x].G * filt5;
		sum_B += in[x].B * filt5;

		//  .  .  .
    	//  .  .  x
    	//  .  .  .
		++x;
		sum_R += in[x].R * filt6;
		sum_G += in[x].G * filt6;
		sum_B += in[x].B * filt6;
		

		//  x  .  .
    	//  .  .  .
    	//  .  .  .
		x = r*ncols - ncols + c - 1;
		sum_R += in[x].R * filt1;
		sum_G += in[x].G * filt1;
		sum_B += in[x].B * filt1;
		

		//  .  x  .
    	//  .  .  .
    	//  .  .  .
		++x;
		sum_R += in[x].R * filt2;
		sum_G += in[x].G * filt2;
		sum_B += in[x].B * filt2;
		


		//  .  .  x
    	//  .  .  .
    	//  .  .  .		
		++x;
		sum_R += in[x].R * filt3;
		sum_G += in[x].G * filt3;
		sum_B += in[x].B * filt3;

		x = r*ncols + c;
		
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;
	}
}
}



