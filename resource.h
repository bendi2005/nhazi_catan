#pragma once
#include <set>


#include <stdio.h>



enum enum_ResourceTypes
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
enum_ResourceTypes Resourcetype;


Resource() = delete;

Resource(enum_ResourceTypes);

bool operator<(const Resource&) const;
};





