#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

/*
Template para branch de REMOCAO.
- Cole sua insercao pronta em inserir_main_branch() para montar arvores de teste.
- Implemente remover_main_branch().
- Nao depende de inserir/remover no TAD.
*/

#define TEST_MIN_VAL -128
#define TEST_MAX_VAL 128
#define TEST_RANGE_SIZE (TEST_MAX_VAL - TEST_MIN_VAL + 1)

typedef struct {
    char tipo; /* 'I' ou 'R' */
    int valor;
} Operacao;

static int total_casos = 0;
static int casos_ok = 0;

static int max2(int a,int b)
{
    return (a > b) ? a : b;
}

static void atualiza_altura(ArvAVL no)
{
    if (no == NIL) return;
    no->alt = 1 + max2(no->esq->alt,no->dir->alt);
}

/* TODO: cole aqui sua insercao pronta da branch de insercao */
int insercao_ArvAVL(ArvAVL *raiz, int valor)
{
	if (raiz == NULL)    return 0;

    // criar nó aux 
    ArvAVL aux = malloc(sizeof(struct NO));
    if (aux == NULL) return 0;
    aux->val = valor;
	aux->alt = 1;
    aux->esq = NIL;
    aux->dir = NIL;
    aux->pai = NIL;
    
    // árvore vazia
    if (*raiz == NIL)
    {
        *raiz = aux;
        (*raiz)->pai = NIL;
        return 1;
    }

    // descida na arvore
    ArvAVL q1 = *raiz;
    ArvAVL q2 = NULL;
    while (q1 != NIL)
    {
        q2 = q1;
        if (valor < q1->val)        q1 = q1->esq;
        else if (valor > q1->val)   q1 = q1->dir;
        else
        {
            free(aux);
            return 0;
        }    
    }
    if (valor < q2->val)    q2->esq = aux;
    else                    q2->dir = aux;
    aux->pai = q2;

	// subida pelo caminho e ajustes
	ArvAVL x = q2;
	while (1)
	{
		if (x->esq->alt > x->dir->alt + 1)
		{
			ArvAVL y = x->esq;
			if (y->esq->alt > y->dir->alt)
			{
				x = rotacao_dir(raiz,x);
			}
			else
			{
				y = rotacao_esq(raiz,y);
				x = rotacao_dir(raiz,x);
			}
		}
		else if (x->dir->alt > x->esq->alt + 1)
		{
			ArvAVL y = x->dir;
			if (y->dir->alt > y->esq->alt)
			{
				x = rotacao_esq(raiz,x);
			}
			else
			{
				y = rotacao_dir(raiz,y);
				x = rotacao_esq(raiz,x);
			}
		}
		else
		{
			atualiza_altura(x);
		}
		if (x->pai == NIL) 	return 1;
		else 				x = x->pai;
	}

}
static int inserir_main_branch(ArvAVL *raiz, int valor)
{
    return insercao_ArvAVL(raiz,valor);
}

/* TODO: implemente aqui sua remocao */
int remocao_ArvAVL(ArvAVL *raiz,int valor)
{
    ArvAVL q;
    ArvAVL inicio_ajuste = NIL;

    if (raiz == NULL || *raiz == NIL) return 0;

    q = *raiz;
    while (q != NIL)
    {
        if (q->val == valor) break;
        if (valor < q->val) q = q->esq;
        else q = q->dir;
    }
    if (q == NIL) return 0;

    if (q->esq == NIL || q->dir == NIL)
    {
        ArvAVL filho = (q->esq != NIL) ? q->esq : q->dir;
        ArvAVL pai = q->pai;

        if (pai == NIL)
        {
            *raiz = filho;
            if (filho != NIL) filho->pai = NIL;
            inicio_ajuste = filho;
        }
        else
        {
            if (q == pai->esq) pai->esq = filho;
            else pai->dir = filho;
            if (filho != NIL) filho->pai = pai;
            inicio_ajuste = pai;
        }

        free(q);
    }
    else
    {
        ArvAVL s = q->dir;
        while (s->esq != NIL) s = s->esq;

        if (s->pai != q)
        {
            ArvAVL pai_antigo_s = s->pai;
            ArvAVL filho_s = s->dir;

            pai_antigo_s->esq = filho_s;
            if (filho_s != NIL) filho_s->pai = pai_antigo_s;

            s->dir = q->dir;
            s->dir->pai = s;

            inicio_ajuste = pai_antigo_s;
        }
        else
        {
            inicio_ajuste = s;
        }

        if (q->pai == NIL)
        {
            *raiz = s;
            s->pai = NIL;
        }
        else if (q == q->pai->esq)
        {
            q->pai->esq = s;
            s->pai = q->pai;
        }
        else
        {
            q->pai->dir = s;
            s->pai = q->pai;
        }

        s->esq = q->esq;
        s->esq->pai = s;

        atualiza_altura(s);
        free(q);
    }

    q = inicio_ajuste;
    while (q != NIL)
    {
        if (q->esq->alt > q->dir->alt + 1)
        {
            ArvAVL y = q->esq;
            if (y->esq->alt >= y->dir->alt)
            {
                q = rotacao_dir(raiz,q);
            }
            else
            {
                rotacao_esq(raiz,y);
                q = rotacao_dir(raiz,q);
            }
        }
        else if (q->dir->alt > q->esq->alt + 1)
        {
            ArvAVL y = q->dir;
            if (y->dir->alt >= y->esq->alt)
            {
                q = rotacao_esq(raiz,q);
            }
            else
            {
                rotacao_dir(raiz,y);
                q = rotacao_esq(raiz,q);
            }
        }
        else
        {
            atualiza_altura(q);
        }

        q = q->pai;
    }

    return 1;
}

static int remover_main_branch(ArvAVL *raiz, int valor)
{
    return remocao_ArvAVL(raiz,valor);
}

static int idx_valor(int valor)
{
    if (valor < TEST_MIN_VAL || valor > TEST_MAX_VAL) return -1;
    return valor - TEST_MIN_VAL;
}


static void imprimir_inorder_rec(ArvAVL no)
{
    if (no == NIL) return;
    imprimir_inorder_rec(no->esq);
    printf("%d ", no->val);
    imprimir_inorder_rec(no->dir);
}

static void imprimir_inorder(ArvAVL raiz)
{
    printf("in-order: ");
    if (raiz == NIL)
    {
        printf("<vazia>\n");
        return;
    }
    imprimir_inorder_rec(raiz);
    printf("\n");
}

static void aborta_falha(const char *caso,
                         int passo,
                         char op,
                         int valor,
                         ArvAVL *raiz,
                         int esperado,
                         int obtido,
                         const char *motivo)
{
    printf("\nFALHA\n");
    printf("caso   : %s\n", caso);
    printf("passo  : %d\n", passo);
    printf("op     : %c %d\n", op, valor);
    printf("motivo : %s\n", motivo);
    if (esperado != obtido)
    {
        printf("esperado: %d | obtido: %d\n", esperado, obtido);
    }
    if (raiz != NULL)
    {
        printf("nos    : %d\n", contar_nos_ArvAVL(*raiz));
        imprimir_inorder(*raiz);
    }
    exit(1);
}

static void check_estado(const char *caso,
                         int passo,
                         char op,
                         int valor,
                         ArvAVL *raiz,
                         const int *presentes,
                         int esperado_nos)
{
    int i;
    int real_nos;

    if (!valida_ArvAVL(*raiz))
    {
        aborta_falha(caso, passo, op, valor, raiz, 0, 0, "valida_ArvAVL retornou 0");
    }

    real_nos = contar_nos_ArvAVL(*raiz);
    if (real_nos != esperado_nos)
    {
        aborta_falha(caso,
                     passo,
                     op,
                     valor,
                     raiz,
                     esperado_nos,
                     real_nos,
                     "contagem de nos diferente do esperado");
    }

    for (i = 0; i < TEST_RANGE_SIZE; i++)
    {
        int v = TEST_MIN_VAL + i;
        int esperado = presentes[i];
        int obtido = busca_ArvAVL(raiz, v);
        if (!!esperado != !!obtido)
        {
            aborta_falha(caso,
                         passo,
                         op,
                         valor,
                         raiz,
                         esperado,
                         obtido,
                         "busca inconsistente com estado esperado");
        }
    }
}

static void executa_cenario(const char *nome, const Operacao *ops, int n_ops, int imprimir_final)
{
    ArvAVL *raiz = criar_ArvAVL();
    int presentes[TEST_RANGE_SIZE];
    int esperado_nos = 0;
    int i;

    total_casos++;
    memset(presentes, 0, sizeof(presentes));

    if (raiz == NULL)
    {
        aborta_falha(nome, -1, '-', 0, NULL, 0, 0, "falha ao criar arvore");
    }

    check_estado(nome, 0, '-', 0, raiz, presentes, esperado_nos);

    for (i = 0; i < n_ops; i++)
    {
        int id = idx_valor(ops[i].valor);
        int esperado_retorno;
        int retorno;

        if (id < 0)
        {
            aborta_falha(nome, i + 1, ops[i].tipo, ops[i].valor, raiz, 0, 0, "valor fora do dominio");
        }

        if (ops[i].tipo == 'I')
        {
            esperado_retorno = (presentes[id] == 0) ? 1 : 0;
            retorno = inserir_main_branch(raiz, ops[i].valor);
            if (retorno != esperado_retorno)
            {
                aborta_falha(nome,
                             i + 1,
                             ops[i].tipo,
                             ops[i].valor,
                             raiz,
                             esperado_retorno,
                             retorno,
                             "retorno inesperado de inserir_main_branch");
            }
            if (retorno == 1)
            {
                presentes[id] = 1;
                esperado_nos++;
            }
        }
        else if (ops[i].tipo == 'R')
        {
            esperado_retorno = (presentes[id] == 1) ? 1 : 0;
            retorno = remover_main_branch(raiz, ops[i].valor);
            if (retorno != esperado_retorno)
            {
                aborta_falha(nome,
                             i + 1,
                             ops[i].tipo,
                             ops[i].valor,
                             raiz,
                             esperado_retorno,
                             retorno,
                             "retorno inesperado de remover_main_branch");
            }
            if (retorno == 1)
            {
                presentes[id] = 0;
                esperado_nos--;
            }
        }
        else
        {
            aborta_falha(nome,
                         i + 1,
                         ops[i].tipo,
                         ops[i].valor,
                         raiz,
                         0,
                         0,
                         "operacao invalida no cenario");
        }

        check_estado(nome, i + 1, ops[i].tipo, ops[i].valor, raiz, presentes, esperado_nos);
    }

    if (imprimir_final)
    {
        printf("\nCASO: %s\n", nome);
        imprimir_inorder(*raiz);
    }

    destroi_ArvAVL(raiz);
    casos_ok++;
}

int main(void)
{
    static const Operacao c1[] = {
        {'I', 10}, {'I', 5}, {'I', 15}, {'I', 3}, {'I', 7}, {'I', 12}, {'I', 20},
        {'R', 3}
    };
    static const Operacao c2[] = {
        {'I', 10}, {'I', 5}, {'I', 15}, {'I', 12},
        {'R', 15}
    };
    static const Operacao c3[] = {
        {'I', 10}, {'I', 5}, {'I', 15}, {'I', 12}, {'I', 20},
        {'R', 15}
    };
    static const Operacao c4[] = {
        {'I', 10}, {'I', 5}, {'I', 15}, {'I', 2}, {'I', 7}, {'I', 12}, {'I', 20},
        {'R', 10}
    };
    static const Operacao c5[] = {
        {'I', 8}, {'I', 4}, {'I', 12},
        {'R', 100}
    };
    static const Operacao c6[] = {
        {'I', 8}, {'I', 4}, {'I', 12}, {'I', 2}, {'I', 6}, {'I', 10}, {'I', 14},
        {'R', 2}, {'R', 4}, {'R', 6}, {'R', 8}, {'R', 10}, {'R', 12}, {'R', 14}
    };

    printf("=== TEMPLATE REMOCAO ===\n");
    executa_cenario("remove-folha", c1, (int)(sizeof(c1) / sizeof(c1[0])), 1);
    executa_cenario("remove-um-filho", c2, (int)(sizeof(c2) / sizeof(c2[0])), 1);
    executa_cenario("remove-dois-filhos", c3, (int)(sizeof(c3) / sizeof(c3[0])), 1);
    executa_cenario("remove-raiz", c4, (int)(sizeof(c4) / sizeof(c4[0])), 1);
    executa_cenario("remove-inexistente", c5, (int)(sizeof(c5) / sizeof(c5[0])), 1);
    executa_cenario("remove-ate-esvaziar", c6, (int)(sizeof(c6) / sizeof(c6[0])), 1);

    printf("\nRESUMO: %d/%d casos passaram.\n", casos_ok, total_casos);
    return 0;
}
