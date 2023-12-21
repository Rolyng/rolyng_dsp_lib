#include "dft.h"
#include <stdint.h>
#include <stdlib.h>

struct dft_res dft(struct stream in, uint64_t sampleFreq, uint32_t numberOfPoints){
     double baseFreq = (double) in.size * sampleFreq/numberOfPoints;
     struct dft_res res;
     res.size = numberOfPoints;
     res.comp = (struct dft_comp *) malloc(sizeof(struct dft_comp) * numberOfPoints);

     for(unsigned m = 0; m < numberOfPoints; m++){
         double xm = 0;
        for(unsigned n = 0; n < numberOfPoints; n++){
            xm +=  
        } 
     }

     return res;
}
