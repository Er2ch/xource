/* Low-level target platform information
 * (c) Er2 2023 <er2@dismail.de>
 * Zlib License
 */

#pragma once

// OS detection
#if defined(_WIN32)
# define PLAT_WIN32 1
#elif defined(__WATCOMC__) && defined(__DOS__)
# define PLAT_DOS4GW 1
#else // POSIX
# define PLAT_POSIX 1
# if defined(__linux__)
#  define PLAT_LINUX 1
#  ifdef __ANDROID__
#   define PLAT_ANDROID 1
#   define PLAT_MOBILE 1
#  endif
# elif defined(__FreeBSD__)
#  define PLAT_BSD 1
#  define PLAT_FBSD 1
# elif defined(__APPLE__)
#  define PLAT_APPLE 1
#  include <TargetConditionals.h>
#  if TARGET_OS_IOS
#   define PLAT_IOS 1
#   define PLAT_MOBILE 1
#  endif
# else
#  error "Unknown OS"
# endif
#endif

// Endianness
#if defined(PLAT_WIN32) || __LITTLE_ENDIAN__
# define PLAT_LE 1 // Note: every Win32 little endian?
#elif __BIG_ENDIAN__
# define PLAT_BE 1
#else
# include <sys/param.h>
# if __BYTE_ORDER == __BIG_ENDIAN
#  define PLAT_BE 1
# elif __BYTE_ORDER == __LITTLE_ENDIAN
#  define PLAT_LE 1
# else
#  error "Unknown endianness"
# endif
#endif

// CPU
#if defined(__x86_64__) || defined(_M_X64)
# define PLAT_64 1
# define PLAT_AMD64 1
#elif defined(__i386__) || defined(_X86_) || defined(_M_IX86)
# define PLAT_X86 1
#elif defined(__aarch64__) || defined(_M_ARM64)
# define PLAT_64 1
# define PLAT_ARM 8
#elif defined(_M_ARM) // MSVC armv7
# define PLAT_ARM 7
#elif defined(__arm__)
# if __ARM_ARCH == 8 || __ARM_ARCH_8__
#  define PLAT_ARM 8
# elif __ARM_ARCH == 7 || __ARM_ARCH_7__
#  define PLAT_ARM 7
# elif __ARM_ARCH == 6 || __ARM_ARCH_6__ || __ARM_ARCH_6J__
#  define PLAT_ARM 6
# elif __ARM_ARCH == 5 || __ARM_ARCH_5__
#  define PLAT_ARM 5
# elif __ARM_ARCH == 4 || __ARM_ARCH_4__
#  define PLAT_ARM 4
# else
#  error "Unknown ARM version"
# endif
# if defined(__SOFTP__) || __ARM_PCS_VFP == 0
#  define PLAT_ARM_SOFTFP 1
# else
#  define PLAT_ARM_HARDFP 1
# endif
#else
# error "Unknown CPU"
#endif
