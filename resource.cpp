#include "resource.h"
bool Resource::operator<(const Resource& other) const 
{
    return (this->Resourcetype < other.Resourcetype);
}

Resource::Resource(ResourceTypes in_rtype) : Resourcetype(in_rtype)
{
    
}