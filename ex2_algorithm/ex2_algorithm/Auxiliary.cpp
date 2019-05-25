#include "Auxiliary.h"

/* --------------------------------- Some helper functions -------------------------------- */

/* return: the opposite direction of Move a */
Move operator!(const Move& a) {
	switch (a) {
	case Move::UP:
		return Move::DOWN;
	case Move::DOWN:
		return Move::UP;
	case Move::LEFT:
		return Move::RIGHT;
	case Move::RIGHT:
		return Move::LEFT;
	default:
		return a;
	}
}

/* returns the capital letter represents the move. */
char getActionChar(const Move& a) {
	switch (a) {
	case Move::UP:
		return 'U';
	case Move::DOWN:
		return 'D';
	case Move::LEFT:
		return 'L';
	case Move::RIGHT:
		return 'R';
	default:
		return 'B';
	}
}

void updateCoordinate(Coordinate & c, const int i, const int j) {
	c.first = i;
	c.second = j;
}