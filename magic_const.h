//idea: put this in coords.h since that is included in everything
#pragma once
#include <stdio.h>
#include "resource.h"
#include <vector>
#include <set>
constexpr int BOARD_SIDE_LENGTH = 3;
constexpr int SHAPE_NODE_COUNT = 6;
constexpr int MAX_HOW_MANY_SIDES_DOES_AN_EDGE_BORDER = 2;
//akkor se lesznek benne magic konstansok
constexpr int HOW_MANY_RESOURCES_DOES_A_TILE_HAVE = 1;
constexpr int HOW_MANY_RESOURCES_DOES_A_NODE_HAVE_MAX = 3;
constexpr int ACTION_COUNT = 3;
constexpr int VICTORY_POINT_VALUE_SETTLEMENT = 1;
constexpr int VICTORY_POINT_VALUE_CITY = 2;
