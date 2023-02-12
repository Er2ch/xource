/* External renderers support
 * (c) Er2 2023 <er2@dismail.de>
 * Zlib License
 */

#include "port.h"
#include "common/dev.h"
#include "common/plat.h"
#include "common/cvar.h"
#include "common/host.h"
#include "common/system.h"

// Add new renderers here
#define DEFAULT_RENDERERS {"render_opengl", NULL}
#define DEFAULT_RENDERERS_NUM 2 // + NULL

int validRen = 0;
char *validRenderers[DEFAULT_RENDERERS_NUM];

// ConVars
cvar_t *gl_vsync;
cvar_t *gl_clear;
cvar_t *r_showtextures;

typedef void (*GetRefAPI_t)();

LIB_EXPORT
xbool R_LoadRenderer(const char *name) {
	void *lib = Sys_LibLoad(name, true);
	GetRefAPI_t func = Sys_LibFunc(lib, "GetRefAPI");
	if (!func) {
		DevMsg("R_LoadRenderer: Cannot find entry point in %s renderer", name);
		Sys_LibUnload(lib);
		return false;
	}
	func();
	return true;
}

void R_EnumerateRenderers() {
	// Enumerate valid renderers
	void *lib;
	char *renderers[DEFAULT_RENDERERS_NUM] = DEFAULT_RENDERERS;
	for (int i = 0; i < DEFAULT_RENDERERS_NUM - 1; i++) {
		lib = Sys_LibLoad(renderers[i], false);
		if (!Sys_LibFunc(lib, "GetRefAPI")) {
			DevMsg("Renderers: Cannot find entry point in %s renderer", renderers[i]);
			continue;
		}
		DevMsg("Found renderer: %s", renderers[i]);
		Sys_LibUnload(lib);
		validRenderers[validRen++] = renderers[i];
	}
}

void VID_Init() {
	if (Host_IsDedicated())
		return;

	int i;
	R_EnumerateRenderers();

	// Create ConVars
	gl_vsync = Cvar_Gset("gl_vsync", "0", FCVAR_ARCHIVE, "enable vertical syncronization");
	gl_clear = Cvar_Gset("gl_clear", "0", FCVAR_ARCHIVE, "clear GL buffer after each frame");
	r_showtextures = Cvar_Gset("r_showtextures", "0", FCVAR_CHEATS, "show all uploaded textures");

	for (i = 0; i < validRen; i++) {
		if (R_LoadRenderer(validRenderers[i])) break;
	}
	if (i == validRen)
		Err("Cannot initialize any renderer. Check your drivers!");

	Cvar_Gset("width", "0", 0, "Screen width");
	Cvar_Gset("height", "0", 0, "Screen height");
	R_VideoInit();
}

void VID_Stop() {
	R_VideoDestroy();
}

