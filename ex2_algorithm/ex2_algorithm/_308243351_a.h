#ifndef _308243351_A_H
#define _308243351_A_H

#include "AbstractAlgorithm.h"
#include "AlgorithmRegistration.h"
#include "Auxiliary.h"

#define STEPS_NUM_TO_BOOKMARK 25
#define MAX_SAME_MOVE_NUM 30

class _308243351_a : public AbstractAlgorithm {
public:

	/* ---------------------------------------------------------------------------------------- */
	/* ----------------------------- Algorithm A public functions ----------------------------- */
	/* ---------------------------------------------------------------------------------------- */

	/* ------------------------------------- c'tor -------------------------------------- */
	_308243351_a();

	/* --------------------------------- Main functions --------------------------------- */
	Move					move();
	void					hitWall();
	void					hitBookmark(int seq);


private:

	/* ---------------------------------------------------------------------------------------- */
	/* ---------------------------------- Algorithm A members --------------------------------- */
	/* ---------------------------------------------------------------------------------------- */

	int						m_rowsNum = MAX_INT;
	int						m_colsNum = MAX_INT;
	vector<Coordinate>		m_bookmarkVector;
	vector<Move>			m_moveVector;
	Coordinate				m_location;
	map <Coordinate, char>	m_mazeMapping; // a map contains every revealed coordinate's char value
	Move					m_currMove;
	int						m_currMoveCounter = 0;

	/* ---------------------------------------------------------------------------------------- */
	/* ----------------------------- Algorithm A private functions ---------------------------- */
	/* ---------------------------------------------------------------------------------------- */

	void					updateLocation(const bool undo = false);
	void					updateMapping(const Coordinate loc, char c);
	void					generateMove(vector<Move> exclusions);
	bool					inVector(vector<Move> exclusions);
	vector<Move>			findExclusions();
	void					arrangeMapping(bool rows);
	char					getCharByDirection(Move a);
	Coordinate				getCoordinateByMove(Coordinate loc, const Move & a);
	inline int				numOfSteps() { return (int)m_moveVector.size(); }
};

#endif