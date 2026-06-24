#include "Equipamento.hpp"

#include <iostream>

Equipamento::Equipamento(int id, std::string desc, std::string nome) {
    this->_id = id;
    this->_desc = desc;
    this->_nome = nome;
}

void Equipamento::AdicionarParametro(double ValorAtual, std::string Desc, int id) {
    Parametro p(ValorAtual, Desc, id);

    this->_Parametros.insert(id, p);
}

void Equipamento::AdicionarParametro(double ValorAtual, double Max, double Min, std::string Desc, ind id) {
    Parametro p(ValorAtual, Max, Min, Desc, id);

    this->_Parametros.insert(id, p);
}

void Equipamento::RemoverParametro(int id) {
    this->_Parametros.erase(id);
}

std::vector<int> Equipamento::DiagnosticarEquipamento() const { return {}; }

void Equipamento::AtualizarAlarmes() {}

void Equipamento::ExibirParametros() const {
    std::cout << "Equipamento " << this->_nome << std::endl;
    for (const auto& p : this->_Parametros) {
        std::cout << p.first << " - " << p.second.GetDesc() << " " << p.second.GetValorAtual() << std::endl;
    }
}

void Equipamento::ExibirAlarmes() const {}

int Equipamento::QuantidadeParametros() const { return 0; }

int Equipamento::QuantidadeAlarmes() const { return 0; }

int Equipamento::GetId() const { return 0; }

const std::vector<Parametro>& Equipamento::GetParametros() const { return _Parametros; }

const std::vector<Alarme>& Equipamento::GetAlarmes() const { return _Alarmes; }

void Equipamento::SetDesc(std::string desc) {}
