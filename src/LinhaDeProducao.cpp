#include "LinhaDeProducao.hpp"

#include <iostream>

LinhaDeProducao::LinhaDeProducao(int id, std::string desc, std::string local, std::string nome) {
    
}

void LinhaDeProducao::AdicionarConjunto(int id, std:string nome, std::string desc) {
    Conjunto c(id, nome, desc);
    this->_Conjuntos[id] = c;
}

void LinhaDeProducao::RemoverConjunto(int id) {
    this->_Conjuntos.erase(id);
}

void LinhaDeProducao::ExibirConjuntos() const {
    for (const auto& conjunto : this->_Conjuntos){
        std::cout << "Conjunto ID: " << conjunto.first << " - " << conjunto.second.GetNome() << endl;
        std::cout << "Desc: " << conjunto.second.GetDesc(); << endl;
    }
}

void LinhaDeProducao::ExibirAlarmes() const {}

void LinhaDeProducao::ExibirTudo() const {}

int LinhaDeProducao::QuantidadeConjuntos() const {
    int i = 0;
    for (const auto& conjunto : this->_Conjuntos){
        i++;
    }
    return i;
}

int LinhaDeProducao::QuantidadeAlarmes() const { return 0; }

std::vector<int> LinhaDeProducao::DiagnosticarLinha() const { return {}; }

void LinhaDeProducao::AtualizarAlarmes() {}

void LinhaDeProducao::SetDesc(std::string desc) {
    this->_desc = desc;
}

void LinhaDeProducao::SetLocal(std::string local) {
    this->_local = local;
}

void LinhaDeProducao::SetNome(std::string nome) {
    this->_nome = nome;
}

const std::vector<Conjunto>& LinhaDeProducao::GetConjuntos() const { return _Conjuntos; }

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
