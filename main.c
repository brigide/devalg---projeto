#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iup.h>

struct login{
    char usuario[100];
    char senha[100];
};

struct carteira{
    struct login login;
    char saldo[100];
    char poupanca[100];
};

struct carteira c;

//menus
Ihandle *btnCriar, *btnLogin, *btnDel, *btnSair, *vbox1, *menu1; // menu principal
Ihandle *btnCriarCart, *btnVoltar, *uLabel, *sLabel, *saldoLabel, *uText, *sText, *saldoText, *vboxCriar, *menuCriar; // criar conta
Ihandle *btnDelCart, *btnVoltarDel, *uLabelDel, *sLabelDel, *uTextDel, *sTextDel, *vboxDel, *menuDel; // deletar conta
Ihandle *btnLoginCart, *btnVoltarLogin, *uLabelLogin, *sLabelLogin, *uTextLogin, *sTextLogin, *vboxLogin, *menuLogin; // verificar login
Ihandle *btnGasto, *btnReceita, *btnPoupanca, *btnRelatorio, *btnVoltarCart, *label1Cart, *label2Cart, *label3Cart, *label4Cart, *vboxCart, *menuCart;   // menu carteira
Ihandle *btnMoradia, *btnEstudo, *btnConducao, *btnAlimentacao, *btnOutros, *btnProsseguir, *btnVoltarGastoMenu, *tipoLabel, *selectLabel, *tipoTextRO, *vboxGasto, *menuGasto;// menu de gasto
Ihandle *tipoTextRO2, *valorLabel, *valorText, *diaLabelG, *diaTextG, *mesLabelG, *mesTextG, *anoLabelG, *anoTextG, *descLabelG, *descTextG, *btnSalvarG, *btnVoltarG, *vboxG, *menuG; // menu 2 gasto
Ihandle *btnSalario, *btnAdiantamento, *btnComissao, *btnVendas, *btnDiversos, *btnProsseguirR, *btnVoltarReceitaMenu, *tipoLabelR, *selectLabelR, *tipoTextR, *vboxReceita, *menuReceita;// menu de receita
Ihandle *tipoTextR2, *valorLabelR, *valorTextR, *diaLabelR, *diaTextR, *mesLabelR, *mesTextR, *anoLabelR, *anoTextR, *descLabelR, *descTextR, *btnSalvarR, *btnVoltarR, *vboxR, *menuR; // menu 2 receita
Ihandle *btnAplicar, *btnResgatar, *btnVoltarPoupanca, *vboxPoupanca, *menuPoupanca; // menu poupanca
Ihandle *valorLabelAplicar, *valorTextAplicar, *diaLabelAplicar, *diaTextAplicar, *mesLabelAplicar, *mesTextAplicar, *anoLabelAplicar, *anoTextAplicar, *btnSalvarAplicar, *btnVoltarAplicar, *vboxAplicar, *menuAplicar; // menu aplicar
Ihandle *valorLabelResgatar, *valorTextResgatar, *diaLabelResgatar, *diaTextResgatar, *mesLabelResgatar, *mesTextResgatar, *anoLabelResgatar, *anoTextResgatar, *btnSalvarResgatar, *btnVoltarResgatar, *vboxResgatar, *menuResgatar; // menu Resgatar
Ihandle *btnMov, *btnPou, *btnVoltarRela, *vboxRela, *menuRela; // menu relatorios
Ihandle *rLabelMov, *btnrGeral, *btnrMoradia, *btnrEstudo, *btnrConducao, *btnrAlimentacao, *btnrOutros, *btnrSalario, *btnrAdiantamento, *btnrComissao, *btnrVendas, *btnrDiversos, *rTextRO, *btnrMov, *btnrVoltarMov, *rvboxMov, *rmenuMov; // menu categorias 
Ihandle *tText, *iLabel, *diLabel, *diText, *miLabel, *miText, *aiLabel, *aiText, *fLabel, *dfLabel, *dfText, *mfLabel, *mfText, *afLabel, *afText, *btnDP, *btnDV, *vboxData, *menuData; //data final e inicial mov
Ihandle *iLabelP, *diLabelP, *diTextP, *miLabelP, *miTextP, *aiLabelP, *aiTextP, *fLabelP, *dfLabelP, *dfTextP, *mfLabelP, *mfTextP, *afLabelP, *afTextP, *btnDPP, *btnDVP, *vboxDataP, *menuDataP; //data final e inicial poupanca
Ihandle *relaLabel, *relaText, *relaVoltar, *relavbox, *relamenu; // interface relatorio
Ihandle *relaLabelP, *relaTextP, *relaVoltarP, *relavboxP, *relamenuP; // interface relatorio poupanca

int contarLinhas(char *ext){
    char nomeArq[strlen(c.login.usuario)+strlen(ext)+1];
    snprintf( nomeArq, sizeof( nomeArq ), "%s%s", c.login.usuario, ext );  

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

int quit(Ihandle *self){
	IupMessage("Obrigado", "Obrigado por utilizar nossa carteira virtual!");
	IupClose();
	return EXIT_SUCCESS;
}

int funcCriar(Ihandle *self){
	int main();
	struct carteira c; //declara a struct
	
	char *usuario = IupGetAttribute(uText, "VALUE");
	char *senha = IupGetAttribute(sText, "VALUE");
	char *saldo = IupGetAttribute(saldoText, "VALUE");
	char poupanca[] = "0.00";

	strcpy(c.login.usuario, usuario);
	strcpy(c.login.senha, senha);
	strcpy(c.saldo, saldo);
	strcpy(c.poupanca, poupanca);
	
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
         IupMessage("Erro", "Carteira já existente. Digite outro");
    }
    else {
        FILE* fw = fopen(nomeArqInfo, "w");
        FILE* fwg = fopen(nomeArqGasto, "w");
        FILE* fwr = fopen(nomeArqReceita, "w");
        FILE* fwp = fopen(nomeArqPoupanca, "w");

        fprintf(fw, "%s\n", c.login.usuario);
        fprintf(fw, "%s\n", c.login.senha);
        fprintf(fw, "%s\n", c.saldo);
        fprintf(fw, "%s\n", c.poupanca);

        fclose(fw);
        fclose(fwg);
        fclose(fwr);
        fclose(fwp);

        IupMessage("Sucesso", "Carteira criada com sucesso");
        main();
        return EXIT_SUCCESS;
    }

}

int menuCriarFunc(Ihandle *self){
	int main();
	btnCriarCart = IupButton("Criar Carteira", NULL);
  	btnVoltar = IupButton("Voltar", NULL);
  	uLabel = IupLabel("Usuario");
  	sLabel = IupLabel("Senha");
  	saldoLabel = IupLabel("Saldo Inicial");
  	uText = IupText(NULL);
  	sText = IupText(NULL);
  	IupSetAttribute(sText, "PASSWORD", "YES");
  	saldoText = IupText(NULL);
  	IupSetAttribute(saldoText, "MASK", "[+/-]?(/d+/.?/d*|/./d+)");
  	vboxCriar = IupVbox(
  		uLabel,
  		uText,
  		sLabel,
  		sText,
  		saldoLabel,
  		saldoText,
  		btnCriarCart,
  		btnVoltar,
  		NULL
  	);
  	menuCriar = IupDialog(vboxCriar);
  	IupSetAttribute(menuCriar, "TITLE", "Criar Carteira");
  	IupSetAttribute(vboxCriar, "ALIGNMENT", "ACENTER");
  	IupSetAttribute(vboxCriar, "GAP", "10");
  	IupSetAttribute(vboxCriar, "MARGIN", "80x80");
  	IupShowXY(menuCriar, IUP_CENTER, IUP_CENTER);
  	
  	//IupDestroy(menu1);
  
  	IupSetCallback(btnCriarCart, "ACTION", (Icallback) funcCriar);
  	IupSetCallback(btnVoltar, "ACTION", (Icallback) main);
  
  	IupMainLoop();
  	return EXIT_SUCCESS;
}

int funcDel(Ihandle *self){
	int main();
	int del;
    char *usuario = IupGetAttribute(uTextDel, "VALUE");
    char *senha = IupGetAttribute(sTextDel, "VALUE");
    
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
        int i;
        for(i = 0; i < 2; i++){
            fscanf(fr, "%s", senhaArq);
        }
        fclose(fr);
        if ( strcmp(senha, senhaArq) == 0){
            del = remove(nomeArqInfo); // remove o arquivo com determinado nomeArqInfo
            del = remove(nomeArqGasto); // remove o arquivo com determinado nomeArqasto
            del = remove(nomeArqReceita); // remove o arquivo com determinado nomeArqReceita
            del = remove(nomeArqPoupanca); // remove o arquivo com determinado nomeArq
            IupMessage("Sucesso", "Carteira excluida com sucesso.");
            main();
            return EXIT_SUCCESS;
        }
        else{
            IupMessage("Erro", "Senha incorreta");
        }
    }
    else {
        IupMessage("Erro", "Carteira nao existente.");
    }	
}

int menuDelFunc(Ihandle *self){
	int main();
	btnDelCart = IupButton("Deletar Carteira", NULL);
  	btnVoltarDel = IupButton("Voltar", NULL);
  	uLabelDel = IupLabel("Usuario");
  	sLabelDel = IupLabel("Senha");
  	uTextDel = IupText(NULL);
  	sTextDel = IupText(NULL);
  	IupSetAttribute(sTextDel, "PASSWORD", "YES");
  	vboxDel = IupVbox(
  		uLabelDel,
  		uTextDel,
  		sLabelDel,
  		sTextDel,
  		btnDelCart,
  		btnVoltarDel,
  		NULL
  	);
  	menuDel = IupDialog(vboxDel);
  	IupSetAttribute(menuDel, "TITLE", "Deletar Carteira");
  	IupSetAttribute(vboxDel, "ALIGNMENT", "ACENTER");
  	IupSetAttribute(vboxDel, "GAP", "10");
  	IupSetAttribute(vboxDel, "MARGIN", "80x80");
  	IupShowXY(menuDel, IUP_CENTER, IUP_CENTER);
  
  	//IupDestroy(menu1);
  
  	IupSetCallback(btnDelCart, "ACTION", (Icallback) funcDel);
  	IupSetCallback(btnVoltarDel, "ACTION", (Icallback) main);
  
  	IupMainLoop();
  	return EXIT_SUCCESS;
}

int agradece(Ihandle *self){
	int main();
	IupMessage("Obrigado", "Voce deslogou da sua conta");
	//IupDestroy(menuCart);
	main();
	return EXIT_SUCCESS;
}

int voltaCartGasto(Ihandle *self){
	int menuCarteira();
	//IupDestroy(menuGasto);
    menuCarteira();
	return EXIT_SUCCESS;
}
int voltaCartG(Ihandle *self){
	int menuCarteira();
	//IupDestroy(menuG);
    menuCarteira();
	return EXIT_SUCCESS;
}
int voltaCartReceita(Ihandle *self){
	int menuCarteira();
	//IupDestroy(menuReceita);
    menuCarteira();
	return EXIT_SUCCESS;
}
int voltaCartR(Ihandle *self){
	int menuCarteira();
	//IupDestroy(menuR);
    menuCarteira();
	return EXIT_SUCCESS;
}
int voltaCartAplicar(Ihandle *self){
	int menuCarteira();
	//IupDestroy(menuAplicar);
    menuCarteira();
	return EXIT_SUCCESS;
}
int voltaCartResgatar(Ihandle *self){
	int menuCarteira();
	//IupDestroy(menuResgatar);
    menuCarteira();
	return EXIT_SUCCESS;
}
int voltaCartPoupanca(Ihandle *self){
	int menuCarteira();
	//IupDestroy(menuPoupanca);
    menuCarteira();
	return EXIT_SUCCESS;
}
int voltaCartrelamenu(Ihandle *self){
	int menuCarteira();
	//IupDestroy(relamenu);
    menuCarteira();
	return EXIT_SUCCESS;
}
int voltaCartrelamenuP(Ihandle *self){
	int menuCarteira();
	//IupDestroy(relamenuP);
    menuCarteira();
	return EXIT_SUCCESS;
}
int voltaCartData(Ihandle *self){
	int menuCarteira();
	//IupDestroy(menuData);
    menuCarteira();
	return EXIT_SUCCESS;
}
int voltaCartDataP(Ihandle *self){
	int menuCarteira();
	//IupDestroy(menuDataP);
    menuCarteira();
	return EXIT_SUCCESS;
}
int voltaCartrmenuMov(Ihandle *self){
	int menuCarteira();
	//IupDestroy(rmenuMov);
    menuCarteira();
	return EXIT_SUCCESS;
}
int voltaCartRela(Ihandle *self){
	int menuCarteira();
	//IupDestroy(menuRela);
    menuCarteira();
	return EXIT_SUCCESS;
}


int mudaValMoradia(Ihandle *self){
	IupSetAttribute(tipoTextRO, "VALUE", "Moradia");
	return EXIT_SUCCESS;
}
int mudaValEstudo(Ihandle *self){
	IupSetAttribute(tipoTextRO, "VALUE", "Estudo");
	return EXIT_SUCCESS;
}
int mudaValConducao(Ihandle *self){
	IupSetAttribute(tipoTextRO, "VALUE", "Conducao");
	return EXIT_SUCCESS;
}
int mudaValAlimentacao(Ihandle *self){
	IupSetAttribute(tipoTextRO, "VALUE", "Alimentacao");
	return EXIT_SUCCESS;
}
int mudaValOutros(Ihandle *self){
	IupSetAttribute(tipoTextRO, "VALUE", "Outros");
	return EXIT_SUCCESS;
}

int mudaValSalario(Ihandle *self){
	IupSetAttribute(tipoTextR, "VALUE", "Salario");
	return EXIT_SUCCESS;
}
int mudaValAdiantamento(Ihandle *self){
	IupSetAttribute(tipoTextR, "VALUE", "Adiantamento");
	return EXIT_SUCCESS;
}
int mudaValComissao(Ihandle *self){
	IupSetAttribute(tipoTextR, "VALUE", "Comissao");
	return EXIT_SUCCESS;
}
int mudaValVendas(Ihandle *self){
	IupSetAttribute(tipoTextR, "VALUE", "Vendas");
	return EXIT_SUCCESS;
}
int mudaValDiversos(Ihandle *self){
	IupSetAttribute(tipoTextR, "VALUE", "Diversos");
	return EXIT_SUCCESS;
}

int mudaRelGeral(Ihandle *self){
	IupSetAttribute(rTextRO, "VALUE", "Geral");
	return EXIT_SUCCESS;
}
int mudaRelMoradia(Ihandle *self){
	IupSetAttribute(rTextRO, "VALUE", "Moradia");
	return EXIT_SUCCESS;
}
int mudaRelEstudo(Ihandle *self){
	IupSetAttribute(rTextRO, "VALUE", "Estudo");
	return EXIT_SUCCESS;
}
int mudaRelConducao(Ihandle *self){
	IupSetAttribute(rTextRO, "VALUE", "Conducao");
	return EXIT_SUCCESS;
}
int mudaRelAlimentacao(Ihandle *self){
	IupSetAttribute(rTextRO, "VALUE", "Alimentacao");
	return EXIT_SUCCESS;
}
int mudaRelOutros(Ihandle *self){
	IupSetAttribute(rTextRO, "VALUE", "Outros");
	return EXIT_SUCCESS;
}
int mudaRelSalario(Ihandle *self){
	IupSetAttribute(rTextRO, "VALUE", "Salario");
	return EXIT_SUCCESS;
}
int mudaRelAdiantamento(Ihandle *self){
	IupSetAttribute(rTextRO, "VALUE", "Adiantamento");
	return EXIT_SUCCESS;
}
int mudaRelComissao(Ihandle *self){
	IupSetAttribute(rTextRO, "VALUE", "Comissao");
	return EXIT_SUCCESS;
}
int mudaRelVendas(Ihandle *self){
	IupSetAttribute(rTextRO, "VALUE", "Vendas");
	return EXIT_SUCCESS;
}
int mudaRelDiversos(Ihandle *self){
	IupSetAttribute(rTextRO, "VALUE", "Diversos");
	return EXIT_SUCCESS;
}


int salvarGasto(Ihandle *self){
	//int voltaCart();
	char *gastoC = IupGetAttribute(valorText, "VALUE");
	char *diaC = IupGetAttribute(diaTextG, "VALUE");
	char *mesC = IupGetAttribute(mesTextG, "VALUE");
	char *anoC = IupGetAttribute(anoTextG, "VALUE");
	char *desc = IupGetAttribute(descTextG, "VALUE");
	
	char ch1 = ' ';
	char ch2 = '_';
	
	char d[100];
	
	int tam = strlen(desc);
	int i;
	for(i = 0; i < tam; i++){
		if(desc[i] == ch1){
			d[i] = ch2;
		}
		else{
			d[i] = desc[i];
		}
	}
	
	
	float gasto = atof(gastoC);
	int dia = atoi(diaC);
	int mes = atoi(mesC);
	int ano = atoi(anoC);
	
	char *tipo = IupGetAttribute(tipoTextRO2, "VALUE");
	
	float saldo = atof(c.saldo);
	
	if(dia < 1 || dia > 31 || mes < 1 || mes > 12){
		IupMessage("Erro", "Insira uma data valida");
	}
	else{
	
	if(saldo < gasto){
		IupMessage("Erro", "Você nao possui saldo suficiente para registrar esse gasto");
	}
	else{
		char* ext = "_gasto.txt";
    	char nomeArqGasto[strlen(c.login.usuario)+strlen(ext)+1];
    	snprintf( nomeArqGasto, sizeof( nomeArqGasto ), "%s%s", c.login.usuario, ext );//forma a string variavel + .txt

    	char* ext2 = "_info.txt";
    	char nomeArqInfo[strlen(c.login.usuario)+strlen(ext2)+1];
    	snprintf( nomeArqInfo, sizeof( nomeArqInfo ), "%s%s", c.login.usuario, ext2 );
    	
    	saldo = saldo - gasto;
    	
    	FILE* fa = fopen(nomeArqGasto, "a");
        fprintf(fa, "%d %d %d   %s   %.2f   %s\n", dia, mes, ano, tipo, gasto, d);
        fclose(fa);


        FILE* fw = fopen(nomeArqInfo, "w");
        fprintf(fw, "%s\n", c.login.usuario);
        fprintf(fw, "%s\n", c.login.senha);
        fprintf(fw, "%.2f\n", saldo);
        fprintf(fw, "%s", c.poupanca);
        fclose(fw);
        
        FILE* fr = fopen(nomeArqInfo, "r");
        fscanf(fr, "%s", c.login.usuario);
        fscanf(fr, "%s", c.login.senha);
        fscanf(fr, "%s", c.saldo);
        fscanf(fr, "%s", c.poupanca);
        fclose(fr);

		char msg[strlen("Novo saldo: RS ")+strlen(c.saldo)+1];
    	snprintf( msg, sizeof( msg ), "%s%s", "Novo saldo: RS ", c.saldo );//concatenar string

        IupMessage("Sucesso", msg);
        voltaCartG(self);
        return EXIT_SUCCESS;
	}
	}
	return EXIT_SUCCESS;
}

int menuGasto2Func(Ihandle *self){
	
	
	char *tipo = IupGetAttribute(tipoTextRO, "VALUE");
	
	char label1[strlen("Valor do gasto para ")+strlen(tipo)+1];
    snprintf( label1, sizeof( label1 ), "%s%s", "Valor do gasto para ", tipo );//concatenar string
	
	tipoTextRO2 = IupText(NULL);
	IupSetAttribute(tipoTextRO2, "READONLY", "YES");
	IupSetAttribute(tipoTextRO2, "VALUE", tipo);
	valorLabel = IupLabel(label1);
	valorText = IupText(NULL);
	IupSetAttribute(valorText, "MASK", "[+/-]?(/d+/.?/d*|/./d+)");
	diaLabelG = IupLabel("Dia:");
	diaTextG = IupText(NULL);
	IupSetAttribute(diaTextG, "MASK", "/d+");
	mesLabelG = IupLabel("Mes:");
	mesTextG = IupText(NULL);
	IupSetAttribute(diaTextG, "MASK", "/d+");
	anoLabelG = IupLabel("Ano:");
	anoTextG = IupText(NULL);
	IupSetAttribute(diaTextG, "MASK", "/d+");
	descLabelG = IupLabel("Descrição do gasto");
	descTextG = IupText(NULL);
	//IupSetAttribute(descTextG, "MULTILINE", "YES");
	IupSetAttribute(descTextG, "SIZE", "400x50");
	btnSalvarG = IupButton("Salvar Gasto", NULL);
	btnVoltarG = IupButton("Voltar", NULL);
	
	vboxG= IupVbox(
		tipoTextRO2,
		valorLabel,
		valorText,
		diaLabelG,
		diaTextG,
		mesLabelG,
		mesTextG,
		anoLabelG,
		anoTextG,
		descLabelG,
		descTextG,
		btnSalvarG,
		btnVoltarG,
		NULL
  	);
  	menuG = IupDialog(vboxG);
  	IupSetAttribute(menuG, "TITLE", "Valor do gasto");
  	IupSetAttribute(vboxG, "ALIGNMENT", "ACENTER");
  	IupSetAttribute(vboxG, "GAP", "10");
  	IupSetAttribute(vboxG, "MARGIN", "80x80");
  	IupShowXY(menuG, IUP_CENTER, IUP_CENTER);
  
  	//IupDestroy(menuGasto);
  
  	IupSetCallback(btnSalvarG, "ACTION", (Icallback) salvarGasto);
  	IupSetCallback(btnVoltarG, "ACTION", (Icallback) voltaCartG);
  
  	IupMainLoop();
  	return EXIT_SUCCESS;
	
	
}

int menuGastoFunc(Ihandle *self){
	tipoLabel = IupLabel("Selecione um tipo de gasto");
	selectLabel = IupLabel("Tipo selecionado");
	tipoTextRO = IupText(NULL);
	IupSetAttribute(tipoTextRO, "READONLY", "YES");
	IupSetAttribute(tipoTextRO, "VALUE", "Moradia");
	btnMoradia = IupButton("Moradia", NULL);
	btnEstudo = IupButton("Estudo", NULL);
	btnConducao = IupButton("Conducao", NULL);
	btnAlimentacao = IupButton("Alimentacao", NULL);
	btnOutros = IupButton("Outros", NULL);
	btnProsseguir = IupButton("Prosseguir", NULL);
	btnVoltarGastoMenu = IupButton("Voltar", NULL);
	
	vboxGasto = IupVbox(
		tipoLabel,
		btnMoradia,
		btnEstudo,
		btnConducao,
		btnAlimentacao,
		btnOutros,
		selectLabel,
		tipoTextRO,
		btnProsseguir,
		btnVoltarGastoMenu,
		NULL
  	);
  	menuGasto = IupDialog(vboxGasto);
  	IupSetAttribute(menuGasto, "TITLE", "Menu de gastos");
  	IupSetAttribute(vboxGasto, "ALIGNMENT", "ACENTER");
  	IupSetAttribute(vboxGasto, "GAP", "10");
  	IupSetAttribute(vboxGasto, "MARGIN", "80x80");
  	IupShowXY(menuGasto, IUP_CENTER, IUP_CENTER);
  	
  	//IupDestroy(menuCart);
  
  	IupSetCallback(btnMoradia, "ACTION", (Icallback) mudaValMoradia);
  	IupSetCallback(btnEstudo, "ACTION", (Icallback) mudaValEstudo);
  	IupSetCallback(btnConducao, "ACTION", (Icallback) mudaValConducao);
  	IupSetCallback(btnAlimentacao, "ACTION", (Icallback) mudaValAlimentacao);
  	IupSetCallback(btnOutros, "ACTION", (Icallback) mudaValOutros);
  	IupSetCallback(btnProsseguir, "ACTION", (Icallback) menuGasto2Func);
  	IupSetCallback(btnVoltarGastoMenu, "ACTION", (Icallback) voltaCartGasto);
  
  	IupMainLoop();
  	return EXIT_SUCCESS;
	
	
}



int salvarReceita(Ihandle *self){
	int voltaCart();
	char *receitaC = IupGetAttribute(valorTextR, "VALUE");
	char *diaCr = IupGetAttribute(diaTextR, "VALUE");
	char *mesCr = IupGetAttribute(mesTextR, "VALUE");
	char *anoCr = IupGetAttribute(anoTextR, "VALUE");
	char *desc = IupGetAttribute(descTextR, "VALUE");
	
	char ch1 = ' ';
	char ch2 = '_';
	
	char d[100];
	
	int tam = strlen(desc);
	int i;
	for(i = 0; i < tam; i++){
		if(desc[i] == ch1){
			d[i] = ch2;
		}
		else{
			d[i] = desc[i];
		}
	}
	
	float receita = atof(receitaC);
	int diar = atoi(diaCr);
	int mesr = atoi(mesCr);
	int anor = atoi(anoCr);
	
	char *tipo = IupGetAttribute(tipoTextR2, "VALUE");
	
	float saldo = atof(c.saldo);
	
	if(diar < 1 || diar > 31 || mesr < 1 || mesr > 12){
		IupMessage("Erro", "Insira uma data valida");
	}
	else{
		char* ext = "_receita.txt";
    	char nomeArqReceita[strlen(c.login.usuario)+strlen(ext)+1];
    	snprintf( nomeArqReceita, sizeof( nomeArqReceita ), "%s%s", c.login.usuario, ext );//forma a string variavel + .txt

    	char* ext2 = "_info.txt";
    	char nomeArqInfo[strlen(c.login.usuario)+strlen(ext2)+1];
    	snprintf( nomeArqInfo, sizeof( nomeArqInfo ), "%s%s", c.login.usuario, ext2 );
    	
    	saldo = saldo + receita;
    	
    	FILE* fa = fopen(nomeArqReceita, "a");
        fprintf(fa, "%d %d %d   %s   %.2f   %s\n", diar, mesr, anor, tipo, receita, d);
        fclose(fa);


        FILE* fw = fopen(nomeArqInfo, "w");
        fprintf(fw, "%s\n", c.login.usuario);
        fprintf(fw, "%s\n", c.login.senha);
        fprintf(fw, "%.2f\n", saldo);
        fprintf(fw, "%s", c.poupanca);
        fclose(fw);
        
        FILE* fr = fopen(nomeArqInfo, "r");
        fscanf(fr, "%s", c.login.usuario);
        fscanf(fr, "%s", c.login.senha);
        fscanf(fr, "%s", c.saldo);
        fscanf(fr, "%s", c.poupanca);
        fclose(fr);

		char msg[strlen("Novo saldo: RS ")+strlen(c.saldo)+1];
    	snprintf( msg, sizeof( msg ), "%s%s", "Novo saldo: RS ", c.saldo );//concatenar string

        IupMessage("Sucesso", msg);
        voltaCartR(self);
        return EXIT_SUCCESS;
	}
	return EXIT_SUCCESS;
}

int menuReceita2Func(Ihandle *self){
	
	
	char *tipo = IupGetAttribute(tipoTextR, "VALUE");
	
	char label1[strlen("Valor da receita para ")+strlen(tipo)+1];
    snprintf( label1, sizeof( label1 ), "%s%s", "Valor do gasto para ", tipo );//concatenar string
	
	tipoTextR2 = IupText(NULL);
	IupSetAttribute(tipoTextR2, "READONLY", "YES");
	IupSetAttribute(tipoTextR2, "VALUE", tipo);
	valorLabelR = IupLabel(label1);
	valorTextR = IupText(NULL);
	IupSetAttribute(valorTextR, "MASK", "[+/-]?(/d+/.?/d*|/./d+)");
	diaLabelR = IupLabel("Dia:");
	diaTextR = IupText(NULL);
	IupSetAttribute(diaTextR, "MASK", "/d+");
	mesLabelR = IupLabel("Mes:");
	mesTextR = IupText(NULL);
	IupSetAttribute(diaTextR, "MASK", "/d+");
	anoLabelR = IupLabel("Ano:");
	anoTextR = IupText(NULL);
	IupSetAttribute(diaTextR, "MASK", "/d+");
	descLabelR = IupLabel("Descrição da receita");
	descTextR = IupText(NULL);
	//IupSetAttribute(descTextG, "MULTILINE", "YES");
	IupSetAttribute(descTextR, "SIZE", "400x50");
	btnSalvarR = IupButton("Salvar Receita", NULL);
	btnVoltarR = IupButton("Voltar", NULL);
	
	vboxR = IupVbox(
		tipoTextR2,
		valorLabelR,
		valorTextR,
		diaLabelR,
		diaTextR,
		mesLabelR,
		mesTextR,
		anoLabelR,
		anoTextR,
		descLabelR,
		descTextR,
		btnSalvarR,
		btnVoltarR,
		NULL
  	);
  	menuR = IupDialog(vboxR);
  	IupSetAttribute(menuR, "TITLE", "Valor da receita");
  	IupSetAttribute(vboxR, "ALIGNMENT", "ACENTER");
  	IupSetAttribute(vboxR, "GAP", "10");
  	IupSetAttribute(vboxR, "MARGIN", "80x80");
  	//
  	IupShowXY(menuR, IUP_CENTER, IUP_CENTER);
  
  	//IupDestroy(menuReceita);
  
  	IupSetCallback(btnSalvarR, "ACTION", (Icallback) salvarReceita);
  	IupSetCallback(btnVoltarR, "ACTION", (Icallback) voltaCartR);
  
  	IupMainLoop();
  	return EXIT_SUCCESS;
	
	
}

int menuReceitaFunc(Ihandle *self){
	
	tipoLabelR = IupLabel("Selecione um tipo de receita");
	selectLabelR = IupLabel("Tipo selecionado");
	tipoTextR = IupText(NULL);
	IupSetAttribute(tipoTextR, "READONLY", "YES");
	IupSetAttribute(tipoTextR, "VALUE", "Salario");
	btnSalario = IupButton("Salario", NULL);
	btnAdiantamento = IupButton("Adiantamento", NULL);
	btnComissao = IupButton("Comissao", NULL);
	btnVendas = IupButton("Vendas", NULL);
	btnDiversos = IupButton("Diversos", NULL);
	btnProsseguirR = IupButton("Prosseguir", NULL);
	btnVoltarReceitaMenu = IupButton("Voltar", NULL);
	
	vboxReceita = IupVbox(
		tipoLabelR,
		btnSalario,
		btnAdiantamento,
		btnComissao,
		btnVendas,
		btnDiversos,
		selectLabelR,
		tipoTextR,
		btnProsseguirR,
		btnVoltarReceitaMenu,
		NULL
  	);
  	menuReceita = IupDialog(vboxReceita);
  	IupSetAttribute(menuReceita, "TITLE", "Menu de Receitas");
  	IupSetAttribute(vboxReceita, "ALIGNMENT", "ACENTER");
  	IupSetAttribute(vboxReceita, "GAP", "10");
  	IupSetAttribute(vboxReceita, "MARGIN", "80x80");
  	IupShowXY(menuReceita, IUP_CENTER, IUP_CENTER);
  	
  	//IupDestroy(menuCart);
  
  	IupSetCallback(btnSalario, "ACTION", (Icallback) mudaValSalario);
  	IupSetCallback(btnAdiantamento, "ACTION", (Icallback) mudaValAdiantamento);
  	IupSetCallback(btnComissao, "ACTION", (Icallback) mudaValComissao);
  	IupSetCallback(btnVendas, "ACTION", (Icallback) mudaValVendas);
  	IupSetCallback(btnDiversos, "ACTION", (Icallback) mudaValDiversos);
  	IupSetCallback(btnProsseguirR, "ACTION", (Icallback) menuReceita2Func);
  	IupSetCallback(btnVoltarReceitaMenu, "ACTION", (Icallback) voltaCartReceita);
  
  	IupMainLoop();
  	return EXIT_SUCCESS;
	
	
}



void renderPoupanca(int diaR, int mesR, int anoR){
	char operacao[100];
    float val;
    char tipo[] = "Aniversario";
    
    int dia;
    int mes;
    int ano;
    
    int diaA;
    int mesA;
    int anoA;
    
	char* ext = "_info.txt";
    char* ext2 = "_poupanca.txt";

    int li = contarLinhas(ext2);

    char nomeArqInfo[strlen(c.login.usuario)+strlen(ext)+1];
    snprintf( nomeArqInfo, sizeof( nomeArqInfo ), "%s%s", c.login.usuario, ext );

    char nomeArqPoupanca[strlen(c.login.usuario)+strlen(ext2)+1];
    snprintf( nomeArqPoupanca, sizeof( nomeArqPoupanca ), "%s%s", c.login.usuario, ext2 );
    
    FILE* f = fopen(nomeArqInfo, "r");
    fscanf(f, "%s", c.login.usuario);
    fscanf(f, "%s", c.login.senha);
    fscanf(f, "%s", c.saldo);
    fscanf(f, "%s", c.poupanca);
    fclose(f);
    
    float poupanca = atof(c.poupanca);

    FILE* fw = fopen(nomeArqInfo, "w");
    FILE* fa = fopen(nomeArqPoupanca, "r");
	   
    int i;
    for(i = 0; i < li; i++){

        fscanf(fa, "%d", &dia);
        fscanf(fa, "%d", &mes);
        fscanf(fa, "%d", &ano);

        fscanf(fa, "%s", operacao);
        fscanf(fa, "%f", &val);
    }
    fclose(fa);
    FILE* fr = fopen(nomeArqPoupanca, "a"); 
    diaA = dia;
    mesA = mes;
    anoA = ano;
    while((diaA < diaR) || (mesA < mesR) || (anoA < anoR)){
        diaA += 1;
        if(diaA > 31 && mesA < 12){
            diaA = 1;
            mesA += 1;
        }
        if(mesA >= 12 && diaA > 31){
            diaA = 1;
            mesA = 1;
            anoA += 1;
        }
        if(diaA == dia){
            poupanca = poupanca + ((poupanca * 0.3755)/100);
            fprintf(fr, "%d %d %d   %s   %.2f\n", diaA, mesA, anoA, tipo, poupanca);
            
        }
            
    }

    fprintf(fw, "%s\n", c.login.usuario);
    fprintf(fw, "%s\n", c.login.senha);
    fprintf(fw, "%s\n", c.saldo);
    fprintf(fw, "%.2f\n", poupanca);
    
    FILE* fi = fopen(nomeArqInfo, "r");
    fscanf(fi, "%s", c.login.usuario);
    fscanf(fi, "%s", c.login.senha);
    fscanf(fi, "%s", c.saldo);
    fscanf(fi, "%s", c.poupanca);
    fclose(fi);

    fclose(fw);
    fclose(fr);
    
}

int salvarPoupancaA(Ihandle *self){
	char ap[] = "Aplicar";
	
	char *apC = IupGetAttribute(valorTextAplicar, "VALUE");
	char *diaC = IupGetAttribute(diaTextAplicar, "VALUE");
	char *mesC = IupGetAttribute(mesTextAplicar, "VALUE");
	char *anoC = IupGetAttribute(anoTextAplicar, "VALUE");
	
	float apV = atof(apC);
	int dia = atoi(diaC);
	int mes = atoi(mesC);
	int ano = atoi(anoC);
	
	renderPoupanca(dia, mes, ano);
	
	float saldo = atof(c.saldo);
	float poupanca = atof(c.poupanca);
	
	if(dia < 1 || dia > 31 || mes < 1 || mes > 12){
		IupMessage("Erro", "Insira uma data valida");
	}
	else{
		if(apV > saldo){
			IupMessage("Erro", "Você nao possui saldo suficiente para aplicar essa quantia");
		}
		else{
			char* ext = "_info.txt";
    		char* ext2 = "_poupanca.txt";

    		char nomeArqInfo[strlen(c.login.usuario)+strlen(ext)+1];
    		snprintf( nomeArqInfo, sizeof( nomeArqInfo ), "%s%s", c.login.usuario, ext );

    		char nomeArqPoupanca[strlen(c.login.usuario)+strlen(ext2)+1];
    		snprintf( nomeArqPoupanca, sizeof( nomeArqPoupanca ), "%s%s", c.login.usuario, ext2 );
    		
    		//
    		saldo = saldo - apV;
    		poupanca = poupanca + apV;
    	
    		FILE* fa = fopen(nomeArqPoupanca, "a");
        	fprintf(fa, "%d %d %d   %s   %.2f\n", dia, mes, ano, ap, apV);
        	fclose(fa);


       	 	FILE* fw = fopen(nomeArqInfo, "w");
        	fprintf(fw, "%s\n", c.login.usuario);
        	fprintf(fw, "%s\n", c.login.senha);
        	fprintf(fw, "%.2f\n", saldo);
        	fprintf(fw, "%.2f", poupanca);
        	fclose(fw);
        
        	FILE* fr = fopen(nomeArqInfo, "r");
        	fscanf(fr, "%s", c.login.usuario);
        	fscanf(fr, "%s", c.login.senha);
        	fscanf(fr, "%s", c.saldo);
        	fscanf(fr, "%s", c.poupanca);
        	fclose(fr);

			char msg[strlen("Novo saldo: RS ")+strlen(c.saldo)+1];
    		snprintf( msg, sizeof( msg ), "%s%s", "Novo saldo: RS ", c.saldo );//concatenar string

        	IupMessage("Sucesso", msg);
        	
        	char msg2[strlen("Nova poupanca: RS ")+strlen(c.poupanca)+1];
    		snprintf( msg2, sizeof( msg2 ), "%s%s", "Nova poupanca: RS ", c.poupanca );//concatenar string

        	IupMessage("Sucesso", msg2);
        	voltaCartAplicar(self);
        	return EXIT_SUCCESS;
		}
	}
	
	
}

int menuAplicarPoupanca(Ihandle *self){
	int menuPoupancaFunc();

	valorLabelAplicar = IupLabel("Valor da aplicacao");
	valorTextAplicar = IupText(NULL);
	IupSetAttribute(valorTextAplicar, "MASK", "[+/-]?(/d+/.?/d*|/./d+)");
	diaLabelAplicar = IupLabel("Dia:");
	diaTextAplicar = IupText(NULL);
	IupSetAttribute(diaTextAplicar, "MASK", "/d+");
	mesLabelAplicar = IupLabel("Mes:");
	mesTextAplicar = IupText(NULL);
	IupSetAttribute(mesTextAplicar, "MASK", "/d+");
	anoLabelAplicar = IupLabel("Ano:");
	anoTextAplicar = IupText(NULL);
	IupSetAttribute(anoTextAplicar, "MASK", "/d+");
	btnSalvarAplicar = IupButton("Aplicar", NULL);
	btnVoltarAplicar = IupButton("Voltar", NULL);
	
	vboxAplicar = IupVbox(
		valorLabelAplicar,
		valorTextAplicar,
		diaLabelAplicar,
		diaTextAplicar,
		mesLabelAplicar,
		mesTextAplicar,
		anoLabelAplicar,
		anoTextAplicar,
		btnSalvarAplicar,
		btnVoltarAplicar,
		NULL
  	);
  	menuAplicar = IupDialog(vboxAplicar);
  	IupSetAttribute(menuAplicar, "TITLE", "Valor da aplicacao");
  	IupSetAttribute(vboxAplicar, "ALIGNMENT", "ACENTER");
  	IupSetAttribute(vboxAplicar, "GAP", "10");
  	IupSetAttribute(vboxAplicar, "MARGIN", "80x80");
  	IupShowXY(menuAplicar, IUP_CENTER, IUP_CENTER);
  
  	//IupDestroy(menuPoupanca);
  
  	IupSetCallback(btnSalvarAplicar, "ACTION", (Icallback) salvarPoupancaA);
  	IupSetCallback(btnVoltarAplicar, "ACTION", (Icallback) voltaCartAplicar);
  
  	IupMainLoop();
  	return EXIT_SUCCESS;
	
}

int salvarPoupancaR(Ihandle *self){
	char re[] = "Resgatar";
	
	char *reC = IupGetAttribute(valorTextResgatar, "VALUE");
	char *diaC = IupGetAttribute(diaTextResgatar, "VALUE");
	char *mesC = IupGetAttribute(mesTextResgatar, "VALUE");
	char *anoC = IupGetAttribute(anoTextResgatar, "VALUE");
	
	float reV = atof(reC);
	int dia = atoi(diaC);
	int mes = atoi(mesC);
	int ano = atoi(anoC);
	
	renderPoupanca(dia, mes, ano);
	
	char* ext = "_info.txt";
    char* ext2 = "_poupanca.txt";

    char nomeArqInfo[strlen(c.login.usuario)+strlen(ext)+1];
    snprintf( nomeArqInfo, sizeof( nomeArqInfo ), "%s%s", c.login.usuario, ext );

    char nomeArqPoupanca[strlen(c.login.usuario)+strlen(ext2)+1];
    snprintf( nomeArqPoupanca, sizeof( nomeArqPoupanca ), "%s%s", c.login.usuario, ext2 );
	
	FILE* f = fopen(nomeArqInfo, "r");
    fscanf(f, "%s", c.login.usuario);
    fscanf(f, "%s", c.login.senha);
    fscanf(f, "%s", c.saldo);
    fscanf(f, "%s", c.poupanca);
    fclose(f);
	
	float saldo = atof(c.saldo);
	float poupanca = atof(c.poupanca);
	
	if(dia < 1 || dia > 31 || mes < 1 || mes > 12){
		IupMessage("Erro", "Insira uma data valida");
	}
	else{
		if(reV > poupanca){
			IupMessage("Erro", "Você nao possui saldo suficiente para resgatar essa quantia");
		}
		else{
			
    		
    		//
    		saldo = saldo + reV;
    		poupanca = poupanca - reV;
    	
    		FILE* fa = fopen(nomeArqPoupanca, "a");
        	fprintf(fa, "%d %d %d   %s   %.2f\n", dia, mes, ano, re, reV);
        	fclose(fa);


       	 	FILE* fw = fopen(nomeArqInfo, "w");
        	fprintf(fw, "%s\n", c.login.usuario);
        	fprintf(fw, "%s\n", c.login.senha);
        	fprintf(fw, "%.2f\n", saldo);
        	fprintf(fw, "%.2f", poupanca);
        	fclose(fw);
        
        	FILE* fr = fopen(nomeArqInfo, "r");
        	fscanf(fr, "%s", c.login.usuario);
        	fscanf(fr, "%s", c.login.senha);
        	fscanf(fr, "%s", c.saldo);
        	fscanf(fr, "%s", c.poupanca);
        	fclose(fr);

			char msg[strlen("Novo saldo: RS ")+strlen(c.saldo)+1];
    		snprintf( msg, sizeof( msg ), "%s%s", "Novo saldo: RS ", c.saldo );//concatenar string

        	IupMessage("Sucesso", msg);
        	
        	char msg2[strlen("Nova poupanca: RS ")+strlen(c.poupanca)+1];
    		snprintf( msg2, sizeof( msg2 ), "%s%s", "Nova poupanca: RS ", c.poupanca );//concatenar string

        	IupMessage("Sucesso", msg2);
        	voltaCartResgatar(self);
        	return EXIT_SUCCESS;
		}
	}
	
	
}

int menuResgatarPoupanca(Ihandle *self){
	int menuPoupancaFunc();

	valorLabelResgatar = IupLabel("Valor do resgate");
	valorTextResgatar = IupText(NULL);
	IupSetAttribute(valorTextResgatar, "MASK", "[+/-]?(/d+/.?/d*|/./d+)");
	diaLabelResgatar = IupLabel("Dia:");
	diaTextResgatar = IupText(NULL);
	IupSetAttribute(diaTextResgatar, "MASK", "/d+");
	mesLabelResgatar = IupLabel("Mes:");
	mesTextResgatar = IupText(NULL);
	IupSetAttribute(mesTextResgatar, "MASK", "/d+");
	anoLabelResgatar = IupLabel("Ano:");
	anoTextResgatar = IupText(NULL);
	IupSetAttribute(anoTextResgatar, "MASK", "/d+");
	btnSalvarResgatar = IupButton("Resgatar", NULL);
	btnVoltarResgatar = IupButton("Voltar", NULL);
	
	vboxResgatar = IupVbox(
		valorLabelResgatar,
		valorTextResgatar,
		diaLabelResgatar,
		diaTextResgatar,
		mesLabelResgatar,
		mesTextResgatar,
		anoLabelResgatar,
		anoTextResgatar,
		btnSalvarResgatar,
		btnVoltarResgatar,
		NULL
  	);
  	menuResgatar = IupDialog(vboxResgatar);
  	IupSetAttribute(menuResgatar, "TITLE", "Valor do resgate");
  	IupSetAttribute(vboxResgatar, "ALIGNMENT", "ACENTER");
  	IupSetAttribute(vboxResgatar, "GAP", "10");
  	IupSetAttribute(vboxResgatar, "MARGIN", "80x80");
  	IupShowXY(menuResgatar, IUP_CENTER, IUP_CENTER);
  
  	//IupDestroy(menuPoupanca);
  
  	IupSetCallback(btnSalvarResgatar, "ACTION", (Icallback) salvarPoupancaR);
  	IupSetCallback(btnVoltarResgatar, "ACTION", (Icallback) voltaCartResgatar);
  
  	IupMainLoop();
  	return EXIT_SUCCESS;
	
}

int menuPoupancaFunc(Ihandle *self){
	btnAplicar = IupButton("Aplicar", NULL);
	btnResgatar = IupButton("Resgatar", NULL);
	btnVoltarPoupanca = IupButton("Voltar", NULL);
	
	vboxPoupanca = IupVbox(
		btnAplicar,
		btnResgatar,
		btnVoltarPoupanca,
		NULL
  	);
  	menuPoupanca = IupDialog(vboxPoupanca);
  	IupSetAttribute(menuPoupanca, "TITLE", "Menu da Poupanca");
  	IupSetAttribute(vboxPoupanca, "ALIGNMENT", "ACENTER");
  	IupSetAttribute(vboxPoupanca, "GAP", "10");
  	IupSetAttribute(vboxPoupanca, "MARGIN", "80x80");
  	IupShowXY(menuPoupanca, IUP_CENTER, IUP_CENTER);
  
  	//IupDestroy(menuCart);
  
  	IupSetCallback(btnAplicar, "ACTION", (Icallback) menuAplicarPoupanca);
  	IupSetCallback(btnResgatar, "ACTION", (Icallback) menuResgatarPoupanca);
  	IupSetCallback(btnVoltarPoupanca, "ACTION", (Icallback) voltaCartPoupanca);
  
  	IupMainLoop();
  	return EXIT_SUCCESS;
}



int imprimirMov(Ihandle *self){
	char geral[] = "Geral";
	char tArq[100];
    char tArqr[100];
    char desc[100];
    char descr[100];
    float valor, valorr;
    float total = 0;
    float totalGeral = 0;
    char ch1 = '_';
	char ch2 = ' ';
	char d[100];
	char dr[100];
	
	int dia, mes, ano;
	int diar, mesr, anor;
	
	char *tipo = IupGetAttribute(tText, "VALUE");
	char *diC = IupGetAttribute(diText, "VALUE");
	char *miC = IupGetAttribute(miText, "VALUE");
	char *aiC = IupGetAttribute(aiText, "VALUE");
	char *dfC = IupGetAttribute(dfText, "VALUE");
	char *mfC = IupGetAttribute(mfText, "VALUE");
	char *afC = IupGetAttribute(afText, "VALUE");
	
	int di = atoi(diC);
	int mi = atoi(miC);
	int ai = atoi(aiC);
	int df = atoi(dfC);
	int mf = atoi(mfC);
	int af = atoi(afC);
	
	df += 1;
	if(df > 31 && mf < 12){
		df = 1;
		mf += 1;
	}
	if(df > 31 && mf == 12){
		df = 1;
		mf = 1;
		af += 1;
	}
	
	if(di < 1 || di > 31 || df < 1 || df > 31 || mi < 1 || mi > 12 || mf < 1 || mf > 12){
		IupMessage("Erro", "Insira uma data valida");
	}
	else{
		char* ext = "_gasto.txt";
    	char* ext2 = "_receita.txt";
    	
    	char nomeArqGasto[strlen(c.login.usuario)+strlen(ext)+1];
    	snprintf( nomeArqGasto, sizeof( nomeArqGasto ), "%s%s", c.login.usuario, ext );//forma a string variavel + .txt

    	char nomeArqReceita[strlen(c.login.usuario)+strlen(ext2)+1];
    	snprintf( nomeArqReceita, sizeof( nomeArqReceita ), "%s%s", c.login.usuario, ext2 );
    	
    	int lig = contarLinhas(ext);
    	int lir = contarLinhas(ext2);
		
		relaLabel = IupLabel("Relatorio:");
		relaText = IupText(NULL);
		IupSetAttribute(relaText, "READONLY", "YES");
		IupSetAttribute(relaText, "MULTILINE", "YES");
		IupSetAttribute(relaText, "SIZE", "400x250");
		
		relaVoltar = IupButton("Voltar", NULL);
		
		relavbox = IupVbox(
			relaLabel,
			relaText,
			relaVoltar,
			NULL
  		);
		relamenu = IupDialog(relavbox);
  		IupSetAttribute(relamenu, "TITLE", "Relatorio");
  		IupSetAttribute(relavbox, "ALIGNMENT", "ACENTER");
  		IupSetAttribute(relavbox, "GAP", "10");
  		IupSetAttribute(relavbox, "MARGIN", "80x80");
  		IupShowXY(relamenu, IUP_CENTER, IUP_CENTER);
  		
  		//IupDestroy(menuData);
  		
  		char didf[300];
  		char rline[300];
  		char ma[300];
    	snprintf( didf, sizeof( didf ),"%d/%d/%d  %d/%d/%d\n", di, mi, ai, df, mf, af);
    	snprintf( rline, sizeof( rline ),"%s", "____________________________________________\n");
    	snprintf( ma, sizeof( ma ),"Mes/Ano: %d/%d\n\n", mi, ai);
  		
  		IupSetAttribute(relaText, "INSERT", didf);
  		IupSetAttribute(relaText, "INSERT", rline);
  		IupSetAttribute(relaText, "INSERT", ma);
  		
  		char liGasto[300];
  		char liReceita[300];
  		char totmes[300];
  		char totper[300];
  		
  		while((di < df) || (mi < mf) || (ai < af)){
        FILE* frg = fopen(nomeArqGasto, "r");
        FILE* frr = fopen(nomeArqReceita, "r");
        int i;
        for(i = 0; i < lig; i++){
        	char desc[100];
            fscanf(frg,"%d", &dia);
            fscanf(frg,"%d", &mes);
            fscanf(frg,"%d", &ano);
            fscanf(frg,"%s", tArq);
            fscanf(frg,"%f", &valor);
            fscanf(frg,"%s", desc);
            char d[100];
			int tam = strlen(desc);
			int i;
			for(i = 0; i < tam; i++){
				if(desc[i] == ch1){
					d[i] = ch2;
				}
				else{
					d[i] = desc[i];
				}
			}
            if(strcmp(tipo, geral) == 0){
                if((di == dia) && (mi == mes) && (ai == ano)){
                	snprintf( liGasto, sizeof( liGasto ),"Data: %d/%d/%d   Tipo: %s   - R$%.2f    Descricao: %s\n", dia, mes, ano, tArq, valor, d);
                	IupSetAttribute(relaText, "INSERT", liGasto);
                    //printf("Data: %d/%d/%d   Tipo: %s   - R$%.2f\n", data.dia, data.mes, data.ano, tArq, valor);
                    total -= valor;
                }
            }
            else if(strcmp(tipo, tArq) == 0){
                if((di == dia) && (mi == mes) && (ai == ano)){
                	snprintf( liGasto, sizeof( liGasto ),"Data: %d/%d/%d   Tipo: %s   - R$%.2f    Descricao: %s\n", dia, mes, ano, tArq, valor, d);
                	IupSetAttribute(relaText, "INSERT", liGasto);
                    //printf("Data: %d/%d/%d   Tipo: %s   - R$%.2f\n", data.dia, data.mes, data.ano, tArq, valor);
                    total -= valor;
                }
            }
        }
        int j;
        for(j = 0; j < lir; j++){
        	char descr[100];
            fscanf(frr,"%d", &diar);
            fscanf(frr,"%d", &mesr);
            fscanf(frr,"%d", &anor);
            fscanf(frr,"%s", tArqr);
            fscanf(frr,"%f", &valorr);
            fscanf(frr,"%s", descr);
            char dr[100];
			int tam = strlen(descr);
			int i;
			for(i = 0; i < tam; i++){
				if(descr[i] == ch1){
					dr[i] = ch2;
				}
				else{
					dr[i] = descr[i];
				}
			}
            if(strcmp(tipo, geral) == 0){
                if((di == diar) && (mi == mesr) && (ai == anor)){
                	snprintf( liReceita, sizeof( liReceita ),"Data: %d/%d/%d   Tipo: %s   + R$%.2f    Descricao: %s\n", diar, mesr, anor, tArqr, valorr, dr);
                	IupSetAttribute(relaText, "INSERT", liReceita);
                    //printf("Data: %d/%d/%d   Tipo: %s   + R$%.2f\n", datar.dia, datar.mes, datar.ano, tArqr, valorr);
                    total += valorr;
                }
            }
            else if(strcmp(tipo, tArqr) == 0){
                if((di == diar) && (mi == mesr) && (ai == anor)){
                	snprintf( liReceita, sizeof( liReceita ),"Data: %d/%d/%d   Tipo: %s   + R$%.2f    Descricao: %s\n", diar, mesr, anor, tArqr, valorr, dr);
                	IupSetAttribute(relaText, "INSERT", liReceita);
                    //printf("Data: %d/%d/%d   Tipo: %s   + R$%.2f\n", datar.dia, datar.mes, datar.ano, tArqr, valor);
                    total += valor;
                }
            }
        }
        fclose(frg);
        fclose(frr);
        di += 1;
        if(di > 31 && mi < 12){
        	snprintf( totmes, sizeof( totmes ),"\nTotal do mes %d: R$ %.2f\n\n", mi, total);
        	IupSetAttribute(relaText, "INSERT", totmes);
            //printf("\nTotal do mes %d: R$%.2f\n\n", dataIni->mes, total);
            di = 1;
            mi += 1;
    		snprintf( ma, sizeof( ma ),"Mes/Ano: %d/%d\n\n", mi, ai);
    		IupSetAttribute(relaText, "INSERT", rline);
  			IupSetAttribute(relaText, "INSERT", ma);
            //printf("____________________________________________\n");
            //printf("Mes/Ano: %d/%d\n\n", dataIni->mes, dataIni->ano);
            totalGeral += total;
            total = 0;
        }
            
        if(mi >= 12 && di > 31){
        	snprintf( totmes, sizeof( totmes ),"\nTotal do mes %d: R$ %.2f\n\n", mi, total);
        	IupSetAttribute(relaText, "INSERT", totmes);
            //printf("\nTotal do mes %d: R$%.2f\n\n", dataIni->mes, total);
            di = 1;
            mi = 1;
            ai += 1;
            snprintf( ma, sizeof( ma ),"Mes/Ano: %d/%d\n\n", mi, ai);
    		IupSetAttribute(relaText, "INSERT", rline);
  			IupSetAttribute(relaText, "INSERT", ma);
            //printf("____________________________________________\n");
            //printf("Mes/Ano: %d/%d\n\n", dataIni->mes, dataIni->ano);
            totalGeral += total;
            total = 0;
        }
            
    }
    snprintf( totmes, sizeof( totmes ),"\nTotal do mes %d: R$ %.2f\n\n", mi, total);
    IupSetAttribute(relaText, "INSERT", totmes);
    //printf("\nTotal do mes %d: R$%.2f\n\n", dataIni->mes, total);
    totalGeral += total;
    snprintf( totper, sizeof( totper ),"\nTotal do periodo: R$ %.2f\n\n", totalGeral);
    IupSetAttribute(relaText, "INSERT", totper);
    //printf("\nTotal do periodo: R$%.2f\n\n", totalGeral);
  		

  		
  		
  		
  		
  		IupSetCallback(relaVoltar, "ACTION", (Icallback) voltaCartrelamenu);
  	
  		
  		
  		IupMainLoop();
  		return EXIT_SUCCESS;
		
	} 
}

int imprimirPou(Ihandle *self){
	char geral[] = "Geral";
	char tArq[100];
    float valor;
	
	int dia, mes, ano;
	
	char *diC = IupGetAttribute(diTextP, "VALUE");
	char *miC = IupGetAttribute(miTextP, "VALUE");
	char *aiC = IupGetAttribute(aiTextP, "VALUE");
	char *dfC = IupGetAttribute(dfTextP, "VALUE");
	char *mfC = IupGetAttribute(mfTextP, "VALUE");
	char *afC = IupGetAttribute(afTextP, "VALUE");
	
	int di = atoi(diC);
	int mi = atoi(miC);
	int ai = atoi(aiC);
	int df = atoi(dfC);
	int mf = atoi(mfC);
	int af = atoi(afC);
	
	df += 1;
	if(df > 31 && mf < 12){
		df = 1;
		mf += 1;
	}
	if(df > 31 && mf == 12){
		df = 1;
		mf = 1;
		af += 1;
	}
	
	if(di < 1 || di > 31 || df < 1 || df > 31 || mi < 1 || mi > 12 || mf < 1 || mf > 12){
		IupMessage("Erro", "Insira uma data valida");
	}
	else{
		char* ext = "_poupanca.txt";
    	
    	char nomeArqPoupanca[strlen(c.login.usuario)+strlen(ext)+1];
    	snprintf( nomeArqPoupanca, sizeof( nomeArqPoupanca ), "%s%s", c.login.usuario, ext );//forma a string variavel + .txt
    	
    	int lip = contarLinhas(ext);
		
		relaLabelP = IupLabel("Relatorio:");
		relaTextP = IupText(NULL);
		IupSetAttribute(relaTextP, "READONLY", "YES");
		IupSetAttribute(relaTextP, "MULTILINE", "YES");
		IupSetAttribute(relaTextP, "SIZE", "400x250");
		
		relaVoltarP = IupButton("Voltar", NULL);
		
		relavboxP = IupVbox(
			relaLabelP,
			relaTextP,
			relaVoltarP,
			NULL
  		);
		relamenuP = IupDialog(relavboxP);
  		IupSetAttribute(relamenuP, "TITLE", "Relatorio");
  		IupSetAttribute(relavboxP, "ALIGNMENT", "ACENTER");
  		IupSetAttribute(relavboxP, "GAP", "10");
  		IupSetAttribute(relavboxP, "MARGIN", "80x80");
  		IupShowXY(relamenuP, IUP_CENTER, IUP_CENTER);
  		
  		//IupDestroy(menuDataP);
  		
  		char didf[300];
  		char rline[300];
  		char ma[300];
    	snprintf( didf, sizeof( didf ),"%d/%d/%d  %d/%d/%d\n", di, mi, ai, df, mf, af);
    	snprintf( rline, sizeof( rline ),"%s", "____________________________________________\n");
    	snprintf( ma, sizeof( ma ),"Mes/Ano: %d/%d\n\n", mi, ai);
  		
  		IupSetAttribute(relaTextP, "INSERT", didf);
  		IupSetAttribute(relaTextP, "INSERT", rline);
  		IupSetAttribute(relaTextP, "INSERT", ma);
  		
  		char liPoupanca[300];
  		
  		while((di < df) || (mi < mf) || (ai < af)){
        FILE* frp = fopen(nomeArqPoupanca, "r");
        int i;
        for(i = 0; i < lip; i++){
        	char desc[100];
            fscanf(frp,"%d", &dia);
            fscanf(frp,"%d", &mes);
            fscanf(frp,"%d", &ano);
            fscanf(frp,"%s", tArq);
            fscanf(frp,"%f", &valor);
    
            if((di == dia) && (mi == mes) && (ai == ano)){
                snprintf( liPoupanca, sizeof( liPoupanca ),"Data: %d/%d/%d   Tipo: %s    R$%.2f\n", dia, mes, ano, tArq, valor);
                IupSetAttribute(relaTextP, "INSERT", liPoupanca);
                //printf("Data: %d/%d/%d   Tipo: %s   - R$%.2f\n", data.dia, data.mes, data.ano, tArq, valor);
            }
    	}
        fclose(frp);
        di += 1;
        if(di > 31 && mi < 12){

            di = 1;
            mi += 1;
    		snprintf( ma, sizeof( ma ),"Mes/Ano: %d/%d\n\n", mi, ai);
    		IupSetAttribute(relaTextP, "INSERT", rline);
  			IupSetAttribute(relaTextP, "INSERT", ma);
            //printf("____________________________________________\n");
            //printf("Mes/Ano: %d/%d\n\n", dataIni->mes, dataIni->ano);
        }
            
        if(mi >= 12 && di > 31){
        
            //printf("\nTotal do mes %d: R$%.2f\n\n", dataIni->mes, total);
            di = 1;
            mi = 1;
            ai += 1;
            snprintf( ma, sizeof( ma ),"Mes/Ano: %d/%d\n\n", mi, ai);
    		IupSetAttribute(relaTextP, "INSERT", rline);
  			IupSetAttribute(relaTextP, "INSERT", ma);
            //printf("____________________________________________\n");
            //printf("Mes/Ano: %d/%d\n\n", dataIni->mes, dataIni->ano);
        
        }
            
    }
 
  		
  		
  		
  		
  		IupSetCallback(relaVoltarP, "ACTION", (Icallback) voltaCartrelamenuP);
  	
  		
  		
  		IupMainLoop();
  		return EXIT_SUCCESS;
		
	} 
}

int menuIniFinMov(Ihandle *self){
	char *tipo = IupGetAttribute(rTextRO, "VALUE");
	
	tText = IupText(NULL);
	IupSetAttribute(tText, "READONLY", "YES");
	IupSetAttribute(tText, "VALUE", tipo);
	iLabel = IupLabel("Data Inicial:");
	diLabel = IupLabel("Dia");
	diText = IupText(NULL);
	IupSetAttribute(diText, "MASK", "/d+");
	miLabel = IupLabel("Mes");
	miText = IupText(NULL);
	IupSetAttribute(miText, "MASK", "/d+");
	aiLabel = IupLabel("Ano");
	aiText = IupText(NULL);
	IupSetAttribute(aiText, "MASK", "/d+");
	fLabel = IupLabel("Data Final:");
	dfLabel = IupLabel("Dia");
	dfText = IupText(NULL);
	IupSetAttribute(dfText, "MASK", "/d+");
	mfLabel = IupLabel("Mes");
	mfText = IupText(NULL);
	IupSetAttribute(mfText, "MASK", "/d+");
	afLabel = IupLabel("Ano");
	afText = IupText(NULL);
	IupSetAttribute(afText, "MASK", "/d+");
	btnDP = IupButton("Prosseguir", NULL);
	btnDV = IupButton("Voltar", NULL);
	
	vboxData = IupVbox(
		tText,
		iLabel,
		diLabel,
		diText,
		miLabel,
		miText,
		aiLabel,
		aiText,
		fLabel,
		dfLabel,
		dfText,
		mfLabel,
		mfText,
		afLabel,
		afText,
		btnDP,
		btnDV,
		NULL
  	);
  	menuData = IupDialog(vboxData);
  	IupSetAttribute(menuData, "TITLE", "Datas do relatorio");
  	IupSetAttribute(vboxData, "ALIGNMENT", "ACENTER");
  	IupSetAttribute(vboxData, "GAP", "10");
  	IupSetAttribute(vboxData, "MARGIN", "80x80");
  	IupShowXY(menuData, IUP_CENTER, IUP_CENTER);
  	
  	//IupDestroy(rmenuMov);
  
  	IupSetCallback(btnDP, "ACTION", (Icallback) imprimirMov);
  	IupSetCallback(btnDV, "ACTION", (Icallback) voltaCartData);
  	
  
  	IupMainLoop();
  	return EXIT_SUCCESS;
}

int menuIniFinPoup(Ihandle *self){
	iLabelP = IupLabel("Data Inicial:");
	diLabelP = IupLabel("Dia");
	diTextP = IupText(NULL);
	IupSetAttribute(diTextP, "MASK", "/d+");
	miLabelP = IupLabel("Mes");
	miTextP = IupText(NULL);
	IupSetAttribute(miTextP, "MASK", "/d+");
	aiLabelP = IupLabel("Ano");
	aiTextP = IupText(NULL);
	IupSetAttribute(aiTextP, "MASK", "/d+");
	fLabelP = IupLabel("Data Final:");
	dfLabelP = IupLabel("Dia");
	dfTextP = IupText(NULL);
	IupSetAttribute(dfTextP, "MASK", "/d+");
	mfLabelP = IupLabel("Mes");
	mfTextP = IupText(NULL);
	IupSetAttribute(mfTextP, "MASK", "/d+");
	afLabelP = IupLabel("Ano");
	afTextP = IupText(NULL);
	IupSetAttribute(afTextP, "MASK", "/d+");
	btnDPP = IupButton("Prosseguir", NULL);
	btnDVP = IupButton("Voltar", NULL);
	
	vboxDataP = IupVbox(
		iLabelP,
		diLabelP,
		diTextP,
		miLabelP,
		miTextP,
		aiLabelP,
		aiTextP,
		fLabelP,
		dfLabelP,
		dfTextP,
		mfLabelP,
		mfTextP,
		afLabelP,
		afTextP,
		btnDPP,
		btnDVP,
		NULL
  	);
  	menuDataP = IupDialog(vboxDataP);
  	IupSetAttribute(menuDataP, "TITLE", "Datas do relatorio");
  	IupSetAttribute(vboxDataP, "ALIGNMENT", "ACENTER");
  	IupSetAttribute(vboxDataP, "GAP", "10");
  	IupSetAttribute(vboxDataP, "MARGIN", "80x80");
  	IupShowXY(menuDataP, IUP_CENTER, IUP_CENTER);
  	
  	//IupDestroy(menuRela);
  
  	IupSetCallback(btnDPP, "ACTION", (Icallback) imprimirPou);
  	IupSetCallback(btnDVP, "ACTION", (Icallback) voltaCartDataP);
  	
  
  	IupMainLoop();
  	return EXIT_SUCCESS;
}

int menuRelatorioMov(Ihandle *self){
	rLabelMov = IupLabel("Para movimentacoes: Selecione uma categoria");
	btnrGeral = IupButton("Todas as categorias", NULL);
	btnrMoradia = IupButton("Moradia", NULL);
	btnrEstudo = IupButton("Estudo", NULL);
	btnrConducao = IupButton("Conducao", NULL);
	btnrAlimentacao = IupButton("Alimentacao", NULL);
	btnrOutros = IupButton("Outros", NULL);
	btnrSalario = IupButton("Salario", NULL);
	btnrAdiantamento = IupButton("Adiantamento", NULL);
	btnrComissao = IupButton("Comissao", NULL);
	btnrVendas = IupButton("Vendas", NULL);
	btnrDiversos = IupButton("Diversos", NULL);
	rTextRO = IupText(NULL);
	IupSetAttribute(rTextRO, "READONLY", "YES");
	IupSetAttribute(rTextRO, "VALUE", "Geral");
	btnrMov = IupButton("Prosseguir", NULL);
	btnrVoltarMov = IupButton("Voltar", NULL);
	
	rvboxMov = IupVbox(
		rLabelMov,
		btnrGeral,
		btnrMoradia,
		btnrEstudo,
		btnrConducao,
		btnrAlimentacao,
		btnrOutros,
		btnrSalario,
		btnrAdiantamento,
		btnrComissao,
		btnrVendas,
		btnrDiversos,
		rTextRO,
		btnrMov,
		btnrVoltarMov,
		NULL
  	);
  	rmenuMov = IupDialog(rvboxMov);
  	IupSetAttribute(rmenuMov, "TITLE", "Movimentacao");
  	IupSetAttribute(rvboxMov, "ALIGNMENT", "ACENTER");
  	IupSetAttribute(rvboxMov, "GAP", "10");
  	IupSetAttribute(rvboxMov, "MARGIN", "50x50");
  	IupShowXY(rmenuMov, IUP_CENTER, IUP_CENTER);
  	
  	//IupDestroy(menuRela);
  	
  	IupSetCallback(btnrGeral, "ACTION", (Icallback) mudaRelGeral);
  	IupSetCallback(btnrMoradia, "ACTION", (Icallback) mudaRelMoradia);
  	IupSetCallback(btnrEstudo, "ACTION", (Icallback) mudaRelEstudo);
  	IupSetCallback(btnrConducao, "ACTION", (Icallback) mudaRelConducao);
  	IupSetCallback(btnrAlimentacao, "ACTION", (Icallback) mudaRelAlimentacao);
  	IupSetCallback(btnrOutros, "ACTION", (Icallback) mudaRelOutros);
  	IupSetCallback(btnrSalario, "ACTION", (Icallback) mudaRelSalario);
  	IupSetCallback(btnrAdiantamento, "ACTION", (Icallback) mudaRelAdiantamento);
  	IupSetCallback(btnrComissao, "ACTION", (Icallback) mudaRelComissao);
  	IupSetCallback(btnrVendas, "ACTION", (Icallback) mudaRelVendas);
  	IupSetCallback(btnrDiversos, "ACTION", (Icallback) mudaRelDiversos);
  	IupSetCallback(btnrMov, "ACTION", (Icallback) menuIniFinMov);
  	IupSetCallback(btnrVoltarMov, "ACTION", (Icallback) voltaCartrmenuMov);
  	
  	IupMainLoop();
  	return EXIT_SUCCESS;
}

int menuRelatorioFunc(Ihandle *self){
	btnMov = IupButton("Movimentacoes", NULL);
  	btnPou = IupButton("Poupanca", NULL);
  	btnVoltarRela = IupButton("Voltar", NULL);
  	vboxRela = IupVbox(
  		btnMov,
  		btnPou,
  		btnVoltarRela,
  		NULL
	);
  	menuRela = IupDialog(vboxRela);
  	IupSetAttribute(menuRela, "TITLE", "Relatorios");
  	IupSetAttribute(vboxRela, "ALIGNMENT", "ACENTER");
  	IupSetAttribute(vboxRela, "GAP", "10");
  	IupSetAttribute(vboxRela, "MARGIN", "80x80");
  	IupShowXY(menuRela, IUP_CENTER, IUP_CENTER);
  
  	//IupDestroy(menuCart);
  
  	IupSetCallback(btnMov, "ACTION", (Icallback) menuRelatorioMov);
  	IupSetCallback(btnPou, "ACTION", (Icallback) menuIniFinPoup);
  	IupSetCallback(btnVoltarRela, "ACTION", (Icallback) voltaCartRela);
  
  	IupMainLoop();
  	return EXIT_SUCCESS;
}


int menuCarteira(){
	int main();
	
	
	
	char label1[strlen("Ola ")+strlen(c.login.usuario)+1];
    snprintf( label1, sizeof( label1 ), "%s%s", "Ola ", c.login.usuario );//concatenar string
    
    char label2[strlen("Saldo: RS ")+strlen(c.saldo)+1];
    snprintf( label2, sizeof( label2 ), "%s%s", "Saldo: RS ", c.saldo );//concatenar string
    
    char label3[strlen("Poupanca: RS ")+strlen(c.poupanca)+1];
    snprintf( label3, sizeof( label3 ), "%s%s", "Poupanca: RS ", c.poupanca );//concatenar string
    
	
	btnGasto = IupButton("Registrar Gasto", NULL);
  	btnReceita = IupButton("Registrar Receita", NULL);
  	btnPoupanca = IupButton("Poupanca", NULL);
  	btnRelatorio = IupButton("Relatorios", NULL);
  	btnVoltarCart= IupButton("Sair", NULL);
  	label1Cart = IupLabel(label1);
  	label2Cart = IupLabel("Informacoes da conta:");
  	label3Cart = IupLabel(label2);
  	label4Cart = IupLabel(label3);
  	
  	vboxCart = IupVbox(
		label1Cart,
		label2Cart,
		label3Cart,
		label4Cart,
		btnGasto,
		btnReceita,
		btnPoupanca,
		btnRelatorio,
		btnVoltarCart,
		NULL
  	);
  	menuCart = IupDialog(vboxCart);
  	IupSetAttribute(menuCart, "TITLE", "Menu");
  	IupSetAttribute(vboxCart, "ALIGNMENT", "ACENTER");
  	IupSetAttribute(vboxCart, "GAP", "10");
  	IupSetAttribute(vboxCart, "MARGIN", "80x80");
  	IupShowXY(menuCart, IUP_CENTER, IUP_CENTER);
  	
  //	IupDestroy(menuLogin);

	
  
  	IupSetCallback(btnGasto, "ACTION", (Icallback) menuGastoFunc);
  	IupSetCallback(btnReceita, "ACTION", (Icallback) menuReceitaFunc);
  	IupSetCallback(btnPoupanca, "ACTION", (Icallback) menuPoupancaFunc);
  	IupSetCallback(btnRelatorio, "ACTION", (Icallback) menuRelatorioFunc);
  	IupSetCallback(btnVoltarCart, "ACTION", (Icallback) agradece);
  
  	IupMainLoop();
  	return EXIT_SUCCESS;
}

int funcLogin(Ihandle *self){
    int main();
	int del;
    char *usuario = IupGetAttribute(uTextLogin, "VALUE");
    char *senha = IupGetAttribute(sTextLogin, "VALUE");
    
    char* ext = "_info.txt";

    char nomeArqInfo[strlen(usuario)+strlen(ext)+1];
    snprintf( nomeArqInfo, sizeof( nomeArqInfo ), "%s%s", usuario, ext );//formaa string variavel + .txt

    if( access( nomeArqInfo, R_OK|W_OK ) != -1 ) { // verifica se a carteira com o nome digitado existe
        char senhaArq[100];
        FILE* fr = fopen(nomeArqInfo, "r");
        int i;
        for(i = 0; i < 2; i++){
            fscanf(fr, "%s", senhaArq);
        }
        fclose(fr);
        if ( strcmp(senha, senhaArq) == 0){
            //struct carteira c;
            FILE* fr = fopen(nomeArqInfo, "r");
            fscanf(fr, "%s", c.login.usuario);
            fscanf(fr, "%s", c.login.senha);
            fscanf(fr, "%s", c.saldo);
            fscanf(fr, "%s", c.poupanca);
            IupMessage("Sucesso", "Login efetuado com sucesso.");
            fclose(fr);
            menuCarteira();
            return EXIT_SUCCESS;

        }
        else{
            IupMessage("Erro", "Senha incorreta");
        }
    }
    else {
        IupMessage("Erro", "Carteira nao existente.");
    }
}

int menuLoginFunc(Ihandle *self){
	int main();
	
	btnLoginCart = IupButton("Efetuar Login", NULL);
  	btnVoltarLogin = IupButton("Voltar", NULL);
  	uLabelLogin = IupLabel("Usuario");
  	sLabelLogin = IupLabel("Senha");
  	uTextLogin = IupText(NULL);
  	sTextLogin = IupText(NULL);
  	IupSetAttribute(sTextLogin, "PASSWORD", "YES");
  	vboxLogin = IupVbox(
  		uLabelLogin,
  		uTextLogin,
  		sLabelLogin,
  		sTextLogin,
  		btnLoginCart,
  		btnVoltarLogin,
  		NULL
  	);
  	menuLogin = IupDialog(vboxLogin);
  	IupSetAttribute(menuLogin, "TITLE", "Login");
  	IupSetAttribute(vboxLogin, "ALIGNMENT", "ACENTER");
  	IupSetAttribute(vboxLogin, "GAP", "10");
  	IupSetAttribute(vboxLogin, "MARGIN", "80x80");
  	IupShowXY(menuLogin, IUP_CENTER, IUP_CENTER);
  
  	//IupDestroy(menu1);
  
  	IupSetCallback(btnLoginCart, "ACTION", (Icallback) funcLogin);
  	IupSetCallback(btnVoltarLogin, "ACTION", (Icallback) main);
  
  	IupMainLoop();
  	return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
  IupOpen(&argc, &argv);
  
  
  
  btnCriar = IupButton("Criar Carteira", NULL);
  btnLogin = IupButton("Login", NULL);
  btnDel = IupButton("Deletar Carteira", NULL);
  btnSair = IupButton("Sair", NULL);
  vbox1 = IupVbox(
  	btnCriar,
  	btnLogin,
  	btnDel,
  	btnSair,
  	NULL
  );
  menu1 = IupDialog(vbox1);
  IupSetAttribute(menu1, "TITLE", "Carteira Virtual");
  IupSetAttribute(vbox1, "ALIGNMENT", "ACENTER");
  IupSetAttribute(vbox1, "GAP", "10");
  IupSetAttribute(vbox1, "MARGIN", "80x80");
  IupShowXY(menu1, IUP_CENTER, IUP_CENTER);
  
  //IupDestroy(menuCriar);
  //IupDestroy(menuLogin);
  //IupDestroy(menuDel);
  //IupDestroy(menuCart);
  
  IupSetCallback(btnCriar, "ACTION", (Icallback) menuCriarFunc);
  IupSetCallback(btnLogin, "ACTION", (Icallback) menuLoginFunc);
  IupSetCallback(btnDel, "ACTION", (Icallback) menuDelFunc);
  IupSetCallback(btnSair, "ACTION", (Icallback) quit);
  
  IupMainLoop();
  return EXIT_SUCCESS;
}
