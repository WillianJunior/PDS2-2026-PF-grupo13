#include "doctest.h"
#include "Sistema.hpp"
#include "Cargo.hpp"
#include "Excecoes.hpp"

#include <iostream>
#include <sstream>
#include <cstdio>

namespace {
template <typename F>
std::string capturaSaida(F&& f) {
    std::stringstream buf;
    auto* old = std::cout.rdbuf(buf.rdbuf());
    f();
    std::cout.rdbuf(old);
    return buf.str();
}
}

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

TEST_CASE("Sistema - AcessarLinha inexistente lanca") {
    Sistema s;
    CHECK_THROWS_AS(s.AcessarLinha(99), IdInexistente);
}

TEST_CASE("Sistema - RemoverLinha inexistente lanca") {
    Sistema s;
    CHECK_THROWS_AS(s.RemoverLinha(99), IdInexistente);
}

TEST_CASE("Sistema - AdicionarLinha duplicada lanca") {
    Sistema s;
    s.AdicionarLinha(1, "d", "l", "n");
    CHECK_THROWS_AS(s.AdicionarLinha(1, "d", "l", "n"), IdDuplicado);
}

TEST_CASE("Sistema - AdicionarLinha auto-id retorna id assignado") {
    Sistema s;
    int a = s.AdicionarLinha("d", "l", "n");
    int b = s.AdicionarLinha("d", "l", "n");
    CHECK(a == 1);
    CHECK(b == 2);
}

TEST_CASE("Sistema - ExibirLinhas com linha cadastrada executa") {
    Sistema s;
    s.AdicionarLinha(1, "Desc", "Local", "L");
    std::string out = capturaSaida([&]{ s.ExibirLinhas(); });
    CHECK(out.find("Linha") != std::string::npos);
}

TEST_CASE("Sistema - RemoverUsuario sem usuarios e silencioso") {
    Sistema s;
    s.RemoverUsuario("ninguem");
    CHECK(true);
}

TEST_CASE("Sistema - RemoverUsuario inexistente quando ha outros") {
    Sistema s;
    s.AdicionarUsuario("a", "p", Cargo::ADMIN);
    s.RemoverUsuario("inexistente");
    CHECK(s.Login("a", "p") == true);
}

TEST_CASE("Sistema - persistencia round-trip") {
    std::remove("dados/save.txt");
    {
        Sistema s;
        s.AdicionarUsuario("u", "p", Cargo::ADMIN);
        int lid = s.AdicionarLinha("d", "l", "n");
        s.AcessarLinha(lid).AdicionarConjunto("c", "cd");
        s.AcessarLinha(lid).AcessarConjunto(1).AdicionarEquipamento(1, "eq");
        s.AcessarLinha(lid).AcessarConjunto(1).AcessarEquipamento(1)
            .AdicionarParametro(1.0, 10.0, 0.0, "P", 1);
        REQUIRE(s.SalvarAlteracoes());
    }
    Sistema s2;
    REQUIRE(s2.CarregarUltimoSave());
    CHECK(s2.GetLinhas().size() == 1);
    CHECK(s2.Login("u", "p") == true);
    std::remove("dados/save.txt");
}

TEST_CASE("Sistema - CarregarSave arquivo inexistente retorna false") {
    Sistema s;
    CHECK(s.CarregarSave("arquivo_que_nao_existe_xyz.txt") == false);
}
