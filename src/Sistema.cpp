#include "Sistema.hpp"
#include "Excecoes.hpp"

#include <iostream>
#include <algorithm>
#include <utility>
#include <fstream>
#include <sstream>

Sistema::Sistema() : _UsuarioLogadoIdx(-1), _arquivoSave("dados/save.txt") {
    this->_ProximoId = 1;
}

void Sistema::AdicionarLinha(int id, std::string desc, std::string local, std::string nome) {
    if (this->IdAtivo(id)) {
        throw IdDuplicado("Sistema: linha com id ja existente");
    }
    LinhaDeProducao Linha(id, desc, local, nome);

    this->_Linhas.emplace(id, std::move(Linha));
    if (id >= this->_ProximoId) {
        this->_ProximoId = id + 1;
    }
}

int Sistema::AdicionarLinha(std::string desc, std::string local, std::string nome) {
    int id = this->_ProximoId;
    Sistema::AdicionarLinha(id, desc, local, nome);
    return id;
}

void Sistema::RemoverLinha(int id) {
    if (this->_Linhas.count(id) == 0) {
        throw IdInexistente("Sistema: linha inexistente");
    }
    this->_Linhas.erase(id);
}

const std::map<int, LinhaDeProducao>& Sistema::GetLinhas() const {
    return _Linhas;
}

LinhaDeProducao& Sistema::AcessarLinha(int id) {
    auto it = this->_Linhas.find(id);
    if (it == this->_Linhas.end()) {
        throw IdInexistente("Sistema: linha inexistente");
    }
    return it->second;
}

void Sistema::ExibirLinhas() {
    std::cout << "Linhas de producao:" << std::endl;
    for (const auto& linha : this->_Linhas){
        std::cout << "Linha ID: " << linha.first << " - " << linha.second.GetNome() << std::endl
        << "Local: " << linha.second.GetLocal() << std::endl
        << "Descricao: " << linha.second.GetDesc() << std::endl;
    }
}

void Sistema::AdicionarUsuario(std::string login, std::string senha, Cargo cargo) {
     Usuario user(login, senha, cargo);

    this->_Usuarios.push_back(user);

    std::cout << "Usuario " << login << " adicionado." << std::endl;
}

void Sistema::RemoverUsuario(std::string login) {

    if (this->_Usuarios.size() < 1){
        return;
    }

    for (size_t i = 0; i < this->_Usuarios.size(); i++){
        if (this->_Usuarios[i].GetLogin() == login){
            this->_Usuarios.erase(this->_Usuarios.begin() + i);
            std::cout << "Usuario " << login << " removido." << std::endl;

            return;
        }
    }
    std::cout << "Nenhum usuario removido." << std::endl;
}

int Sistema::ProximoIdDisponivel() const {
    return this->_ProximoId;
}

bool Sistema::IdAtivo(int Id) const {
    return this->_Linhas.count(Id) > 0;
}

bool Sistema::Login(std::string login, std::string senha) {

    for (size_t i = 0; i < this->_Usuarios.size(); i++){
        if (this->_Usuarios[i].GetLogin() == login && this->_Usuarios[i].ValidarSenha(senha) == true){
            this->_UsuarioLogadoIdx = static_cast<int>(i);

            std::cout << "Usuario " << login << " logado." << std::endl;

            return true;
        }
    }
    std::cout << "Usuario " << login << " nao encontrado." << std::endl;
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

namespace {

std::string cargoParaTexto(Cargo c) {
    switch (c) {
        case Cargo::ADMIN:      return "ADMIN";
        case Cargo::ENGENHEIRO: return "ENGENHEIRO";
        case Cargo::TECNICO:    return "TECNICO";
    }
    return "TECNICO";
}

Cargo textoParaCargo(const std::string& s) {
    if (s == "ADMIN")      return Cargo::ADMIN;
    if (s == "ENGENHEIRO") return Cargo::ENGENHEIRO;
    return Cargo::TECNICO;
}

// Divide uma linha por separador, preservando campos vazios (inclusive finais).
std::vector<std::string> dividir(const std::string& linha, char sep) {
    std::vector<std::string> campos;
    std::string atual;
    std::istringstream iss(linha);
    while (std::getline(iss, atual, sep)) {
        campos.push_back(atual);
    }
    return campos;
}

} // namespace

bool Sistema::SalvarAlteracoes() {
    std::ofstream ofs(this->_arquivoSave);
    if (!ofs.is_open()) {
        return false;
    }

    for (const auto& u : this->_Usuarios) {
        ofs << "USUARIO;" << u.GetLogin() << ';' << u.GetSenha() << ';'
            << cargoParaTexto(u.GetCargo()) << '\n';
    }

    for (const auto& linhaPar : this->_Linhas) {
        int lid = linhaPar.first;
        const LinhaDeProducao& linha = linhaPar.second;
        ofs << "LINHA;" << lid << ';' << linha.GetNome() << ';'
            << linha.GetLocal() << ';' << linha.GetDesc() << '\n';

        for (const auto& conjPar : linha.GetConjuntos()) {
            int cid = conjPar.first;
            const Conjunto& conj = conjPar.second;
            ofs << "CONJUNTO;" << lid << ';' << cid << ';'
                << conj.GetNome() << ';' << conj.GetDesc() << '\n';

            for (const auto& equipPar : conj.GetEquipamentos()) {
                int eid = equipPar.first;
                const Equipamento& eq = *equipPar.second;
                ofs << "EQUIP;" << lid << ';' << cid << ';' << eid << ';'
                    << eq.GetDesc() << ';' << eq.GetNome() << '\n';

                for (const auto& paramPar : eq.GetParametros()) {
                    const Parametro& p = paramPar.second;
                    ofs << "PARAM;" << lid << ';' << cid << ';' << eid << ';'
                        << paramPar.first << ';' << p.GetValorAtual() << ';'
                        << p.GetMin() << ';' << p.GetMax() << ';'
                        << p.GetDesc() << '\n';
                }
            }
        }
    }

    return ofs.good();
}

bool Sistema::CarregarUltimoSave() {
    return this->CarregarSave(this->_arquivoSave);
}

bool Sistema::CarregarSave(std::string arquivo) {
    std::ifstream ifs(arquivo);
    if (!ifs.is_open()) {
        return false;
    }

    // Substitui o estado atual pelo conteúdo do arquivo.
    this->_Linhas.clear();
    this->_Usuarios.clear();
    this->_ProximoId = 1;
    this->_UsuarioLogadoIdx = -1;

    try {
        std::string linha;
        while (std::getline(ifs, linha)) {
            if (linha.empty()) {
                continue;
            }
            std::vector<std::string> t = dividir(linha, ';');

            if (t[0] == "USUARIO" && t.size() >= 4) {
                this->AdicionarUsuario(t[1], t[2], textoParaCargo(t[3]));
            } else if (t[0] == "LINHA" && t.size() >= 5) {
                this->AdicionarLinha(std::stoi(t[1]), t[4], t[3], t[2]);
            } else if (t[0] == "CONJUNTO" && t.size() >= 5) {
                this->AcessarLinha(std::stoi(t[1]))
                    .AdicionarConjunto(std::stoi(t[2]), t[3], t[4]);
            } else if (t[0] == "EQUIP" && t.size() >= 6) {
                int lid = std::stoi(t[1]);
                int cid = std::stoi(t[2]);
                int eid = std::stoi(t[3]);
                auto eq = std::make_unique<Equipamento>(eid, t[4], t[5]);
                this->AcessarLinha(lid).AcessarConjunto(cid)
                    .AdicionarEquipamento(std::move(eq));
            } else if (t[0] == "PARAM" && t.size() >= 9) {
                int lid = std::stoi(t[1]);
                int cid = std::stoi(t[2]);
                int eid = std::stoi(t[3]);
                int pid = std::stoi(t[4]);
                double valor = std::stod(t[5]);
                double minimo = std::stod(t[6]);
                double maximo = std::stod(t[7]);
                this->AcessarLinha(lid).AcessarConjunto(cid)
                    .AcessarEquipamento(eid)
                    .AdicionarParametro(valor, maximo, minimo, t[8], pid);
            }
        }
    } catch (const std::exception&) {
        return false;
    }

    return true;
}
