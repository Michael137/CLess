#ifndef MOVE_IN_H
#define MOVE_IN_H

#include <string>
#include <vector>

namespace rook {

class Position
{
  private:
	char piece;
	char x;
	int y;

  public:
	char Piece() { return piece; }
	char X() { return x; }
	int Y() { return y; }
};

class GameMove
{
  private:
	std::pair<Position, Position> initialPositions;
	std::pair<Position, Position> finalPositions;
	std::string move;

  public:
	std::string ToString() { return ""; }
	std::string Move() { return move; }
};
using Move = GameMove;

class State
{
  private:
	std::pair<Move, Move> moves;
	int round;
	bool isFinal;
};

class Game
{
  private:
	std::vector<State> states;
};

} // namespace rook

#endif // MOVE_IN_H
