cmake_minimum_required(VERSION 3.20.0)
project(reactor-uc-hello-world)

add_subdirectory(../reactor-uc reactor-uc)

add_executable(Shutdown shutdown.c)
target_link_libraries(Shutdown PRIVATE reactor-uc)

