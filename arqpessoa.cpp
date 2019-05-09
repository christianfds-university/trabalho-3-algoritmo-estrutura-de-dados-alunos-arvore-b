#include "arqpessoa.h"
#include "pessoa.h"
#include <stdlib.h>
#include <stdio.h>

ArqPessoa::ArqPessoa(){

    arq = fopen("pessoas.dat","r+b");

    if(!arq){
        arq = fopen("pessoas.dat","w+b");
        cab = new Cabecalho(arq);
        this->cab->setLivre(-1);
        this->cab->setTopo(0);
        this->cab->Update(arq);
    }
    else{
        cab = new Cabecalho(arq);
    }

    fseek(arq,0,SEEK_SET);

}

void ArqPessoa::Inicializar(){
    fclose(arq);

    arq = fopen("pessoas.dat","w+b");
    cab = new Cabecalho(arq);
    this->cab->setLivre(-1);
    this->cab->setTopo(0);
    this->cab->Update(arq);

    fclose(arq);
    arq = fopen("pessoas.dat","r+b");

    fseek(arq,0,SEEK_SET);
}

int ArqPessoa::InserePessoa(Pessoa *p){

    int aux;

    if( cab->getLivre() != -1){

        Pessoa Paux;
        fseek(arq,sizeof(Cabecalho) + sizeof(Pessoa)*cab->getLivre(),SEEK_SET);

        fread(&Paux,sizeof(Pessoa),1,arq);
        cab->setLivre(p->GetNext());

        fseek(arq,sizeof(Cabecalho) + sizeof(Pessoa)*cab->getLivre(),SEEK_SET);
        aux = cab->getLivre();

    }
    else{
        fseek(arq,sizeof(Cabecalho) + sizeof(Pessoa)*cab->getTopo(),SEEK_SET);
        aux = cab->getTopo();
    }

    p->SetMyPos(aux);
    fwrite(p,sizeof(Pessoa),1,arq);

    cab->setTopo(cab->getTopo() + 1);

    cab->Update(arq);

    return aux;
}

int ArqPessoa::InserePessoa(Pessoa *p, int a){
    fseek(arq,sizeof(Cabecalho) + sizeof(Pessoa)*a,SEEK_SET);
    fwrite(p,sizeof(Pessoa),1,arq);
    return p->GetMyPos();
}

void ArqPessoa::ImprimePessoa(int a){

    Pessoa p;

    fseek(arq,sizeof(Cabecalho) + sizeof(Pessoa)*a,SEEK_SET);

    fread(&p,sizeof(Pessoa),1,arq);

    p.Show();
}

void ArqPessoa::EditarPessoa(int a){
    Pessoa p;

    fseek(arq,sizeof(Cabecalho) + sizeof(Pessoa)*a,SEEK_SET);

    fread(&p,sizeof(Pessoa),1,arq);

    p.Editar();

    InserePessoa(&p,p.GetMyPos());

}

void ArqPessoa::RemovePessoa(int a){
    Pessoa p;

    fseek(arq,sizeof(Cabecalho) + sizeof(Pessoa)*a,SEEK_SET);
    fread(&p,sizeof(Pessoa),1,arq);

    p.SetNext(cab->getLivre());
    cab->setLivre(p.GetMyPos());

    fwrite(&p,sizeof(Pessoa),1,arq);
    cab->Update(arq);

}

ArqPessoa::~ArqPessoa(){

    cab->Update(arq);
    delete cab;

    fclose(this->arq);

}
