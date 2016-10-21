cmake_minimum_required(VERSION 2.6)

project(quark CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()
message("Current build type is : ${CMAKE_BUILD_TYPE}")
message("path is  : ${PROJECT_SOURCE_DIR}")
message("sysmtem name is  : ${CMAKE_SYSTEM_NAME}")

if (UNIX)
elseif(WIN32)

endif()

# compiler flags.
if (UNIX)
    set(CMAKE_CXX_FLAGS
        -ggdb
        -Wall
        -Wextra 
        -Woverloaded-virtual
        -Wno-unused-parameter
        -Wno-missing-field-initializers 
    )
elseif(WIN32)
    set(CMAKE_CXX_FLAGS 
        /Zi 
        /nologo  
        /EHsc 
        /GS 
        /Gd 
        /GR 
        /GF 
        /fp:precise 
        /Zc:wchar_t 
        /Zc:forScope 
        /errorReport:queue
        /FC
        /W3 
        /WX- 
    )
	if(${MSVC_VERSION} GREATER 1700)
	LIST(APPEND CMAKE_CXX_FLAGS
		/d2Zi+ 
		)
	endif()
endif()

string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

# for base build
include_directories(${PROJECT_SOURCE_DIR}/include)

if (UNIX)
set(CMAKE_CXX_COMPILER "g++")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 ")
endif()

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)


set(SOURCES 
    src/lockpool.cpp
)

add_library(quark ${SOURCES})

