#pragma once

#include <string>

#include "OrbitalParameters.h"

class JsonExporter
{
public:
    void exportParameters(
        const std::string& satelliteName,
        const OrbitalParameters& params,
        const std::string& outputPath);
};