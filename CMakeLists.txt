# runs with the following option:
# -DCMAKE_TOOLCHAIN_FILE "$CHEERP_PATH/share/cmake/Modules/CheerpToolchain.cmake"

cmake_minimum_required(VERSION 3.0)

project(libcrails-semantic)
include_directories(/usr/local/include . lib)
link_directories(/usr/local/lib/genericjs /usr/lib/genericjs)

set(CMAKE_CXX_FLAGS "-target cheerp-genericjs -fexceptions -D__CHEERP_CLIENT__ -D__COMET_CLIENT__")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unknown-pragmas -pedantic")

file(GLOB_RECURSE app_src
  libcrails-semantics/*.cpp
)

file(GLOB_RECURSE headers
  libcrails-semantics/*.hpp
)

add_library(crails-semantics ${app_src})

install(FILES ${headers} DESTINATION include/crails/utils)
install(TARGETS crails-semantics DESTINATION ${CMAKE_INSTALL_LIBDIR})
