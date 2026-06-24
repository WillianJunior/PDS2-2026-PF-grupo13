#include "Sistema.hpp"

#include <iostream>
#include <algorithm>

Sistema::Sistema() : _UsuarioLogadoIdx(-1) {
    this->_ProximoId = 1;
}

void Sistema::AdicionarId(int Id) {
    this->_IdsAtivos.push_back(Id);
}

void Sistema::RemoverId(int Id) {
    this->_IdsAtivos.erase(
        std::remove(this->_IdsAtivos.begin(), this->_IdsAtivos.end(), Id),
        this->_IdsAtivos.end());
}

void Sistema::AdicionarLinha(int id, std::string desc, std::string local, std::string nome) {
    LinhaDeProducao Linha(id, desc, local, nome);

    this->_Linhas.insert({id, Linha});
    this->AdicionarId(id);
}

void Sistema::AdicionarLinha(std::string desc, std::string local, std::string nome) {

    int id = this->ProximoIdDisponivel();

    Sistema::AdicionarLinha(id, desc, local, nome);
}

void Sistema::RemoverLinha(int id) {
    this->_Linhas.erase(id);
    this->RemoverId(id);
}

const std::map<int, LinhaDeProducao>& Sistema::GetLinhas() const {
    return _Linhas;
}

void Sistema::ExibirLinhas() {
    std::cout << "Linhas de produção:" << std::endl;
    for (const auto& linha : this->_Linhas){
        std::cout << "Linha ID: " << linha.first << " - " << linha.second.GetNome() << std::endl
        << "Local: " << linha.second.GetLocal() << std::endl
        << "Descrição: " << linha.second.GetDesc() << std::endl;
    }
}

void Sistema::AdicionarUsuario(std::string login, std::string senha, Cargo cargo) {
     Usuario user(login, senha, cargo);

    this->_Usuarios.push_back(user);

    std::cout << "Usuário " << login << " adicionado." << std::endl;
}

void Sistema::RemoverUsuario(std::string login) {

    if (this->_Usuarios.size() < 1){
        return;
    }

    for (size_t i = 0; i < this->_Usuarios.size(); i++){
        if (this->_Usuarios[i].GetLogin() == login){
            this->_Usuarios.erase(this->_Usuarios.begin() + i);
            std::cout << "Usuário " << login << " removido." << std::endl;

            return;
        }
    }
    std::cout << "Nenhum usuário removido." << std::endl;
}

int Sistema::ProximoIdDisponivel() const {
    int x = 1;
    while (this->IdAtivo(x)) {
        x++;
    }
    return x;
}

bool Sistema::IdAtivo(int Id) const {
    for (const auto& elemento : this->_IdsAtivos){
        if (elemento == Id){
            return true;
        }
    }
    return false;
}

bool Sistema::Login(std::string login, std::string senha) {

    for (size_t i = 0; i < this->_Usuarios.size(); i++){
        if (this->_Usuarios[i].GetLogin() == login && this->_Usuarios[i].ValidarSenha(senha) == true){
            this->_UsuarioLogadoIdx = static_cast<int>(i);

            std::cout << "Usuário " << login << " logado." << std::endl;

            return true;
        }
    }
    std::cout << "Usuário " << login << " não encontrado." << std::endl;
    return false;

}

bool Sistema::Logout() {
    if (this->_UsuarioLogadoIdx != -1){
        this->_UsuarioLogadoIdx = -1;
        return true;
    }

    return false;
}

Usuario* Sistema::GetUsuarioLogado() const {
    if (this->_UsuarioLogadoIdx == -1){
        return nullptr;
    }

    return const_cast<Usuario*>(&this->_Usuarios[this->_UsuarioLogadoIdx]);
}

bool Sistema::SalvarAlteracoes() { return false; }

bool Sistema::CarregarUltimoSave() { return false; }

bool Sistema::CarregarSave(std::string arquivo) { (void)arquivo; return false; }
