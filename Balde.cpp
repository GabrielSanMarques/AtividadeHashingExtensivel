#include "Balde.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

/// @brief Construtor da classe Balde
/// @param profundidade Profundidade do balde
/// @param tamanho Tamanho do balde
Balde::Balde(int profundidade, int tamanho)
{
    this->profundidade = profundidade;
    this->tamanho = tamanho;
}

/// @brief Insere uma pseud-chave no balde ou retorna falso se o balde está cheio
/// @param pschave Pseudo-chave a ser inserida no balde
bool Balde::insere(string pschave)
{
    if(baldeCheio())
    {
        return false;
    }
    pschaves.push_back(pschave);
    return true;
}

/// @brief Aumenta a profundidade do balde e retorna a nova profundidade
int Balde::aumentarProfundidade()
{
    profundidade++;
    return profundidade;
}

/// @brief Verifica se uma pseudo-chave está no balde
/// @param pschave Pseudo-chave a ser buscada no balde
bool Balde::busca(string pschave)
{
    vector<string>::iterator it;
    it = find(pschaves.begin(), pschaves.end(), pschave);
    if(it != pschaves.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

/// @brief Copia o balde e retorna a cópia
vector<string> Balde::copiaBalde()
{
    vector<string> aux(pschaves.begin(), pschaves.end());
    return aux;
}

/// @brief Realiza a impressão do balde
void Balde::imprimeBalde()
{
    for(int i = 0; i < tamanho; i++)
    {
        if(i < pschaves.size())
            cout << i << " - " << pschaves[i] << endl;
        else
            cout << i << " - " << endl;
    }
}