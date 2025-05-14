#pragma once
#include <set>
#include <stdio.h>
#include <string>


enum ResourceTypes
{
    BRICK,
    LUMBER,
    ORE,
    GRAIN,
    WOOL
};
class Resource
{
public:
ResourceTypes Resourcetype;


Resource() = delete;

Resource(ResourceTypes);

bool operator<(const Resource&) const;

std::string EnumToString();


};





