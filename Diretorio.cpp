#include "Diretorio.hpp"
#include "Balde.hpp"
#include <math.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

/// @brief Construtor da classe Diretório
/// @param nbits Número de bits da pseudo-chave
/// @param tamanho_balde Tamanho dos baldes da hash
Diretorio::Diretorio(int nbits, int tamanho_balde)
{
    this->tamanho_balde = tamanho_balde;
    this->profundidade_global = 1;
    this->nbits = nbits;
    for(int i = 0; i < 1<<profundidade_global; i++)
    {
        baldes.push_back(new Balde(profundidade_global, tamanho_balde));
    }
}

/// @brief Calcula o índice do balde em que a chave deve ser inserida a partir do binário
/// @param pschave Pseudo-chave cujo índice do balde será calculado
int Diretorio::getIndiceBalde(string pschave)
{
    return stoi(pschave.substr(0, this->profundidade_global), nullptr, 2);
}

/// @brief Insere uma chave no diretório
/// @param pschave Pseudo-chave a ser inserida
/// @param reinserido Controla se a chave está sendo inserida pela primeira vez ou reinserida por outro processo
void Diretorio::insere(string pschave, bool reinserido)
{
    int indiceBalde = getIndiceBalde(pschave);
    bool log = baldes[indiceBalde]->insere(pschave);
    if(log)
    {
        if(!reinserido)
        {
            //cout << "Pseudo-chave " << pschave << " inserida no balde " << indiceBalde << " d = " << baldes[indiceBalde]->getProfundidade() << endl; 
        }
        else
        {
            //cout << "Pseudo-chave " << pschave << " movida para o balde " << indiceBalde << " d = " << baldes[indiceBalde]->getProfundidade() << endl; 
        }
    }
    else
    {
        divideBalde(indiceBalde);
        insere(pschave, reinserido);
    }
}

/// @brief Verifica se a pseudo-chave existe no diretório
/// @param pschave Pseudo-chave a ser buscada no diretório
bool Diretorio::busca(string pschave)
{
    int indiceBalde = getIndiceBalde(pschave);
    if(indiceBalde < 1<<profundidade_global)
    {
        return baldes[indiceBalde]->busca(pschave);
    }
    else
    {
        cout << "Chave não encontrada!" << endl;
        return false;
    }
}

/// @brief Duplica o diretório
void Diretorio::duplicaDir()
{
    for(int i = 0; i < 1<<profundidade_global; i++)
    {
        baldes.push_back(baldes[i]);
    }
    profundidade_global++;
}

/// @brief Divide o balde
/// @param indiceBalde Índice do balde a ser dividido
void Diretorio::divideBalde(int indiceBalde)
{
    int novaProfundidade = baldes[indiceBalde]->aumentarProfundidade();
    int indicePar = indiceBalde^(1<<(novaProfundidade-1));
    int tamDir = getTamDir();
    int indiceDiff;
    vector<string> aux;
    vector<string>::iterator it;

    if(novaProfundidade > profundidade_global)
        duplicaDir();
    
    baldes[indicePar] = new Balde(novaProfundidade, tamanho_balde);
    aux = baldes[indiceBalde]->copiaBalde();
    baldes[indiceBalde]->limpaBalde();

    indiceDiff = 1<<novaProfundidade;

    for(int i = indicePar - indiceDiff; i >= 0; i-=indiceDiff)
        baldes[i] = baldes[indicePar];
    
    for(int i = indicePar + indiceDiff; i < tamDir; i+=indiceDiff)
        baldes[i] = baldes[indicePar];

    for(it = aux.begin(); it != aux.end(); it++)
        insere((*it), 1);
}

/// @brief Realiza a impressão do diretório
void Diretorio::imprimeDiretorio()
{
    cout << "Imprimindo diretorio..." << endl;
    cout << "Profundidade global: " << profundidade_global << endl;
    for(vector<Balde*>::iterator it = baldes.begin(); it != baldes.end(); it++)
    {
        cout << "Balde de indice " << it - baldes.begin() << " e profundidade local " << (*it)->getProfundidade() << ":" << endl;
        (*it)->imprimeBalde();
    }
}