#include "io_internal.h"

int64 io_timeouted() {
  tai6464 now;
  static long ptr;
  io_entry* e;
  long alen=array_length(&io_fds,sizeof(io_entry));
  taia_now(&now);
  ++ptr;
  if (ptr>=alen) ptr=0;
  e=array_get(&io_fds,sizeof(io_entry),ptr);
  if (!e) return -1;
  for (;ptr<alen; ++ptr,++e) {
    if (e->inuse && e->timeout.sec.x && taia_less(&e->timeout,&now))
      return ptr;
  }
  ptr=-1;	/* this is for really pathological cases, where more
		   connections come in all the time and so the timeout
		   handling does not trigger initially */
  return -1;
}
