cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

list( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake )

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

set(antlr_proj_namespace "project_namespace" CACHE STRING "" )
set(antlr_output_exe "project_exe" CACHE STRING "" )

set(generated_src_dir
  ${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr_proj_namespace}/RookLexer.cpp
  ${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr_proj_namespace}/RookParser.cpp
  ${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr_proj_namespace}/RookParserBaseVisitor.cpp
  ${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr_proj_namespace}/RookParserVisitor.cpp
)
set(generated_include_dir ${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr_proj_namespace})

add_executable(${antlr_output_exe} ${generated_src_dir} src/main.cpp src/Visitor.cpp)
add_custom_command(
    OUTPUT ${generated_src_dir}
    COMMAND
    ${CMAKE_COMMAND} -E make_directory ${ANTLR4CPP_GENERATED_SRC_DIR}
    COMMAND "${Java_JAVA_EXECUTABLE}" -jar "${ANTLR4CPP_JAR_LOCATION}" -Werror -Dlanguage=Cpp RookLexer.g4 RookParser.g4 -no-listener -visitor -o "${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr_proj_namespace}" -package ${antlr_proj_namespace}
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)

include_directories(${generated_include_dir})
add_dependencies(${antlr_output_exe} antlr4cpp)
target_link_libraries(${antlr_output_exe} antlr4-runtime)
