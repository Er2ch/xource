/* CONsole VARiables
 * (c) Er2 2023 <er2@dismail.de>
 * Zlib License
 */

#pragma once
#include "types.h"

typedef struct convar_s {
	char		*name;
	char		*str;
	int		flags;
	struct convar_s	*next;
	char		*desc;
	char		*default_str;
} cvar_t;

// Flags
#define FCVAR_NONE	0
#define FCVAR_HIDDEN	(1 << 1) // do not find or autocomplete
#define FCVAR_SPONLY	(1 << 2) // singleplayer only
#define FCVAR_ARCHIVE	(1 << 3) // save to vars.rc
#define FCVAR_NOTIFY	(1 << 4) // notify players
#define FCVAR_CHEATS	(1 << 5) // only with cheats
#define FCVAR_RO	(1 << 6) // read-only

#define CVAR_DEFINE(cv, cvname, cvstr, cvflags, cvdesc) \
	cvar_t cv = {(char*)cvname, (char*)cvstr, cvflags, NULL, (char*)cvdesc, (char*)NULL}

#define CVAR(cv, cvstr, cvflags, cvdesc) CVAR_DEFINE(cv, #cv, cvstr, cvflags, cvdesc)

#define CVAR_TO_BOOL(x) (X_atof((x)->str) != 0.0f ? true : false)

cvar_t *Cvar_List(); // List variables
cvar_t *Cvar_Get(const char *name);
// Set variable if not exists, just get otherwise
cvar_t *Cvar_Gset(const char *name, const char *val, int flags, const char *desc);
void Cvar_Register(cvar_t *var);
void Cvar_Set(const char *name, const char *val);
void Cvar_Reset(const char *name);
void Cvar_DirectSet(cvar_t *var, const char *val);
float Cvar_GetNum(const char *name);
char *Cvar_GetStr(const char *name);
xbool Cvar_Exists(const char *name);

