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
#include <stdio.h>
#include <string>
#import "constantes.cpp"
#import "livrosdb.cpp"
#import "usuario.cpp"
#import "utilitario.cpp"

using namespace std;

int estaLogado = 0;
struct Usuario usuario;

//Definicoes das funcoes basicas do sistema.
void usuarios();
void livros();
void minhaEstante();
void pesquisas();
void recomendacoes();
void cadastraUsuario();
void exibeMenu();
void exibeMenuUsuario();
void exibeMenuVisitante();
void exibeAutenticacaoUsuario();
void exibeCadastroUsuario();
void exibeEdicaoPerfilUsuario();
void exibeRemoveUsuario();

int main() {
    exibeMenu();
    return 0;
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
        cout << " (2) Gerenciar livros" << endl;
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
                exibeEdicaoPerfilUsuario();
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
                exibeCadastroUsuario();
                break;
            case MV_AUTENTICACAO:
                exibeAutenticacaoUsuario();
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
 * Exibe cadastro de usuario.
 */
void exibeCadastroUsuario() {
    if (cadastroUsuario()) {
        exibeMenu();
    }
}

/**
 * Exibe autenticacao de usuario.
 */
void exibeAutenticacaoUsuario() {
    usuario = autenticacaoUsuario();

    if (usuario.id > 0) {
        estaLogado = 1;
        exibeMenu();
    } else {
        estaLogado = 0;
    }
}

void exibeEdicaoPerfilUsuario() {
    if (edicaoPerfilUsuario(usuario)) {
        exibeMenu();
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
        if (remocaoUsuario(usuario.id)) {
            exibeMenu();
        } else {
            estaLogado = 0;
            usuario.id = 0;
        }
    }

    exibeMenu();
}

//Falta implementacao
void cadastrar() {

    string nome;
    cout << "Digite o seu nome:" << endl;
    cin >> nome;

    string login;
    cout << "Digite o seu login:" << endl;
    cin >> login;

    int senha;
    cout << "Digite a sua senha númerica:" << endl;
    cin >> senha;


}

//Falta implementacao
void CadastarLivros() {

    string nome;
    cout << "Digite o nome do Livro:" << endl;
    cin >> nome;

    string autor;
    cout << "Digite o nome do Autor:" << endl;
    cin >> autor;

    int paginas;
    cout << "Quantidade de paginas: " << endl;
    cin >> paginas;

    int genero;
    cout << "Digite o genero do livro(Ficção[1] Romance[2] Não Ficção[3] Suspense[4]): " << endl;
    cin >> genero;


}

//Falta implementacao
void realizarLogin() {

    string login;
    cout << "Digite o seu login:" << endl;
    cin >> login;

    int senha;
    cout << "Digite a sua senha:" << endl;
    cin >> senha;


}

//Falta implementacao
void pesquisas() {
}

//Falta implementacao
void recomendacoes() {
    
}