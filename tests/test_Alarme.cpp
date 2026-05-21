#include "doctest.h"
#include "Alarme.hpp"
#include "Parametro.hpp"

TEST_CASE("Alarme - estado inicial e false") {
    Parametro p(5.0, 10.0, 0.0, "Temp", 1);
    Alarme a("Alarme Temperatura", 1, p);
    CHECK(a.GetEstado() == false);
}

TEST_CASE("Alarme - SetEstado ativa alarme") {
    Parametro p(5.0, 10.0, 0.0, "Temp", 2);
    Alarme a("Alarme Temp", 2, p);
    a.SetEstado(true);
    CHECK(a.GetEstado() == true);
}

TEST_CASE("Alarme - SetEstado desativa alarme") {
    Parametro p(5.0, 10.0, 0.0, "Temp", 3);
    Alarme a("Alarme Temp", 3, p);
    a.SetEstado(true);
    a.SetEstado(false);
    CHECK(a.GetEstado() == false);
}

TEST_CASE("Alarme - AtualizarAlarme retorna true quando parametro em falha") {
    Parametro p(15.0, 10.0, 0.0, "Pressao", 4);
    p.DiagnosticarParametro();
    Alarme a("Alarme Pressao", 4, p);
    CHECK(a.AtualizarAlarme() == true);
}

TEST_CASE("Alarme - AtualizarAlarme retorna false quando parametro ok") {
    Parametro p(5.0, 10.0, 0.0, "Pressao", 5);
    Alarme a("Alarme Pressao", 5, p);
    CHECK(a.AtualizarAlarme() == false);
}

TEST_CASE("Alarme - AtualizarAlarme sincroniza estado interno") {
    Parametro p(15.0, 10.0, 0.0, "Vibr", 6);
    p.DiagnosticarParametro();
    Alarme a("Alarme Vibr", 6, p);
    a.AtualizarAlarme();
    CHECK(a.GetEstado() == true);
}
