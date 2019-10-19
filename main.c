#include <stdio.h>
#include <stdlib.h>

struct login{
    char usuario[100];
    char senha[100];
    float salario;
    float saldo;
};

struct data{
    int dia;
    int mes;
    int ano;
};

struct receita{
    float salario;
    float adiantamento_salario;
    float comissao;
    float diversos;
};

struct gasto{
    float moradia;
    float estudo;
    float conducao;
    float alimentacao;
    float trabalho;
    float diversos;
};

struct carteira{
    struct login login;
    struct data data;
    struct receita receita;
    struct gasto gasto;
};


int main(void){
    printf("Hello World!\n");
    return 0;
}