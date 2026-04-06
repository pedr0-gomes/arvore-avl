# Árvore AVL

![Build](https://github.com/pedr0-gomes/arvore-avl/actions/workflows/build.yml/badge.svg)

Implementação de Árvore AVL em C com inserção e remoção balanceadas.

## Estrutura

| Arquivo | Descrição |
|---------|-----------|
| `avl.h` | Interface pública do TAD |
| `avl.c` | Implementação da árvore |
| `insercao.c` | Harness de testes — inserção |
| `remocao.c` | Harness de testes — remoção |
| `template.c` | Esqueleto para novos harnesses |
| `template_insercao.c` | Ponto de partida para implementar a inserção |
| `template_remocao.c` | Ponto de partida para implementar a remoção |

## Como compilar
```bash
make insercao.exe
.\insercao.exe

make remocao.exe
.\remocao.exe
```

## Licença

[MIT](LICENSE)