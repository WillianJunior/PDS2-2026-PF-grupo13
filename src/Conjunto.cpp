#include "Conjunto.hpp"

#include <iostream>

Conjunto::Conjunto(int id, std::string nome, std::string desc) {
    this->_id = id;
    this->_nome = nome;
    this->_desc = desc;
}

void Conjunto::AdicionarEquipamento(int id, std::string desc) {
    this->_Equipamentos.insert({id, Equipamento(id, desc, desc)});
}

void Conjunto::RemoverEquipamento(int id) {
    this->_Equipamentos.erase(id);
}

void Conjunto::SetDesc(std::string desc) {
    this->_desc = desc;
}

void Conjunto::SetNome(std::string nome) {
    this->_nome = nome;
}

void Conjunto::ExibirEquipamentos() const {
    std::cout << "Conjunto " << this->_nome << std::endl;
    for (const auto& e : this->_Equipamentos) {
        std::cout << "Equipamento ID: " << e.first << std::endl;
        e.second.ExibirParametros();
    }
}

void Conjunto::ExibirAlarmes() const {
    for (const auto& e : this->_Equipamentos) {
        e.second.ExibirAlarmes();
    }
}

void Conjunto::ExibirTudo() const {
    this->ExibirEquipamentos();
    this->ExibirAlarmes();
}

int Conjunto::QuantidadeEquipamentos() const {
    return static_cast<int>(this->_Equipamentos.size());
}

int Conjunto::QuantidadeAlarmes() const {
    int total = 0;
    for (const auto& e : this->_Equipamentos) {
        total += e.second.QuantidadeAlarmes();
    }
    return total;
}

std::vector<int> Conjunto::DiagnosticarConjunto() const {
    std::vector<int> falhas;
    for (const auto& e : this->_Equipamentos) {
        std::vector<int> f = e.second.DiagnosticarEquipamento();
        falhas.insert(falhas.end(), f.begin(), f.end());
    }
    return falhas;
}

void Conjunto::AtualizarAlarmes() {
    for (auto& e : this->_Equipamentos) {
        e.second.AtualizarAlarmes();
    }
}

const std::map<int, Equipamento>& Conjunto::GetEquipamentos() const { return _Equipamentos; }

int Conjunto::GetId() const { return this->_id; }

std::string Conjunto::GetDesc() const { return this->_desc; }

std::string Conjunto::GetNome() const { return this->_nome; }
