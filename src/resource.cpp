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
        case ResourceTypes::BRICK :
            return "Brick";
        case ResourceTypes::LUMBER :
            return "Lumber";
        case ResourceTypes::ORE :
            return "Ore";
        case ResourceTypes::GRAIN :
            return "Grain";
        case ResourceTypes::WOOL :
            return "Wool";
    }
}

