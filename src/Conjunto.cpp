#include "Conjunto.hpp"
#include "Excecoes.hpp"

#include <iostream>
#include <utility>

Conjunto::Conjunto(int id, std::string nome, std::string desc) {
    if (id < 0) {
        throw IdInvalido("Conjunto: id nao pode ser negativo");
    }
    if (desc.empty()) {
        throw EntradaInvalida("Conjunto: descricao vazia");
    }
    this->_id = id;
    this->_nome = nome;
    this->_desc = desc;
}

void Conjunto::AdicionarEquipamento(int id, std::string desc) {
    if (this->_Equipamentos.count(id) > 0) {
        throw IdDuplicado("Conjunto: equipamento com id ja existente");
    }
    this->_Equipamentos.emplace(id, std::make_unique<Equipamento>(id, desc, desc));
}

void Conjunto::AdicionarEquipamento(std::unique_ptr<Equipamento> equip) {
    if (equip == nullptr) {
        throw EntradaInvalida("Conjunto: equipamento nulo");
    }
    int id = equip->GetId();
    if (this->_Equipamentos.count(id) > 0) {
        throw IdDuplicado("Conjunto: equipamento com id ja existente");
    }
    this->_Equipamentos.emplace(id, std::move(equip));
}

void Conjunto::RemoverEquipamento(int id) {
    if (this->_Equipamentos.count(id) == 0) {
        throw IdInexistente("Conjunto: equipamento inexistente");
    }
    this->_Equipamentos.erase(id);
}

void Conjunto::SetDesc(std::string desc) {
    if (desc.empty()) {
        throw EntradaInvalida("Conjunto: descricao vazia");
    }
    this->_desc = desc;
}

void Conjunto::SetNome(std::string nome) {
    this->_nome = nome;
}

void Conjunto::ExibirEquipamentos() const {
    std::cout << "Conjunto " << this->_nome << std::endl;
    for (const auto& e : this->_Equipamentos) {
        std::cout << "Equipamento ID: " << e.first
                  << " (" << e.second->Tipo() << ")" << std::endl;
        e.second->ExibirParametros();
    }
}

void Conjunto::ExibirAlarmes() const {
    for (const auto& e : this->_Equipamentos) {
        e.second->ExibirAlarmes();
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
        total += e.second->QuantidadeAlarmes();
    }
    return total;
}

std::vector<int> Conjunto::DiagnosticarConjunto() const {
    std::vector<int> falhas;
    for (const auto& e : this->_Equipamentos) {
        std::vector<int> f = e.second->DiagnosticarEquipamento();
        falhas.insert(falhas.end(), f.begin(), f.end());
    }
    return falhas;
}

void Conjunto::AtualizarAlarmes() {
    for (auto& e : this->_Equipamentos) {
        e.second->AtualizarAlarmes();
    }
}

const std::map<int, std::unique_ptr<Equipamento>>& Conjunto::GetEquipamentos() const {
    return _Equipamentos;
}

Equipamento& Conjunto::AcessarEquipamento(int id) {
    auto it = this->_Equipamentos.find(id);
    if (it == this->_Equipamentos.end()) {
        throw IdInexistente("Conjunto: equipamento inexistente");
    }
    return *it->second;
}

int Conjunto::GetId() const { return this->_id; }

std::string Conjunto::GetDesc() const { return this->_desc; }

std::string Conjunto::GetNome() const { return this->_nome; }
