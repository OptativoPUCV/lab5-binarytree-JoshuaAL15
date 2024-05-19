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
        return NULL;
    }

    map->root = NULL;
    map->size = 0;
    map->lower_than = lower_than ;

    return map;
}

void insertTreeMap(TreeMap *tree, void *key, void *value) {
    
}
TreeNode *minimum(TreeNode *x) {
    return NULL;
}



void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    
}
Pair* searchTreeMap(TreeMap* tree, void* key) {
    // Inicializar el puntero current como NULL
    tree->current = NULL;

    // Comenzar la búsqueda desde la raíz del árbol
    TreeNode* current = tree->root;

    // Recorrer el árbol hasta encontrar el nodo con la clave o llegar a una hoja
    while (current != NULL) {
        int cmp = tree->lower_than(key, current->pair->key);
        if (cmp == 0) {
            // Se encontró la clave, actualizar el puntero current y devolver el par asociado
            tree->current = current;
            return current->pair;
        } else if (cmp < 0) {
            // La clave buscada es menor que la clave actual, buscar en el subárbol izquierdo
            current = current->left;
        } else {
            // La clave buscada es mayor que la clave actual, buscar en el subárbol derecho
            current = current->right;
        }
    }

    // No se encontró la clave, no es necesario actualizar el puntero current
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
