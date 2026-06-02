#include "TleDownloader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "httplib.h"


void TleDownloader::downloadIssTle()
{
    httplib::SSLClient client(
        "celestrak.org");

    auto response =
        client.Get(
            "/NORAD/elements/gp.php?CATNR=25544&FORMAT=TLE");

    if (!response)
    {
        std::cout
            << "Failed to download TLE\n";

        return;
    }

    if (response->status != 200)
    {
        std::cout
            << "HTTP error: "
            << response->status
            << "\n";

        return;
    }

    std::ofstream file("data/iss.tle");

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

    file.close();

    std::cout
        << "ISS TLE downloaded successfully\n";
}