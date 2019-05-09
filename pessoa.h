#ifndef PESSOA_H
#define PESSOA_H


//Verifica se o CPF/Telefone/Celular é valido
bool isValid(char *str);

class Pessoa{
private:
    int  Matricula;		//**Obrigatório** Matricula da pessoa
    char Nome[100];		//**Obrigatório** Nome da pessoa
    char Sexo;			//**Obrigatório** Sexo da pessoa
    int  CPF[2];		//**Obrigatório** CPF no formato xxxxxxxxx-xx, apenas x faz parte do array
    char RG[10];		//**Obrigatório** RG
    char Endereco[100]; //**Obrigatório** Endereço da pessoa
    int  Nascimento[3];	//**Obrigatório** Data de nascimento no formato xx/xx/xxxx
    char Email[100]; 	//Endereço de e-mail da pessoa
    int  Telefone[3];	//Telefone no formato xx-xxxx-xxxx, apenas x faz parte do array
    int  Celular[3];	//Celular no formato xx-xxxx-xxxx, apenas x faz parte do array

    int MyPos;
    int Next;

public:
    Pessoa();
    Pessoa(char s[]);
    void Show();
    void SetMatricula(int m);
    void SetNome(char s[]);
    void SetSexo(char s);
    void SetCPF(char s[]);
    void SetRG(char s[]);
    void SetEndereco(char s[]);
    void SetNascimento(char s[]);
    void SetEmail(char s[]);
    void SetTelefone(char s[]);
    void SetCelular(char s[]);
    void SetNext(int a);
    void SetMyPos(int a);
    int GetMatricula(){return Matricula;}
    int GetNext(){return Next;}
    int GetMyPos(){return MyPos;}
    void Editar();
    ~Pessoa();
};

#endif // PESSOA_H
