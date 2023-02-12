/* CONsole VARiables
 * (c) Er2 2023 <er2@dismail.de>
 * Zlib License
 */

#include "port.h"
#include "common/dev.h"
#include "common/cvar.h"
#include "common/cmd.h"
#include "common/host.h"

cvar_t *cvars = NULL; // head

cvar_t *Cvar_List() {
	return cvars;
}

LIB_EXPORT
cvar_t *Cvar_Get(const char *name) {
	cvar_t *var;
	if (!name) return NULL;
	for (var = cvars; var; var = var->next) {
		if (!X_strcmp(name, var->name))
			return var;
	}
	return NULL;
}

LIB_EXPORT
cvar_t *Cvar_Gset(const char *name, const char *val, int flags, const char *desc) {
	cvar_t *var, *cur, *find;

	// do not crash
	if (!name || !*name)
		return NULL;

	if (Cmd_Exists(name)) {
		Warn("Can't register variable '%s', it is defined as command", name);
		return NULL;
	}

	var = Cvar_Get(name);
	if (var) return var;

	// create new variable
	var = X_malloc(sizeof(*var));
	var->name = X_copystr(name);
	var->str = X_copystr(val);
	var->default_str = X_copystr(val);
	var->desc = X_copystr(desc);
	var->flags = flags;

	Cvar_Register(var);
	return var;
}

void Cvar_Changed(cvar_t *var) {
	if (!X_strcmp(var->name, "sv_cheats"))
		g_Host.use_cheats = CVAR_TO_BOOL(var);
}

LIB_EXPORT
void Cvar_Register(cvar_t *var) {
	cvar_t *cur, *find;

	if (!var) return;
	if (Cmd_Exists(var->name)) {
		Warn("Can't register variable '%s', it is defined as command", var->name);
		return;
	}

	// link in alphabetical order
	for (cur = NULL, find = cvars; find && X_strcmp(find->name, var->name) < 0; cur = find, find = find->next);

	if (cur) cur->next = var;
	else cvars = var;
	var->next = find;

	if (var->flags & FCVAR_NOTIFY)
		Print("'%s' changed to '%s'", var->name, var->str);
	Cvar_Changed(var);
}

LIB_EXPORT
void Cvar_Set(const char *name, const char *val) {
	cvar_t *var = Cvar_Get(name);
	if (var) {
		Cvar_DirectSet(var, val);
	} else {
		DevMsg("Cvar_Set: variable '%s' not found", name);
	}
}

LIB_EXPORT
void Cvar_Reset(const char *name) {
	Cvar_Set(name, NULL);
}

void Cvar_DirectSet(cvar_t *var, const char *val) {
	if (!var) return;

	if (var != Cvar_Get(var->name)) return;

	if (var->flags & FCVAR_RO) {
		Warn("'%s' is read-only", var->name);
		return;
	}
	if (var->flags & FCVAR_CHEATS && !g_Host.use_cheats) {
		Warn("'%s' is cheat protected", var->name);
		return;
	}

	if (!val)
		val = var->default_str;

	X_freestr(var->str);
	var->str = X_copystr(val);
	Cvar_Changed(var);
}

LIB_EXPORT
float Cvar_GetNum(const char *name) {
	cvar_t *var = Cvar_Get(name);
	if (!var) return 0.0F;
	return X_atof(var->str);
}

LIB_EXPORT
char *Cvar_GetStr(const char *name) {
	cvar_t *var = Cvar_Get(name);
	if (!var) return "";
	return var->str;
}

LIB_EXPORT
xbool Cvar_Exists(const char *name) {
	return Cvar_Get(name) ? true : false;
}

