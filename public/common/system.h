/* System
 * (c) Er2 2023 <er2@dismail.de>
 * Zlib License
 */

#pragma once
#include "types.h"

xbool Sys_DebuggerPresent();
void Sys_DebugBreak();
double Sys_DoubleTime();
void Sys_Exit(int code);
void Sys_Shutdown();
void Sys_Print(const char *msg);

// Returns argument position (from 1 to argc - 1) or 0 if not found
int Sys_CheckParm(const char *parm);

// Fills out with parm value and returns true on success
xbool Sys_GetParm(const char *parm, char *out, size_t size);

// Modules
void *Sys_LibLoad(const char *name, xbool error);
void Sys_LibUnload(void *lib);
char *Sys_LibError();
void *Sys_LibFunc(void *lib, const char *name);

void Sys_ModsLoad(char *libs[]);
void Sys_ModsUnload();

