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
 *
 */

#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

//Definicoes das funcoes basicas do sistema.
void usuarios();
void livros();
void minhaEstante();
void pesquisas();
void recomendacoes();

//metodo main, roda o menu do sistema.
int main(){
	int entrada;
	cout << " .::. PrompSkoob .::." << endl;
	cout << "   Menu Principal  " << endl;
	cout << "   Ola, usuario!" << endl << endl;
	cout << "   (1) Cadastrar Usuario"<< endl;
	cout << "   (2) Cadastrar Livros" << endl;
	cout << "   (3) Realizar Login" << endl;
	cout << "   (6) Sair" << endl << endl;
	cout << " Opcao: ";
	cin >> entrada;

	switch(entrada){
		case 1:
			cadastrarUsuario();
			break;
		case 2:
			cadastrarLivros();
			break;
		case 3:
			realizarLogin();
			break;
		default:
			cout << "Valor invalido!";
	}
	return 0;
}

//Falta implementacao
void cadastrar(){
	
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
void CadastarLivros(){

	string nome; 
	cout <<"Digite o nome do Livro:" << endl;
	cin >> nome;

	string autor;
	cout << "Digite o nome do Autor:" << endl;
	cin >> autor;

}

//Falta implementacao
void realizarLogin(){

	string login;
	cout << "Digite o seu login:" << endl;
	cin >> login;

	int senha; 
	cout << "Digite a sua senha:" << endl;
	cin >> senha;


}

//Falta implementacao
void pesquisas(){
}

//Falta implementacao
void recomendacoes(){
}





