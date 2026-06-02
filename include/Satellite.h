#pragma once

#include <string>

class Satellite
{
public:
    Satellite(std::string name, int noradId);

    std::string getName() const;
    int getNoradId() const;

private:
    std::string name_;
    int noradId_;
};