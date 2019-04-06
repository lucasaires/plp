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

#include <iostream>;
#include <stdio.h>;
#include <string>;
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
	cout << "   (1) Usuarios"<< endl;
	cout << "   (2) Livros" << endl;
	cout << "   (3) Minha Estante" << endl;
	cout << "   (4) Pesquisas" << endl;
	cout << "   (5) Recomendacoes de Livros" << endl;
	cout << "   (6) Sair" << endl << endl;
	cout << " Opcao: ";
	cin >> entrada;

	switch(entrada){
		case 1:
			usuarios();
			break;
		case 2:
			livros();
			break;
		case 3:
			minhaEstante();
			break;
		case 4:
			pesquisas();
			break;
		case 5:
			recomendacoes();
			break;
		case 6:
			cout << "Volte sempre!";
			break;
		default:
			cout << "Valor invalido!";
	}
	return 0;
}

//Falta implementacao
void usuarios(){
}

//Falta implementacao
void livros(){
}

//Falta implementacao
void minhaEstante(){

}

//Falta implementacao
void pesquisas(){
}

//Falta implementacao
void recomendacoes(){
}





