#include "LinhaDeProducao.hpp"

LinhaDeProducao::LinhaDeProducao(int id, std::string desc, std::string local, std::string nome) {}

void LinhaDeProducao::AdicionarConjunto(int id, std::string desc) {}

void LinhaDeProducao::RemoverConjunto(int id) {}

void LinhaDeProducao::ExibirConjuntos() const {}

void LinhaDeProducao::ExibirAlarmes() const {}

void LinhaDeProducao::ExibirTudo() const {}

int LinhaDeProducao::QuantidadeConjuntos() const { return 0; }

int LinhaDeProducao::QuantidadeAlarmes() const { return 0; }

std::vector<int> LinhaDeProducao::DiagnosticarLinha() const { return {}; }

void LinhaDeProducao::AtualizarAlarmes() {}

void LinhaDeProducao::SetDesc(std::string desc) {}

void LinhaDeProducao::SetLocal(std::string local) {}

void LinhaDeProducao::SetNome(std::string nome) {}

const std::vector<Conjunto>& LinhaDeProducao::GetConjuntos() const { return _Conjuntos; }

int LinhaDeProducao::GetId() const { return 0; }

std::string LinhaDeProducao::GetDesc() const { return ""; }

std::string LinhaDeProducao::GetLocal() const { return ""; }

std::string LinhaDeProducao::GetNome() const { return ""; }
