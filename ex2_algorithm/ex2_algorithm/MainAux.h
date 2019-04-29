#ifndef MAINAUX_H
#define MAINAUX_H

#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <fstream>
#include <sys/stat.h>

#include "AbstractAlgorithm.h"

#define MAX_INT 2147483647
#define ABS(x,y) x > y ? x - y : y - x
#define SPACE_CHAR ' '
#define WALL_CHAR '#'
#define NUM_OF_STEPS 4

using namespace std;
using Coordinate = pair<int, int>;
typedef AbstractAlgorithm::Move Move;

Move operator!(const Move& a);
char getActionChar(const Move& a);
void updateCoordinate(Coordinate & c, const int i, const int j);

#endif