#include <stdlib.h>

#include "table.h"

typedef struct cell cell;

struct cell{
	KEY key;
	VALUE val;
	cell *next; // Pekare till annan cell vars nyckel har samma hash, i en
	//riktad lista
};

cell *cell_create(KEY key, VALUE val, cell *link){
	cell *c = malloc(sizeof(cell));
	c->key = key;
	c->val = val;
	c->next = link;  //Tar in adressen till cellen den hamnar före
	return c;
}

void cell_kill(cell **c, keyFreeFunc keyFree, valFreeFunc valFree){ // Dubbelpekare pekar på länken i föregående värde
//eller pekaren i arrayen (om cellen är först i listan)
	cell *tmp = (*c)->next;
	if (keyFree){
		keyFree((*c)->key);
	}
	else{
		free((*c)->key);
	}
	if (valFree){
		valFree((*c)->val);
	}
	else{
		free((*c)->val);
	}
	free(*c);
	*c = tmp;
}


struct table
{
	size_t cap;
    size_t size;
	cell **buckets;
	//Dubbelpekare till första elementet i en array med cell-pekare
	key_compare_func key_cmp;
	key_hash_func hash;
	keyFreeFunc keyFree;
	valFreeFunc valFree;
};

cell **table_find(table *t, KEY key){
	// Returnerar dubbelpekare för att enklare kunna användas med cell_kill
	int ix = (t->hash(key))%(t->cap);
	cell **c = &(t->buckets[ix]);
	while (*c != NULL){
		if (t->key_cmp(key, (*c)->key)){
			return c;
		}
		c = &((*c)->next);
	}
	return c;
}

table *table_empty(int capacity, key_compare_func cmp, key_hash_func hash,
                   keyFreeFunc keyFree, valFreeFunc valFree){
    table *t;

    t = malloc(sizeof *t);
	t->cap = capacity;
    t->size = 0;
	t->buckets = calloc(sizeof(cell*), capacity);
	//Allokerar och rensar minne åt cellpekar-arrayen,
	t->key_cmp = cmp;
	t->hash = hash;
	t->keyFree = keyFree;
	t->valFree = valFree;
    return t;
}


bool table_is_empty(table *t)
{
    return t->size == 0;
}


void table_insert(table *t, KEY key, VALUE val)
{
	int ix = (t->hash(key))%(t->cap);
    cell **d = table_find(t, key);
	if (*d != NULL){ // Om table_find hittat dublett, tas cellen bort
		cell_kill(d, t->keyFree, t->valFree);
		t->size -= 1;
		// Minskar t->size trots att det ökas igen.
		//Detta för att slippa göra en extra koll
	}
	cell *c = cell_create(key, val, t->buckets[ix]);
	//Lägger in det nya värdet först i rätt buckets lista
	t->buckets[ix] = c;
	t->size += 1;
}


VALUE table_lookup(table *t, KEY key)
{
    cell *c = *(table_find(t, key));
	if (c != NULL){ // Om nyckel hittas
		return c->val;
	}
    return NULL;
}


void table_remove(table *t, KEY key)
{
    cell **c = table_find(t, key);
	if (*c != NULL){ //Omm nyckel hittas ska ett par tas bort
		cell_kill(c, t->keyFree, t->valFree);
		t->size -= 1;
	}
}


void table_kill(table *t){
	cell *c;
    for (size_t i = 0; i < t->cap; i++){
		c = t->buckets[i];
		while (c != NULL){ //Om pekaren i arrayen är NULL är bucket tom
			cell *tmp = c;
			c = c->next;
			cell_kill(&tmp, t->keyFree, t->valFree);
		}
	}
	free(t->buckets);
    free(t);
}
