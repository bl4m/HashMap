#ifndef HASHMAP_H

#define HASHMAP_H
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    void *key;
    size_t key_size;
    
    void *value;
    size_t value_size;
    
    struct Node *next;
} Node;

typedef struct HashMap {
    size_t size;
    size_t count;
    Node **array;
} HashMap;

void setup_hashmap(HashMap *map);
size_t Hash(size_t array_size,void*key,size_t key_size);
void add_array(Node **array,Node *node, size_t map_size);
void resize_hashmap(HashMap *map);
Node* get(HashMap*hash_map,void *key, size_t key_size);
int edit(HashMap*hash_map,void *key, size_t key_size, void *value, size_t value_size);
void add(HashMap*hash_map,void*key,size_t key_size,void*value, size_t value_size);
int del(HashMap *hash_map, void*key, size_t key_size);
void destroy(HashMap *hash_map);

#endif
