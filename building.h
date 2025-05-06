#pragma once
class Building   
{
private:
public:
    
    //ha keves a hely o megy elsonek
    virtual ~Building() = default;
    
    //egyebkent igen
    virtual int GetVictoryPoints() const = 0;

};