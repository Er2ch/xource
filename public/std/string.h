/* String functions
 * (c) Er2 2023 <er2@dismail.de>
 * Zlib License
 */

#pragma once
#include <stdarg.h>

void	*X_memcpy(void *out, const void *inp, size_t size);
void	*X_memmove(void *out, const void *inp, size_t size);
void	*X_memset(void *out, int val, size_t size);

size_t	X_strlen(const char *str);
int	X_strcmp(const char *stra, const char *strb);
char	*X_strncpy(char *out, const char *str, size_t size);
int	X_snprintf(char *out, size_t size, const char *fmt, ...);
char	*X_copystr(const char *string);
void	X_freestr(char *string);

