# OpenGL renderer

find_package(OpenGL REQUIRED)

set(SRC gl_main.c)
set(LIBS common ${OPENGL_LIBRARIES})
set(INCS ${OPENGL_INCLUDE_DIR})
lib(render_opengl)

