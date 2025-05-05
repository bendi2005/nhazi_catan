#include "resource.h"
bool Resource::operator<(const Resource& other) const 
{
    return (this->Resourcetype < other.Resourcetype);
}
bool operator<(const std::set<Resource>& first,const std::set<Resource>& second)
{
    return (first.begin()->Resourcetype < second.begin()->Resourcetype);
}
Resource::Resource(enum_ResourceTypes in_rtype) : Resourcetype(in_rtype)
{}