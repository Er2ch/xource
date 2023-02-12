/* Video initialization using SDL
 * (c) Er2 2023 <er2@dismail.de>
 * Zlib License
 */

#include "port.h"
#include "common/dev.h"
#include "common/plat.h"
#include "common/host.h"
#include "common/cvar.h"
#include "common/system.h"
#include <SDL.h>
#include <SDL_video.h>
//#include <SDL_opengl.h>

xbool VID_CreateWindow(int width, int height, xbool fullscreen) {
	int xpos, ypos;
	Uint32 winFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_MOUSE_FOCUS;
	if (fullscreen) {
		winFlags |= SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS | SDL_WINDOW_INPUT_GRABBED;
		xpos = ypos = 0;
	} else {
		winFlags |= SDL_WINDOW_RESIZABLE;
		xpos = Cvar_GetNum("_window_xpos");
		ypos = Cvar_GetNum("_window_ypos");
	}

	g_Host.wind = SDL_CreateWindow("Xource", xpos, ypos, width, height, winFlags);
	if (!g_Host.wind)
		Err("Unable to create window: %s", SDL_GetError());
	g_Host.winctx = SDL_GL_CreateContext(g_Host.wind);

	SDL_ShowWindow(g_Host.wind);
	return true;
}

void VID_DestroyWindow() {
	if (!g_Host.wind)
		return;

	SDL_GL_DeleteContext(g_Host.winctx);
	SDL_DestroyWindow(g_Host.wind);
	g_Host.wind = NULL;
}

LIB_EXPORT
void GL_SwapBuffers() {
	SDL_GL_SwapWindow(g_Host.wind);
}

LIB_EXPORT
xbool R_VideoInit() {
#if PLAT_WIN32
#else
	SDL_SetHint("SDL_VIDEO_X11_XRANDR", "1");
	SDL_SetHint("SDL_VIDEO_X11_XVIDMODE", "1");
	if (Sys_CheckParm("-egl"))
		SDL_SetHint("SDL_VIDEO_X11_FORCE_EGL", "1");
#endif
	if (SDL_GL_LoadLibrary(NULL)) {
		Err("Couldn't initialize OpenGL: %s", SDL_GetError());
		return false;
	}
	VID_CreateWindow(320, 200, false);
	return true;
}

LIB_EXPORT
void R_VideoDestroy() {
	VID_DestroyWindow();
	SDL_GL_UnloadLibrary();
}

