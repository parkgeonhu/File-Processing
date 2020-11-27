#include <iostream>
using namespace std;

class Node {
public:
  Node *left, *right;
  int key, bf;

  Node::Node(int key, int bf=0, Node *left=NULL, Node *right=NULL){
    this->key=key;
    this->left=left;
    this->right=right;
  }
};

// /**
// * updateBF updates balancing factors of nodes in T
// * and finds the unbalanced node nearest to y.
// * @param T: an AVL tree
// * @param y: the inserted/deleted node
// * @param x: the unbalanced node nearest to y
// * @param p: parent node of x
// */
void updateBF(Tree *T, Node *y, Node **x, Node **p) {
  /* write your code here */
}

// /**
// * rotateLL implements LL rotation in subtree rooted with x.
// * @param T: an AVL tree
// * @param x: root node of subtree
// * @param p: parent node of x
// */
void rotateLL(Tree *T, Node *x, Node *p) {
}

// /**
// * rotateRR implements RR rotation in subtree rooted with x.
// * @param T: an AVL tree
// * @param x: root node of subtree
// * @param p: parent node of x
// */
void rotateRR(Tree *T, Node *x, Node *p) {
  /* write your code here */
}

// /**
// * rotateLR implements LR rotation in subtree rooted with x.
// * @param T: an AVL tree
// * @param x: root node of subtree
// * @param p: parent node of x
// */
void rotateLR(Tree *T, Node *x, Node *p) {
}

// /**
// * rotateRL implements RL rotation in subtree rooted with x.
// * @param T: an AVL tree
// * @param x: root node of subtree
// * @param p: parent node of x
// */
void rotateRL(Tree *T, Node *x, Node *p) {
}
​
// /**
// * insertBST inserts newKey into T
// * and returns the inserted node.
// * @param T: a binary search tree
// * @param newKey: a key to insert
// * @return the inserted node
// */
Node *insertBST(Tree *T, int newKey) {
}
​
// /**
// * insertAVL inserts newKey into T.
// * @param T: an AVL tree
// * @param newKey: a key to insert
// */
void insertAVL(Tree *T, int newKey) {
  if(T==null){
    T = new Node(newKey);
    return;
  }
  Node * temp = T;
  Node * newNode = new Node(newKey);
  bool found = false;
  while(!found){
    if(newKey < )
  }
}
​
Node *deleteBST(Tree *T, int deleteKey) {
  /* write your code here */
}
​
// /**
// * deleteAVL deletes deleteKey from T.
// * @param T: an AVL tree
// * @param deleteKey: a key to delete
// */
void deleteAVL(Tree *T, int deleteKey) {
  /**
  * print "NO" if not rotates
  * print "LL" if rotates LL
  * print "RR" if rotates RR
  * print "LR" if rotates LR
  * print "RL" if rotates RL
  */
  /* write your code here */
}
​
/**
* inorderAVL implements inorder traversal in T.
* @param T: an AVL tree
*/
void inorderAVL(Tree T) {
  /* write your code here */
}
​
int main() {
  /* Do not modify the code below */
  ​
  int testcase[] = { 40, 11, 77, 33, 20, 90, 99, 70, 88, 80, 66, 10, 22, 30, 44, 55, 50, 60, 25, 49 };
  ​
  Tree T = NULL;
  ​
  // insertion
  for (int i=0; i<20; i++) { printf("%d ", testcase[i]); insertAVL(&T, testcase[i]); printf(" : "); inorderAVL(T); printf("\n"); }
  ​
  // deletion
  for (int i=0; i<20; i++) { printf("%d ", testcase[i]); deleteAVL(&T, testcase[i]); printf(" : "); inorderAVL(T); printf("\n"); }
  ​
  T = NULL;
  ​
  // reinsertion
  for (int i=0; i<20; i++) { printf("%d ", testcase[i]); insertAVL(&T, testcase[i]); printf(" : "); inorderAVL(T); printf("\n"); }
  ​
  // redeletion
  for (int i=19; 0<=i; i--) { printf("%d ", testcase[i]); deleteAVL(&T, testcase[i]); printf(" : "); inorderAVL(T); printf("\n"); }
}
