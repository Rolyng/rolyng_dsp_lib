#include "stream.h"
#include "stdlib.h"

void freeStream(struct stream* stream) {
    free(stream->samples);
}
