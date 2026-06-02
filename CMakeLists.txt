include(FetchContent)

cmake_minimum_required(VERSION 3.20)

project(SatelliteMissionDashboard)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

include_directories(external/sgp4/libsgp4)

include_directories(external/cpp-httplib)

FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3
)

FetchContent_MakeAvailable(json)
add_subdirectory(external/sgp4)

add_executable(SatelliteMissionDashboard
        src/main.cpp
        src/Satellite.cpp
        src/TleLoader.cpp
        src/TleParser.cpp

        include/Satellite.h
        include/TelemetryPoint.h
        include/TleData.h
        include/TleLoader.h
        include/OrbitalParameters.h
        include/TleParser.h
        include/JsonExporter.h
        src/JsonExporter.cpp
        include/PositionData.h
        include/OrbitPropagator.h
        src/OrbitPropagator.cpp
        include/TelemetryServer.h
        src/TelemetryServer.cpp
        include/TleDownloader.h
        src/TleDownloader.cpp

)

target_compile_definitions(SatelliteMissionDashboard
        PRIVATE CPPHTTPLIB_OPENSSL_SUPPORT
)

target_link_libraries(SatelliteMissionDashboard
        PRIVATE
        nlohmann_json::nlohmann_json
        sgp4
)

find_package(OpenSSL REQUIRED)

target_link_libraries(
        SatelliteMissionDashboard
        PRIVATE
        OpenSSL::SSL
        OpenSSL::Crypto
)