# arvore-avl
![Build](https://github.com/pedr0-gomes/arvore-avl/actions/workflows/build.yml/badge.svg)

> Implementação de inserção e remoção em Árvore AVL em C, com abordagem iterativa e ponteiro pai.

## Sobre o projeto

Referência teórica: [`docs/aula22-arvores-avl.pdf`](docs/aula22-arvores-avl.pdf)

Repositório desenvolvido na disciplina de Estruturas de Informação, com base na Aula 22 — Árvores AVL. O objetivo é implementar as operações de inserção e remoção em uma AVL Tree, usando uma abordagem iterativa com ponteiro pai em cada nó e um nó sentinela NIL global compartilhado.

## Estrutura do repositório

| Arquivo | Descrição |
|---------|-----------|
| `avl.h` | Interface pública do TAD |
| `avl.c` | Implementação da árvore |
| `insercao.c` | Harness de testes — inserção |
| `remocao.c` | Harness de testes — remoção |
| `template.c` | Esqueleto para novos harnesses |
| `template_insercao.c` | Ponto de partida para implementar a inserção |
| `template_remocao.c` | Ponto de partida para implementar a remoção |

## Como compilar e executar

**Ambiente:** Windows 11 + PowerShell + GCC via MinGW
```powershell
make insercao.exe
.\insercao.exe

make remocao.exe
.\remocao.exe
```

## Implementação

O TAD (`avl.h` / `avl.c`) define a estrutura do nó com os campos `val`, `esq`, `dir`, `pai` e `alt`, além do sentinela NIL estático que representa todas as folhas ausentes. As rotações (`rotacao_esq`, `rotacao_dir`) atualizam os ponteiros pai dos três nós envolvidos e são expostas no header para uso direto nos harnesses de inserção e remoção.

A inserção desce iterativamente até a posição correta, insere o novo nó vermelho e sobe pelo caminho via ponteiro pai aplicando rotações simples ou duplas conforme o desequilíbrio encontrado — esquerda-esquerda, esquerda-direita, direita-direita ou direita-esquerda.

A remoção localiza o nó, substitui pelo sucessor em ordem quando necessário, e sobe pelo caminho aplicando os casos simétricos de rebalanceamento com o mesmo mecanismo de rotações.

| Operação | Melhor caso | Caso médio | Pior caso |
|----------|-------------|------------|-----------|
| Inserção | O(log n)    | O(log n)   | O(log n)  |
| Remoção  | O(log n)    | O(log n)   | O(log n)  |
| Busca    | O(1)        | O(log n)   | O(log n)  |

## Aprendizados

- A diferença prática entre implementação recursiva e iterativa com ponteiro pai — o ponteiro pai torna explícito o caminho de subida que na recursão é implícito na pilha de chamadas
- Como o sentinela NIL elimina verificações de NULL e centraliza as invariantes da estrutura, simplificando todas as condições de borda nas rotações
- Fluxo completo de engenharia de software: branch → implementação → validação → PR → merge → limpeza

## Status

Concluído — inserção e remoção implementadas e validadas.