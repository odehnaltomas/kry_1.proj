cmake_minimum_required(VERSION 3.17)
project(1_proj)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -pedantic -Werror -DDEBUG_ENABLE)

add_executable(1_proj main.cpp utils.h kasiski_test.cpp kasiski_test.h friedman_test.cpp friedman_test.h key_cracker.cpp key_cracker.h)