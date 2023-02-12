/* Types
 * (c) Er2 2023 <er2@dismail.de>
 * Zlib License
 */

#pragma once
#include "platform.h"

#include <sys/types.h>

// Limits
#define MAX_STRING	256
#define MAX_PRINT_MSG	8192

// Typedefs
typedef short i16;
typedef uint32_t u32;
typedef unsigned short u16;
typedef unsigned char byte;
typedef unsigned int uint;
typedef uint64_t longtime_t;
typedef int	sound_t;
typedef float	vec_t;
typedef vec_t	vec2_t[2];
typedef vec_t	vec3_t[3];
typedef byte	rgba_t[4];
typedef byte	rgb_t[3];
typedef uint	dword;
typedef char	string[MAX_STRING];

#undef true
#undef false

#ifdef __cplusplus
typedef int xbool;
#else
typedef enum { false, true } xbool;
#endif

#ifndef NULL
# define NULL ((void *)0)
#endif

