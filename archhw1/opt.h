int temp;

for (int c = 0; c < ncols; c++) {
	for (int r = 0; r < nrows; r++) {
    	
    	uint sum_R = 0;
    	uint sum_G = 0;
    	uint sum_B = 0;

    	for (int dc = -1; dc <= 1; dc++) {
			
			for (int dr = -1; dr <= 1; dr++) {
	  			
	  			int cc = c+dc;
	  			int rr = r+dr;
	  			
	  			if (rr >= 0 && cc >= 0 && rr < nrows && cc < ncols) {
	    			uint x = ncols*rr+cc;
	    			uint y = 3*(dc+1)+(dr+1);
	    			assert(x < ncols*nrows);
	    			assert(y < FILTER_BYTES);
	    			temp = filt[y];
	    			
	    			// Increment the accumulators
	    			sum_R += in[x].R * temp;
	    			sum_G += in[x].G * temp;
	    			sum_B += in[x].B * temp;
	  			}
			}
      	}

    uint x = ncols*r+c;
    uchar d = filt[FILTER_BYTES-1];
    out[x].R = (float) sum_R / d;
    out[x].G = (float) sum_G / d;
    out[x].B = (float) sum_B / d;

	}
}
