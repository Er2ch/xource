/* String functions
 * (c) Er2 2023 <er2@dismail.de>
 * Zlib License
 */

#include "port.h"
#include "std/stdlib.h"
#include <stdlib.h>

#define L LIB_EXPORT

L
int X_atoi(char *str) {
#if 1
	return atoi(str);
#else
	int sign, val;
	char cur;

	if (!str) return 0;
	while (str && *str == ' ') str++;
	if (!str) return 0;

	sign = *str == '-' ? -1 : 1;

	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
		str += 2;
		do {
			cur = *str++;
			if (cur >= '0' && cur <= '9') val = (val<<4) + cur - '0';
			else if (cur >= 'A' && cur <= 'F') val = (val<<4) + cur - 'A' + 10;
			else if (cur >= 'a' && cur <= 'f') val = (val<<4) + cur - 'a' + 10;
			else return val * sign;
		} while (cur);
	}

	do {
		cur = *str++;
		if (cur >= '0' && cur <= '9') val = val * 10 + cur - '0';
		else return val * sign;
	} while (cur);

	return val * sign;
#endif
}

L
float X_atof(char *str) {
	return atof(str);
}

L
void X_free(void *ptr) {
	free(ptr);
}

L
void *X_malloc(size_t size) {
	void *buf = malloc(size);
	if (!buf)
		Err("Memory error");
	return buf;
}

L
void *X_realloc(void *ptr, size_t size) {
	return realloc(ptr, size);
}

