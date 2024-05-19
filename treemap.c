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
    
    searchTreeMap(tree, key);
    // Verificar si la clave ya existe en el árbol
    if (tree->current != NULL) {
        // La clave ya existe en el árbol, no hacer nada
        return;
    }

    // Crear un nuevo nodo para el nuevo dato
    TreeNode* new_node = createTreeNode(key, value);
    if (new_node == NULL) {
        
        return;
    }

    // Insertar el nuevo nodo en el árbol
    if (tree->root == NULL) {
        // El árbol está vacío, el nuevo nodo se convierte en la raíz
        tree->root = new_node;
    } else {
        TreeNode* current = tree->root;
        TreeNode* parent = NULL;
        while (current != NULL) {
            parent = current;
            if (tree->lower_than(key, current->pair->key)) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        // Insertar el nuevo nodo como hijo del nodo padre encontrado
        if (tree->lower_than(key, parent->pair->key)) {
            parent->left = new_node;
        } else {
            parent->right = new_node;
        }
        new_node->parent = parent;
    }
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
    // Caso 1: Nodo sin hijos
    if (node->left == NULL && node->right == NULL) {
        if (node->parent != NULL) {
            // El nodo tiene un padre, anulamos el puntero del padre que apuntaba al nodo
            if (node->parent->left == node) {
                node->parent->left = NULL;
            } else {
                node->parent->right = NULL;
            }
        } else {
            // El nodo es la raíz del árbol, simplemente lo marcamos como NULL
            tree->root = NULL;
        }
        free(node->pair->key);
        free(node->pair->value);
        free(node->pair);
        free(node);
    }
    // Caso 2: Nodo con un hijo
    else if (node->left == NULL || node->right == NULL) {
        TreeNode* child = (node->left != NULL) ? node->left : node->right;
        if (node->parent != NULL) {
            // El nodo tiene un padre, el padre pasa a ser padre del hijo del nodo
            if (node->parent->left == node) {
                node->parent->left = child;
            } else {
                node->parent->right = child;
            }
            child->parent = node->parent;
        } else {
            // El nodo es la raíz del árbol, el hijo pasa a ser la nueva raíz
            tree->root = child;
            child->parent = NULL;
        }
        free(node->pair->key);
        free(node->pair->value);
        free(node->pair);
        free(node);
    }
        
    else {
        TreeNode* successor = minimum(node->right);
        node->pair = successor->pair; 
        removeNode(tree, successor); 
    }
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;
    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);
}


Pair* searchTreeMap(TreeMap* tree, void* key) {
    // Reiniciar el puntero current
    tree->current = NULL;

    // Iniciar la búsqueda desde la raíz
    TreeNode* current = tree->root;

    // Realizar búsqueda en el árbol
    while (current != NULL) {
        // Comparar la clave del nodo actual con la clave buscada
        int cmp = tree->lower_than(key, current->pair->key);
        if (cmp == 0) {
            // Se encontró la clave buscada, actualizar el puntero current y retornar el par asociado
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

    // Si no se encuentra la clave, retornar NULL
    return NULL;
}


Pair * firstTreeMap(TreeMap * tree) {
    
    if (tree == NULL || tree->root == NULL) return NULL;

    
    TreeNode *current = tree->root;
    while (current->left != NULL) {
        current = current->left;
    }

    
    tree->current = current;

    return current->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
    
    if (tree == NULL || tree->current == NULL) return NULL;

    TreeNode *current = tree->current;

    
    if (current->right != NULL) {
        current = current->right;
        while (current->left != NULL) {
            current = current->left;
        }
        
        tree->current = current;
       
        return current->pair;
    }

    
    TreeNode *parent = current->parent;
    while (parent != NULL && current == parent->right) {
        current = parent;
        parent = parent->parent;
    }

    
    tree->current = parent;

    
    if (parent == NULL) return NULL;

    
    return parent->pair;
}
Pair* upperBound(TreeMap* tree, void* key) {
    // Inicializar el nodo auxiliar para el upper bound
    TreeNode* ub_node = NULL;

    // Realizar la búsqueda normal
    TreeNode* current = tree->root;
    while (current != NULL) {
        int cmp = tree->lower_than(key, current->pair->key);
        if (cmp == 0) {
            // Se encontró una clave igual, se retorna el par asociado
            return current->pair;
        } else if (cmp < 0) {
            // La clave buscada es menor que la clave actual, buscar en el subárbol izquierdo
            ub_node = current;
            current = current->left;
        } else {
            // La clave buscada es mayor que la clave actual, buscar en el subárbol derecho
            current = current->right;
        }
    }

    // Si no se encontró una clave igual, retornar el par del nodo ub_node (el upper bound)
    return (ub_node != NULL) ? ub_node->pair : NULL;
}




