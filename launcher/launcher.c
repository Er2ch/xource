/* Xource client launcher
 * (c) Er2 2023 <er2@dismail.de>
 * Zlib License
 */

#include "port.h"
#include "common/dev.h"
#include "common/host.h"
#include "common/plat.h"
#include "common/system.h"

#define DEFAULT_GAMEDIR "hl2"
#define I "\n  "
#if PLAT_WIN32
# define EXE_EXT ".exe"
#else
# define EXE_EXT
#endif

const char *g_UsageString =
	"xource" EXE_EXT " [options]\n"
	"Version: " STR(VERSION) "\n"
	"Options:"
	I "-game <dir>	: start with specific game directory"
	I "-dev		: start with enabled cheats"
	I "-log		: write log to \"engine.log\""
	I "-console	: run with opened console"
	"\n";

LIB_EXPORT
int LauncherMain(int argc, char **argv) {
	double oldtime, newtime;

	g_Host.starttime = Sys_DoubleTime();
	g_Host.argc = argc;
	g_Host.argv = argv;
	g_Host.status = host_init;
	X_strncpy(g_Host.basedir, DEFAULT_GAMEDIR, MAX_STRING);

	// Argument checks
	if (Sys_CheckParm("-help") || Sys_CheckParm("-h") || Sys_CheckParm("--help")) {
		Msg(g_UsageString);
		return 0;
	}
	if (Sys_CheckParm("-console"))
		g_Host.use_console = true;
	if (Sys_CheckParm("-dev")) {
		g_Host.use_console = true;
	}

#if PLAT_DEDICATED
	g_Host.type = host_dedicated;
#else
	if (Sys_CheckParm("-dedicated"))
		g_Host.type = host_dedicated;
	else
		g_Host.type = host_single;
#endif

	if (Host_IsDedicated()) {
		g_Host.use_console = true;
	}

	// Initialization
	Plat_Init();
	char *libs[] = {
		"filesystem",
		"engine",
		"server",
		"client",
		NULL
	};
	Sys_ModsLoad(libs);

	if (!g_Host.frame)
		Err("No frame function found!");

	oldtime = Sys_DoubleTime() - 0.1;
	while (!g_Host.shutdown) {
		newtime = Sys_DoubleTime();
#if !PLAT_DEDICATED
		Plat_PollEvents();
#endif
		g_Host.frame(newtime - oldtime);
		oldtime = newtime;
	}

	Sys_Shutdown();

	return 0;
}

