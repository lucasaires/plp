#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Usuario {
    int id;
    string nome;
    string email;
    string senha;
    int ficcao;
    int naoFiccao;
    int romance;
    int horror;
    int biografia;
    vector<struct Estante> estantes;
};