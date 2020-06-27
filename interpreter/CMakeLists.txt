cmake_minimum_required(VERSION 2.4)

project(interpreter)

SET(CMAKE_CXX_FLAGS "-std=c++17")

add_executable(interpreter 
	src/tp_tokenizer_parser.h
	src/tp_tokenizer_parser.cpp
	src/sm_state_machine.h
	src/sm_state_machine.cpp
	lib/ds/ds_stack.h
	lib/ds/ds_stack.cpp
	test/test_state_machine.h
	test/test_state_machine.cpp
	test/test_factorial_code.h
	test/test_factorial_code.cpp
	interpreter.cpp)