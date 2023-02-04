#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 10 // Capacity of the Hash Table

typedef struct HashTable
{
   char *name;
   char *type;
   char *value;
}Hash;

Hash *hash[CAPACITY];

void init_hash_table();
void hash_insert(char *name, char *type, char *value);
Hash *hash_search(char *name);
int hash_function(char *name);
void hash_update(char *name, char *value);
void print_hash();
char *hash_get();

int main(int argc, char const *argv[])
{
    init_hash_table();

    hash_insert("b","char", "batata");

    print_hash(); 

    hash_insert("aa","inta","hahahah");

    print_hash(); 
    // Hash *buscado = hash_search("b");

    // printf("\t%s\t%s\t%s", buscado->name, buscado->type, buscado->value);


    printf("a => %u\n", hash_function("a"));
    printf("Sarah=> %u\n", hash_function("b"));
    printf("Antonio => %u\n", hash_function("Antonio"));
    printf("Gustavo => %u\n", hash_function("Gustavo"));


    return 0;
}


void init_hash_table(){
    int i;
    
    for(i = 0; i < CAPACITY; i++){
        hash[i] = NULL;
    }
    return;
    // tabela vazia
}

void print_hash(){
    int i;

    for(i = 0; i < CAPACITY; i++){
        if(hash[i] == NULL){
            printf("\t%i\t---\n", i);

        } else { 
            printf("\t%i\t%s\t%s\t%s\n", i, hash[i]->name ,hash[i]->type, hash[i]->value);
        }
    }
}


int hash_function(char *name){
    int i;

    int lenght = strnlen(name, 1000);
    unsigned int hash_value = 0;
    
    for(i = 0; i < lenght; i++){
        hash_value += name[i]; 
        hash_value = (hash_value * name[i]) % CAPACITY;      
    }

	return hash_value;
}

void hash_insert(char *name, char *type, char *value){
    int i;
    
    Hash *item = (Hash*) malloc(sizeof(Hash));;

    item->name = name;
    item->type = type;
    item->value = value;
    int index = hash_function(name);
    for(i = 0; i<CAPACITY; i++){

        int try = (i + index) % CAPACITY;
        printf("%d", i);
        if(hash[try] == NULL){
            hash[try] = item;
            
            return;
        }else{
            return;
        }
    
    }
}

Hash *hash_search(char *name)
{
    int i;
    int index = hash_function(name);
    
    for(i = 0; i<CAPACITY; i++){
        int try = (i + index) % CAPACITY;
        if(hash[try] != NULL && 
        strncmp(hash[try]->name, name, CAPACITY)== 0){
        return hash[try];
    }else{
        printf("return null");
    }
    }
}

void hash_update(char *name, char *value){
    int index = hash_function(name);
    Hash *object = hash_search(name);
    Hash item = {.name =object->name, .type=object->type, .value=value };
    
    for(int i = 0; i<CAPACITY; i++){
        int try = (i + index) % CAPACITY;
        if(strncmp(hash[try]->name, name, CAPACITY)){
            hash[try] = &item;
            return;
        }
    }
}


char *hash_get(char *name){
    return hash_search(name)->value;
}

