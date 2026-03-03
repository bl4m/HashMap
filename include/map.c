#include <stdlib.h>
#include <string.h>
#include "map.h"


void setup_hashmap(HashMap *map){
    map->array = (Node**)calloc(map->size,sizeof(Node *));
    map->count = 0;
}

size_t Hash(size_t array_size,void*key,size_t key_size){
    unsigned char *bytes = key;
    size_t hash = 0;
    for (size_t i =0;i<key_size;i++){
        hash = hash * 31 + bytes[i];
    }
    return hash % array_size;
}

void add_array(Node **array,Node *node, size_t map_size){
    
    size_t hash = Hash(map_size,node->key,node->key_size);
    
    node->next = array[hash];
    array[hash] = node;
}

void resize_hashmap(HashMap *map){
    
    size_t new_size = map->size * 2;
    Node **array = (Node**)calloc(new_size,sizeof(Node *));
    
    
    for(size_t i=0;i<map->size;i++){
        Node *current = map->array[i];
        while (current){
            Node*next = current->next;
            add_array(array,current,new_size);
            current = next;
        }
    }
    free(map->array);
    map->array = array;
    map->size = new_size;
}

Node* get(HashMap*hash_map,void *key, size_t key_size) {
    size_t hash = Hash(hash_map->size,key, key_size);
    Node *current = hash_map->array[hash];

    while (current) {
        if (current->key_size == key_size &&
            memcmp(current->key, key, key_size) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int edit(HashMap*hash_map,void *key, size_t key_size, void *value, size_t value_size){
    size_t hash = Hash(hash_map->size,key, key_size);
    Node *current = hash_map->array[hash];

    while (current) {
        if (current->key_size == key_size &&
            memcmp(current->key, key, key_size) == 0) {
                
            free(current->value);
            
            current->value = malloc(value_size);
            memcpy(current->value,value,value_size);
            current->value_size = value_size;
            
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void add(HashMap*hash_map,void*key,size_t key_size,void*value, size_t value_size){
    
    if (edit(hash_map,key,key_size,value,value_size)){
        return;
    }
    if ((hash_map->count + 1) * 4 > hash_map->size * 3){
        resize_hashmap(hash_map);
    }
    Node *node = malloc(sizeof(Node));
    
    node->key = malloc(key_size);
    memcpy(node->key,key,key_size);
    node->key_size = key_size;
    
    node->value = malloc(value_size);
    memcpy(node->value,value,value_size);
    node->value_size = value_size;
    
    size_t hash = Hash(hash_map->size,node->key,node->key_size);
    
    node->next = hash_map->array[hash];
    hash_map->array[hash] = node;
    hash_map->count ++;
}

int del(HashMap *hash_map, void*key, size_t key_size){
    size_t hash = Hash(hash_map->size,key, key_size);
    Node *current = hash_map->array[hash];
    Node *prev = NULL;

    while (current) {
        if (current->key_size == key_size &&
            memcmp(current->key, key, key_size) == 0) {
                Node *next = current->next;
                free(current->key);
                free(current->value);
                free(current);
                if (prev){
                    prev->next = next;
                }
                else hash_map->array[hash] = next;
                hash_map->count --;
                
                return 1;
        }
        prev = current;
        current = current->next;
    }
    return 0;
}

void destroy(HashMap *hash_map){
    for (size_t i=0;i<hash_map->size;i++){
        Node *current = hash_map->array[i];
        while (current){
            Node *next = current->next;
            free(current->key);
            free(current->value);
            free(current);
            current = next;
        }
    }
    free(hash_map->array);
    hash_map->array = NULL;
    hash_map->size = 0;
    hash_map->count = 0;
}
