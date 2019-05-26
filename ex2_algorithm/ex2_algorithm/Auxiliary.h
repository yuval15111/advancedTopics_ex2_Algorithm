#ifndef AUXILIARY_H
#define AUXILIARY_H

#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <fstream>
#include <sys/stat.h>
#include <algorithm>

#include "AbstractAlgorithm.h"

#define MAX_INT 2147483647
#define ABS(x,y) x > y ? x - y : y - x
#define SPACE_CHAR ' '
#define WALL_CHAR '#'
#define NUM_OF_STEPS 4

/* ---------------------------- typedefs/using for readability ---------------------------- */

using namespace std;
using Coordinate = pair<int, int>;
typedef AbstractAlgorithm::Move Move;


/* --------------------------------- Some helper functions -------------------------------- */
Move			operator!			(const Move& a);
char			getActionChar		(const Move& a);
void			updateCoordinate	(Coordinate & c, const int i, const int j);
inline	bool	visitedAllDirections(vector<char> dirCharValues)
				{ return find(dirCharValues.begin(), dirCharValues.end(), '0') == dirCharValues.end(); }

#endif