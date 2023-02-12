/* Development features
 * (c) Er2 2023
 * Zlib License
 */

#pragma once
#define PRINTF(fn) void fn(const char *fmt, ...)

PRINTF(Msg);
PRINTF(Print); // Prints newline at the end
PRINTF(DevMsg);
PRINTF(Warn);
PRINTF(Err);

