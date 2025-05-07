#pragma once
#include "magic_const.h"
#include <map>
#include <utility>
class Building   
{
private:
public:
    
    //ha keves a hely o megy elsonek
    virtual ~Building() = default;
    
    
    virtual int GetVictoryPoints() const = 0;

    
    
    //ez egy csunyabb kor emleke
    //virtual std::map<Resource,int> GetCost() const = 0;
};