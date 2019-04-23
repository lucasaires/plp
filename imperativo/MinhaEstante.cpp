#include <iostream>
#include <vector>
#include "livrosdb.cpp"
#include "pesquisas.cpp"
#include "usuariodb.cpp"

using namespace std;

void visualizarMinhaEstante();
int removerLivroMinhaEst();
int adicionaLivroMinhaEst();
int mudarStatusLeitura();
int insertionSort();
void swapLivros();
void printandoLivros(vector<vector<string>> livros);

int adicionaLivroMinhaEst(){
    int idUsuario;
    int idLivro;
    int retorno;
    int opcao; 

    cout << " .::. PrompSkoob .::." << endl;
    cout << " - Adicionando livros a minha estante - " << endl << endl;

    vector<vector<string>> livros;

    cout << "Digite a opção de Pesquisa de sua preferência: " << endl;
    cout << "Pesquisa por Autor[1]: " << endl;
    cout << "Pesquisa por Titulo[2]: " << endl;
    cout << "Pesquisa por Gênero[3]: " << endl;
    cout << "Listar todos os Livros[4]: " << endl;
    cin >> opcao;

    switch (opcao){
        case 1:
            pesquisasAutor();
            break;
        
        case 2:
            pesquisasTitulo();
            break;
        
        case 3:
            pesquisasGenero();
            break;

        case 4:
            listaTodosLivros(livros);
            cout << "Livros cadastrados na biblioteca do PrompSkoob: " << endl << "id - titulo";
            printandoLivros(livros);
    
        default:
            cout << "Opcao inválida" << endl;
            break;
}

    cout << "insira o id do livro que você quer cadastrar na sua estante: ";
    cin >> idLivro;

    idUsuario = obtemID();

    insereEstante(idEstante, idLivro);

    return 0;
}

void printandoLivros(vector<vector<string>> livros){
    int indexIdLivro = 0;
    int indexNomeLivro = 2;

    if(livros.size() == 0){
        cout << "Sem livros cadastrados na biblioteca do PrompSkoob" << endl;
    }

    for(size_t i = 0; i < livros.size(); i++){
        cout << livros.at(i).at(indexIdLivro) << " - " << livros.at(i).at(indexNomeLivro) << endl;
    }
    
}