#include "LinhaDeProducao.hpp"
#include "Excecoes.hpp"

#include <iostream>
#include <utility>

LinhaDeProducao::LinhaDeProducao(int id, std::string desc, std::string local, std::string nome) {
    if (id < 0) {
        throw IdInvalido("LinhaDeProducao: id nao pode ser negativo");
    }
    if (desc.empty()) {
        throw EntradaInvalida("LinhaDeProducao: descricao vazia");
    }
    this->_id = id;
    this->_desc = desc;
    this->_local = local;
    this->_nome = nome;
}

void LinhaDeProducao::AdicionarConjunto(int id, std::string nome, std::string desc) {
    if (this->_Conjuntos.count(id) > 0) {
        throw IdDuplicado("LinhaDeProducao: conjunto com id ja existente");
    }
    Conjunto c(id, nome, desc);
    this->_Conjuntos.emplace(id, std::move(c));
}

void LinhaDeProducao::RemoverConjunto(int id) {
    if (this->_Conjuntos.count(id) == 0) {
        throw IdInexistente("LinhaDeProducao: conjunto inexistente");
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
    for (const auto& conjunto : this->_Conjuntos){
        std::cout << "Conjunto ID: " << conjunto.first << " - " << conjunto.second.GetNome() << std::endl;
        std::cout << "Desc: " << conjunto.second.GetDesc() << std::endl;
        conjunto.second.ExibirTudo();
    }
}

int LinhaDeProducao::QuantidadeConjuntos() const {
    return static_cast<int>(this->_Conjuntos.size());
}

int LinhaDeProducao::QuantidadeAlarmes() const {
    int total = 0;
    for (const auto& conjunto : this->_Conjuntos){
        total += conjunto.second.QuantidadeAlarmes();
    }
    return total;
}

std::vector<int> LinhaDeProducao::DiagnosticarLinha() const {
    std::vector<int> falhas;
    for (const auto& conjunto : this->_Conjuntos){
        std::vector<int> f = conjunto.second.DiagnosticarConjunto();
        falhas.insert(falhas.end(), f.begin(), f.end());
    }
    return falhas;
}

void LinhaDeProducao::AtualizarAlarmes() {
    for (auto& conjunto : this->_Conjuntos){
        conjunto.second.AtualizarAlarmes();
    }
}

void LinhaDeProducao::SetDesc(std::string desc) {
    this->_desc = desc;
}

void LinhaDeProducao::SetLocal(std::string local) {
    this->_local = local;
}

void LinhaDeProducao::SetNome(std::string nome) {
    this->_nome = nome;
}

const std::map<int, Conjunto>& LinhaDeProducao::GetConjuntos() const { return _Conjuntos; }

Conjunto& LinhaDeProducao::AcessarConjunto(int id) {
    auto it = this->_Conjuntos.find(id);
    if (it == this->_Conjuntos.end()) {
        throw IdInexistente("LinhaDeProducao: conjunto inexistente");
    }
    return it->second;
}

int LinhaDeProducao::GetId() const { 
    return this->_id; 
}

std::string LinhaDeProducao::GetDesc() const {
    return this->_desc;
}

std::string LinhaDeProducao::GetLocal() const {
    return this->_local;
}

std::string LinhaDeProducao::GetNome() const {
    return this->_nome;
}
