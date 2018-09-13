#include "Visitor.h"

#include <cstdio>

antlrcpp::Any rook::Visitor::visitGame( rook::RookParser::GameContext* ctx )
{
//	visitLine( ctx->line( 0 ) );
	return nullptr;
}

antlrcpp::Any rook::Visitor::visitLine( rook::RookParser::LineContext* ctx )
{
//	std::cout << __LINE__ << ":" << __func__
//			  << ": matched : " << ctx->getText();
//
//	for( auto move : ctx->moves ) {
//		puts( "CALLED" );
//		antlrcpp::Any mv = visitMove( mv );
//	}

	return nullptr;
}

antlrcpp::Any rook::Visitor::visitMove( rook::RookParser::MoveContext* ctx )
{

	return nullptr;
}
