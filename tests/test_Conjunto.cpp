#include "doctest.h"
#include "Conjunto.hpp"
#include "Equipamento.hpp"
#include "Excecoes.hpp"

#include <iostream>
#include <sstream>
#include <memory>

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

TEST_CASE("Conjunto - GetId retorna id correto") {
    Conjunto c(1, "Conjunto A", "Conjunto A");
    CHECK(c.GetId() == 1);
}

TEST_CASE("Conjunto - GetDesc retorna descricao correta") {
    Conjunto c(2, "Conjunto B", "Linha Principal");
    CHECK(c.GetDesc() == "Linha Principal");
}

TEST_CASE("Conjunto - QuantidadeEquipamentos inicia em zero") {
    Conjunto c(3, "Setor B", "Setor B");
    CHECK(c.QuantidadeEquipamentos() == 0);
}

TEST_CASE("Conjunto - AdicionarEquipamento incrementa quantidade") {
    Conjunto c(4, "Setor C", "Setor C");
    c.AdicionarEquipamento(1, "Motor");
    CHECK(c.QuantidadeEquipamentos() == 1);
}

TEST_CASE("Conjunto - AdicionarEquipamento multiplos") {
    Conjunto c(5, "Setor D", "Setor D");
    c.AdicionarEquipamento(1, "Motor");
    c.AdicionarEquipamento(2, "Bomba");
    CHECK(c.QuantidadeEquipamentos() == 2);
}

TEST_CASE("Conjunto - RemoverEquipamento decrementa quantidade") {
    Conjunto c(6, "Setor E", "Setor E");
    c.AdicionarEquipamento(1, "Motor");
    c.RemoverEquipamento(1);
    CHECK(c.QuantidadeEquipamentos() == 0);
}

TEST_CASE("Conjunto - SetNome atualiza nome") {
    Conjunto c(7, "Nome", "Desc");
    c.SetNome("ConjuntoAlfa");
    CHECK(c.GetNome() == "ConjuntoAlfa");
}

TEST_CASE("Conjunto - SetDesc atualiza descricao") {
    Conjunto c(8, "Nome", "Antiga");
    c.SetDesc("Nova");
    CHECK(c.GetDesc() == "Nova");
}

TEST_CASE("Conjunto - DiagnosticarConjunto vazio sem falhas") {
    Conjunto c(9, "Setor F", "Setor F");
    std::vector<int> falhas = c.DiagnosticarConjunto();
    CHECK(falhas.empty() == true);
}

TEST_CASE("Conjunto - GetEquipamentos retorna vetor correto") {
    Conjunto c(10, "Setor G", "Setor G");
    c.AdicionarEquipamento(1, "Reator");
    CHECK(c.GetEquipamentos().size() == 1);
}

TEST_CASE("Conjunto - construtor rejeita id negativo") {
    CHECK_THROWS_AS(Conjunto(-1, "n", "d"), IdInvalido);
}

TEST_CASE("Conjunto - construtor rejeita descricao vazia") {
    CHECK_THROWS_AS(Conjunto(1, "n", ""), EntradaInvalida);
}

TEST_CASE("Conjunto - AdicionarEquipamento(unique_ptr) rejeita nullptr") {
    Conjunto c(11, "n", "d");
    CHECK_THROWS_AS(c.AdicionarEquipamento(std::unique_ptr<Equipamento>(nullptr)),
                    EntradaInvalida);
}

TEST_CASE("Conjunto - AdicionarEquipamento(unique_ptr) rejeita duplicado") {
    Conjunto c(12, "n", "d");
    c.AdicionarEquipamento(1, "eq");
    auto novo = std::make_unique<Equipamento>(1, "outro", "outro");
    CHECK_THROWS_AS(c.AdicionarEquipamento(std::move(novo)), IdDuplicado);
}

TEST_CASE("Conjunto - AdicionarEquipamento(int,desc) rejeita duplicado") {
    Conjunto c(13, "n", "d");
    c.AdicionarEquipamento(1, "eq");
    CHECK_THROWS_AS(c.AdicionarEquipamento(1, "eq2"), IdDuplicado);
}

TEST_CASE("Conjunto - ProximoIdEquipamento avanca a cada insercao") {
    Conjunto c(14, "n", "d");
    CHECK(c.ProximoIdEquipamento() == 1);
    c.AdicionarEquipamento(1, "eq");
    CHECK(c.ProximoIdEquipamento() == 2);
    c.AdicionarEquipamento(std::make_unique<Equipamento>(5, "eq", "eq"));
    CHECK(c.ProximoIdEquipamento() == 6);
}

TEST_CASE("Conjunto - RemoverEquipamento inexistente lanca") {
    Conjunto c(15, "n", "d");
    CHECK_THROWS_AS(c.RemoverEquipamento(99), IdInexistente);
}

TEST_CASE("Conjunto - SetDesc rejeita vazia") {
    Conjunto c(16, "n", "d");
    CHECK_THROWS_AS(c.SetDesc(""), EntradaInvalida);
}

TEST_CASE("Conjunto - AcessarEquipamento OK e erro") {
    Conjunto c(17, "n", "d");
    c.AdicionarEquipamento(1, "eq");
    CHECK(c.AcessarEquipamento(1).GetId() == 1);
    CHECK_THROWS_AS(c.AcessarEquipamento(99), IdInexistente);
}

TEST_CASE("Conjunto - ExibirEquipamentos vazio mostra mensagem") {
    Conjunto c(18, "n", "d");
    std::string s = capturaSaida([&]{ c.ExibirEquipamentos(); });
    CHECK(s.find("Nenhum") != std::string::npos);
}

TEST_CASE("Conjunto - ExibirEquipamentos com itens lista nome") {
    Conjunto c(19, "Bloco", "d");
    c.AdicionarEquipamento(1, "eq");
    std::string s = capturaSaida([&]{ c.ExibirEquipamentos(); });
    CHECK(s.find("Bloco") != std::string::npos);
}

TEST_CASE("Conjunto - ExibirAlarmes vazio e cheio") {
    Conjunto c1(20, "n", "d");
    std::string s1 = capturaSaida([&]{ c1.ExibirAlarmes(); });
    CHECK(s1.find("Nenhum") != std::string::npos);

    Conjunto c2(21, "n", "d");
    c2.AdicionarEquipamento(1, "eq");
    capturaSaida([&]{ c2.ExibirAlarmes(); });
}

TEST_CASE("Conjunto - ExibirTudo executa") {
    Conjunto c(22, "n", "d");
    c.AdicionarEquipamento(1, "eq");
    capturaSaida([&]{ c.ExibirTudo(); });
}

TEST_CASE("Conjunto - QuantidadeAlarmes soma equipamentos") {
    Conjunto c(23, "n", "d");
    c.AdicionarEquipamento(1, "eq");
    c.AcessarEquipamento(1).AdicionarParametro(15.0, 10.0, 0.0, "P", 1);
    c.AtualizarAlarmes();
    CHECK(c.QuantidadeAlarmes() == 1);
}

TEST_CASE("Conjunto - GetEquipamentos const ref") {
    Conjunto c(24, "n", "d");
    c.AdicionarEquipamento(1, "eq");
    const auto& m = c.GetEquipamentos();
    CHECK(m.size() == 1);
}
