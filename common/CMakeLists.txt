# Library with things used by most parts

# Options
option(USE_SDL		"Use SDL" ON)

set(SRC
	globals.c
	dev.c
	system.c
	cmd.c
	cvar.c

	std/stdlib.c
	std/string.c
)

# Platforms
if(UNIX)
	set(SRC ${SRC}
		platform/posix/posix.c
		platform/posix/debug.c
	)
else()
	message(FATAL_ERROR "Unknown OS")
endif()
if(USE_SDL)
	find_package(SDL2 REQUIRED)
	add_definitions(-DPLAT_SDL)
	set(INCS ${INCS} ${SDL2_INCLUDE_DIRS})
	set(LIBS ${LIBS} ${SDL2_LIBRARIES})
	set(SRC ${SRC}
		platform/sdl/sdl.c
		platform/sdl/video.c
		platform/sdl/event.c
	)
else()
	message(FATAL_ERROR "Unknown platform frontend")
endif()

lib(common)
target_compile_definitions(common PUBLIC
	LIBDIR=${CMAKE_INSTALL_LIBDIR}
)
#target_include_directories(common PUBLIC .)
add_subdirectory(test)

