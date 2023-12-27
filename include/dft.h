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

typedef complex double (*windowFunc)(complex double, double);

enum dft_window {
    DFT_WINDOW_RECTANGLE = 0,
    DFT_WINDOW_TRIANGLE,
    DFT_WINDOW_HANNING,
    DFT_WINDOW_HAMMING,
    DFT_WINDOW_LAST,
};

void apply_window(struct stream* in, enum dft_window win);

//have to apply window before calling dft. if no window => rectangular window
struct dft_res dft(struct stream in, uint32_t N);

//returns stream AFTER applying window function
struct stream idft(struct dft_res dft_res);
