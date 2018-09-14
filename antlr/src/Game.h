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
	std::string const& Move() { return move; }
};
using Move = GameMove;

class State
{
  private:
	std::pair<Move, Move> moves;
	int round;
	bool isFinal;

  public:
	std::pair<Move, Move> const& Moves() { return moves; }
};

class Game
{
  private:
	std::vector<State> states;

  public:
	std::vector<State> const& States() { return states; }
};

} // namespace rook

#endif // MOVE_IN_H
