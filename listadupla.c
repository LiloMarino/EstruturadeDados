#include "listadupla.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct StListaDupla
{
    Item info;
    int ID;
    struct StListaDupla *prox;
    struct StListaDupla *ant;
};

struct StInfoLista
{
    struct StListaDupla *inicio;
    struct StListaDupla *final;
    int capac;
    int length;
};

struct StIterator
{
    struct StListaDupla *curr;
    bool reverso;
};

typedef struct StListaDupla ListaDupla;
typedef struct StInfoLista ListaInfo;
typedef struct StIterator IteratorInfo;

Lista CreateLista(int capacidade)
{
    ListaInfo *lista = malloc(sizeof(ListaInfo));
    lista->inicio = NULL;
    lista->final = NULL;
    lista->capac = capacidade;
    lista->length = 0;
    if (capacidade < 0)
    {
        lista->capac = CAPAC_ILIMITADA;
    }
    return lista;
}

int lengthLst(Lista L)
{
    ListaInfo *lista = (ListaInfo *)L;
    return lista->length;
}

int maxLengthLst(Lista L)
{
    if (((ListaInfo *)L)->capac == CAPAC_ILIMITADA)
    {
        return -1;
    }
    else
    {
        return ((ListaInfo *)L)->capac;
    }
}

bool isEmptyLst(Lista L)
{
    return ((ListaInfo *)L)->length == 0;
}

bool isFullLst(Lista L)
{
    if (((ListaInfo *)L)->capac == CAPAC_ILIMITADA)
    {
        return false;
    }
    else
    {
        return ((ListaInfo *)L)->length == ((ListaInfo *)L)->capac;
    }
}

Posic insertLst(Lista L, Item info)
{
    // Verifica se a lista está cheia
    if (((ListaInfo *)L)->length >= ((ListaInfo *)L)->capac)
    {
        return NIL;
    }
    else
    {
        ListaDupla *aux;
        aux = malloc(sizeof(ListaDupla));
        aux->info = info;
        aux->prox = NULL;
        aux->ant = NULL;
        aux->ID = 0;

        // Verifica se a lista está vazia
        if (((ListaInfo *)L)->inicio == NULL)
        {
            ((ListaInfo *)L)->inicio = aux;
        }
        else
        {
            ListaDupla *p;
            p = ((ListaInfo *)L)->final;
            aux->ant = p;
            p->prox = aux;
            aux->ID = p->ID++;
        }
        ((ListaInfo *)L)->length++;
        ((ListaInfo *)L)->final = aux;
        return aux;
    }
}

Item popLst(Lista L)
{
    ListaInfo *lista = (ListaInfo *)L;
    // Verifica se a lista está vazia
    if (lista->inicio == NULL)
    {
        printf("Erro: Lista vazia\n");
        exit(1);
    }
    ListaDupla *aux = lista->inicio;
    lista->inicio = aux->prox;
    if (lista->inicio != NULL)
    {
        lista->inicio->ant = NULL; // Se houver um segundo elemento na lista, atualiza o ponteiro ant do mesmo para NULL
    }
    else
    {
        lista->final = NULL; // Caso contrário, a lista ficou vazia e o ponteiro final também deve ser atualizado para NULL
    }
    Item item = aux->info; 
    free(aux);            
    lista->length--;       
    return item;          
}

void removeLst(Lista L, Posic p)
{
    ListaDupla *rmv, *aux;
    rmv = (ListaDupla *)p;

    // Verifica se é o primeiro elemento da lista
    if (rmv->ID == 0)
    {
        if (rmv->prox != NULL)
        {
            ((ListaInfo *)L)->inicio = rmv->prox;
            rmv->prox->ant = rmv->ant;
            aux = rmv->prox;
            aux->ID--;
        }
        else
        {
            ((ListaInfo *)L)->inicio = NULL;
        }
    }
    else if (rmv->prox != NULL)
    {
        rmv->prox->ant = rmv->ant;
        rmv->ant->prox = rmv->prox;
        aux = rmv->prox;
        aux->ID--;
    }

    // Se for o último elemento da lista
    if (rmv->ID + 1 == ((ListaInfo *)L)->length)
    {
        ((ListaInfo *)L)->final = rmv->ant;
    }
    ((ListaInfo *)L)->length--;
    free(rmv);

    // Ajeita o ID das próximas
    if (((ListaInfo *)L)->length != 0)
    {
        while (aux->prox != NULL)
        {
            aux = aux->prox;
            aux->ID--;
        }
    }
}

Item getLst(Posic p)
{
    ListaDupla *aux = (ListaDupla *)p;
    return aux->info;
}

Posic insertBefore(Lista L, Posic p, Item info)
{
    // Verifica se a lista está cheia
    if (((ListaInfo *)L)->length >= ((ListaInfo *)L)->capac)
    {
        return NIL;
    }
    else
    {
        // Insere um item na lista antes do item indicado por p
        ListaDupla *aux = (ListaDupla *)p;
        ListaDupla *new = malloc(sizeof(ListaDupla));
        new->info = info;
        new->prox = aux;
        aux->ant = new;
        new->ant = aux->ant;
        new->ID = aux->ID;
        if (new->ant != NULL)
        {
            new->ant->prox = new;
        }
        else
        {
            ((ListaInfo *)L)->inicio = new;
        }
        ((ListaInfo *)L)->length++;

        // Ajeita o ID das próximas
        aux->ID++;
        while (aux->prox != NULL)
        {
            aux = aux->prox;
            aux->ID++;
        }
        return new;
    }
}

Posic insertAfterLst(Lista L, Posic p, Item info)
{
    // Verifica se a lista está cheia
    if (((ListaInfo *)L)->length >= ((ListaInfo *)L)->capac)
    {
        return NIL;
    }
    else
    {
        // Insere um item na lista depois do item indicado por p
        ListaDupla *aux = (ListaDupla *)p;
        ListaDupla *new = malloc(sizeof(ListaDupla));
        new->info = info;
        new->ant = aux;
        aux->prox = new;
        new->prox = aux->prox;
        new->ID = aux->ID;
        if (new->prox != NULL)
        {
            new->prox->ant = new;
        }
        else
        {
            ((ListaInfo *)L)->final = new;
        }
        ((ListaInfo *)L)->length++;

        // Ajeita o ID das próximas
        aux->ID++;
        while (aux->prox != NULL)
        {
            aux = aux->prox;
            aux->ID++;
        }
        return new;
    }
}

Posic getFirstLst(Lista L)
{
    if (((ListaInfo *)L)->length == 0)
    {
        return NIL;
    }
    else
    {
        return ((ListaInfo *)L)->inicio;
    }
}

Posic getNextLst(Lista L, Posic p)
{
    if (((ListaInfo *)L)->final == p)
    {
        return NIL;
    }
    else
    {
        return ((ListaDupla *)p)->prox;
    }
}

Posic getLastLst(Lista L)
{
    if (((ListaInfo *)L)->length == 0)
    {
        return NIL;
    }
    else
    {
        return ((ListaInfo *)L)->final;
    }
}

Posic getPreviousLst(Lista L, Posic p)
{
    if (((ListaInfo *)L)->inicio == p)
    {
        return NIL;
    }
    else
    {
        return ((ListaDupla *)p)->ant;
    }
}

void PrintLista(Lista L)
{
    ListaDupla *p;
    printf("\n");
    printf("====== Lista ======\n");
    for (p = ((ListaInfo *)L)->inicio; p != NULL; p = p->prox)
        printf("%p ID: %d\n", p->info, p->ID);
    if (p != NULL)
    {
        printf("Inicio: %p ID: %d\n", ((ListaInfo *)L)->inicio->info, ((ListaInfo *)L)->inicio->ID);
        printf("Fim: %p ID: %d\n", ((ListaInfo *)L)->final->info, ((ListaInfo *)L)->final->ID);
    }
    printf("Tamanho: %d\n", ((ListaInfo *)L)->length);
    printf("\n");
}

void killLst(Lista L)
{
    ListaDupla *rmv, *p;
    rmv = ((ListaInfo *)L)->inicio;
    p = ((ListaInfo *)L)->inicio;
    while (p->prox != NULL)
    {
        p = p->prox;
        free(rmv);
        rmv = p;
    }
    if (rmv != NULL)
    {
        free(rmv);
    }
    ((ListaInfo *)L)->inicio = NULL;
    ((ListaInfo *)L)->final = NULL;
    ((ListaInfo *)L)->length = 0;
}

/*
 * Iterador
 */

Iterador createIterador(Lista L, bool reverso)
{
    IteratorInfo *it = malloc(sizeof(IteratorInfo));
    it->reverso = reverso;
    if (reverso)
    {
        it->curr = ((ListaInfo *)L)->final;
    }
    else
    {
        it->curr = ((ListaInfo *)L)->inicio;
    }
    return it;
}

bool isIteratorEmpty(Lista L, Iterador it)
{
    if (((IteratorInfo *)it)->reverso)
    {
        return (((IteratorInfo *)it)->curr == ((ListaDupla *)getFirstLst(L))->ant);
    }
    else
    {
        return (((IteratorInfo *)it)->curr == ((ListaDupla *)getLastLst(L))->prox);
    }
}

Item getIteratorNext(Lista L, Iterador it)
{
    IteratorInfo *itimpl = (IteratorInfo *)it;
    Item valor = itimpl->curr->info;
    if (itimpl->reverso)
    {
        itimpl->curr = (ListaDupla *)getPreviousLst(L, itimpl->curr);
    }
    else
    {
        itimpl->curr = (ListaDupla *)getNextLst(L, itimpl->curr);
    }
    return valor;
}

void killIterator(Lista L, Iterador it)
{
    free(it);
}

/*
 * High-order functions
 */

// A função "map" recebe uma lista "L" e um ponteiro para uma função "f" que será aplicada em cada elemento da lista.
// Ela retorna uma nova lista com os elementos transformados pela função "f".
Lista map(Lista L, Apply f)
{
    Lista novaLista = CreateLista(((ListaInfo *)L)->capac);
    Iterador it = createIterador(L, false);
    while (!isIteratorEmpty(L, it))
    {
        Item item = getIteratorNext(L, it);
        insertLst(novaLista, f(item));
    }
    return novaLista;
}

// A função "filter" é similar à função "map", porém seleciona apenas os elementos que satisfazem a condição imposta por "f".
// Ela recebe uma Lista "L" e um ponteiro para uma função "f" que retorna true ou false.
// A função retorna uma nova lista contendo apenas os itens que satisfazem a condição.
Lista filter(Lista L, Check f)
{
    Lista novaLista = CreateLista(((ListaInfo *)L)->capac);
    Iterador it = createIterador(L, false);
    while (!isIteratorEmpty(L, it))
    {
        Item item = getIteratorNext(L, it);
        if (f(item))
        {
            insertLst(novaLista, item);
        }
    }
    return novaLista;
}

// A função "fold" é usada para reduzir a lista L a um único valor, aplicando a função "f" sucessivamente em cada item da lista.
// Ela recebe uma lista "L", um ponteiro para uma função "f" e uma Clausura "c".
void fold(Lista L, ApplyClosure f, Clausura c)
{
    Iterador it = createIterador(L, false);
    while (!isIteratorEmpty(L, it))
    {
        Item item = getIteratorNext(L, it);
        f(item, c);
    }
}
