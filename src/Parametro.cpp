#include "Parametro.hpp"

#include <limits>

Parametro::Parametro(double ValorAtual, std::string Desc, int id) {
    this->_Estado = false;

    double Backup_min = this->_Min;
    double Backup_max = this->_Max;

    this->_Min = std::numeric_limits<double>::lowest();
    this->_Max = std::numeric_limits<double>::max();

    if (this->ValorValido(ValorAtual)){
        this->_ValorAtual = ValorAtual;
        this->_Hist.push_back(this->_ValorAtual);
    } else {
        this->_Min = Backup_min;
        this->_Max = Backup_max;
        return;
    }

    this->_Desc = Desc;
    this->_id = id;
}

Parametro::Parametro(double ValorAtual, double Max, double Min, std::string Desc, int id) {
    this->_Estado = false;

    double Backup_min = this->_Min;
    double Backup_max = this->_Max;

    if ((Max >= Min) && 
        (Min >= std::numeric_limits<double>::lowest()) &&
        (Max <= std::numeric_limits<double>::max())){

            this->_Min = Min;
            this->_Max = Max;
    } else {
        return;
    }

    if (this->ValorValido(ValorAtual)){
        this->_ValorAtual = ValorAtual;
        this->_Hist.push_back(this->_ValorAtual);
    } else {
        this->_Min = Backup_min;
        this->_Max = Backup_max;
        return;
    }

    this->_Desc = Desc;
    this->_id = id;
}

bool Parametro::ValorValido(double Valor) const {
    return (Valor >= this->_Min)&&(Valor <= this->_Max);
}

void Parametro::SetValorAtual(double Valor) {
    this->_ValorAtual = Valor;
    this->_Hist.push_back(this->_ValorAtual);
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

bool Parametro::DiagnosticarParametro() {
    this->_Estado = !this->ValorValido(this->_ValorAtual);
    return this->_Estado;
}

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

const std::vector<double>& Parametro::GetHist() const { 
    return this->_Hist;
}

int Parametro::GetId() {
    return this->_id;
}

void Parametro::ResetarLimites() {
    this->_Min = std::numeric_limits<double>::lowest();
    this->_Max = std::numeric_limits<double>::max();
}

void Parametro::ResetarHistorico() {
    this->_Hist.clear();
}
