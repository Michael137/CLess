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

## Generate parser/lexer from .g4 specs
## antlr4cpp_process_grammar() Macro args:
## 1. project
## 2. project namespace
## 3. grammar lexer
## 4. grammar parser
## NOTE: ideally call macro provided with antlr runtime .cmake, but it is bugged. So for now do it
##       in a different way. Potential bugfix is to replace add_custom_target with add_custom_command
##       inside the antlr4cpp_process_grammar() macro
#antlr4cpp_process_grammar( rook_antlr rook ${CMAKE_CURRENT_SOURCE_DIR}/RookLexer.g4 ${CMAKE_CURRENT_SOURCE_DIR}/RookParser.g4 )
#include_directories(${antlr4cpp_include_dirs_rook})
## Build project
#message(STATUS "Adding following source files to executable: ${antlr4cpp_src_files_rook}")
##add_executable(rook_antlr main.cpp Visitor.cpp ${antlr4cpp_src_files_rook})
#add_executable(rook_antlr main.cpp ${antlr4cpp_src_files_rook})
#add_dependencies(rook_antlr antlr4cpp antlr4cpp_generation_rook)
#target_link_libraries(rook_antlr antlr4-runtime)

set(rook-GENERATED_SRC
  ${ANTLR4CPP_GENERATED_SRC_DIR}/rook/RookLexer.cpp
  ${ANTLR4CPP_GENERATED_SRC_DIR}/rook/RookParser.cpp
  ${ANTLR4CPP_GENERATED_SRC_DIR}/rook/RookParserBaseVisitor.cpp
  ${ANTLR4CPP_GENERATED_SRC_DIR}/rook/RookParserVisitor.cpp
)

add_executable(rook_antlr ${rook-GENERATED_SRC} main.cpp)
add_custom_command(
    OUTPUT ${rook-GENERATED_SRC}
    COMMAND
    ${CMAKE_COMMAND} -E make_directory ${ANTLR4CPP_GENERATED_SRC_DIR}
    COMMAND "${Java_JAVA_EXECUTABLE}" -jar "${ANTLR4CPP_JAR_LOCATION}" -Werror -Dlanguage=Cpp RookLexer.g4 RookParser.g4 -no-listener -visitor -o "${ANTLR4CPP_GENERATED_SRC_DIR}/rook" -package rook 
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)
set(rook-GENERATED_INCLUDES ${ANTLR4CPP_GENERATED_SRC_DIR}/rook)
include_directories(${rook-GENERATED_INCLUDES})
target_link_libraries(rook_antlr antlr4-runtime)
