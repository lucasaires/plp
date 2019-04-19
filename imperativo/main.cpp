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
#include "constantes.cpp"
#include "livrosdb.cpp"

using namespace std;

int usuarioLogado = 1;

//Definicoes das funcoes basicas do sistema.
void usuarios();
void livros();
void minhaEstante();
void pesquisas();
void recomendacoes();
void cadastraUsuario();
void exibeMensagem(string mensagem);
void exibeMensagemErro(string mensagem);
void exibeMenu();
void exibeMenuVisitante();

int main() {
    if (usuarioLogado) {
        exibeMenu();
    } else {
        exibeMenuVisitante();
    }

    return 0;
}

void exibeMensagem(string mensagem) {
    cout << "\033[1;32m" << "--- " << mensagem << " ---" << "\033[0m\n\n";
}

void exibeMensagemErro(string mensagem) {
    cout << "\033[1;31m" << "--- " << mensagem << " ---" << "\033[0m\n\n";
}

/**
 * Exibe o menu principal da aplicacao caso o usuario esteja logado.
 */
void exibeMenu() {
    int opcao;

    while (opcao != M_SAIR) {
        cout << " .::. PrompSkoob .::." << endl;
        cout << " - Menu Principal - " << endl;
        cout << " Ola, NOME USUARIO!" << endl << endl;
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
            case M_SAIR:
                exibeMensagem("Ate breve... :)");
                break;
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
                cadastraUsuario();
                break;
            case MV_SAIR:
                exibeMensagem("Ate breve... :)");
                break;
            default:
                exibeMensagemErro("Opcao invalida!");
        }
    }
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
    int opcao; 
    const int AUTOR = 1;
    const int LIVRO = 2;
    const int GENERO = 3;

    cout << "Digite a opção de Pesquisa de sua preferência: " << endl;
    cout << "Pesquisa por (1)Autor: " << endl;
    cout << "Pesquisa por (2)Livro: " << endl;
    cout << "Pesquisa por (3)Gênero:" << endl;
    cin >> opcao;

    switch (opcao)
    {
        case AUTOR:
            pesquisasAutor();
            break;
        
        case LIVRO:
            pesquisasLivro();
            break;
        
        case GENERO:
            pesquisasGenero();
            break;
    
        default:
            cout << "Opcao inválida" << endl;
            break;
    }
}

void pesquisasAutor() {
    string pesquisa;
    cout << "Digite o nome do Autor: " << endl;

    cin >> pesquisa;

}

void pesquisasLivro() {
    string pesquisa;
    cout << "Digite o nome do Livro: " << endl; 

    cin >> pesquisa;

}

void pesquisasGenero() {
    string pesquisa;
    cout << "Digite o nome do gênero: " << endl;

    cin >> pesquisa;
    
}

//Falta implementacao
void recomendacoes() {
    
}