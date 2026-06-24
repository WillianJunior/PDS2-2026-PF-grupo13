#include "Sensor.hpp"

Sensor::Sensor(int id, std::string desc, double sinal)
    : Equipamento(id, desc, "Sensor") {
    this->AdicionarParametro(sinal, "Sinal de saida do sensor", id * 100 + 1);
}

std::string Sensor::Tipo() const { return "Sensor"; }
