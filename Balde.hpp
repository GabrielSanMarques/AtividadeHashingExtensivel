#pragma once
#include <vector>
#include <string>

using namespace std;

class Balde
{
    private:
        int profundidade, tamanho;
        vector<string> pschaves;
    public:
        Balde(int profundidade, int tamanho);
        bool insere(string pschave);
        bool busca(string pschave);  
        int aumentarProfundidade();
        vector<string> copiaBalde();
        void imprimeBalde();
        void limpaBalde()       {pschaves.clear();};
        int getProfundidade()   {return profundidade;};
        int baldeCheio()        {return pschaves.size() == tamanho;};
};