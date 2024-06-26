#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <stdbool.h>

#define MAX_CLIENTES 100
#define MAX_PRODUTOS 100
#define MAX_COMPRAS 100
#define MAX_CARACTER 50

typedef struct {
    int id;
    char nome[MAX_CARACTER];
    float preco;
    int quantidade;
} Produto;

typedef struct {
    int id;
    char nome[MAX_CARACTER];
} Cliente;

typedef struct {
    char nomecliente[MAX_CARACTER];
    char nomeproduto[MAX_COMPRAS][MAX_CARACTER];
    int quantidade[MAX_COMPRAS];
    int num_produtos;
    float preco[MAX_COMPRAS];
} Carrinho;

Cliente clientes[MAX_CLIENTES];
Produto produtos[MAX_PRODUTOS];
Carrinho carrinho;

int numClientes = 0;
int numProdutos = 0;
int numCompras = 0;

/*Fun��o respons�vel por fazer teste de erro
TESTE 1 - Testa se � composto somente de letras
TESTE 2- Testa se � composto somente de n�meros

Caso haja um erro ele retorna 1, caso contr�rio retorna 0*/
int tratamento(char analise[], int teste){
	int i;
	
	for(i = 0; analise[i] != '\0'; i++){
		
		if(teste == 1){
			if(isalpha(analise[i]) == 0){
				return 1;
			}
		}
		else{
			if(isdigit(analise[i]) == 0){
				return 1;
			}
		}
	}
	
	return 0;
}

// Modulo venda - cadastrar cliente
void cadastrarCliente() {
    char buffer[MAX_CARACTER];

    if (numClientes < MAX_CLIENTES) {
        printf("Digite o nome do cliente: ");
        scanf(" %49[^\n]s", buffer);

        strcpy(clientes[numClientes].nome, buffer);
        numClientes++;

        printf("Cliente cadastrado com sucesso!\n");
    } else {
        printf("Limite de clientes atingido.\n");
    }
}

// Modulo estoque - Adiciona uma quantidade ao estoque de um produto
void adicionar(Produto produtos[], int numProdutos) {
    char nomeP[MAX_CARACTER];
    int qtdP;
    int i;
    int j;

    printf("Digite o nome do produto: ");
    scanf("%s", nomeP);

    printf("Digite 1 para adicionar produto ou digite 2 para remover: ");
    scanf("%d", &j);
   
switch (j) {
        case 1:
    printf("Digite a quantidade do produto a ser adicionada: ");
    scanf("%d", &qtdP);
   
    if (qtdP <= 0) {
        printf("A quantidade escolhida deve ser positiva!\n");
        return;
    }

    for (i = 0; i < numProdutos; i++) {
        if (strcmp(produtos[i].nome, nomeP) == 0) {
            produtos[i].quantidade += qtdP;
            printf("Quantidade de %s atualizada para %d.\n", produtos[i].nome, produtos[i].quantidade);
            return;
        }
    }
    printf("Produto de nome %s n?o encontrado.\n", nomeP);
        break;
   
        case 2:
        printf("Digite a quantidade do produto a ser removida: ");
    scanf("%d", &qtdP);
   
    if (qtdP <= 0) {
        printf("A quantidade escolhida deve ser positiva!\n");
        return;
    }

    for (i = 0; i < numProdutos; i++) {
        if (strcmp(produtos[i].nome, nomeP) == 0) {
            produtos[i].quantidade -= qtdP;
            printf("Quantidade de %s atualizada para %d.\n", produtos[i].nome, produtos[i].quantidade);
            return;
        }
    }
    printf("Produto de nome %s n?o encontrado.\n", nomeP);
        break;
       
}
}

// Modulo estoque - Cadastra produto
void cadastrarProduto() {
    if (numProdutos < MAX_PRODUTOS) {
        Produto p;
        p.id = numProdutos + 1;
        printf("Digite o nome do produto: ");
        scanf(" %49[^\n]s", p.nome);
        printf("Digite o preco do produto: ");
        scanf("%f", &p.preco);
        printf("Digite a quantidade do produto: ");
        scanf("%d", &p.quantidade);
        produtos[numProdutos] = p;
        numProdutos++;
        printf("Produto cadastrado com sucesso!\n");
    } else {
        printf("Limite de produtos atingido.\n");
    }
}

// Modulo venda - realiza uma compra
void comprar() {
    char buffer[MAX_CARACTER], compara[MAX_CARACTER];
    int qtd_compras, quantidade, i, x, z;
    int achou = 0;

    if (numClientes == 0 || numProdutos == 0) {
        printf("N�o h� clientes ou produtos cadastrados.\n");
        return;
    }

    printf("Digite o nome cliente: ");
    scanf(" %49[^\n]s", buffer);

    for (i = 0; buffer[i] != '\0'; i++) {
        buffer[i] = tolower(buffer[i]);
    }

    for (i = 0; i < numClientes; i++) {
        strcpy(compara, clientes[i].nome);
        for (x = 0; compara[x] != '\0'; x++) {
            compara[x] = tolower(compara[x]);
        }
        if (strcmp(compara, buffer) == 0) {
            achou = 1;
            break;
        }
    }

    if (achou == 0) {
        printf("Cliente n�o encontrado.\n");
        return;
    }

    buffer[0] = toupper(buffer[0]);
    achou = 0;
    strcpy(carrinho.nomecliente, buffer);

    printf("Digite o n�mero de produtos que deseja comprar: ");
    scanf("%d", &qtd_compras);

    if (qtd_compras > MAX_COMPRAS) {
        printf("Limite de produtos por compra excedido.\n");
        return;
    }

    for (i = 0; i < qtd_compras; i++) {
        achou = 0;
        printf("Digite o nome do %d produto: ", i + 1);
        scanf(" %49[^\n]s", buffer);

        for (x = 0; buffer[x] != '\0'; x++) {
            buffer[x] = tolower(buffer[x]);
        }

        for (x = 0; x < numProdutos; x++) {
            strcpy(compara, produtos[x].nome);
            for (z = 0; compara[z] != '\0'; z++) {
                compara[z] = tolower(compara[z]);
            }

            if (strcmp(compara, buffer) == 0) {
                achou = 1;

                if (produtos[x].quantidade == 0) {
                    printf("N�o quantidade deste produto no estoque...\n");
                    break;
                }

                do {
                    printf("Quantidade de \'%s\' em estoque: %d;\n", produtos[x].nome, produtos[x].quantidade);
                    printf("Digite a quantidade do %d produto: ", i + 1);
                    scanf("%d", &quantidade);

                    system("cls");
                } while (!(quantidade > 0 && quantidade <= produtos[x].quantidade));

                produtos[x].quantidade -= quantidade;

                strcpy(carrinho.nomeproduto[numCompras], buffer);
                carrinho.quantidade[numCompras] = quantidade;
                carrinho.preco[numCompras] = produtos[x].preco;

                numCompras++;

                printf("Compra realizada com sucesso!!\n");
                break;
            }
        }

        if (!achou) {
            printf("Produto n�o encontrado.\n");
            return;
        }
    }

    carrinho.num_produtos = numCompras;
}

// Modulo venda - Lista todos os clientes
void listarClientes() {
    int i;
    printf("Lista de Clientes: \n");
    for (i = 0; i < numClientes; i++) {
        printf("ID: %d, Nome: %s\n", clientes[i].id, clientes[i].nome);
    }
}

// Modulo estoque - Lista todos os produtos
void listarProdutos() {
    int i;
    for (i = 0; i < numProdutos; i++) {
        printf("ID: %d, Nome: %s, Pre�o: %.2f, quantidade: %d\n", produtos[i].id, produtos[i].nome, produtos[i].preco, produtos[i].quantidade);
    }
}

// Modulo vendas - calcula e retorna o total do carrinho
float calcularTotalCarrinho() {
	int i;
    float total = 0.0;
    for (i = 0; i < carrinho.num_produtos; i++) {
        total += carrinho.preco[i] * carrinho.quantidade[i];
    }
    return total;
}

// Modulo vendas - lista todas as compras efetuadas
void listarCompras() {
    int j;
    printf("Nome cliente: %s\n", carrinho.nomecliente);
    for (j = 0; j < carrinho.num_produtos; j++) {
        printf("Produto: %s, Quantidade: %d, Pre�o: %.2f\n", carrinho.nomeproduto[j], carrinho.quantidade[j], carrinho.preco[j]);
    }
    float total = calcularTotalCarrinho();
    printf("Total do carrinho: %.2f\n", total);
}

// Modulo vendas/estoque - Permite a troca de usu�rios
int login() {
	char buffer[MAX_CARACTER];
    int senha_usuario;
    int cod_usuario;
	
	do{
		
	    printf("Informe o login: ");
	    scanf("%s", buffer);
	    
	    if(tratamento(buffer, 2)){
	    	system("cls");
	    	
	    	printf("ERRO!! Cont�m letras...\n");
	    	continue;
		}
		
		sscanf(buffer, "%d", &cod_usuario);
	    
		printf("Informe a senha: ");
	    scanf("%s", buffer);
	    
	    if(tratamento(buffer, 2)){
	    	system("cls");
	    	
	    	printf("ERRO!! Cont�m letras...\n");
	    	continue;
		}
		
		sscanf(buffer, "%d", &senha_usuario);
	    
	    
	}while(0);
    // Vendas
    if (cod_usuario == 2525 && senha_usuario == 1234) {
        return 1;
    }
    
    return 0;
}

// Modulo estoque - Fun��o para excluir um produto do estoque pelo nome
void delete_product(Produto produtos[], int *numProdutos, char nomeP[]) {
    bool produto_existe = false;
    int indice = -1;
    int i;

    // Verificar se o produto existe no estoque
    for (i = 0; i < *numProdutos; i++) {
        if (strcmp(produtos[i].nome, nomeP) == 0) {
            produto_existe = true;
            indice = i;
            break;
        }
    }

    if (!produto_existe) {
        printf("Produto de nome %s n�o encontrado no estoque.\n", nomeP);
        return;
    }

    // Remover o produto do estoque e ajustar a lista de produtos
    for (i = indice; i < *numProdutos - 1; i++) {
        produtos[i] = produtos[i + 1];
    }

    (*numProdutos)--;
    printf("Produto removido com sucesso!\n");
}

int main() {
    int opcao = -1;
    char nomeP[MAX_CARACTER], buffer[MAX_CARACTER];

    setlocale(LC_ALL, "Portuguese");

    do {
        if (login()) {
            do {
                printf("1. Cadastrar Cliente\n");
                printf("2. Cadastrar produto\n");
                printf("3. Adicionar/remover produto\n");
                printf("4. Deletar produto\n");
                printf("5. Realizar Venda\n");
                printf("6. Listar Carrinho\n");
                printf("7. Listar clientes\n");
                printf("8. Listar Produtos\n");
                printf("9. Sair\n");
                printf("Escolha uma op��o: ");
                scanf("%s", buffer);
                
                system("cls");
                
                if(tratamento(buffer, 2)){
                	printf("ERRO!! Cont�m letras...\n");
                	
                	continue;
				}
				
				sscanf(buffer, "%d", &opcao);

                switch (opcao) {
                    case 1:
                        cadastrarCliente();
                        break;
                    case 2:
                    	cadastrarProduto();
                    break;
                    case 3:
                    	adicionar(produtos, numProdutos);
                    break;
                    case 4:	
                    	printf("Digite o nome do produto a ser removido: ");
                        scanf(" %49[^\n]s", buffer);
                        
                        if(tratamento(buffer, 1)){
                        	printf("ERRO!! Possui n�meros...\n");
                        }
                        else{
                        	sscanf(buffer, " %49[^\n]s", nomeP);
                        	
                        	delete_product(produtos, &numProdutos, nomeP);
						}
                    break;
                    case 5:
                    	comprar();
                    break;
                    case 6:
                    	listarCompras();
                    break;
                    case 7:
                    	listarClientes();
                    break;
                    case 8:
                    	listarProdutos();
                    case 9:
                    break;
                    default:
                        printf("Op��o inv�lida, por favor tente novamente...\n");
                    break;
                }
            }while(opcao != 9);
    	}
    } while (1);
    
    return 0;
}


