#include "../include/resource.h"
bool Resource::operator<(const Resource& other) const 
{
    return (this->Resourcetype < other.Resourcetype);
}

Resource::Resource(ResourceTypes in_rtype) : Resourcetype(in_rtype)
{
    
}


std::string Resource::EnumToString()
{
    switch(Resourcetype)
    {
        case BRICK :
            return "Brick";
        case LUMBER :
            return "Lumber";
        case ORE :
            return "Ore";
        case GRAIN :
            return "Grain";
        case WOOL :
            return "Wool";
    }
}

