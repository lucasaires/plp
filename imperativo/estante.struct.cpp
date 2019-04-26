#include <iostream>

using namespace std;

struct Estante {
    int idLivro;
    int idUsuario;
    struct Usuario usuario;
    struct Livro livro;
    float nota;
    int situacao;
};