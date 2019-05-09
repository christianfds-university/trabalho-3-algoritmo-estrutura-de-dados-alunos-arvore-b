#ifndef ARQPESSOA_H
#define ARQPESSOA_H
#include "pessoa.h"
#include <stdlib.h>
#include <stdio.h>

class ArqPessoa{

    class Cabecalho{
    private:
        int Topo;
        int Livre;
    public:
        //Inicializa o cabeçalho
        Cabecalho(FILE *arq){
            fseek(arq,0,SEEK_SET);
            fread(this,sizeof(Cabecalho),1,arq);
        }

        //Atualiza as informações do cabeçalho
        void Update(FILE *arq){
            fseek(arq,0,SEEK_SET);
            fwrite(this,sizeof(Cabecalho),1,arq);
        }

        //Imprime as informações do cabeçalho
        void Imprimir(){
            printf("Topo: %d\nLivre: %d\n", Topo, Livre);
        }

        //SETTER's
        void setTopo(int a){
            this->Topo = a;
        }
        void setLivre(int a){
            this->Livre = a;
        }

        //GETTER's
        int getTopo(){
            return Topo;
        }
        int getLivre(){
            return Livre;
        }

        ~Cabecalho(){}
    };

private:
    FILE *arq;
    Cabecalho *cab;

public:
    ArqPessoa();
    void Inicializar();
    int InserePessoa(Pessoa *p);
    int InserePessoa(Pessoa *p, int a);
    void EditarPessoa(int a);
    void ImprimePessoa(int a);
    void RemovePessoa(int a);
    ~ArqPessoa();
};

#endif // ARQPESSOA_H
