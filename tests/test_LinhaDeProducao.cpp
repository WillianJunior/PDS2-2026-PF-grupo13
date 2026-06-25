#include "doctest.h"
#include "LinhaDeProducao.hpp"
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

TEST_CASE("LinhaDeProducao - GetId retorna id correto") {
    LinhaDeProducao l(1, "Desc", "Local", "Linha1");
    CHECK(l.GetId() == 1);
}

TEST_CASE("LinhaDeProducao - GetNome retorna nome correto") {
    LinhaDeProducao l(2, "Desc", "Bloco A", "LinhaAlfa");
    CHECK(l.GetNome() == "LinhaAlfa");
}

TEST_CASE("LinhaDeProducao - GetLocal retorna local correto") {
    LinhaDeProducao l(3, "Desc", "Bloco B", "LinhaBeta");
    CHECK(l.GetLocal() == "Bloco B");
}

TEST_CASE("LinhaDeProducao - GetDesc retorna descricao correta") {
    LinhaDeProducao l(4, "Producao principal", "Bloco C", "LinhaGama");
    CHECK(l.GetDesc() == "Producao principal");
}

TEST_CASE("LinhaDeProducao - QuantidadeConjuntos inicia em zero") {
    LinhaDeProducao l(5, "Desc", "Local", "Linha5");
    CHECK(l.QuantidadeConjuntos() == 0);
}

TEST_CASE("LinhaDeProducao - AdicionarConjunto incrementa quantidade") {
    LinhaDeProducao l(6, "Desc", "Local", "Linha6");
    l.AdicionarConjunto(1, "Conjunto 1", "Desc");
    CHECK(l.QuantidadeConjuntos() == 1);
}

TEST_CASE("LinhaDeProducao - AdicionarConjunto multiplos") {
    LinhaDeProducao l(7, "Desc", "Local", "Linha7");
    l.AdicionarConjunto(1, "C1", "Desc");
    l.AdicionarConjunto(2, "C2", "Desc");
    CHECK(l.QuantidadeConjuntos() == 2);
}

TEST_CASE("LinhaDeProducao - RemoverConjunto decrementa quantidade") {
    LinhaDeProducao l(8, "Desc", "Local", "Linha8");
    l.AdicionarConjunto(1, "C1", "Desc");
    l.RemoverConjunto(1);
    CHECK(l.QuantidadeConjuntos() == 0);
}

TEST_CASE("LinhaDeProducao - SetNome atualiza nome") {
    LinhaDeProducao l(9, "Desc", "Local", "Antiga");
    l.SetNome("Nova");
    CHECK(l.GetNome() == "Nova");
}

TEST_CASE("LinhaDeProducao - DiagnosticarLinha vazio sem falhas") {
    LinhaDeProducao l(10, "Desc", "Local", "Linha10");
    std::vector<int> falhas = l.DiagnosticarLinha();
    CHECK(falhas.empty() == true);
}

TEST_CASE("LinhaDeProducao - GetConjuntos retorna vetor correto") {
    LinhaDeProducao l(11, "Desc", "Local", "Linha11");
    l.AdicionarConjunto(1, "C1", "Desc");
    CHECK(l.GetConjuntos().size() == 1);
}

TEST_CASE("LinhaDeProducao - construtor rejeita id negativo") {
    CHECK_THROWS_AS(LinhaDeProducao(-1, "d", "l", "n"), IdInvalido);
}

TEST_CASE("LinhaDeProducao - construtor rejeita descricao vazia") {
    CHECK_THROWS_AS(LinhaDeProducao(1, "", "l", "n"), EntradaInvalida);
}

TEST_CASE("LinhaDeProducao - AdicionarConjunto auto-id retorna ids monotonicos") {
    LinhaDeProducao l(20, "d", "l", "n");
    int a = l.AdicionarConjunto("C1", "d");
    int b = l.AdicionarConjunto("C2", "d");
    CHECK(a == 1);
    CHECK(b == 2);
    CHECK(l.ProximoIdConjunto() == 3);
}

TEST_CASE("LinhaDeProducao - AdicionarConjunto explicito avanca ProximoId") {
    LinhaDeProducao l(21, "d", "l", "n");
    l.AdicionarConjunto(10, "C", "d");
    CHECK(l.ProximoIdConjunto() == 11);
}

TEST_CASE("LinhaDeProducao - RemoverConjunto inexistente lanca") {
    LinhaDeProducao l(22, "d", "l", "n");
    CHECK_THROWS_AS(l.RemoverConjunto(99), IdInexistente);
}

TEST_CASE("LinhaDeProducao - AcessarConjunto inexistente lanca") {
    LinhaDeProducao l(23, "d", "l", "n");
    CHECK_THROWS_AS(l.AcessarConjunto(99), IdInexistente);
}

TEST_CASE("LinhaDeProducao - AcessarConjunto retorna referencia mutavel") {
    LinhaDeProducao l(24, "d", "l", "n");
    int cid = l.AdicionarConjunto("C", "d");
    Conjunto& c = l.AcessarConjunto(cid);
    CHECK(c.GetNome() == "C");
}

TEST_CASE("LinhaDeProducao - ExibirConjuntos / ExibirAlarmes / ExibirTudo executam") {
    LinhaDeProducao l(25, "d", "l", "n");
    int cid = l.AdicionarConjunto("C", "d");
    l.AcessarConjunto(cid).AdicionarEquipamento(1, "eq");
    std::string s1 = capturaSaida([&]{ l.ExibirConjuntos(); });
    std::string s2 = capturaSaida([&]{ l.ExibirAlarmes(); });
    std::string s3 = capturaSaida([&]{ l.ExibirTudo(); });
    CHECK(!s1.empty());
    CHECK(!s3.empty());
    (void)s2;
}

TEST_CASE("LinhaDeProducao - QuantidadeAlarmes soma conjuntos") {
    LinhaDeProducao l(26, "d", "l", "n");
    int cid = l.AdicionarConjunto("C", "d");
    Conjunto& c = l.AcessarConjunto(cid);
    c.AdicionarEquipamento(1, "eq");
    c.AcessarEquipamento(1).AdicionarParametro(15.0, 10.0, 0.0, "P", 1);
    l.AtualizarAlarmes();
    CHECK(l.QuantidadeAlarmes() == 1);
}

TEST_CASE("LinhaDeProducao - SetDesc atualiza descricao") {
    LinhaDeProducao l(27, "d", "l", "n");
    l.SetDesc("nova");
    CHECK(l.GetDesc() == "nova");
}

TEST_CASE("LinhaDeProducao - SetLocal atualiza local") {
    LinhaDeProducao l(28, "d", "l", "n");
    l.SetLocal("Bloco Z");
    CHECK(l.GetLocal() == "Bloco Z");
}

TEST_CASE("LinhaDeProducao - DiagnosticarLinha reporta parametro fora de faixa") {
    LinhaDeProducao l(29, "d", "l", "n");
    int cid = l.AdicionarConjunto("C", "d");
    Conjunto& c = l.AcessarConjunto(cid);
    c.AdicionarEquipamento(1, "eq");
    c.AcessarEquipamento(1).AdicionarParametro(99.0, 10.0, 0.0, "P", 1);
    std::vector<int> falhas = l.DiagnosticarLinha();
    CHECK(falhas.size() == 1);
}
