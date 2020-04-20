#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"

/* global data */
int _totalReservations = 0;
int _activereReservations = 0;
reservationNode* _dbRoot = NULL;

/* local prototypes */
reservationNode* tree_new();
void tree_insert(reservationNode*, reservationInfo*);
void tree_transversal(reservationInfo* list[], int*, reservationNode*);
void tree_search(reservationNode*, char*, reservationInfo**);

/* routines */
void appendReservation(reservationInfo* newReservation) {
  if (_dbRoot == NULL) {
    _dbRoot = tree_new();
  }

  tree_insert(_dbRoot, newReservation);
  _totalReservations++;
  _activereReservations++;
}

void loadReservations(reservationInfo* reservations[]) {
  int scanIndex = 0;
  tree_transversal(reservations, &scanIndex, _dbRoot);
}

void findReservation(reservationInfo** reservation, char* plate, bool* reservationFound) {
  tree_search(_dbRoot, plate, reservation);
  *reservationFound = (*reservation != NULL);
}

int reservationsActiveCount() {
  return _activereReservations;
}

int reservationsCount() {
  return _totalReservations;
}

void releaseReservation() {
  _activereReservations--;
}

/* binary tree: administration */
void tree_insert(reservationNode* tree, reservationInfo* val) {
  // reserva de enderecos
  reservationInfo* ptrTreeVal = tree->val;
  reservationInfo* ptrLeafVal = val;

  // tratamento para o caso de raiz
  bool isRoot = false;
  if (tree->val == NULL) {
    tree->val = val;
    return;
  }
  
  // tratamento para o caso não seja a raiz
  if (strcmp(val->plate, tree->val->plate) < 0) {
    if (tree->left != NULL) {
      tree_insert(tree->left, val);
    }
    else {
      tree->left = tree_new();
      tree->left->val = val;
    }
  }
  else {
    if (tree->right != NULL) {
      tree_insert(tree->right, val);
    }
    else {
      tree->right = tree_new();
      tree->right->val = val;
    }
  }
}

reservationNode* tree_new() {
  reservationNode* node = (reservationNode*) malloc(sizeof(reservationNode));
  node->val = NULL;
  node->left = NULL;
  node->right = NULL;
  return node;
}

void tree_search(reservationNode* tree, char* plate, reservationInfo** found) {
  *found = NULL;
  if (tree != NULL) {
      if (strcmp(tree->val->plate, plate) == 0 && tree->val->checkOut == 0) {
        *found = tree->val;
        return;
      }
      
      tree_search(tree->left, plate, found);
      if (*found != NULL) { return; }
      
      tree_search(tree->right, plate, found);
      if (*found != NULL) { return; }
  }
}

void tree_transversal(reservationInfo* list[], int* reservationIndex, reservationNode* tree) {
  if (tree != NULL) {
      tree_transversal(list, reservationIndex, tree->left);
      list[(*reservationIndex)++] = tree->val;
      tree_transversal(list, reservationIndex, tree->right);
   }
}
