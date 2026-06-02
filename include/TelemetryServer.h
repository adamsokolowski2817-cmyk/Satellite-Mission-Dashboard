#pragma once

#include "OrbitPropagator.h"
#include "TleData.h"

class TelemetryServer
{
public:
    void start(const TleData& tleData);

private:
    OrbitPropagator propagator_;
};