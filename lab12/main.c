#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HashMapNode {
    const char *key;
    int value;
}HMNode;

typedef struct HashMap {
    HMNode **table;
    size_t capacity;
    size_t elements;
    size_t (*hashFunc)(const char*, int);
}HMap;

size_t hash_func(const char *key, int cap){
    size_t index=0;
    for(int i=0; i<strlen(key); i++)
        index=index+(key[i]%26 + (i*(i+1))/2 )%cap;
    index=index%cap;
    return index;
}
HMap* init_map(size_t (*func)(const char*, int)){
    HMap *this=calloc(1, sizeof(HMap));
    this->elements=0;
    this->capacity=10;
    this->hashFunc=func;
    this->table=calloc(this->capacity, sizeof(HMNode*));
    return this;
}
HMNode* init_node(const char* key, int value){
    HMNode* this=calloc(1, sizeof(HMNode));
    this->key=key;
    this->value=value;
    return this;
}
double get_load(HMap* map){
    return (double)map->elements/(double)map->capacity;
}
void extend_capacity(HMap* map){
    map->capacity*=2;
}
size_t offset(size_t x){
    return x;
}
void insert_map(HMap *hmap, const char *key, int value) {
    size_t keyHash=hmap->hashFunc(key, hmap->capacity);
    size_t index=keyHash;
    HMNode *element=init_node(key, value);
    size_t x=1;
    if (get_load(hmap)>0.75)
        extend_capacity(hmap);
    while (!is_bucket_available(hmap->table[index])) {
        if(hmap->table[index] != NULL)
            if(!strcmp(hmap->table[index]->key, key)){
                fprintf(stdout, "Key \"%s\" already used! Replacing old value (%d) with new value (%d)\n", key, hmap->table[index]->value, value);
                hmap->table[index]=element;
                return;
            }
        index=(keyHash + offset(x)) % hmap->capacity;
        x++;
    }
    hmap->elements++;
    hmap->table[index]=element;
}
HMNode* get_removed(){
    HMNode* this=init_node("thiswasused", 1);
    return this;
}
int is_bucket_available(HMNode* element){
    if(element==NULL)
        return 1;
    if(element==get_removed())
        return 1;
    return 0;
}
int get_value(HMap *hmap, const char *key){
    size_t keyHash=hmap->hashFunc(key, hmap->capacity);
    size_t index=keyHash;
    size_t x=1;
    while (hmap->table[index]!=NULL && index<hmap->capacity) {
        if(!strcmp(hmap->table[index]->key, key))
            break;
        index=(keyHash + offset(x))%hmap->capacity;
        x++;
    }
    if(index>=hmap->capacity){
        printf("Value not found!\n");
        return -1;
    }
    if(hmap->table[index]==NULL){
        printf("Value not found!\n");
        return -1;
    }
    return hmap->table[index]->value;
}
void remove_map(HMap *hmap, const char *key) {
    size_t keyHash=hmap->hashFunc(key, hmap->capacity);
    size_t index=keyHash;
    size_t x=1;
    while (hmap->table[index]!=NULL) {
        if (!strcmp(hmap->table[index]->key, key)) {
            hmap->table[index]=get_removed();
            hmap->elements--;
            return;
        }
        index=(keyHash+offset(x))%hmap->capacity;
        x++;
        if (x>=hmap->capacity) {
            fprintf(stdout, "Element with key \"%s\" doesn't exist!\n", key);
            return;
        }
    }
}
int contains_key(HMap *hmap, const char *key){
    size_t keyHash=hmap->hashFunc(key, hmap->capacity);
    size_t index=keyHash;
    size_t x=1;
    while (hmap->table[index]!=NULL && index<hmap->capacity) {
        if(!strcmp(hmap->table[index]->key, key))
            break;
        index=(keyHash+offset(x))%hmap->capacity;
        x++;
    }
    if(index>=hmap->capacity)
        return 0;
    if(hmap->table[index]==NULL)
        return 0;
    return 1;
}
int main(void){
    HMap* map=init_map(hash_func);
    const char matrix[5][100]={"intalnire", "mancare", "masa", "intalnire", "restaurant"};
    for(int i=0; i<5; i++){
        if(!contains_key(map, matrix[i]))
            insert_map(map, matrix[i], 1);
        else
            insert_map(map, matrix[i], get_value(map, matrix[i]) + 1);
    }
    remove_map(map, "intalnire");
    fprintf(stdout, "Sunt %ld cuvinte in dictionar!\n", map->elements);
    for(int i=0; i<map->capacity; i++)
        if(map->table[i]!=NULL)
            if(strcmp(map->table[i]->key, get_removed()->key))
                fprintf(stdout, "%s ==> %d\n", map->table[i]->key, map->table[i]->value);
        
}