#pragma once
#include <set>
#include <stdio.h>

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
};





