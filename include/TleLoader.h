#pragma once

#include <string>
#include "TleData.h"

class TleLoader
{
public:
    TleData loadFromFile(const std::string& path);
};