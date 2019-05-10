#include "_308243351_b.h"
#include <time.h>

REGISTER_ALGORITHM (_308243351_b)

_308243351_b::_308243351_b() {
	m_bookmarkVector.push_back(make_pair(0, 0)); // first bookmark in starting point
	m_location = make_pair(0, 0);
	updateMapping(m_location, SPACE_CHAR);
	m_currMove = Move::BOOKMARK;
}


void _308243351_b::updateLocation(bool undo) {
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

/*	params: Coordinate and action
	return: New coordinate according to movement */
Coordinate _308243351_b::getCoordinateByMove(Coordinate loc, const Move & a) {
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

void _308243351_b::updateMapping(Coordinate loc, char c) {
	m_mazeMapping[loc] = c;
}

Move _308243351_b::move() {
	generateMove(findExclusions());
	if (m_currMove == Move::BOOKMARK) return m_currMove; // no updates needed in player's other fields
	updateLocation();
	if (m_mazeMapping.find(m_location) == m_mazeMapping.end()) updateMapping(m_location, SPACE_CHAR);
	return m_currMove;
}

// we update here the mapping with the wall we saw, the player location and undo the path
void _308243351_b::hitWall()
{
	updateMapping(m_location, WALL_CHAR);
	updateLocation(true); // undo
}

void _308243351_b::hitBookmark(int seq)
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

void _308243351_b::generateMove(vector<Move> exclusions) {
	if (m_moveVector.size() % STEPS_NUM_TO_BOOKMARK == 0) {	// TIME FOR A BOOKMARK
		m_currMove = Move::BOOKMARK;
		m_bookmarkVector.push_back(m_location);
	}
	else {														// STEP ACTION
		srand((unsigned int)time(0));
		// generates a step action until it finds an action not in exclusions
		do {
			m_currMove = Move(rand()*rand() % NUM_OF_STEPS);
		} while (inVector(exclusions));
	}
	if (numOfSteps() != 0 && m_currMove == m_moveVector[numOfSteps() - 1]) m_currMoveCounter++; // updates the current action counter
	else if (m_currMove != Move::BOOKMARK) m_currMoveCounter = 1;
	m_moveVector.push_back(m_currMove); // push action into the action list
}

bool _308243351_b::inVector(vector<Move> exclusions) {
	for (vector<Move>::iterator it = exclusions.begin(); it != exclusions.end(); ++it) {
		if (*it == m_currMove)
			return true;
	}
	return false;
}

/*	return: vector of actions which none of them won't be chosen as the next action */
vector<Move> _308243351_b::findExclusions()
{
	vector<Move> exclusions;

	char up = getCharByDirection(Move::UP);
	char down = getCharByDirection(Move::DOWN);
	char left = getCharByDirection(Move::LEFT);
	char right = getCharByDirection(Move::RIGHT);

	vector <char> directions = { up, right, down, left };
	vector <int> visit = { 0,0,0,0 };
	int space = 0;
	int wall = 0;

	// We won't allow more than MAX_SAME_ACTION_NUM steps of the same action.
	if (m_currMoveCounter == MAX_SAME_ACTION_NUM) {
		exclusions.push_back(m_currMove);
	}

	for (int i = 0; i < NUM_OF_STEPS; ++i) {
		if (directions[i] == WALL_CHAR) {
			exclusions.push_back(static_cast<Move>(i));
			// In this location we hit a wall
			visit[i] = 2;
			wall++;
		}
		else if (directions[i] == SPACE_CHAR) {

			// we visited in this location
			visit[i] = 1;
			space++;
		}
	}

	// If we visited in all the directions
	if ((wall + space) == NUM_OF_STEPS) return exclusions;

	// If we didn't visit all the directions we will push the locations that we visit
	else {
		for (int j = 0; j < NUM_OF_STEPS; ++j) { if (visit[j] == 1) exclusions.push_back(static_cast<Move>(j)); };
	}

	return exclusions;
}


void _308243351_b::arrangeMapping(bool rows)
{
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

char _308243351_b::getCharByDirection(Move a)
{
	Coordinate key = getCoordinateByMove(m_location, a);
	if (m_mazeMapping.find(key) != m_mazeMapping.end())
		return m_mazeMapping[key];
	return '0';
}