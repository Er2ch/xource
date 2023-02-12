/* Command processing
 * (c) Er2 2023 <er2@dismail.de>
 * Zlib License
 */

#include "port.h"
#include "types.h"
#include "common/dev.h"
#include "common/cvar.h"
#include "common/cmd.h"

#define MAX_CMD_BUF	32728
#define MAX_CMD_LINE	2048
#define MAX_ALIAS_NAME	32

cmd_t	*cmds; // head
string	cmd_text;
size_t	cmd_len;

void Cbuf_Clear() {
	X_memset(cmd_text, 0, MAX_STRING);
	cmd_len = 0;
}

void Cbuf_AddText(const char *text) {
	int len = X_strlen(text);
	if (len + cmd_len >= MAX_STRING) {
		Warn("Cbuf_AddText: overflow");
		return;
	}
	// Note for newbies: add pointer, means moving into free part of string
	X_memcpy(cmd_text + cmd_len, text, len);
	cmd_len += len;
}

void Cmd_ExecuteString(const char *line) {
	//if (!CVAR_TO_BOOL(cmd_scripting)) return;
	// Preprocess variables
	while (*line) {
		// check for excape
		if ((*line == '\\' || *line == '$') && (*(line + 1) == '$')) {
			line++;
		} else if (*line == '$') {
			// TODO:
		}
	}

#if 0
	Cmd_TokenizeString(line);
#endif
}

// subdivide commands and remove comments
void Cbuf_ExecuteCommands() {
	xbool quotes;
	char v, *comment;
	char line[MAX_CMD_LINE];
	for (int i = 0; i < cmd_len; i++) {
		v = cmd_text[i];
		if (comment) ; // do nothing
		// Others will be here
		else if (v == '/' && cmd_text[i + 1] == '/') comment = &v, i++;
		else if (v == '"') quotes = !quotes;
		else if (quotes) {
			if (v == '\\') i++;
		} else if (v == '\0' || v == ';' || v == '\n' || v == '\r') {
			int offset = comment ? (comment - cmd_text) : i;
			X_memcpy(line, cmd_text, offset);
			line[offset] = '\0';
			comment = 0;
			// remove from line
			if (i == cmd_len) cmd_len = 0;
			else {
				cmd_len -= ++i;
				X_memmove(cmd_text, cmd_text + i, MAX_STRING);
			}
			i = -1; // because of i++ at the end
			Cmd_ExecuteString(line);
		}
	}
}

LIB_EXPORT
xbool Cmd_AddCommand(const char *name, xcmd_t func, const char *desc) {
	cmd_t *cmd, *cur, *find;

	if (!name) return false;

	if (Cvar_Get(name)) {
		Warn("AddCommand: '%s' already defined as variable", name);
		return false;
	}

	if (Cmd_Exists(name)) {
		Warn("AddCommand: '%s' already defined", name);
		return false;
	}

	cmd = X_malloc(sizeof(cmd_t));
	X_strncpy(cmd->name, name, MAX_STRING);
	X_strncpy(cmd->desc, desc, MAX_STRING);
	cmd->func = func;
	cmd->flags = 0;

	// insert in alphabetical order
	for (cur = NULL, find = cmds; find && X_strcmp(find->name, name) < 0; cur = find, find = find->next);

	if (cur) cur->next = cmd;
	else cmds = cmd;
	cmd->next = find;
	return true;
}

LIB_EXPORT
void Cmd_RemoveCommand(const char *name) {
	cmd_t *cmd;
	if (!name) return;

	for (cmd = cmds; cmd; cmd = cmd->next) {
		if (!X_strcmp(name, cmd->name)) {
			X_free(cmd->name);
			X_free(cmd->desc);
			X_free(cmd);
			return;
		}
	}
}

LIB_EXPORT
xbool Cmd_Exists(const char *name) {
	cmd_t *cmd;
	for (cmd = cmds; cmd; cmd = cmd->next) {
		if (!X_strcmp(name, cmd->name))
			return true;
	}
	return false;
}

void Cmd_Echo_fn(int argc, char **argv) {
	for (int i = 1; i < argc; i++)
		Msg("%s", argv[i]);
	Print("");
}



LIB_EXPORT
void Cmd_Init() {
	Cbuf_Clear();
	Cmd_AddCommand("echo", Cmd_Echo_fn, "print arguments to console");
}

