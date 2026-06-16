#include "Sensor.hpp"

Sensor::Sensor(int id, std::string desc, double sinal) : Equipamento(int id, std::string desc){
    Parametro sig(sinal, "Sinal de saida do sensor", id+1);

    this->_Parametros.push_back(sig);
}