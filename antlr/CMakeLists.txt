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
# antlr4cpp_process_grammar() Macro args:
# 1. project
# 2. project namespace
# 3. grammar lexer
# 4. grammar parser
# NOTE: ideally call macro provided with antlr runtime .cmake, but it is bugged. So for now do it
#       in a different way

#antlr4cpp_process_grammar( rook_antlr rook ${CMAKE_CURRENT_SOURCE_DIR}/grammar/RookLexer.g4 ${CMAKE_CURRENT_SOURCE_DIR}/grammar/RookParser.g4 )
#include_directories(${antlr4cpp_include_dirs_rook})
## Build project
#message(STATUS "Adding following source files to executable: ${antlr4cpp_src_files_rook}")
##add_executable(rook_antlr main.cpp Visitor.cpp ${antlr4cpp_src_files_rook})
#add_executable(rook_antlr main.cpp ${antlr4cpp_src_files_rook})
#add_dependencies(rook_antlr antlr4cpp antlr4cpp_generation_rook)
#target_link_libraries(rook_antlr antlr4-runtime)

set(rook-GENERATED_SRC
  ${PROJECT_SOURCE_DIR}/rook/RookLexer.cpp
  ${PROJECT_SOURCE_DIR}/rook/RookParser.cpp
  ${PROJECT_SOURCE_DIR}/rook/RookParserBaseVisitor.cpp
  ${PROJECT_SOURCE_DIR}/rook/RookParserVisitor.cpp
)

add_executable(rook_antlr ${rook-GENERATED_SRC} main.cpp)
add_custom_command(
    OUTPUT ${rook-GENERATED_SRC}
    COMMAND "${Java_JAVA_EXECUTABLE}" -jar "${ANTLR4CPP_JAR_LOCATION}" -Werror -Dlanguage=Cpp -listener -visitor -o "${ANTLR4CPP_GENERATED_SRC_DIR}/rook" -package rook "${antlr4cpp_grammar_lexer}" "${antlr4cpp_grammar_parser}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(rook_antlr antlr4-runtime)
