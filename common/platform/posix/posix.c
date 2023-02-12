/* POSIX platform
 * (c) Er2 2023 <er2@dismail.de>
 * Zlib License
 */

#include "port.h"
#include "common/dev.h"
#include "common/host.h"
#include "common/plat.h"

#include <dlfcn.h>

void *Plat_LibLoad(const char *name, xbool error) {
	string libpath;
	X_snprintf(libpath, MAX_STRING, STR(LIBDIR) "/" LIB_PREFIX "%s" LIB_EXT, name);
	DevMsg("Loading '%s'", libpath);
	void *lib = dlopen(libpath, RTLD_NOW | RTLD_GLOBAL);
	if (!lib) {
		if (error) {
			Err("Cannot load %s: %s", name, Plat_LibError());
		} else {
			DevMsg("Cannot load %s: %s", name, Plat_LibError());
		}
	}
	return lib;
}

void Plat_LibUnload(void *lib) {
	dlclose(lib);
}

char *Plat_LibError() {
	return dlerror();
}

void *Plat_LibFunc(void *lib, const char *name) {
	return dlsym(lib, name);
}

