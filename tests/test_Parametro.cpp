#include "doctest.h"
#include "Parametro.hpp"

TEST_CASE("Parametro - construtor simples armazena valor inicial") {
    Parametro p(10.0, "Temperatura", 1);
    CHECK(p.GetValorAtual() == doctest::Approx(10.0));
}

TEST_CASE("Parametro - construtor com limites armazena max e min") {
    Parametro p(5.0, 20.0, 0.0, "Pressao", 2);
    CHECK(p.GetMax() == doctest::Approx(20.0));
    CHECK(p.GetMin() == doctest::Approx(0.0));
}

TEST_CASE("Parametro - GetDesc retorna descricao correta") {
    Parametro p(1.0, "Velocidade", 3);
    CHECK(p.GetDesc() == "Velocidade");
}

TEST_CASE("Parametro - GetId retorna id correto") {
    Parametro p(0.0, "Tensao", 42);
    CHECK(p.GetId() == 42);
}

TEST_CASE("Parametro - SetValorAtual atualiza valor") {
    Parametro p(0.0, "Corrente", 5);
    p.SetValorAtual(15.0);
    CHECK(p.GetValorAtual() == doctest::Approx(15.0));
}

TEST_CASE("Parametro - SetValorAtual adiciona ao historico") {
    Parametro p(0.0, "Fluxo", 6);
    p.SetValorAtual(1.0);
    p.SetValorAtual(2.0);
    CHECK(p.GetHist().size() >= 2);
}

TEST_CASE("Parametro - ValorValido dentro dos limites retorna true") {
    Parametro p(5.0, 10.0, 0.0, "Nivel", 7);
    CHECK(p.ValorValido(5.0) == true);
}

TEST_CASE("Parametro - ValorValido acima do maximo retorna false") {
    Parametro p(5.0, 10.0, 0.0, "Nivel", 8);
    CHECK(p.ValorValido(15.0) == false);
}

TEST_CASE("Parametro - DiagnosticarParametro retorna false quando dentro dos limites") {
    Parametro p(5.0, 10.0, 0.0, "Rotacao", 9);
    CHECK(p.DiagnosticarParametro() == false);
}

TEST_CASE("Parametro - DiagnosticarParametro retorna true quando fora dos limites") {
    Parametro p(15.0, 10.0, 0.0, "Rotacao", 10);
    CHECK(p.DiagnosticarParametro() == true);
}

TEST_CASE("Parametro - GetEstado reflete diagnostico") {
    Parametro p(15.0, 10.0, 0.0, "Vibr", 11);
    p.DiagnosticarParametro();
    CHECK(p.GetEstado() == true);
}

TEST_CASE("Parametro - ResetarLimites remove restricoes") {
    Parametro p(5.0, 10.0, 0.0, "Temp", 12);
    p.ResetarLimites();
    CHECK(p.ValorValido(999.0) == true);
}

TEST_CASE("Parametro - ResetarHistorico limpa vetor") {
    Parametro p(0.0, "Pressao", 13);
    p.SetValorAtual(1.0);
    p.SetValorAtual(2.0);
    p.ResetarHistorico();
    CHECK(p.GetHist().empty() == true);
}

TEST_CASE("Parametro - SetDesc atualiza descricao") {
    Parametro p(0.0, "Antiga", 14);
    p.SetDesc("Nova");
    CHECK(p.GetDesc() == "Nova");
}
