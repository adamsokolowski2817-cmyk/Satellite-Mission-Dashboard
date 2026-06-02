#include "TleParser.h"

#include <string>

OrbitalParameters TleParser::parse(const TleData& tle)
{
    OrbitalParameters params;

    // Line 2 example:
    // 2 25544  51.6435  92.1234 0005312 ...

    params.noradId =
        std::stoi(tle.line2.substr(2, 5));

    params.inclination =
        std::stod(tle.line2.substr(8, 8));

    std::string eccentricity =
        tle.line2.substr(26, 7);

    params.eccentricity =
        std::stod("0." + eccentricity);

    params.meanMotion =
        std::stod(tle.line2.substr(52, 11));

    return params;
}