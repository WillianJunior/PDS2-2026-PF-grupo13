#include "Atuador.hpp"

Atuador::Atuador(int id, std::string desc, double retorno)
    : Equipamento(id, desc, "Atuador") {
    this->AdicionarParametro(retorno, "Sinal de retorno do atuador", id * 100 + 1);
}

std::string Atuador::Tipo() const { return "Atuador"; }
