#include "arqarvore.h"
#include <arqpessoa.h>
#include "pessoa.h"
#include <queue>

ArqArvore::ArqArvore(){

    arq = fopen("arvore.dat","r+b");

    if(!arq){
        arq = fopen("arvore.dat","w+b");
        cab = new Cabecalho(arq);
        this->cab->setLivre(-1);
        this->cab->setTopo(0);
        this->cab->setRaiz(-1);
        this->cab->Update(arq);
    }
    else{
        cab = new Cabecalho(arq);
    }

    fseek(arq,0,SEEK_SET);

}

void ArqArvore::insereAux(Node *r, int elemento, int satelite){
    int pos;
    if(!r->buscaPos(elemento,&pos)){
        if(r->ehFolha()){
            for(int i = r->getNumChaves(); i > pos; i--){
                r->setChave(r->getChave(i - 1), i);
                r->setSatelite(r->getSatelite(i - 1), i);
                r->setFilho(r->getFilho(i), i+1);
            }
            r->setChave(elemento,pos);
            r->setSatelite(satelite,pos);
            r->setNumChaves(r->getNumChaves() + 1);
            r->Update(arq);
        }
        else{
            Node *aux = new Node(arq,r->getFilho(pos));
            insereAux(aux,elemento,satelite);

            if(aux->getNumChaves()==Ordem){
                int m, s;
                Node *aux2;
                aux2 = aux->Split(arq,cab,&m,&s);
                r->adicionaDireita(arq,pos,m,s,aux2);

                aux2->Update(arq);
                delete aux2;
            }

            aux->Update(arq);
            delete aux;
        }
    }
}

void ArqArvore::insereArv(int elemento, int satelite){

    fseek(arq,0,SEEK_SET);

    if(cab->getRaiz() == -1){
        Node *no = new Node();
        no->setNumChaves(1);
        no->setChave(elemento,0);
        no->setSatelite(satelite,0);
        no->insereNo(arq,cab);
        cab->setRaiz(no->getMyPos());
        delete no;
    }
    else{
        Node *no = new Node(arq,cab->getRaiz());//Raiz
        insereAux(no,elemento,satelite);

        if(no->getNumChaves() == Ordem){//Realiza o split na raiz
            int m, s;
            Node *x = no->Split(arq,cab,&m,&s);
            Node *Raiz = new Node();

            Raiz->insereNo(arq,cab);

            Raiz->setChave(m,0);
            Raiz->setSatelite(s,0);
            Raiz->setFilho(no->getMyPos(),0);
            Raiz->setFilho(x->getMyPos(),1);
            Raiz->setPai(no->getPai());

            if(Raiz->getPai() == -1){
                cab->setRaiz(Raiz->getMyPos());
            }

            Raiz->setNumChaves(1);

            no->setPai(Raiz->getMyPos());
            x->setPai(Raiz->getMyPos());

            Raiz->Update(arq);
            no->Update(arq);
            x->Update(arq);
            delete Raiz;
            delete x;
        }

        no->Update(arq);
        delete no;
    }

    cab->Update(arq);
}

void ArqArvore::Inicializar(){
    fclose(arq);

    arq = fopen("arvore.dat","w+b");
    cab = new Cabecalho(arq);
    this->cab->setLivre(-1);
    this->cab->setTopo(0);
    this->cab->setRaiz(-1);
    this->cab->Update(arq);
    fclose(arq);
    arq = fopen("arvore.dat","r+b");

}

int ArqArvore::buscaPessoaAux(int matricula, int k){
    int pos;

    Node *aux = new Node(arq,k);

    if(k == -1){
        delete aux;
        return -1;
    }
    if(aux->buscaPos(matricula, &pos)){
        delete aux;
        int auxInt = aux->getSatelite(pos);
        return auxInt;
    }
    else{
        int auxInt = aux->getFilho(pos);
        delete aux;
        return buscaPessoaAux(matricula,auxInt);
    }
}

int ArqArvore::buscaPessoa(int matricula){

    return buscaPessoaAux(matricula,cab->getRaiz());

}

void ArqArvore::removeNo(int pos){
    Node aux;
    aux.Ler(arq,pos);
    aux.setFilho(cab->getLivre(),0);
    cab->setLivre(aux.getMyPos());
    cab->Update(arq);
    aux.Update(arq);
}

void ArqArvore::ImprimeCadastroAux(int k){
    Node *no = new Node(arq,k);

    if(k!=-1){
        ArqPessoa ArqP;
        for(int i = 0; i < no->getNumChaves(); i++){
            ImprimeCadastroAux(no->getFilho(i));
            ArqP.ImprimePessoa(no->getSatelite(i));
        }
        ImprimeCadastroAux(no->getFilho(no->getNumChaves()));
    }

    delete no;
}

void ArqArvore::ImprimeCadastro(){

    if(cab->getRaiz() == -1){
        printf("Sem alunos cadastrados\n");
    }
    else{
        ImprimeCadastroAux(cab->getRaiz());
    }

}

int ArqArvore::getHeightAux(int k){
    if(k!=-1){
        int aux;
        Node *no = new Node(arq,k);
        aux = getHeightAux(no->getFilho(0));
        delete no;
        return 1 + aux;
    }
    return 0;
}

int ArqArvore::getHeight(){
    return this->getHeightAux(cab->getRaiz());
}

void ArqArvore::ImprimeAux(std::queue<int> Fila[], int nivel, int posNode){

    if(posNode == -1){
        return;
    }

    Fila[nivel].push(posNode);

    Node *no = new Node(arq,posNode);

    for(int i = 0; i <= no->getNumChaves(); i++){
        ImprimeAux(Fila,nivel+1,no->getFilho(i));
    }

    delete no;
}

void ArqArvore::Imprime(){

    int i = this->getHeight();

    std::queue<int> Fila[i];

    ImprimeAux(Fila,0,cab->getRaiz());

    Node *aux;

    for(int counter = 0; counter < i; counter++){
        int counter2 = 0;
        while(counter2 < (int) Fila[counter].size()){
            aux = new Node(arq,Fila[counter].front());
            aux->Show();
            Fila[counter].pop();
            delete aux;
        }
        printf("\n");
    }

}

ArqArvore::~ArqArvore(){
    delete cab;
    fclose(arq);
}
