#pragma once

#include "TleData.h"
#include "OrbitalParameters.h"

class TleParser
{
public:
    OrbitalParameters parse(const TleData& tle);
};