#include <iostream>

#include "TleLoader.h"
#include "TleParser.h"
#include "JsonExporter.h"
#include "OrbitPropagator.h"
#include "TelemetryServer.h"
#include "TleDownloader.h"

int main()
{

    TleDownloader downloader;

    downloader.downloadIssTle();

    TleLoader loader;

    TleData tle =
        loader.loadFromFile("data/iss.tle");

    TleParser parser;

    OrbitalParameters params =
        parser.parse(tle);

    JsonExporter exporter;

    exporter.exportParameters(
        tle.name,
        params,
        "data/iss.json");

    OrbitPropagator propagator;

    PositionData position =
        propagator.calculateCurrentPosition(tle);

    std::cout << "Satellite Mission Dashboard\n\n";

    std::cout << "Satellite: "
              << tle.name << "\n\n";

    std::cout << "NORAD ID: "
              << params.noradId << "\n";

    std::cout << "Inclination: "
              << params.inclination << " deg\n";

    std::cout << "Eccentricity: "
              << params.eccentricity << "\n";

    std::cout << "Mean motion: "
              << params.meanMotion << " rev/day\n";

    std::cout << "\nJSON exported to data/iss.json\n";

    std::cout << "\nCurrent position:\n";

    std::cout << "Latitude: "
              << position.latitude << " deg\n";

    std::cout << "Longitude: "
              << position.longitude << " deg\n";

    std::cout << "Altitude: "
              << position.altitudeKm << " km\n";

    TelemetryServer server;

    server.start(tle);

    return 0;
}