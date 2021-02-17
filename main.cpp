#include <iostream>
#include <iomanip>
#include <string>
#include "Balde.hpp"
#include "Diretorio.hpp"

using namespace std;

/// @brief Realiza o teste com pseudo-chaves aleatórias
/// @param dir Ponteiro para o diretório
/// @param nbits Número de bits das pseudo-chaves
/// @param n Número de inserções a serem realizadas
void testeChavesAleatorias(Diretorio *dir, int nbits, int n)
{
    cout << "Teste com " << n << " pseudo-chaves aleatorias:" << endl;
    string pschave = "";
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < nbits; j++)
        {
            pschave.push_back('0' + rand() % 2);
        }
        if(!dir->busca(pschave))
        {
            dir->insere(pschave, 0);
        }
        else
        {
            i--;//Se foi gerada uma chave já existente, decrementa o contador para uma nova tentativa
        }
        pschave.erase(pschave.begin(), pschave.end());
    }
}

/// @brief Realiza o teste com pseudo-chaves nbits/2 bits iniciais iguais
/// @param dir Ponteiro para o diretório
/// @param nbits Número de bits das pseudo-chaves
/// @param n Número de inserções a serem realizadas
void testeChavesPadronizadas(Diretorio *dir, int nbits, int n)
{
    cout << "Teste com " << n << " pseudo-chaves padronizadas nos nbits/2 primeiros bits:" << endl;
    string pschave = "";
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < nbits/2; j++)
        {
            pschave.push_back('1');
        }
        for(int j = 0; j < nbits - nbits/2; j++)
        {
            pschave.push_back('0' + rand() % 2);
        }
        dir->insere(pschave, 0);
        pschave.erase(pschave.begin(), pschave.end());
    }
}

int menu()
{
    int opcao;
    cout << "Escolha a opcao desejada:" << endl;
    cout << "1 - Teste com N chaves aleatórias." << endl;
    cout << "2 - Teste com N chaves padronizadas." << endl;
    cout << "0 - Sair." << endl;
    cin >> opcao;
    while(opcao < 0 || opcao > 2)
    {   
        cout << "Opcao invalida!" << endl;
        cout << "Escolha a opcao desejada:" << endl;
        cout << "1 - Teste com N chaves aleatórias." << endl;
        cout << "2 - Teste com N chaves padronizadas." << endl;
        cout << "0 - Sair." << endl;
        cin >> opcao;
    }
    return opcao;
}

int main(int argc, char * argv[])
{
    srand (time(NULL));
    int nbits, tamanho_balde, n, opcao;
    string pschave = "";
    cout << "Digite o numero de bits: ";
    cin >> nbits;
    cout << "Digite o tamanho do balde: ";
    cin >> tamanho_balde;
    cout << "Digite o numero de insercoes: ";
    cin >> n;

    Diretorio *dir = new Diretorio(nbits, tamanho_balde);

    opcao = menu();

    while(opcao != 0)
    {
        if(opcao == 1)
            testeChavesAleatorias(dir, nbits, n);
        else
            testeChavesPadronizadas(dir, nbits, n);
        dir->imprimeDiretorio();
        cout << "Fator de carga: " << setprecision(5) << double(n)/double(dir->getTamDir()*tamanho_balde) << endl; 
        opcao = menu();  
    }

    return 0;
}