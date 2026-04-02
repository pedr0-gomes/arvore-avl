#include <limits.h>
#include <stdlib.h>
#include "avl.h"

/* Sentinela NIL */
struct NO NIL_NODE = {0, &NIL_NODE, &NIL_NODE, &NIL_NODE, 0};
ArvAVL NIL = &NIL_NODE;

/* Criar e Destruir */
ArvAVL *criar_ArvAVL(void)
{
    ArvAVL *raiz = malloc(sizeof(ArvAVL));
    if (raiz == NULL) return NULL;
    *raiz = NIL;
    return raiz;
}

static void destroi_rec(ArvAVL no)
{
    if (no == NIL) return;
    destroi_rec(no->esq);
    destroi_rec(no->dir);
    free(no);
}

void destroi_ArvAVL(ArvAVL *raiz)
{
    if (raiz == NULL) return;
    destroi_rec(*raiz);
    free(raiz);
}

/* Consulta */
int busca_ArvAVL(ArvAVL *raiz,int valor)
{
    if (raiz == NULL) return 0;
    ArvAVL p;
    p = *raiz;
    while (p != NIL)
    {
        if (p->val == valor) return 1;
        else if (p->val > valor) p = p->esq;
        else                     p = p->dir;
    }
    return 0;
}

static int conta_rec(ArvAVL no)
{
    if (no == NIL) return 0;
    int c1 = conta_rec(no->esq);
    int c2 = conta_rec(no->dir);
    return 1 + c1 + c2;
}

int contar_nos_ArvAVL(ArvAVL raiz)
{
    return conta_rec(raiz);
}

static int altura_rec(ArvAVL no)
{
    if (no == NIL)     return 0;
    int c1 = altura_rec(no->esq);
    int c2 = altura_rec(no->dir);
    if (c1 > c2)    return c1 + 1;
    else            return c2 + 1;
}

int altura_ArvAVL(ArvAVL raiz)
{
    return altura_rec(raiz);
}

static int max2(int a,int b)
{
    return (a > b) ? a : b;
}

static void atualiza_altura(ArvAVL no)
{
    if (no == NIL) return;
    no->alt = 1 + max2(no->esq->alt,no->dir->alt);
}

/* Rotações */
ArvAVL rotacao_esq(ArvAVL *raiz,ArvAVL x)
{
    ArvAVL y = x->dir;
    if (x == NIL || y == NIL) return x;

    x->dir = y->esq;
    if (y->esq != NIL)  y->esq->pai = x;

    y->pai = x->pai;
    if (x->pai == NIL)          *raiz = y;
    else if (x->pai->dir == x)  x->pai->dir = y;
    else                        x->pai->esq = y;    

    y->esq = x;
    x->pai = y;

    atualiza_altura(x);
    atualiza_altura(y);

    return y;
}
ArvAVL rotacao_dir(ArvAVL *raiz,ArvAVL x)
{
    ArvAVL  y = x->esq;
    if (x == NIL || y == NIL) return x;

    x->esq = y->dir;
    if (y->dir != NIL) y->dir->pai = x;

    y->pai = x->pai;
    if (x->pai == NIL)           *raiz = y;
    else if (x->pai->dir == x)   x->pai->dir = y;            
    else                         x->pai->esq = y;

    y->dir = x;
    x->pai = y;

    atualiza_altura(x);
    atualiza_altura(y);

    return y;
}

static int balanco(ArvAVL no)
{
    if (no == NIL) return 1;
    int d = no->esq->alt - no->dir->alt;
    return (d >= -1 && d <= 1);
}

/* Validação */
static int valida_avl_rec(ArvAVL no,ArvAVL pai,long long min,long long max)
{
    if (no == NULL) return INT_MIN;
    if (no == NIL) return 0;

    if (no->pai != pai) return INT_MIN;
    if (no->esq == NULL || no->dir == NULL) return INT_MIN;

    if ((long long)no->val <= min || (long long)no->val >= max) return INT_MIN;

    if (no->esq == no || no->dir == no) return INT_MIN;

    if (no->esq != NIL && no->esq->pai != no) return INT_MIN;
    if (no->dir != NIL && no->dir->pai != no) return INT_MIN;

    int h_esq = valida_avl_rec(no->esq,no,min,no->val);
    if (h_esq == INT_MIN) return INT_MIN;

    int h_dir = valida_avl_rec(no->dir,no,no->val,max);
    if (h_dir == INT_MIN) return INT_MIN;

    if (!balanco(no)) return INT_MIN;

    int h_real = 1 + max2(h_esq,h_dir);
    if (no->alt != h_real) return INT_MIN;

    return h_real;
}

int valida_ArvAVL(ArvAVL raiz)
{
    if (NIL == NULL) return 0;
    if (NIL != &NIL_NODE) return 0;

    if (NIL->esq != NIL || NIL->dir != NIL || NIL->pai != NIL) return 0;
    if (NIL->alt != 0) return 0;

    if (raiz == NULL) return 0;
    if (raiz == NIL) return 1;

    if (raiz->pai != NIL) return 0;

    return valida_avl_rec(raiz,NIL,LLONG_MIN,LLONG_MAX) != INT_MIN;
}