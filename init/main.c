/* Xource engine init file
 * (c) Er2 2023 <er2@dismail.de>
 * Zlib License
 */

#include "port.h"
#include <stdio.h>
#include <stdlib.h>

#define LIBNAME LIB_PREFIX "launcher" LIB_EXT

#if PLAT_WIN32
# include <shellapi.h>

// Enable high performance graphics
LIB_EXPORT DWORD NvOptimusEnablement = 1;
LIB_EXPORT int AmdPowerXpressRequestHighPerformance = 1;

static const char *GetStringLastError() {
	static char buf[1024];
	FormatMessageA(
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, GetLastError(),
		MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT),
		buf, sizeof(buf),
		NULL
	);
	return buf;
}

// POSIX compatibility
# define dlerror() GetStringLastError()
# define dlopen(name, x) LoadLibrary(name)
# define dlsym(ptr, name) GetProcAddress(ptr, name)
#else
# include <libgen.h>
#endif

static void Xrc_Error(const char *str) {
#if PLAT_WIN32
	MessageBox(0, str, "Xource error", MB_OK);
#else
	fprintf(stderr, "Xource error: %s\n", str);
#endif
	exit(1);
}

// Define launcher function type
typedef int (*LauncherMain_t)(int argc, char **argv);

// Inline mostly for Win32
_inline int Xrc_Start(int argc, char **argv) {
	// Load launcher
	void *launcher = dlopen(LIBNAME, RTLD_NOW);
	if (!launcher)
		Xrc_Error(dlerror());
	LauncherMain_t startup = (LauncherMain_t)dlsym(launcher, "LauncherMain");
	if (!startup)
		Xrc_Error("Cannot locate entry point!");

	return startup(argc, argv);
}

#if PLAT_WIN32
int __stdcall WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR cmdLine, int nCmdShow) {
	// Convert to argc and argv
	int argc, ret;
	LPWSTR *lpArgv = CommandLineToArgvW(GetCommandLineW(), &argc);
	char **argv = malloc((argc + 1) * sizeof(char *));
	for (int i = 0; i < argc; i++) {
		size_t size = wcslen(lpArgv[i]) + 1;
		argv[i] = malloc(size * sizeof(wchar_t));
		wcstombs(argv[i], lpArgv[i], size);
	}
	argv[argc] = '\0';

	// Startup
	ret = Xrc_Start(argc, argv);

	for (int i = 0; i < argc; i++)
		free(argv[i]);
	free(argv);
	return ret;
}
#else
int main(int argc, char **argv) {
	chdir(dirname(argv[0]));
	return Xrc_Start(argc, argv);
}
#endif

