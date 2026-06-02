#include "TleLoader.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

TleData TleLoader::loadFromFile(const std::string& path)
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open TLE file");
    }

    TleData tle;

    std::getline(file, tle.name);
    std::getline(file, tle.line1);
    std::getline(file, tle.line2);

    return tle;
}