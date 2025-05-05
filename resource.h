#pragma once
#include <set>
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
bool operator<(const std::set<Resource>& ,const std::set<Resource>&);




