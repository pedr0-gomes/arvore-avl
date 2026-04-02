#ifndef AVL_H
#define AVL_H

/*
TAD - Árvore AVL 
Referência: Aula 22 - Estrutura de Informação
*/

struct NO
{
    int val;
    struct NO *esq;
    struct NO *dir;
    struct NO *pai;
    int alt;
};

typedef struct NO *ArvAVL;

/* Sentinela NIL - representa toda folha ausente */
extern struct NO NIL_NODE;
extern ArvAVL NIL;

/* Criar e Destruir */
ArvAVL *criar_ArvAVL(void);
void destroi_ArvAVL(ArvAVL *raiz);

/* Consulta */
int busca_ArvAVL(ArvAVL *raiz,int valor);
int contar_nos_ArvAVL(ArvAVL raiz);
int altura_ArvAVL(ArvAVL raiz);

/* Rotações */
ArvAVL rotacao_esq(ArvAVL *raiz,ArvAVL x);
ArvAVL rotacao_dir(ArvAVL *raiz,ArvAVL x);

/* Validação */
int valida_ArvAVL(ArvAVL raiz);


#endif