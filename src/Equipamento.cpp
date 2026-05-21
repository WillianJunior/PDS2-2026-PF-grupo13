#include "Equipamento.hpp"

Equipamento::Equipamento(int id, std::string desc) {}

void Equipamento::AdicionarParametro(double ValorAtual, std::string Desc, int id) {}

void Equipamento::AdicionarParametroComLimites(double ValorAtual, double Max, double Min, std::string Desc) {}

void Equipamento::RemoverParametro(int id) {}

std::vector<int> Equipamento::DiagnosticarEquipamento() const { return {}; }

void Equipamento::AtualizarAlarmes() {}

void Equipamento::ExibirParametros() const {}

void Equipamento::ExibirAlarmes() const {}

int Equipamento::QuantidadeParametros() const { return 0; }

int Equipamento::QuantidadeAlarmes() const { return 0; }

int Equipamento::GetId() const { return 0; }

const std::vector<Parametro>& Equipamento::GetParametros() const { return _Parametros; }

const std::vector<Alarme>& Equipamento::GetAlarmes() const { return _Alarmes; }

void Equipamento::SetDesc(std::string desc) {}
