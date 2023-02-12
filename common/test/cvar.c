/* CVar Test
 * (c) Er2 2023 <er2@dismail.de>
 * Zlib License
 */

#include "test.h"
#include "common/cvar.h"

CVAR(test, "0", FCVAR_NONE, "Testing CVar");

TEST(cvar) {
	TestMsg("Ensure it exists but not registered");
	AssertNP(Cvar_Get("test"));

	TestMsg("Register CVar");
	Cvar_Register(&test);
	AssertP(Cvar_Get("test"));

	TestMsg("Check properties");
	AssertStrEq(test.name, "test");
	AssertNP(test.default_str);
	AssertStrEq(test.str, "0");
}

