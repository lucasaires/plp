/*
 * Projeto PrompSkoob!
 *
 * Projeto que simula uma estante virtual, onde os usuarios poderao registrar/editar/adicionar
 * livros a sua biblioteca pessoal, tambem podendo avalia-los e indica-los.
 *
 * Grupo: Álex Micaela de Oliveira Fidelis - alex.fidelis@ccc.ufcg.edu.br
 * 		  Caio Benjamim Lima Simplício - caio.simplicio@ccc.ufcg.edu.br
 * 		  Caroliny Mylena Bezerra e Silva - caroliny.silva@ccc.ufcg.edu.br
 * 		  Júlia Fernandes Alves - julia.alves@ccc.ufcg.edu.br
 * 		  Lucas Gomes Aires - lucas.aires@ccc.ufcg.edu.br
 */

#include <iostream>
#include <string>
#import "constantes.cpp"
#import "usuario.cpp"
#import "livro.cpp"
#import "estante.cpp"
#import "utilitario.cpp"

using namespace std;

int estaLogado = 0;
struct Usuario usuario;

void exibeAutenticacaoUsuario();
void exibeMenu();
void exibeMenuLivro();
void exibeMenuMinhaEstante();
void exibeMenuRecomendacao();
void exibeMenuUsuario();
void exibeMenuVisitante();
void exibeRemoveUsuario();

int main() {
    criaTabelaEstante();
    criaTabelaUsuario();
    criaTabelaLivro();
    exibeMenu();
    return 0;
}

/**
 * Exibe autenticacao de usuario.
 */
void exibeAutenticacaoUsuario() {
    usuario = autenticacaoUsuario();

    if (usuario.id > 0) {
        estaLogado = 1;
    } else {
        estaLogado = 0;
    }
    exibeMenu();
}

/**
 * Exibe o menu de acordo com usuario logado.
 */
void exibeMenu() {
    if (estaLogado) {
        exibeMenuUsuario();
    } else {
        exibeMenuVisitante();
    }
}

/**
 * Exibe o menu principal da aplicacao caso o usuario esteja logado.
 */
void exibeMenuUsuario() {
    int opcao;

    while (opcao != M_SAIR) {
        cout << " .::. PrompSkoob .::." << endl;
        cout << " - Menu Principal - " << endl;
        cout << " Ola, " << usuario.nome << "!" << endl << endl;
        cout << " (1) Editar meu perfil" << endl;
        cout << " (2) Gerenciar livro" << endl;
        cout << " (3) Minha estante" << endl;
        cout << " (4) Pesquisar no acervo" << endl;
        cout << " (5) Recomendações de livros" << endl;
        cout << " (6) Remover meu perfil" << endl;
        cout << " (7) Sair da conta" << endl;
        cout << " (8) Sair" << endl << endl;
        cout << "Opcao: ";
        cin >> opcao;

        switch (opcao) {
            case M_EDITAR_PERFIL:
                edicaoPerfilUsuario(usuario);
                break;
            case M_CADASTRAR_LIVRO:
                exibeMenuLivro();
                break;
            case M_MINHA_ESTANTE:
                exibeMenuMinhaEstante();
                break;
            case M_PESQUISA:
                pesquisaAcervo();
                break;
            case M_RECOMENDACOES:
                exibeMenuRecomendacao();
                break;
            case M_REMOVER_PERFIL:
                exibeRemoveUsuario();
                break;
            case M_SAIR_CONTA:
                estaLogado = 0;
                usuario.id = 0;
                exibeMenu();
                break;
            case M_SAIR:
                exibeMensagem("Ate breve... :)");
                exit(EXIT_SUCCESS);
            default:
                exibeMensagemErro("Opcao invalida!");
        }
    }
}

/**
 * Exibe a listagem de livros juntamente com o submenu.
 * 1 - Cadastrar livros
 * 2 - Editar livro
 * 3 - Remover livro
 * 4 - Voltar para o menu principal
 */
void exibeMenuLivro() {
    int opcao;

    while (opcao != 5) {
        cout << " .::. PrompSkoob .::." << endl;
        cout << " - Gerenciar Livro - " << endl << endl;
        listagemLivros();
        cout << " (1) Cadastrar | (2) Editar | (3) Remover | (4) Adicionar a Estante | (5) Voltar" << endl << endl;
        cout << "Opcao: ";
        cin >> opcao;
        cout << endl;

        switch (opcao) {
            case 1:
                cadastroLivro();
                break;
            case 2:
                edicaoLivro();
                break;
            case 3:
                remocaoLivro();
                break;
            case 4:
                adicionaLivro(usuario);
                break;
            case 5:
                exibeMenu();
            default:
                exibeMensagemErro("Opcao invalida!");
        }
    }
}

/**
 * Exibe a listagem de livros juntamente com o submenu da estante.
 */
void exibeMenuMinhaEstante() {
    int opcao;

    while (opcao != 5) {
        cout << " .::. PrompSkoob .::." << endl;
        cout << " - Minha Estante - " << endl << endl;
        listagemEstantes(usuario);
        cout << " (1) Mudar Status | (2) Avaliar | (3) Remover | (4) Registro de Leitura |  (5) Voltar" << endl << endl;
        cout << "Opcao: ";
        cin >> opcao;
        cout << endl;

        switch (opcao) {
            case 1:
                edicaoSituacao(usuario);
                break;
            case 2:
                avalicaoLivro(usuario);
                break;
            case 3:
                remocaoLivroEstante(usuario);
                break;
            case 4:
                registroLeitura(usuario);
                break;
            case 5:
                exibeMenu();
            default:
                exibeMensagemErro("Opcao invalida!");
        }
    }
}

/**
 * Exibe o menu principal da aplicacao caso o usuario nao possua conta no PrompSkoob.
 */
void exibeMenuVisitante() {
    int opcao;

    while (opcao != MV_SAIR) {
        cout << " .::. PrompSkoob .::." << endl;
        cout << " - Menu Principal - " << endl;
        cout << " Ola, visitante!" << endl << endl;
        cout << " (1) Quero me cadastrar" << endl;
        cout << " (2) Autenticacao" << endl;
        cout << " (3) Pesquisar no acervo" << endl;
        cout << " (4) Sair" << endl << endl;
        cout << "Opcao: ";
        cin >> opcao;

        switch (opcao) {
            case MV_CADASTRO_USUARIO:
                cadastroUsuario();
                break;
            case MV_AUTENTICACAO:
                exibeAutenticacaoUsuario();
                break;
            case MV_PESQUISA:
                pesquisaAcervo();
                break;
            case MV_SAIR:
                exibeMensagem("Ate breve... :)");
                exit(EXIT_SUCCESS);
            default:
                exibeMensagemErro("Opcao invalida!");
        }
    }
}

/**
 * Exibe o menu de recomendacoes de livros de acordo com os interesses do usuario.
 */
void exibeMenuRecomendacao() {
    int opcao;

    while (opcao != 2) {
        cout << " .::. PrompSkoob .::." << endl;
        cout << " - Recomendacoes de Livros - " << endl << endl;
        listagemRecomendacoes(usuario);
        cout << " (1) Adicionar a Estante | (2) Voltar" << endl << endl;
        cout << "Opcao: ";
        cin >> opcao;
        cout << endl;

        switch (opcao) {
            case 1:
                adicionaLivro(usuario);
                break;
            case 2:
                exibeMenu();
            default:
                exibeMensagemErro("Opcao invalida!");
        }
    }
}

/**
 * Exibe remoçao de usuario.
 */
void exibeRemoveUsuario() {
    char confirmacao;
    cout << "Deseja realmente remover seu perfil? (S/N) : ";
    cin >> confirmacao;

    if (confirmacao == 's' || confirmacao == 'S') {
        if (!remocaoUsuario(usuario.id)) {
            estaLogado = 0;
            usuario.id = 0;
        }
    }
    exibeMenu();
}