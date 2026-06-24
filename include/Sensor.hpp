#ifndef SENSOR_HPP
#define SENSOR_HPP

#include "Equipamento.hpp"

class Sensor : public Equipamento {
public:
    Sensor(int id, std::string desc, double sinal);
    ~Sensor() override = default;

    std::string Tipo() const override;
};

#endif