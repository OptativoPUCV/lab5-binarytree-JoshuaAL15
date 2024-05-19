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

void insertTreeMap(TreeMap* tree, void* key, void* value) {
    // Realizar una búsqueda para encontrar la posición de inserción
    searchTreeMap(tree, key);

    // Verificar si la clave ya existe en el árbol
    if (tree->current != NULL) {
        // La clave ya existe en el árbol, no hacer nada
        return;
    }

    // Crear un nuevo nodo para el nuevo dato
    TreeNode* new_node = createTreeNode(key, value);
    if (new_node == NULL) {
        // Manejo de error: No se pudo crear el nuevo nodo
        fprintf(stderr, "Error: No se pudo crear el nuevo nodo para la clave %p.\n", key);
        return;
    }

    // Insertar el nuevo nodo en el árbol
    if (tree->root == NULL) {
        // El árbol está vacío, el nuevo nodo se convierte en la raíz
        tree->root = new_node;
    } else {
        // Buscar la posición correcta para insertar el nuevo nodo
        TreeNode* current = tree->current;
        if (tree->lower_than(key, current->pair->key)) {
            current->left = new_node;
        } else {
            current->right = new_node;
        }
        new_node->parent = current;
    }

    // Actualizar el puntero current para que apunte al nuevo nodo
    tree->current = new_node;
}
TreeNode * minimum(TreeNode * x) {
    // Mientras haya un hijo izquierdo, seguimos avanzando
    while (x != NULL && x->left != NULL) {
        x = x->left;
    }
    // Devolvemos el nodo encontrado (puede ser NULL si x es NULL)
    return x;
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
