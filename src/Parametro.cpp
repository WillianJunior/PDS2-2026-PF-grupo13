#include "Parametro.hpp"
#include "Excecoes.hpp"

#include <limits>

Parametro::Parametro(double ValorAtual, std::string Desc, int id) {
    if (Desc.empty()) {
        throw EntradaInvalida("parametro sem descricao");
    }
    if (id < 0) {
        throw IdInvalido("id de parametro < 0");
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
        throw EntradaInvalida("parametro sem descricao");
    }
    if (id < 0) {
        throw IdInvalido("id de parametro < 0");
    }
    if (Max < Min) {
        throw LimitesInvalidos("Max < Min, inverteu os limites?");
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
    return Valor >= _Min && Valor <= _Max;
}

void Parametro::SetValorAtual(double Valor) {
    _ValorAtual = Valor;
    _Hist.push_back(Valor);
}

void Parametro::SetMax(double Valor) {
    if (Valor < this->_Min) {
        throw LimitesInvalidos("novo Max ficaria abaixo do Min atual");
    }
    this->_Max = Valor;
}

void Parametro::SetMin(double Valor) {
    if (Valor > this->_Max) {
        throw LimitesInvalidos("novo Min passaria do Max");
    }
    this->_Min = Valor;
}

void Parametro::SetDesc(std::string Desc) {
    if (Desc.empty()) {
        throw EntradaInvalida("descricao vazia no SetDesc");
    }
    this->_Desc = Desc;
}

bool Parametro::DiagnosticarParametro() {
    _Estado = !ValorValido(_ValorAtual);
    return _Estado;
}

double Parametro::GetValorAtual() const { return _ValorAtual; }
double Parametro::GetMax() const { return _Max; }
double Parametro::GetMin() const { return _Min; }
std::string Parametro::GetDesc() const { return _Desc; }
bool Parametro::GetEstado() const { return _Estado; }

const std::vector<double>& Parametro::GetHist() const {
    return _Hist;
}

int Parametro::GetId() { return _id; }

void Parametro::ResetarLimites() {
    _Min = std::numeric_limits<double>::lowest();
    _Max = std::numeric_limits<double>::max();
}

void Parametro::ResetarHistorico() {
    _Hist.clear();
}
