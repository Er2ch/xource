/* FileSystem
 * (c) Er2 2023 <er2@dismail.de
 * Zlib License
 */

#include "port.h"
#include "fs.h"
#include "common/dev.h"
#include "common/host.h"
#include "common/system.h"
#include <stdio.h>

LIB_EXPORT
file_t *FS_Open(string name, string mode) {
	FILE *fptr;
	file_t *file;

	if (!name) return NULL;

	fptr = fopen(name, mode);
	if (!fptr) {
		Warn("Error opening %s!", file);
		return NULL;
	}

	file = X_malloc(sizeof(file_t *));

	// Get file length
	fseek(fptr, 0, SEEK_END);
	file->len = ftell(fptr);
	fseek(fptr, 0, SEEK_SET);

	file->buf = X_malloc(file->len + 1);
	fread(file->buf, file->len, 1, fptr);
	fclose(fptr);

	return file;
}

LIB_EXPORT
void FS_Close(file_t *file) {
	if (file != NULL) {
		X_free(file->buf);
		X_free(file);
		file = NULL;
	}
}

LIB_EXPORT
xbool FS_Init(xbool caseinsensitive, string basedir, string gamedir) {
	X_strncpy(g_Host.gamename, basedir, MAX_STRING);
	return true;
}

LIB_EXPORT
void Init() {
	xbool caseinsensitive = true;
	string gamedir;

#if !PLAT_WIN32
	if (Sys_CheckParm("-casesensitive"))
		caseinsensitive = false;
#endif

	if (!Sys_GetParm("-game", gamedir, MAX_STRING))
		X_strncpy(gamedir, g_Host.basedir, MAX_STRING);

	if (!FS_Init(caseinsensitive, g_Host.basedir, gamedir))
		Err("Unable to initialize filesystem!");
}

