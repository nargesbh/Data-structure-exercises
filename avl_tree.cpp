// AVL tree implementation in C++
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

class Node {
   public:
  int key;
  Node *left;
  Node *right;
  int height;
};
class avl{
    private:
        Node *root = NULL;
        vector<int> help;
        bool helpPrint;
    public:
        avl();
        int height(Node *N);
        int max(int a, int b);
        Node *newNode(int key);
        Node *rightRotate(Node *y) ;
        Node *leftRotate(Node *x);
        int getBalanceFactor(Node *N);
        Node *insertNode(Node *node, int key);
        void printTree(Node *node ,int n , bool help);
        void avl_pr(Node* node);

};
avl ::avl(){
    vector<int> inputs;
    string x;
    while(x!="q"){
		cin >> x ;
        if(x=="q"){break;}
        stringstream h(x);
        int x=0 ;
        h >> x;
        inputs.push_back(x);
    }
    int count =1;
    for(int i=0 ; i<inputs.size() ; i++){
        root = insertNode(root , inputs[i]);
        helpPrint = true;
        printTree(root,count,helpPrint);
        int n = help.size();
        // cout <<"help :"<<count<< " /";
        // for(int j=0 ; j<help.size() ; j++){
        //   cout<<help[j]<<" ";
        // }
        // cout<<endl;
        if(count%2 !=0 ){
            float m = help[count/2];
            cout << m <<endl; 
        }

        else{
            float m = (float(help[count/2]) + float(help[(count/2)-1]))/2;
            cout << m << endl;
        }
        count++;
        help.clear();
    }
}
int avl:: height(Node *N) {
  if (N == NULL)
    return 0;
  return N->height;
}

int avl:: max(int a, int b) {
  return (a > b) ? a : b;
}

// New node creation
Node* avl :: newNode(int key) {
  Node *node = new Node();
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return (node);
}

// Rotate right
Node* avl :: rightRotate(Node *y) {
  Node *x = y->left;
  Node *T2 = x->right;
  x->right = y;
  y->left = T2;
  y->height = max(height(y->left),
          height(y->right)) +
        1;
  x->height = max(height(x->left),
          height(x->right)) +
        1;
  return x;
}

// Rotate left
Node* avl :: leftRotate(Node *x) {
  Node *y = x->right;
  Node *T2 = y->left;
  y->left = x;
  x->right = T2;
  x->height = max(height(x->left),
          height(x->right)) +
        1;
  y->height = max(height(y->left),
          height(y->right)) +
        1;
  return y;
}

// Get the balance factor of each node
int avl:: getBalanceFactor(Node *N) {
  if (N == NULL)
    return 0;
  return height(N->left) -
       height(N->right);
}

// Insert a node
Node* avl :: insertNode(Node *node, int key) {
  // Find the correct postion and insert the node
  if (node == NULL)
    return (newNode(key));
  if (key < node->key)
    node->left = insertNode(node->left, key);
  else if (key >= node->key)
    node->right = insertNode(node->right, key);

  // Update the balance factor of each node and
  // balance the tree
  node->height = 1 + max(height(node->left),
               height(node->right));
  int balanceFactor = getBalanceFactor(node);
  if (balanceFactor > 1) {
    if (key < node->left->key) {
      return rightRotate(node);
    } else if (key > node->left->key) {
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }
  }
  if (balanceFactor < -1) {
    if (key > node->right->key) {
      return leftRotate(node);
    } else if (key < node->right->key) {
      node->right = rightRotate(node->right);
      return leftRotate(node);
    }
  }
  return node;
}
// Print the tree
void avl :: printTree(Node *node, int n , bool helpPrint) {
        if (node == NULL || !helpPrint) 
            return; 
    
        /* first recur on left child */
        printTree(node->left,n , helpPrint); 
    
        help.push_back(node->key);
        if(help.size()>n/2){
          // cout<<"n/2 :"<<n/2<<endl;
          // cout<<"size:"<<help.size()<<endl;
          helpPrint = false;
          printTree(node->right,n , helpPrint); 
          // exit ;
          // return;
        }
    
        /* now recur on right child */
        else{
        printTree(node->right,n , helpPrint); 
        }
}
void avl ::avl_pr(Node* Node){

}

int main() {
    avl ans;
}
