#include "RookParser.h"
#include "RookParserBaseVisitor.h"
#include <antlr4-runtime.h>

namespace rook {

class Visitor : rook::RookParserBaseVisitor
{
  public:
	antlrcpp::Any visitGame( rook::RookParser::GameContext* ctx ) override;
	antlrcpp::Any visitLine( rook::RookParser::LineContext* ctx ) override;
	antlrcpp::Any visitMove( rook::RookParser::MoveContext* ctx ) override;
};

} // namespace
