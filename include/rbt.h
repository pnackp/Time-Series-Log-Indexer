#ifndef RBT_H
#define RBT_H

#include <time.h>

typedef enum{RED,BLACK}Color;

typedef struct node{
  time_t timestamp;
  long byte_offset;
  struct node* left , *right , *parent;
  Color color;
}node;

extern node* root;

node* create_node(time_t timestamp, long offset);
void insert(time_t timestamp , long offset);
void free_tree(node* root);

#endif
