#ifndef _STRLEN_H_
#define _STRLEN_H_
int strlen(char *s) {
	int i = 0;
	while (*s++) i++;
	return i;
}
#endif /* _STRLEN_H_ */
