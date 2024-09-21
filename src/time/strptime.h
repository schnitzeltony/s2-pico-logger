#ifndef STRPTIME_h
#define STRPTIME_h

#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

char *strptime(const char *buf, const char *fmt, struct tm *tm);

#ifdef __cplusplus
}
#endif

#endif //STRPTIME_h
