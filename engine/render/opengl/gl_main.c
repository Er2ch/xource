/* OpenGL Renderer
 * (c) Er2 2023 <er2@dismail.de>
 * Zlib License
 */

#include "port.h"
#include "common/plat.h"
#include "common/host.h"
#include <GL/gl.h>

void R_Frame(double time) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GL_SwapBuffers();
}

LIB_EXPORT
void GetRefAPI() {
	g_Host.frame = R_Frame;
}

