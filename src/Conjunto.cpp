#include "Conjunto.hpp"
#include "Excecoes.hpp"

#include <iostream>
#include <utility>

Conjunto::Conjunto(int id, std::string nome, std::string desc) {
    if (id < 0) {
        throw IdInvalido("id negativo nao rola");
    }
    if (desc.empty()) {
        throw EntradaInvalida("descricao do conjunto vazia");
    }
    this->_id = id;
    this->_nome = nome;
    this->_desc = desc;
}

void Conjunto::AdicionarEquipamento(int id, std::string desc) {
    if (this->_Equipamentos.count(id) > 0) {
        throw IdDuplicado("ja existe equipamento com esse id no conjunto");
    }
    this->_Equipamentos.emplace(id, std::make_unique<Equipamento>(id, desc, desc));
    if (id >= this->_ProximoIdEquipamento) {
        this->_ProximoIdEquipamento = id + 1;
    }
}

void Conjunto::AdicionarEquipamento(std::unique_ptr<Equipamento> equip) {
    if (equip == nullptr) {
        throw EntradaInvalida("equipamento nulo");
    }
    int id = equip->GetId();
    if (this->_Equipamentos.count(id) > 0) {
        throw IdDuplicado("id de equipamento repetido");
    }
    this->_Equipamentos.emplace(id, std::move(equip));
    if (id >= this->_ProximoIdEquipamento) {
        this->_ProximoIdEquipamento = id + 1;
    }
}

int Conjunto::ProximoIdEquipamento() const { return _ProximoIdEquipamento; }

void Conjunto::RemoverEquipamento(int id) {
    if (this->_Equipamentos.count(id) == 0) {
        throw IdInexistente("equipamento nao achado");
    }
    this->_Equipamentos.erase(id);
}

void Conjunto::SetDesc(std::string desc) {
    if (desc.empty()) {
        throw EntradaInvalida("descricao vazia");
    }
    _desc = desc;
}

void Conjunto::SetNome(std::string nome) { _nome = nome; }

void Conjunto::ExibirEquipamentos() const {
    if (this->_Equipamentos.size() > 0){
        for (const auto& e : this->_Equipamentos) {
            std::cout << "Equipamento ID: " << e.first
                    << " (" << e.second->Tipo() << ")" << std::endl;
            e.second->ExibirParametros();
        }

        return;
    }
    
    std::cout << "Nenhum equipamento presente" << std::endl;
}

void Conjunto::ExibirAlarmes() const {
    if (this->_Equipamentos.size() > 0){
        for (const auto& e : this->_Equipamentos) {
            e.second->ExibirAlarmes();
        }

        return;
    }

    std::cout << "Nenhum alarme presente" << std::endl;
}

void Conjunto::ExibirTudo() const {

    this->ExibirEquipamentos();
    this->ExibirAlarmes();
}

int Conjunto::QuantidadeEquipamentos() const {
    return static_cast<int>(_Equipamentos.size());
}

int Conjunto::QuantidadeAlarmes() const {
    int total = 0;
    for (const auto& e : _Equipamentos) {
        total += e.second->QuantidadeAlarmes();
    }
    return total;
}

std::vector<int> Conjunto::DiagnosticarConjunto() const {
    std::vector<int> falhas;
    for (const auto& e : _Equipamentos) {
        auto f = e.second->DiagnosticarEquipamento();
        falhas.insert(falhas.end(), f.begin(), f.end());
    }
    return falhas;
}

void Conjunto::AtualizarAlarmes() {
    for (auto& e : _Equipamentos) {
        e.second->AtualizarAlarmes();
    }
}

const std::map<int, std::unique_ptr<Equipamento>>& Conjunto::GetEquipamentos() const {
    return _Equipamentos;
}

Equipamento& Conjunto::AcessarEquipamento(int id) {
    auto it = _Equipamentos.find(id);
    if (it == _Equipamentos.end()) {
        throw IdInexistente("equipamento nao achado");
    }
    return *it->second;
}

int Conjunto::GetId() const { return _id; }
std::string Conjunto::GetDesc() const { return _desc; }
std::string Conjunto::GetNome() const { return _nome; }
