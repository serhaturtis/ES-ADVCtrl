cmake_minimum_required(VERSION 3.10.2)
project(advctrli2c VERSION 1.0 DESCRIPTION "IIC Control app for ADV7x8x")

include(GNUInstallDirs)

include_directories(./include)
include_directories(/usr/include)
include_directories(/usr/local/include)
link_directories(/usr/lib)
link_directories(/usr/local/lib)

add_executable(advctrli2c main.c)
set_target_properties(advctrli2c PROPERTIES VERSION ${PROJECT_VERSION})

file(GLOB SOURCEFILES "src/*.c")

target_sources(advctrli2c PRIVATE ${SOURCEFILES})

target_link_libraries(advctrli2c i2c)

install(TARGETS advctrli2c RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})


