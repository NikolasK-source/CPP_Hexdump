cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)

# project 
project(CPP_Posix_Threading LANGUAGES CXX VERSION 0.0.1)

# settings
set(Target "Hexdump")                   # LibName
set(STANDARD 11)                        # C++ Standard

# Do not change!
set(Source_dir "src")
set(Header_dir "header")

add_library(${Target})
add_subdirectory(${Source_dir})
add_subdirectory(${Header_dir})

set_target_properties(${Target}
    PROPERTIES
        CXX_STANDARD ${STANDARD}
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
  )

# gcc settings
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    # more debugging information
    SET(CMAKE_CXX_FLAGS_DEBUG "-g3")  

    target_compile_options(${Target} PUBLIC -pthread)

    # general warnings
    target_compile_options(${Target} PUBLIC -Wall -Wextra -Werror -pedantic -pedantic-errors)

    # more warnings (see https://gcc.gnu.org/onlinedocs/gcc-4.3.2/gcc/Warning-Options.html for more details)
    target_compile_options(${Target} PUBLIC -Wduplicated-cond)
    target_compile_options(${Target} PUBLIC -Wduplicated-branches)
    target_compile_options(${Target} PUBLIC -Wlogical-op)
    target_compile_options(${Target} PUBLIC -Wrestrict)
    target_compile_options(${Target} PUBLIC -Wnull-dereference)
    target_compile_options(${Target} PUBLIC -Wold-style-cast)
    target_compile_options(${Target} PUBLIC -Wuseless-cast -Wno-error=useless-cast)
    target_compile_options(${Target} PUBLIC -Wdouble-promotion)
    target_compile_options(${Target} PUBLIC -Wformat=2)
    target_compile_options(${Target} PUBLIC -Wshadow=local -Wno-error=shadow)
    target_compile_options(${Target} PUBLIC -Winit-self)
    target_compile_options(${Target} PUBLIC -Wsequence-point)
    target_compile_options(${Target} PUBLIC -Wswitch-default)
    target_compile_options(${Target} PUBLIC -Wswitch-enum)
    target_compile_options(${Target} PUBLIC -Wconversion)
    #target_compile_options(${Target} PUBLIC -Waggregate-return -Wno-error=aggregate-return)
    target_compile_options(${Target} PUBLIC -Wcast-align)
    target_compile_options(${Target} PUBLIC -Wfloat-equal)
    target_compile_options(${Target} PUBLIC -Wundef)
    target_compile_options(${Target} PUBLIC -Wcast-qual)
elseif(MSVC)
    message(AUTHOR_WARNING "You are not using the GNU compiler! Consider using the GNU compiler.")
    target_compile_options(${Target} PUBLIC /Wall /WX)
else()
message(AUTHOR_WARNING "You are not using the GNU compiler! No additional warnings are enabled!!! Consider using the GNU compiler.")
endif()


