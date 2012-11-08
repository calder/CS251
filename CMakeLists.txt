cmake_minimum_required(VERSION 2.8)
project(CS251)
set(CMAKE_C_COMPILER clang)
set(CMAKE_C_FLAGS -g)

### Library ###
include_directories(Library)
file(GLOB LIB_SOURCE Library/*.c Library/*/*.c)
file(GLOB LIB_HEADER Library/*.h Library/*/*.h)
add_library(cs251 ${LIB_SOURCE} ${LIB_HEADER})

### Tests ###
file(GLOB TEST_SOURCE Tests/*.c Tests/*/*.c)
file(GLOB TEST_HEADER Tests/*.h Tests/*/*.h)
add_executable(test ${TEST_SOURCE} ${TEST_HEADER})
target_link_libraries(test cs251)

### Tokenizer ###
add_executable(tokenize Executables/Tokenizer.c)
target_link_libraries(tokenize cs251)

### Parser ###
add_executable(parse Executables/Parser.c)
target_link_libraries(parse cs251)

### Interpreter ###
add_executable(interpreter Executables/Interpreter.c)
target_link_libraries(interpreter cs251)