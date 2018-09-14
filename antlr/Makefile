all: clean compile tags

.PHONY:
compile:
	if [ ! -d build ]; then mkdir build; fi
	cd build && cmake .. && make -j4

.PHONY:
tags:
	ctags -R --c++-kinds=+p --fields=+iaS --extra=+q 

.PHONY:
clean:
	rm -f *.out
	rm -f *.o
	rm -f tags
	rm -rf generated
	# Delete files generated through CMake
	# Keep external to prevent from redownloading
	if [ -d build ]; then \
		find build/ -maxdepth 1 ! -name externals ! -name build -exec rm -r "{}" \;; \
	fi

####################
#################### Targets below currently not working from non-interactive 
#################### shell due to alias expansion issues 
####################

.PHONY:
build_:
	# Lexer/parser cpp files that can be included into project
	antlr4 -Dlanguage=Cpp grammar/RookParser.g4 grammar/RookLexer.g4 -listener -visitor -o generated/grammar
	# To test with grun on command line need to generate and java target
	antlr4 grammar/RookParser.g4 grammar/RookLexer.g4 -listener -visitor -o generated/grammar
	javac generated/Rook*.java

.PHONY:
run_:
	cd generated && grun Rook game -tokens -gui ../test/test_basic.in

####################
####################
####################
####################
