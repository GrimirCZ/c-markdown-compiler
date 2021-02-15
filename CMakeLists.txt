# cmake_minimum_required(VERSION <specify CMake version here>)
project(MD C)

set(CMAKE_C_STANDARD 11)

add_executable(MD main.c reader/reader_ctx.h reader/string_reader/string_reader.h reader/string_reader/string_reader.c util.h tokenizer/token.h tokenizer/tokenizer.c tokenizer/tokenizer.h tokenizer/token.c util/utf8.h util/utf8.h util/utf8.c)