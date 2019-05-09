#ifndef ARQARVORE_H
#define ARQARVORE_H
#include <stdlib.h>
#include <stdio.h>
#include <queue>
#define Ordem 5

class ArqArvore{

    class Cabecalho{
    private:
        int Topo;
        int Livre;
        int Raiz;

    public:
        //Inicializa as informações do cabecalho
        Cabecalho(FILE *arq){
            fseek(arq,0,SEEK_SET);
            fread(this,sizeof(Cabecalho),1,arq);
        }

        //Atualiza as informações no arquivo
        void Update(FILE *arq){
            fseek(arq,0,SEEK_SET);
            fwrite(this,sizeof(Cabecalho),1,arq);
        }

        //Imprime o conteúdo do cabecalho
        void Imprimir(){
            printf("\nTopo: %d\nLivre: %d\nRaiz: %d\n\n", Topo, Livre, Raiz);
        }

        //GETTER's
        int getTopo(){
            return Topo;
        }
        int getLivre(){
            return Livre;
        }
        int getRaiz(){
            return Raiz;
        }

        //SETTER's
        void setTopo(int a){
            Topo = a;
        }
        void setLivre(int a){
            Livre = a;
        }
        void setRaiz(int a){
            Raiz = a;
        }

        ~Cabecalho(){}
    };


    class Node{
    private:
        int MyPos;
        int Pai;
        int NumChaves;
        int Chave[Ordem];
        int Satelite[Ordem];
        int Filho[Ordem+1];

    public:
        Node(){
            MyPos = -1;
            Pai = -1;
            NumChaves = 0;
            for(int i = 0; i <= Ordem; i++)
                Filho[i] = -1;
        }
        Node(FILE *arq, int pos){
            Ler(arq,pos);
        }
        void Ler(FILE *arq, int pos){
            fseek(arq,sizeof(Cabecalho) + sizeof(Node)*pos,SEEK_SET);
            fread(this,sizeof(Node),1,arq);
        }

        void Show(){
//            printf("%d:%d", this->getPai(), this->getMyPos());
            printf("[");
            for(int i = 0; i < this->getNumChaves(); i++)
                if(i==this->getNumChaves() - 1)
                    printf(" %d ", this->getChave(i));
                else
                    printf(" %d,", this->getChave(i));

            printf("]");
//            printf("[");
//            for(int i = 0; i <= this->getNumChaves(); i++)
//                if(i==this->getNumChaves())
//                    printf(" %d ", this->getFilho(i));
//                else
//                    printf(" %d,", this->getFilho(i));
//            printf("]");
        }

        //Escreve um nó no arquivo
        int insereNo(FILE *arq, Cabecalho *cab){
            int r;
            if(cab->getLivre() == -1){
                setMyPos(cab->getTopo());
                Escrever(arq,cab->getTopo());
                r = cab->getTopo();
                cab->setTopo(cab->getTopo()+1);
            }
            else{
                Node aux;
                aux.Ler(arq,cab->getLivre());
                Escrever(arq,cab->getLivre());
                r = cab->getLivre();
                cab->setLivre(aux.getFilho(0));
            }

            cab->Update(arq);

            return r;
        }

        void Escrever(FILE *arq, int pos){
            fseek(arq,sizeof(Cabecalho) + sizeof(Node)*pos,SEEK_SET);
            fwrite(this,sizeof(Node),1,arq);
        }
        void Update(FILE *arq){
            fseek(arq,sizeof(Cabecalho) + sizeof(Node)*this->MyPos,SEEK_SET);
            fwrite(this,sizeof(Node),1,arq);
        }
        bool ehFolha(){
            return this->getFilho(0)== -1;
        }

        //Realiza o split de um nó
        Node *Split(FILE *arq, Cabecalho *cab, int *mediana, int *satelite){
            int q = Ordem/2;

            *mediana = this->getChave(q);
            *satelite = this->getSatelite(q);

            Node *aux = new Node();

            aux->setNumChaves( this->getNumChaves() - q - 1);
            this->setNumChaves(q);

            for(int i = 0; i < aux->getNumChaves(); i++){
                aux->setChave(this->getChave(q+i+1),i);
                aux->setSatelite(this->getSatelite(q+i+1),i);
                aux->setFilho(this->getFilho(q+i+2),i+1);
            }

//FILHO DO AUX 0 errado aqui
            aux->setPai(this->getPai());
            this->Update(arq);
            aux->insereNo(arq,cab);
            return aux;
        }

        //Verifica uma chave existe dentro de um nó, retornando true ou false e a posição da chave na variável pos
        bool buscaPos(int info, int *pos){
            for((*pos) = 0; (*pos) < this->getNumChaves(); (*pos)++)
                if(info == this->getChave(*pos))
                    return true;
                else if(info < this->getChave(*pos))
                    break;
            return false;
        }

        //Resulta de um split
        void adicionaDireita(FILE *arq, int pos, int elemento, int satelite, Node *p){
            for(int i = this->getNumChaves(); i > pos; i--){
                this->setChave(this->getChave(i - 1), i);
                this->setSatelite(this->getSatelite(i - 1), i);
                this->setFilho(this->getFilho(i),i+1);
            }

            this->setChave(elemento,pos);
            this->setSatelite(satelite,pos);
//            if(this->getNumChaves() > 0 && this->ehFolha()){
//                this->setFilho(p->getMyPos(),0);
//            }
//            else{
                this->setFilho(p->getMyPos(),pos+1);
                this->setNumChaves(this->getNumChaves() + 1);
//            }

            p->setPai(this->getMyPos());
            this->Update(arq);
            p->Update(arq);
        }

        //GETTER's
        int getMyPos(){
            return MyPos;
        }
        int getPai(){
            return Pai;
        }
        int getNumChaves(){
            return NumChaves;
        }
        int getChave(int i){
            return Chave[i];
        }
        int getSatelite(int i){
            return Satelite[i];
        }
        int getFilho(int i){
            return Filho[i];
        }

        //SETTER's
        void setMyPos(int a){
            MyPos = a;
        }
        void setPai(int a){
            Pai = a;
        }
        void setNumChaves(int a){
            NumChaves = a;
        }
        void setChave(int a, int pos){
            Chave[pos] = a;
        }
        void setSatelite(int a, int pos){
            Satelite[pos] = a;
        }
        void setFilho(int a, int pos){
            Filho[pos] = a;
        }

        ~Node(){

        }
    };

private:
    FILE *arq;
public:
    Cabecalho *cab;

public:
    ArqArvore();
    void Inicializar();
    void ImprimeCadastroAux(int k);
    void ImprimeAux(std::queue<int> Pilha[], int nivel, int posNode);
    void ImprimeCadastro();
    void Imprime();
    int getHeightAux(int k);
    int getHeight();
    void insereAux(Node *r, int elemento, int satelite);
    void insereArv(int elemento, int satelite);
    int buscaPessoaAux(int matricula, int k);
    int buscaPessoa(int matricula);
    void removeNo(int pos);
    ~ArqArvore();
};

#endif // ARQARVORE_H
