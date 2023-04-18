#ifndef LOGGER_H_
#define LOGGER_H_

#define LOGTYPE_ERROR 0
#define LOGTYPE_INFO 1

void log(const char* msg, unsigned int type);

#endif
