#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PEDIDOS 100
#define MAX_CLIENTES 50

// ============================================
// SISTEMA DE LOGISTICA - UNIPAR EAD
// Aluno: Marciliano dos Santos Afonso
// RA: 09064532
// Disciplina: Programacao para Internet
// ============================================

typedef struct {
    int id;
    char cliente[50];
    char destino[50];
    float peso;
    float valorFrete;
    int status; // 0=Pendente 1=Em Transito 2=Entregue
    char data[20];
} Pedido;

typedef struct {
    int id;
    char nome[50];
    char cidade[30];
    char telefone[20];
} Cliente;

Pedido pedidos[MAX_PEDIDOS];
Cliente clientes[MAX_CLIENTES];
int totalPedidos = 0;
int totalClientes = 0;

void limparTela() {
    system("cls || clear");
}

void exibirBanner() {
    printf("==============================================\n");
    printf("   SISTEMA DE LOGISTICA INTELIGENTE v2.0    \n");
    printf("   UNIPAR - SISTEMAS DE INFORMACAO          \n");
    printf("==============================================\n\n");
}

float calcularFrete(float peso, float distancia) {
    float base = 25.0;
    float porKg = 2.5;
    float porKm = 0.85;
    float frete = base + (peso * porKg) + (distancia * porKm);
    if (peso > 50) frete *= 1.15;
    if (distancia > 500) frete *= 0.95;
    return frete;
}

void cadastrarCliente() {
    limparTela();
    exibirBanner();
    printf("--- CADASTRO DE CLIENTE ---\n");
    Cliente c;
    c.id = totalClientes + 1;
    printf("Nome: ");
    scanf(" %[^\n]", c.nome);
    printf("Cidade: ");
    scanf(" %[^\n]", c.cidade);
    printf("Telefone: ");
    scanf(" %[^\n]", c.telefone);
    clientes[totalClientes++] = c;
    printf("\n[OK] Cliente %s cadastrado com sucesso! ID: %d\n", c.nome, c.id);
    system("pause");
}

void cadastrarPedido() {
    limparTela();
    exibirBanner();
    printf("--- NOVO PEDIDO ---\n");
    Pedido p;
    p.id = totalPedidos + 1000;
    printf("Nome do cliente: ");
    scanf(" %[^\n]", p.cliente);
    printf("Destino: ");
    scanf(" %[^\n]", p.destino);
    printf("Peso (kg): ");
    scanf("%f", &p.peso);
    float distancia;
    printf("Distancia (km): ");
    scanf("%f", &distancia);
    p.valorFrete = calcularFrete(p.peso, distancia);
    p.status = 0;
    strcpy(p.data, "17/11/2026");// proximo programa verificar amanh
    pedidos[totalPedidos++] = p;
    printf("\n[OK] Pedido #%d criado! Frete: R$ %.2f\n", p.id, p.valorFrete);
    system("pause");
}

void listarPedidos() {
    limparTela();
    exibirBanner();
    printf("--- LISTA DE PEDIDOS (%d) ---\n\n", totalPedidos);
    if (totalPedidos == 0) {
        printf("Nenhum pedido cadastrado.\n");
    }
    for (int i = 0; i < totalPedidos; i++) {
        printf("ID: #%d | Cliente: %s\n", pedidos[i].id, pedidos[i].cliente);
        printf("Destino: %s | Peso: %.1f kg\n", pedidos[i].destino, pedidos[i].peso);
        printf("Frete: R$ %.2f | Status: ", pedidos[i].valorFrete);
        if (pedidos[i].status == 0) printf("PENDENTE\n");
        else if (pedidos[i].status == 1) printf("EM TRANSITO\n");
        else printf("ENTREGUE\n");
        printf("-------------------------------------\n");
    }
    system("pause");
}

void atualizarStatus() {
    int id, novo;
    printf("ID do pedido: ");
    scanf("%d", &id);
    printf("Novo status (0=Pendente 1=Transito 2=Entregue): ");
    scanf("%d", &novo);
    for (int i = 0; i < totalPedidos; i++) {
        if (pedidos[i].id == id) {
            pedidos[i].status = novo;
            printf("[OK] Status atualizado!\n");
            return;
        }
    }
    printf("[ERRO] Pedido nao encontrado!\n");
}

void relatorio() {
    float total = 0;
    int entregues = 0;
    for (int i = 0; i < totalPedidos; i++) {
        total += pedidos[i].valorFrete;
        if (pedidos[i].status == 2) entregues++;
    }
    printf("\n=== RELATORIO FINAL ===\n");
    printf("Total Pedidos: %d\n", totalPedidos);
    printf("Entregues: %d\n", entregues);
    printf("Faturamento Total: R$ %.2f\n", total);
    printf("Media por Pedido: R$ %.2f\n", totalPedidos > 0 ? total/totalPedidos : 0);
}

void salvarDados() {
    FILE *f = fopen("pedidos.txt", "w");
    for (int i = 0; i < totalPedidos; i++) {
        fprintf(f, "%d;%s;%s;%.2f;%d\n", pedidos[i].id, pedidos[i].cliente, pedidos[i].destino, pedidos[i].valorFrete, pedidos[i].status);
    }
    fclose(f);
    printf("[OK] Dados salvos em pedidos.txt\n");
}

int main() {
    int opcao;
    srand(time(NULL));
    do {
        limparTela();
        exibirBanner();
        printf("1 - Cadastrar Cliente\n");
        printf("2 - Cadastrar Pedido\n");
        printf("3 - Listar Pedidos\n");
        printf("4 - Atualizar Status\n");
        printf("5 - Relatorio\n");
        printf("6 - Salvar Dados\n");
        printf("0 - Sair\n");
        printf("\nEscolha: ");
        scanf("%d", &opcao);
        switch(opcao) {
            case 1: cadastrarCliente(); break;
            case 2: cadastrarPedido(); break;
            case 3: listarPedidos(); break;
            case 4: atualizarStatus(); break;
            case 5: relatorio(); system("pause"); break;
            case 6: salvarDados(); system("pause"); break;
            case 0: printf("Saindo... Ate mais!\n"); break;
            default: printf("Opcao invalida!\n"); system("pause"); break;
        }
    } while(opcao != 0);
    return 0;
}