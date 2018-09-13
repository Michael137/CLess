CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
SET (CMAKE_CXX_STANDARD 14)

LIST( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake )

set(ANTLR4CPP_JAR_LOCATION /usr/local/lib/antlr-4.7.1-complete.jar)
include( ExternalAntlr4Cpp )

include_directories( ${ANTLR4CPP_INCLUDE_DIRS} )
link_directories( ${ANTLR4CPP_LIBS} )
message(STATUS "Found antlr4cpp libs: ${ANTLR4CPP_LIBS} and includes: ${ANTLR4CPP_INCLUDE_DIRS} ")

# Macro args:
# 1. project
# 2. project namespace
# 3. grammar lexer
# 4. grammar parser
antlr4cpp_process_grammar( rook rook ${CMAKE_CURRENT_SOURCE_DIR}/RookLexer.g4 ${CMAKE_CURRENT_SOURCE_DIR}/RookParser.g4 )
include_directories(${antlr4cpp_include_dirs_rook})

add_executable(rook main.cpp ${antlr4cpp_src_files_rook})
add_dependencies(rook antlr4cpp antlr4cpp_generation_rook)
target_link_libraries(rook antlr4-runtime)
