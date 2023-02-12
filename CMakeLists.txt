# CMake Build file
# (c) Er2 2023
# Zlib License

cmake_minimum_required(VERSION 3.1)
if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
	message(FATAL_ERROR "Prevented in-tree build.\n"
		"Use cmake -S. -Bbuild instead.")
endif()

project(xource)
set(VERSION alpha-0.01)
message(STATUS "Xource ${VERSION}")

# Options
option(DEDICATED "Build dedicated server" OFF)

# Preprocessor
include_directories(public)

cmake_policy(SET CMP0063 NEW)
set(CMAKE_INSTALL_BINDIR ".")
set(CMAKE_INSTALL_LIBDIR "lib")
set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_LIBDIR})
set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

# Macros
macro(_common tgt)
	target_link_libraries(${tgt} ${LIBS})
	if (INCS)
		target_include_directories(${tgt} PUBLIC ${INCS})
	endif()
endmacro()

macro(lib name)
	add_library(${name} SHARED ${SRC})
	install(TARGETS ${name} LIBRARY)
	_common(${name})
endmacro()

include(CTest)
macro(test name)
if (BUILD_TESTING)
	add_executable(test_${name} ${SRC})
	add_test(NAME ${name} COMMAND test_${name})
	set(INCS ${INCS} .)
	set(LIBS ${name} ${LIBS})
	_common(test_${name})
endif()
endmacro()

macro(exe name)
	add_executable(${name} ${SRC})
	install(TARGETS ${name} RUNTIME)
	_common(${name})
endmacro()

find_program(CLANG_TIDY NAMES clang-tidy)
if(CLANG_TIDY)
	set(CMAKE_C_CLANG_TIDY clang-tidy --use-color -header-filter=.*)
endif()

# Subdirectories
add_subdirectory(init)
add_subdirectory(common)
add_subdirectory(launcher)
add_subdirectory(filesystem)
add_subdirectory(engine)
add_subdirectory(game)

