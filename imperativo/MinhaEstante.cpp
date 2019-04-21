/*
 * MinhaEstante2.cpp
 *
 *  Created on: 17 de abr de 2019
 *      Author: Álex Micaela
 */

#include <iostream>
#include <vector>

using namespace std;

struct Livro{
	string ISBN;
	string nome;
	string autor;
	int paginas;
	string genero;
	int paginasLidas;
};

void visualizarMinhaEstante(vector<Livro> &estante);
int removerLivroMinhaEst(vector<Livro> &estante, string ISBN);
void adicionaLivroMinhaEst(vector<Livro> &estante, string ISBN, string nome, string autor, int paginas, string genero, int paginasLidas);
int mudarStatusLeitura(vector<Livro> &estante, int paginasLidas, string ISBN);
int insertionSort(vector<Livro> &estante);
void swapLivros(vector<Livro> &estante, int i, int j);

void adicionaLivroMinhaEst(vector<Livro> &estante, string ISBN, string nome, string autor, int paginas, string genero, int paginasLidas){
	Livro livro;
	livro.ISBN = ISBN;
	livro.nome = nome;
	livro.autor = autor;
	livro.paginas = paginas;
	livro.genero = genero;
	livro.paginasLidas= paginasLidas;
	estante.push_back(livro);
	insertionSort(estante);
}

int removerLivroMinhaEst(vector<Livro> &estante, string isbn){
	int indexParaRemover = -1;
	int retorno = -1;
	
	for(int i = 0; i <= (int)estante.size() - 1; i++){
		if (estante.at(i).ISBN == isbn){
			indexParaRemover = i;
			break;
		}

	if(indexParaRemover > -1) {
		estante.erase(estante.begin() + indexParaRemover);
		retorno = 1;
	} else {
		retorno = 0;
		}
	}
	return retorno;
}

int mudarStatusLeitura(vector<Livro> &estante, int paginasLidas, string ISBN){
	int indexParaAtualizar = -1;
	int retorno = -1;
	
	for(int i = 0; i < (int)estante.size(); i++){
		if (estante.at(i).ISBN == ISBN){
			indexParaAtualizar = i;
			break;
		}
	}
	
	if(indexParaAtualizar > -1){
		estante.at(indexParaAtualizar).paginasLidas += paginasLidas;
		retorno = 1;
	} else {
		retorno = 0;
	}
	return retorno;
}

void visualizarMinhaEstante(vector<Livro> estante){
	
}

int insertionSort(vector<Livro> &estante){
	int indexNewLivro = estante.size() - 1;
	for(int i = estante.size() - 1; i >= 0; i--){
		if(estante.at(indexNewLivro).ISBN < estante.at(i).ISBN){
			swapLivros(estante, i, indexNewLivro);
			indexNewLivro--;
		}
	}
	return 0;
}

void swapLivros(vector<Livro> &estante, int i, int j){
	Livro aux = estante.at(i);
	estante.at(i) = estante.at(j);
	estante.at(j) = aux;
}
