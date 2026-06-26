#include "Valvula.hpp"

Valvula::Valvula(int id, std::string desc, double vazao)
    : Equipamento(id, desc, "Valvula")
{
    AdicionarParametro(vazao, "vazao");
}

std::string Valvula::Tipo() const { return "Valvula"; }
