#include <complex.h>
#include "stream.h"

struct dft_comp {
    complex double freq;
    complex double ampl;
};

struct dft_res {
    struct dft_comp* comp;
    uint32_t size;
};

typedef double (*windowFunc) (double, double) ;

enum dft_window{
    DFT_WINDOW_RECTANGLE=0,
    DFT_WINDOW_TRIANLE,
    DFT_WINDOW_HANNING,
    DFT_WINDOW_HAMMING,
    DFT_WINDOW_LAST,
};

struct dft_res dft(struct stream in, uint32_t N, enum dft_window win);

//returns stream AFTER applying window function
struct stream idft(struct dft_res dft_res);
