// list/list.c
// 
// Implementation for linked list.
//
// <Tashiana Johnson>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"



list_t *list_alloc() { 
  list_t* mylist =  (list_t *) malloc(sizeof(list_t)); 
  mylist->head = NULL;
}

void list_free(list_t *l){
  node_t *head, *node; 
  head = l->head;

  // Checks if the system is NULL to avoid double free
  if (l == NULL){return;}
  
  // Loops for node at head and frees the node
  while(head != NULL){
    node = head;
    head = head->next;
    node_free(node);
  }
  // Sets the head to NULL so the pointer isn't still pointing to the same address space
  l->head = NULL;
}

node_t *node_alloc(elem val){
  node_t *node = (node_t*) malloc(sizeof(node_t));
  node->value = val;
  node->next = NULL;
  return node;
}

void node_free(node_t *node){
  free(node);
}

void list_print(list_t *l){
node_t *node = l->head;

printf("\nList|");

// Checks for an empty list
if (node == NULL){
  printf("Empty!\n");
}

// Loops through list and print values while not at the end of list 
while (node != NULL){
  printf("%d ", node->value);
  node = node->next;
}

}    

char * listToString(list_t *l) {
  char* buf = (char *) malloc(sizeof(char) * 1024);
  char tbuf[20];

	node_t* curr = l->head;
  while (curr != NULL) {
    sprintf(tbuf, "%d->", curr->value);
    curr = curr->next;
    strcat(buf, tbuf);
  }
  strcat(buf, "NULL");
  return buf;
}

int list_length(list_t *l){
  node_t *node = l->head;
  int length = 0;

  // Loops through list and gets the node count
  while( node != NULL){
    node = node->next;
    length++;
  }

  return length;
}

void list_add_to_back(list_t *l, elem value){
  node_t *newNode, *head;
  newNode = node_alloc(value);
  head = l->head;

  // Checks for an empty list
  if(head == NULL){
    l->head = newNode;
    return;
  }

  // Loops to the end of the list where the next points to NULL
  while(head->next != NULL){
    head = head->next;
  }

  head->next = newNode;
}

void list_add_to_front(list_t *l, elem value){
  node_t *newNode, *head;
  newNode = node_alloc(value);
  head = l->head;

  // Checks for an empty list
  if(head == NULL){
  l->head = newNode;
  return;
  }

  // Sets the newNode to the head and points to the old head
  newNode->next = head;
  l->head = newNode;
}

void list_add_at_index(list_t *l, elem value, int index){
  node_t *newNode = node_alloc(value);
  node_t *prevNode = NULL;
  node_t *node = l->head;

  int length = list_length(l);
  int counter = 1;

  // Check for a negative index and returns
  if (index < 1 ){
      return;
    }

  // Checks when the index is the head and updates list
  if (index == 1){        
    newNode->next = node;
    l->head = newNode;
    return;
  }

  // Check for index within length of list
  if(index > length){
    return;
  }

  //Finds index within list
  while(counter < index){
    prevNode = node;
    node = node->next;
    counter++;
  }

  //Adds the newNode at index and points to the next node
  prevNode->next = newNode;
  newNode->next = node;
}

elem list_remove_from_back(list_t *l){
  node_t *node, *prevNode;
  elem removedElem;

  node = l->head;

  //Checks for an empty list
  if (list_length(l) == 0){
    return -1;
  } 

  // Checks if one elem list and frees the head
  if(node->next == NULL){
    removedElem = node->value;
    l->head = NULL;
    node_free(node);
    return removedElem;
  }

  // Loops to the end of the list
  while(node->next != NULL){
    prevNode = node;
    node = node->next;
  }

  removedElem = node->value;
  prevNode->next = NULL;
  node_free(node);

return removedElem;
}

elem list_remove_from_front(list_t *l){
  node_t *node, *nextNode;
  elem removedElem;

  node = l->head;
  nextNode = NULL;

  // Check for an empty list
  if (list_length(l) == 0){
    return -1;
  } 

  // Check for one elem list
  if (node->next == NULL){
    removedElem = node->value;
    l->head = NULL;
    node_free(node);
    return removedElem;
  }

  removedElem = node->value;
  nextNode = node->next;
  node_free(node);
  l->head = nextNode;

  return removedElem;
}

elem list_remove_at_index(list_t *l, int index) {
  int counter = 1;
  int length = list_length(l);
  elem removedElem;
  node_t *node = l->head;
  node_t *prevNode = NULL;


  // Check for invalid or negative index 
  if(index > length || index < 1) {
    return -1; 
  }

  // Removing the head node
  if (index == 1) {
    removedElem = node->value;
    l->head = node->next;
    node_free(node);
    return removedElem;
  }

  // Traverse the list to find the node at the given index and node is not empty 
  while (node != NULL && counter < index) {
      prevNode = node;
      node = node->next;
      counter++;
  }

  // Remove the node
  if (node != NULL) {
      removedElem = node->value;
      prevNode->next = node->next;
      node_free(node);
      return removedElem;
  }

  // If the node wasn't found, return an error value
  return -1; 
}



bool list_is_in(list_t *l, elem value){
node_t *node = l->head; 

  // Check for an empty list 
  if (l == NULL){
    return false;
  }

  // Loops through the list given the node is not empty and finds the value
  while(node != NULL){
    if(node->value == value){
      return true; 
    }
    node = node->next;
  }
  return false;
}

elem list_get_elem_at(list_t *l, int index){
  int length = 0;
  int counter = 1; 
  elem nValue = -1; 
  node_t *node;

  node = l->head;
  length = list_length(l);

  // Checks for out of bounds or empty lists
  if(index > length || length == 0){ 
    return -1;
  }

  // Checks if index is negative 
  if(index < 1){
    return -1;
  }

  // Retreive value at index of node while finding node at index
  while(index <= length){
    
    if(index == counter){
      nValue = node->value;      
      return nValue;
    }

    node = node->next;
    counter++;
  }

  return nValue; //returns -1: value not found
}

int list_get_index_of(list_t *l, elem value){
  int index, length;
  node_t *node;

  node = l->head; 
  length = list_length(l);
  index = 1;

  // Checks for an empty list
  if(length == 0){
    return -1;
  }

  // Loops through list to the end 
  while(node->next != NULL){

    if(node->value == value){
      return index;       //returns index when found
    }

    node = node->next;
    index++;   
  }

  if (node->next == NULL){
    printf("not found");
  }

return -1;        //returns -1: index not found
}