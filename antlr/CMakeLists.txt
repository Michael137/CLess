CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
SET (CMAKE_CXX_STANDARD 17)
PROJECT( "rook_antlr" )
INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_BINARY_DIR})

LIST( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake )

set(ANTLR4CPP_JAR_LOCATION /usr/local/lib/antlr-4.7.1-complete.jar)
include( ExternalAntlr4Cpp )

include_directories( ${ANTLR4CPP_INCLUDE_DIRS} )
link_directories( ${ANTLR4CPP_LIBS} )
message(STATUS "Found antlr4cpp libs: ${ANTLR4CPP_LIBS} and includes: ${ANTLR4CPP_INCLUDE_DIRS} ")

# Generate parser/lexer from .g4 specs
# Macro args:
# 1. project
# 2. project namespace
# 3. grammar lexer
# 4. grammar parser
antlr4cpp_process_grammar( rook_antlr rook ${CMAKE_CURRENT_SOURCE_DIR}/grammar/RookLexer.g4 ${CMAKE_CURRENT_SOURCE_DIR}/grammar/RookParser.g4 )
include_directories(${antlr4cpp_include_dirs_rook})

# Build project
message(STATUS "Adding following source files to executable: ${antlr4cpp_src_files_rook}")
add_executable(rook_antlr main.cpp Visitor.cpp ${antlr4cpp_src_files_rook})
add_dependencies(rook_antlr antlr4cpp antlr4cpp_generation_rook)
target_link_libraries(rook_antlr antlr4-runtime)
