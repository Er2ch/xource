/* SDL Event handler
 * (c) Er2 2023 <er2@dismail.de>
 * Zlib License
 */

#include "port.h"
#include "common/dev.h"
#include "common/plat.h"
#include "common/host.h"
#include <SDL.h>

LIB_EXPORT
void Plat_PollEvents() {
	SDL_Event event;
	while (!g_Host.shutdown && SDL_PollEvent(&event)) {
		switch(event.type) {
		case SDL_QUIT:
			g_Host.shutdown = true;
			break;
		}
	}
}

