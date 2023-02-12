# Payload for engine
# Provides HUD, scripts etc.

# Options
option(BUILD_CLIENT "Build client" ON)
set(BUILD_GAMES hl2 CACHE STRING "Games to build")

# Subdirectories
set(_GAME ${BUILD_GAMES})
add_subdirectory(server)
if(BUILD_CLIENT)
	add_subdirectory(client)
endif()

