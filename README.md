# Sistema de Tolerância de Falha em Fábricas

Sistema de monitoramento industrial orientado a objetos desenvolvido em C++. Permite o acompanhamento em tempo real de parâmetros de equipamentos organizados em linhas de produção, detectando automaticamente condições de falha e disparando alarmes.

## Motivação

A indústria depende de equipamentos que operam continuamente sob limites bem definidos de temperatura, pressão, vibração e outros parâmetros. Uma falha não detectada em um único equipamento pode se propagar pela linha de produção e gerar paradas custosas ou riscos de segurança. Escolhemos este tema porque ele exercita de forma natural os pilares da disciplina: uma **hierarquia clara de composição** (Sistema → Linha → Conjunto → Equipamento → Parâmetro), **herança** entre tipos de equipamento (Motor, Sensor, Válvula, Atuador), **encapsulamento** dos limites e do histórico de cada parâmetro, e **propagação de diagnóstico** por toda a estrutura. Além de ser um domínio rico em regras de negócio, é um problema concreto e fácil de visualizar, o que facilita a modelagem e a escrita de testes significativos.

## Funcionalidades

- Gerenciamento hierárquico de **Linhas de Produção → Conjuntos → Equipamentos → Parâmetros**
- Monitoramento de parâmetros com limites configuráveis (Min/Max)
- Disparo automático de **alarmes** quando parâmetros violam seus limites
- **Diagnóstico** propagado por toda a hierarquia, identificando os pontos de falha
- Controle de acesso por usuários com três níveis de cargo
- Persistência de dados com save/load de estado
- Registro de eventos via **Log** em arquivo

## Hierarquia do Sistema

Composição (relação "tem-um"):

```
Sistema
 \-- LinhaDeProducao
       \-- Conjunto
             \-- Equipamento
                   +-- Parametro
                   \-- Alarme
```

Herança (relação "é-um") — especializações de `Equipamento`:

```
Equipamento
 +-- Motor      (velocidade, torque)
 +-- Sensor     (sinal)
 +-- Valvula    (vazao)
 \-- Atuador    (retorno)
```

## Cargos de Usuário

| Cargo | Permissões |
|---|---|
| `ADMIN` | Gerencia usuários e toda a estrutura do sistema |
| `ENGENHEIRO` | Configura linhas, conjuntos e equipamentos |
| `TECNICO` | Visualiza dados e alarmes |

## Estrutura de Diretórios

```
.
+-- include/        # Contratos das classes (.hpp), incl. Excecoes.hpp
+-- src/            # Implementacoes (.cpp) e main.cpp (interface de terminal)
+-- design/         # User Stories, Cartoes CRC e documentacao gerada
+-- tests/          # Testes automatizados (doctest)
+-- dados/          # Arquivos de inicializacao (ex.: inicial.txt)
+-- build/          # Artefatos de compilacao
+-- Makefile        # Automacao de build e testes
+-- Doxyfile        # Configuracao do Doxygen
\-- README.md
```

## Estado de Desenvolvimento

Comportamentos implementados e validados:

- **Contratos (`.hpp`)** e **documentação Doxygen** para todas as classes principais.
- **Implementação (`.cpp`)** completa das entidades e do `Sistema`, incluindo
  diagnóstico propagado, alarmes e persistência (save/load) de estado.
- **Especializações** de equipamento (Motor, Sensor, Válvula, Atuador) integradas
  via **polimorfismo** com `std::unique_ptr<Equipamento>`.
- **Programação defensiva**: validação de entradas com **exceções próprias**
  (hierarquia `ExcecaoSistema` em `include/Excecoes.hpp`).
- **RAII**: nenhuma gestão manual de memória (`new`/`delete`); alocação dinâmica
  apenas via smart pointers.
- **Interface de terminal** interativa (`src/main.cpp`) com login, controle de
  acesso por cargo e tratamento de exceções.
- **Testes de unidade** (doctest): uma suíte por classe principal + suíte de
  exceções/polimorfismo/persistência. Atualmente **98 testes** passando com
  **~74% de cobertura** (`gcovr`).

## Programação Defensiva e Tratamento de Exceções

As entradas inválidas lançam exceções específicas do domínio, todas derivadas de
`ExcecaoSistema` (logo, captráveis por um único `catch (const ExcecaoSistema&)`):

| Exceção | Quando |
|---|---|
| `EntradaInvalida` | string vazia (descrição, login, senha) |
| `LimitesInvalidos` | `Max < Min` em um parâmetro |
| `IdInvalido` | identificador negativo |
| `IdDuplicado` | inserir um ID já existente |
| `IdInexistente` | acessar/remover um ID ausente |
| `AcessoNegado` | operação acima do cargo do usuário (interface) |
| `SessaoInvalida` | operação que exige sessão sem usuário logado (interface) |

> Observação: uma **leitura fora dos limites** de um parâmetro **não** é erro —
> é justamente a condição de falha que o sistema detecta, então é armazenada e
> sinalizada via diagnóstico/alarme.

## Compilação e Testes

O `Makefile` automatiza a compilação e a verificação por testes de unidade
(framework [doctest](https://github.com/doctest/doctest)):

```bash
make        # compila os módulos e gera build/test_runner
make test   # executa os testes e gera os relatórios de cobertura (gcovr)
make app    # compila a aplicação interativa em build/sistema
make run    # compila (se preciso) e executa a aplicação
make clean  # remove a pasta build/
```

- `make test` executa todos os casos de teste e, em seguida, gera a cobertura
  via `gcovr` (saída em texto e em `build/coverage.html`).
- O `make clean` é portável: usa `rmdir /S /Q` no Windows e `rm -rf` em
  Linux/macOS (detecção automática de SO no Makefile).

### Instalação do gcovr

O `gcovr` é uma ferramenta Python (wrapper do `gcov`) e precisa ser instalado
à parte. Caso o `pip` não esteja disponível, primeiro habilite-o com:

```bash
python -m ensurepip --upgrade
```

Em seguida instale o `gcovr` via `pip`:

| SO | Comando |
|---|---|
| **Linux** | `python3 -m pip install --user gcovr` |
| **macOS** | `python3 -m pip install --user gcovr` |
| **Windows** | `python -m pip install --user gcovr` |

Alternativas pelo gerenciador de pacotes do sistema:

- **Fedora/RHEL:** `sudo dnf install gcovr`
- **Debian/Ubuntu:** `sudo apt install gcovr`
- **macOS (Homebrew):** `brew install gcovr`

Verifique a instalação com `python3 -m gcovr --version` (use `python` no
Windows). O Makefile invoca `python3 -m gcovr` em Linux/macOS e `python -m gcovr`
em Windows.

## Execução da Aplicação

```bash
make run     # ou: make app && ./build/sistema
```

Ao iniciar, o sistema carrega o arquivo de inicialização `dados/inicial.txt`
(fornecido no repositório), que cadastra três usuários de exemplo:

| Login | Senha | Cargo |
|---|---|---|
| `admin` | `admin123` | ADMIN |
| `eng` | `eng123` | ENGENHEIRO |
| `tec` | `tec123` | TECNICO |

Após o login, um menu por cargo permite criar/listar/remover linhas, conjuntos,
equipamentos (Motor/Sensor/Válvula/Atuador) e parâmetros, executar diagnóstico,
e salvar/carregar o estado (`save.txt`). Entradas inválidas são tratadas por
exceções e exibidas sem encerrar o programa.

## Documentação

A documentação das classes pode ser gerada com o Doxygen a partir da raiz do projeto:

```bash
doxygen Doxyfile
```

A saída HTML estará disponível em `docs/html/index.html`.
Uma versão, atualiza, em PDF pode ser encontrada na raiz do projeto como `doxygen_doc.pdf`.

## Equipe
| Nº Matrícula | Nome |
|--------------|------| 
| 2024010002 | Felipe Hildegardes Jorge |
| 2022028400 | Wennedes de Oliveira Nogueira Junior |
| 2020057144 | Gustavo Coelho Santos |