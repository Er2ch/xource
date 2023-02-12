/* All platforms
 * (c) Er2 2023
 * Zlib License
 */

#pragma once
#include "platform.h"

// Common macros
#define _STR(s) #s
#define STR(s) _STR(s)

#ifdef __cplusplus
# define C extern "C"
#else
# define C
#endif

// Platform support
#if PLAT_WIN32
# define PATH_SEP "\\"
# ifdef __MINGW32__
#  define _inline static inline
#  define FORCEINLINE inline __attribute__((always_inline))
# else
#  define FORCEINLINE __forceinline
# endif
# define open _open
# define read _read
# define alloca _alloca
# define HSPRITE WINAPI_HSPRITE
#  define WIN32_LEAN_AND_MEAN
#  include <winsock2.h>
#  include <windows.h>
# undef HSPRITE
# define LIB_PREFIX ""
# define LIB_EXT ".dll"
# define LIB_EXPORT C __declspec(dllexport)

#else // !WIN32
# define LIB_PREFIX "lib"
# if PLAT_APPLE
#  include <sys/syslimits.h>
#  define LIB_EXT ".dylib"
#  define OPEN_CMD "open"
# else
#  define LIB_EXT ".so"
#  define OPEN_CMD "xdg-open"
# endif
# if defined(__GNUC__) || defined(__clang__)
#  define LIB_EXPORT C __attribute__((visibility("default")))
# else
#  define LIB_EXPORT C
# endif
// Windows-specific
# define __cdecl
# define __stdcall
# define _inline static inline
# define FORCEINLINE inline __attribute__((always_inline))

# if PLAT_POSIX
#  include <dlfcn.h>
#  include <unistd.h>
#  define PATH_SEP "/"
# endif
#endif

#include "std/stdlib.h"
#include "std/string.h"

