/* Commands
 * (c) Er2 2023 <er2@dismail.de,
 * Zlib License
 */

#pragma once
#include "types.h"

typedef void (*xcmd_t)(int argc, char **argv);
typedef struct cmd_s {
	struct cmd_s	*next;
	string		name;
	xcmd_t		func;
	int		flags;
	string		desc;
} cmd_t;

void Cmd_Init(); // INTERNAL only
xbool Cmd_AddCommand(const char *name, xcmd_t func, const char *desc);
void Cmd_RemoveCommand(const char *name);
xbool Cmd_Exists(const char *name);

