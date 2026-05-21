#include "doctest.h"
#include "Log.hpp"

TEST_CASE("Log - GetArquivoLog retorna caminho correto") {
    Log log("sistema.log");
    CHECK(log.GetArquivoLog() == "sistema.log");
}

TEST_CASE("Log - Registrar retorna true em mensagem valida") {
    Log log("sistema.log");
    CHECK(log.Registrar("Evento de teste") == true);
}

TEST_CASE("Log - Registrar retorna false em mensagem vazia") {
    Log log("sistema.log");
    CHECK(log.Registrar("") == false);
}

TEST_CASE("Log - SetArquivoLog retorna true e atualiza caminho") {
    Log log("antigo.log");
    bool ok = log.SetArquivoLog("novo.log");
    CHECK(ok == true);
    CHECK(log.GetArquivoLog() == "novo.log");
}

TEST_CASE("Log - Registrar retorna false para mensagem acima de 500 chars") {
    Log log("sistema.log");
    std::string msg(501, 'x');
    CHECK(log.Registrar(msg) == false);
}

TEST_CASE("Log - SetArquivoLog rejeita caminho vazio") {
    Log log("sistema.log");
    CHECK(log.SetArquivoLog("") == false);
}
