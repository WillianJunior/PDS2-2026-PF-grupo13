#include "Parametro.hpp"

Parametro::Parametro(double ValorAtual, std::string Desc, int id) {}

Parametro::Parametro(double ValorAtual, double Max, double Min, std::string Desc, int id) {}

bool Parametro::ValorValido(double Valor) const { return false; }

void Parametro::SetValorAtual(double Valor) {}

void Parametro::SetMax(double Valor) {}

void Parametro::SetMin(double Valor) {}

void Parametro::SetDesc(std::string Desc) {}

bool Parametro::DiagnosticarParametro() { return false; }

double Parametro::GetValorAtual() const { return 0.0; }

double Parametro::GetMax() const { return 0.0; }

double Parametro::GetMin() const { return 0.0; }

std::string Parametro::GetDesc() const { return ""; }

bool Parametro::GetEstado() const { return false; }

const std::vector<double>& Parametro::GetHist() const { return _Hist; }

int Parametro::GetId() { return 0; }

void Parametro::ResetarLimites() {}

void Parametro::ResetarHistorico() {}
