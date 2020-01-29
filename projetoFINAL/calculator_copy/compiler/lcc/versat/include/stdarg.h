#ifndef _STDARG_H_
#define _STDARG_H_

typedef int *va_list;
#define va_start(ap,fmt) ((ap)=(va_list)&(fmt))
#define va_arg(ap,type) ((type)*++ap)
#define va_end(ap)

#endif /* _STDARG_H_ */
