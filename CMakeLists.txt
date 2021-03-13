cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)

# project 
project(CPP_Posix_Threading LANGUAGES CXX VERSION 0.0.1)

# settings
set(Target "Hexdump")                   # LibName
set(STANDARD 11)                        # C++ Standard
option(COMPILER_WARNINGS "Enable compiler warnings" ON)

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


function(commonwarn)
    # see https://gcc.gnu.org/onlinedocs/gcc-4.3.2/gcc/Warning-Options.html for more details

    target_compile_options(${Target} PUBLIC -Wnull-dereference)
    target_compile_options(${Target} PUBLIC -Wold-style-cast)
    target_compile_options(${Target} PUBLIC -Wdouble-promotion)
    target_compile_options(${Target} PUBLIC -Wformat=2)
    target_compile_options(${Target} PUBLIC -Winit-self)
    target_compile_options(${Target} PUBLIC -Wsequence-point)
    target_compile_options(${Target} PUBLIC -Wswitch-default)
    target_compile_options(${Target} PUBLIC -Wswitch-enum)
    target_compile_options(${Target} PUBLIC -Wconversion)
    # target_compile_options(${Target} PUBLIC -Waggregate-return -Wno-error=aggregate-return)
    target_compile_options(${Target} PUBLIC -Wcast-align)
    target_compile_options(${Target} PUBLIC -Wfloat-equal)
    target_compile_options(${Target} PUBLIC -Wundef)
    target_compile_options(${Target} PUBLIC -Wcast-qual)
endfunction()

function(gccwarn)
    # see https://gcc.gnu.org/onlinedocs/gcc-4.3.2/gcc/Warning-Options.html for more details

    target_compile_options(${Target} PUBLIC -Wduplicated-cond)
    target_compile_options(${Target} PUBLIC -Wduplicated-branches)
    target_compile_options(${Target} PUBLIC -Wlogical-op)
    target_compile_options(${Target} PUBLIC -Wrestrict)
    target_compile_options(${Target} PUBLIC -Wuseless-cast -Wno-error=useless-cast)
    target_compile_options(${Target} PUBLIC -Wshadow=local -Wno-error=shadow)

    target_compile_options(${Target} PUBLIC -Wno-error=switch-default)
    target_compile_options(${Target} PUBLIC -Wno-error=attributes)
endfunction()

function(clangwarn)
    # enable all
    target_compile_options(${Target} PUBLIC -Weverything)

    # and remove "useless" ones
    target_compile_options(${Target} PUBLIC -Wno-c++98-compat)
    target_compile_options(${Target} PUBLIC -Wno-c++98-c++11-c++14-compat)
    target_compile_options(${Target} PUBLIC -Wno-c++98-compat-pedantic)
    target_compile_options(${Target} PUBLIC -Wno-error=covered-switch-default)
    target_compile_options(${Target} PUBLIC -Wno-shadow-field-in-constructor)
    target_compile_options(${Target} PUBLIC -Wno-padded)
    target_compile_options(${Target} PUBLIC -Wno-shadow-field)
    target_compile_options(${Target} PUBLIC -Wno-weak-vtables)
    target_compile_options(${Target} PUBLIC -Wno-exit-time-destructors)
    target_compile_options(${Target} PUBLIC -Wno-global-constructors)
    target_compile_options(${Target} PUBLIC -Wno-error=unreachable-code-return)
    target_compile_options(${Target} PUBLIC -Wno-error=unreachable-code)
    target_compile_options(${Target} PUBLIC -Wno-error=documentation)
    target_compile_options(${Target} PUBLIC -Wno-error=unused-exception-parameter)
    target_compile_options(${Target} PUBLIC -Wno-nested-anon-types)
    target_compile_options(${Target} PUBLIC -Wno-gnu-anonymous-struct)

endfunction()

if(COMPILER_WARNINGS)
    message("Compiler warnings enabled.")
else()
    message("Compiler warnings disabled.")
endif()

# gcc settings
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    # compiler specific defines
    target_compile_definitions(${Target} PUBLIC "COMPILER_GNU")

    # more debugging information
    SET(CMAKE_CXX_FLAGS_DEBUG "-g3")

    target_compile_options(${Target} PUBLIC -fopenmp)

    # enable warnings
    if(COMPILER_WARNINGS)
        target_compile_options(${Target} PUBLIC -Wall -Wextra -Werror -pedantic -pedantic-errors)

        commonwarn()
        gccwarn()
    else()
        target_compile_options(${Target} PUBLIC -w)
    endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    # compiler specific defines
    target_compile_definitions(${Target} PUBLIC "COMPILER_CLANG")

    # more debugging information
    SET(CMAKE_CXX_FLAGS_DEBUG "-g3 -O3")

    target_compile_options(${Target} PUBLIC -fopenmp)

    # enable warnings (general)
    if(COMPILER_WARNINGS)
        target_compile_options(${Target} PUBLIC -Wall -Wextra -Werror -pedantic -pedantic-errors)
        commonwarn()
        clangwarn()
    else()
        target_compile_options(${Target} PUBLIC -w)
    endif()

elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    # compiler specific defines
    target_compile_definitions(${Target} PUBLIC "COMPILER_MSVC")

    # more debugging information
    SET(CMAKE_CXX_FLAGS_DEBUG "/Zi")
    message(AUTHOR_WARNING "You are not using the GNU compiler! Consider using the GNU compiler.")
    target_compile_options(${Target} PUBLIC /Wall /WX /OpenMP)
else()
    message(AUTHOR_WARNING "You are not using the GNU compiler! No additional warnings are enabled!!! Consider using the GNU compiler.")
endif()

# threading lib (std::thread)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${Target} PRIVATE Threads::Threads)

# os dependent defines
if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    target_compile_definitions(${Target} PUBLIC "OS_LINUX")
    target_compile_definitions(${Target} PUBLIC "OS_POSIX")
elseif(CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
    target_compile_definitions(${Target} PUBLIC "OS_FREEBSD")
    target_compile_definitions(${Target} PUBLIC "OS_POSIX")
elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
    target_compile_definitions(${Target} PUBLIC "OS_WINDOWS")
    target_compile_options(${Target} PUBLIC -D_DLL -D_MT -Xclang --dependent-lib=msvcrtd)
    SET(CMAKE_CXX_FLAGS_DEBUG "-g3 -D_DEBUG")
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    target_compile_definitions(${Target} PUBLIC "OS_DARWIN")
    target_compile_definitions(${Target} PUBLIC "OS_POSIX")
endif()
