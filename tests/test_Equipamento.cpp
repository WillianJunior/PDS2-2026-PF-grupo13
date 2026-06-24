#include "doctest.h"
#include "Equipamento.hpp"

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
