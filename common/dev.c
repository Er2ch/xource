/* Developer things
 * (c) Er2 2023 <er2@dismail.de>
 * Zlib License
 */

#include "port.h"
#include "common/dev.h"
#include "common/host.h"
#include "common/system.h"
#include <stdio.h>

#define PRINT()						\
	va_list vargs;					\
	char text[MAX_PRINT_MSG];			\
	va_start(vargs, fmt);				\
	vsnprintf(text, MAX_PRINT_MSG, fmt, vargs);	\
	va_end(vargs);					\


LIB_EXPORT
PRINTF(Msg) {
	PRINT();
	Sys_Print(text);
}

LIB_EXPORT
PRINTF(Print) {
	PRINT();
	Msg("%s\n", text);
}

LIB_EXPORT
PRINTF(DevMsg) {
	if (!g_Host.use_console) return;
	PRINT();
	Print(text);
}

LIB_EXPORT
PRINTF(Warn) {
	PRINT();
	Print("Warn: %s", text);
	Sys_DebugBreak();
}

LIB_EXPORT
PRINTF(Err) {
	PRINT();
	Print("Err: %s", text);
	Sys_DebugBreak();
	Sys_Exit(1);
}

