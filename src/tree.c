#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/tree.h"

typedef struct
{
    HuffmanNode **data;
    int size;
    int capacity;

} MinHeap;

HuffmanNode *create_node(
    unsigned char symbol,
    uint64_t frequency)
{
    HuffmanNode *node =
        (HuffmanNode *)malloc(sizeof(HuffmanNode));

    if (!node)
        return NULL;

    node->symbol = symbol;
    node->frequency = frequency;

    node->left = NULL;
    node->right = NULL;

    return node;
}

int is_leaf(HuffmanNode *node)
{
    if (!node)
        return 0;

    return node->left == NULL &&
           node->right == NULL;
}


void free_tree(HuffmanNode *root)
{
    if (!root)
        return;

    free_tree(root->left);
    free_tree(root->right);

    free(root);
}

static MinHeap *create_heap(int capacity)
{
    MinHeap *heap =
        (MinHeap *)malloc(sizeof(MinHeap));

    if (!heap)
        return NULL;

    heap->data =
        (HuffmanNode **)malloc(
            sizeof(HuffmanNode *) * capacity);

    if (!heap->data)
    {
        free(heap);
        return NULL;
    }

    heap->size = 0;
    heap->capacity = capacity;

    return heap;
}

static void free_heap(MinHeap *heap)
{
    if (!heap)
        return;

    free(heap->data);
    free(heap);
}

static void swap_nodes(
    HuffmanNode **a,
    HuffmanNode **b)
{
    HuffmanNode *tmp = *a;
    *a = *b;
    *b = tmp;
}

static void heapify_up(
    MinHeap *heap,
    int index)
{
    while (index > 0)
    {
        int parent =
            (index - 1) / 2;

        if (heap->data[parent]->frequency <=
            heap->data[index]->frequency)
        {
            break;
        }

        swap_nodes(
            &heap->data[parent],
            &heap->data[index]);

        index = parent;
    }
}

static void heapify_down(
    MinHeap *heap,
    int index)
{
    while (1)
    {
        int smallest = index;

        int left =
            2 * index + 1;

        int right =
            2 * index + 2;

        if (left < heap->size &&
            heap->data[left]->frequency <
            heap->data[smallest]->frequency)
        {
            smallest = left;
        }

        if (right < heap->size &&
            heap->data[right]->frequency <
            heap->data[smallest]->frequency)
        {
            smallest = right;
        }

        if (smallest == index)
            break;

        swap_nodes(
            &heap->data[index],
            &heap->data[smallest]);

        index = smallest;
    }
}

static void heap_insert(
    MinHeap *heap,
    HuffmanNode *node)
{
    heap->data[heap->size] = node;

    heapify_up(
        heap,
        heap->size);

    heap->size++;
}

static HuffmanNode *heap_extract_min(
    MinHeap *heap)
{
    if (heap->size == 0)
        return NULL;

    HuffmanNode *min =
        heap->data[0];

    heap->size--;

    heap->data[0] =
        heap->data[heap->size];

    heapify_down(heap, 0);

    return min;
}

HuffmanNode *build_huffman_tree(
    uint64_t frequencies[MAX_SYMBOLS])
{
    MinHeap *heap =
        create_heap(MAX_SYMBOLS);

    if (!heap)
        return NULL;

    for (int i = 0; i < MAX_SYMBOLS; i++)
    {
        if (frequencies[i] > 0)
        {
            heap_insert(
                heap,
                create_node(
                    (unsigned char)i,
                    frequencies[i]));
        }
    }

    if (heap->size == 0)
    {
        free_heap(heap);
        return NULL;
    }

    if (heap->size == 1)
    {
        HuffmanNode *only =
            heap_extract_min(heap);

        HuffmanNode *root =
            create_node(
                0,
                only->frequency);

        root->left = only;

        free_heap(heap);

        return root;
    }

    while (heap->size > 1)
    {
        HuffmanNode *left =
            heap_extract_min(heap);

        HuffmanNode *right =
            heap_extract_min(heap);

        HuffmanNode *parent =
            create_node(
                0,
                left->frequency +
                right->frequency);

        parent->left = left;
        parent->right = right;

        heap_insert(
            heap,
            parent);
    }

    HuffmanNode *root =
        heap_extract_min(heap);

    free_heap(heap);

    return root;
}


void generate_codes(
    HuffmanNode *root,
    HuffmanCode table[MAX_SYMBOLS],
    char *buffer,
    int depth)
{
    if (!root)
        return;
    if (is_leaf(root))
    {
        if (depth == 0)
        {
            buffer[0] = '0';
            buffer[1] = '\0';
        }
        else
        {
            buffer[depth] = '\0';
        }

        strcpy(
            table[root->symbol].code,
            buffer);

        return;
    }

    buffer[depth] = '0';

    generate_codes(
        root->left,
        table,
        buffer,
        depth + 1);

    buffer[depth] = '1';

    generate_codes(
        root->right,
        table,
        buffer,
        depth + 1);
}