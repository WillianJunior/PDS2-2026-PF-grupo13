#include "Conjunto.hpp"

Conjunto::Conjunto(int id, std::string desc) {}

void Conjunto::AdicionarEquipamento(int id, std::string desc) {}

void Conjunto::RemoverEquipamento(int id) {}

void Conjunto::SetDesc(std::string desc) {}

void Conjunto::SetNome(std::string nome) {}

void Conjunto::ExibirEquipamentos() const {}

void Conjunto::ExibirAlarmes() const {}

void Conjunto::ExibirTudo() const {}

int Conjunto::QuantidadeEquipamentos() const { return 0; }

int Conjunto::QuantidadeAlarmes() const { return 0; }

std::vector<int> Conjunto::DiagnosticarConjunto() const { return {}; }

void Conjunto::AtualizarAlarmes() {}

const std::vector<Equipamento>& Conjunto::GetEquipamentos() const { return _Equipamentos; }

int Conjunto::GetId() const { return 0; }

std::string Conjunto::GetDesc() const { return ""; }

std::string Conjunto::GetNome() const { return ""; }
