//Criado e Codificado inteiramente por Felipe H. F. Cruz.

//////Bibliotecas Usadas//////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <locale.h>
#include <time.h>
///////////////////////////////////

//Defines usados
#define Letras 1024 // Define globalmente que o limite de letras é 1024
#define PegaUser getenv("USERPROFILE") //Pega o caminho para o nome do usuario
#define Final ".txt" //Define a Extensao do arquivo
///////////////////////////////////

//Structs Usados
struct Ficha {
	char Nome[Letras];
	char Usuario[Letras];
	char Senha[Letras];
	char Nascimento[Letras];
	char RG[Letras];
	long long int CPF;
    char Endereco[Letras];
	char Numero[Letras];
	char Complemento[Letras];
	char Cidade[Letras];
	char Estado[Letras];
	char SimNao[Letras];	
	char CarteiraDeTrabalho[Letras];
	char Cargo[Letras];
};
struct Ficha Dados;
///////////////////////////////////
struct DadosPizzaria{
	char Endereco[Letras];
	char Numero[Letras];
	char NomeSede[Letras];
	char Referencia[Letras];
	int NumeroDaSede;
	int QuantidadeSedes;
	int CEP;
};
struct DadosPizzaria Sede;
///////////////////////////////////
struct tm *DataEHora;     
///////////////////////////////////

//Variaveis Globais Usadas
char Usuario[Letras],Senha[Letras],UsuarioCheck[Letras],SenhaCheck[Letras]; //Define as variaveis de Login
int NivelDeAcesso; //- Define o Nivel de Acesso da Pessoa esta usando o sistema em 2 Niveis, 1- Funcionario | 2- Gerente
char* Local; //Define o lugar onde vai se alocar a pasta do Martiello
char* Disparo; //Monta o caminho onde a pasta vai ficar fazendo a juncao do usuario com o local
FILE *Arquivo;//Define o nome do ponteiro de arquivo
FILE *Temporario;//Define o Nome do Ponteiro para o Arquivo Temporario
char Saida[Letras] = ""; //Pega as informacoes das pizzas
////////////////////////////////////////////////////////////////////


//Variaveis Globais do Pedido
//Variaveis Usadas
  int MesaEntrega,QPessoas,ID,NumeroMesa,DinheiroCartao,Parcelamento,QuantidadePizza,i=0;
  char RodizioOuPizza[Letras],SimNao[Letras],Avaliacao[Letras];
  float PrecoRodizio,ValorASerPago,ValorParcela;
//////////////////////////////////////////////////////////////////////////////  



//Funcoes Usadas
void Logon();
void TeladeRelatorio();
void PainelFuncionario();
void PedidoEstoque();
void PainelAdministrativo();
int Pedido();
void CadastroCardapio();
void Cardapio();
void CadastroFuncionario();
void Sumario();
void CadastroFidelidade();
void GerenciaFuncionarios();
void ListarFidelidade();
////////////////////////////////////////////////////////////////////



main(){
setlocale(LC_ALL, "Portuguese"); //Define o programa para aceitar acentuações em portugues
setlocale(LC_NUMERIC, "pt_BR"); //Define o programa para aceitar Virgulas no lugar do ponto

////////////////////////////////////////////////////////////////////
Local = "\\AppData\\Martiello\\Funcionarios\\Logins";
Disparo = (char *) malloc(1 + strlen(PegaUser)+ strlen(Local) );
strcpy(Disparo, PegaUser);
strcat(Disparo, Local);   
DIR* Diretorio = opendir(Disparo);
////////////////////////////////////////////////////////////////////

if(Diretorio){

	printf("Autenticação Martielo\n---------------------------------------------------------------------------------------------\n");
	printf("Digite o Nome do Usuario: ");
	scanf("%s",&Usuario);
    printf("Digite a Senha: ");
	scanf("%s",&Senha);
    Logon(Usuario,Senha);
	

}else if(Diretorio == NULL){
//Caso o diretorio do Programa nao existe ele cria
Local = "\\AppData\\Martiello";
Disparo = (char *) malloc(1 + strlen(PegaUser)+ strlen(Local) );
strcpy(Disparo, PegaUser);
strcat(Disparo, Local); 	  
mkdir(Disparo);
memset (&Disparo, 0, sizeof (Disparo));
//////////////////////////////////////////////////////////////////////////////   

//Cria a Pasta de Funcionarios
Local = "\\AppData\\Martiello\\Funcionarios";
Disparo = (char *) malloc(1 + strlen(PegaUser)+ strlen(Local) );
strcpy(Disparo, PegaUser);
strcat(Disparo, Local); 	  
mkdir(Disparo);
memset (&Disparo, 0, sizeof (Disparo));
//////////////////////////////////////////////////////////////////////////////   

//Gera o Arquivo de Registro
Local = "\\AppData\\Martiello\\Clientes Fidelidade.txt";
Disparo = (char *) malloc(1 + strlen(PegaUser)+ strlen(Local) );
strcpy(Disparo, PegaUser);
strcat(Disparo, Local); 
Arquivo = fopen(Disparo,"a");
fclose(Arquivo);
memset (&Disparo, 0, sizeof (Disparo));
//////////////////////////////////////////////////////////////////////////////   

//Gera o Arquivo de Registro
Local = "\\AppData\\Martiello\\Registro.txt";
Disparo = (char *) malloc(1 + strlen(PegaUser)+ strlen(Local) );
strcpy(Disparo, PegaUser);
strcat(Disparo, Local); 
Arquivo = fopen(Disparo,"a");
fclose(Arquivo);
memset (&Disparo, 0, sizeof (Disparo));
//////////////////////////////////////////////////////////////////////////////   

//Gera o Arquivo dos dados da Sede
Local = "\\AppData\\Martiello\\Dados da Pizzaria.txt";
Disparo = (char *) malloc(1 + strlen(PegaUser)+ strlen(Local) );
strcpy(Disparo, PegaUser);
strcat(Disparo, Local); 
Arquivo = fopen(Disparo,"a");
fclose(Arquivo);
memset (&Disparo, 0, sizeof (Disparo));
////////////////////////////////////////////////////////////////////////////// 

//Gera o Arquivo de Cardapio
Local = "\\AppData\\Martiello\\Cardapio.txt";
Disparo = (char *) malloc(1 + strlen(PegaUser)+ strlen(Local) );
strcpy(Disparo, PegaUser);
strcat(Disparo, Local); 
Arquivo = fopen(Disparo,"a");
fclose(Arquivo);
memset (&Disparo, 0, sizeof (Disparo));
///////////////////////////////////////////////////////////////////////////

//////////Inicia o primeiro cadastro no caso o administrador//////////
	printf("Primeiro Login\n---------------------------------------------------------------------------------------------\n");
	printf("Olá Bem-vindo ao Martiello!\nPara Iniciarmos Cadastre o primeiro usuario, Este usuario sera o Administrador!\n\n");	
	printf("Nome Completo\n* ");
	scanf(" %[^\n]s",&Dados.Nome);
	fflush(stdin);
	printf("Data Nascimento exemplo: 31/12/2019\n* ");
	scanf(" %[^\n]s",&Dados.Nascimento);
	fflush(stdin);
	printf("RG\n* ");
	scanf(" %[^\n]s",&Dados.RG);
	fflush(stdin);
	printf("CPF\n* ");
	
	while(scanf("%lld",&Dados.CPF) != 1)
    {
        printf("Digite um Numero de CPF valido!\n");
	    while(getchar() != '\n');
	    sleep(1);
	    system("cls");
	   	printf("Primeiro Login\n---------------------------------------------------------------------------------------------\n");
		printf("Olá Bem-vindo ao Martiello!\nPara Iniciarmos Cadastre o primeiro usuario, Este usuario sera o Administrador!\n\n");	
		printf("Nome Completo\n* %s\n",Dados.Nome);
		printf("Data Nascimento exemplo: 31/12/2019\n* %s\n",Dados.Nascimento);
		printf("RG\n* %s\n",Dados.RG);
		printf("CPF\n* ");
	}
	char Tamanho = 1 + (int)log10(Dados.CPF);

	if (Tamanho > 11 || Tamanho < 11){
    printf("O numero de CPF digitado e Invalido!\n");
	sleep(1);
	system("cls");
	main();
	}
	fflush(stdin);
	printf("Endereco Ex: Rua das Palmeiras\n* ");
	scanf(" %[^\n]s",&Dados.Endereco);
	fflush(stdin);
	printf("Numero\n* ");
	scanf(" %[^\n]s",&Dados.Numero);
	fflush(stdin);
	printf("Complemento\n* ");
	scanf(" %[^\n]s",&Dados.Complemento);
	fflush(stdin);
	printf("Cidade\n* ");
	scanf(" %[^\n]s",&Dados.Cidade);
	fflush(stdin);
	printf("Estado exemplo: SP , RJ , SC. . .\n* ");
	scanf(" %[^\n]s",&Dados.Estado);
	fflush(stdin);
	system("cls");
	
	///////////////////////////////////////////////////////////////////////////
	printf("Confirmação dos Dados\n---------------------------------------------------------------------------------------------\n\n");
	printf("Nome: %s\nData de Nascimento: %s\nRG: %s\nCPF: %lld\nEndereço: %s\nNumero: %s\nComplemento: %s\nCidade: %s\nEstado: %s\n\n",Dados.Nome,Dados.Nascimento,Dados.RG,Dados.CPF,Dados.Endereco,Dados.Numero,Dados.Complemento,Dados.Cidade,Dados.Estado);
	printf("As Informacoes Digitadas estao corretas? S/N \n* ");
	scanf("%s",&Dados.SimNao);
	///////////////////////////////////////////////////////////////////////////
	
	while(1){
	if (strcmp(Dados.SimNao,"S")==0 || (strcmp(Dados.SimNao,"s")==0)){
	system("cls");
	printf("Cadastro da Pizzaria\n---------------------------------------------------------------------------------------------\n");
	printf("Digite o nome da Pizzaria\n- ");
	scanf(" %[^\n]s",&Sede.NomeSede);
	printf("Endereco\n- ");
	scanf(" %[^\n]s",&Sede.Endereco);
	printf("Numero\n- ");
	scanf(" %[^\n]s",&Sede.Numero);
	printf("CEP (com 8 Digitos sem Tracos)\n- ");
	
	while(scanf("%d",&Sede.CEP) != 1 || Sede.CEP <= 0)
    {
    printf("Insira Numero de CEP valido!\n");
	while(getchar() != '\n');
	sleep(1);
	system("cls");
	printf("Cadastro da Pizzaria\n---------------------------------------------------------------------------------------------\n");
	printf("Digite o nome da Pizzaria\n- %s\n",Sede.NomeSede);
	printf("Endereco\n- %s\n",Sede.Endereco);
	printf("Numero\n- %s\n",Sede.Numero);
	printf("CEP (com 8 Digitos sem Tracos)\n- ");
	}
	char Tamanho = 1 + (int)log10(Sede.CEP);
	if (Tamanho < 8 || Tamanho > 8){
		printf("O CEP que você digitou é invalido!\n");
		sleep(1);
		system("cls");
	}
	
	printf("Quantas Sedes suas pizzaria possui\n- ");
	
	while(scanf("%d",&Sede.QuantidadeSedes) != 1|| Sede.QuantidadeSedes <=0)
    {
    printf("Digite um Numero valido!\n");
	while(getchar() != '\n');
	sleep(1);
	system("cls");
	printf("Cadastro da Pizzaria\n---------------------------------------------------------------------------------------------\n");
	printf("Digite o nome da Pizzaria\n- %s\n",Sede.NomeSede);
	printf("Endereco\n- %s\n",Sede.Endereco);
	printf("Numero\n- %s\n",Sede.Numero);
	printf("CEP (com 8 Digitos sem Tracos)\n- %d\n",Sede.CEP);
	printf("Quantas Sedes suas pizzaria possui\n- ");
	}
	printf("Atribua um numero de Identificacao para esta Sede\n- ");
	while(scanf("%d",&Sede.NumeroDaSede) != 1|| Sede.NumeroDaSede <=0)
    {
    printf("Digite um Numero valido!\n");
	while(getchar() != '\n');
	sleep(1);
	system("cls");
	printf("Cadastro da Pizzaria\n---------------------------------------------------------------------------------------------\n");
	printf("Digite o nome da Pizzaria\n- %s\n",Sede.NomeSede);
	printf("Endereco\n- %s\n",Sede.Endereco);
	printf("Numero\n- %s\n",Sede.Numero);
	printf("CEP (com 8 Digitos sem Tracos)\n- %d\n",Sede.CEP);
	printf("Quantas Sedes suas pizzaria possui\n- %d\n",Sede.QuantidadeSedes);
	printf("Atribua um numero de Identificacao para esta Sede\n- ");
	}
	system("cls");
	printf("Confirme os Dados da Pizzaria\n---------------------------------------------------------------------------------------------\n");
	printf("Nome da Pizzaria : %s\n",Sede.NomeSede);
	printf("Endereco : %s\n",Sede.Endereco);
	printf("Numero : %s\n",Sede.Numero);
	printf("CEP : %d\n",Sede.CEP);
	printf("Quantidade de Sedes : %d\n",Sede.QuantidadeSedes);
	printf("Numero de Identificacao da Sede Atual : %d\n\n",Sede.NumeroDaSede);
	printf("As Informacoes Digitadas estao corretas? S/N \n* ");
	scanf("%s",&Dados.SimNao);
	
	
	while(1){
	if (strcmp(Dados.SimNao,"s")==0||(strcmp(Dados.SimNao,"S")==0)){
	Local = "\\AppData\\Martiello\\Dados da Pizzaria.txt";
	Disparo = (char *) malloc(1 + strlen(PegaUser)+ strlen(Local) );
	strcpy(Disparo, PegaUser);
	strcat(Disparo, Local); 
	Arquivo = fopen(Disparo,"w");
	fprintf(Arquivo,"Nome da Pizzaria : %s\nEndereco : %s\nNumero : %s\nCEP : %d\nQuantidade de Sedes : %d\nNumero da Sede Atual : %d",Sede.NomeSede,Sede.Endereco,Sede.Numero,Sede.CEP,Sede.QuantidadeSedes,Sede.NumeroDaSede);
	fclose(Arquivo);
	printf("Dados da Pizzaria salvos com sucesso!");
	sleep(1);
	break;
	}else if(strcmp(Dados.SimNao,"N")||(strcmp(Dados.SimNao,"n"))){
	printf("Reiniciando Cadastro . . .");
	sleep(1);
	system("cls");
	printf("Cadastro da Pizzaria\n---------------------------------------------------------------------------------------------\n");
	printf("Digite o nome da Pizzaria\n- ");
	scanf(" %[^\n]s",&Sede.NomeSede);
	printf("Endereco\n- ");
	scanf(" %[^\n]s",&Sede.Endereco);
	printf("Numero\n- ");
	scanf(" %[^\n]s",&Sede.Numero);
	printf("CEP (com 8 Digitos sem Tracos)\n- ");
	
	while(scanf("%d",&Sede.CEP) != 1 || Sede.CEP <= 0)
    {
    printf("Insira Numero de CEP valido!\n");
	while(getchar() != '\n');
	sleep(1);
	system("cls");
	printf("Cadastro da Pizzaria\n---------------------------------------------------------------------------------------------\n");
	printf("Digite o nome da Pizzaria\n- %s\n",Sede.NomeSede);
	printf("Endereco\n- %s\n",Sede.Endereco);
	printf("Numero\n- %s\n",Sede.Numero);
	printf("CEP (com 8 Digitos sem Tracos)\n- ");
	}
	char Tamanho = 1 + (int)log10(Sede.CEP);
	if (Tamanho < 8 || Tamanho > 8){
		printf("O CEP que você digitou é invalido!\n");
		sleep(1);
		system("cls");
		
	}
	
	printf("Quantas Sedes suas pizzaria possui\n- ");
	
	while(scanf("%d",&Sede.QuantidadeSedes) != 1|| Sede.QuantidadeSedes <=0)
    {
    printf("Digite um Numero valido!\n");
	while(getchar() != '\n');
	sleep(1);
	system("cls");
	printf("Cadastro da Pizzaria\n---------------------------------------------------------------------------------------------\n");
	printf("Digite o nome da Pizzaria\n- %s\n",Sede.NomeSede);
	printf("Endereco\n- %s\n",Sede.Endereco);
	printf("Numero\n- %s\n",Sede.Numero);
	printf("CEP\n- %d\n",Sede.CEP);
	printf("Quantas Sedes suas pizzaria possui\n- ");
	}
	printf("Atribua um numero de Identificacao para esta Sede\n- ");
	while(scanf("%d",&Sede.NumeroDaSede) != 1|| Sede.NumeroDaSede <=0)
    {
    printf("Digite um Numero valido!\n");
	while(getchar() != '\n');
	sleep(1);
	system("cls");
	printf("Cadastro da Pizzaria\n---------------------------------------------------------------------------------------------\n");
	printf("Digite o nome da Pizzaria\n- %s\n",Sede.NomeSede);
	printf("Endereco\n- %s\n",Sede.Endereco);
	printf("Numero\n- %s\n",Sede.Numero);
	printf("CEP\n- %d\n",Sede.CEP);
	printf("Quantas Sedes suas pizzaria possui\n- %d\n",Sede.QuantidadeSedes);
	printf("Atribua um numero de Identificacao para esta Sede\n- ");
	}
	system("cls");
	printf("Confirme os Dados da Pizzaria\n---------------------------------------------------------------------------------------------\n");
	printf("Nome da Pizzaria : %s\n",Sede.NomeSede);
	printf("Endereco : %s\n",Sede.Endereco);
	printf("Numero : %s\n",Sede.Numero);
	printf("CEP : %d\n",Sede.CEP);
	printf("Quantidade de Sedes : %d\n",Sede.QuantidadeSedes);
	printf("Numero de Identificacao da Sede Atual : %d\n\n",Sede.NumeroDaSede);
	printf("As Informacoes Digitadas estao corretas? S/N \n* ");
	scanf("%s",&Dados.SimNao);
	}
	}
	
	
		
	system("cls");
	printf("Criação de Usuario\n---------------------------------------------------------------------------------------------\n");
	printf("Usuario\n* ");
	scanf(" %[^\n]s",&Dados.Usuario);
	printf("Senha (No Minimo 4 Digitos)\n* ");
	scanf(" %[^\n]s",&Dados.Senha);
	
	
	//Gera o arquivo de Funcionarios, Criando o primeiro funcionario sendo o administrador	
    Local = "\\AppData\\Martiello\\Funcionarios\\";
    Disparo = (char *) malloc(1 + strlen(PegaUser)+ strlen(Local)+ strlen(Dados.Nome)+ strlen(Final));
    strcpy(Disparo, PegaUser);
    strcat(Disparo, Local); 
    strcat(Disparo, Dados.Nome); 
    strcat(Disparo, Final); 
    Arquivo = fopen(Disparo,"a"); 
   	////////////////////////////////////////////////////////////////////////////////////////////

    
	////////////////////////////////////////////////////////////////////////////////////////////
	sleep(1);
	printf("Usuario Administrador cadastrado com Exito!\n");
	fprintf(Arquivo,"======Dados Do Administrador======\nNome: %s\nData de Nascimento: %s\nRG: %s\nCPF: %lld\nEndereco: %s\nNumero: %s\nComplemento: %s\nCidade: %s\nEstado: %s\n\nUsuario: %s\nSenha: %s\nNivel de Acesso: 2",Dados.Nome,Dados.Nascimento,Dados.RG,Dados.CPF,Dados.Endereco,Dados.Numero,Dados.Complemento,Dados.Cidade,Dados.Estado,Dados.Usuario,Dados.Senha);
	fclose(Arquivo);	
	////////////////////////////////////////////////////////////////////////////////////////////

	//Cria a Pasta de Logins
	Local = "\\AppData\\Martiello\\Funcionarios\\Logins";
	Disparo = (char *) malloc(1 + strlen(PegaUser)+ strlen(Local) );
	strcpy(Disparo, PegaUser);
	strcat(Disparo, Local); 	  
	mkdir(Disparo);
	memset (&Disparo, 0, sizeof (Disparo));
	//////////////////////////////////////////////////////////////////////////////   
	
	
	///////Cria um arquivo de Login de Acordo com o nome do usuario///////
    Local = "\\AppData\\Martiello\\Funcionarios\\Logins\\";
    Disparo = (char *) malloc(1 + strlen(PegaUser)+ strlen(Local)+ strlen(Dados.Usuario)+ strlen(Final));
    strcpy(Disparo, PegaUser);
    strcat(Disparo, Local); 
    strcat(Disparo, Dados.Usuario); 
    strcat(Disparo, Final); 
    Arquivo = fopen(Disparo,"a"); 
	fprintf(Arquivo,"Usuario: %s\nSenha: %s\nNivel de Acesso: 2",Dados.Usuario,Dados.Senha);
	fclose(Arquivo);
	fflush(stdin);
	//////////////////////////////////////////////////////////////////////////////   

	
	printf("Redirecionando para Menu Principal. . .\n");
	sleep(2);
	system("cls");
	main();
	break;
	}else if (strcmp(Dados.SimNao,"n")==0 || (strcmp(Dados.SimNao,"N")==0)){
	printf("Reiniciando Cadastro. . .");
	sleep(2);
	system("cls");
	return main();
	break;
	}else{
	printf("A opcao entrada e invalida! Digite S/N \n* ");
	scanf("%s",&Dados.SimNao);
	}			
	}


}else{
printf("Ocorreu um erro ao gerar a Pasta do Martiello! \n\nContate o Suporte Imediante");}

}//Main
void Logon(char Usuario[Letras], char Senha[Letras]){
	
//Abre o Arquivo de Login de Acordo com o respectivo Login digitado
  Local = "\\AppData\\Martiello\\Funcionarios\\Logins\\";
  Disparo = (char *) malloc(1 + strlen(PegaUser)+ strlen(Local)+ strlen(Usuario)+ strlen(Final));
  strcpy(Disparo, PegaUser);
  strcat(Disparo, Local); 
  strcat(Disparo, Usuario); 
  strcat(Disparo, Final); 
  Arquivo = fopen(Disparo,"r"); 
//////////////////////////////////////////////////////////////////////////////   


while(1){
if(access(Disparo, F_OK ) != -1 ){	


fscanf(Arquivo,"Usuario: %s\nSenha: %s\n",UsuarioCheck,SenhaCheck);

//Verifica uma linha especifica do arquivo cujo e o nivel de acesso
int Finall, Loop, Linha = 3;
    char str[512];
    for(Finall = Loop = 0;Loop<Linha;++Loop){
        if(0==fgets(str, sizeof(str), Arquivo)){
            Finall = 1;
            break;
        }
    }
//////////////////////////////////////////////////////////////////////////////   

//CASO O NIVEL DE ACESSO SER DO NIVEL 2 ELE REDIRECIONA PARA O MENU DO GERENTE	
if((strcmp(Usuario,UsuarioCheck)==0) && (strcmp(Senha,SenhaCheck)==0) && (strcmp(str,"Nivel de Acesso: 2")==0)){	

    printf("\nLogado com sucesso! Redirecionando. . .");
    sleep(1);
    system("cls");
	PainelAdministrativo();
	break;

//CASO O NIVEL DE ACESSO SER DO NIVEL 1 ELE REDIRECIONA PARA O MENU DO FUNCIONARIO	
}else if((strcmp(Usuario,UsuarioCheck)==0) && (strcmp(Senha,SenhaCheck)==0)&& (strcmp(str,"Nivel de Acesso: 1")==0)){	
	  
	printf("\nLogado com sucesso! Redirecionando. . .");
    sleep(1);
    system("cls");
	PainelFuncionario();
	break;
	  
	}else{ //Else do Usuario	
    printf("\nUsuario ou Senha Incorretos. Tente Novamente");
    sleep(1);
    system("cls");
	return main();}
    
	}else{ //Else do Arquivo
    printf("\nUsuario ou Senha Incorretos. Tente Novamente");
    sleep(1);
    system("cls");
    return main();}
    fclose(Arquivo);}
}//Logon




void PainelFuncionario(){
int OPT;
printf("Painel Martiello | Funcionario : %s\n---------------------------------------------------------------------------------------------\n",Usuario);
printf("|1| - Realizar Pedido\n");
printf("|2| - Cardapio\n");
printf("|3| - Cadastrar Pizza ou Produto\n");
printf("|4| - Cadastrar Clientes (Plano Fidelidade)\n");
printf("|5| - Ver Clientes Fidelidade\n");
printf("|6| - Deslogar\n");
printf("|7| - Sair\n\n- ");

    while(scanf("%d",&OPT) != 1||OPT <=0)
    {
        printf("Selecione uma Opcao valida!\n");
	    while(getchar() != '\n');
	    sleep(1);
		system("cls");
		return PainelFuncionario();
		break;
	}	

switch(OPT){
	case 1:
	system("cls");
	Pedido();
	break;
	
	case 2:
	system("cls");
	Cardapio();
	break;
		
	case 3:
	system("cls");
	CadastroCardapio();
	break;
	
	case 4:
	system("cls");
	CadastroFidelidade();
	break;
	
	case 5:
	system("cls");
	ListarFidelidade();
	break;
	
	case 6:
	printf("Deslogando . . .");
	sleep(1);
	system("cls");
	return main();
	break;
	
	case 7:
	exit(-1);
	break;
	
	default:
	printf("Opção invalida!");
	sleep(1);
	system("cls");
	return PainelFuncionario();
	break;}
}//Painel Funcionario

void PainelAdministrativo(){
int OPT;
printf("Painel Martiello | Administrador : %s\n---------------------------------------------------------------------------------------------\n",Usuario);
printf("|1| - Realizar Pedido\n");
printf("|2| - Cardapio\n");
printf("|3| - Cadastrar Funcionario\n");
printf("|4| - Cadastrar Pizza ou Produto\n");
printf("|5| - Pedido de Suplementos\n");
printf("|6| - Relatorio de Pedidos\n");
printf("|7| - Cadastrar Clientes (Plano Fidelidade)\n");
printf("|8| - Ver Clientes Fidelidade\n");
printf("|9| - Deslogar\n");
printf("|10| - Sair\n\n- ");

    while(scanf("%d",&OPT) != 1||OPT <=0)
    {
    printf("Selecione uma Opcao valida!\n");
	while(getchar() != '\n');
	sleep(1);
	system("cls");
	return PainelAdministrativo();
	break;
	}	
	
switch(OPT){
	case 1:
	system("cls");
	Pedido();
	break;
	
	case 2:
	system("cls");
	Cardapio();
	break;
	
	case 3:
	system("cls");
	CadastroFuncionario();
	break;
	
	case 4:
	system("cls");
	CadastroCardapio();
	break;
		
	case 5:
	system("cls");
	PedidoEstoque();
	break;
	
	case 6:
	system("cls");
	TeladeRelatorio();
	break;

	case 7:
	system("cls");
	CadastroFidelidade();
	break;
	
	case 8:
	system("cls");
	ListarFidelidade();
	break;
	
	case 9:
	printf("Deslogando . . .");
	sleep(1);
	system("cls");
	return main();
	break;
	
	case 10:
	exit(-1);
	struct Ficha empty = {0};
	break;
	
	default:
	printf("Opção invalida!");
	sleep(1);
	system("cls");
	return PainelAdministrativo();
	break;}
}//Painel Administrativo

void CadastroCardapio(){
setlocale(LC_ALL, "Portuguese"); //Define o programa para aceitar acentuações em portugues
setlocale(LC_NUMERIC, "pt_BR"); //Define o programa para aceitar Virgulas no lugar do ponto

memset(&Dados.SimNao, 0,sizeof(Dados.SimNao));

//Abre o arquivo de cardapio para a entrada de Dados
Local = "\\AppData\\Martiello\\Cardapio.txt";
Disparo = (char *) malloc(1 + strlen(PegaUser)+ strlen(Local) );
strcpy(Disparo, PegaUser);
strcat(Disparo, Local); 
Arquivo = fopen(Disparo,"a");
//////////////////////////////////////////////////////////////////////////////   

//Variaveis
int Tipo,ID,MLouLitro;
float PGrande,PPequena,Preco;
char NomePizza[Letras],Ingredientes[Letras],NomeBebida[Letras],OutroNome[Letras],Descricao[Letras];
//////////////////////////////////////////////////////////////////////////////   


printf("Cadastro de Pizza e Produtos\n---------------------------------------------------------------------------------------------\n");
printf("Oque sera cadastrado [1]Pizza | [2]Bebida | [3]Outro | [4]Voltar\n- ");

 while(scanf("%d",&Tipo) != 1 || Tipo >4 ||Tipo <=0)
    {
        printf("Digite uma Opcao valida!\n");
	    while(getchar() != '\n');
	    memset(&Tipo, 0, sizeof (Tipo));
	    sleep(1);
        system("cls");
        return CadastroCardapio();
	}
	switch(Tipo){
		case 1:
		printf("Digite o nome da Pizza\n- ");
		scanf(" %[^\n]s",&NomePizza);
		printf("Quais seus ingredientes\n- ");
		scanf(" %[^\n]s",&Ingredientes);
		printf("Preço R$\n- ");
		scanf("%f",&PGrande);
		printf("Atribua um numero de Identificacao\n- ");
 		while(scanf("%d",&ID) != 1)
    	{
        printf("Digite uma Opcao valida!\n");
	    while(getchar() != '\n');
	    memset(&ID, 0, sizeof (ID));
	    sleep(1);
        system("cls");
        printf("Cadastro de Pizza e Produtos\n---------------------------------------------------------------------------------------------\n");
		printf("Oque sera cadastrado [1]Pizza | [2]Bebida | [3]Outro\n- 1\n");
        printf("Digite o nome da Pizza\n- %s\n",NomePizza);
        printf("Quais seus ingredientes\n- %s\n",Ingredientes);
        printf("Preço R$\n- %.2f\n",PGrande);
		printf("Atribua um numero de Identificacao\n- ");
		}
		system("cls");
		printf("Confirmação dos Dados\n---------------------------------------------------------------------------------------------\n");
		printf("Nome Pizza : %s\nIngredientes : %s\nPreço R$: %.2f\nID : %d\n",NomePizza,Ingredientes,PGrande,ID);
		printf("As Informacoes Digitadas estao corretas? S/N \n* ");
		scanf("%s",&Dados.SimNao);
		while(1){
		if(strcmp(Dados.SimNao,"S")==0||(strcmp(Dados.SimNao,"s")==0)){
		fprintf(Arquivo,"ID : %d\n- Nome da Pizza : %s\nIngredientes : %s\nValor R$: %.2f\n\n==========================================\n",ID,NomePizza,Ingredientes,PGrande);
		fclose(Arquivo);
		printf("Pizza Inserida com Sucesso ao Cardapio!");	
		sleep(1);	
		system("cls");
		return CadastroCardapio();
		break;
		}else if(strcmp(Dados.SimNao,"n")==0||(strcmp(Dados.SimNao,"N")==0)){
		printf("Reiniciando o Cadastro . . .");
		sleep(1);
		system("cls");
		memset(&NomePizza, 0,sizeof(NomePizza));
		memset(&Ingredientes, 0,sizeof(Ingredientes));
		memset(&PGrande, 0,sizeof(PGrande));
		memset(&PPequena, 0,sizeof(PPequena));
		return CadastroCardapio();
		break;
		}else{
		printf("Digite uma Opcao valida!\n");
	 	sleep(1);
	 	system("cls");
		printf("Confirmação dos Dados\n---------------------------------------------------------------------------------------------\n");
		printf("Nome Pizza : %s\nIngredientes : %s\nValor R$: %.2f\nID : %d\n",NomePizza,Ingredientes,PGrande,ID);
		printf("As Informacoes Digitadas estao corretas? S/N \n* ");
		scanf("%s",&Dados.SimNao);
		}		
		}
		break;
		
		
		
		case 2:
		printf("Nome da Bebida\n- ");
		scanf(" %[^\n]s",&NomeBebida);
		printf("Preço R$\n- ");
		scanf("%f",&Preco);
		printf("Quantos ml ou Litros\n- ");
		
 		while(scanf("%d",&MLouLitro) != 1)
    	{
        printf("A quantidade inserida e invalida!\n");
	    while(getchar() != '\n');
	    memset(&MLouLitro, 0, sizeof (MLouLitro));
	    sleep(1);
        system("cls");
        printf("Cadastro de Pizza e Produtos\n---------------------------------------------------------------------------------------------\n");
		printf("Oque sera cadastrado [1]Pizza | [2]Bebida | [3]Outro\n- 2\n");
		printf("Nome da Bebida\n- %s\n",NomeBebida);
		printf("Preço R$\n- %.2f\n",Preco);
		printf("Quantos ml ou Litros\n- ");
		}
		
		
		printf("Atribua um numero de Identificacao\n- ");
			
 		while(scanf("%d",&ID) != 1)
    	{
        printf("Digite uma Opcao valida!\n");
	    while(getchar() != '\n');
	    memset(&ID, 0, sizeof (ID));
	    sleep(1);
	    system("cls");
        printf("Cadastro de Pizza e Produtos\n---------------------------------------------------------------------------------------------\n");
		printf("Oque sera cadastrado [1]Pizza | [2]Bebida | [3]Outro\n- 2\n");
		printf("Nome da Bebida\n- %s\n",NomeBebida);
		printf("Preço R$\n- %.2f\n",Preco);
		printf("Quantos ml ou Litros\n- %d\n",MLouLitro);
		printf("Atribua um numero de Identificacao\n- ");
		}
		
		system("cls");
		printf("Confirmação dos Dados\n---------------------------------------------------------------------------------------------\n");
		printf("Nome Bebida : %s\nLitros ou ml : %d\nPreço R$ : %.2f\nID : %d\n",NomeBebida,MLouLitro,Preco,ID);
		printf("As Informacoes Digitadas estao corretas? S/N \n* ");
		scanf("%s",&Dados.SimNao);
		while(1){
		if(strcmp(Dados.SimNao,"S")==0||(strcmp(Dados.SimNao,"s")==0)){
		fprintf(Arquivo,"ID : %d\n- Nome Bebida : %s\nLitros ou ml : %d\nValor R$: %.2f\n\n==========================================\n",ID,NomeBebida,MLouLitro,Preco);
		fclose(Arquivo);
		printf("Bebida Inserida com Sucesso ao Cardapio!");		
		sleep(1);	
		system("cls");
		return CadastroCardapio();
		break;
		}else if(strcmp(Dados.SimNao,"n")==0||(strcmp(Dados.SimNao,"N")==0)){
		printf("Reiniciando o Cadastro . . .");
		sleep(1);
		system("cls");
		memset(&NomeBebida, 0,sizeof(NomeBebida));
		memset(&MLouLitro, 0,sizeof(MLouLitro));
		memset(&Preco, 0,sizeof(Preco));
		memset(&ID, 0,sizeof(ID));
		return CadastroCardapio();
		break;
		}else{
		printf("Digite uma Opcao valida!\n");
	 	sleep(1);
	 	system("cls");
	 	printf("Confirmação dos Dados\n---------------------------------------------------------------------------------------------\n");
		printf("Nome Bebida : %s\nLitros ou ml : %d\nValor R$ : %.2f\nID : %d\n",NomeBebida,MLouLitro,Preco,ID);
		printf("As Informacoes Digitadas estao corretas? S/N \n* ");
		scanf("%s",&Dados.SimNao);
	 	}
		}
		break;
		
		
		
		
		case 3:
		printf("Nome do Produto\n- ");
		scanf(" %[^\n]s",&OutroNome);
		printf("Preço R$\n- ");
		scanf("%f",&Preco);
		printf("Descrição do Produto\n- ");
		scanf(" %[^\n]s",&Descricao);
		printf("Atribua um numero de Identificacao\n- ");
 		while(scanf("%d",&ID) != 1)
    	{
        printf("Digite uma Opcao valida!\n");
	    while(getchar() != '\n');
	    memset(&ID, 0, sizeof (ID));
	    sleep(1);
	    system("cls");
        printf("Cadastro de Pizza e Produtos\n---------------------------------------------------------------------------------------------\n");
		printf("Oque sera cadastrado [1]Pizza | [2]Bebida | [3]Outro | [4]Voltar\n- 3\n");
		printf("Nome do Produto\n- %s",OutroNome);
		printf("Preço R$\n- %.2f",Preco);
		printf("Descrição do Produto\n- %s",Descricao);
		printf("Atribua um numero de Identificacao\n- ");
		}
		system("cls");
		printf("Confirmação dos Dados\n---------------------------------------------------------------------------------------------\n");
		printf("Nome do Produto : %s\nPreço R$ : %.2f\nDescrição : %s\nID : %d\n",OutroNome,Preco,Descricao,ID);
		printf("As Informacoes Digitadas estao corretas? S/N \n* ");
		scanf("%s",&Dados.SimNao);
		while(1){
		if(strcmp(Dados.SimNao,"S")==0||(strcmp(Dados.SimNao,"s")==0)){
		fprintf(Arquivo,"ID : %d\n- Nome Produto : %s\nValor Uni R$ : %.2f\nDescrição : %s\n\n==========================================\n",ID,OutroNome,Preco,Descricao);
		fclose(Arquivo);
		printf("Produto Inserido com Sucesso ao Cardapio!");		
		sleep(1);	
		system("cls");
		return CadastroCardapio();
		break;
		}else if(strcmp(Dados.SimNao,"n")==0||(strcmp(Dados.SimNao,"N")==0)){
		printf("Reiniciando o Cadastro . . .");
		sleep(1);
		system("cls");
		memset(&OutroNome, 0,sizeof(OutroNome));
		memset(&Preco, 0,sizeof(Preco));
		memset(&Descricao, 0,sizeof(Descricao));
		memset(&ID, 0,sizeof(ID));
		return CadastroCardapio();
		break;
		}else{
		printf("Digite uma Opcao valida!\n");
	 	sleep(1);
	 	system("cls");
	 	printf("Confirmação dos Dados\n---------------------------------------------------------------------------------------------\n");
		printf("Nome do Produto : %s\nPreço R$ : %.2f\nDescrição : %s\nID : %d\n",OutroNome,Preco,Descricao,ID);
	 	printf("As Informacoes Digitadas estao corretas? S/N \n* ");
		scanf("%s",&Dados.SimNao);
		}
		}
		break;
		
		case 4:
	//Abre o arquivo do respectivo usuario logado para ver seu nivel de acesso	
	Local = "\\AppData\\Martiello\\Funcionarios\\Logins\\";
 	Disparo = (char *) malloc(1 + strlen(PegaUser)+ strlen(Local)+ strlen(Usuario)+ strlen(Final));
  	strcpy(Disparo, PegaUser);
 	strcat(Disparo, Local); 
 	strcat(Disparo, Usuario); 
  	strcat(Disparo, Final); 
  	Arquivo = fopen(Disparo,"r"); 
	////////////////////////////////////////////////////////////////////////////// 
	//Verifica uma linha especifica do arquivo cujo e o nivel de acesso
	int Finall, Loop, Linha = 3;
    char str[512];
    for(Finall = Loop = 0;Loop<Linha;++Loop){
        if(0==fgets(str, sizeof(str), Arquivo)){
            Finall = 1;
            break;
        }
    }
	//////////////////////////////////////////////////////////////////////////////  
	
	//Redireciona para o respectivo menu de acordo com seu nivel	
	if (strcmp(str,"Nivel de Acesso: 2")==0){
			system("cls");
			PainelAdministrativo();	
			fclose(Arquivo);
	}else if(strcmp(str,"Nivel de Acesso: 1")==0){
			system("cls");
			PainelFuncionario();
			fclose(Arquivo);
	}
	//////////////////////////////////////////////////////////////////////////////  
		break;}	
	
	
}//Cadastro Cardapio

void Cardapio(){
setlocale(LC_ALL, "Portuguese"); //Define o programa para aceitar acentuações em portugues
setlocale(LC_NUMERIC, "pt_BR"); //Define o programa para aceitar Virgulas no lugar do ponto
	
  Local = "\\AppData\\Martiello\\Cardapio.txt";
  Disparo = (char *) malloc(1 + strlen(PegaUser)+ strlen(Local) );
  strcpy(Disparo, PegaUser);
  strcat(Disparo, Local); 
  Arquivo = fopen(Disparo,"r");
  
  	printf("Cardapio\n---------------------------------------------------------------------------------------------\n");

    char Termino[Letras];
    while(Arquivo && fgets(Termino, sizeof(Termino), Arquivo))
    {
        if (strstr(Termino, "ID : "))
            printf("%s", Termino);
        else if (strstr(Termino, "Nome da Pizza : "))
            printf("%s", Termino);
    	else if (strstr(Termino, "Ingredientes : "))
            printf("%s", Termino);
        else if (strstr(Termino, "Valor Grande R$: "))
            printf("%s", Termino);
		else if (strstr(Termino, "Valor Broto R$: "))
            printf("%s\n", Termino);
        else if (strstr(Termino, "Nome Bebida : "))
            printf("%s", Termino);
        else if (strstr(Termino, "Litros ou ml : "))
            printf("%s", Termino);
       else if (strstr(Termino, "Valor R$: "))
            printf("%s\n", Termino);    
        else if (strstr(Termino, "Nome Produto : "))
            printf("%s", Termino);   
    	else if (strstr(Termino, "Descrição : "))
            printf("%s", Termino);   
        else if (strstr(Termino, "Valor Uni R$ : "))
            printf("%s\n", Termino); 
	}
int Sair;
printf("Para retornar ao menu Digite 1\n- ");
while(scanf("%d",&Sair) != 1|| Sair >1||Sair <= 0)
    	{
        printf("Digite uma Opcao valida!\n");
	    while(getchar() != '\n');
	    sleep(1);
	    system("cls");
	    Cardapio();
		}		
	//Abre o arquivo do respectivo usuario logado para ver seu nivel de acesso	
	Local = "\\AppData\\Martiello\\Funcionarios\\Logins\\";
 	Disparo = (char *) malloc(1 + strlen(PegaUser)+ strlen(Local)+ strlen(Usuario)+ strlen(Final));
  	strcpy(Disparo, PegaUser);
 	strcat(Disparo, Local); 
 	strcat(Disparo, Usuario); 
  	strcat(Disparo, Final); 
  	Arquivo = fopen(Disparo,"r"); 
	//////////////////////////////////////////////////////////////////////////////  
	
		
	//Verifica uma linha especifica do arquivo cujo e o nivel de acesso
	int Finall, Loop, Linha = 3;
    char str[512];
    for(Finall = Loop = 0;Loop<Linha;++Loop){
        if(0==fgets(str, sizeof(str), Arquivo)){
            Finall = 1;
            break;
        }
    }
	//////////////////////////////////////////////////////////////////////////////  
		
	
	//Redireciona para o respectivo menu de acordo com seu nivel	
	if (Sair == 1){
	if (strcmp(str,"Nivel de Acesso: 2")==0){
			system("cls");
			PainelAdministrativo();	
	}else if(strcmp(str,"Nivel de Acesso: 1")==0){
			system("cls");
			PainelFuncionario();
	}
	}
	//////////////////////////////////////////////////////////////////////////////  
    if(Arquivo){fclose(Arquivo);}			
}//Cardapio

int Pedido(){

  fclose(fopen("Temporario.txt", "w"));//Limpa o arquivo temporario para a nova entrada de Dados
  //Define as variaveis abaixo para o uso de data e hora para registrar a data e hora que o pedido foi feito
  time_t segundos;  
  time(&segundos);   
  DataEHora = localtime(&segundos); 
  //////////////////////////////////////////////////////////////////////////////  

setlocale(LC_ALL, "Portuguese"); //Define o programa para aceitar acentuações em portugues
setlocale(LC_NUMERIC, "pt_BR"); //Define o programa para aceitar Virgulas no lugar do ponto

printf("Realize o Pedido\n---------------------------------------------------------------------------------------------\n");
printf("Selecione uma das Opcao para realizar o pedido |1| Mesa / |2| Entrega / |3| Voltar\n- ");
    while(scanf("%d",&MesaEntrega) != 1 || MesaEntrega > 3 || MesaEntrega <= 0)
    {
        printf("Digite uma Opcao valida!\n");
	    while(getchar() != '\n');
        memset(&MesaEntrega, 0, sizeof (MesaEntrega));
	    sleep(1);
        system("cls");
        return Pedido();
        break;
    }		
	switch(MesaEntrega){
		case 1:
		printf("Numero da Mesa\n- ");
		
		while(scanf("%d",&NumeroMesa) != 1)
    	{
        printf("Digite uma Opcao valida!\n");
	    while(getchar() != '\n');
        memset(&NumeroMesa, 0, sizeof (NumeroMesa));
	    sleep(1);
        system("cls");
        printf("Realize o Pedido\n---------------------------------------------------------------------------------------------\n");
		printf("Selecione uma das Opcao para realizar o pedido |1| Mesa / |2| Entrega / |3| Voltar\n- 1\n");
		printf("Numero da Mesa\n- ");
    	}		
		
		printf("Quantas Pessoas\n- ");
		
	 	while(scanf("%d",&QPessoas) != 1 || QPessoas <=0)
    	{
        printf("Digite uma Opcao valida!\n");
	    while(getchar() != '\n');
        memset(&QPessoas, 0, sizeof (QPessoas));
	    sleep(1);
        system("cls");
        printf("Realize o Pedido\n---------------------------------------------------------------------------------------------\n");
		printf("Selecione uma das Opcao para realizar o pedido |1| Mesa / |2| Entrega / |3| Voltar\n- 1\n");
		printf("Numero da Mesa\n- %d\n",NumeroMesa);
		printf("Quantas Pessoas\n- ");
    	}		
    	
		printf("[R]odizio ou [P]izza\n- ");
		scanf("%s",&RodizioOuPizza);
		
		while(1){
		if (strcmp(RodizioOuPizza,"r")==0 ||(strcmp(RodizioOuPizza,"R")==0)){
		printf("Insira o Preco do Rodizio\n- ");
		scanf("%f",&PrecoRodizio);
		ValorASerPago = PrecoRodizio * QPessoas;
		
		printf("Qual o metodo de Pagamento [1]Dinheiro [2]Cartao\n- ");
		while(scanf("%d",&DinheiroCartao) != 1 || DinheiroCartao <= 0 || DinheiroCartao >=3)
    	{
        printf("Digite uma Opcao valida!\n");
	    while(getchar() != '\n');
        memset(&DinheiroCartao, 0, sizeof (DinheiroCartao));
	    sleep(1);
        system("cls");
        printf("Realize o Pedido\n---------------------------------------------------------------------------------------------\n");
		printf("Selecione uma das Opcao para realizar o pedido |1| Mesa / |2| Entrega / |3| Voltar\n- 1\n");
		printf("Numero da Mesa\n- %d\n",NumeroMesa);
		printf("Quantas Pessoas\n- %d\n",QPessoas);
		printf("[R]odizio ou [P]izza\n- %s\n",RodizioOuPizza);
		printf("Insira o Preco do Rodizio\n- %.2f\n",PrecoRodizio);
		printf("Qual o metodo de Pagamento [1]Dinheiro [2]Cartao\n- ");
    	}	

    	//Dinheiro
		if (DinheiroCartao == 1){
		printf("Comentario de Avaliação do Cliente\n- ");
		scanf(" %[^\n]s",&Avaliacao);
		system("cls");
		printf("Confirmacao do Pedido\n---------------------------------------------------------------------------------------------\n");
		printf("Tipo de Pedido : Local\nTipo : Rodizio\nNumero da Mesa : %d\nPessoas : %d\nPreco do Rodizio : %.2f\nValor Total : %.2f\nPagamento : Dinheiro\nComentario do Cliente : %s\n\nAs Informacoes acima estao corretas? Deseja dar baixa neste pedido? S/N\n- ",NumeroMesa,QPessoas,PrecoRodizio,ValorASerPago,Avaliacao);
		scanf("%s",&SimNao);

		
		while(1){
		if (strcmp(SimNao,"s")==0||(strcmp(SimNao,"S")==0)){
		//Abre o arquivo de Registro para poder ser inserido no final final do pedido o respectivo dados da comanda		
 		 Local = "\\AppData\\Martiello\\Registro.txt";
  		Disparo = (char *) malloc(1 + strlen(PegaUser)+ strlen(Local) );
  		strcpy(Disparo, PegaUser);
  		strcat(Disparo, Local); 
  		Arquivo = fopen(Disparo,"a");
  		//////////////////////////////////////////////////////////////////////////////  
  		
		fprintf(Arquivo,"======================================\n\nTipo de Pedido : Local\nTipo : Rodizio\nNumero da Mesa : %d\nPessoas : %d\nPreco do Rodizio : %.2f\nValor Total : %.2f\nPagamento : Dinheiro\nStatus : PAGO\nComentario do Cliente : %s\nPedido Realizado por : %s\nData : %d/%d/%d | Hora : %d:%d:%d\n======================================\n",NumeroMesa,QPessoas,PrecoRodizio,ValorASerPago,Avaliacao,Usuario,DataEHora->tm_mday,DataEHora->tm_mon+1,DataEHora->tm_year+1900,DataEHora->tm_hour,DataEHora->tm_min,DataEHora->tm_sec);
		fclose(Arquivo);
		
		//Abre o arquivo do respectivo usuario logado para pegar seu nivel de acesso
	    Local = "\\AppData\\Martiello\\Funcionarios\\Logins\\";
 	 	Disparo = (char *) malloc(1 + strlen(PegaUser)+ strlen(Local)+ strlen(Usuario)+ strlen(Final));
  		strcpy(Disparo, PegaUser);
 		strcat(Disparo, Local); 
 		strcat(Disparo, Usuario); 
  		strcat(Disparo, Final); 
  		Arquivo = fopen(Disparo,"r"); 
		//////////////////////////////////////////////////////////////////////////////  
		
		//Verifica uma linha especifica do arquivo cujo e o nivel de acesso
		int Finall, Loop, Linha = 3;
   		char str[512];
   		for(Finall = Loop = 0;Loop<Linha;++Loop){
        if(0==fgets(str, sizeof(str), Arquivo)){
            Finall = 1;
            break;
        }
    	}
		//////////////////////////////////////////////////////////////////////////////  
		
		//Retorna para o respectivo menu de acordo com seu nivel de acesso
		if (strcmp(str,"Nivel de Acesso: 2")==0){
		printf("Pedido Faturado, Retornando. . .");
		sleep(1);
		system("cls");
		fclose(Arquivo);
		Pedido();
		}else if(strcmp(str,"Nivel de Acesso: 1")==0){
		printf("Pedido Faturado, Retornando. . .");
		sleep(1);
		system("cls");
		Pedido();
		fclose(Arquivo);}
		//////////////////////////////////////////////////////////////////////////////  
		break;
		
		}else if(strcmp(SimNao,"N")==0||(strcmp(SimNao,"n")==0)){
		printf("Reiniciando Pedido. . .");
		sleep(1);
		system("cls");
		return Pedido();
		break;	
		}else{
		printf("Digite uma opcao valida!");
		sleep(1);
		system("cls");
		printf("Confirmacao do Pedido\n---------------------------------------------------------------------------------------------\n");
		printf("Tipo de Pedido : Local\nTipo : Rodizio\nNumero da Mesa : %d\nPessoas : %d\nPreco do Rodizio : %.2f\nValor Total : %.2f\nPagamento : Dinheiro\nComentario do Cliente : %s\n\nAs Informacoes acima estao corretas? Deseja dar baixa neste pedido? S/N\n- ",NumeroMesa,QPessoas,PrecoRodizio,ValorASerPago,Avaliacao);
		scanf("%s",&SimNao);}
		}
		
		
		
		
			
		//Cartao
		}else if(DinheiroCartao == 2){
		printf("Parcelas do Pedido\n- ");
		
		while(scanf("%d",&Parcelamento) != 1 || Parcelamento <=0)
    	{
        printf("Digite uma Opcao de parcelamento Valida!\n");
	    while(getchar() != '\n');
	    memset(&Parcelamento, 0, sizeof (Parcelamento));
	    sleep(1);
        system("cls");
        printf("Realize o Pedido\n---------------------------------------------------------------------------------------------\n");
		printf("Selecione uma das Opcao para realizar o pedido |1| Mesa / |2| Entrega / |3| Voltar\n- 1\n");
		printf("Numero da Mesa\n- %d\n",NumeroMesa);
		printf("Quantas Pessoas\n- %d\n",QPessoas);
		printf("[R]odizio ou [P]izza\n- %s\n",RodizioOuPizza);
		printf("Insira o Preco do Rodizio\n- %.2f\n",PrecoRodizio);
		printf("Qual o metodo de Pagamento [1]Dinheiro [2]Cartao\n- 2\n");
		printf("Parcelas do Pedido\n- ");
		}
		
		ValorParcela = ValorASerPago / Parcelamento;
		printf("Comentario de Avalição do Cliente\n- ");
		scanf(" %[^\n]s",&Avaliacao);
		system("cls");
		printf("Confirmacao do Pedido\n---------------------------------------------------------------------------------------------\n");
		printf("Tipo de Pedido : Local\nTipo : Rodizio\nNumero da Mesa : %d\nPessoas : %d\nPreco do Rodizio : %.2f\nValor Total : %.2f\nPagamento : Cartao\nParcelas : %d\nValor das Parcelas : %.2f\nComentario do Cliente : %s\n\nAs Informacoes acima estao corretas? Deseja dar baixa neste pedido? S/N\n",NumeroMesa,QPessoas,PrecoRodizio,ValorASerPago,Parcelamento,ValorParcela,Avaliacao);
		scanf("%s",&SimNao);
		
		while(1){
		if (strcmp(SimNao,"s")==0||(strcmp(SimNao,"S")==0)){
		//Abre o arquivo de Registro para poder ser inserido no final final do pedido o respectivo dados da comanda		
 		Local = "\\AppData\\Martiello\\Registro.txt";
  		Disparo = (char *) malloc(1 + strlen(PegaUser)+ strlen(Local) );
  		strcpy(Disparo, PegaUser);
  		strcat(Disparo, Local); 
  		Arquivo = fopen(Disparo,"a");
  		//////////////////////////////////////////////////////////////////////////////  
  			
		fprintf(Arquivo,"======================================\n\nTipo de Pedido : Local\nTipo : Rodizio\nNumero da Mesa : %d\nPessoas : %d\nPreco do Rodizio : %.2f\nValor Total : %.2f\nPagamento : Cartao\nParcelas : %d\nValor das Parcelas : %.2f\nComentario do Cliente : %s\nPedido Realizado por : %s\nStatus : PAGO\nData : %d/%d/%d | Hora : %d:%d:%d\n",NumeroMesa,QPessoas,PrecoRodizio,ValorASerPago,Parcelamento,ValorParcela,Avaliacao,Usuario,DataEHora->tm_mday,DataEHora->tm_mon+1,DataEHora->tm_year+1900,DataEHora->tm_hour,DataEHora->tm_min,DataEHora->tm_sec);
		fclose(Arquivo);
		
		//Abre o arquivo do respectivo usuario logado para pegar seu nivel de acesso
	    Local = "\\AppData\\Martiello\\Funcionarios\\Logins\\";
 	 	Disparo = (char *) malloc(1 + strlen(PegaUser)+ strlen(Local)+ strlen(Usuario)+ strlen(Final));
  		strcpy(Disparo, PegaUser);
 		strcat(Disparo, Local); 
 		strcat(Disparo, Usuario); 
  		strcat(Disparo, Final); 
  		Arquivo = fopen(Disparo,"r"); 
		//////////////////////////////////////////////////////////////////////////////  
		
		//Verifica uma linha especifica do arquivo cujo e o nivel de acesso
		int Finall, Loop, Linha = 3;
   		char str[512];
   		for(Finall = Loop = 0;Loop<Linha;++Loop){
        if(0==fgets(str, sizeof(str), Arquivo)){
            Finall = 1;
            break;
        }
    	}
		//////////////////////////////////////////////////////////////////////////////  
		
		//Retorna para o respectivo menu de acordo com seu nivel de acesso
		if (strcmp(str,"Nivel de Acesso: 2")==0){
		printf("Pedido Faturado, Retornando. . .");
		sleep(1);
		system("cls");
		Pedido();
		fclose(Arquivo);
		}else if(strcmp(str,"Nivel de Acesso: 1")==0){
		printf("Pedido Faturado, Retornando. . .");
		sleep(1);
		system("cls");
		Pedido();
		fclose(Arquivo);}
		//////////////////////////////////////////////////////////////////////////////  
		break;
		}else if(strcmp(SimNao,"N")==0||(strcmp(SimNao,"n")==0)){
		printf("Reiniciando Pedido. . .");
		sleep(1);
		system("cls");
		return Pedido();
		break;	
		}else{
		printf("Digite uma opcao valida!");
		sleep(1);
		system("cls");
		printf("Confirmacao do Pedido\n---------------------------------------------------------------------------------------------\n");
		printf("Tipo de Pedido : Local\nTipo : Rodizio\nNumero da Mesa : %d\nPessoas : %d\nPreco do Rodizio : %.2f\nValor Total : %.2f\nPagamento : Cartao\nParcelas : %d\nValor das Parcelas : %.2f\nComentario do Cliente : %s\n\nAs Informacoes acima estao corretas? Deseja dar baixa neste pedido? S/N\n",NumeroMesa,QPessoas,PrecoRodizio,ValorASerPago,Parcelamento,ValorParcela,Avaliacao);
		scanf("%s",&SimNao);}
		}}
		 	
		break;
		}else if (strcmp(RodizioOuPizza,"p")==0||(strcmp(RodizioOuPizza,"P")==0)){	
		printf("Quantidade de Pizzas\n* ");
		while(scanf("%d",&QuantidadePizza) != 1 || QuantidadePizza <=0)
    	{
        printf("Digite uma Quantidade Valida!\n");
	    while(getchar() != '\n');
		sleep(1);
		system("cls");
        printf("Realize o Pedido\n---------------------------------------------------------------------------------------------\n");
		printf("Selecione uma das Opcao para realizar o pedido |1| Mesa / |2| Entrega / |3| Voltar\n- 1\n");
		printf("Numero da Mesa\n- %d\n",NumeroMesa);
		printf("Quantas Pessoas\n- %d\n",QPessoas);
		printf("[R]odizio ou [P]izza\n- %s\n",RodizioOuPizza);
		printf("Quantidade de Pizzas\n* ");
		}
		Local = "\\AppData\\Martiello\\Cardapio.txt";
		Disparo = (char *) malloc(1 + strlen(PegaUser)+ strlen(Local) );
		strcpy(Disparo, PegaUser);
		strcat(Disparo, Local); 
		Arquivo = fopen(Disparo,"r");
		struct Ficha empty = {0};
		fflush(stdin);
		///////////////////////////////////////////////////////////////////////
		if (!(Arquivo = fopen (Disparo, "r"))){
        perror ("Ocorreu um problema ao carregar o arquivo de Cardapio ou certifique que a items no cardapio!");
        return 1;
    	}
		
	Temporario = fopen("Temporario.txt","a+");
	fprintf(Temporario,"======================================\n\n* Produtos Pedidos\n");
	fclose(Temporario);
		
	
    	for(i=0;i < QuantidadePizza;i++){ 
        int ID = 0, Entrada = 0;

        rewind(Arquivo);
        fputs("Insira o ID do Produto: ", stdout);
        fflush(stdout); 

        if (!fgets (Saida, Letras, stdin) || strcmp (Saida, "quit\n") == 0)
            break;  
        if (sscanf (Saida, "%d", &Entrada) != 1) {
            fputs ("Digite um Numero de ID valido!, Reiniciando Pedido. . .\n", stderr);
            sleep(1);
            system("cls");
            Pedido();
            break;
        }
        while (fgets (Saida, Letras, Arquivo))
            if (sscanf (Saida, "ID : %d", &ID) == 1 && ID == Entrada)
                break;
        if (ID != Entrada){ 
            fputs("ID Nao foi Encontrado!\n", stderr);
            continue;
        }
        while (fgets (Saida, Letras, Arquivo) && *Saida != '='){		
		Temporario = fopen("Temporario.txt","a+");
		fprintf(Temporario,"%s",Saida);
		fclose(Temporario);
    	}
		}
		printf("\nComentario de Avaliação do Cliente\n- ");
		scanf(" %[^\n]s",&Avaliacao);
		printf("Qual o metodo de Pagamento [1]Dinheiro [2]Cartao\n- ");
		while(1){
		while(scanf("%d",&DinheiroCartao) != 1 || DinheiroCartao <= 0 || DinheiroCartao >=3)
    	{
        printf("Digite uma Opcao valida!\n");
	    while(getchar() != '\n');
        memset(&DinheiroCartao, 0, sizeof (DinheiroCartao));
		printf("Qual o metodo de Pagamento [1]Dinheiro [2]Cartao\n- ");
		}
		if(DinheiroCartao == 1){
					
		Temporario = fopen("Temporario.txt","a+");
		fprintf(Temporario,"Tipo de Pedido : Local\nTipo : Mesa\nNumero da Mesa : %d\nPessoas : %d\nPagamento : Dinheiro\nStatus : PAGO\nPedido Realizado por : %s\nData : %d/%d/%d | Hora : %d:%d:%d\n\n",NumeroMesa,QPessoas,Usuario,DataEHora->tm_mday,DataEHora->tm_mon+1,DataEHora->tm_year+1900,DataEHora->tm_hour,DataEHora->tm_min,DataEHora->tm_sec);
		fclose(Temporario);
		printf("\nIndo para a Confirmacao de Dados. . .");
    	sleep(1);
		Sumario();
    	fclose(Arquivo);
		}else if(DinheiroCartao==2){
					
		Temporario = fopen("Temporario.txt","a+");
		fprintf(Temporario,"Tipo de Pedido : Local\nTipo : Mesa\nNumero da Mesa : %d\nPessoas : %d\nPagamento : Cartao\nStatus : PAGO\nPedido Realizado por : %s\nData : %d/%d/%d | Hora : %d:%d:%d\n\n",NumeroMesa,QPessoas,Usuario,DataEHora->tm_mday,DataEHora->tm_mon+1,DataEHora->tm_year+1900,DataEHora->tm_hour,DataEHora->tm_min,DataEHora->tm_sec);
		fclose(Temporario);
		printf("\nIndo para a Confirmacao de Dados. . .");
    	sleep(1);
		Sumario();
    	fclose(Arquivo);
		}else{
		printf("Digite uma Opcao valida!\n");
		while(scanf("%d",&DinheiroCartao) != 1 || DinheiroCartao <= 0 || DinheiroCartao >=3)
    	{
        printf("Digite uma Opcao valida!\n");
	    while(getchar() != '\n');
        memset(&DinheiroCartao, 0, sizeof (DinheiroCartao));
		}
		
		}
		
		
		}
    	return 0;
		///////////////////////////////////////////////////////////////////////
		
		
		}else{
		printf("Insira uma opcao Valida!");
		sleep(1);
		system("cls");
		printf("Realize o Pedido\n---------------------------------------------------------------------------------------------\n");
		printf("Selecione uma das Opcao para realizar o pedido |1| Mesa / |2| Entrega / [3] Sair\n- 1\n");
		printf("Numero da Mesa\n- %d\n",NumeroMesa);
		printf("Quantas Pessoas\n- %d\n",QPessoas);
		printf("[R]odizio ou [P]izza\n- ");
		scanf("%s",&RodizioOuPizza);}
		}	
		break;
		
		
		
		
		
		
		int CidadeEntrega=0;

		case 2:
		printf("Nome do Cliente\n- ");
		scanf(" %[^\n]s",&Dados.Nome);
		printf("Insira o Endereco de Entrega\n- ");
		scanf(" %[^\n]s",&Dados.Endereco);
		printf("Numero\n- ");
		scanf(" %[^\n]s",&Dados.Numero);
		printf("Referencia\n- ");
		scanf(" %[^\n]s",&Dados.Complemento);
		printf("Qual o metodo de Pagamento [1]Dinheiro [2]Cartao\n- ");
		while(scanf("%d",&DinheiroCartao) != 1 || DinheiroCartao <= 0 || DinheiroCartao >=3)
    	{
        printf("Digite uma Opcao valida!\n");
	    while(getchar() != '\n');
        memset(&DinheiroCartao, 0, sizeof (DinheiroCartao));
	    sleep(1);
	    system("cls");
	    printf("Realize o Pedido\n---------------------------------------------------------------------------------------------\n");
		printf("Selecione uma das Opcao para realizar o pedido |1| Mesa / |2| Entrega / |3| Voltar\n- 2");
		printf("Nome do Cliente\n- %s\n",Dados.Nome);
		printf("Insira o Endereco de Entrega\n- %s\n",Dados.Endereco);
		printf("Referencia\n- %s\n",Dados.Complemento);
		printf("Numero\n- %s\n",Dados.Numero);
		printf("Qual o metodo de Pagamento [1]Dinheiro [2]Cartao\n- ");
		}
		printf("Cidade da Entrega \n[1]Guaruja - Preco de Entrega R$ 15,00 | Estimativa : 1:20\n[2]Santos - Preco de Entrega R$ 6,50 | Estimativa : 00:45\n[3]Sao Vicente - Preco de Entrega R$ 10,00 | Estimativa : 1:00\n[4]Praia Grande - Preco de Entrega 18,00 | Estimativa : 1:30\n- ");
		while(scanf("%d",&CidadeEntrega) != 1 || CidadeEntrega <= 0 || CidadeEntrega >4)
    	{
    	printf("Digite uma Opcao valida!\n");
	    while(getchar() != '\n');
	    sleep(1);
	    system("cls");
	    printf("Realize o Pedido\n---------------------------------------------------------------------------------------------\n");
		printf("Selecione uma das Opcao para realizar o pedido |1| Mesa / |2| Entrega / |3| Voltar\n- 2");
		printf("Nome do Cliente\n- %s\n",Dados.Nome);
		printf("Insira o Endereco de Entrega\n- %s\n",Dados.Endereco);
		printf("Referencia\n- %s\n",Dados.Complemento);
		printf("Numero\n- %s\n",Dados.Numero);
		printf("Cidade da Entrega [1]Guaruja - Preco de Entrega R$ 15,00 | Estimativa : 1:20\n [2]Santos - Preco de Entrega R$ 6,50 |Estimativa : 00:45\n [3]Sao Vicente - Preco de Entrega R$ 10,00 | Estimativa : 1:00\n [4]Praia Grande - Preco de Entrega 18,00 | Estimativa : 1:30\n- ");
    	}

    	

    	
    	
    	switch(CidadeEntrega){
    	//Guaruja
		case 1:
		if(DinheiroCartao==1){
		Temporario = fopen("Temporario.txt","a+");
		fprintf(Temporario,"======================================\n\nTipo de Pedido : Entrega\nNome do Cliente : %s\nEndereco : %s\nNumero : %s\nReferencia : %s\nCidade da Entrega : Guaruja\nPreco da Entrega R$ 15,00\nEstimativa de Entrega : 1:20\nMetodo de Pagamento : Dinheiro\nPedido Realizado por : %s\nData : %d/%d/%d | Hora : %d:%d:%d\n\n* Produtos Pedidos\n",Dados.Nome,Dados.Endereco,Dados.Numero,Dados.Complemento,Usuario,DataEHora->tm_mday,DataEHora->tm_mon+1,DataEHora->tm_year+1900,DataEHora->tm_hour,DataEHora->tm_min,DataEHora->tm_sec);
		fclose(Temporario);
		}else if(DinheiroCartao==2){
		Temporario = fopen("Temporario.txt","a+");
		fprintf(Temporario,"======================================\n\nTipo de Pedido : Entrega\nNome do Cliente : %s\nEndereco : %s\nNumero : %s\nReferencia : %s\nCidade da Entrega : Guaruja\nPreco da Entrega R$ 15,00\nEstimativa de Entrega : 1:20\nMetodo de Pagamento : Cartao\nPedido Realizado por : %s\nData : %d/%d/%d | Hora : %d:%d:%d\n\n* Produtos Pedidos\n",Dados.Nome,Dados.Endereco,Dados.Numero,Dados.Complemento,Usuario,DataEHora->tm_mday,DataEHora->tm_mon+1,DataEHora->tm_year+1900,DataEHora->tm_hour,DataEHora->tm_min,DataEHora->tm_sec);
		fclose(Temporario);
		}
			
			
		printf("Quantidade de Pizzas\n- ");
		while(scanf("%d",&QuantidadePizza) != 1 || QuantidadePizza <=0)
    	{
        printf("Digite uma Opcao valida!\n");
	    while(getchar() != '\n');
	    sleep(1);
	    system("cls");
	    printf("Realize o Pedido\n---------------------------------------------------------------------------------------------\n");
		printf("Selecione uma das Opcao para realizar o pedido |1| Mesa / |2| Entrega / |3| Voltar\n- 2");
		printf("Nome do Cliente\n- %s\n",Dados.Nome);
		printf("Insira o Endereco de Entrega\n- %s\n",Dados.Endereco);
		printf("Referencia\n- %s\n",Dados.Complemento);
		printf("Numero\n- %s\n",Dados.Numero);
		printf("Cidade da Entrega [1]Guaruja - Preco de Entrega R$ 15,00 | Estimativa : 1:20\n [2]Santos - Preco de Entrega R$ 6,50 |Estimativa : 00:45\n [3]Sao Vicente - Preco de Entrega R$ 10,00 | Estimativa : 1:00\n [4]Praia Grande - Preco de Entrega 18,00 | Estimativa : 1:30\n- 1");
		printf("Quantidade de Pizzas\n- ");
		}
		Local = "\\AppData\\Martiello\\Cardapio.txt";
		Disparo = (char *) malloc(1 + strlen(PegaUser)+ strlen(Local) );
		strcpy(Disparo, PegaUser);
		strcat(Disparo, Local); 
		Arquivo = fopen(Disparo,"r");
		fflush(stdin);
		///////////////////////////////////////////////////////////////////////
		if (!(Arquivo = fopen (Disparo, "r"))){
        perror ("Ocorreu um problema ao carregar o arquivo de Cardapio ou certifique que a items no cardapio!");
        return 1;
    	}
    	for(i=0;i < QuantidadePizza;i++){ 
        int ID = 0, Entrada = 0;

        rewind(Arquivo);
        fputs("Insira o ID do Produto: ", stdout);
        fflush(stdout); 

        if (!fgets (Saida, Letras, stdin) || strcmp (Saida, "quit\n") == 0)
            break;  
        if (sscanf (Saida, "%d", &Entrada) != 1) {
            fputs ("Digite um Numero de ID valido!, Reiniciando Pedido. . .\n", stderr);
            sleep(1);
            system("cls");
            Pedido();
            break;
        }
        while (fgets (Saida, Letras, Arquivo))
            if (sscanf (Saida, "ID : %d", &ID) == 1 && ID == Entrada)
                break;
        if (ID != Entrada){ 
            fputs("ID Nao foi Encontrado!\n", stderr);
            continue;
        }
        while (fgets (Saida, Letras, Arquivo) && *Saida != '='){		
		Temporario = fopen("Temporario.txt","a+");
		fprintf(Temporario,"%s",Saida);
		fclose(Temporario);
    	}
		}
		fprintf(Temporario,"======================================\n");
		fclose(Temporario);
		Sumario();
		fclose(Arquivo);
		break;	
    	
    	//Santos
    	case 2:
    	if(DinheiroCartao==1){
		Temporario = fopen("Temporario.txt","a+");
		fprintf(Temporario,"======================================\n\nTipo de Pedido : Entrega\nNome do Cliente : %s\nEndereco : %s\nNumero : %s\nReferencia : %s\nCidade da Entrega : Santos\nPreco da Entrega R$ 6,50\nEstimativa de Entrega : 0:45\nMetodo de Pagamento : Dinheiro\nPedido Realizado por : %s\nData : %d/%d/%d | Hora : %d:%d:%d\n\n* Produtos Pedidos\n",Dados.Nome,Dados.Endereco,Dados.Numero,Dados.Complemento,Usuario,DataEHora->tm_mday,DataEHora->tm_mon+1,DataEHora->tm_year+1900,DataEHora->tm_hour,DataEHora->tm_min,DataEHora->tm_sec);
		fclose(Temporario);
		}else if(DinheiroCartao==2){
		Temporario = fopen("Temporario.txt","a+");
		fprintf(Temporario,"======================================\n\nTipo de Pedido : Entrega\nNome do Cliente : %s\nEndereco : %s\nNumero : %s\nReferencia : %s\nCidade da Entrega : Santos\nPreco da Entrega R$ 6,50\nEstimativa de Entrega : 0:45\nMetodo de Pagamento : Cartao\nPedido Realizado por : %s\nData : %d/%d/%d | Hora : %d:%d:%d\n\n* Produtos Pedidos\n",Dados.Nome,Dados.Endereco,Dados.Numero,Dados.Complemento,Usuario,DataEHora->tm_mday,DataEHora->tm_mon+1,DataEHora->tm_year+1900,DataEHora->tm_hour,DataEHora->tm_min,DataEHora->tm_sec);
		fclose(Temporario);
		}
					
			
		printf("Quantidade de Pizzas\n- ");
		while(scanf("%d",&QuantidadePizza) != 1 || QuantidadePizza <=0)
    	{
        printf("Digite uma Opcao valida!\n");
	    while(getchar() != '\n');
	    sleep(1);
	    system("cls");
	    printf("Realize o Pedido\n---------------------------------------------------------------------------------------------\n");
		printf("Selecione uma das Opcao para realizar o pedido |1| Mesa / |2| Entrega / |3| Voltar\n- 2");
		printf("Nome do Cliente\n- %s\n",Dados.Nome);
		printf("Insira o Endereco de Entrega\n- %s\n",Dados.Endereco);
		printf("Referencia\n- %s\n",Dados.Complemento);
		printf("Numero\n- %s\n",Dados.Numero);
		printf("Cidade da Entrega [1]Guaruja - Preco de Entrega R$ 15,00 | Estimativa : 1:20\n [2]Santos - Preco de Entrega R$ 6,50 |Estimativa : 00:45\n [3]Sao Vicente - Preco de Entrega R$ 10,00 | Estimativa : 1:00\n [4]Praia Grande - Preco de Entrega 18,00 | Estimativa : 1:30\n- 1");
		printf("Quantidade de Pizzas\n- ");
		}
		Local = "\\AppData\\Martiello\\Cardapio.txt";
		Disparo = (char *) malloc(1 + strlen(PegaUser)+ strlen(Local) );
		strcpy(Disparo, PegaUser);
		strcat(Disparo, Local); 
		Arquivo = fopen(Disparo,"r");
		fflush(stdin);
		///////////////////////////////////////////////////////////////////////
		if (!(Arquivo = fopen (Disparo, "r"))){
        perror ("Ocorreu um problema ao carregar o arquivo de Cardapio ou certifique que a items no cardapio!");
        return 1;
    	}
    	for(i=0;i < QuantidadePizza;i++){ 
        int ID = 0, Entrada = 0;

        rewind(Arquivo);
        fputs("Insira o ID do Produto: ", stdout);
        fflush(stdout); 

        if (!fgets (Saida, Letras, stdin) || strcmp (Saida, "quit\n") == 0)
            break;  
        if (sscanf (Saida, "%d", &Entrada) != 1) {
            fputs ("Digite um Numero de ID valido!, Reiniciando Pedido. . .\n", stderr);
            sleep(1);
            system("cls");
            Pedido();
            break;
        }
        while (fgets (Saida, Letras, Arquivo))
            if (sscanf (Saida, "ID : %d", &ID) == 1 && ID == Entrada)
                break;
        if (ID != Entrada){ 
            fputs("ID Nao foi Encontrado!\n", stderr);
            continue;
        }
        while (fgets (Saida, Letras, Arquivo) && *Saida != '='){		
		Temporario = fopen("Temporario.txt","a+");
		fprintf(Temporario,"%s",Saida);
		fclose(Temporario);
    	}
		}
		Sumario();
		fclose(Arquivo);
		break;	
		
		//Sao Vicente
		case 3:
		if(DinheiroCartao==1){
		Temporario = fopen("Temporario.txt","a+");
		fprintf(Temporario,"======================================\n\nTipo de Pedido : Entrega\nNome do Cliente : %s\nEndereco : %s\nNumero : %s\nReferencia : %s\nCidade da Entrega : Sao Vicente\nPreco da Entrega R$ 10,00\nEstimativa de Entrega : 1:00\nMetodo de Pagamento : Dinheiro\nPedido Realizado por : %s\nData : %d/%d/%d | Hora : %d:%d:%d\n\n* Produtos Pedidos\n",Dados.Nome,Dados.Endereco,Dados.Numero,Dados.Complemento,Usuario,DataEHora->tm_mday,DataEHora->tm_mon+1,DataEHora->tm_year+1900,DataEHora->tm_hour,DataEHora->tm_min,DataEHora->tm_sec);
		fclose(Temporario);
		}else if(DinheiroCartao==2){
		Temporario = fopen("Temporario.txt","a+");
		fprintf(Temporario,"======================================\n\nTipo de Pedido : Entrega\nNome do Cliente : %s\nEndereco : %s\nNumero : %s\nReferencia : %s\nCidade da Entrega : Sao Vicente\nPreco da Entrega R$ 10,00\nEstimativa de Entrega : 1:00\nMetodo de Pagamento : Cartao\nPedido Realizado por : %s\nData : %d/%d/%d | Hora : %d:%d:%d\n\n* Produtos Pedidos\n",Dados.Nome,Dados.Endereco,Dados.Numero,Dados.Complemento,Usuario,DataEHora->tm_mday,DataEHora->tm_mon+1,DataEHora->tm_year+1900,DataEHora->tm_hour,DataEHora->tm_min,DataEHora->tm_sec);
		fclose(Temporario);
		}
		
					
			
		printf("Quantidade de Pizzas\n- ");
		while(scanf("%d",&QuantidadePizza) != 1 || QuantidadePizza <=0)
    	{
        printf("Digite uma Opcao valida!\n");
	    while(getchar() != '\n');
	    sleep(1);
	    system("cls");
	    printf("Realize o Pedido\n---------------------------------------------------------------------------------------------\n");
		printf("Selecione uma das Opcao para realizar o pedido |1| Mesa / |2| Entrega / |3| Voltar\n- 2");
		printf("Nome do Cliente\n- %s\n",Dados.Nome);
		printf("Insira o Endereco de Entrega\n- %s\n",Dados.Endereco);
		printf("Referencia\n- %s\n",Dados.Complemento);
		printf("Numero\n- %s\n",Dados.Numero);
		printf("Cidade da Entrega [1]Guaruja - Preco de Entrega R$ 15,00 | Estimativa : 1:20\n [2]Santos - Preco de Entrega R$ 6,50 |Estimativa : 00:45\n [3]Sao Vicente - Preco de Entrega R$ 10,00 | Estimativa : 1:00\n [4]Praia Grande - Preco de Entrega 18,00 | Estimativa : 1:30\n- 1");
		printf("Quantidade de Pizzas\n- ");
		}
		Local = "\\AppData\\Martiello\\Cardapio.txt";
		Disparo = (char *) malloc(1 + strlen(PegaUser)+ strlen(Local) );
		strcpy(Disparo, PegaUser);
		strcat(Disparo, Local); 
		Arquivo = fopen(Disparo,"r");
		fflush(stdin);
		///////////////////////////////////////////////////////////////////////
		if (!(Arquivo = fopen (Disparo, "r"))){
        perror ("Ocorreu um problema ao carregar o arquivo de Cardapio ou certifique que a items no cardapio!");
        return 1;
    	}
    	for(i=0;i < QuantidadePizza;i++){ 
        int ID = 0, Entrada = 0;

        rewind(Arquivo);
        fputs("Insira o ID do Produto: ", stdout);
        fflush(stdout); 

        if (!fgets (Saida, Letras, stdin) || strcmp (Saida, "quit\n") == 0)
            break;  
        if (sscanf (Saida, "%d", &Entrada) != 1) {
            fputs ("Digite um Numero de ID valido!, Reiniciando Pedido. . .\n", stderr);
            sleep(1);
            system("cls");
            Pedido();
            break;
        }
        while (fgets (Saida, Letras, Arquivo))
            if (sscanf (Saida, "ID : %d", &ID) == 1 && ID == Entrada)
                break;
        if (ID != Entrada){ 
            fputs("ID Nao foi Encontrado!\n", stderr);
            continue;
        }
        while (fgets (Saida, Letras, Arquivo) && *Saida != '='){		
		Temporario = fopen("Temporario.txt","a+");
		fprintf(Temporario,"%s",Saida);
		fclose(Temporario);
    	}
		}
		Sumario();
		fclose(Arquivo);
		break;
		
		//Praia Grande
		case 4:
		if(DinheiroCartao==1){
		Temporario = fopen("Temporario.txt","a+");
		fprintf(Temporario,"======================================\n\nTipo de Pedido : Entrega\nNome do Cliente : %s\nEndereco : %s\nNumero : %s\nReferencia : %s\nCidade da Entrega : Santos\nPreco da Entrega R$ 18,00\nEstimativa de Entrega : 1:30\nMetodo de Pagamento : Dinheiro\nPedido Realizado por : %s\nData : %d/%d/%d | Hora : %d:%d:%d\n\n* Produtos Pedidos\n",Dados.Nome,Dados.Endereco,Dados.Numero,Dados.Complemento,Usuario,DataEHora->tm_mday,DataEHora->tm_mon+1,DataEHora->tm_year+1900,DataEHora->tm_hour,DataEHora->tm_min,DataEHora->tm_sec);
		fclose(Temporario);
		}else if(DinheiroCartao==2){
		Temporario = fopen("Temporario.txt","a+");
		fprintf(Temporario,"======================================\n\nTipo de Pedido : Entrega\nNome do Cliente : %s\nEndereco : %s\nNumero : %s\nReferencia : %s\nCidade da Entrega : Santos\nPreco da Entrega R$ 18,00\nEstimativa de Entrega : 1:30\nMetodo de Pagamento : Cartao\nPedido Realizado por : %s\nData : %d/%d/%d | Hora : %d:%d:%d\n\n* Produtos Pedidos\n",Dados.Nome,Dados.Endereco,Dados.Numero,Dados.Complemento,Usuario,DataEHora->tm_mday,DataEHora->tm_mon+1,DataEHora->tm_year+1900,DataEHora->tm_hour,DataEHora->tm_min,DataEHora->tm_sec);
		fclose(Temporario);
		}
		
					
			
		printf("Quantidade de Pizzas\n- ");
		while(scanf("%d",&QuantidadePizza) != 1 || QuantidadePizza <=0)
    	{
        printf("Digite uma Opcao valida!\n");
	    while(getchar() != '\n');
	    sleep(1);
	    system("cls");
	    printf("Realize o Pedido\n---------------------------------------------------------------------------------------------\n");
		printf("Selecione uma das Opcao para realizar o pedido |1| Mesa / |2| Entrega / |3| Voltar\n- 2");
		printf("Nome do Cliente\n- %s\n",Dados.Nome);
		printf("Insira o Endereco de Entrega\n- %s\n",Dados.Endereco);
		printf("Referencia\n- %s\n",Dados.Complemento);
		printf("Numero\n- %s\n",Dados.Numero);
		printf("Cidade da Entrega [1]Guaruja - Preco de Entrega R$ 15,00 | Estimativa : 1:20\n [2]Santos - Preco de Entrega R$ 6,50 |Estimativa : 00:45\n [3]Sao Vicente - Preco de Entrega R$ 10,00 | Estimativa : 1:00\n [4]Praia Grande - Preco de Entrega 18,00 | Estimativa : 1:30\n- 1");
		printf("Quantidade de Pizzas\n- ");
		}
		Local = "\\AppData\\Martiello\\Cardapio.txt";
		Disparo = (char *) malloc(1 + strlen(PegaUser)+ strlen(Local) );
		strcpy(Disparo, PegaUser);
		strcat(Disparo, Local); 
		Arquivo = fopen(Disparo,"r");
		fflush(stdin);
		///////////////////////////////////////////////////////////////////////
		if (!(Arquivo = fopen (Disparo, "r"))){
        perror ("Ocorreu um problema ao carregar o arquivo de Cardapio ou certifique que a items no cardapio!");
        return 1;
    	}
    	for(i=0;i < QuantidadePizza;i++){ 
        int ID = 0, Entrada = 0;

        rewind(Arquivo);
        fputs("Insira o ID do Produto: ", stdout);
        fflush(stdout); 

        if (!fgets (Saida, Letras, stdin) || strcmp (Saida, "quit\n") == 0)
            break;  
        if (sscanf (Saida, "%d", &Entrada) != 1) {
            fputs ("Digite um Numero de ID valido!, Reiniciando Pedido. . .\n", stderr);
            sleep(1);
            system("cls");
            Pedido();
            break;
        }
        while (fgets (Saida, Letras, Arquivo))
            if (sscanf (Saida, "ID : %d", &ID) == 1 && ID == Entrada)
                break;
        if (ID != Entrada){ 
            fputs("ID Nao foi Encontrado!\n", stderr);
            continue;
        }
        while (fgets (Saida, Letras, Arquivo) && *Saida != '='){		
		Temporario = fopen("Temporario.txt","a+");
		fprintf(Temporario,"%s",Saida);
		fclose(Temporario);
    	}
		}
		Sumario();
		fclose(Arquivo);
		break;
		
		default:
		printf("Opcao Digitada Invalida!\n");
		sleep(1);
		system("cls");
		Pedido();
		break;
		}
    	
    	return 0;
		///////////////////////////////////////////////////////////////////////
		break;
		
		
		
		case 3:
		//Abre o arquivo do respectivo usuario logado para pegar seu nivel de acesso
	    Local = "\\AppData\\Martiello\\Funcionarios\\Logins\\";
 	 	Disparo = (char *) malloc(1 + strlen(PegaUser)+ strlen(Local)+ strlen(Usuario)+ strlen(Final));
  		strcpy(Disparo, PegaUser);
 		strcat(Disparo, Local); 
 		strcat(Disparo, Usuario); 
  		strcat(Disparo, Final); 
  		Arquivo = fopen(Disparo,"r"); 
		//////////////////////////////////////////////////////////////////////////////  
		
		//Verifica uma linha especifica do arquivo cujo e o nivel de acesso
		int Finall, Loop, Linha = 3;
   		char str[512];
   		for(Finall = Loop = 0;Loop<Linha;++Loop){
        if(0==fgets(str, sizeof(str), Arquivo)){
            Finall = 1;
            break;
        }
    	}
		//////////////////////////////////////////////////////////////////////////////  
		//Retorna para o respectivo menu de acordo com seu nivel de acesso
		if (strcmp(str,"Nivel de Acesso: 2")==0){
		printf("Retornando. . .");
		sleep(1);
		system("cls");
		PainelAdministrativo();
		fclose(Arquivo);
		}else if(strcmp(str,"Nivel de Acesso: 1")==0){
		printf("Retornando. . .");
		sleep(1);
		system("cls");
		PainelFuncionario();
		fclose(Arquivo);}
		//////////////////////////////////////////////////////////////////////////////  	
		break;
		
		default:
		printf("Digite uma Opcao valida!");	
		sleep(1);
		system("cls");
		return Pedido();
		break;
	
}
}//Pedido
void CadastroFuncionario(){
	printf("Tela de Cadastro de Funcionario\n---------------------------------------------------------------------------------------------\n");
	printf("Nome Completo\n* ");
	scanf(" %[^\n]s",&Dados.Nome);
	printf("Data Nascimento exemplo: 31/12/2019\n* ");
	scanf(" %[^\n]s",&Dados.Nascimento);
	printf("RG\n* ");
	scanf(" %[^\n]s",&Dados.RG);
	printf("CPF\n* ");
	while(scanf("%lld",&Dados.CPF) != 1)
    {
        printf("Digite um Numero de CPF valido!\n");
	    while(getchar() != '\n');
	    sleep(1);
	    system("cls");
	   	printf("Tela de Cadastro de Funcionario\n---------------------------------------------------------------------------------------------\n");
		printf("Nome Completo\n* %s\n",Dados.Nome);
		printf("Data Nascimento exemplo: 31/12/2019\n* %s\n",Dados.Nascimento);
		printf("RG\n* %s\n",Dados.RG);
		printf("CPF\n* ");
	}
	char Tamanho = 1 + (int)log10(Dados.CPF);

	if (Tamanho > 11 || Tamanho < 11){
    printf("O numero de CPF digitado e Invalido!\n");
	sleep(1);
	system("cls");
	CadastroFuncionario();
	}
	printf("Cargo do Funcionario\n* ");
	scanf(" %[^\n]s",&Dados.Cargo);
	printf("Endereco Ex: Rua das Palmeiras\n* ");
	scanf(" %[^\n]s",&Dados.Endereco);
	printf("Numero\n* ");
	scanf(" %[^\n]s",&Dados.Numero);
	printf("Complemento\n* ");
	scanf(" %[^\n]s",&Dados.Complemento);
	printf("Cidade\n* ");
	scanf(" %[^\n]s",&Dados.Cidade);
	printf("Estado exemplo: SP , RJ , SC. . .\n* ");
	scanf(" %[^\n]s",&Dados.Estado);
	system("cls");
	printf("Confirmação dos Dados\n---------------------------------------------------------------------------------------------\n");
	printf("Nome: %s\nData de Nascimento: %s\nRG: %s\nCPF: %lld\nCargo: %s\nEndereco: %s\nNumero: %s\nComplemento: %s\nCidade: %s\nEstado: %s\n\n",Dados.Nome,Dados.Nascimento,Dados.RG,Dados.CPF,Dados.Cargo,Dados.Endereco,Dados.Numero,Dados.Complemento,Dados.Cidade,Dados.Estado);
	printf("As Informacoes Digitadas estao corretas? S/N \n* ");
	scanf("%s",&Dados.SimNao);
	while(1){
	if (strcmp(Dados.SimNao,"S")==0 || (strcmp(Dados.SimNao,"s")==0)){
	system("cls");
	printf("Criação do Usuario de Acesso\n---------------------------------------------------------------------------------------------\n");
	printf("O Usuario deve conter no Minimo 6 Caracteres!\n");
	printf("Usuario\n* ");
	scanf(" %[^\n]s",&Dados.Usuario);
	printf("A senha de Acesso deve conter no Minimo 5 Caracteres ou Numeros sem acentos ou pontuacao!\n");
	printf("Senha\n* ");
	scanf(" %[^\n]s",&Dados.Senha);
	printf("Nivel de Acesso [1]Funcionario | [2]Gerente\n* ");
    while(scanf("%d",&NivelDeAcesso) != 1|| NivelDeAcesso >=3 || NivelDeAcesso <=0)
    {
        printf("Digite um Nivel valido!\n* ");
        sleep(1);
        while(getchar() != '\n');
        system("cls");
        printf("Criação do Usuario de Acesso\n---------------------------------------------------------------------------------------------\n");
		printf("Login\n* %s\n",Dados.Usuario);
		printf("Senha\n* %s\n",Dados.Senha);
		printf("Nivel de Acesso [1]Funcionario | [2]Gerente\n* ");


    }
	//Cria um Arquivo de Acordo com o nome do Funcionario
    Local = "\\AppData\\Martiello\\Funcionarios\\";
    Disparo = (char *) malloc(1 + strlen(PegaUser)+ strlen(Local)+ strlen(Dados.Nome)+ strlen(Final));
    strcpy(Disparo, PegaUser);
    strcat(Disparo, Local); 
    strcat(Disparo, Dados.Nome); 
    strcat(Disparo, Final); 
    Arquivo = fopen(Disparo,"a"); 
	printf("Funcionario cadastrado com Exito!\n");
	fprintf(Arquivo,"======Dados Do Funcionario======\nNome: %s\nData de Nascimento: %s\nRG: %s\nCPF: %lld\nCargo: %s\nEndereco: %s\nNumero: %s\nComplemento: %s\nCidade: %s\nEstado: %s\n\nUsuario: %s\nSenha: %s\nNivel de Acesso: %d",Dados.Nome,Dados.Nascimento,Dados.RG,Dados.CPF,Dados.Cargo,Dados.Endereco,Dados.Numero,Dados.Complemento,Dados.Cidade,Dados.Estado,Dados.Usuario,Dados.Senha,NivelDeAcesso);
	fclose(Arquivo);
    ///////////////////////////////////

	//Cria um Arquivo de Acordo com o nome do Usuario do Funcionario
    Local = "\\AppData\\Martiello\\Funcionarios\\Logins\\";
    Disparo = (char *) malloc(1 + strlen(PegaUser)+ strlen(Local)+ strlen(Dados.Usuario)+ strlen(Final));
    strcpy(Disparo, PegaUser);
    strcat(Disparo, Local); 
    strcat(Disparo, Dados.Usuario); 
    strcat(Disparo, Final); 
    Arquivo = fopen(Disparo,"a"); 
    ///////////////////////////////////

	fprintf(Arquivo,"Usuario: %s\nSenha: %s\nNivel de Acesso: %d",Dados.Usuario,Dados.Senha,NivelDeAcesso);
	fclose(Arquivo);
	printf("Redirecionando para Menu Principal. . .\n");
	sleep(3);
	system("cls");
	PainelAdministrativo();
	break;
	return 1;
	}else if (strcmp(Dados.SimNao,"n")==0 || (strcmp(Dados.SimNao,"N")==0)){
	printf("Reiniciando Cadastro. . .");
	sleep(2);
	system("cls");
	return main();
	break;
	}else{
	printf("A opcao entrada e invalida! Digite S/N \n* ");
	scanf("%s",&Dados.SimNao);
	}		
	}	
	
}//Cadastro Funcionario
void Sumario(){
	Temporario = fopen("Temporario.txt","a+");
	fprintf(Temporario,"======================================\n\n--------------------------------------\n\n");
	fclose(Temporario);
	system("cls");
	printf("Confirmacao do Pedido\n---------------------------------------------------------------------------------------------\n");	
    FILE *Temp; 
	char Leitor;
	Temp = fopen("Temporario.txt","r");
    Leitor = fgetc(Temp); 
    while (Leitor != EOF) 
    { 
        printf ("%c", Leitor); 
        Leitor = fgetc(Temp); 
    } 
    fclose(Temp);
    printf("\n\nDesejar dar baixa neste Pedido? S/N\n* ");
	scanf(" %[^\n]s",Dados.SimNao);
		
    while(1){
	if(strcmp(Dados.SimNao,"s")==0||(strcmp(Dados.SimNao,"S")==0)){
	char Transferencia;
    Temp = fopen("Temporario.txt", "r"); 
    if (Temp == NULL) 
    { 
        printf("Nao foi possivel abrir o arquivo Temporario, reinicie o programa, Caso erro persistir contate o suporte!"); 
        exit(0); 
    } 
    Local = "\\AppData\\Martiello\\Registro.txt";
  	Disparo = (char *) malloc(1 + strlen(PegaUser)+ strlen(Local) );
  	strcpy(Disparo, PegaUser);
  	strcat(Disparo, Local); 
  	Arquivo = fopen(Disparo,"a"); 
    if (Arquivo == NULL) 
    { 
        printf("Nao foi possivel abrir o arquivo de Registro, reinicie o programa, Caso erro persistir contate o suporte!"); 
        exit(0); 
    } 
    Transferencia = fgetc(Temp); 
    while (Transferencia != EOF) 
    { 
        fputc(Transferencia, Arquivo); 
        Transferencia = fgetc(Temp);  
    } 
    fclose(Temp); 
    fclose(Arquivo); 
    printf("\nPedido Adicionado com Exito ao Registro!");
    sleep(1);
    system("cls");
    Pedido();
    return 0;
	}else if(strcmp(Dados.SimNao,"n")==0||(strcmp(Dados.SimNao,"N")==0)){
	fclose(Temp); 
    fclose(Arquivo); 
    printf("\nRetornando a tela de Pedido novamente. . .");
    sleep(1);
    system("cls");
    Pedido();
    return 0;
	}else{
	printf("Digite uma Opcao Valida!");
	sleep(1);
	system("cls");
	Sumario();	
	}
		
	}
}//Sumario

void TeladeRelatorio(){
	setlocale(LC_ALL, "Portuguese"); //Define o programa para aceitar acentuações em portugues
	setlocale(LC_NUMERIC, "pt_BR"); //Define o programa para aceitar Virgulas no lugar do ponto
	
  	Local = "\\AppData\\Martiello\\Registro.txt";
  	Disparo = (char *) malloc(1 + strlen(PegaUser)+ strlen(Local) );
  	strcpy(Disparo, PegaUser);
  	strcat(Disparo, Local); 
  	Arquivo = fopen(Disparo,"r");
  
  	printf("Relatorios desta Unidade\n---------------------------------------------------------------------------------------------\n");

    char Termino[Letras];
    while(Arquivo && fgets(Termino, sizeof(Termino), Arquivo))
    {
        if (strstr(Termino, "- Nome da Pizza : "))
            printf("%s", Termino);
    	else if (strstr(Termino, "Ingredientes : "))
            printf("%s", Termino);
        else if (strstr(Termino, "Valor R$ : "))
            printf("%s\n", Termino);

		else if (strstr(Termino, "Tipo de Pedido : "))
            printf("%s", Termino);
        else if (strstr(Termino, "Tipo : "))
            printf("%s", Termino);
    	else if (strstr(Termino, "Numero da Mesa : "))
            printf("%s", Termino);
        else if (strstr(Termino, "Pessoas : "))
            printf("%s", Termino);
		else if (strstr(Termino, "Pagamento : "))
            printf("%s", Termino);
        else if (strstr(Termino, "Status : "))
            printf("%s", Termino);
		else if (strstr(Termino, "Data : "))
            printf("%s", Termino);        
    	else if (strstr(Termino, "="))
            printf("%s\n", Termino);      

       else if (strstr(Termino, "- Nome Produto : "))
            printf("%s", Termino);
		else if (strstr(Termino, "Valor Uni R$ : "))
            printf("%s", Termino);        
    	else if (strstr(Termino, "Descrição : "))
            printf("%s\n", Termino);  
            
            
        else if (strstr(Termino, "- Nome Bebida : "))
            printf("%s", Termino);
		else if (strstr(Termino, "Litros ou ml : "))
            printf("%s", Termino);        
    	else if (strstr(Termino, "Valor R$: "))
            printf("%s\n", Termino);
        
		else if (strstr(Termino, "Nome do Cliente : "))
            printf("%s", Termino);
		else if (strstr(Termino, "Endereco : "))
            printf("%s", Termino);        
    	else if (strstr(Termino, "Numero : "))
            printf("%s", Termino);
		else if (strstr(Termino, "Referencia : "))
            printf("%s", Termino);
		else if (strstr(Termino, "Preco da Entrega R$ "))
            printf("%s", Termino);        
    	else if (strstr(Termino, "Estimativa de Entrega : "))
            printf("%s\n", Termino);
		else if (strstr(Termino, "Metodo de Pagamento : "))
            printf("%s", Termino);
		else if (strstr(Termino, "Pedido Realizado por : "))
            printf("%s", Termino);         
       	else if (strstr(Termino, "* Produtos Pedidos"))
            printf("%s", Termino);       
        else if (strstr(Termino, "--------------------------------------"))
         printf("%s\n", Termino);       



	}
int Sair;
printf("Para retornar ao menu Digite 1\n- ");
while(scanf("%d",&Sair) != 1|| Sair <=0)
    	{
        printf("Digite uma Opcao valida!\n");
	    while(getchar() != '\n');
	    sleep(1);
	    system("cls");
	    TeladeRelatorio();
		}

	if(Sair>1){
	printf("Digite uma Opcao valida!\n");
	sleep(1);
	system("cls");
	TeladeRelatorio();	
	}	
	
	
	
		
	//Abre o arquivo do respectivo usuario logado para ver seu nivel de acesso	
	Local = "\\AppData\\Martiello\\Funcionarios\\Logins\\";
 	Disparo = (char *) malloc(1 + strlen(PegaUser)+ strlen(Local)+ strlen(Usuario)+ strlen(Final));
  	strcpy(Disparo, PegaUser);
 	strcat(Disparo, Local); 
 	strcat(Disparo, Usuario); 
  	strcat(Disparo, Final); 
  	Arquivo = fopen(Disparo,"r"); 
	//////////////////////////////////////////////////////////////////////////////  
	
		
	//Verifica uma linha especifica do arquivo cujo e o nivel de acesso
	int Finall, Loop, Linha = 3;
    char str[512];
    for(Finall = Loop = 0;Loop<Linha;++Loop){
        if(0==fgets(str, sizeof(str), Arquivo)){
            Finall = 1;
            break;
        }
    }
	//////////////////////////////////////////////////////////////////////////////  
		
		
		
	//Redireciona para o respectivo menu de acordo com seu nivel	
	if (Sair == 1){
	if (strcmp(str,"Nivel de Acesso: 2")==0){
			system("cls");
			PainelAdministrativo();	
	}else if(strcmp(str,"Nivel de Acesso: 1")==0){
			system("cls");
			PainelFuncionario();
	}
	//////////////////////////////////////////////////////////////////////////////  

		
	}else if (Sair >1){
	printf("Digite uma Opcao valida!\n");
	sleep(1);
	system("cls");
	Cardapio();
	}
    if(Arquivo){fclose(Arquivo);}			
}//Tela de Relatorio


void PedidoEstoque(){
	fclose(fopen("Temporario.txt", "w"));//Limpa o arquivo temporario para a nova entrada de Dados
	char Item[Letras];
	int QuantidadeP,QuantidadeI;
	printf("Pedido de Estoque\n---------------------------------------------------------------------------------------------\n");
	printf("Quantidade de Produtos Necessarios\n- ");
	while(scanf("%d",&QuantidadeI) != 1|| QuantidadeI <=0)
    	{
        printf("Digite um valor Valido!\n");
	    while(getchar() != '\n');
	    sleep(1);
	    system("cls");
	    PedidoEstoque();
		}
	for(i=1;i<QuantidadeI;i++){	
	system("cls");
	printf("Pedido de Estoque\n---------------------------------------------------------------------------------------------\n");
	printf("%d - Nome do Produto\n- ",i);
	scanf(" %[^\n]s",&Item);
	printf("%d - Especifique sua Quantidade em Litros, Unidade, Gramas ou Kilos\n- ",i);
	scanf(" %[^\n]s",&QuantidadeP);
	
	Temporario = fopen("Temporario.txt","a");
//	fprintf(Temporario,"Pedido de Estoque | Pedido Realizado em Data : %d/%d/%d | Hora : %d:%d:%d\n- Produtos Pedidos e Suas Respectivas Quantidades\n",DataEHora->tm_mday,DataEHora->tm_mon+1,DataEHora->tm_year+1900,DataEHora->tm_hour,DataEHora->tm_min,DataEHora->tm_sec);
	fprintf(Arquivo,"Banana");
	system("cls");
	printf("Pedido de Estoque\n---------------------------------------------------------------------------------------------\n");
	}

}//Pedido Estoque

void CadastroFidelidade(){
	int Retorno;
	printf("Cadastro Fidelidade\n---------------------------------------------------------------------------------------------\n");
	printf("O Cadastro fidelidade Oferece ao Cliente 2 Pizzas mensalmente no Valor de R$ 50!\n");
	printf("Para Prosseguir com o cadastro Digite 1, Para Retornar ao Menu digite 2\n- ");
	while(scanf("%d",&Retorno) != 1|| Retorno <=0|| Retorno >2)
    	{
        printf("Digite uma Opcaa Valida!\n");
	    while(getchar() != '\n');
	    sleep(1);
	    system("cls");
	    CadastroFidelidade();
		}
	
	if(Retorno ==2){
	//Abre o arquivo do respectivo usuario logado para ver seu nivel de acesso	
	Local = "\\AppData\\Martiello\\Funcionarios\\Logins\\";
 	Disparo = (char *) malloc(1 + strlen(PegaUser)+ strlen(Local)+ strlen(Usuario)+ strlen(Final));
  	strcpy(Disparo, PegaUser);
 	strcat(Disparo, Local); 
 	strcat(Disparo, Usuario); 
  	strcat(Disparo, Final); 
  	Arquivo = fopen(Disparo,"r"); 
	////////////////////////////////////////////////////////////////////////////// 
	
	
	
	int Finall, Loop, Linha = 3;
    char str[512];
    for(Finall = Loop = 0;Loop<Linha;++Loop){
        if(0==fgets(str, sizeof(str), Arquivo)){
            Finall = 1;
            break;
        }
    }
	//////////////////////////////////////////////////////////////////////////////  
		
	
	//Redireciona para o respectivo menu de acordo com seu nivel	
	if (strcmp(str,"Nivel de Acesso: 2")==0){
			system("cls");
			PainelAdministrativo();	
	}else if(strcmp(str,"Nivel de Acesso: 1")==0){
			system("cls");
			PainelFuncionario();
	}
	//////////////////////////////////////////////////////////////////////////////  
    if(Arquivo){fclose(Arquivo);}	
	}
	
	
	printf("Nome Completo do Cliente\n* ");
	scanf(" %[^\n]s",&Dados.Nome);
	fflush(stdin);
	printf("Data Nascimento exemplo: 31/12/2019\n* ");
	scanf(" %[^\n]s",&Dados.Nascimento);
	fflush(stdin);
	printf("CPF\n* ");
	
	while(scanf("%lld",&Dados.CPF) != 1)
    {
        printf("Digite um Numero de CPF valido!\n");
	    while(getchar() != '\n');
	    sleep(1);
	    system("cls");
		printf("Cadastro Fidelidade\n---------------------------------------------------------------------------------------------\n");
		printf("O Cadastro fidelidade Oferece ao Cliente 2 Pizzas mensalmente no Valor de R$ 50!\n");
		printf("Para Prosseguir com o cadastro Digite 1, Para Retornar ao Menu digite 2\n- 1\n");
		printf("Nome Completo do Cliente\n* %s\n",Dados.Nome);
		printf("Data Nascimento exemplo: 31/12/2019\n* %s\n",Dados.Nascimento);
		printf("CPF\n* ");
	}
	char Tamanho = 1 + (int)log10(Dados.CPF);

	if (Tamanho > 11 || Tamanho < 11){
    printf("O numero de CPF digitado e Invalido!\n");
	sleep(1);
	system("cls");
	CadastroFidelidade();
	}
	fflush(stdin);
	printf("Endereco Ex: Rua das Palmeiras\n* ");
	scanf(" %[^\n]s",&Dados.Endereco);
	fflush(stdin);
	printf("Numero\n* ");
	scanf(" %[^\n]s",&Dados.Numero);
	fflush(stdin);
	printf("Complemento\n* ");
	scanf(" %[^\n]s",&Dados.Complemento);
	fflush(stdin);
	printf("Cidade\n* ");
	scanf(" %[^\n]s",&Dados.Cidade);
	fflush(stdin);
	printf("Estado exemplo: SP , RJ , SC. . .\n* ");
	scanf(" %[^\n]s",&Dados.Estado);
	fflush(stdin);
	system("cls");
	
	///////////////////////////////////////////////////////////////////////////
	printf("Confirmação dos Dados\n---------------------------------------------------------------------------------------------\n\n");
	printf("Nome: %s\nData de Nascimento: %s\nCPF: %lld\nEndereço: %s\nNumero: %s\nComplemento: %s\nCidade: %s\nEstado: %s\n\n",Dados.Nome,Dados.Nascimento,Dados.CPF,Dados.Endereco,Dados.Numero,Dados.Complemento,Dados.Cidade,Dados.Estado);
	printf("As Informacoes Digitadas estao corretas? S/N\n- ");
	scanf("%s",&Dados.SimNao);
	///////////////////////////////////////////////////////////////////////////
	
	
	while(1){
	if (strcmp(Dados.SimNao,"S")==0 || (strcmp(Dados.SimNao,"s")==0)){
	Local = "\\AppData\\Martiello\\Clientes Fidelidade.txt";
	Disparo = (char *) malloc(1 + strlen(PegaUser)+ strlen(Local) );
	strcpy(Disparo, PegaUser);
	strcat(Disparo, Local); 
	Arquivo = fopen(Disparo,"a");
	fprintf(Arquivo,"======================================\n\nNome do Cliente : %s\nData de Nascimento : %s\nCPF : %lld\nEndereco : %s\nNumero : %s\nComplemento : %s\nCidade : %s\nEstado : %s\n\n======================================\n\n",Dados.Nome,Dados.Nascimento,Dados.CPF,Dados.Endereco,Dados.Numero,Dados.Complemento,Dados.Cidade,Dados.Estado);
	printf("Cliente inserido no Plano Fidelidade com Exito!\n\n");
	fclose(Arquivo);
	
	int VoltaInsere = 0;
	printf("Deseja Inserir outro cliente ou Retornar ao Menu? [1]Retornar ao Menu | [2]Inserir outro Cliente no Plano\n- ");
	while(scanf("%d",&VoltaInsere) != 1|| VoltaInsere <=0 || VoltaInsere >2)
    {
    printf("Insira uma Opcao Valida!");
    sleep(1);
    system("cls");
    printf("Confirmação dos Dados\n---------------------------------------------------------------------------------------------\n\n");
	printf("Nome: %s\nData de Nascimento: %s\nCPF: %lld\nEndereço: %s\nNumero: %s\nComplemento: %s\nCidade: %s\nEstado: %s\n\n",Dados.Nome,Dados.Nascimento,Dados.CPF,Dados.Endereco,Dados.Numero,Dados.Complemento,Dados.Cidade,Dados.Estado);
	printf("As Informacoes Digitadas estao corretas? S/N \n* %s\n",Dados.SimNao);
	printf("\nDeseja Inserir outro cliente ou Retornar ao Menu? [1]Retornar ao Menu | [2]Inserir outro Cliente no Plano\n- ");
	}
	
	if(VoltaInsere == 1){
    memset(&Disparo, 0, sizeof (Disparo));
    memset(&Arquivo, 0, sizeof (Arquivo));
	//Abre o arquivo do respectivo usuario logado para ver seu nivel de acesso	
	Local = "\\AppData\\Martiello\\Funcionarios\\Logins\\";
 	Disparo = (char *) malloc(1 + strlen(PegaUser)+ strlen(Local)+ strlen(Usuario)+ strlen(Final));
  	strcpy(Disparo, PegaUser);
 	strcat(Disparo, Local); 
 	strcat(Disparo, Usuario); 
  	strcat(Disparo, Final); 
  	Arquivo = fopen(Disparo,"r"); 
	//////////////////////////////////////////////////////////////////////////////  
	
		
	//Verifica uma linha especifica do arquivo cujo e o nivel de acesso
	int Finall, Loop, Linha = 3;
    char str[512];
    for(Finall = Loop = 0;Loop<Linha;++Loop){
        if(0==fgets(str, sizeof(str), Arquivo)){
            Finall = 1;
            break;
        }
    }
	//////////////////////////////////////////////////////////////////////////////  
	//Redireciona para o respectivo menu de acordo com seu nivel	
	if (strcmp(str,"Nivel de Acesso: 2")==0){
			system("cls");
			PainelAdministrativo();	
			fclose(Arquivo);
	}else if(strcmp(str,"Nivel de Acesso: 1")==0){
			system("cls");
			PainelFuncionario();
			fclose(Arquivo);
	}
	//////////////////////////////////////////////////////////////////////////////  
	
	
	
	}else if(VoltaInsere == 2){
	system("cls");
	struct Ficha empty = {0};
	CadastroFidelidade();
	}
	
	
	
	
	break;
	}else if(strcmp(Dados.SimNao,"n")==0 || (strcmp(Dados.SimNao,"N")==0)){
	printf("Reiniciando Cadastro Fidelidade. . .");
	sleep(1);
	system("cls");
	CadastroFidelidade();
	break;
	}
	}
}//Cadastro Fidelidade

void ListarFidelidade(){
setlocale(LC_ALL, "Portuguese"); //Define o programa para aceitar acentuações em portugues
setlocale(LC_NUMERIC, "pt_BR"); //Define o programa para aceitar Virgulas no lugar do ponto
	
  Local = "\\AppData\\Martiello\\Clientes Fidelidade.txt";
  Disparo = (char *) malloc(1 + strlen(PegaUser)+ strlen(Local) );
  strcpy(Disparo, PegaUser);
  strcat(Disparo, Local); 
  Arquivo = fopen(Disparo,"r");
  
  	printf("Clientes Cadastrados no Plano\n---------------------------------------------------------------------------------------------\n");

    char Termino[Letras];
    while(Arquivo && fgets(Termino, sizeof(Termino), Arquivo))
    {
        if (strstr(Termino, "Nome do Cliente : "))
            printf("%s", Termino);
        else if (strstr(Termino, "======================================"))
            printf("%s", Termino);
        else if (strstr(Termino, "Data de Nascimento : "))
            printf("%s", Termino);
    	else if (strstr(Termino, "CPF : "))
            printf("%s", Termino);
        else if (strstr(Termino, "Endereco : "))
            printf("%s", Termino);
		else if (strstr(Termino, "Numero : "))
            printf("%s", Termino);
        else if (strstr(Termino, "Complemento : "))
            printf("%s", Termino);
        else if (strstr(Termino, "Cidade : "))
            printf("%s", Termino);
       else if (strstr(Termino, "Estado : "))
            printf("%s\n", Termino);    
	}
int Sair;
printf("\n\nPara retornar ao menu Digite 1\n- ");
while(scanf("%d",&Sair) != 1|| Sair >1||Sair <= 0)
    	{
        printf("Digite uma Opcao valida!\n");
	    while(getchar() != '\n');
	    sleep(1);
	    system("cls");
	    Cardapio();
		}		
	//Abre o arquivo do respectivo usuario logado para ver seu nivel de acesso	
	Local = "\\AppData\\Martiello\\Funcionarios\\Logins\\";
 	Disparo = (char *) malloc(1 + strlen(PegaUser)+ strlen(Local)+ strlen(Usuario)+ strlen(Final));
  	strcpy(Disparo, PegaUser);
 	strcat(Disparo, Local); 
 	strcat(Disparo, Usuario); 
  	strcat(Disparo, Final); 
  	Arquivo = fopen(Disparo,"r"); 
	//////////////////////////////////////////////////////////////////////////////  
	
		
	//Verifica uma linha especifica do arquivo cujo e o nivel de acesso
	int Finall, Loop, Linha = 3;
    char str[512];
    for(Finall = Loop = 0;Loop<Linha;++Loop){
        if(0==fgets(str, sizeof(str), Arquivo)){
            Finall = 1;
            break;
        }
    }
	//////////////////////////////////////////////////////////////////////////////  
		
	
	//Redireciona para o respectivo menu de acordo com seu nivel	
	if (Sair == 1){
	if (strcmp(str,"Nivel de Acesso: 2")==0){
			system("cls");
			PainelAdministrativo();	
	}else if(strcmp(str,"Nivel de Acesso: 1")==0){
			system("cls");
			PainelFuncionario();
	}
	}
	//////////////////////////////////////////////////////////////////////////////  
    if(Arquivo){fclose(Arquivo);}		
	
}//Listar Fidelidade


