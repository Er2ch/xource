/* Host global variable
 * (c) Er2 2023 <er2@dismail.de>
 * Zlib License
 */

#pragma once
#include "types.h"

typedef enum {
	host_single,
	host_dedicated,
} host_t;

typedef enum {
	host_init,
} host_st_t;

typedef void (*HostFrame_t)(double time);

typedef struct {
/*
	host_status_t	status;
	game_status_t	game;
*/
	host_t		type;
	host_st_t	status;
	void		*wind;
	void		*winctx;
	HostFrame_t	frame;

	// Command line
	int		argc;
	char		**argv;

	double		starttime;
	string		gamename;
	string		basedir;

	xbool		use_console;
	xbool		use_cheats;
	xbool		mouse_visible;
	xbool		shutdown;
} host_parm_t;

extern host_parm_t	g_Host;

#define Host_IsDedicated() (g_Host.type == host_dedicated)

