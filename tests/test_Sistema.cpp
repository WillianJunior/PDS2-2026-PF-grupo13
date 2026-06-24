#include "doctest.h"
#include "Sistema.hpp"
#include "Cargo.hpp"

TEST_CASE("Sistema - inicia sem linhas") {
    Sistema s;
    CHECK(s.GetLinhas().empty() == true);
}

TEST_CASE("Sistema - inicia sem usuario logado") {
    Sistema s;
    CHECK(s.GetUsuarioLogado() == nullptr);
}

TEST_CASE("Sistema - AdicionarLinha incrementa lista") {
    Sistema s;
    s.AdicionarLinha(1, "Desc", "Local", "Linha1");
    CHECK(s.GetLinhas().size() == 1);
}

TEST_CASE("Sistema - RemoverLinha decrementa lista") {
    Sistema s;
    s.AdicionarLinha(1, "Desc", "Local", "Linha1");
    s.RemoverLinha(1);
    CHECK(s.GetLinhas().empty() == true);
}

TEST_CASE("Sistema - Login com credenciais corretas retorna true") {
    Sistema s;
    s.AdicionarUsuario("admin", "senha123", Cargo::ADMIN);
    CHECK(s.Login("admin", "senha123") == true);
}

TEST_CASE("Sistema - Login com senha errada retorna false") {
    Sistema s;
    s.AdicionarUsuario("admin", "senha123", Cargo::ADMIN);
    CHECK(s.Login("admin", "senhaerrada") == false);
}

TEST_CASE("Sistema - Login com usuario inexistente retorna false") {
    Sistema s;
    CHECK(s.Login("naoexiste", "qualquer") == false);
}

TEST_CASE("Sistema - GetUsuarioLogado retorna usuario apos login") {
    Sistema s;
    s.AdicionarUsuario("eng01", "pass", Cargo::ENGENHEIRO);
    s.Login("eng01", "pass");
    CHECK(s.GetUsuarioLogado() != nullptr);
}

TEST_CASE("Sistema - Logout retorna true quando ha sessao ativa") {
    Sistema s;
    s.AdicionarUsuario("tec01", "pass", Cargo::TECNICO);
    s.Login("tec01", "pass");
    CHECK(s.Logout() == true);
}

TEST_CASE("Sistema - Logout retorna false sem sessao ativa") {
    Sistema s;
    CHECK(s.Logout() == false);
}

TEST_CASE("Sistema - IdAtivo retorna false para id nao usado") {
    Sistema s;
    CHECK(s.IdAtivo(99) == false);
}

TEST_CASE("Sistema - IdAtivo retorna true para id em uso") {
    Sistema s;
    s.AdicionarLinha(5, "Desc", "Local", "Linha");
    CHECK(s.IdAtivo(5) == true);
}

TEST_CASE("Sistema - ProximoIdDisponivel retorna 1 no inicio") {
    Sistema s;
    CHECK(s.ProximoIdDisponivel() == 1);
}

TEST_CASE("Sistema - AdicionarUsuario permite login posterior") {
    Sistema s;
    s.AdicionarUsuario("novouser", "novasenha", Cargo::TECNICO);
    CHECK(s.Login("novouser", "novasenha") == true);
}

TEST_CASE("Sistema - RemoverUsuario impede login posterior") {
    Sistema s;
    s.AdicionarUsuario("tempuser", "pass", Cargo::TECNICO);
    s.RemoverUsuario("tempuser");
    CHECK(s.Login("tempuser", "pass") == false);
}
