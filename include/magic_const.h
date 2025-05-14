//idea: put this in coords.h since that is included in everything
#pragma once
#include <stdio.h>
#include "resource.h"
#include <vector>
#include <set>
constexpr int BOARD_SIDE_LENGTH = 3;
constexpr int SHAPE_NODE_COUNT = 6;
constexpr int SHAPE_EDGE_COUNT = 3;
constexpr int MAX_HOW_MANY_SIDES_DOES_AN_EDGE_BORDER = 2;
constexpr int HOW_MANY_RESOURCES_DOES_A_TILE_HAVE = 1;
constexpr int HOW_MANY_RESOURCES_DOES_A_NODE_HAVE_MAX = 3;
constexpr int TILE_COUNT = 19;

constexpr char* geci = "asd";
constexpr int ACTION_COUNT = 3;

constexpr int RESOURCE_COUNT = 5;


constexpr int PRODUCE_RESOURCE_VALUE_SETTLEMENT = 1; 
constexpr int PRODUCE_RESOURCE_VALUE_CITY = 2; 
constexpr int PRODUCE_RESOURCE_VALUE_ROAD = 0; 

constexpr int VICTORY_POINT_VALUE_SETTLEMENT = 1;
constexpr int VICTORY_POINT_VALUE_CITY = 2;
constexpr int VICTORY_POINT_VALUE_ROAD = 0;



constexpr int SETTLEMENT_PIECE_COUNT = 5;
constexpr int CITY_PIECE_COUNT = 4;
constexpr int ROAD_PIECE_COUNT = 15;

