#include "doctest.h"
#include "LinhaDeProducao.hpp"

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
