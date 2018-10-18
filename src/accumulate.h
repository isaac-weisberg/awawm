#ifndef ACCUMULATE_H
#define ACCUMULATE_H

#include <unistd.h>
#include <stdlib.h>

int accumulate_stream(const int fd, char** stream_ptr, int* length_ptr);

int dump_stream(const int fd, char* stream_ptr, int length_ptr);

#endif