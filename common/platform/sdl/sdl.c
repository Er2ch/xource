/* SDL platform
 * (c) Er2 2023 <er2@dismail.de>
 * Zlib License
 */

#include "port.h"
#include "common/dev.h"
#include "common/host.h"
#include "common/plat.h"
#include <SDL.h>

double Plat_DoubleTime() {
	static longtime_t g_PerformanceFreq;
	static longtime_t g_ClockStart;
	longtime_t curTime;

	if (!g_PerformanceFreq) {
		g_PerformanceFreq = SDL_GetPerformanceFrequency();
		g_ClockStart = SDL_GetPerformanceCounter();
	}
	curTime = SDL_GetPerformanceCounter();
	return (double)(curTime - g_ClockStart) / (double)g_PerformanceFreq;
}

LIB_EXPORT
void Plat_MessageBox(const char *title, const char *msg, xbool parentMain) {
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, msg, parentMain ? g_Host.wind : NULL);
}

LIB_EXPORT
void Plat_Init() {
	SDL_version ver;
	SDL_GetVersion(&ver);
	Print("SDL version: %d.%d.%d rev: %s", ver.major, ver.minor, ver.patch, SDL_GetRevision());

	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_EVENTS | SDL_INIT_VIDEO) != 0) {
		Warn("SDL_Init failed: %s", SDL_GetError());
		g_Host.type = host_dedicated;
	}

	SDL_SetHint(SDL_HINT_ACCELEROMETER_AS_JOYSTICK, "0");
	SDL_StopTextInput();

#if PLAT_WIN32
	Wcon_CreateConsole(); // used for dedicated or to show fatal errors
#endif
}

LIB_EXPORT
void Plat_Stop() {
#if PLAT_WIN32
	Wcon_DestroyConsole();
#endif
	SDL_Quit();
}

