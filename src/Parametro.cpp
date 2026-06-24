#include "Parametro.hpp"

Parametro::Parametro(double ValorAtual, std::string Desc, int id) {}

Parametro::Parametro(double ValorAtual, double Max, double Min, std::string Desc, int id) {}

bool Parametro::ValorValido(double Valor) const {
    return (Valor >= this->_Min)&&(Valor <= this->_Max);
}

void Parametro::SetValorAtual(double Valor) {
    this->_ValorAtual = Valor;
}

void Parametro::SetMax(double Valor) {
    this->_Max = Valor;
}

void Parametro::SetMin(double Valor) {
    this->_Min = Valor;
}

void Parametro::SetDesc(std::string Desc) {
    this->_Desc = Desc;
}

bool Parametro::DiagnosticarParametro() { return false; }

double Parametro::GetValorAtual() const { 
    return this->_ValorAtual;
}

double Parametro::GetMax() const {
    return this->_Max;
}

double Parametro::GetMin() const {
    return this->_Min;
}

std::string Parametro::GetDesc() const {
    return this->_Desc;
}

bool Parametro::GetEstado() const {
    return this->_Estado;
}

const std::vector<double>& Parametro::GetHist() const { return _Hist; }

int Parametro::GetId() {
    return this->_id;
}

void Parametro::ResetarLimites() {}

void Parametro::ResetarHistorico() {}
