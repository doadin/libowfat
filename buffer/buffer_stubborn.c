#include <errno.h>
#include "buffer.h"

int buffer_stubborn(ssize_t (*op)(),int fd,const char* buf, size_t len) {
  int w;
  while (len) {
    if ((w=op(fd,buf,len))<0) {
      if (errno == EINTR) continue;
      return -1;
    };
    buf+=w;
    len-=w;
  }
  return 0;
}
