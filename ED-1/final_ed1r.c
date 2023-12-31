#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura de notícia
typedef struct NewsNode {
    int id;
    char title[100];
    char author[100];
    char text[1000];
    struct NewsNode* next;
    struct NewsNode* prev;
} NewsNode;

typedef struct NewsList {
    NewsNode* head;
    NewsNode* tail;
} NewsList;

typedef struct HistoryNode {
    NewsNode* newsNode;
    struct HistoryNode* next;
} HistoryNode;

typedef struct HistoryQueue {
    HistoryNode* head;
    HistoryNode* tail;
    int size;
} HistoryQueue;

// Função para criar um novo nó de notícia
NewsNode* createNewsNode(int id, const char* title, const char* author, const char* text) {
    NewsNode* node = (NewsNode*)malloc(sizeof(NewsNode));
    node->id = id;
    strcpy(node->title, title);
    strcpy(node->author, author);
    strcpy(node->text, text);
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void pushHistory(HistoryQueue* fila, NewsNode* newsNode) {
    HistoryNode* newNode = (HistoryNode*)malloc(sizeof(HistoryNode));
    newNode->newsNode = newsNode;
    newNode->next = NULL;

    if (fila->size == 5) {
        // Remove o nó mais antigo do histórico
        HistoryNode* temp = fila->head;
        fila->head = fila->head->next;
        free(temp);
    } else {
        fila->size++;
    }

    if (fila->head == NULL) {
        // Se a fila está vazia
        fila->head = newNode;
        fila->tail = newNode;
    } else {
        // Se a fila já contém elementos
        fila->tail->next = newNode;
        fila->tail = newNode;
    }
}


// Função para inserir uma nova notícia na lista
void insertNews(NewsList* list, int id, const char* title, const char* author, const char* text) {
    NewsNode* newNode = createNewsNode(id, title, author, text);

    if (list->head == NULL) {
        // Se a lista está vazia
        list->head = newNode;
        list->tail = newNode;
    } else {
        // Se a lista já contém elementos
        list->tail->next = newNode;
        newNode->prev = list->tail;
        list->tail = newNode;
    }
}

// Função para remover uma notícia da lista pelo ID
void removeNews(NewsList* list, int id, NewsNode* atual_navi, HistoryQueue* history) {
    NewsNode* current = list->head;
  
    while (current != NULL) {
        if (current->id == id) {
            if (current == list->head) {
                list->head = current->next;
                if (list->head != NULL) {
                    list->head->prev = NULL;
                }
            } else if (current == list->tail) {
                list->tail = current->prev;
                if (list->tail != NULL) {
                    list->tail->next = NULL;
                }
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }

            // Atualizar o ponteiro next e prev para NULL
            current->next = NULL;
            current->prev = NULL;

            // Adicionar a notícia removida ao histórico
            //pushHistory(history, current);

            return;
        }
        current = current->next;
    }
}

// Função para buscar uma notícia pelo ID
NewsNode* findNews(NewsList* list, int id, NewsNode** atual_navi, HistoryQueue* history) {
    NewsNode* current = list->head;
    while (current != NULL) {
        if (current->id == id) {
            *atual_navi = current;
            pushHistory(history, *atual_navi);
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void mostrarProximo(NewsList* list, NewsNode** atual_navi, HistoryQueue* history) {
    if (*atual_navi != NULL && (*atual_navi)->next != NULL) {
        *atual_navi = (*atual_navi)->next;
        printf("Próxima notícia:\n");
        printf("ID: %d\n", (*atual_navi)->id);
        printf("Título: %s\n", (*atual_navi)->title);
        printf("Autor: %s\n", (*atual_navi)->author);
        printf("Texto: %s\n", (*atual_navi)->text);
        pushHistory(history, *atual_navi);
    } else {
        printf("Não há mais notícias disponíveis.\n");
    }
}

void mostrarAnterior(NewsList* list, NewsNode** atual_navi, HistoryQueue* history) {
    if (*atual_navi != NULL && (*atual_navi)->prev != NULL) {
        *atual_navi = (*atual_navi)->prev;
        printf("Notícia anterior:\n");
        printf("ID: %d\n", (*atual_navi)->id);
        printf("Título: %s\n", (*atual_navi)->title);
        printf("Autor: %s\n", (*atual_navi)->author);
        printf("Texto: %s\n", (*atual_navi)->text);
        pushHistory(history, *atual_navi);
    } else {
        printf("Não há mais notícias disponíveis.\n");
    }
}

void ir_para_ultimo(NewsList* list, NewsNode** atual_navi, HistoryQueue* history) {
    if (list->tail != NULL) {
        *atual_navi = list->tail;
        printf("Última notícia:\n");
        printf("ID: %d\n", (*atual_navi)->id);
        printf("Título: %s\n", (*atual_navi)->title);
        printf("Autor: %s\n", (*atual_navi)->author);
        printf("Texto: %s\n", (*atual_navi)->text);
        pushHistory(history, *atual_navi);
    } else {
        printf("A lista de notícias está vazia.\n");
    }
}

void historico(HistoryQueue* history) {
    printf("Histórico das últimas notícias acessadas:\n");
    
    HistoryNode* current = history->head;
    while (current != NULL) {
        printf("ID: %d\n", current->newsNode->id);
        printf("Título: %s\n", current->newsNode->title);
        printf("Autor: %s\n", current->newsNode->author);
        printf("Texto: %s\n", current->newsNode->text);
        printf("\n");
        current = current->next;
    }
}

void todas_noti(NewsList* list) {
    NewsNode* current = list->head;
    while (current != NULL) {
        printf("ID: %d\n", current->id);
        printf("Título: %s\n", current->title);
        printf("Autor: %s\n", current->author);
        printf("Texto: %s\n", current->text);
        printf("\n");
        current = current->next;
    }
}

int main() {
    // Inicialização das estruturas de dados
    NewsList newsList;
    newsList.head = NULL;
    newsList.tail = NULL;

    HistoryQueue history;
    history.head = NULL;
    history.tail = NULL;
    history.size = 0;

    NewsNode* atual_navi = NULL;
    NewsNode Nnode;

    int j = 7;

    // Inserção das 6 notícias iniciais
    insertNews(&newsList, 1, "News 1", "Author 1", "Text 1");
    insertNews(&newsList, 2, "News 2", "Author 2", "Text 2");
    insertNews(&newsList, 3, "News 3", "Author 3", "Text 3");
    insertNews(&newsList, 4, "News 4", "Author 4", "Text 4");
    insertNews(&newsList, 5, "News 5", "Author 5", "Text 5");
    insertNews(&newsList, 6, "News 6", "Author 6", "Text 6");

    int option;
    do {
        printf("Choose an option:\n");
        printf("1. Inserir notícia (ok)\n");
        printf("2. Remover notícia (ok)\n");
        printf("3. Buscar notícia (ok)\n");
        printf("4. Listar todas (ok)\n");
        printf("5. Ir para o último (ok)\n");
        printf("6. Mostrar a próxima (ok)\n");
        printf("7. Mostrar anterior (ok)\n");
        printf("8. Histórico\n");
        printf("0. Sair\n");
        printf("|-> ");
        scanf("%d", &option);
        printf("\n");

        switch (option) {
            case 6:
                mostrarProximo(&newsList, &atual_navi, &history);
                break;
            case 7:
                mostrarAnterior(&newsList, &atual_navi, &history);
                break;
            case 5:
                ir_para_ultimo(&newsList, &atual_navi, &history);
                break;
            case 4:
                todas_noti(&newsList);
                break;
            case 8:
                historico(&history);
                break;
            case 1: {
                int id;
                for (int i = j; i <= 50; i++) {
                    id = i;
                    j++;
                    break;
                }
                char title[100];
                char author[100];
                char text[1000];

                printf("Digite o título da notícia: ");
                getchar(); // Para consumir o caractere de nova linha
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = '\0'; // Remover o caractere de nova linha
                printf("Digite o autor da notícia: ");
                fgets(author, sizeof(author), stdin);
                author[strcspn(author, "\n")] = '\0'; // Remover o caractere de nova linha
                printf("Digite o texto da notícia: ");
                fgets(text, sizeof(text), stdin);
                text[strcspn(text, "\n")] = '\0'; // Remover o caractere de nova linha

                insertNews(&newsList, id, title, author, text);
                break;
            }
            case 2: {
                int id;
                printf("Digite o ID da notícia a ser removida: ");
                scanf("%d", &id);
                removeNews(&newsList, id, atual_navi, &history);
                break;
            }
            case 3: {
                int id;
                printf("Digite o ID da notícia a ser buscada: ");
                scanf("%d", &id);
                NewsNode* foundNews = findNews(&newsList, id, &atual_navi, &history);
                if (foundNews != NULL) {
                    printf("Notícia encontrada:\n");
                    printf("ID: %d\n", foundNews->id);
                    printf("Título: %s\n", foundNews->title);
                    printf("Autor: %s\n", foundNews->author);
                    printf("Texto: %s\n", foundNews->text);
                } else {
                    printf("Notícia não encontrada.\n");
                }
                break;
            }
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }

        printf("\n");
    } while (option != 0);

    return 0;
}
