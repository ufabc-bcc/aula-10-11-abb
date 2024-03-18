#include "bst.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    Element key;
    struct Node* left;
    struct Node* right;
} Node;

struct BST {
    Node* root;
};

Node* createNode(Element key) {
    Node* node = malloc(sizeof(Node));

    node->key = key;
    node->left = NULL;
    node->right = NULL;

    return node;
}

BST* bst_create() {
    BST* bst = malloc(sizeof(BST));

    bst->root = NULL;

    return bst;
}

void bst_destroyRecur(Node* node) {
    if (node == NULL) {
        return;
    }
    bst_destroyRecur(node->left);
    bst_destroyRecur(node->right);
    free(node);
}

void bst_destroy(BST* bst) {
    bst_destroyRecur(bst->root);
    free(bst);
}

/**
* Caso base 1: a árvore é vazia, cria um novo nó
* Caso base 2: a chave já exista, termine
* Caso recursivo 1: se a chave for menor que a chave da raiz atual, 
*                   recursão à esquerda
* Caso recursivo 2: se a chave for maior que a chave da raiz atual,
*                   recursão à direita
*/
Node* bst_insertRecur(Node* node, Element key) {
    if (node == NULL) {
        return createNode(key);
    }
    if (key < node->key) {
        node->left = bst_insertRecur(node->left, key);
    } else if (key > node->key) {
        node->right = bst_insertRecur(node->right, key);
    }

    return node;
}


void bst_insertIter(BST* bst, Element key) {
    if (bst->root == NULL) {
        bst->root = createNode(key);

        return;
    }

    Node* parent = NULL;
    Node* cur = bst->root;

    while (cur != NULL) {
        if (cur->key == key) {
            return;
        } else if (key < cur->key) {
            parent = cur;
            cur = cur->left;
        } else if (key > cur->key) {
            parent = cur;
            cur = cur->right;
        }
    }

    if (key < parent->key) {
        parent->left = createNode(key);
    } else if (key > parent->key){
        parent->right = createNode(key);
    }
}

void bst_insert(BST* bst, Element key) {
    bst->root = bst_insertRecur(bst->root, key);
}


bool bst_searchRecur(Node* node, Element key) {
    if (node == NULL) {
        return false;
    }
    if (node->key == key) {
        return true;
    }
    if (key < node->key) {
        return bst_searchRecur(node->left, key);
    } 
    
    return bst_searchRecur(node->right, key);
}

bool bst_search(BST* bst, Element key) {
    return bst_searchRecur(bst->root, key);
}

void bst_printInOrderRecur(Node* node) {
    if (node == NULL) {
        return;
    }
    bst_printInOrderRecur(node->right);
    element_print(node->key);
    printf(" ");
    bst_printInOrderRecur(node->left);
    
}

void bst_printInOrder(BST* bst) {
    bst_printInOrderRecur(bst->root);
    printf("\n");
}

void printPreOrderRecur(Node* node) {
    if (node == NULL) {
        return;
    }
    element_print(node->key);
    printf(" ");
    printPreOrderRecur(node->left);
    printPreOrderRecur(node->right);
}

void bst_printPreOrder(BST* bst) {
    printPreOrderRecur(bst->root);
    printf("\n");
}

void printPostOrderRecur(Node* node) {
    if (node == NULL) {
        return;
    }
    printPostOrderRecur(node->left);
    printPostOrderRecur(node->right);
    element_print(node->key);
    printf(" ");
}

void bst_printPostOrder(BST* bst) {
    printPostOrderRecur(bst->root);
    printf("\n");
}

void bst_printDiagram(Node* node, int level) {
  if (node == NULL) {
      return;
  }
  for (int i = 0; i < level; i++) {
    printf("  ");
  }
  element_print(node->key);
  printf("\n");
  bst_printDiagram(node->left, level + 1);  
  bst_printDiagram(node->right, level + 1);
}

void bst_print(BST* bst) {
  bst_printDiagram(bst->root, 0);
}