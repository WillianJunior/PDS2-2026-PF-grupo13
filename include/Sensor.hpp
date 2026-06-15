#ifndef SENSOR_HPP
#define SENSOR_HPP

#include "Equipamento.hpp"

class Sensor : public Equipamento {
private:
    
public:
    Sensor(int id, std::string desc, double sinal);
    ~Sensor();
};

#endif