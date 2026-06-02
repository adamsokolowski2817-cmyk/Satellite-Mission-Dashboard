#pragma once

#include <vector>

#include "PositionData.h"
#include "TleData.h"

class OrbitPropagator
{
public:
    PositionData calculateCurrentPosition(
        const TleData& tleData);

    std::vector<PositionData> predictOrbit(
        const TleData& tleData,
        int points,
        int stepMinutes);
};