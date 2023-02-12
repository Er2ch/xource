# Engine itself

# Options
#option(USE_SDL		"Use SDL" ON)
#option(USE_STDIN	"Use stdin for console (enabled for dedicated)" OFF)

# Options
option(RENDER_OPENGL "OpenGL Renderer" ON)
# option(RENDER_VULKAN "Vulkan Renderer" OFF)

set(SRC
	engine.c
	bsp.c
	render/render.c
)

set(LIBS common)

# Subdirectories
if(RENDER_OPENGL)
	add_subdirectory(render/opengl)
endif()

lib(engine)

