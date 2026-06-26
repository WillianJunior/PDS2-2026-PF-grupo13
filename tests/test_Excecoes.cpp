#include "doctest.h"

#include "Excecoes.hpp"
#include "Parametro.hpp"
#include "Equipamento.hpp"
#include "Conjunto.hpp"
#include "LinhaDeProducao.hpp"
#include "Sistema.hpp"
#include "Usuario.hpp"
#include "Cargo.hpp"
#include "Motor.hpp"
#include "Sensor.hpp"
#include "Valvula.hpp"
#include "Atuador.hpp"

#include <memory>

// ---------- Validação / exceções ----------

TEST_CASE("Parametro - Max < Min lanca LimitesInvalidos") {
    CHECK_THROWS_AS(Parametro(5.0, 0.0, 10.0, "Temp", 1), LimitesInvalidos);
}

TEST_CASE("Parametro - descricao vazia lanca EntradaInvalida") {
    CHECK_THROWS_AS(Parametro(5.0, "", 1), EntradaInvalida);
}

TEST_CASE("Parametro - id negativo lanca IdInvalido") {
    CHECK_THROWS_AS(Parametro(5.0, "Temp", -1), IdInvalido);
}

TEST_CASE("Parametro - leitura fora dos limites NAO lanca (caso de falha)") {
    CHECK_NOTHROW(Parametro(15.0, 10.0, 0.0, "Pressao", 1));
}

TEST_CASE("Parametro - SetMin maior que Max lanca LimitesInvalidos") {
    Parametro p(5.0, 10.0, 0.0, "Temp", 1);
    CHECK_THROWS_AS(p.SetMin(20.0), LimitesInvalidos);
}

TEST_CASE("Equipamento - id negativo lanca IdInvalido") {
    CHECK_THROWS_AS(Equipamento(-1, "Motor", "M"), IdInvalido);
}

TEST_CASE("Equipamento - descricao vazia lanca EntradaInvalida") {
    CHECK_THROWS_AS(Equipamento(1, "", "M"), EntradaInvalida);
}

TEST_CASE("Equipamento - parametro duplicado lanca IdDuplicado") {
    Equipamento e(1, "Motor", "M");
    e.AdicionarParametro(5.0, "Temp", 1);
    CHECK_THROWS_AS(e.AdicionarParametro(6.0, "Outra", 1), IdDuplicado);
}

TEST_CASE("Equipamento - remover parametro inexistente lanca IdInexistente") {
    Equipamento e(1, "Motor", "M");
    CHECK_THROWS_AS(e.RemoverParametro(99), IdInexistente);
}

TEST_CASE("Conjunto - equipamento duplicado lanca IdDuplicado") {
    Conjunto c(1, "Nome", "Desc");
    c.AdicionarEquipamento(1, "Motor");
    CHECK_THROWS_AS(c.AdicionarEquipamento(1, "Bomba"), IdDuplicado);
}

TEST_CASE("Conjunto - acessar equipamento inexistente lanca IdInexistente") {
    Conjunto c(1, "Nome", "Desc");
    CHECK_THROWS_AS(c.AcessarEquipamento(42), IdInexistente);
}

TEST_CASE("LinhaDeProducao - conjunto duplicado lanca IdDuplicado") {
    LinhaDeProducao l(1, "Desc", "Local", "Nome");
    l.AdicionarConjunto(1, "C1", "D1");
    CHECK_THROWS_AS(l.AdicionarConjunto(1, "C2", "D2"), IdDuplicado);
}

TEST_CASE("Usuario - login vazio lanca EntradaInvalida") {
    CHECK_THROWS_AS(Usuario("", "senha", Cargo::ADMIN), EntradaInvalida);
}

TEST_CASE("Sistema - linha duplicada lanca IdDuplicado") {
    Sistema s;
    s.AdicionarLinha(1, "Desc", "Local", "Nome");
    CHECK_THROWS_AS(s.AdicionarLinha(1, "Outra", "Local", "Nome"), IdDuplicado);
}

TEST_CASE("Sistema - remover linha inexistente lanca IdInexistente") {
    Sistema s;
    CHECK_THROWS_AS(s.RemoverLinha(99), IdInexistente);
}

TEST_CASE("Excecoes - derivadas capturaveis como ExcecaoSistema") {
    CHECK_THROWS_AS(Parametro(5.0, 0.0, 10.0, "Temp", 1), ExcecaoSistema);
}

// ---------- Polimorfismo via unique_ptr ----------

TEST_CASE("Polimorfismo - Tipo() despacha para a classe concreta") {
    std::unique_ptr<Equipamento> motor   = std::make_unique<Motor>(1, "M", 100.0, 50.0);
    std::unique_ptr<Equipamento> sensor  = std::make_unique<Sensor>(2, "S", 1.0);
    std::unique_ptr<Equipamento> valvula = std::make_unique<Valvula>(3, "V", 2.0);
    std::unique_ptr<Equipamento> atuador = std::make_unique<Atuador>(4, "A", 3.0);

    CHECK(motor->Tipo() == "Motor");
    CHECK(sensor->Tipo() == "Sensor");
    CHECK(valvula->Tipo() == "Valvula");
    CHECK(atuador->Tipo() == "Atuador");
}

TEST_CASE("Polimorfismo - Motor cria seus parametros") {
    Motor m(1, "Motor principal", 100.0, 50.0);
    CHECK(m.QuantidadeParametros() == 2);
}

TEST_CASE("Conjunto - aceita equipamento derivado via unique_ptr") {
    Conjunto c(1, "Nome", "Desc");
    c.AdicionarEquipamento(std::make_unique<Sensor>(5, "Sensor", 1.0));
    CHECK(c.QuantidadeEquipamentos() == 1);
    CHECK(c.AcessarEquipamento(5).Tipo() == "Sensor");
}

// ---------- Persistência (round-trip) ----------

TEST_CASE("Sistema - salvar e carregar restaura estrutura") {
    Sistema s1;
    s1.AdicionarUsuario("admin", "123", Cargo::ADMIN);
    s1.AdicionarLinha(1, "Desc", "Local", "Linha");
    s1.AcessarLinha(1).AdicionarConjunto(1, "Conj", "DescC");
    s1.AcessarLinha(1).AcessarConjunto(1).AdicionarEquipamento(2, "Equip");
    s1.AcessarLinha(1).AcessarConjunto(1).AcessarEquipamento(2)
        .AdicionarParametro(15.0, 10.0, 0.0, "Pressao", 3);
    CHECK(s1.SalvarAlteracoes() == true);

    Sistema s2;
    CHECK(s2.CarregarSave("dados/save.txt") == true);
    CHECK(s2.GetLinhas().size() == 1);
    CHECK(s2.AcessarLinha(1).QuantidadeConjuntos() == 1);
    CHECK(s2.AcessarLinha(1).AcessarConjunto(1).QuantidadeEquipamentos() == 1);
}
