#include "_308243351_a.h"
#include <time.h>

REGISTER_ALGORITHM(_308243351_a)

/* ---------------------------------------------------------------------------------------- */
/* ----------------------------- Algorithm A public functions ----------------------------- */
/* ---------------------------------------------------------------------------------------- */

/* ------------------------------------- c'tor -------------------------------------- */

_308243351_a::_308243351_a() {
	m_location = make_pair(0, 0);
	updateMapping(m_location, SPACE_CHAR);
	m_currMove = Move::BOOKMARK;
}

/* --------------------------------- Main functions --------------------------------- */

/*	This function returns a Move enum of the decided algorithm's movement,
	and updates the new location and the mapping. */
Move _308243351_a::move() {
	generateMove(findExclusions());
	if (m_currMove == Move::BOOKMARK) return m_currMove; // no updates needed in player's other fields
	updateLocation();
	if (m_mazeMapping.find(m_location) == m_mazeMapping.end()) updateMapping(m_location, SPACE_CHAR);
	return m_currMove;
}

/* This function updates the mapping with the wall we saw and undoes the last movement. */
void _308243351_a::hitWall()
{
	updateMapping(m_location, WALL_CHAR);
	updateLocation(true); // undo
}

/*	This function updates the dimentions of the map (and the mazeMapping coordinates accordingly)
	using the bookmark utilities. */
void _308243351_a::hitBookmark(int seq)
{
	if (m_bookmarkVector[seq] == m_location) return;
	else {
		if (m_bookmarkVector[seq].first == m_location.first) { // Defines col dimention
			m_colsNum = ABS(m_bookmarkVector[seq].second, m_location.second);
			arrangeMapping(false);
		}
		else if (m_bookmarkVector[seq].second == m_location.second) {
			m_rowsNum = ABS(m_bookmarkVector[seq].first, m_location.first);
			arrangeMapping(true);
		}
		m_location = getCoordinateByMove(m_location, Move::BOOKMARK);
		m_bookmarkVector[seq] = getCoordinateByMove(m_bookmarkVector[seq], Move::BOOKMARK);
	}
}

/* ---------------------------------------------------------------------------------------- */
/* ----------------------------- Algorithm A private functions ---------------------------- */
/* ---------------------------------------------------------------------------------------- */

/*	This function updates m_location member according to currMove. */
void _308243351_a::updateLocation(bool undo) {
	m_currMove = undo ? !m_currMove : m_currMove;
	switch (m_currMove) {
	case Move::UP:
		m_location.first = (m_location.first + 1) % m_rowsNum;
		break;
	case Move::DOWN:
		if (m_rowsNum == MAX_INT) m_location.first--;
		else m_location.first = (m_location.first == 0 ? (m_rowsNum - 1) : (m_location.first - 1));
		break;
	case Move::LEFT:
		if (m_colsNum == MAX_INT) m_location.second--;
		else m_location.second = (m_location.second == 0 ? (m_colsNum - 1) : (m_location.second - 1));
		break;
	case Move::RIGHT:
		m_location.second = (m_location.second + 1) % m_colsNum;
		break;
	default:
		break;
	}
}

/* This cute function updates mazeMapping with the given parameters. */
void _308243351_a::updateMapping(Coordinate loc, char c) {
	m_mazeMapping[loc] = c;
}

/* This function updates currMove member with a generated move and pushes it into the moves vector. */
void _308243351_a::generateMove(vector<Move> exclusions) {
	if ((m_moveVector.size() + 1) % STEPS_NUM_TO_BOOKMARK == 0) {	// TIME FOR A BOOKMARK
		m_currMove = Move::BOOKMARK;
		m_bookmarkVector.push_back(m_location);
	}
	else {														// STEP ACTION
		srand((unsigned int)time(0));
		// generates a step action until it finds an action not in exclusions
		do {
			m_currMove = Move(rand() % NUM_OF_STEPS);
		} while (inVector(exclusions)); // as long as currMove is in the exclusions, we keep looking for another move
	}
	if (numOfSteps() != 0 && m_currMove == m_moveVector[numOfSteps() - 1]) m_currMoveCounter++; // updates the current action counter
	else if (m_currMove != Move::BOOKMARK) m_currMoveCounter = 1;
	m_moveVector.push_back(m_currMove); // push action into the action list
}

/* This function returns true iff currMove member is in the exclusions vector. */
bool _308243351_a::inVector(vector<Move> exclusions) {
	for (vector<Move>::iterator it = exclusions.begin(); it != exclusions.end(); ++it) {
		if (*it == m_currMove)
			return true;
	}
	return false;
}

/*	This function returns a vector of excluded moves, i.e none of which will be chosen as the next move. */
vector<Move> _308243351_a::findExclusions() {
	vector<Move> exclusions;
	vector <char> directionsCharValues = {  getCharByDirection(Move::UP), getCharByDirection(Move::RIGHT),
											getCharByDirection(Move::DOWN), getCharByDirection(Move::LEFT) };

	// We won't allow more than MAX_SAME_MOVE_NUM steps of the same move.
	if (m_currMoveCounter == MAX_SAME_MOVE_NUM) exclusions.push_back(m_currMove);

	// Also a move into a wall will be excluded.
	for (int i = 0; i < NUM_OF_STEPS; ++i)
		if (directionsCharValues[i] == WALL_CHAR) exclusions.push_back(static_cast<Move>(i));

	// If we visited all the directions, only movements into directions with walls will be excluded.
	if (visitedAllDirections(directionsCharValues))	return exclusions;

	// Otherwise, we'll push to exclusions only the directions that we visited.
	else for (int i = 0; i < NUM_OF_STEPS; ++i)
			if (directionsCharValues[i] == SPACE_CHAR) exclusions.push_back(static_cast<Move>(i));
	return exclusions;
}



/* This function updates mazeMapping coordinates after an update in the maze dimensions is revealed. */
void _308243351_a::arrangeMapping(bool rows) {
	map <Coordinate, char> newMapping;
	if (rows) {
		for (map<Coordinate, char>::iterator it = m_mazeMapping.begin(); it != m_mazeMapping.end(); ++it) {
			char& c = m_mazeMapping[(*it).first];
			Coordinate newLocation = (*it).first;
			if (newLocation.first < 0) newLocation.first = (m_rowsNum + newLocation.first % m_rowsNum) % m_rowsNum;
			else newLocation.first %= m_rowsNum;
			newMapping[newLocation] = c;
		}
	}
	else {
		for (map<Coordinate, char>::iterator it = m_mazeMapping.begin(); it != m_mazeMapping.end(); ++it) {
			char& c = m_mazeMapping[(*it).first];
			Coordinate newLocation = (*it).first;
			if (newLocation.second < 0) newLocation.second = (m_colsNum + newLocation.second % m_colsNum) % m_colsNum;
			else newLocation.second %= m_colsNum;
			newMapping[newLocation] = c;
		}
	}
	m_mazeMapping.clear();
	m_mazeMapping = newMapping;
}

/*	param: A move a.
	return: Coordinate <m_location + a>'s char value, or '0' if not known. */
char _308243351_a::getCharByDirection(Move a)
{
	Coordinate key = getCoordinateByMove(m_location, a);
	if (m_mazeMapping.find(key) != m_mazeMapping.end())
		return m_mazeMapping[key];
	return '0';
}

/*	params: Coordinate and action
	return: New coordinate according to movement */
Coordinate _308243351_a::getCoordinateByMove(Coordinate loc, const Move & a) {
	switch (a) {
	case Move::UP:
		loc.first = (loc.first + 1) % m_rowsNum;
		break;
	case Move::DOWN:
		if (m_rowsNum == MAX_INT) loc.first--;
		else loc.first = (loc.first == 0 ? (m_rowsNum - 1) : (loc.first - 1));
		break;
	case Move::LEFT:
		if (m_colsNum == MAX_INT) loc.second--;
		else loc.second = (loc.second == 0 ? (m_colsNum - 1) : (loc.second - 1));
		break;
	case Move::RIGHT:
		loc.second = (loc.second + 1) % m_colsNum;
		break;
	default: // bookmark
		loc.first = (loc.first >= 0 ? (loc.first % m_rowsNum) : ((m_rowsNum + (loc.first % m_rowsNum)) % m_rowsNum));
		loc.second = (loc.second >= 0 ? (loc.second % m_colsNum) : ((m_colsNum + (loc.second % m_colsNum)) % m_colsNum));
	}
	return loc;
}

