#pragma once
#include "building.h"
class Settlement : public Building
{
private:
    static int settlement_count;
public:
    Settlement();
    int GetVictoryPoints() const override;
};