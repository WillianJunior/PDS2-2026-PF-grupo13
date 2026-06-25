#include "doctest.h"
#include "Equipamento.hpp"
#include "Excecoes.hpp"

#include <iostream>
#include <sstream>

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

TEST_CASE("Equipamento - GetId retorna id correto") {
    Equipamento e(1, "Motor A", "Motor A");
    CHECK(e.GetId() == 1);
}

TEST_CASE("Equipamento - QuantidadeParametros inicia em zero") {
    Equipamento e(2, "Bomba", "Bomba");
    CHECK(e.QuantidadeParametros() == 0);
}

TEST_CASE("Equipamento - AdicionarParametro incrementa quantidade") {
    Equipamento e(3, "Compressor", "Compressor");
    e.AdicionarParametro(10.0, "Temperatura", 1);
    CHECK(e.QuantidadeParametros() == 1);
}

TEST_CASE("Equipamento - AdicionarParametro multiplos") {
    Equipamento e(4, "Turbina", "Turbina");
    e.AdicionarParametro(10.0, "Temperatura", 1);
    e.AdicionarParametro(5.0, "Pressao", 2);
    CHECK(e.QuantidadeParametros() == 2);
}

TEST_CASE("Equipamento - RemoverParametro decrementa quantidade") {
    Equipamento e(5, "Valvula", "Valvula");
    e.AdicionarParametro(10.0, "Temp", 1);
    e.RemoverParametro(1);
    CHECK(e.QuantidadeParametros() == 0);
}

TEST_CASE("Equipamento - AdicionarParametroComLimites incrementa quantidade") {
    Equipamento e(6, "Sensor", "Sensor");
    e.AdicionarParametro(5.0, 10.0, 0.0, "Nivel", 1);
    CHECK(e.QuantidadeParametros() == 1);
}

TEST_CASE("Equipamento - DiagnosticarEquipamento vazio quando sem falhas") {
    Equipamento e(7, "Reator", "Reator");
    e.AdicionarParametro(5.0, 10.0, 0.0, "Temp", 1);
    std::vector<int> falhas = e.DiagnosticarEquipamento();
    CHECK(falhas.empty() == true);
}

TEST_CASE("Equipamento - GetParametros retorna vetor correto") {
    Equipamento e(8, "Eixo", "Eixo");
    e.AdicionarParametro(1.0, "Velocidade", 10);
    CHECK(e.GetParametros().size() == 1);
}

TEST_CASE("Equipamento - QuantidadeAlarmes inicia em zero") {
    Equipamento e(9, "CLP", "CLP");
    CHECK(e.QuantidadeAlarmes() == 0);
}

TEST_CASE("Equipamento - construtor rejeita id negativo") {
    CHECK_THROWS_AS(Equipamento(-1, "d", "n"), IdInvalido);
}

TEST_CASE("Equipamento - AdicionarParametro 2-arg auto-id retorna ids monotonicos") {
    Equipamento e(10, "d", "n");
    int a = e.AdicionarParametro(1.0, "P1");
    int b = e.AdicionarParametro(2.0, "P2");
    CHECK(a == 1);
    CHECK(b == 2);
    CHECK(e.ProximoIdParametro() == 3);
}

TEST_CASE("Equipamento - AdicionarParametro 4-arg auto-id retorna ids monotonicos") {
    Equipamento e(11, "d", "n");
    int a = e.AdicionarParametro(1.0, 10.0, 0.0, "P1");
    int b = e.AdicionarParametro(2.0, 10.0, 0.0, "P2");
    CHECK(a == 1);
    CHECK(b == 2);
}

TEST_CASE("Equipamento - AdicionarParametro 4-arg explicito rejeita duplicado") {
    Equipamento e(12, "d", "n");
    e.AdicionarParametro(1.0, 10.0, 0.0, "P", 5);
    CHECK_THROWS_AS(e.AdicionarParametro(2.0, 10.0, 0.0, "P", 5), IdDuplicado);
}

TEST_CASE("Equipamento - AdicionarParametro 3-arg rejeita duplicado") {
    Equipamento e(13, "d", "n");
    e.AdicionarParametro(1.0, "P", 1);
    CHECK_THROWS_AS(e.AdicionarParametro(2.0, "P", 1), IdDuplicado);
}

TEST_CASE("Equipamento - RemoverParametro inexistente lanca") {
    Equipamento e(14, "d", "n");
    CHECK_THROWS_AS(e.RemoverParametro(99), IdInexistente);
}

TEST_CASE("Equipamento - AtualizarAlarmes sincroniza vetor de alarmes") {
    Equipamento e(15, "d", "n");
    e.AdicionarParametro(15.0, 10.0, 0.0, "P", 1);
    e.AtualizarAlarmes();
    CHECK(e.QuantidadeAlarmes() == 1);
    CHECK(e.GetAlarmes().size() == 1);
}

TEST_CASE("Equipamento - ExibirParametros executa") {
    Equipamento e(16, "d", "n");
    e.AdicionarParametro(1.0, "P", 1);
    std::string s = capturaSaida([&]{ e.ExibirParametros(); });
    CHECK(!s.empty());
}

TEST_CASE("Equipamento - ExibirAlarmes executa") {
    Equipamento e(17, "d", "n");
    e.AdicionarParametro(1.0, 10.0, 0.0, "P", 1);
    e.AtualizarAlarmes();
    std::string s = capturaSaida([&]{ e.ExibirAlarmes(); });
    CHECK(!s.empty());
}

TEST_CASE("Equipamento - SetDesc atualiza descricao") {
    Equipamento e(18, "d", "n");
    e.SetDesc("nova");
    CHECK(e.GetDesc() == "nova");
}

TEST_CASE("Equipamento - Tipo base retorna 'Equipamento'") {
    Equipamento e(19, "d", "n");
    CHECK(e.Tipo() == "Equipamento");
}
