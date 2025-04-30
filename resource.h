#pragma once
#include <set>
class Resource
{
public:
int data;
bool operator<(const Resource&) const;
};
bool operator<(const std::set<Resource>& ,const std::set<Resource>&);