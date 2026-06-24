#include "Valvula.hpp"

Valvula::Valvula(int id, std::string desc, double vazao)
    : Equipamento(id, desc, "Valvula") {
    this->AdicionarParametro(vazao, "Vazao nominal da valvula", id * 100 + 1);
}

std::string Valvula::Tipo() const { return "Valvula"; }
