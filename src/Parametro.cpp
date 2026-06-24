#include "Parametro.hpp"
#include "Excecoes.hpp"

#include <limits>

Parametro::Parametro(double ValorAtual, std::string Desc, int id) {
    if (Desc.empty()) {
        throw EntradaInvalida("Parametro: descricao vazia");
    }
    if (id < 0) {
        throw IdInvalido("Parametro: id nao pode ser negativo");
    }

    this->_Estado = false;
    this->_Min = std::numeric_limits<double>::lowest();
    this->_Max = std::numeric_limits<double>::max();

    // Uma leitura pode estar fora dos limites (caso de falha): sempre armazenada.
    this->_ValorAtual = ValorAtual;
    this->_Hist.push_back(this->_ValorAtual);

    this->_Desc = Desc;
    this->_id = id;
}

Parametro::Parametro(double ValorAtual, double Max, double Min, std::string Desc, int id) {
    if (Desc.empty()) {
        throw EntradaInvalida("Parametro: descricao vazia");
    }
    if (id < 0) {
        throw IdInvalido("Parametro: id nao pode ser negativo");
    }
    if (Max < Min) {
        throw LimitesInvalidos("Parametro: Max nao pode ser menor que Min");
    }

    this->_Estado = false;
    this->_Min = Min;
    this->_Max = Max;

    // Uma leitura pode estar fora dos limites (caso de falha): sempre armazenada.
    this->_ValorAtual = ValorAtual;
    this->_Hist.push_back(this->_ValorAtual);

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
    if (Valor < this->_Min) {
        throw LimitesInvalidos("Parametro: Max nao pode ser menor que Min");
    }
    this->_Max = Valor;
}

void Parametro::SetMin(double Valor) {
    if (Valor > this->_Max) {
        throw LimitesInvalidos("Parametro: Min nao pode ser maior que Max");
    }
    this->_Min = Valor;
}

void Parametro::SetDesc(std::string Desc) {
    if (Desc.empty()) {
        throw EntradaInvalida("Parametro: descricao vazia");
    }
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
