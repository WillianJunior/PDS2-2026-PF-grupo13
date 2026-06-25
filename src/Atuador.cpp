#include "Atuador.hpp"

Atuador::Atuador(int id, std::string desc, double retorno)
    : Equipamento(id, desc, "Atuador") {
    this->AdicionarParametro(retorno, "Sinal de retorno do atuador");
}

std::string Atuador::Tipo() const { return "Atuador"; }
