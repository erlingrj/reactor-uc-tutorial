cmake_minimum_required(VERSION 3.20.0)
project(reactor-uc-hello-world)

add_subdirectory(../reactor-uc reactor-uc)

add_executable(Shutdown shutdown.c)
target_link_libraries(Shutdown PRIVATE reactor-uc)

add_executable(Solution shutdown_solution.c)
target_link_libraries(Solution PRIVATE reactor-uc)

