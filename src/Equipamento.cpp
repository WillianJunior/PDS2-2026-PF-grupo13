#include "Equipamento.hpp"

#include <iostream>

Equipamento::Equipamento(int id, std::string desc, std::string nome) {
    this->_id = id;
    this->_desc = desc;
    this->_nome = nome;
}

void Equipamento::AdicionarParametro(double ValorAtual, std::string Desc, int id) {
    Parametro p(ValorAtual, Desc, id);

    this->_Parametros.insert({id, p});
}

void Equipamento::AdicionarParametro(double ValorAtual, double Max, double Min, std::string Desc, int id) {
    Parametro p(ValorAtual, Max, Min, Desc, id);

    this->_Parametros.insert({id, p});
}

void Equipamento::RemoverParametro(int id) {
    this->_Parametros.erase(id);
}

std::vector<int> Equipamento::DiagnosticarEquipamento() const {
    std::vector<int> falhas;
    for (const auto& p : this->_Parametros) {
        if (!p.second.ValorValido(p.second.GetValorAtual())) {
            falhas.push_back(p.first);
        }
    }
    return falhas;
}

void Equipamento::AtualizarAlarmes() {
    this->_Alarmes.clear();
    for (auto& p : this->_Parametros) {
        Alarme a(p.second.GetDesc(), p.first, p.second);
        a.AtualizarAlarme();
        this->_Alarmes.push_back(a);
    }
}

void Equipamento::ExibirParametros() const {
    std::cout << "Equipamento " << this->_nome << std::endl;
    for (const auto& p : this->_Parametros) {
        std::cout << p.first << " - " << p.second.GetDesc() << " " << p.second.GetValorAtual() << std::endl;
    }
}

void Equipamento::ExibirAlarmes() const {
    std::cout << "Alarmes do equipamento " << this->_nome << std::endl;
    for (const auto& a : this->_Alarmes) {
        std::cout << "Alarme " << (a.GetEstado() ? "ATIVO" : "inativo") << std::endl;
    }
}

int Equipamento::QuantidadeParametros() const { return static_cast<int>(this->_Parametros.size()); }

int Equipamento::QuantidadeAlarmes() const { return static_cast<int>(this->_Alarmes.size()); }

int Equipamento::GetId() const {
    return this->_id;
}

const std::map<int, Parametro>& Equipamento::GetParametros() const {
    return this->_Parametros;
}

const std::vector<Alarme>& Equipamento::GetAlarmes() const {
    return this->_Alarmes;
}

void Equipamento::SetDesc(std::string desc) {
    this->_desc = desc;
}
