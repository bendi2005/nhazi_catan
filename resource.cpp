#include "resource.h"
bool Resource::operator<(const Resource& other) const 
{
    return (this->data<other.data);
}
bool operator<(const std::set<Resource>& first,const std::set<Resource>& second)
{
    
    return (first.begin()->data < second.begin()->data);
}