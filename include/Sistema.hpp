#ifndef SISTEMA_HPP
#define SISTEMA_HPP

#include <vector>
#include <string>

#include "LinhaDeProducao.hpp"
#include "Usuario.hpp"
#include "Cargo.hpp"

class Sistema {
private:
    std::vector<LinhaDeProducao> _Linhas;
    std::vector<Usuario> _Usuarios;
    std::vector<int> _IdsUtilizados;

    Usuario* _UsuarioLogado;

    void AdicionarId (int Id);
    void RemoverId (int Id);
public:
    Sistema();

    void AdicionarLinha (int id, std::string desc, std::string local, std::string nome);
    void RemoverLinha (int id);
    const std::vector<LinhaDeProducao>& GetLinhas() const;
    void ExibirLinhas ();

    void AdicionarUsuario(std::string login, std::string senha, Cargo cargo);
    void RemoverUsuario(std::string login);

    int ProximoIdDisponivel () const;
    bool IdDisponivel (int Id) const;

    bool Login (std::string login, std::string senha);
    bool Logout ();
    Usuario* GetUsuarioLogado() const;

    bool SalvarAlteracoes ();
    bool CarregarUltimoSave ();
    bool CarregarSave (std::string arquivo);
};

#endif