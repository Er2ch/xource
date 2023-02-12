/* Sys_ functions
 * (c) Er2 2023 <er2@dismail.de>
 * Zlib License
 */

#include "port.h"
#include "common/dev.h"
#include "common/system.h"
#include "common/host.h"
#include "common/plat.h"

#include <stdio.h>  // stdout, fputs
#include <stdlib.h> // exit()
#include <signal.h>
#include <stdarg.h>

LIB_EXPORT
void Sys_DebugBreak() {
	if (Sys_DebuggerPresent())
		raise(SIGINT);
}

LIB_EXPORT
double Sys_DoubleTime() {
	return Plat_DoubleTime();
}

LIB_EXPORT
void Sys_Exit(int code) {
	Sys_Shutdown();
	exit(code);
}

LIB_EXPORT
void Sys_Shutdown() {
	Sys_ModsUnload();
	Plat_Stop();
}

LIB_EXPORT
int Sys_CheckParm(const char *parm) {
	for (int i = 1; i < g_Host.argc; i++) {
		if (!g_Host.argv[i]) continue;
		if (!X_strcmp(parm, g_Host.argv[i]))
			return i;
	}
	return 0;
}

LIB_EXPORT
xbool Sys_GetParm(const char *parm, char *out, size_t size) {
	int argc = Sys_CheckParm(parm);
	if (!argc || !out || !g_Host.argv[argc + 1])
		return false;

	X_strncpy(out, g_Host.argv[argc + 1], size);
	return true;
}

LIB_EXPORT
void Sys_Print(const char *msg) {
	fputs(msg, stdout);
#if !PLAT_DEDICATED
	if (!Host_IsDedicated()) {
		; // TODO:
	}
#endif
}

// Exports
LIB_EXPORT
void *Sys_LibLoad(const char *name, xbool error) {
	return Plat_LibLoad(name, error);
}

LIB_EXPORT
void Sys_LibUnload(void *lib) {
	return Plat_LibUnload(lib);
}

LIB_EXPORT
char *Sys_LibError() {
	return Plat_LibError();
}

LIB_EXPORT
void *Sys_LibFunc(void *lib, const char *name) {
	return Plat_LibFunc(lib, name);
}

// Modules
typedef void (*ModInit_t)();
void **mods;
int modsi;

LIB_EXPORT
void Sys_ModsLoad(char *libs[]) {
	if (!mods)
		mods = X_malloc((modsi + 1) * sizeof(void **));
	for (int i = 0; libs[i]; i++) {
		void *lib = Plat_LibLoad(libs[i], true);
		ModInit_t func = Plat_LibFunc(lib, "Init");
		if (!func) {
			Err("Unknown entry point in %s", libs[i]);
			break; // unreachable
		}
		mods = X_realloc(mods, (modsi + 1) * sizeof(void **));
		mods[modsi++] = lib;
		func();
	}
}

LIB_EXPORT
void Sys_ModsUnload() {
	if (!mods) return;
	for (int i = 0; i < modsi; i++) {
		ModInit_t func = Plat_LibFunc(mods[i], "Stop");
		if (func) func();
		Plat_LibUnload(mods[i]);
	}
	X_free(mods);
}

