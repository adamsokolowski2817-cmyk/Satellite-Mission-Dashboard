#include "TelemetryServer.h"

#include <iostream>

#include "httplib.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <sstream>
#include <ctime>

using json = nlohmann::json;

void TelemetryServer::start(const TleData& tleData)
{
    httplib::Server server;

    server.set_pre_routing_handler(
    [](const httplib::Request&,
       httplib::Response& response)
    {
        response.set_header("Access-Control-Allow-Origin", "*");
        response.set_header("Access-Control-Allow-Methods", "GET, OPTIONS");
        response.set_header("Access-Control-Allow-Headers", "Content-Type");
        return httplib::Server::HandlerResponse::Unhandled;
    });

    server.Get("/health",
    [](const httplib::Request&,
       httplib::Response& response)
    {
        response.set_content(
            "{\"status\":\"ok\"}",
            "application/json");
    });

    server.Get("/dashboard",
    [](const httplib::Request&,
       httplib::Response& response)
    {
        std::ifstream file("web/dashboard.html");

        std::stringstream buffer;

        buffer << file.rdbuf();

        response.set_content(
            buffer.str(),
            "text/html");
    });


    server.Get("/telemetry/current",
    [&](const httplib::Request&,
        httplib::Response& response)
    {
        PositionData position =
            propagator_.calculateCurrentPosition(tleData);

        json telemetry;

        telemetry["satellite"] = tleData.name;
        telemetry["latitude"] = position.latitude;
        telemetry["longitude"] = position.longitude;
        telemetry["altitude_km"] = position.altitudeKm;
        telemetry["velocity_km_s"] = position.velocityKmS;
        telemetry["source"] = "CelesTrak";
        telemetry["timestamp"] = std::time(nullptr);

        response.set_content(
            telemetry.dump(4),
            "application/json");
    });

    server.Get("/telemetry/orbit",
        [&](const httplib::Request&,
            httplib::Response& response)
        {
            auto orbit =
                propagator_.predictOrbit(
                    tleData,
                    120,
                    2);

            json orbitJson =
                json::array();

            for (const auto& point : orbit)
            {
                json item;

                item["latitude"] =
                    point.latitude;

                item["longitude"] =
                    point.longitude;

                item["altitude_km"] =
                    point.altitudeKm;

                orbitJson.push_back(item);
            }

            response.set_content(
                orbitJson.dump(4),
                "application/json");
        });


    std::cout
        << "\nTelemetry server started:\n"
        << "http://localhost:8090/health\n"
        << "http://localhost:8090/telemetry/current\n"
        << "http://localhost:8090/telemetry/orbit\n"
        << "http://localhost:8090/dashboard\n";

    server.listen("0.0.0.0", 8090);
}