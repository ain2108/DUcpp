int temp;

for (int c = 0; c < ncols; c++) {
	for (int r = 0; r < nrows; r++) {
    	
    	uint sum_R = 0;
    	uint sum_G = 0;
    	uint sum_B = 0;

      	/* Unrolling the loop */
      	int dc = -1;
      	int dr = -1;

      	int cc = c+dc;
		int rr = r+dr;
		
		if (rr >= 0 && cc >= 0 && rr < nrows && cc < ncols) {
			uint x = ncols*rr+cc;
			uint y = 3*(dc+1)+(dr+1);
			
			// Increment the accumulators
			temp = filt[y];
			sum_R += in[x].R * temp;
			sum_G += in[x].G * temp;
			sum_B += in[x].B * temp;
		}

		dc = -1;
		dr = 0;
		cc = c+dc;
		rr = r+dr;
		
		if (rr >= 0 && cc >= 0 && rr < nrows && cc < ncols) {
			uint x = ncols*rr+cc;
			uint y = 3*(dc+1)+(dr+1);
			
			// Increment the accumulators
			temp = filt[y];
			sum_R += in[x].R * temp;
			sum_G += in[x].G * temp;
			sum_B += in[x].B * temp;
		}

		dc = -1;
		dr = 1;
		cc = c+dc;
		rr = r+dr;
		
		if (rr >= 0 && cc >= 0 && rr < nrows && cc < ncols) {
			uint x = ncols*rr+cc;
			uint y = 3*(dc+1)+(dr+1);
			
			// Increment the accumulators
			temp = filt[y];
			sum_R += in[x].R * temp;
			sum_G += in[x].G * temp;
			sum_B += in[x].B * temp;
		}

		dc = 0;
		dr = -1;
		cc = c+dc;
		rr = r+dr;
		
		if (rr >= 0 && cc >= 0 && rr < nrows && cc < ncols) {
			uint x = ncols*rr+cc;
			uint y = 3*(dc+1)+(dr+1);
			
			// Increment the accumulators
			temp = filt[y];
			sum_R += in[x].R * temp;
			sum_G += in[x].G * temp;
			sum_B += in[x].B * temp;
		}

		dc = 0;
		dr = 0;
		cc = c+dc;
		rr = r+dr;
		
		if (rr >= 0 && cc >= 0 && rr < nrows && cc < ncols) {
			uint x = ncols*rr+cc;
			uint y = 3*(dc+1)+(dr+1);
			
			// Increment the accumulators
			temp = filt[y];
			sum_R += in[x].R * temp;
			sum_G += in[x].G * temp;
			sum_B += in[x].B * temp;
		}

		dc = 0;
		dr = 1;
		cc = c+dc;
		rr = r+dr;
		
		if (rr >= 0 && cc >= 0 && rr < nrows && cc < ncols) {
			uint x = ncols*rr+cc;
			uint y = 3*(dc+1)+(dr+1);
			
			// Increment the accumulators
			temp = filt[y];
			sum_R += in[x].R * temp;
			sum_G += in[x].G * temp;
			sum_B += in[x].B * temp;
		}

		dc = 1;
		dr = -1;
		cc = c+dc;
		rr = r+dr;
		
		if (rr >= 0 && cc >= 0 && rr < nrows && cc < ncols) {
			uint x = ncols*rr+cc;
			uint y = 3*(dc+1)+(dr+1);
			
			// Increment the accumulators
			temp = filt[y];
			sum_R += in[x].R * temp;
			sum_G += in[x].G * temp;
			sum_B += in[x].B * temp;
		}

		dc = 1;
		dr = 0;
		cc = c+dc;
		rr = r+dr;
		
		if (rr >= 0 && cc >= 0 && rr < nrows && cc < ncols) {
			uint x = ncols*rr+cc;
			uint y = 3*(dc+1)+(dr+1);
			
			// Increment the accumulators
			temp = filt[y];
			sum_R += in[x].R * temp;
			sum_G += in[x].G * temp;
			sum_B += in[x].B * temp;
		}

		dc = 1;
		dr = 1;
		cc = c+dc;
		rr = r+dr;
		
		if (rr >= 0 && cc >= 0 && rr < nrows && cc < ncols) {
			uint x = ncols*rr+cc;
			uint y = 3*(dc+1)+(dr+1);
			
			// Increment the accumulators
			temp = filt[y];
			sum_R += in[x].R * temp;
			sum_G += in[x].G * temp;
			sum_B += in[x].B * temp;
		}


    	uint x = ncols*r+c;
    	uchar d = filt[FILTER_BYTES-1];
    	out[x].R = (float) sum_R / d;
    	out[x].G = (float) sum_G / d;
    	out[x].B = (float) sum_B / d;

	}
}
