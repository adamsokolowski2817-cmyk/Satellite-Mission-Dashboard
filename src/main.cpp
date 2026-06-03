#include <iostream>

#include "TleLoader.h"
#include "TleParser.h"
#include "JsonExporter.h"
#include "OrbitPropagator.h"
#include "TelemetryServer.h"
#include "TleDownloader.h"

int main(int argc, char* argv[])
{
    int noradId = 25544; // domyślnie ISS

    if (argc > 1)
    {
        noradId = std::stoi(argv[1]);
    }

    TleDownloader downloader;

    downloader.downloadTleByNoradId(
        noradId,
        "data/current.tle");

    TleLoader loader;

    TleData tle =
        loader.loadFromFile("data/current.tle");

    TleParser parser;

    OrbitalParameters params =
        parser.parse(tle);

    JsonExporter exporter;

    exporter.exportParameters(
        tle.name,
        params,
        "data/current.json");

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

    std::cout << "\nJSON exported to data/current.json\n";

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