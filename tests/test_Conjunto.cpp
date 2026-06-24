#include "doctest.h"
#include "Conjunto.hpp"

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
