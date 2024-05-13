#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
    int size;
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}


TreeMap *createTreeMap(int (*lower_than)(void* key1, void* key2)) {
    TreeMap *map = (TreeMap *)malloc(sizeof(TreeMap));
    if (map == NULL) {
        // Error: No se pudo reservar memoria para el mapa
        return NULL;
    }

    map->root = NULL;
    map->size = 0;
    map->lower_than = lower_than ;

    return map;
}

void insertTreeMap(TreeMap *tree, void *key, void *value) {
    TreeNode *current = NULL;
    searchTreeMap(tree, key, &current); // Busca la clave en el árbol y actualiza el puntero 'current'

    if (current != NULL) {
        // La clave ya existe en el árbol, no hagas nada
        return;
    }

    // Crea un nuevo nodo para el nuevo dato
    TreeNode *new_node = (TreeNode *)malloc(sizeof(TreeNode));
    if (new_node == NULL) {
        // Error: No se pudo reservar memoria para el nuevo nodo
        return;
    }

    // Inicializa el nuevo nodo con el par (key, value)
    new_node->pair = (Pair *)malloc(sizeof(Pair));
    if (new_node->pair == NULL) {
        // Error: No se pudo reservar memoria para el par (key, value)
        free(new_node); // Libera la memoria del nuevo nodo antes de salir
        return;
    }
    new_node->pair->key = key;
    new_node->pair->value = value;
    new_node->left = NULL;
    new_node->right = NULL;

    // Inserta el nuevo nodo en el árbol
    if (tree->root == NULL) {
        // El árbol está vacío, el nuevo nodo se convierte en la raíz
        tree->root = new_node;
    } else {
        // Busca la posición correcta para insertar el nuevo nodo
        current = tree->root;
        TreeNode *parent = NULL;
        while (current != NULL) {
            parent = current;
            if (tree->lower_than(key, current->pair->key)) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        // Inserta el nuevo nodo como hijo del nodo encontrado
        if (tree->lower_than(key, parent->pair->key)) {
            parent->left = new_node;
        } else {
            parent->right = new_node;
        }
    }

    // Incrementa el tamaño del árbol
    tree->size++;

    // Actualiza el puntero 'current' para que apunte al nuevo nodo
    current = new_node;
}

TreeNode * minimum(TreeNode * x){

    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}



Pair *searchTreeMap(TreeMap *tree, void *key, TreeNode **current) {
    *current = tree->root;

    while (current != NULL) {
        int cmp = tree->lower_than(key, (*current)->pair->key);
        if (cmp == 0) {

            return (*current)->pair;
        } else if (cmp < 0) {

            *current =(*current)->left;
        } else {

            *current =(*current)->right;
        }
    }
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
