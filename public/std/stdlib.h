/* String functions
 * (c) Er2 2023 <er2@dismail.de>
 * Zlib License
 */

#pragma once

int X_atoi(char *str);
float X_atof(char *str);
void X_free(void *ptr);
void *X_malloc(size_t size);
void *X_realloc(void *ptr, size_t size);

