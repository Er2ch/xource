/* Testing library
 * (c) Er2 2023 <er2@dismail.de,
 * Zlib License
 */

#include "port.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>

typedef void (*test_t)();
typedef struct {
	test_t fn;
	char *name;
} tests_t;

#define TEST(x) void test_ ## x ()
#define T(x) {test_ ## x, #x}
#define TESTS tests_t tests[]

extern TESTS;

#define Msg(...) fprintf(stderr, __VA_ARGS__)

#define MAIN() \
	int main(int argc, char **argv) {			\
		(void)argc, (void)argv;				\
		for (int i = 0; tests[i].fn; i++) {		\
			Msg("Executing %s\n", tests[i].name);	\
			tests[i].fn();				\
			Msg("Test %s passed\n", tests[i].name);	\
		}						\
		return 0;					\
	}

_inline void _Assert(char *testMsg, xbool exp) {
	Msg("Checking for %s		... ", testMsg);
	if (exp)
		Msg("passed\n");
	else {
		Msg("failed\n");
		exit(1);
	}
}

#define TestMsg(str) Msg("-- " str "\n")
#define Assert(exp) _Assert(#exp, exp)
#define AssertP(exp) _Assert("valid pointer " #exp, exp != NULL)
#define AssertNP(exp) _Assert("NULL pointer " #exp, exp == NULL)
#define AssertStrEq(str1, str2) _Assert(#str1 " == " #str2, !X_strcmp(str1, str2))

