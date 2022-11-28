cmake_minimum_required(VERSION 3.15)
project(FinalProjExamples)

# filesystem.h require C++17
set(CMAKE_CXX_STANDARD 17)

file(COPY sample_data/ DESTINATION sample_data/)

# show compiler output and enable warnings
set(CMAKE_VERBOSE_MAKEFILE ON)
add_compile_options(-Wall -Wextra -pedantic)

include(CTest)
add_executable(rapidJSONExample rapidJSONExample.cpp key.h indexHandler.h tests.cpp DocParser.h query.h Porter2/porter2_stemmer.h Porter2/porter2_stemmer.cpp Porter2/hash.h Porter2/string_view.h userInterface.h)
add_executable(tests test.cpp test.cpp DocParser.h)
add_test(NAME SimpleTest COMMAND tests)


# this makes sure we also link rapidjson
target_include_directories(rapidJSONExample PRIVATE rapidjson/)

set(CMAKE_VERBOSE_MAKEFILE OFF)
