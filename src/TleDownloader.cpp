#include "TleDownloader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "httplib.h"

void TleDownloader::downloadTleByNoradId(
    int noradId,
    const std::string& outputPath)
{
    httplib::SSLClient client("celestrak.org");

    std::string path =
        "/NORAD/elements/gp.php?CATNR=" +
        std::to_string(noradId) +
        "&FORMAT=TLE";

    auto response = client.Get(path);

    if (!response || response->status != 200)
    {
        std::cout << "Failed to download TLE\n";
        return;
    }

    std::ofstream file(outputPath);

    std::istringstream stream(response->body);
    std::string line;

    while (std::getline(stream, line))
    {
        if (!line.empty() && line.back() == '\r')
        {
            line.pop_back();
        }

        if (line.starts_with("1 ") || line.starts_with("2 "))
        {
            line = line.substr(0, 69);
        }

        file << line << "\n";
    }

    std::cout << "TLE downloaded for NORAD ID: "
              << noradId << "\n";
}

