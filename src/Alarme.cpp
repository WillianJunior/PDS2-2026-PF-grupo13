#include "Alarme.hpp"

Alarme::Alarme(std::string Desc, int Id, Parametro& p) {
    this->_Desc = Desc;
    this->_Id = Id;
    this->_Parametro = p;
}

bool Alarme::AtualizarAlarme() { return false; }

bool Alarme::GetEstado() const { 
    return this->_Estado;
}

void Alarme::SetEstado(bool Estado) {
    this->_Estado = Estado;
}

void Alarme::SetDesc(std::string desc) {
    this->_Desc = desc;
}
