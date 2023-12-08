cmake_minimum_required(VERSION 3.12)

project(kml)

set(CMAKE_CXX_STANDARD 14)

set(PCRE2_INCLUDE_DIR "/usr/local/include")
set(PCRE2_LIBRARY_DIR "/usr/local/lib/")

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PCRE2_INCLUDE_DIR})
include_directories(${PCRE2_LIBRARY_DIR})
include_directories("data_structures")
include_directories("io")
include_directories("kml")

find_library(PCRE2_LIBRARY NAMES PCRE2 HINTS "{PCRE2_LIBRARY_DIR}")

add_executable(kml
        main.cpp
        kml/lexer/kml_lexer.cpp
        kml/lexer/kml_lexer.h
        io/smlkr_io.cpp
        data_structures/smlkr_linked_list.cpp
        data_structures/smlkr_node.cpp
)

target_link_libraries(kml PRIVATE ${PCRE2_LIBRARY})
