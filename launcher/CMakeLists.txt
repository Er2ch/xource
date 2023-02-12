# Launcher library for engine initialization
# Do not confuse with init/

set(SRC launcher.c)
set(LIBS common)

lib(launcher)
target_compile_definitions(xource PUBLIC VERSION=${VERSION})

