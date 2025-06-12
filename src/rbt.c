#include "../include/rbt.h"
#include <stdlib.h>
#include <stdio.h>

node *root = NULL;

node* create_node(time_t timestamp, long offset){
  node* new_node = malloc(sizeof(node));
  new_node->timestamp = timestamp;
  new_node->byte_offset = offset;
  new_node->parent = new_node->left = new_node->right = NULL;
  new_node->color = red;
  return new_node;
}

void rotateleft(node *n){
  node* y = n->right;
  n->right = y->left;
  if(y->left != NULL)y->left->parent = n;
  y->parent = n->parent;
  if(n->parent == NULL){
    root = y;
  }else if (n == n->parent->left) {
    n->parent->left = y;
  }else {
    n->parent->right = y;
  }
  y->left = n;
  n->parent = y;
}

void rotateright(node *n){
  node* y = n->left;
  n->left = y->right;
  if(y->right != NULL)y->right->parent = n;
  y->parent = n->parent;
  if(n->parent == NULL){
    root = y;
  }else if (n == n->parent->right) {
    n->parent->right = y;
  }else {
    n->parent->left = y;
  }
  y->right = n;
  n->parent = y;
}

void* insertfix(node* n){
  node* p = NULL;
  node* g = NULL;
  node* u = NULL;
  while((n != root) && (n->parent->color == red)){
    p = n->parent;
    g = p->parent;
    if (p == g->left){
      u = g->right;
      if(u != NULL && u->color == red){
        g->color = red;
        p->color = black;
        u->color = black;
        n = g;
      }else {
        if(n == p->right){
          n = p;
          rotateleft(p);
        }
        p->color = black;
        g->color = red;
        rotateright(g);
      }
    }else {
      u = g->left;
      if(u != NULL && u->color == red){
        g->color = red;
        p->color = black;
        u->color = black;
        n = g;
      }else {
        if(n == p->left){
          n = p;
          rotateright(p);
        }
        p->color = black;
        g->color = red;
        rotateleft(g);
      }
    }
  }
  root->color = black;
  return;
}

void insert(time_t timestamp , long offset){
  node*new_node = create_node(timestamp , offset);
  node*x = root;
  node*y = NULL;
  while(x != NULL){
    y = x;
    if(timestamp < x->timestamp){
      x = x->left;
    }else {
      x = x->right;
    }
  }
  new_node->parent = y;
  if(y == NULL){
    root = new_node;
    root->color = black;
    return;
  }else if(timestamp < y->timestamp){
    y->left = new_node;
  }else {
    y->right = new_node;
  }
  insertfix(new_node);////
  return;
}

void free_call(){
  free_tree(root);
  root = NULL;
  return;
}

void free_tree(node*root){
  if(root != NULL){
    free_tree(root->left);
    free_tree(root->right);
    free(root);
  }
  return;
}
