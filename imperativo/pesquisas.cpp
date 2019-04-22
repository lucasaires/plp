#include <iostream>
#include <sqlite3.h>
#include <vector>
#include "constantes.cpp"

using namespace std;

void pesquisasAutor() {
    string autor;
    cout << "Digite o nome do Autor: " << endl;

    cin >> autor;
    /*
    * Consultar no banco de dados
    * cout << (pesquisaAutor(AUTOR, autor )) >> endl;
    */

}

void pesquisasTitulo() {
    string titulo;
    cout << "Digite o nome do Titulo: " << endl; 

    cin >> titulo;
    /*
    * Consultar no banco de dados
    * cout << (pesquisaTitulo(TITULO, titulo )) >> endl;
    */

}

void pesquisasGenero() {
    int genero;
    cout << "Digite o nome do gênero: " << endl;

    cin >> genero;

    /*
    * Consultar no banco de dados
    * cout << (pesquisaTitulo(GENERO, genero )) >> endl;
    */
    
}