#ifndef PLAYER_H
#define PLAYER_H

#include "AbstractAlgorithm.h"
#include "MainAux.h"

#define STEPS_NUM_TO_BOOKMARK 25
#define MAX_SAME_ACTION_NUM 30

class Player : public AbstractAlgorithm {
public:
	Move move();
	void hitWall();
	void hitBookmark(int seq);

private:
	int						m_rowsNum = MAX_INT;
	int						m_colsNum = MAX_INT;
	Coordinate				m_bookmark;
	vector <Move>			m_actionVector;
	Coordinate				m_location;
	map <Coordinate, char>	m_mazeMapping;
	Move					m_action;
	int						m_currActionCounter = 0;

	void					updateLocation(const bool undo = false);
	void					updateMapping(const Coordinate loc, char c);
	void					generateAction(vector<Move> exclusions);
	bool					inVector(vector<Move> exclusions);
	vector<Move>			findExclusions();
	void					arrangeMapping(bool rows);
	char					getCharByDirection(Move a);
	inline int				numOfSteps() { return (int)m_actionVector.size(); }
	Coordinate				getCoordinateByAction(Coordinate loc, const Move & a);
};

#endif