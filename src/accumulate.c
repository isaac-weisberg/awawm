#include "accumulate.h"

int accumulate_stream(const int fd, char** stream_ptr, int* length_ptr) {
    int offset = 0;
    size_t bufferSize = 1024;
    size_t allocated = bufferSize;
    char* total = malloc(allocated);

    while (1) {
        int bytesRead = read(fd, total + offset, bufferSize);
        offset += bytesRead;
        if (bytesRead == 0)
            break;
        total = realloc(total, offset + bufferSize);
    }

    total = realloc(total, offset + 1);
    total[offset] = '\0';

    *stream_ptr = total;
    *length_ptr = offset;
    return 0;
}

int dump_stream(const int fd, char* stream_ptr, int length_ptr) {
    return -1;
}
