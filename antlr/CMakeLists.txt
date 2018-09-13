CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
SET (CMAKE_CXX_STANDARD 14)

LIST( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake )

set(ANTLR4CPP_JAR_LOCATION /usr/local/lib/antlr-4.7.1-complete.jar)
include( ExternalAntlr4Cpp )

include_directories( ${ANTLR4CPP_INCLUDE_DIRS} )
link_directories( ${ANTLR4CPP_LIBS} )

antlr4cpp_process_grammar( demo rooktest ${CMAKE_CURRENT_SOURCE_DIR}/RookLexer.g4 ${CMAKE_CURRENT_SOURCE_DIR}/RookParser.g4 )
include_directories(${antlr4cpp_include_dirs_rooktest})

add_executable(test_rook main.cpp ${antlr4cpp_src_files_rooktest})
add_dependencies(test_rook antlr4cpp antlr4cpp_generation_rooktest)
target_link_libraries(test_rook antlr4-runtime)
