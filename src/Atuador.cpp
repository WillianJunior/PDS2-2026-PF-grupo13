#include "Atuador.hpp"

Atuador::Atuador(int id, std::string desc, double retorno)
    : Equipamento(id, desc, "Atuador") {
    AdicionarParametro(retorno, "Sinal de retorno");
}

std::string Atuador::Tipo() const {
    return "Atuador";
}
