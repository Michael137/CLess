#include "Visitor.h"

#include <cstdio>

antlrcpp::Any rook::Visitor::visitGame( rook::RookParser::GameContext* ctx )
{
	if( ctx ) {
		auto ctxs = ctx->line();
		std::cout << ctxs.size() << " lines matched" << std::endl;
		for( auto context : ctxs )
			visitLine( context );
	}
	return nullptr;
}

antlrcpp::Any rook::Visitor::visitLine( rook::RookParser::LineContext* ctx )
{
	if( ctx ) {
		auto moves = ctx->moves;
		std::cout << "\t" << moves.size() << " moves matched" << std::endl;
		for( auto mv : moves )
			visitMove( mv );
	}

	return nullptr;
}

antlrcpp::Any rook::Visitor::visitMove( rook::RookParser::MoveContext* ctx )
{
	std::cout << "\t\t" << "move visited" << std::endl;
	if(ctx->CELL())
		std::cout << "\t\t\t" << "matched cell: " << ctx->CELL()->getText() << std::endl;

	if(ctx->PIECE())
		std::cout << "\t\t\t" << "matched piece: " << ctx->PIECE()->getText() << std::endl;

	return nullptr;
}
