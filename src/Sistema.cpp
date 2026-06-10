#include "Sistema.hpp"

Sistema::Sistema() : _UsuarioLogado(nullptr) {}

void Sistema::AdicionarId(int Id) {}

void Sistema::RemoverId(int Id) {}

void Sistema::AdicionarLinha(int id, std::string desc, std::string local, std::string nome) {}

void Sistema::RemoverLinha(int id) {}

const std::vector<LinhaDeProducao>& Sistema::GetLinhas() const { return _Linhas; }

void Sistema::ExibirLinhas() {}

void Sistema::AdicionarUsuario(std::string login, std::string senha, Cargo cargo) {
     Usuario user(login, senha, cargo);

    this->_Usuarios.push_back(user);

    std::cout << "Usuário " << login << " adicionado." << endl;
}

void Sistema::RemoverUsuario(std::string login) {

    if (this->_Usuarios.size < 1){
        return;
    }

    for (int i = 0; i < this->_Usuarios.size; i++){
        if (this->_Usuarios[i] == login){
            this->_Usuarios.erase(i);
            std::cout << "Usuário " << login << " removido." << endl;

            return;
        }
    }
    std::cout << "Nenhum usuário removido." << endl
}

int Sistema::ProximoIdDisponivel() const { return 0; }

bool Sistema::IdDisponivel(int Id) const { return false; }

bool Sistema::Login(std::string login, std::string senha) { 

    for (int i = 0; i < this->_Usuarios.size; i++){
        if (this->_Usuarios[i].GetLogin == login && this->_Usuarios[i].ValidarSenha(senha) == true){
            this->_UsuarioLogado = &this->_Usuarios[i];

            std::cout << "Usuário " << login << " logado." << endl;

            return true;
        }
    }
    std::cout << "Usuário " << login << " não encontrado." << endl;
    return false;

 }

bool Sistema::Logout() { return false; }

Usuario* Sistema::GetUsuarioLogado() const { return nullptr; }

bool Sistema::SalvarAlteracoes() { return false; }

bool Sistema::CarregarUltimoSave() { return false; }

bool Sistema::CarregarSave(std::string arquivo) {  }
