#include "Equipamento.hpp"
#include "Excecoes.hpp"

#include <iostream>

Equipamento::Equipamento(int id, std::string desc, std::string nome) {
    if (id < 0) {
        throw IdInvalido("equipamento com id negativo");
    }
    if (desc.empty()) {
        throw EntradaInvalida("precisa de uma descricao pro equipamento");
    }
    this->_id = id;
    this->_desc = desc;
    this->_nome = nome;
}

std::string Equipamento::Tipo() const { return "Equipamento"; }

void Equipamento::AdicionarParametro(double ValorAtual, std::string Desc, int id) {
    if (this->_Parametros.count(id) > 0) {
        throw IdDuplicado("parametro duplicado nesse equipamento");
    }
    Parametro p(ValorAtual, Desc, id);

    this->_Parametros.insert({id, p});
    if (id >= this->_ProximoIdParametro) {
        this->_ProximoIdParametro = id + 1;
    }
}

int Equipamento::AdicionarParametro(double ValorAtual, std::string Desc) {
    int id = this->_ProximoIdParametro;
    this->AdicionarParametro(ValorAtual, Desc, id);
    return id;
}

void Equipamento::AdicionarParametro(double ValorAtual, double Max, double Min, std::string Desc, int id) {
    if (this->_Parametros.count(id) > 0) {
        throw IdDuplicado("id de parametro repetido");
    }
    Parametro p(ValorAtual, Max, Min, Desc, id);

    this->_Parametros.insert({id, p});
    if (id >= this->_ProximoIdParametro) {
        this->_ProximoIdParametro = id + 1;
    }
}

int Equipamento::AdicionarParametro(double ValorAtual, double Max, double Min, std::string Desc) {
    int id = this->_ProximoIdParametro;
    this->AdicionarParametro(ValorAtual, Max, Min, Desc, id);
    return id;
}

int Equipamento::ProximoIdParametro() const {
    return _ProximoIdParametro;
}

void Equipamento::RemoverParametro(int id) {
    if (this->_Parametros.count(id) == 0) {
        throw IdInexistente("parametro nao existe");
    }
    this->_Parametros.erase(id);
}

std::vector<int> Equipamento::DiagnosticarEquipamento() const {
    std::vector<int> falhas;
    for (const auto& p : _Parametros) {
        if (!p.second.ValorValido(p.second.GetValorAtual())) {
            falhas.push_back(p.first);
        }
    }
    return falhas;
}

void Equipamento::AtualizarAlarmes() {
    _Alarmes.clear();
    for (auto& p : _Parametros) {
        Alarme a(p.second.GetDesc(), p.first, p.second);
        a.AtualizarAlarme();
        _Alarmes.push_back(a);
    }
}

void Equipamento::ExibirParametros() const {
    std::cout << "Equipamento " << _nome << std::endl;
    for (const auto& p : _Parametros) {
        std::cout << p.first << " - " << p.second.GetDesc() << " : " << p.second.GetValorAtual() << std::endl;
    }
}

void Equipamento::ExibirAlarmes() const {
    std::cout << "Alarmes do equipamento " << _nome << std::endl;
    for (const auto& a : _Alarmes) {
        std::string estado;
        if (a.GetEstado()) {
            estado = "ATIVO";
        } else {
            estado = "inativo";
        }
        std::cout << "Alarme " << estado << std::endl;
    }
}

int Equipamento::QuantidadeParametros() const {
    return static_cast<int>(_Parametros.size());
}

int Equipamento::QuantidadeAlarmes() const {
    return static_cast<int>(_Alarmes.size());
}

int Equipamento::GetId() const { return _id; }
std::string Equipamento::GetDesc() const { return _desc; }
std::string Equipamento::GetNome() const { return _nome; }

const std::map<int, Parametro>& Equipamento::GetParametros() const {
    return _Parametros;
}

const std::vector<Alarme>& Equipamento::GetAlarmes() const {
    return _Alarmes;
}

void Equipamento::SetDesc(std::string desc) {
    _desc = desc;
}
