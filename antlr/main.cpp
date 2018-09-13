#include "RookLexer.h"
#include "RookParser.h"
#include "Visitor.h"
#include <antlr4-runtime.h>
#include <iostream>

int main()
{
// std::string stream( "1. e4 e5\n2. Nf3 Nc6\n3. Bb5 a6\n4. Bxc6 dxc6\n5. O-O 1-0 (black resigns)\n\n" );
//	std::string stream( R"(
//1. e4 e5
//2. Nf3 Nc6
//3. Bb5 a6
//4. Bxc6 dxc6
//5. O-O 1-0 (black resigns)
//)" );
	std::ifstream stream("test/test_no_newlines.in");

	antlr4::ANTLRInputStream input(stream);

	rook::RookLexer lexer( &input );
	antlr4::CommonTokenStream tokens( &lexer );

	tokens.fill();
	for( auto token : tokens.getTokens() ) {
		std::cout << token->toString() << std::endl;
	}

	rook::RookParser parser( &tokens );
	antlr4::tree::ParseTree* tree = parser.game();

	std::cout << tree->toStringTree( &parser ) << std::endl;

	rook::RookParser::GameContext* parse_tree = parser.game();
	rook::Visitor visitor;
	visitor.visitGame( parse_tree );

	return 0;
}
