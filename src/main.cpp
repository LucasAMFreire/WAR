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
#include <limits>

using namespace std;

// Função auxiliar para validar entrada inteira positiva
int lerInteiroPositivo(const string& mensagem) {
    int valor;
    while (true) {
        cout << mensagem;
        if (cin >> valor && valor > 0) {
            break;
        } else {
            cout << "Entrada inválida. Digite um número inteiro positivo." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return valor;
}

// Função auxiliar para validar o índice do exército
int lerIndiceExercito(const string& mensagem, int limite) {
    int indice;
    while (true) {
        cout << mensagem;
        if (cin >> indice && indice >= 1 && indice <= limite) {
            break;
        } else {
            cout << "Número inválido. Escolha um número entre 1 e " << limite << "." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return indice;
}

int main() {
    Campanha campanha;
    Batalhas aux;
    vector<Exercito*> exercitos;
    int cont = 0;
    
    int numExercitos = lerInteiroPositivo("Quantos exercitos deseja criar? ");

    for (int i = 0; i < numExercitos; i++) {
        string nome;
        do {
            cout << "Digite o nome do exercito " << (i + 1) << ": ";
            cin >> ws;
            getline(cin, nome);
            if (nome.empty()) {
                cout << "O nome do exército não pode ser vazio." << endl;
            }
        } while (nome.empty());

        Exercito* novoExercito = new Exercito(nome);
        exercitos.push_back(novoExercito);
        exercitos[i]->adicionaUnidades();
    }

    int opcao;
    do {
        cout << "\nMENU DE BATALHAS\n";
        cout << "1. Iniciar batalha aleatória\n";
        cout << "2. Escolher exércitos para batalhar\n";
        cout << "3. Exibir histórico de batalhas\n";
        cout << "4. Rank\n";
        cout << "0. Sair\n";
        opcao = lerInteiroPositivo("Escolha uma opção: ");
        
        if (opcao > 4) {
            cout << "Opção inválida. Escolha de 0 a 4." << endl;
            continue;
        }

        if (opcao == 2 && exercitos.size() < 2) {
            cout << "Não há exércitos suficientes para batalhar!" << endl;
            continue;
        }

        if (opcao == 1) {
            // Batalha aleatória
            // (mantendo a lógica existente, mas com entradas filtradas)
            int idxA = rand() % exercitos.size();
            int idxB;
            do {
                idxB = rand() % exercitos.size();
            } while (idxA == idxB);
            campanha.simularBatalhas(exercitos[idxA], exercitos[idxB]);
        } else if (opcao == 2) {
            // Escolha de exércitos para batalhar
            int idxA = lerIndiceExercito("Digite o número do primeiro exército: ", exercitos.size());
            int idxB;
            do {
                idxB = lerIndiceExercito("Digite o número do segundo exército: ", exercitos.size());
                if (idxA == idxB) {
                    cout << "Os exércitos devem ser diferentes." << endl;
                }
            } while (idxA == idxB);
            campanha.simularBatalhas(exercitos[idxA - 1], exercitos[idxB - 1]);
        } else if (opcao == 3) {
            campanha.exibirHistorico();
        } else if (opcao == 4) {
            campanha.gerarTabelaDePosicoes(exercitos);
        }
    } while (opcao != 0);

    for (Exercito* e : exercitos) {
        delete e;
    }
    cout << "Programa encerrado!" << endl;
    return 0;
}
