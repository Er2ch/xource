/* FileSystem
 * (c) Er2 2023 <er2@dismail.de>
 * Zlib License
 */

#pragma once
#include "types.h"

typedef struct {
	byte	*buf;
	size_t	len;
} file_t;

file_t *FS_Open(string name, string mode);
void FS_Close(file_t *file);

