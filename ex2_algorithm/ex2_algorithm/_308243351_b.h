#ifndef _308243351_B_H
#define _308243351_B_H

#include "AbstractAlgorithm.h"
#include "AlgorithmRegistration.h"
#include "Auxiliary.h"

#define STEPS_NUM_TO_BOOKMARK 5
#define MAX_SAME_ACTION_NUM 30

class _308243351_b : public AbstractAlgorithm {
public:
	_308243351_b();
	Move move();
	void hitWall();
	void hitBookmark(int seq);

private:
	int						m_rowsNum = MAX_INT;
	int						m_colsNum = MAX_INT;
	vector<Coordinate>		m_bookmarkVector;
	vector<Move>			m_moveVector;
	Coordinate				m_location;
	map <Coordinate, char>	m_mazeMapping;
	Move					m_currMove;
	int						m_currMoveCounter = 0;

	void					updateLocation(const bool undo = false);
	void					updateMapping(const Coordinate loc, char c);
	void					generateMove(vector<Move> exclusions);
	bool					inVector(vector<Move> exclusions);
	vector<Move>			findExclusions();
	void					arrangeMapping(bool rows);
	char					getCharByDirection(Move a);
	inline int				numOfSteps() { return (int)m_moveVector.size(); }
	Coordinate				getCoordinateByMove(Coordinate loc, const Move & a);
};

#endif