#include "JsonExporter.h"

#include <fstream>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

void JsonExporter::exportParameters(
    const std::string& satelliteName,
    const OrbitalParameters& params,
    const std::string& outputPath)
{
    json j;

    j["name"] = satelliteName;
    j["norad_id"] = params.noradId;
    j["inclination"] = params.inclination;
    j["eccentricity"] = params.eccentricity;
    j["mean_motion"] = params.meanMotion;

    std::ofstream file(outputPath);

    file << j.dump(4);
}