#include "OrbitPropagator.h"

#include <chrono>

#include "SGP4.h"
#include "Tle.h"
#include "Eci.h"
#include "CoordGeodetic.h"
#include "DateTime.h"

using namespace libsgp4;

PositionData OrbitPropagator::calculateCurrentPosition(
    const TleData& tleData)
{
    Tle tle(
        tleData.name,
        tleData.line1,
        tleData.line2);

    SGP4 sgp4(tle);

    DateTime now = DateTime::Now();

    Eci eci = sgp4.FindPosition(now);

    CoordGeodetic geo =
        eci.ToGeodetic();

    PositionData position;

    position.latitude =
        geo.latitude * 180.0 / M_PI;

    position.longitude =
        geo.longitude * 180.0 / M_PI;

    position.altitudeKm =
        geo.altitude;

    position.velocityKmS =
        eci.Velocity().Magnitude();

    return position;
}

std::vector<PositionData>
OrbitPropagator::predictOrbit(
    const TleData& tleData,
    int points,
    int stepMinutes)
{
    Tle tle(
        tleData.name,
        tleData.line1,
        tleData.line2);

    SGP4 sgp4(tle);

    std::vector<PositionData> orbit;

    DateTime start =
        DateTime::Now();

    for (int i = 0; i < points; i++)
    {
        DateTime current =
            start + TimeSpan(
                0,
                i * stepMinutes,
                0);

        Eci eci =
            sgp4.FindPosition(current);

        CoordGeodetic geo =
            eci.ToGeodetic();

        PositionData position;

        position.latitude =
            geo.latitude * 180.0 / M_PI;

        position.longitude =
            geo.longitude * 180.0 / M_PI;

        position.altitudeKm =
            geo.altitude;

        position.velocityKmS =
            eci.Velocity().Magnitude();

        orbit.push_back(position);
    }

    return orbit;
}