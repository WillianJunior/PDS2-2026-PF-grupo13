#include "doctest.h"
#include "Usuario.hpp"
#include "Cargo.hpp"

TEST_CASE("Usuario - GetLogin retorna login correto") {
    Usuario u("admin", "senha123", Cargo::ADMIN);
    CHECK(u.GetLogin() == "admin");
}

TEST_CASE("Usuario - ValidarSenha retorna true com senha correta") {
    Usuario u("eng01", "minhasenha", Cargo::ENGENHEIRO);
    CHECK(u.ValidarSenha("minhasenha") == true);
}

TEST_CASE("Usuario - ValidarSenha retorna false com senha errada") {
    Usuario u("tec01", "senha_certa", Cargo::TECNICO);
    CHECK(u.ValidarSenha("senha_errada") == false);
}

TEST_CASE("Usuario - ValidarSenha case-sensitive") {
    Usuario u("user1", "SenhaA", Cargo::TECNICO);
    CHECK(u.ValidarSenha("senhaa") == false);
}

TEST_CASE("Usuario - GetCargo retorna cargo ADMIN") {
    Usuario u("admin", "pass", Cargo::ADMIN);
    CHECK(u.GetCargo("admin") == Cargo::ADMIN);
}

TEST_CASE("Usuario - GetCargo retorna cargo ENGENHEIRO") {
    Usuario u("eng01", "pass", Cargo::ENGENHEIRO);
    CHECK(u.GetCargo("eng01") == Cargo::ENGENHEIRO);
}

TEST_CASE("Usuario - GetCargo retorna cargo TECNICO") {
    Usuario u("tec01", "pass", Cargo::TECNICO);
    CHECK(u.GetCargo("tec01") == Cargo::TECNICO);
}
