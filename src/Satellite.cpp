#include "Satellite.h"

Satellite::Satellite(std::string name, int noradId)
    : name_(std::move(name)), noradId_(noradId)
{
}

std::string Satellite::getName() const
{
    return name_;
}

int Satellite::getNoradId() const
{
    return noradId_;
}