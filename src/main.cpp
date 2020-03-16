
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<ctype.h>

#define MAPA_TAMANHO_X 20
#define MAPA_TAMANHO_Y 10

//DEFINE O MAPA DE 20 X 10 POSIÇÕES
char mapa[MAPA_TAMANHO_Y][MAPA_TAMANHO_X];

//DEFINE O FORMATO DO MAPA
char formatoMapa[300] = 
"####################\
# ## ####### # # ###\
# ##   #####  ## ###\
# #### ###### ##   #\
#                  #\
### # #### #####  ##\
### # ## # ###   ###\
### #    # ##### ###\
### ###### #########\
####################";

//OUTRAS VARIAVEIS
int atualizar;
int sair;
int jogadorPosX;
int jogadorPosY;
int jogadorPosXAnterior;
int jogadorPosYAnterior;
int saidaPosX;
int saidaPosY;
char teclaPressionada;
int fimDeJogo;
	
	
// MÉTODOS	
void restauraPosicaoAnteriorJogador()
{
	jogadorPosX = jogadorPosXAnterior;
	jogadorPosY = jogadorPosYAnterior;
}
	
void configuracaoInicial()
{
	//DEFININDO VARIAVEIS
	atualizar = 1;
	sair = 0;
    fimDeJogo = 0;
    teclaPressionada = 0;
	
	//DEFININDO A POSIÇÃO INICIAL DO JOGADOR
	jogadorPosX = 3;
	jogadorPosY = 8;
	
	jogadorPosXAnterior = jogadorPosX;
	jogadorPosYAnterior = jogadorPosY;
	
	//DEFININDO A POSIÇÃO DA SAIDA
	saidaPosX = 12;
	saidaPosY = 1;
		
	//CARREGANDO O MAPA NA MATRIZ (VOU PRECISAR DE 2 LAÇOS ENCADEADOS, UM VARRE A POSIÇÃO X E O OUTRO A POSIÇÃO Y DA MATRIZ)
	int totalBlocosLidos = 0;
	
	for(int countY = 0 ; countY < MAPA_TAMANHO_Y ; countY++ )
	{
		for(int countX = 0 ; countX < MAPA_TAMANHO_X ; countX++ )
		{
			//LEMBRE-SE QUE AS MATRIZES TRABALHAM NA ORDEM LINHA E COLUNA E, POR ISSO, HOUVE A NECESSIDADE DE INVERTER O X COM O Y.
			mapa[countY][countX] = formatoMapa[ totalBlocosLidos ];
			totalBlocosLidos++;
		}		
	}
	
	//ADICIONANDO JOGADOR NO MAPA
	mapa[jogadorPosY][jogadorPosX] = '%';
	
	//ADICIONANDO SAIDA NO MAPA
	mapa[saidaPosY][saidaPosX] = '$';
	
}

void atualizarLogica()
{
	int houveMovimento = 0;
	
	// VERIFICA SE A MOVIMENTAÇÃO DO USUÁRIO É VÁLIDA
	
	if(toupper(teclaPressionada) == 'A')
	{
		//SE O USUÁRIO MOVEU PARA ESQUERDA...
		jogadorPosX -= 1;
		houveMovimento = 1;
	}
	else if(toupper(teclaPressionada) == 'W')
	{
		//SE O USUÁRIO MOVEU PARA CIMA...
		jogadorPosY -= 1;
		houveMovimento = 1;
	}
	else if(toupper(teclaPressionada) == 'D')
	{
		//SE O USUÁRIO MOVEU PARA DIREITA...
		jogadorPosX += 1;
		houveMovimento = 1;
	}
	else if(toupper(teclaPressionada) == 'S')
	{
		//SE O USUÁRIO MOVEU PARA BAIXO...
		jogadorPosY += 1;
		houveMovimento = 1;
	}
		
	// VERIFICA SE A NOVA POSIÇÃO É VÁLIDA
	
	if(houveMovimento == 1)
	{
	
		if(mapa[jogadorPosY][jogadorPosX] == '#')
		{
			//SE A POSIÇÃO EM QUE O USUÁRIO SE MOVEU FOR UMA PAREDE, ENTÃO:		
			restauraPosicaoAnteriorJogador();
		}
		else if(mapa[jogadorPosY][jogadorPosX] == '$')
		{
			//SE A POSIÇÃO EM QUE O USUÁRIO SE MOVEL FOR A SAIDA, ENTÃO
			fimDeJogo = 1;
		}
		else
		{
			//CASO SEJA UMA POSIÇÃO VÁLIDA, ENTÃO:
			mapa[jogadorPosY][jogadorPosX] = '%';
			mapa[jogadorPosYAnterior][jogadorPosXAnterior] = ' ';
			
			//ATUALIZA A POSIÇÃO ANTERIOR DO JOGADOR
			jogadorPosXAnterior = jogadorPosX;
			jogadorPosYAnterior = jogadorPosY;
			
		}
	}
}

void atualizarTela()
{
	system("CLS"); //LIMPA A TELA
	
	printf("\n\t## LABIRINTO DO C ##\n\n");
	printf("\t# = PAREDE | % = VOCE | $ = SAIDA\n");
	printf("\tUSE (A - W - S - D) PARA SE MOVIMENTAR \n");
	printf("\tTECLE (ESC) PARA SAIR... \n\n\n");
	
	//MOSTRANDO O MAPA NA TELA (VOU PRECISAR DE 2 LAÇOS ENCADEADOS, UM VARRE A POSIÇÃO X E O OUTRO A POSIÇÃO Y DA MATRIZ)
	for(int countY = 0 ; countY < MAPA_TAMANHO_Y ; countY++ )
	{
		printf("\n\t"); //PULA UMA LINHA SEMPRE QUE INICIA-SE UMA NOVA LINHA DA MATRIZ
		
		for(int countX = 0 ; countX < MAPA_TAMANHO_X ; countX++ )
		{
			//LEMBRE-SE QUE AS MATRIZES TRABALHAM NA ORDEM LINHA E COLUNA E, POR ISSO, HOUVE A NECESSIDADE DE INVERTER O X COM O Y.
			printf( "%c", mapa[countY][countX] );
		}		
	}
}

int main()
{
	configuracaoInicial();
	
	do
	{
		if(atualizar == 1)
		{
			atualizarLogica();
			atualizarTela();
		}
		
		if(fimDeJogo == 0)
		{
			
			//LEITURA DOS COMANDOS DO TECLADO
			teclaPressionada = getch();
			
			switch( toupper(teclaPressionada) )
			{
				case 'A':
				
					atualizar = 1;
					
				break;
				
				case 'W':
				
					
					atualizar = 1;
					
				break;
				
				case 'D':
				
					atualizar = 1;
					
				break;
				
				case 'S':
				
					atualizar = 1;
					
				break;									
				
				case 27:
				
					atualizar = 1;
					int opcaoUsuario;
					printf("\n\n\tDESEJA REALMENTE SAIR? (S/N): ");
					opcaoUsuario = getch();
					
					if(opcaoUsuario == 83 || opcaoUsuario == 115)
					{
						//CASO TECLE SIM;
						sair = 1;
					}
					else if(opcaoUsuario == 78 || opcaoUsuario == 110)
					{
						//CASO TECLE NÃO;
					}
					else
					{
						printf("OPCAO INVALIDA!!!");
						getch();
					}
	
				break;
				
				default:
								
					atualizar = 0;
					
				break;
			}
		}
		else
		{
			printf("\n\n\tPARABENS! VOCE EH DEMAIS!!! ");
			getch();
			printf("\n\tQUER JOGAR NOVAMENTE? (S)  ");
			
			char opcaoUsuario = getch();
					
			if(opcaoUsuario == 83 || opcaoUsuario == 115)
			{
				//CASO TECLE SIM;
				configuracaoInicial();
			}
			else
			{
				sair = 1;
			}
		}
		
	} while(sair == 0);
	
	
	return 0;
}
