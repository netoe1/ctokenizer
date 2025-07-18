# 📦 Tokenizer - Biblioteca de Lista Encadeada de Tokens em C

Esta biblioteca fornece uma estrutura de lista encadeada simples para armazenar e manipular _tokens_ de texto em C. Ideal para parsing, análise de comandos, separação de argumentos, entre outros usos relacionados a manipulação de strings.

---

## 🛠️ Funcionalidades

- Tokenização de strings com delimitadores personalizados
- Sanitização automática dos tokens (remove espaços, tabs e `\n`)
- Inserção, remoção e busca por conteúdo ou índice
- Impressão e liberação completa da lista

---

## 📁 Estrutura da Lista

```c
struct Node {
    char *token;
    struct Node *next;
};
```

## 🔍 Funções Disponíveis

```c
void tokenize(struct Node **list, const char *text, const char *separator)
```

- Divide uma string com base em um delimitador e adiciona os tokens à lista.

```c
 void sanitizeToken(char *str)
```

- Remove espaços/tabs iniciais e finais, além de \n. Usada automaticamente na tokenização.

```c
void addToken(struct Node **head, const char *value)
```

- Adiciona um novo token ao final da lista.

```c
void removeTokenByContent(struct Node **head, const char *value)
```

- Remove o primeiro nó que contém o token igual ao valor especificado.

```c
void removeTokenByIndex(struct Node **head, int index)
```

- Remove o nó localizado no índice informado.

```c
int getTokenByIndex(struct Node *head, const char *value)
```

- Retorna o índice da primeira ocorrência do token. Retorna -1 se não encontrado.

```c
void printTokens(struct Node *head)
```

- Imprime todos os tokens da lista no formato (para visualização em terminal):

```
   bash@foo:$ token1 -> token2 -> ... -> NULL
```

```c
void freeList(struct Node *head)
```

- Libera toda a memória alocada pela lista.

# 🧼 Segurança e Robustez

- Todos os tokens são duplicados com strdup()

- Validações de ponteiros nulos e índices inválidos

- Tokens sanitizados automaticamente antes de serem adicionados

# 🧩 Sugestões de Uso

- Analisadores sintáticos simples

- Leitores de arquivos delimitados

- Interpretação de comandos linha por linha

- Pré-processamento de entrada do usuário

# 📄 Licença

- Este projeto está sob a licença GNU GPLv3 . Livre para uso e modificação.
