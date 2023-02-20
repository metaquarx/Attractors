# SPDX-FileCopyrightText: 2023 metaquarx <metaquarx@protonmail.com>
# SPDX-License-Identifier: GPL-3.0-only

add_executable(Lorenz
	"main.cpp"
	"Lorenz.cpp"
)

target_compile_features(Lorenz PUBLIC cxx_std_17)
set_target_properties(Lorenz PROPERTIES CXX_EXTENSIONS OFF)

if (CMAKE_CXX_COMPILER_ID MATCHES "(GNU|CLANG)")
	target_compile_options(Lorenz PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Wold-style-cast)
endif()

include(CheckIPOSupported)
check_ipo_supported(RESULT result)
if (result AND NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
	set_target_properties(Lorenz PROPERTIES INTERPROCEDURAL_OPTIMISATION TRUE)
endif()

target_include_directories(Lorenz PRIVATE "${Stitch_SOURCE_DIR}/src/")

# Dependencies
include(FetchContent)

set(SFML_BUILD_AUDIO OFF)
set(SFML_BUILD_NETWORK OFF)
FetchContent_Declare(SFML
    GIT_REPOSITORY "https://github.com/SFML/SFML"
    GIT_TAG "2.6.x"
)
FetchContent_MakeAvailable(SFML)
target_link_libraries(Lorenz PRIVATE sfml-graphics)
