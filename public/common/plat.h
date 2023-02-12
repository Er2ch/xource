/* Xource platform interface
 * (c) Er2 2023 <er2@dismail.de>
 * Zlib License
 */

#pragma once
#include "types.h"

// General
void Plat_Init();
void Plat_Stop();
double Plat_DoubleTime();
void Plat_MessageBox(const char *title, const char *msg, xbool parentMain);

#if PLAT_MOBILE
void Plat_Vibrate(float life, char flags);
void *Plat_GetNativeObj(const char *name);
#endif

// Input
void Plat_PollEvents();
void Plat_EnableTextInput(xbool enable);

// Renderer
xbool R_VideoInit();
void R_VideoDestroy();
void R_Frame(double time);

void VID_Frame(double time);

// GL Functions
void GL_SwapBuffers();

/*
xbool VID_SetMode();
//rserr_t R_ChangeDisplaySettings(int width, int height, xbool fullscreen);
int R_MaxVideoModes();
*/

void *Plat_LibLoad(const char *name, xbool error);
void Plat_LibUnload(void *lib);
char *Plat_LibError();
void *Plat_LibFunc(void *lib, const char *name);

