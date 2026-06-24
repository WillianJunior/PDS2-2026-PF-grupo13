#include "Sistema.hpp"
#include "Cargo.hpp"
#include "Excecoes.hpp"
#include "Motor.hpp"
#include "Sensor.hpp"
#include "Valvula.hpp"
#include "Atuador.hpp"

#include <iostream>
#include <string>
#include <memory>
#include <limits>

namespace {

const std::string ARQUIVO_INICIAL = "dados/inicial.txt";

// ---- Leitura robusta de entrada ----

std::string lerLinha(const std::string& prompt) {
    std::cout << prompt;
    std::string s;
    std::getline(std::cin, s);
    return s;
}

int lerInt(const std::string& prompt) {
    while (true) {
        std::string s = lerLinha(prompt);
        try {
            return std::stoi(s);
        } catch (const std::exception&) {
            std::cout << "Valor invalido, digite um numero inteiro.\n";
        }
    }
}

double lerDouble(const std::string& prompt) {
    while (true) {
        std::string s = lerLinha(prompt);
        try {
            return std::stod(s);
        } catch (const std::exception&) {
            std::cout << "Valor invalido, digite um numero.\n";
        }
    }
}

// ---- Permissões ----

int rank(Cargo c) {
    switch (c) {
        case Cargo::TECNICO:    return 1;
        case Cargo::ENGENHEIRO: return 2;
        case Cargo::ADMIN:      return 3;
    }
    return 0;
}

std::string cargoTexto(Cargo c) {
    switch (c) {
        case Cargo::ADMIN:      return "ADMIN";
        case Cargo::ENGENHEIRO: return "ENGENHEIRO";
        case Cargo::TECNICO:    return "TECNICO";
    }
    return "?";
}

void exigir(const Sistema& s, int minimo) {
    Usuario* u = s.GetUsuarioLogado();
    if (u == nullptr) {
        throw SessaoInvalida("Nenhum usuario logado.");
    }
    if (rank(u->GetCargo()) < minimo) {
        throw AcessoNegado("Cargo sem permissao para esta operacao.");
    }
}

// ---- Operações ----

void criarLinha(Sistema& s) {
    exigir(s, rank(Cargo::ENGENHEIRO));
    int id = lerInt("ID da linha: ");
    std::string nome = lerLinha("Nome: ");
    std::string local = lerLinha("Local: ");
    std::string desc = lerLinha("Descricao: ");
    s.AdicionarLinha(id, desc, local, nome);
    std::cout << "Linha criada.\n";
}

void criarConjunto(Sistema& s) {
    exigir(s, rank(Cargo::ENGENHEIRO));
    int lid = lerInt("ID da linha: ");
    int id = lerInt("ID do conjunto: ");
    std::string nome = lerLinha("Nome: ");
    std::string desc = lerLinha("Descricao: ");
    s.AcessarLinha(lid).AdicionarConjunto(id, nome, desc);
    std::cout << "Conjunto criado.\n";
}

void criarEquipamento(Sistema& s) {
    exigir(s, rank(Cargo::ENGENHEIRO));
    int lid = lerInt("ID da linha: ");
    int cid = lerInt("ID do conjunto: ");
    int eid = lerInt("ID do equipamento: ");
    std::string desc = lerLinha("Descricao: ");
    std::cout << "Tipo: 1-Motor 2-Sensor 3-Valvula 4-Atuador 5-Generico\n";
    int tipo = lerInt("Opcao: ");

    std::unique_ptr<Equipamento> eq;
    switch (tipo) {
        case 1: {
            double v = lerDouble("Velocidade nominal: ");
            double t = lerDouble("Torque nominal: ");
            eq = std::make_unique<Motor>(eid, desc, v, t);
            break;
        }
        case 2: {
            double sinal = lerDouble("Sinal: ");
            eq = std::make_unique<Sensor>(eid, desc, sinal);
            break;
        }
        case 3: {
            double vazao = lerDouble("Vazao: ");
            eq = std::make_unique<Valvula>(eid, desc, vazao);
            break;
        }
        case 4: {
            double retorno = lerDouble("Retorno: ");
            eq = std::make_unique<Atuador>(eid, desc, retorno);
            break;
        }
        default: {
            std::string nome = lerLinha("Nome: ");
            eq = std::make_unique<Equipamento>(eid, desc, nome);
            break;
        }
    }

    s.AcessarLinha(lid).AcessarConjunto(cid).AdicionarEquipamento(std::move(eq));
    std::cout << "Equipamento criado.\n";
}

void criarParametro(Sistema& s) {
    exigir(s, rank(Cargo::ENGENHEIRO));
    int lid = lerInt("ID da linha: ");
    int cid = lerInt("ID do conjunto: ");
    int eid = lerInt("ID do equipamento: ");
    int pid = lerInt("ID do parametro: ");
    std::string desc = lerLinha("Descricao: ");
    double minimo = lerDouble("Limite minimo: ");
    double maximo = lerDouble("Limite maximo: ");
    double valor = lerDouble("Leitura atual: ");
    s.AcessarLinha(lid).AcessarConjunto(cid).AcessarEquipamento(eid)
        .AdicionarParametro(valor, maximo, minimo, desc, pid);
    std::cout << "Parametro criado.\n";
}

void diagnosticar(Sistema& s) {
    int lid = lerInt("ID da linha: ");
    LinhaDeProducao& linha = s.AcessarLinha(lid);
    linha.AtualizarAlarmes();
    std::vector<int> falhas = linha.DiagnosticarLinha();
    if (falhas.empty()) {
        std::cout << "Nenhuma falha detectada na linha.\n";
    } else {
        std::cout << "Parametros em falha (IDs): ";
        for (int id : falhas) {
            std::cout << id << ' ';
        }
        std::cout << "\nAlarmes ativos: " << linha.QuantidadeAlarmes() << '\n';
    }
}

void listar(Sistema& s) {
    const auto& linhas = s.GetLinhas();
    if (linhas.empty()) {
        std::cout << "Nenhuma linha cadastrada.\n";
        return;
    }
    for (const auto& par : linhas) {
        std::cout << "== Linha " << par.first << " ==\n";
        par.second.ExibirTudo();
    }
}

void removerLinha(Sistema& s) {
    exigir(s, rank(Cargo::ENGENHEIRO));
    int id = lerInt("ID da linha a remover: ");
    s.RemoverLinha(id);
    std::cout << "Linha removida.\n";
}

void gerenciarUsuarios(Sistema& s) {
    exigir(s, rank(Cargo::ADMIN));
    std::cout << "1-Criar 2-Remover\n";
    int op = lerInt("Opcao: ");
    if (op == 1) {
        std::string login = lerLinha("Login: ");
        std::string senha = lerLinha("Senha: ");
        std::cout << "Cargo: 1-Admin 2-Engenheiro 3-Tecnico\n";
        int c = lerInt("Opcao: ");
        Cargo cargo = (c == 1) ? Cargo::ADMIN
                    : (c == 2) ? Cargo::ENGENHEIRO
                               : Cargo::TECNICO;
        s.AdicionarUsuario(login, senha, cargo);
    } else if (op == 2) {
        std::string login = lerLinha("Login a remover: ");
        s.RemoverUsuario(login);
    }
}

void menu(Sistema& s) {
    bool continuar = true;
    while (continuar) {
        Usuario* u = s.GetUsuarioLogado();
        std::cout << "\n=== Menu (" << (u ? cargoTexto(u->GetCargo()) : "?")
                  << ") ===\n"
                  << "1 - Listar tudo\n"
                  << "2 - Criar linha\n"
                  << "3 - Remover linha\n"
                  << "4 - Criar conjunto\n"
                  << "5 - Criar equipamento\n"
                  << "6 - Criar parametro\n"
                  << "7 - Diagnosticar linha\n"
                  << "8 - Gerenciar usuarios\n"
                  << "9 - Salvar\n"
                  << "10 - Carregar\n"
                  << "0 - Logout\n";
        int op = lerInt("Opcao: ");
        try {
            switch (op) {
                case 1: listar(s); break;
                case 2: criarLinha(s); break;
                case 3: removerLinha(s); break;
                case 4: criarConjunto(s); break;
                case 5: criarEquipamento(s); break;
                case 6: criarParametro(s); break;
                case 7: diagnosticar(s); break;
                case 8: gerenciarUsuarios(s); break;
                case 9:
                    std::cout << (s.SalvarAlteracoes() ? "Salvo.\n"
                                                       : "Falha ao salvar.\n");
                    break;
                case 10:
                    std::cout << (s.CarregarUltimoSave() ? "Carregado.\n"
                                                         : "Falha ao carregar.\n");
                    break;
                case 0:
                    s.Logout();
                    continuar = false;
                    break;
                default:
                    std::cout << "Opcao invalida.\n";
            }
        } catch (const ExcecaoSistema& e) {
            std::cout << "[Erro] " << e.what() << '\n';
        }
    }
}

} // namespace

int main() {
    std::cout << "Sistema de Tolerancia de Falha em Fabricas\n";

    Sistema s;

    // Carrega usuarios/estrutura inicial fornecidos pelo grupo.
    if (!s.CarregarSave(ARQUIVO_INICIAL)) {
        std::cout << "(Aviso) Arquivo inicial '" << ARQUIVO_INICIAL
                  << "' nao encontrado; criando admin padrao (admin/admin123).\n";
        s.AdicionarUsuario("admin", "admin123", Cargo::ADMIN);
    }

    bool executando = true;
    while (executando) {
        std::cout << "\n--- Login (login vazio encerra) ---\n";
        std::string login = lerLinha("Login: ");
        if (login.empty()) {
            executando = false;
            break;
        }
        std::string senha = lerLinha("Senha: ");

        if (s.Login(login, senha)) {
            menu(s);
        } else {
            std::cout << "Credenciais invalidas.\n";
        }
    }

    std::cout << "Encerrando.\n";
    return 0;
}
