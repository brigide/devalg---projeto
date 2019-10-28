#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct login{
    char usuario[100];
    char senha[100];
};

struct data{
    int dia;
    int mes;
    int ano;
};

struct receita{
    float quant;
};

struct gasto{
    float quant;
};

struct carteira{
    struct login login;
    float saldo;
    float poupanca;
};

int contarLinhas(struct carteira *c, char *ext){
    char nomeArq[strlen(c->login.usuario)+strlen(ext)+1];
    snprintf( nomeArq, sizeof( nomeArq ), "%s%s", c->login.usuario, ext );  

    FILE *fp = fopen(nomeArq,"r");
    int ch = 0;
    int lines = 0;

    while(!feof(fp)){
        ch = fgetc(fp);
        if(ch == '\n'){
        lines++;
        }
    }
  
    fclose(fp);
    return lines;
}

void novaData(struct data *data){
    printf("\nData:\n\n");
    printf("Dia: ");
    scanf("%d", &data->dia);
    if(data->dia < 1 || data->dia > 31){
        printf("Este dia do mes nao existe.\n");
        novaData(data);
    }
    printf("\nMes: ");
    scanf("%d", &data->mes);
    if(data->mes < 1 || data->mes > 12){
        printf("Este mes do ano nao existe.\n");
        novaData(data);
    }
    printf("\nAno: ");
    scanf("%d", &data->ano);
}

void salvarPoupanca(struct carteira *c, float valor, char *operacao, struct data *data){
    char* ext = "_info.txt";
    char* ext2 = "_poupanca.txt";

    char nomeArqInfo[strlen(c->login.usuario)+strlen(ext)+1];
    snprintf( nomeArqInfo, sizeof( nomeArqInfo ), "%s%s", c->login.usuario, ext );

    char nomeArqPoupanca[strlen(c->login.usuario)+strlen(ext2)+1];
    snprintf( nomeArqPoupanca, sizeof( nomeArqPoupanca ), "%s%s", c->login.usuario, ext2 );

    FILE* fw = fopen(nomeArqInfo, "w");
    FILE* fa = fopen(nomeArqPoupanca, "a");

    fprintf(fw, "%s\n", c->login.usuario);
    fprintf(fw, "%s\n", c->login.senha);
    fprintf(fw, "%.2f\n", c->saldo);
    fprintf(fw, "%.2f\n", c->poupanca);

    fprintf(fa, "%d %d %d   %s   %.2f\n", data->dia, data->mes, data->ano, operacao, valor);

    fclose(fw);
    fclose(fa);

}

void renderPoupanca(struct carteira *c, struct data *dataR){
    struct data data;
    struct data dataA;
    char operacaoA[] = "Aplicar";
    char operacaoAni[] = "Aniversario";
    char operacao[100];
    char tipo[100];
    float val;
    char* ext = "_info.txt";
    char* ext2 = "_poupanca.txt";

    int li = contarLinhas(c, ext2);

    char nomeArqInfo[strlen(c->login.usuario)+strlen(ext)+1];
    snprintf( nomeArqInfo, sizeof( nomeArqInfo ), "%s%s", c->login.usuario, ext );

    char nomeArqPoupanca[strlen(c->login.usuario)+strlen(ext2)+1];
    snprintf( nomeArqPoupanca, sizeof( nomeArqPoupanca ), "%s%s", c->login.usuario, ext2 );

    FILE* fw = fopen(nomeArqInfo, "w");
    FILE* fa = fopen(nomeArqPoupanca, "r");

    for(int i = 0; i < li; i++){

        fscanf(fa, "%d", &data.dia);
        fscanf(fa, "%d", &data.mes);
        fscanf(fa, "%d", &data.ano);

        fscanf(fa, "%s", operacao);
        fscanf(fa, "%f", &val);
    }
    dataA.dia = data.dia;
    dataA.mes = data.mes;
    dataA.ano = data.ano;
    while((dataA.dia < dataR->dia) || (dataA.mes < dataR->mes) || (dataA.ano < dataR->ano)){
        dataA.dia += 1;
        if(dataA.dia > 31 && dataA.mes < 12){
            dataA.dia = 1;
            dataA.mes += 1;
        }
        if(dataA.mes > 12 && dataA.dia > 31){
            dataA.dia = 1;
            dataA.mes = 1;
            dataA.ano += 1;
        }
        if(dataA.dia == data.dia){
            c->poupanca = c->poupanca + ((c->poupanca * 0.3755)/100);
            char tipo[] = "Aniversario";
            salvarPoupanca(c, c->poupanca, tipo, &dataA);
        }
            
    }

    /*
    if(dataA.ano == dataR->ano){
        if(dataR->mes == dataA.mes){
            if(dataR->dia >= dataA.dia){
                c->poupanca = c->poupanca + ((c->poupanca * 0.3755)/100);
                char tipo[] = "Aniversario";
                salvarPoupanca(c, c->poupanca, tipo, &dataA);
            }
        }   
        else if(dataR->mes > dataA.mes){
            if(dataR->dia >= dataA.dia){
                int diff = dataR->mes - dataA.mes;
                c->poupanca = c->poupanca + ((c->poupanca * 0.3755)/100) * diff;
                char tipo[] = "Aniversario";
                salvarPoupanca(c, c->poupanca, tipo, &dataA);
            }
        }     
    }
    else if(dataR->ano > dataA.ano){
        if(dataR->mes == dataA.mes){
            if(dataR->dia >= dataA.dia){
                c->poupanca = c->poupanca + ((c->poupanca * 0.3755)/100) * 12;
                char tipo[] = "Aniversario";
                salvarPoupanca(c, c->poupanca, tipo, &dataA);
            }
        }   
        else if(dataR->mes > dataA.mes){
            if(dataR->dia >= dataA.dia){
                int diff = dataR->mes - dataA.mes;
                int diffAno = dataR->ano - dataA.ano;
                c->poupanca = c->poupanca + ((c->poupanca * 0.3755)/100) * diff + ((c->poupanca * 0.3755)/100) * diffAno * diffAno;
                char tipo[] = "Aniversario";
                salvarPoupanca(c, c->poupanca, tipo, &dataA);
            }
        }  
    }
    */

    fprintf(fw, "%s\n", c->login.usuario);
    fprintf(fw, "%s\n", c->login.senha);
    fprintf(fw, "%.2f\n", c->saldo);
    fprintf(fw, "%.2f\n", c->poupanca);

    fclose(fw);
    fclose(fa);
}

void criarCarteira(){
    struct carteira c; //declara a struct

    printf("Insira um nome de usuario para a nova carteira: ");
    scanf("%s", c.login.usuario);

    printf("Crie uma senha para a nova carteira: ");
    scanf("%s", c.login.senha);

    printf("Digite o saldo inicial da carteira: ");
    scanf("%f", &c.saldo);
    c.poupanca = 0;
    system("cls"); // limpa o terminal
    system("clear");

    char* ext = "_info.txt";
    char* ext2 = "_gasto.txt";
    char* ext3 = "_receita.txt";
    char* ext4 = "_poupanca.txt";

    char nomeArqInfo[strlen(c.login.usuario)+strlen(ext)+1];
    snprintf( nomeArqInfo, sizeof( nomeArqInfo ), "%s%s", c.login.usuario, ext );//forma a string variavel + .txt

    char nomeArqGasto[strlen(c.login.usuario)+strlen(ext2)+1];
    snprintf( nomeArqGasto, sizeof( nomeArqGasto ), "%s%s", c.login.usuario, ext2 );//forma a string variavel + .txt

    char nomeArqReceita[strlen(c.login.usuario)+strlen(ext3)+1];
    snprintf( nomeArqReceita, sizeof( nomeArqReceita ), "%s%s", c.login.usuario, ext3 );//forma a string variavel + .txt

    char nomeArqPoupanca[strlen(c.login.usuario)+strlen(ext4)+1];
    snprintf( nomeArqPoupanca, sizeof( nomeArqPoupanca ), "%s%s", c.login.usuario, ext4 );

    if( access( nomeArqInfo, R_OK|W_OK ) != -1 ) { //verifica se um arquivo com o nome digitado existe
        printf("\nCarteira ja existe. Digite outro usuario\n\n");
    }
    else {
        FILE* fw = fopen(nomeArqInfo, "w");
        FILE* fwg = fopen(nomeArqGasto, "w");
        FILE* fwr = fopen(nomeArqReceita, "w");
        FILE* fwp = fopen(nomeArqPoupanca, "w");

        fprintf(fw, "%s\n", c.login.usuario);
        fprintf(fw, "%s\n", c.login.senha);
        fprintf(fw, "%.2f\n", c.saldo);
        fprintf(fw, "%.2f\n", c.poupanca);

        fclose(fw);
        fclose(fwg);
        fclose(fwr);
        fclose(fwp);

        printf("\nCarteira criada com sucesso!\n\n");
    }

}

void salvarRegistroG(struct carteira *c, struct gasto *gasto, struct data *data, char *tipo){
    char* ext = "_gasto.txt";
    char nomeArqGasto[strlen(c->login.usuario)+strlen(ext)+1];
    snprintf( nomeArqGasto, sizeof( nomeArqGasto ), "%s%s", c->login.usuario, ext );//forma a string variavel + .txt

    char* ext2 = "_info.txt";
    char nomeArqInfo[strlen(c->login.usuario)+strlen(ext2)+1];
    snprintf( nomeArqInfo, sizeof( nomeArqInfo ), "%s%s", c->login.usuario, ext2 );

    if(c->saldo - gasto->quant < 0){
        if(c->poupanca > gasto->quant){
            int op = 0;
            while(op != 1 || op != 2){ //rodar o menu ate q o usuario saia
                printf("Seu saldo é insuficiente. Deseja registrar o gasto com quantia da poupança?\n");
                printf("==================================\n");//msg ao usuario
                printf("1 - Sim\n\n"); //msg
                printf("2 - Nao\n\n"); //msg
                printf("Indice: ");//msg
                scanf("%d", &op);//ler entrada do usuário
                printf("\n");
                if(op != 1 && op != 2){//if
                    system("cls"); // limpa o terminal
                    system("clear");
                    printf("Por favor, insira um indice valido\n\n");//msg
                }
                else if(op == 1){
                    renderPoupanca(c, data);
                    system("cls"); // limpa o terminal
                    system("clear");
                    char operacao[] = "Resgatar";
                    c->poupanca = c->poupanca - gasto->quant;
                    system("cls"); // limpa o terminal
                    system("clear");
                    FILE* fa = fopen(nomeArqGasto, "a");
                    fprintf(fa, "%d %d %d   %s   %.2f\n", data->dia, data->mes, data->ano, tipo, gasto->quant);
                    fclose(fa);


                    FILE* fw = fopen(nomeArqInfo, "w");
                    fprintf(fw, "%s\n", c->login.usuario);
                    fprintf(fw, "%s\n", c->login.senha);
                    fprintf(fw, "%.2f\n", c->saldo);
                    fprintf(fw, "%.2f\n", c->poupanca);
                    fclose(fw);

                    system("cls"); // limpa o terminal
                    system("clear");
                    printf("Nova quantia na poupanca: R$%.2f\n", c->poupanca);
                    salvarPoupanca(c, gasto->quant, operacao, data);
                    break;
                }
                else if(op == 2){
                    printf("Nao foi possivel registrar seu gasto\n");
                    break;
                }
            }

        }
        else{
           system("cls"); // limpa o terminal
           system("clear");
           printf("Seu saldo é insuficiente.\n"); 
        }
        
    }
    else{
        c->saldo = c->saldo - gasto->quant;
        FILE* fa = fopen(nomeArqGasto, "a");
        fprintf(fa, "%d %d %d   %s   %.2f\n", data->dia, data->mes, data->ano, tipo, gasto->quant);
        fclose(fa);


        FILE* fw = fopen(nomeArqInfo, "w");
        fprintf(fw, "%s\n", c->login.usuario);
        fprintf(fw, "%s\n", c->login.senha);
        fprintf(fw, "%.2f\n", c->saldo);
        fprintf(fw, "%.2f\n", c->poupanca);
        fclose(fw);

        system("cls"); // limpa o terminal
        system("clear");
        printf("Novo saldo: R$%.2f\n", c->saldo);
    }

}

void registrarGasto(struct carteira *c){
    struct gasto gasto;
    struct data data;
    int op = 1; //variável de menu
    printf("==================================\n");//msg ao usuario
    printf("\nEscolha um indice do menu para continuar\n\n"); //msg ao usuario
    while(op != 0){ //rodar o menu ate q o usuario saia
        printf("Tipo de Gasto:\n");
        printf("==================================\n");//msg ao usuario
        printf("1 - Moradia\n\n"); //msg
        printf("2 - Estudo\n\n"); //msg
        printf("3 - Conducao\n\n"); //mg
        printf("4 - Alimentacao\n\n"); //mg
        printf("5 - Outros\n\n"); //mg
        printf("0 - Voltar\n\n");//msg
        printf("Indice: ");//msg
        scanf("%d", &op);//ler entrada do usuário
        printf("\n");
        if(op != 0 && op != 1 && op != 2 && op != 3 && op != 4 && op != 5){//if
            system("cls"); // limpa o terminal
            system("clear");
            printf("Por favor, insira um indice valido\n\n");//msg
        }
        else if(op == 0){
            system("cls"); // limpa o terminal
            system("clear");
            break;
        }
        else if(op == 1){
            char tipo[] = "Moradia";
            system("cls"); // limpa o terminal
            system("clear");
            printf("==================================\n");//msg ao usuario
            printf("Gasto com %s: R$", tipo); //msg
            scanf("%f", &gasto.quant);
            novaData(&data);
            salvarRegistroG(c, &gasto, &data, tipo);
        }
        else if(op == 2){
            char tipo[] = "Estudo";
            system("cls"); // limpa o terminal
            system("clear");
            printf("==================================\n");//msg ao usuario
            printf("Gasto com %s: R$", tipo); //msg
            scanf("%f", &gasto.quant);
            novaData(&data);
            salvarRegistroG(c, &gasto, &data, tipo);
        }
        else if(op == 3){
            char tipo[] = "Conducao";
            system("cls"); // limpa o terminal
            system("clear");
            printf("==================================\n");//msg ao usuario
            printf("Gasto com %s: R$", tipo); //msg
            scanf("%f", &gasto.quant);
            novaData(&data);
            salvarRegistroG(c, &gasto, &data, tipo);
        }
        else if(op == 4){
            char tipo[] = "Alimentacao";
            system("cls"); // limpa o terminal
            system("clear");
            printf("==================================\n");//msg ao usuario
            printf("Gasto com %s: R$", tipo); //msg
            scanf("%f", &gasto.quant);
            novaData(&data);
            salvarRegistroG(c, &gasto, &data, tipo);
        }
        else if(op == 5){
            char tipo[] = "Outros";
            system("cls"); // limpa o terminal
            system("clear");
            printf("==================================\n");//msg ao usuario
            printf("Gasto com %s: R$", tipo); //msg
            scanf("%f", &gasto.quant);
            novaData(&data);
            salvarRegistroG(c, &gasto, &data, tipo);
        }
    }
}
    
void salvarRegistroR(struct carteira *c, struct receita *receita, struct data *data, char *tipo){
    char* ext = "_receita.txt";
    char nomeArqGasto[strlen(c->login.usuario)+strlen(ext)+1];
    snprintf( nomeArqGasto, sizeof( nomeArqGasto ), "%s%s", c->login.usuario, ext );//forma a string variavel + .txt

    char* ext2 = "_info.txt";
    char nomeArqInfo[strlen(c->login.usuario)+strlen(ext2)+1];
    snprintf( nomeArqInfo, sizeof( nomeArqInfo ), "%s%s", c->login.usuario, ext2 );

    c->saldo = c->saldo + receita->quant;
    FILE* fa = fopen(nomeArqGasto, "a");
    fprintf(fa, "%d %d %d   %s   %.2f\n", data->dia, data->mes, data->ano, tipo, receita->quant);
    fclose(fa);


    FILE* fw = fopen(nomeArqInfo, "w");
    fprintf(fw, "%s\n", c->login.usuario);
    fprintf(fw, "%s\n", c->login.senha);
    fprintf(fw, "%.2f\n", c->saldo);
    fprintf(fw, "%.2f\n", c->poupanca);
    fclose(fw);

    system("cls"); // limpa o terminal
    system("clear");
    printf("Novo saldo: R$%.2f\n", c->saldo);

}

void registrarReceita(struct carteira *c){
    struct receita receita;
    struct data data;
    int op = 1; //variável de menu
    printf("==================================\n");//msg ao usuario
    printf("\nEscolha um indice do menu para continuar\n\n"); //msg ao usuario
    while(op != 0){ //rodar o menu ate q o usuario saia
        printf("Tipo de Receita:\n");
        printf("==================================\n");//msg ao usuario
        printf("1 - Salario\n\n"); //msg
        printf("2 - Adiantamento de salario\n\n"); //msg
        printf("3 - Comissao\n\n"); //mg
        printf("4 - Diversos\n\n"); //mg
        printf("0 - Voltar\n\n");//msg
        printf("Indice: ");//msg
        scanf("%d", &op);//ler entrada do usuário
        printf("\n");
        if(op != 0 && op != 1 && op != 2 && op != 3 && op != 4){//if
            system("cls"); // limpa o terminal
            system("clear");
            printf("Por favor, insira um indice valido\n\n");//msg
        }
        else if(op == 0){
            system("cls"); // limpa o terminal
            system("clear");
            break;
        }
        else if(op == 1){
            char tipo[] = "Salario";
            system("cls"); // limpa o terminal
            system("clear");
            printf("==================================\n");//msg ao usuario
            printf("Receita com %s: R$", tipo); //msg
            scanf("%f", &receita.quant);
            novaData(&data);
            salvarRegistroR(c, &receita, &data, tipo);
        }
        else if(op == 2){
            char tipo[] = "Adiantamento de salario";
            system("cls"); // limpa o terminal
            system("clear");
            printf("==================================\n");//msg ao usuario
            printf("Receita com %s: R$", tipo); //msg
            scanf("%f", &receita.quant);
            novaData(&data);
            salvarRegistroR(c, &receita, &data, tipo);
        }
        else if(op == 3){
            char tipo[] = "Comissao";
            system("cls"); // limpa o terminal
            system("clear");
            printf("==================================\n");//msg ao usuario
            printf("Receita com %s: R$", tipo); //msg
            scanf("%f", &receita.quant);
            novaData(&data);
            salvarRegistroR(c, &receita, &data, tipo);
        }
        else if(op == 4){
            char tipo[] = "Diversos";
            system("cls"); // limpa o terminal
            system("clear");
            printf("==================================\n");//msg ao usuari
            printf("Receita com %s: R$", tipo); //msg
            scanf("%f", &receita.quant);
            novaData(&data);
            salvarRegistroR(c, &receita, &data, tipo);
        }
    }
}

void aplicarPoupanca(struct carteira *c){
    struct data data;
    float valor;
    printf("Insira um valor para aplicar na poupanca: R$ ");
    scanf("%f", &valor);
    novaData(&data);
    if(valor > c->saldo){
        system("cls"); // limpa o terminal
        system("clear");
        printf("Saldo insuficiente. Tente novamente.\n");
        printf("Saldo: R$ %.2f\n", c->saldo);
        aplicarPoupanca(c);
    }
    else{
        char operacao[] = "Aplicar";
        c->poupanca = c->poupanca + valor;
        c->saldo = c->saldo - valor;
        system("cls"); // limpa o terminal
        system("clear");
        printf("Valor de R$ %.2f aplicado com sucesso.\n", valor);
        printf("Novo saldo: R$ %.2f\n", c->saldo);
        printf("Quantia na poupanca: R$ %.2f\n", c->poupanca);
        salvarPoupanca(c, valor, operacao, &data);
    }
}

void resgatarPoupanca(struct carteira *c){
    struct data data;
    float valor;
    printf("Insira um valor para resgatar da poupanca: R$ ");
    scanf("%f", &valor);
    novaData(&data);
    renderPoupanca(c, &data);
    if(valor > c->poupanca){
        system("cls"); // limpa o terminal
        system("clear");
        printf("Valor indisponivel. Tente novamente.\n");
        printf("Poupanca: R$ %.2f\n", c->saldo);
        resgatarPoupanca(c);
    }
    else{
        char operacao[] = "Resgatar";
         c->poupanca = c->poupanca - valor;
        c->saldo = c->saldo + valor;
        system("cls"); // limpa o terminal
        system("clear");
        printf("Valor de R$ %.2f resgatado com sucesso.\n", valor);
        printf("Novo valor de poupanca: R$ %.2f\n", c->poupanca);
        printf("Novo saldo: R$ %.2f\n", c->saldo);
        salvarPoupanca(c, valor, operacao, &data);
        
    }
}

void poupanca(struct carteira *c){
    int op = 1; //variável de menu
    printf("==================================\n");//msg ao usuario
    printf("\nEscolha um indice do menu para continuar\n\n"); //msg ao usuario
    while(op != 0){ //rodar o menu ate q o usuario saia
        printf("==================================\n");//msg ao usuario
        printf("1 - Aplicar valor\n\n"); //msg
        printf("2 - Resgatar valor\n\n"); //msg
        printf("0 - Voltar\n\n");//msg
        printf("Indice: ");//msg
        scanf("%d", &op);//ler entrada do usuário
        printf("\n");
        if(op != 0 && op != 1 && op != 2){//if
            system("cls"); // limpa o terminal
            system("clear");
            printf("Por favor, insira um indice valido\n\n");//msg
        }
        else if(op == 0){
            system("cls"); // limpa o terminal
            system("clear");
            break;
        }
        else if(op == 1){
            system("cls"); // limpa o terminal
            system("clear");
            printf("==================================\n");//msg ao usuario
            printf("Aplicar valor: \n"); //msg
            aplicarPoupanca(c);
        }
        else if(op == 2){
            system("cls"); // limpa o terminal
            system("clear");
            printf("==================================\n");//msg ao usuario
            printf("Resgatar valor: \n"); //msg
            resgatarPoupanca(c);
        }
    }
}

void iniFin(struct carteira *c, struct data *dataFin){ // verifica se a ultima data esta em gasto ou em receitas
    struct data dataG;
    struct data dataR;
    float val;
    char tipo;
    float valr;
    char tipor;

    char* ext = "_gasto.txt";
    char* ext2 = "_receita.txt";

    int lig = contarLinhas(c, ext);
    int lir = contarLinhas(c, ext2); 

    char nomeArqGasto[strlen(c->login.usuario)+strlen(ext)+1];
    snprintf( nomeArqGasto, sizeof( nomeArqGasto ), "%s%s", c->login.usuario, ext );//forma a string variavel + .txt

    char nomeArqReceita[strlen(c->login.usuario)+strlen(ext2)+1];
    snprintf( nomeArqReceita, sizeof( nomeArqReceita ), "%s%s", c->login.usuario, ext2 );//forma a string variavel + .txt

    FILE* fwg = fopen(nomeArqGasto, "r");
    for(int i = 0; i < lig; i++){
        fscanf(fwg,"%d", &dataG.dia);
        fscanf(fwg,"%d", &dataG.mes);
        fscanf(fwg,"%d", &dataG.ano);

        fscanf(fwg,"%s", &tipo);
        fscanf(fwg,"%f", &val);
    }
    fclose(fwg);

    FILE* fwr = fopen(nomeArqReceita, "r");
    for(int i = 0; i < lir; i++){
        fscanf(fwr,"%d", &dataR.dia);
        fscanf(fwr,"%d", &dataR.mes);
        fscanf(fwr,"%d", &dataR.ano);

        fscanf(fwr,"%s", &tipor);
        fscanf(fwr,"%f", &valr);
    }
    fclose(fwr);

    if(dataG.ano > dataR.ano){
        dataFin->dia = dataG.dia;
        dataFin->mes = dataG.mes;
        dataFin->ano = dataG.ano;
    }
    else if(dataR.ano > dataG.ano){
        dataFin->dia = dataR.dia;
        dataFin->mes = dataR.mes;
        dataFin->ano = dataR.ano;
    }
    else{
        if(dataG.mes > dataR.mes){
            dataFin->dia = dataG.dia;
            dataFin->mes = dataG.mes;
            dataFin->ano = dataG.ano;
        }
        else if(dataR.mes > dataG.mes){
            dataFin->dia = dataR.dia;
            dataFin->mes = dataR.mes;
            dataFin->ano = dataR.ano;
        }
        else{
            if(dataG.dia > dataR.dia){
                dataFin->dia = dataG.dia;
                dataFin->mes = dataG.mes;
                dataFin->ano = dataG.ano;
            }
            else if(dataR.dia > dataG.dia){
                dataFin->dia = dataR.dia;
                dataFin->mes = dataR.mes;
                dataFin->ano = dataR.ano;
            }
            else{
                dataFin->dia = dataR.dia;
                dataFin->mes = dataR.mes;
                dataFin->ano = dataR.ano;
            }
        }
    }
    dataFin->dia += 1;
    if(dataFin->dia > 31 && dataFin->mes < 12){
        dataFin->dia = 1;
        dataFin->mes += 1;
    }
    else if(dataFin->dia > 31 && dataFin->mes >= 12){
        dataFin->dia = 1;
        dataFin->mes = 1;
        dataFin->ano += 1; 
    }
}

void moviment(struct carteira *c, struct data *dataIni, struct data *dataFin, char *tipo){
    
    char geral[] = "Geral";
    struct data data;
    struct data datar;
    char* ext = "_gasto.txt";
    char* ext2 = "_receita.txt";
    char tArq[100];
    char tArqr[100];
    float valor;
    float valorr;
    float total = 0;
    float totalGeral = 0;

    char nomeArqGasto[strlen(c->login.usuario)+strlen(ext)+1];
    snprintf( nomeArqGasto, sizeof( nomeArqGasto ), "%s%s", c->login.usuario, ext );//forma a string variavel + .txt

    char nomeArqReceita[strlen(c->login.usuario)+strlen(ext2)+1];
    snprintf( nomeArqReceita, sizeof( nomeArqReceita ), "%s%s", c->login.usuario, ext2 );

    int lig = contarLinhas(c, ext);
    int lir = contarLinhas(c, ext2); 

    system("cls");
    system("clear");
    printf("%d/%d/%d  %d/%d/%d\n", dataIni->dia, dataIni->mes, dataIni->ano, dataFin->dia, dataFin->mes, dataFin->ano);

    if(lig == 0 && lir == 0){
        printf("Não há registros para serem relatados.\n");
    }
    else{
    printf("____________________________________________\n");
    printf("Mes/Ano: %d/%d\n\n", dataIni->mes, dataIni->ano);


     while((dataIni->dia < dataFin->dia) || (dataIni->mes < dataFin->mes) || (dataIni->ano < dataFin->ano)){
        FILE* frg = fopen(nomeArqGasto, "r");
        FILE* frr = fopen(nomeArqReceita, "r");
        for(int i = 0; i < lig; i++){
            fscanf(frg,"%d", &data.dia);
            fscanf(frg,"%d", &data.mes);
            fscanf(frg,"%d", &data.ano);
            fscanf(frg,"%s", tArq);
            fscanf(frg,"%f", &valor);
            if(strcmp(tipo, geral) == 0){
                if((dataIni->dia == data.dia) && (dataIni->mes == data.mes) && (dataIni->ano == data.ano)){
                    printf("Data: %d/%d/%d   Tipo: %s   - R$%.2f\n", data.dia, data.mes, data.ano, tArq, valor);
                    total -= valor;
                }
            }
            else if(strcmp(tipo, tArq) == 0){
                if((dataIni->dia == data.dia) && (dataIni->mes == data.mes) && (dataIni->ano == data.ano)){
                    printf("Data: %d/%d/%d   Tipo: %s   - R$%.2f\n", data.dia, data.mes, data.ano, tArq, valor);
                    total -= valor;
                }
            }
        }
        for(int i = 0; i < lir; i++){
            fscanf(frr,"%d", &datar.dia);
            fscanf(frr,"%d", &datar.mes);
            fscanf(frr,"%d", &datar.ano);
            fscanf(frr,"%s", tArqr);
            fscanf(frr,"%f", &valorr);
            if(strcmp(tipo, geral) == 0){
                if((dataIni->dia == datar.dia) && (dataIni->mes == datar.mes) && (dataIni->ano == datar.ano)){
                    printf("Data: %d/%d/%d   Tipo: %s   + R$%.2f\n", datar.dia, datar.mes, datar.ano, tArqr, valorr);
                    total += valorr;
                }
            }
            else if(strcmp(tipo, tArqr) == 0){
                if((dataIni->dia == datar.dia) && (dataIni->mes == datar.mes) && (dataIni->ano == datar.ano)){
                    printf("Data: %d/%d/%d   Tipo: %s   + R$%.2f\n", datar.dia, datar.mes, datar.ano, tArqr, valor);
                    total += valor;
                }
            }
        }
        fclose(frg);
        fclose(frr);
        dataIni->dia += 1;
        if(dataIni->dia > 31 && dataIni->mes < 12){
            printf("\nTotal do mes %d: R$%.2f\n\n", dataIni->mes, total);
            dataIni->dia = 1;
            dataIni->mes += 1;
            printf("____________________________________________\n");
            printf("Mes/Ano: %d/%d\n\n", dataIni->mes, dataIni->ano);
            totalGeral += total;
            total = 0;
        }
            
        if(dataIni->mes >= 12 && dataIni->dia > 31){
            printf("\nTotal do mes %d: R$%.2f\n\n", dataIni->mes, total);
            dataIni->dia = 1;
            dataIni->mes = 1;
            dataIni->ano += 1;
            printf("____________________________________________\n");
            printf("Mes/Ano: %d/%d\n\n", dataIni->mes, dataIni->ano);
            totalGeral += total;
            total = 0;
        }
            
    }
    printf("\nTotal do mes %d: R$%.2f\n\n", dataIni->mes, total);
    totalGeral += total;
    printf("\nTotal do periodo: R$%.2f\n\n", totalGeral);
    }
    char op;
    printf("\nDgite qualquer tecla para retornar: ");
    scanf("%s", &op);
    system("cls");
    system("clear");
}

void relatMov(struct carteira *c, struct data *dataIni, struct data *dataFin){
    char tipo[100];
    int op = 0;
    while(op != 1 && op != 2 && op != 3 && op != 4 && op != 5 && op != 6 && op != 7 && op != 8 && op != 9 && op != 10){
        printf("Categorias:\n");
        printf("==================================\n");//msg ao usuario
        printf("1 - Todas as categorias\n\n"); //msg
        printf("2 - Moradia\n\n"); //msg
        printf("3 - Estudo\n\n"); //msg
        printf("4 - Conducao\n\n"); //mg
        printf("5 - Alimentacao\n\n"); //mg
        printf("6 - Salario\n\n"); //msg
        printf("7 - Adiantamento de salario\n\n"); //msg
        printf("8 - Comissao\n\n"); //mg
        printf("9 - Diversos\n\n"); //mg
        printf("10 - Outros\n\n"); //mg
        printf("Indice: ");//msg
        scanf("%d", &op);//ler entrada do usuário
        printf("\n");
        if(op != 1 && op != 2 && op != 3 && op != 4 && op != 5 && op != 6 && op != 7 && op != 8 && op != 9 && op != 10){
            system("cls"); // limpa o terminal
            system("clear");
            printf("Por favor, insira um indice valido\n\n");//msg
        }
        else if(op == 1){
            system("cls"); // limpa o terminal
            system("clear");
            char tipo[] = "Geral";
            break;
        }
        else if(op == 2){
            system("cls"); // limpa o terminal
            system("clear");
            char tipo[] = "Moradia";
            break;
        }
        else if(op == 3){
            system("cls"); // limpa o terminal
            system("clear");
            char tipo[] = "Estudo";
            break;
        }
        else if(op == 4){
            system("cls"); // limpa o terminal
            system("clear");
            char tipo[] = "Conducao";
            break;
        }
        else if(op == 5){
            system("cls"); // limpa o terminal
            system("clear");
            char tipo[] = "Alimentacao";
            break;
        }
        else if(op == 6){
            system("cls"); // limpa o terminal
            system("clear");
            char tipo[] = "Salario";
            break;
        }
        else if(op == 7){
            system("cls"); // limpa o terminal
            system("clear");
            char tipo[] = "Adiantamento de salario";
            break;
        }
        else if(op == 8){
            system("cls"); // limpa o terminal
            system("clear");
            char tipo[] = "Comissao";
            break;
        }
        else if(op == 9){
            system("cls"); // limpa o terminal
            system("clear");
            char tipo[] = "Diversos";
            break;
        }
        else if(op == 10){
            system("cls"); // limpa o terminal
            system("clear");
            char tipo[] = "Outros";
            break;
        }
    }
    moviment(c, dataIni, dataFin, tipo);
}

//1 - esolher categoria
//2 - nao escolher
//12 - ultimos 12
//11 - escolher ano
//30 - ultimos 30
//31 - escolher mes
void relatAux(struct carteira *c, int cat, int time){
    struct data dataIni;
    struct data dataFin;
    system("cls");// limpa o terminal
    system("clear");
    int ano;
    int mes;
    if(cat == 1){
        if(time == 12){
            iniFin(c, &dataFin);
            dataIni.dia = dataFin.dia;
            dataIni.mes = dataFin.mes;
            dataIni.ano = dataFin.ano - 1;
            relatMov(c, &dataIni, &dataFin);
        }
        else if(time == 11){
            printf("Digite um ano desejado para o relatório: ");
            scanf("%d", &dataFin.ano);
            dataFin.mes = 12;
            dataFin.dia = 31;
            dataIni.ano = dataFin.ano;
            dataIni.mes = 1;
            dataIni.dia = 1;
            relatMov(c, &dataIni, &dataFin);
        }
        else if(time == 30){
            iniFin(c, &dataFin);
            dataIni.dia = dataFin.dia;
            if(dataFin.mes == 1){
                dataIni.mes = 12;
                dataIni.ano = dataFin.ano - 1;
            }
            else{
                dataIni.mes = dataFin.mes - 1;
                dataIni.ano = dataFin.ano;
            }
            relatMov(c, &dataIni, &dataFin);
        }
        else if(time == 31){
            printf("Digite um ano desejado para o relatório: ");
            scanf("%d", &dataFin.ano);
            printf("\nDigite o mes desejado (entre 1 e 12) de %d: ", dataFin.ano);
            scanf("%d", &dataFin.mes);
            if(dataFin.mes < 1 || dataFin.mes > 12){
                relatAux(c, 1, 31);
            }
            else{
                dataFin.dia = 31;
                dataIni.ano = dataFin.ano;
                dataIni.mes = dataFin.mes;
                dataIni.dia = 1;
            }
            relatMov(c, &dataIni, &dataFin);
        }
    }
    else{
        if(time == 12){
            iniFin(c, &dataFin);
            dataIni.dia = dataFin.dia;
            dataIni.mes = dataFin.mes;
            dataIni.ano = dataFin.ano - 1;
        }
        else if(time == 11){
            printf("Digite um ano desejado para o relatório: ");
            scanf("%d", &dataFin.ano);
            dataFin.mes = 12;
            dataFin.dia = 31;
            dataIni.ano = dataFin.ano;
            dataIni.mes = 1;
            dataIni.dia = 1;
        }
        else if(time == 30){
            iniFin(c, &dataFin);
            dataIni.dia = dataFin.dia;
            if(dataFin.mes == 1){
                dataIni.mes = 12;
                dataIni.ano = dataFin.ano - 1;
            }
            else{
                dataIni.mes = dataFin.mes - 1;
                dataIni.ano = dataFin.ano;
            }

        }
        else if(time == 31){
            printf("Digite um ano desejado para o relatório: ");
            scanf("%d", &dataFin.ano);
            printf("\nDigite o mes desejado (entre 1 e 12) de %d: ", dataFin.ano);
            scanf("%d", &dataFin.mes);
            if(dataFin.mes < 1 || dataFin.mes > 12){
                relatAux(c, 1, 31);
            }
            else{
                dataFin.dia = 31;
                dataIni.ano = dataFin.ano;
                dataIni.mes = dataFin.mes;
                dataIni.dia = 1;
            }
        }
    
    }
}

void relatorios(struct carteira *c){
    int op = 1;
    while(op != 0){
        printf("1 - Movimentacoes nos ultimos 12 meses\n\n");
        printf("2 - Movimentacoes no ano desejado\n\n");
        printf("3 - Movimentacoes nos ultimos 30 dias\n\n");
        printf("4 - Movimentacoes no mes desejado\n\n");
        printf("5 - Poupanca nos ultimos 12 meses\n\n");
        printf("6 - Poupanca no ano desejado\n\n");
        printf("7 - Poupanca nos ultimos 30 dias\n\n");
        printf("8 - Poupanca no mes desejado\n\n");
        printf("0 - Voltar\n\n");//msg
        printf("Indice: ");//msg
        scanf("%d", &op);//ler entrada do usuário
        printf("\n");
        if(op != 0 && op != 1 && op != 2 && op != 3 && op != 4 && op != 5 && op != 6 && op != 7 && op != 8){
            system("cls");// limpa o terminal
            system("clear");
            printf("Por favor, insira um indice valido\n\n");//msg
        }
        if(op == 0){
            system("cls");// limpa o terminal
            system("clear");
            break;
        }
        if(op == 1){
            system("cls");// limpa o terminal
            system("clear");
            relatAux(c, 1, 12);
        }
        if(op == 2){
            system("cls");// limpa o terminal
            system("clear");
            relatAux(c, 1, 11);
        }
        if(op == 3){
            system("cls");// limpa o terminal
            system("clear");
            relatAux(c, 1, 30);
        }
        if(op == 4){
            system("cls");// limpa o terminal
            system("clear");
            relatAux(c, 1, 31);
        }
        if(op == 5){
            system("cls");// limpa o terminal
            system("clear");
            relatAux(c, 2, 12);
        }
        if(op == 6){
            system("cls");// limpa o terminal
            system("clear");
            relatAux(c, 2, 11);
        }
        if(op == 7){
            system("cls");// limpa o terminal
            system("clear");
            relatAux(c, 2, 30);
        }
        if(op == 8){
            system("cls");// limpa o terminal
            system("clear");
            relatAux(c, 2, 31);
        }
    }
}


void menuCarteira(struct carteira *c){
    int op = 1; //variável de menu
    printf("\nOlá %s!\nEscolha um indice do menu para continuar\n\n", c->login.usuario); //msg ao usuario
    while(op != 0){ //rodar o menu ate q o usuario saia
        printf("\nOlá %s!\n\n", c->login.usuario);
        printf("\n");
        printf("==================================\n\n");//msg ao usuario
        printf("Informacoes da carteira:\n\n");
        printf("Saldo: R$ %.2f\n", c->saldo);
        printf("Poupança: R$ %.2f\n\n", c->poupanca);
        printf("Escolha um indice do menu para continuar\n\n");
        printf("==================================\n\n");//msg ao usuario
        printf("1 - Registrar Gasto\n\n"); //msg
        printf("2 - Registrar Receita\n\n"); //msg
        printf("3 - Poupanca\n\n"); //mg
        printf("4 - Relatorios\n\n"); //mg
        printf("0 - Sair da carteira e voltar para o menu principal\n\n");//msg
        printf("Indice: ");//msg
        scanf("%d", &op);//ler entrada do usuário
        printf("\n");
        if(op != 0 && op != 1 && op != 2 && op != 3 && op != 4){//if
            system("cls");// limpa o terminal
            system("clear");
            printf("Por favor, insira um indice valido\n\n");//msg
        }
        else if(op == 0){
            system("cls"); // limpa o terminal
            system("clear");
            printf("Até logo %s!\n", c->login.usuario);
            break;
        }
        else if(op == 1){
            system("cls"); // limpa o terminal
            system("clear");
            printf("==================================\n");//msg ao usuario
            printf("Registrar gasto: \n"); //msg
            registrarGasto(c); 
        }
        else if(op == 2){
           system("cls"); // limpa o terminal
           system("clear");
            printf("==================================\n");//msg ao usuario
            printf("Registrar receita: \n"); //msg
            registrarReceita(c);
        }
        else if(op == 3){
            system("cls"); // limpa o terminal
            system("clear");
            system("clear");
            printf("==================================\n");//msg ao usuario
            printf("Poupanca: \n"); //msg
            printf("Poupanca: \n"); //msg
            poupanca(c);
        }
        else if(op == 4){
            system("cls"); // limpa o terminal
            system("clear");
            printf("==================================\n");//msg ao usuario
            printf("Relatorios disponiveis: \n"); //msg
            relatorios(c); // chama funcao para menu de relatorios
        }
    }
}

void verificarLogin(){
    int del;
    char usuario[100];
    char senha[100];
    printf("\nLogin: ");
    scanf("%s", usuario);
    printf("\nSenha: ");
    scanf("%s", senha);
    system("cls"); // limpa o terminal
    system("clear");
    system("clear");
    char* ext = "_info.txt";

    char nomeArqInfo[strlen(usuario)+strlen(ext)+1];

    snprintf( nomeArqInfo, sizeof( nomeArqInfo ), "%s%s", usuario, ext );//formaa string variavel + .txt

    if( access( nomeArqInfo, R_OK|W_OK ) != -1 ) { // verifica se a carteira com o nome digitado existe
        char senhaArq[100];
        FILE* fr = fopen(nomeArqInfo, "r");
        for(int i = 0; i < 2; i++){
            fscanf(fr, "%s", senhaArq);
        }
        fclose(fr);
        if ( strcmp(senha, senhaArq) == 0){
            struct carteira c;
            FILE* fr = fopen(nomeArqInfo, "r");
            fscanf(fr, "%s", c.login.usuario);
            fscanf(fr, "%s", c.login.senha);
            fscanf(fr, "%f", &c.saldo);
            fscanf(fr, "%f", &c.poupanca);
            printf("\nLogin efetuado com sucesso.\n\n");
            menuCarteira(&c);
            fclose(fr);

        }
        else{
            printf("\nA senha digitada não coincide com a senha da carteira. Verifique-a\n\n");
        }
    }
    else {
        printf("\nCarteira nao encontrada. Verifique o usuario digitado.\n\n");
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
    system("cls"); // limpa o terminalz
    system("clear");
    char* ext = "_info.txt";
    char* ext2 = "_gasto.txt";
    char* ext3 = "_receita.txt";
    char* ext4 = "_poupanca.txt";

    char nomeArqInfo[strlen(usuario)+strlen(ext)+1];
    snprintf( nomeArqInfo, sizeof( nomeArqInfo ), "%s%s", usuario, ext );//forma a string variavel + .txt

    char nomeArqGasto[strlen(usuario)+strlen(ext2)+1];
    snprintf( nomeArqGasto, sizeof( nomeArqGasto ), "%s%s", usuario, ext2 );//forma a string variavel + .txt

    char nomeArqReceita[strlen(usuario)+strlen(ext3)+1];
    snprintf( nomeArqReceita, sizeof( nomeArqReceita ), "%s%s", usuario, ext3 );//forma a string variavel + .txt

    char nomeArqPoupanca[strlen(usuario)+strlen(ext4)+1];
    snprintf( nomeArqPoupanca, sizeof( nomeArqPoupanca ), "%s%s", usuario, ext4 ); 

    if( access( nomeArqInfo, R_OK|W_OK ) != -1 ) { // verifica se a carteira com o nome digitado existe
        char senhaArq[100];
        FILE* fr = fopen(nomeArqInfo, "r");
        for(int i = 0; i < 2; i++){
            fscanf(fr, "%s", senhaArq);
        }
        fclose(fr);
        if ( strcmp(senha, senhaArq) == 0){
            del = remove(nomeArqInfo); // remove o arquivo com determinado nomeArqInfo
            del = remove(nomeArqGasto); // remove o arquivo com determinado nomeArqasto
            del = remove(nomeArqReceita); // remove o arquivo com determinado nomeArqReceita
            del = remove(nomeArqPoupanca); // remove o arquivo com determinado nomeArq
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
    system("cls");
    system("clear");
    int op = 1; //variável de menu
    printf("Bem-vindo a sua carteira virtual!\nEscolha um indice do menu para continuar\n\n"); //msg ao usuario
    while(op != 0){ //rodar o menu ate q o usuario saia
        printf("==================================\n");//msg ao usuario
        printf("1 - Criar nova carteira\n\n"); //msg
        printf("2 - Acessar carteira\n\n"); //msg
        printf("3 - Deletar carteira\n\n"); //mg
        printf("0 - Sair da carteira\n\n");//msg
        printf("Indice: ");//msg
        scanf("%d", &op);//ler entrada do usuário
        printf("\n");
        if(op != 0 && op != 1 && op != 2 && op != 3){//if
            system("cls"); // limpa o terminal
            system("clear");
            printf("Por favor, insira um indice valido\n\n");//msg
        }
        else if(op == 0){
            system("cls"); // limpa o terminal
            system("clear");
            printf("Obrigado por utilizar a sua carteira virtual!\n");
            break;
        }
        else if(op == 1){
            system("cls"); // limpa o terminal
            system("clear");
            printf("==================================\n");//msg ao usuario
            printf("Criar Carteira: \n"); //msg
            criarCarteira(); // chama funcao para criar nova carteira
        }
        else if(op == 2){
            system("cls"); // limpa o terminal
            system("clear");
            printf("==================================\n");//msg ao usuario
            printf("Efetuar Login: \n"); //msg
            verificarLogin(); // chama funcao para logar na carteira
        }
        else if(op == 3){
            system("cls"); // limpa o terminal
            system("clear");
            printf("==================================\n");//msg ao usuario
            printf("Deletar Carteira: \n"); //msg
            deletarCarteira(); // chama funcao para criar nova carteira
        }
    }
    return 0;
}