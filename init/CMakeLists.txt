# Launcher executable
set(SRC main.c)

# Platform-specific stuff
if(WIN32)
	set(SRC ${SRC} main.rc)
endif()

exe(xource)

