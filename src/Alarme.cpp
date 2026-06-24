#include "Alarme.hpp"

Alarme::Alarme(std::string Desc, int Id, Parametro& p) {
    this->_Desc = Desc;
    this->_Id = Id;
    this->_Parametro = &p;
    this->_Estado = false;
}

bool Alarme::AtualizarAlarme() {
    bool falha = !this->_Parametro->ValorValido(this->_Parametro->GetValorAtual());
    this->_Estado = falha;
    return falha;
}

bool Alarme::GetEstado() const { 
    return this->_Estado;
}

void Alarme::SetEstado(bool Estado) {
    this->_Estado = Estado;
}

void Alarme::SetDesc(std::string desc) {
    this->_Desc = desc;
}
