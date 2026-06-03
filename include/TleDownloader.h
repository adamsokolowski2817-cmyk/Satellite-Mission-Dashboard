#pragma once

#include <string>

class TleDownloader
{
public:
    void downloadTleByNoradId(
        int noradId,
        const std::string& outputPath);
};