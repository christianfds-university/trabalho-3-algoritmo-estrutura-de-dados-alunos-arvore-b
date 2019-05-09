#include "pessoa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cctype>

Pessoa::Pessoa(){
}

//Converte uma string do arquivo de inicialização para o formato pessoa
Pessoa::Pessoa(char s[]){

    char *a;
    int i;

    for(i = 0; i < 300; i++){

        if(s[i] == ';' || s[i] == '\n'){
            s[i] = '\0';
        }

    }

    a = s;

    sscanf(a, "%d", &(this->Matricula));

    for(; (*a) != '\0'; a++);
    a++;
    this->SetNome(a);

    for(; (*a) != '\0'; a++);
    a++;
    this->SetSexo(*a);

    for(; (*a) != '\0'; a++);
    a++;
    this->SetCPF(a);

    for(; (*a) != '\0'; a++);
    a++;
    this->SetRG(a);

    for(; (*a) != '\0'; a++);
    a++;
    this->SetTelefone(a);

    for(; (*a) != '\0'; a++);
    a++;
    this->SetCelular(a);

    for(; (*a) != '\0'; a++);
    a++;
    this->SetEmail(a);

    for(; (*a) != '\0'; a++);
    a++;
    this->SetEndereco(a);

    for(; (*a) != '\0'; a++);
    a++;
    this->SetNascimento(a);

    this->Next = -1;
}

//Imprime as informações de uma pessoa
void Pessoa::Show(){

    printf("%s\n", this->Nome);
    printf("Matricula: %d\n", this->Matricula);
    printf("Sexo: %c                | Nascimento: %d/%d/%d\n", this->Sexo, this->Nascimento[0], this->Nascimento[1], this->Nascimento[2]);
    printf("CPF: %09d-%02d      | Endereço: %s\n", this->CPF[0] , this->CPF[1], this->Endereco);
    printf("RG:  %9s         | Email: %s\n", this->RG, this->Email);
    printf("Telefone: %02d-%04d-%04d | Celular: %02d-%04d-%04d\n\n", this->Telefone[0], this->Telefone[1], this->Telefone[2], this->Celular[0], this->Celular[1], this->Celular[2]);
}

//SETTER's
void Pessoa::SetMatricula(int m){
    this->Matricula = m;
}
void Pessoa::SetNome(char s[]){
    int i;

    for(i = 0; i < 300; i++){

        if(s[i] == ';' || s[i] == '\n'){
            s[i] = '\0';
        }

    }

    strcpy(this->Nome, s);
}
void Pessoa::SetSexo(char s){
    this->Sexo = s;
}
void Pessoa::SetCPF(char s[]){
    int i;

    for(i = 0; i < 300; i++){

        if(s[i] == ';' || s[i] == '\n'){
            s[i] = '\0';
        }

    }
    sscanf(s, "%d-%d", this->CPF+0, this->CPF+1);
}
void Pessoa::SetRG(char s[]){
    int i;

    for(i = 0; i < 300; i++){

        if(s[i] == ';' || s[i] == '\n'){
            s[i] = '\0';
        }

    }
    strcpy(this->RG,s);
}
void Pessoa::SetEndereco(char s[]){
    int i;

    for(i = 0; i < 300; i++){

        if(s[i] == ';' || s[i] == '\n'){
            s[i] = '\0';
        }

    }
    strcpy(this->Endereco, s);
}
void Pessoa::SetNascimento(char s[]){
    int i;

    for(i = 0; i < 300; i++){

        if(s[i] == ';' || s[i] == '\n'){
            s[i] = '\0';
        }

    }
    sscanf(s, "%d/%d/%d", this->Nascimento+0, this->Nascimento+1, this->Nascimento+2);
}
void Pessoa::SetEmail(char s[]){
    int i;

    for(i = 0; i < 300; i++){

        if(s[i] == ';' || s[i] == '\n'){
            s[i] = '\0';
        }

    }
    strcpy(this->Email, s);
}
void Pessoa::SetTelefone(char s[]){
    int i;

    for(i = 0; i < 300; i++){

        if(s[i] == ';' || s[i] == '\n'){
            s[i] = '\0';
        }

    }
    sscanf(s,"%d-%d-%d", this->Telefone+0, this->Telefone+1, this->Telefone+2);
}
void Pessoa::SetCelular(char s[]){
    int i;

    for(i = 0; i < 300; i++){

        if(s[i] == ';' || s[i] == '\n'){
            s[i] = '\0';
        }

    }
    sscanf(s,"%d-%d-%d", this->Celular+0, this->Celular+1, this->Celular+2);
}
void Pessoa::SetNext(int a){
    this->Next = a;
}
void Pessoa::SetMyPos(int a){
    this->MyPos = a;
}

//Verifica se o CPF/Telefone/Celular é valido
bool isValid(char *str){
    while((*str)!='\0' && (*str) != '\n'){
        if(isdigit(*str) == false)
            if(*str != '-')
                return false;
        str++;
    }
    return true;
}

void Pessoa::Editar(){
    this->Show();
    int op;
    char strAux[100], charAux;

    system("clear");

    this->Show();

    printf("| %d | %-s\n", 1, "Nome*");
    printf("| %d | %-s\n", 2, "Sexo*");
    printf("| %d | %-s\n", 3, "CPF*");
    printf("| %d | %-s\n", 4, "RG*");
    printf("| %d | %-s\n", 5, "Telefone");
    printf("| %d | %-s\n", 6, "Celular");
    printf("| %d | %-s\n", 7, "E-mail");
    printf("| %d | %-s\n", 8, "Endereço*");
    printf("| %d | %-s\n", 9, "Data de nascimento*");

    printf("Qual informação você deseja alterar? ");
    scanf("%d", &op);
    getchar_unlocked();
    switch (op) {
    case 1:
        do{
            printf("Novo nome*:");
            fgets(strAux,100,stdin);
        }while(strlen(strAux) == 0);
        SetNome(strAux);
        break;
    case 2:
        do{
            printf("Novo sexo* (M/F):");
            charAux = getchar();
            getchar();
        }while( charAux != 'm' && charAux != 'M' && charAux != 'f' && charAux != 'F');
        SetSexo(charAux);
        break;
    case 3:
        do{
            printf("Novo CPF* (xxxxxxxxxx-xx):");
            fgets(strAux,100,stdin);
            printf("%d", isValid(strAux));
        }while(!isValid(strAux));
        SetCPF(strAux);
        break;
    case 4:
        do{
        printf("Novo RG*:");
        fgets(strAux,100,stdin);
        }while(strAux[0] == '\n' || strAux[0] == '\0');
        SetRG(strAux);
        break;
    case 5:
        do{
            printf("Novo Telefone (xx-xxxx-xxxx):");
            fgets(strAux,100,stdin);
        }while(!isValid(strAux));

        if(strlen(strAux) == 0)
            strcpy(strAux,"0-0-0");

        SetTelefone(strAux);
        break;
    case 6:
        do{
            printf("Novo Celular (xx-xxxx-xxxx):");
            fgets(strAux,100,stdin);
        }while(!isValid(strAux));

        if(strlen(strAux) == 0)
            strcpy(strAux,"0-0-0");

        SetCelular(strAux);
        break;
    case 7:
        printf("Novo E-mail:");
        fgets(strAux,100,stdin);
        SetEmail(strAux);
        break;
    case 8:
        do{
            printf("Novo Endereço*:");
            fgets(strAux,100,stdin);
        }while(strAux[0] == '\0' || strAux[0] == '\n');
        SetEndereco(strAux);
        break;
    case 9:
        printf("Nova data de nascimento* (DD/MM/AAAA):");
        fgets(strAux,100,stdin);
        SetNascimento(strAux);
        break;
    default:
        break;
    }
}

Pessoa::~Pessoa(){
}
