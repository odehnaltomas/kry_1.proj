cmake_minimum_required(VERSION 3.17)
project(1_proj)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror -DDEBUG_ENABLE")

#add_compile_options(-Wall -Wextra -pedantic -fopenmp -Werror -DDEBUG_ENABLE)

find_package(Threads)
#find_package(OpenMP REQUIRED)
add_executable(kry main.cpp utils.h kasiski_test.cpp kasiski_test.h friedman_test.cpp friedman_test.h key_cracker.cpp key_cracker.h)

add_executable(kry_t main2.cpp utils.h kasiski_test.cpp kasiski_test.h friedman_test.cpp friedman_test.h key_cracker.cpp key_cracker.h)
target_link_libraries(kry_t ${CMAKE_THREAD_LIBS_INIT})