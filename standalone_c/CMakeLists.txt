cmake_minimum_required(VERSION 3.20.0)
project(reactor-uc-hello-world)
set(MAIN_TARGET HelloWorld)

add_subdirectory(../reactor-uc reactor-uc)

add_executable(HelloWorld hello_world.c)
target_link_libraries(${MAIN_TARGET} PRIVATE reactor-uc)

add_executable(HelloGoodbyeWorld solution_shutdown.c)
target_link_libraries(HelloGoodbyeWorld PRIVATE reactor-uc)