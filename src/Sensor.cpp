#include "Sensor.hpp"

Sensor::Sensor(int id, std::string desc, double sinal)
    : Equipamento(id, desc, "Sensor") {
    this->AdicionarParametro(sinal, "Sinal de saida do sensor");
}

std::string Sensor::Tipo() const { return "Sensor"; }
