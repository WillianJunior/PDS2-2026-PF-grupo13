#include "LinhaDeProducao.hpp"
#include "Excecoes.hpp"

#include <iostream>
#include <utility>

LinhaDeProducao::LinhaDeProducao(int id, std::string desc, std::string local, std::string nome) {
    if (id < 0) {
        throw IdInvalido("id da linha invalido (< 0)");
    }
    if (desc.empty()) {
        throw EntradaInvalida("descricao da linha esta vazia");
    }
    this->_id = id;
    this->_desc = desc;
    this->_local = local;
    this->_nome = nome;
}

void LinhaDeProducao::AdicionarConjunto(int id, std::string nome, std::string desc) {
    if (this->_Conjuntos.count(id) > 0) {
        throw IdDuplicado("ja tem um conjunto com esse id na linha");
    }
    Conjunto c(id, nome, desc);
    this->_Conjuntos.emplace(id, std::move(c));
    if (id >= this->_ProximoIdConjunto) {
        this->_ProximoIdConjunto = id + 1;
    }
}

int LinhaDeProducao::AdicionarConjunto(std::string nome, std::string desc) {
    int id = this->_ProximoIdConjunto;
    this->AdicionarConjunto(id, nome, desc);
    return id;
}

int LinhaDeProducao::ProximoIdConjunto() const { return _ProximoIdConjunto; }

void LinhaDeProducao::RemoverConjunto(int id) {
    if (this->_Conjuntos.count(id) == 0) {
        throw IdInexistente("conjunto nao encontrado");
    }
    this->_Conjuntos.erase(id);
}

void LinhaDeProducao::ExibirConjuntos() const {
    for (const auto& conjunto : this->_Conjuntos){
        std::cout << "Conjunto ID: " << conjunto.first << " - " << conjunto.second.GetNome() << std::endl;
        std::cout << "Desc: " << conjunto.second.GetDesc() << std::endl;
    }
}

void LinhaDeProducao::ExibirAlarmes() const {
    for (const auto& conjunto : this->_Conjuntos){
        conjunto.second.ExibirAlarmes();
    }
}

void LinhaDeProducao::ExibirTudo() const {
    std::cout << "Desc: " << GetDesc() << std::endl;
    std::cout << "Local: " << GetLocal() << std::endl;
    std::cout << "Id " << GetId() << std::endl;
    for (const auto& conjunto : _Conjuntos) {
        std::cout << "-- Conjunto " << conjunto.second.GetNome() << " --" << std::endl;
        std::cout << "ID: " << conjunto.first << std::endl;
        std::cout << "Desc: " << conjunto.second.GetDesc() << std::endl;
        conjunto.second.ExibirTudo();
    }
}

int LinhaDeProducao::QuantidadeConjuntos() const {
    return static_cast<int>(_Conjuntos.size());
}

int LinhaDeProducao::QuantidadeAlarmes() const {
    int total = 0;
    for (const auto& conjunto : _Conjuntos) {
        total += conjunto.second.QuantidadeAlarmes();
    }
    return total;
}

std::vector<int> LinhaDeProducao::DiagnosticarLinha() const {
    std::vector<int> falhas;
    for (const auto& conjunto : _Conjuntos) {
        auto f = conjunto.second.DiagnosticarConjunto();
        falhas.insert(falhas.end(), f.begin(), f.end());
    }
    return falhas;
}

void LinhaDeProducao::AtualizarAlarmes() {
    for (auto& conjunto : _Conjuntos) {
        conjunto.second.AtualizarAlarmes();
    }
}

void LinhaDeProducao::SetDesc(std::string desc) { _desc = desc; }
void LinhaDeProducao::SetLocal(std::string local) { _local = local; }
void LinhaDeProducao::SetNome(std::string nome) { _nome = nome; }

const std::map<int, Conjunto>& LinhaDeProducao::GetConjuntos() const { return _Conjuntos; }

Conjunto& LinhaDeProducao::AcessarConjunto(int id) {
    auto it = _Conjuntos.find(id);
    if (it == _Conjuntos.end()) {
        throw IdInexistente("conjunto nao encontrado");
    }
    return it->second;
}

int LinhaDeProducao::GetId() const { return _id; }
std::string LinhaDeProducao::GetDesc() const { return _desc; }
std::string LinhaDeProducao::GetLocal() const { return _local; }
std::string LinhaDeProducao::GetNome() const { return _nome; }
