//idea: put this in coords.h since that is included in everything
#pragma once
#include <stdio.h>
#include "resource.h"
#include <vector>
#include <set>
#include <math.h>
#include "../SFML-3.0.0/include/SFML/Graphics.hpp"
constexpr int BOARD_SIDE_LENGTH = 3;
constexpr int SHAPE_NODE_COUNT = 6;
constexpr int SHAPE_EDGE_COUNT = 3;
constexpr int MAX_HOW_MANY_SIDES_DOES_AN_EDGE_BORDER = 2;
constexpr int HOW_MANY_RESOURCES_DOES_A_TILE_HAVE = 1;
constexpr int HOW_MANY_RESOURCES_DOES_A_NODE_HAVE_MAX = 3;
constexpr int TILE_COUNT = 19;
constexpr int NODE_COUNT = 54;
constexpr int EDGE_COUNT = 72;

constexpr int ACTION_COUNT = 3;

constexpr int RESOURCE_COUNT = 5;


constexpr int PRODUCE_RESOURCE_VALUE_SETTLEMENT = 1; 
constexpr int PRODUCE_RESOURCE_VALUE_CITY = 2; 
constexpr int PRODUCE_RESOURCE_VALUE_ROAD = 0; 

constexpr int VICTORY_POINT_VALUE_SETTLEMENT = 1;
constexpr int VICTORY_POINT_VALUE_CITY = 2;
constexpr int VICTORY_POINT_VALUE_ROAD = 0;

constexpr int VICTORY_POINT_NEEDED_FOR_WIN = 4;


constexpr int SETTLEMENT_PIECE_COUNT = 5;
constexpr int CITY_PIECE_COUNT = 4;
constexpr int ROAD_PIECE_COUNT = 15;

constexpr int HARBOR_RATE = 2;



constexpr unsigned int INDOW_SIZE_WIDTH = 1800.0f;
constexpr unsigned int WINDOW_SIZE_HEIGHT = 1100.0f;


constexpr float ORTO_U_LAMBDA = 0.0f;
constexpr float ORTO_U_MU = 1/2.0f;
constexpr float ORTO_V_LAMBDA = 1.73205f / 4.0f;
constexpr float ORTO_V_MU = -1/4.0f;

constexpr sf::Vector2f ORIGO{600.0f,200.0f};


constexpr float CLICK_RADIUS = 15.0f;




constexpr float TILE_SIDELENGHT = 100.0f;
//constexpr float TILE_RADIUS = 1.73205f * TILE_SIDELENGHT / 2;
constexpr float TILE_RADIUS = TILE_SIDELENGHT;

constexpr float TILE_BULLSHIT_OFFSET_X = 2.5f;
constexpr float TILE_BULLSHIT_OFFSET_Y = 2.5f;

constexpr sf::Color BACKGROUND_COLOR    (102, 204, 255, 100);

constexpr sf::Color BRICK_COLOR         (255, 80, 0, 150);
constexpr sf::Color LUMBER_COLOR        (0, 128, 0, 150);
constexpr sf::Color WOOL_COLOR          (60, 255, 110, 150);
constexpr sf::Color GRAIN_COLOR         (255, 225, 0, 150);
constexpr sf::Color ORE_COLOR           (80, 80, 80, 150);
constexpr sf::Color DESERT_COLOR        (245, 190, 140, 150);

constexpr sf::Color MULTIRESOURCE_COLOR (0, 150, 255, 100);

constexpr std::array<sf::Color, 9> PLAYER_COLORS = { sf::Color(0,0,255), sf::Color(255,0,255), sf::Color(0,255,255), sf::Color(153, 0, 153), sf::Color(255, 255, 0), sf::Color(0,0,0), sf::Color(180,255,0), sf::Color(255,140,0), sf::Color(255,50,50) };






constexpr float EDGE_THICKNESS = 5;

constexpr float RAD_TO_DEG = 180.0f / 3.14159265f;

constexpr sf::Vector2f TEXTBOX_POS{1100,750};
constexpr unsigned int TEXTSIZE =  25.0f;
constexpr sf::Vector2f NAME_CUR_PLAYER_POS{1400.0f,550.0f};

constexpr float NODE_SIZE = 20.0f;

constexpr float BASE_PLAYER_INFO_WIDTH =  1250.0f;
constexpr float BASE_PLAYER_INFO_HEIGHT =  150.0f;
constexpr float PLAYER_INFO_HEIGHT_SCALE = 50.0f;

constexpr float DIE_NUMBER_SIZE = 22.0f;
