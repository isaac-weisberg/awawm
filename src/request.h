#ifndef REQUEST_H
#define REQUEST_H

#include <stdlib.h>

typedef struct {

} Request;

Request* request_parse(const char* tcpRequest, const int tcpRequestLength);

#endif
