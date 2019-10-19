#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct login{
    char usuario[100];
    char senha[100];
    float salario;
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
    float saldo;
    float aplicacao;
};

void criarCarteira(){
    struct carteira c; //declara a struct

    printf("Insira um nome de usuario para a nova carteira: ");
    scanf("%s", c.login.usuario);

    printf("Crie uma senha para a nova carteira: ");
    scanf("%s", c.login.senha);
 
    printf("Digite seu salario: ");
    scanf("%f", &c.login.salario);

    printf("Digite o saldo inicial da carteira: ");
    scanf("%f", &c.saldo);

    char* ext = ".txt";

    char nomeArq[strlen(c.login.usuario)+strlen(ext)+1];

    snprintf( nomeArq, sizeof( nomeArq ), "%s%s", c.login.usuario, ext );//forma a string variavel + .txt

    if( access( nomeArq, R_OK|W_OK ) != -1 ) { //verifica se um arquivo com o nome digitado existe
        printf("\nCarteira ja existe. Digite outro usuario\n\n");
    }
    else {
        FILE* fw = fopen(nomeArq, "w");

        fprintf(fw, "%s\n", c.login.usuario);
        fprintf(fw, "%s\n", c.login.senha);
        fprintf(fw, "%.2f\n", c.login.salario);
        fprintf(fw, "%.2f\n", c.saldo);

        fclose(fw);

        printf("\nCarteira criada com sucesso!\n\n");
    }

}

void verificaLogin(){
    int del;
    char usuario[100];
    char senha[100];
    printf("\nLogin: ");
    scanf("%s", usuario);
    printf("\nSenha: ");
    scanf("%s", senha);
    char* ext = ".txt";

    char nomeArq[strlen(usuario)+strlen(ext)+1];

    snprintf( nomeArq, sizeof( nomeArq ), "%s%s", usuario, ext );//formaa string variavel + .txt

    if( access( nomeArq, R_OK|W_OK ) != -1 ) { // verifica se a carteira com o nome digitado existe
        char senhaArq[100];
        FILE* fr = fopen(nomeArq, "r");
        for(int i = 0; i < 2; i++){
            fscanf(fr, "%s", senhaArq);
        }
        fclose(fr);
        if ( strcmp(senha, senhaArq) == 0){
        
            printf("\nLogin efetuado com sucesso.\n\n");
        }
        else{
            printf("\nA senha digitada não coincide com a senha da carteira. Verifique-a\n\n");
        }
    }
    else {
        printf("\nCarteira nao encontrada. Verifique o usuario digitado.\n\n");
    }
}
}

void deletarCarteira(){
    int del;
    char usuario[100];
    char senha[100];
    printf("\nDigite o login da carteira que deseja deletar: ");
    scanf("%s", usuario);
    printf("\nDigite a senha da carteira que deseja deletar: ");
    scanf("%s", senha);
    char* ext = ".txt";

    char nomeArq[strlen(usuario)+strlen(ext)+1];

    snprintf( nomeArq, sizeof( nomeArq ), "%s%s", usuario, ext );//formaa string variavel + .txt

    if( access( nomeArq, R_OK|W_OK ) != -1 ) { // verifica se a carteira com o nome digitado existe
        char senhaArq[100];
        FILE* fr = fopen(nomeArq, "r");
        for(int i = 0; i < 2; i++){
            fscanf(fr, "%s", senhaArq);
        }
        fclose(fr);
        if ( strcmp(senha, senhaArq) == 0){
            del = remove(nomeArq); // remove o arquivo com determinado nome
            printf("%d", del);
            printf("\nCarteira deletada com sucesso.\n\n");
        }
        else{
            printf("\nA senha digitada não coincide com a senha da carteira. Verifique-a\n\n");
        }
    }
    else {
        printf("\nCarteira nao encontrada. Verifique o usuario digitado.\n\n");
    }
}

int main(){
    int op = 1; //variável de menu
    printf("Bem-vindo a sua carteira virtual!\n Escolha um indice do menu para continuar\n\n"); //msg ao usuario
    printf("==================================\n");//msg ao usuario
    while(op != 0){ //rodar o menu ate q o usuario saia
        printf("1 - Criar nova carteira\n\n"); //msg
        printf("2 - Acessar carteira\n\n"); //msg
        printf("3 - Deletar carteira\n\n"); //mg
        printf("0 - Sair da carteira\n\n");//msg
        printf("Indice: ");//msg
        scanf("%d", &op);//ler entrada do usuário
        printf("\n");
        if(op != 0 && op != 1 && op != 2 && op != 3){//if
            printf("Por favor, insira um indice valido\n\n");//msg
        }
        else if(op == 0){
            printf("Obrigado por utilizar a sua carteira virtual!\n");
            break;
        }
        else if(op == 1){
            printf("==================================\n");//msg ao usuario
            printf("Criar Carteira: \n"); //msg
            criarCarteira(); // chama funcao para criar nova carteira
        }
        else if(op == 2){
            printf("==================================\n");//msg ao usuario
            printf("Criar Carteira: \n"); //msg
            criarCarteira(); // chama funcao para criar nova carteira
        }
        else if(op == 3){
            printf("==================================\n");//msg ao usuario
            printf("Deletar Carteira: \n"); //msg
            deletarCarteira(); // chama funcao para criar nova carteira
        }
    }
    return 0;
}