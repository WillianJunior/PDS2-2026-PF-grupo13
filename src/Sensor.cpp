#include "Sensor.hpp"

Sensor::Sensor(int id, std::string desc, double sinal) : Equipamento(id, desc, "Sensor") {
    AdicionarParametro(sinal, "leitura do sensor");
}

std::string Sensor::Tipo() const { return "Sensor"; }
