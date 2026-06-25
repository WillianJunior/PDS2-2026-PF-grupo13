#include "Equipamento.hpp"
#include "Excecoes.hpp"

#include <iostream>

Equipamento::Equipamento(int id, std::string desc, std::string nome) {
    if (id < 0) {
        throw IdInvalido("Equipamento: id nao pode ser negativo");
    }
    if (desc.empty()) {
        throw EntradaInvalida("Equipamento: descricao vazia");
    }
    this->_id = id;
    this->_desc = desc;
    this->_nome = nome;
}

std::string Equipamento::Tipo() const { return "Equipamento"; }

void Equipamento::AdicionarParametro(double ValorAtual, std::string Desc, int id) {
    if (this->_Parametros.count(id) > 0) {
        throw IdDuplicado("Equipamento: parametro com id ja existente");
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
        throw IdDuplicado("Equipamento: parametro com id ja existente");
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
    return this->_ProximoIdParametro;
}

void Equipamento::RemoverParametro(int id) {
    if (this->_Parametros.count(id) == 0) {
        throw IdInexistente("Equipamento: parametro inexistente");
    }
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
    int iterator = 0;
    for (const auto& p : this->_Parametros) {
        iterator += 1;
        std::cout << p.first << " - " << p.second.GetDesc() << " : " << p.second.GetValorAtual() << std::endl;
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

std::string Equipamento::GetDesc() const { return this->_desc; }

std::string Equipamento::GetNome() const { return this->_nome; }

const std::map<int, Parametro>& Equipamento::GetParametros() const {
    return this->_Parametros;
}

const std::vector<Alarme>& Equipamento::GetAlarmes() const {
    return this->_Alarmes;
}

void Equipamento::SetDesc(std::string desc) {
    this->_desc = desc;
}
