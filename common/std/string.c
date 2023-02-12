/* String functions
 * (c) Er2 2023 <er2@dismail.de>
 * Zlib License
 */

#include "port.h"
#include "std/string.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define L LIB_EXPORT

L
void *X_memcpy(void *out, const void *inp, size_t size) {
	return memcpy(out, inp, size);
}

L
void *X_memmove(void *out, const void *inp, size_t size) {
	return memmove(out, inp, size);
}

L
void *X_memset(void *out, int val, size_t size) {
	return memset(out, val, size);
}

L
size_t X_strlen(const char *str) {
	return strlen(str);
}

L
int X_strcmp(const char *stra, const char *strb) {
	return strcmp(stra, strb);
}

L
char *X_strncpy(char *out, const char *str, size_t size) {
	return strncpy(out, str, size);
}

L
int X_snprintf(char *out, size_t size, const char *fmt, ...) {
	assert(size > 0);
	assert(out && fmt);
	va_list vargs;
	va_start(vargs, fmt);
	int len = vsnprintf(out, size, fmt, vargs);
	va_end(vargs);
	return len;
}

L
char *X_copystr(const char *string) {
	if (!string) return NULL;

	int len = X_strlen(string) + 1;
	char *out = X_malloc(len);
	X_strncpy(out, string, len);

	return out;
}

L
void X_freestr(char *string) {
	if (string == NULL) return;
	X_free(string);
	string = NULL;
}

