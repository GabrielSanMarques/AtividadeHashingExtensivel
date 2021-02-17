#pragma once
#include <vector>
#include <string>
#include "Balde.hpp"

using namespace std;

class Diretorio
{
    private:
        int profundidade_global, tamanho_balde, nbits;
        vector<Balde*> baldes;
        void divideBalde(int indiceBalde);
        void duplicaDir();
        int getIndiceBalde(string pschave);
    public:
        Diretorio(int nbits, int tamanho_balde);
        void imprimeDiretorio();
        void insere(string pschave, bool reinserido);
        bool busca(string pschave);
        int getTamDir(){return baldes.size();};
};