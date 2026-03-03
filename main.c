#include <stdio.h>
#include <string.h>
#include "map.h"

int main()
{
    HashMap map1 = {64};
    setup_hashmap(&map1);
    
    HashMap map2 = {32};
    setup_hashmap(&map2);
    
    resize_hashmap(&map1);
    
    add(&map1,"255",3,"fruit",5);
    add(&map1,"256",3,"pineapple",9);
    add(&map2,"256",3,"banana",6);

    printf("map1: %zu\n",map1.count);
    printf("map2: %zu\n",map2.count);
    
    del(&map1,"255",3);
    
    printf("map1: %zu\n",map1.count);
    printf("map2: %zu\n",map2.count);
    
    Node *node = get(&map1,"256",3);
    if (node) printf("%s\n",(char*)node->value);
    else printf("node not found");
    
    node = get(&map2,"256",3);
    if (node) printf("%s\n",(char*)node->value);
    else printf("node not found");
    
    node = get(&map1,"255",3);
    if (node) printf("%s\n",(char*)node->value);
    else printf("node not found");
    
    destroy(&map1);
    destroy(&map2);
    
    
    return 0;
}
