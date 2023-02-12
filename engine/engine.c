/* Engine entry point
 * (c) Er2 2023 <er2@dismail.de>
 * Zlib License
 */

#include "port.h"
#include "common/dev.h"
#include "common/cvar.h"
#include "common/cmd.h"
#include "common/system.h"

LIB_EXPORT
void Init() {
	Cmd_Init();
	Sys_DebugBreak();
	VID_Init();

	xbool st = LoadBSP("intro.bsp");
	if (!st) Warn("Failed to load BSP!");
}

LIB_EXPORT
void Stop() {
	VID_Stop();
}

