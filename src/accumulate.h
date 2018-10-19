#ifndef ACCUMULATE_H
#define ACCUMULATE_H

#include <unistd.h>
#include <stdlib.h>

#include "request.h"

int accumulate_request(const int fd, Request* request);

int dump_stream(const int fd, char* stream_ptr, int length_ptr);

#endif