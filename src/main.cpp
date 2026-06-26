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
#include <cstdlib>

const std::string ARQUIVO_INICIAL = "dados/inicial.txt";

void limparTela() {
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif
}

void descartarLinha() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void pausar() {
    std::cout << "\nPressione ENTER para continuar...";
    std::string lixo;
    std::getline(std::cin, lixo);
}

int rank(Cargo c) {
    switch (c) {
        case Cargo::TECNICO:
            return 1;
        case Cargo::ENGENHEIRO:
            return 2;
        case Cargo::ADMIN:
            return 3;
    }
    return 0;
}

std::string cargoTexto(Cargo c) {
    switch (c) {
        case Cargo::ADMIN:
            return "ADMIN";
        case Cargo::ENGENHEIRO:
            return "ENGENHEIRO";
        case Cargo::TECNICO:
            return "TECNICO";
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

void criarLinha(Sistema& s) {
    exigir(s, rank(Cargo::ENGENHEIRO));
    std::string nome;
    std::string local;
    std::string desc;

    std::cout << "Nome: ";
    std::getline(std::cin, nome);

    std::cout << "Local: ";
    std::getline(std::cin, local);

    std::cout << "Descricao: ";
    std::getline(std::cin, desc);

    int id = s.AdicionarLinha(desc, local, nome);
    std::cout << "Linha criada com ID " << id << "." << std::endl;
}

void criarConjunto(Sistema& s) {
    exigir(s, rank(Cargo::ENGENHEIRO));
    int lid;
    std::string nome;
    std::string desc;

    std::cout << "\nID da linha: ";
    std::cin >> lid;
    descartarLinha();

    std::cout << "\nNome: ";
    std::getline(std::cin, nome);

    std::cout << "\nDescricao: ";
    std::getline(std::cin, desc);

    int id = s.AcessarLinha(lid).AdicionarConjunto(nome, desc);
    std::cout << "\nConjunto criado com ID " << id << "." << std::endl;
}

void criarEquipamento(Sistema& s) {
    exigir(s, rank(Cargo::ENGENHEIRO));
    int lid;
    int cid;
    int tipo;
    std::string desc;

    std::cout << "\nID da Linha: ";
    std::cin >> lid;

    std::cout << "\nID do Conjunto: ";
    std::cin >> cid;
    descartarLinha();

    Conjunto& conj = s.AcessarLinha(lid).AcessarConjunto(cid);
    int eid = conj.ProximoIdEquipamento();

    std::cout << "\nDescricao: ";
    std::getline(std::cin, desc);

    std::cout << "Tipo:\n1-Motor\n2-Sensor\n3-Valvula\n4-Atuador\n5-Generico" << std::endl;
    std::cout << "Opcao: ";
    std::cin >> tipo;
    descartarLinha();

    std::unique_ptr<Equipamento> eq;
    switch (tipo) {
        case 1: {
            double v;
            double t;

            std::cout << "\nVelocidade nominal: ";
            std::cin >> v;

            std::cout << "\nTorque nominal: ";
            std::cin >> t;
            descartarLinha();

            eq = std::make_unique<Motor>(eid, desc, v, t);
            break;
        }
        case 2: {
            double sinal;
            std::cout << "\nSinal: ";
            std::cin >> sinal;
            descartarLinha();
            eq = std::make_unique<Sensor>(eid, desc, sinal);
            break;
        }
        case 3: {
            double vazao;
            std::cout << "\nVazao: ";
            std::cin >> vazao;
            descartarLinha();
            eq = std::make_unique<Valvula>(eid, desc, vazao);
            break;
        }
        case 4: {
            double retorno;
            std::cout << "\nRetorno: ";
            std::cin >> retorno;
            descartarLinha();
            eq = std::make_unique<Atuador>(eid, desc, retorno);
            break;
        }
        default: {
            std::string nome;
            std::cout << "\nNome: ";
            std::getline(std::cin, nome);
            eq = std::make_unique<Equipamento>(eid, desc, nome);
            break;
        }
    }

    conj.AdicionarEquipamento(std::move(eq));
    std::cout << "Equipamento criado com ID " << eid << "." << std::endl;
}

void criarParametro(Sistema& s) {
    exigir(s, rank(Cargo::ENGENHEIRO));
    int lid;
    int cid;
    int eid;
    std::string desc;
    double minimo;
    double maximo;
    double valor;

    std::cout << "ID da linha: ";
    std::cin >> lid;

    std::cout << "ID do conjunto: ";
    std::cin >> cid;

    std::cout << "ID do equipamento: ";
    std::cin >> eid;
    descartarLinha();

    std::cout << "Descricao: ";
    std::getline(std::cin, desc);

    std::cout << "Limite minimo: ";
    std::cin >> minimo;

    std::cout << "Limite maximo: ";
    std::cin >> maximo;

    std::cout << "Leitura atual: ";
    std::cin >> valor;
    descartarLinha();

    int pid = s.AcessarLinha(lid).AcessarConjunto(cid).AcessarEquipamento(eid)
        .AdicionarParametro(valor, maximo, minimo, desc);
    std::cout << "Parametro criado com ID " << pid << "." << std::endl;
}

void diagnosticar(Sistema& s) {
    int lid;
    std::cout << "ID da linha: ";
    std::cin >> lid;
    descartarLinha();

    LinhaDeProducao& linha = s.AcessarLinha(lid);
    linha.AtualizarAlarmes();
    std::vector<int> falhas = linha.DiagnosticarLinha();
    if (falhas.empty()) {
        std::cout << "Nenhuma falha detectada na linha." << std::endl;
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
        std::cout << "Nenhuma linha cadastrada." << std::endl;
        return;
    }
    for (const auto& par : linhas) {
        std::cout << "== Linha " << par.second.GetNome() << " ==" << std::endl;
        par.second.ExibirTudo();
    }
}

void removerLinha(Sistema& s) {
    exigir(s, rank(Cargo::ENGENHEIRO));
    int id;
    std::cout << "ID da linha a remover: ";
    std::cin >> id;
    descartarLinha();
    s.RemoverLinha(id);
    std::cout << "Linha removida." << std::endl;
}

void gerenciarUsuarios(Sistema& s) {
    exigir(s, rank(Cargo::ADMIN));
    std::cout << "1-Criar 2-Remover" << std::endl;
    int op;
    std::cout << "Opcao: ";
    std::cin >> op;
    descartarLinha();

    if (op == 1) {
        std::string login;
        std::string senha;
        int c;

        std::cout << "Login: ";
        std::getline(std::cin, login);

        std::cout << "Senha: ";
        std::getline(std::cin, senha);

        std::cout << "Cargo: 1-Admin 2-Engenheiro 3-Tecnico" << std::endl;
        std::cout << "Opcao: ";
        std::cin >> c;
        descartarLinha();

        Cargo cargo;
        if (c == 1) {
            cargo = Cargo::ADMIN;
        } else if (c == 2) {
            cargo = Cargo::ENGENHEIRO;
        } else {
            cargo = Cargo::TECNICO;
        }
        s.AdicionarUsuario(login, senha, cargo);
    } else if (op == 2) {
        std::string login;
        std::cout << "Login a remover: ";
        std::getline(std::cin, login);
        s.RemoverUsuario(login);
    }
}

void menu(Sistema& s) {
    bool continuar = true;
    while (continuar) {
        limparTela();
        Usuario* usuario = s.GetUsuarioLogado();
        if (!usuario) {
         break;
        }
        std::cout << "\n=== Menu (" << cargoTexto(usuario->GetCargo())
                  << ") ===" << std::endl
                  << "1 - Listar tudo" << std::endl
                  << "2 - Criar linha" << std::endl
                  << "3 - Remover linha" << std::endl
                  << "4 - Criar conjunto" << std::endl
                  << "5 - Criar equipamento" << std::endl
                  << "6 - Criar parametro" << std::endl
                  << "7 - Diagnosticar linha" << std::endl
                  << "8 - Gerenciar usuarios" << std::endl
                  << "9 - Salvar" << std::endl
                  << "10 - Carregar" << std::endl
                  << "0 - Logout" << std::endl;

        int op;
        std::cout << "Opcao: ";
        std::cin >> op;
        descartarLinha();

        try {
            switch (op) {
                case 1:
                    listar(s);
                    break;
                case 2:
                    criarLinha(s);
                    break;
                case 3:
                    removerLinha(s);
                    break;
                case 4:
                    criarConjunto(s);
                    break;
                case 5:
                    criarEquipamento(s);
                    break;
                case 6:
                    criarParametro(s);
                    break;
                case 7:
                    diagnosticar(s);
                    break;
                case 8:
                    gerenciarUsuarios(s);
                    break;
                case 9: {
                    bool salvo = s.SalvarAlteracoes();
                    if (salvo) {
                        std::cout << "Salvo." << std::endl;
                    } else {
                        std::cout << "Falha ao salvar." << std::endl;
                    }
                    break;
                }
                case 10: {
                    bool carregado = s.CarregarUltimoSave();
                    if (carregado) {
                        std::cout << "Carregado." << std::endl;
                    } else {
                        std::cout << "Falha ao carregar." << std::endl;
                    }
                    break;
                }
                case 0:
                    s.Logout();
                    continuar = false;
                    break;
                default:
                    std::cout << "Opcao invalida." << std::endl;
            }
        } catch (const ExcecaoSistema& e) {
            std::cout << "[Erro] " << e.what() << '\n';
        }
        if (continuar) {
            pausar();
        }
    }
}


int main() {
    std::cout << "Sistema de Tolerancia de Falha em Fabricas" << std::endl;

    Sistema s;

    if (!s.CarregarSave(ARQUIVO_INICIAL)) {
        std::cout << "(Aviso) Arquivo inicial '" << ARQUIVO_INICIAL
                  << "' nao encontrado; criando admin padrao (admin/admin123)." << std::endl;
        s.AdicionarUsuario("admin", "admin123", Cargo::ADMIN);
    }

    bool executando = true;
    while (executando) {
        limparTela();
        std::cout << "\n--- Login (login vazio encerra) ---" << std::endl;

        std::string login;
        std::cout << "Login: ";
        std::getline(std::cin, login);
        if (login.empty()) {
            executando = false;
            break;
        }

        std::string senha;
        std::cout << "Senha: ";
        std::getline(std::cin, senha);

        if (s.Login(login, senha)) {
            menu(s);
        } else {
            std::cout << "Credenciais invalidas." << std::endl;
        }
    }

    std::cout << "Encerrando." << std::endl;
    return 0;
}
