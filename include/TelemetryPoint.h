#pragma once

#include <string>

struct TelemetryPoint
{
    std::string timestamp;
    double latitude{};
    double longitude{};
    double altitudeKm{};
    double velocityKmS{};
};