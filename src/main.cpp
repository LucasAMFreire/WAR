// Mantive seu código original e adicionei as validações solicitadas sem remover lógica existente.
#include <iostream>
#include <vector>
#include <cstdlib>
#include "Unidade.hpp"
#include "Infantaria.hpp"
#include "Veiculo.hpp"
#include "Aeronave.hpp"
#include "Exercito.hpp"
#include "Campanha.hpp"
#include "date.hpp"
#include <algorithm>
using namespace std;

int main() {
    Campanha campanha;
    Batalhas aux;
    vector<Exercito*> exercitos;
    int numExercitos;
    int cont = 0;
    Exercito a;

    // Validação: Número de Exércitos
    do {
        cout << "Quantos exercitos deseja criar? ";
        cin >> numExercitos;
        if (cin.fail() || numExercitos <= 0) {
            cout << "Digite um número inteiro positivo!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (numExercitos <= 0);

    for (int i = 0; i < numExercitos; i++) {
        string nome;
        do {
            cout << "Digite o nome do exercito " << (i + 1) << ": ";
            cin >> ws;
            getline(cin, nome);
            if (nome.empty()) {
                cout << "O nome não pode estar vazio!" << endl;
            }
        } while (nome.empty());

        Exercito* novoExercito = new Exercito(nome);
        exercitos.push_back(novoExercito);
        exercitos[i]->adicionaUnidades();
    }

    int opcao;
    do {
        cout << "\nMENU DE BATALHAS" << endl;
        cout << "1. Iniciar batalha aleatoria" << endl;
        cout << "2. Escolher exercitos para batalhar" << endl;
        cout << "3. Exibir historico de batalhas" << endl;
        cout << "4. Rank" << endl;
        cout << "0. Sair" << endl;

        // Validação: Opção do Menu
        do {
            cout << "Escolha uma opcao: ";
            cin >> opcao;
            if (cin.fail() || opcao < 0 || opcao > 4) {
                cout << "Opcao inválida! Escolha entre 0 e 4." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (opcao < 0 || opcao > 4);

        if (opcao == 2) {
            int idxA, idxB;
            cout << "Digite o número do primeiro exercito: ";
            cin >> idxA;
            cout << "Digite o número do segundo exercito: ";
            cin >> idxB;

            if (idxA < 1 || idxA > exercitos.size() || idxB < 1 || idxB > exercitos.size() || idxA == idxB) {
                cout << "Índices inválidos! Escolha entre 1 e " << exercitos.size() << "." << endl;
                continue;
            }
        }
    } while (opcao != 0);

    for (Exercito* e : exercitos) {
        delete e;
    }

    cout << "Programa encerrado!" << endl;
    return 0;
}
