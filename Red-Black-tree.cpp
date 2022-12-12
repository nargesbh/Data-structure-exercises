#include <iostream>
#include <bits/stdc++.h>
#include <vector>
using namespace std;

struct Node {
	int data; // holds the key
	Node *parent; // pointer to the parent
	Node *left; // pointer to left child
	Node *right; // pointer to right child
	int color; // 1 -> Red, 0 -> Black
};

typedef Node *NodePtr;

// class RBTree implements the operations in Red Black Tree
class RBTree {
private:
	NodePtr root;
	NodePtr TNULL;
	void initializeNULLNode(NodePtr node, NodePtr parent) {
		node->data = 0;
		node->parent = parent;
		node->left = nullptr;
		node->right = nullptr;
		node->color = 0;
	}

	NodePtr searchTreeHelper(NodePtr node, int key) {
		if (node == TNULL || key == node->data) {
			return node;
		}

		if (key < node->data) {
			return searchTreeHelper(node->left, key);
		} 
		return searchTreeHelper(node->right, key);
	}

	void fixDelete(NodePtr x) {
		NodePtr s;
		while (x != root && x->color == 0) {
			if (x == x->parent->left) {
				s = x->parent->right;
				if (s->color == 1) {

					s->color = 0;
					x->parent->color = 1;
					leftRotate(x->parent);
					s = x->parent->right;
				}

				if (s->left->color == 0 && s->right->color == 0) {

					s->color = 1;
					x = x->parent;
				} else {
					if (s->right->color == 0) {

						s->left->color = 0;
						s->color = 1;
						rightRotate(s);
						s = x->parent->right;
					} 

					s->color = x->parent->color;
					x->parent->color = 0;
					s->right->color = 0;
					leftRotate(x->parent);
					x = root;
				}
			} else {
				s = x->parent->left;
				if (s->color == 1) {

					s->color = 0;
					x->parent->color = 1;
					rightRotate(x->parent);
					s = x->parent->left;
				}

				if (s->right->color == 0 && s->right->color == 0) {

					s->color = 1;
					x = x->parent;
				} else {
					if (s->left->color == 0) {

						s->right->color = 0;
						s->color = 1;
						leftRotate(s);
						s = x->parent->left;
					} 

					s->color = x->parent->color;
					x->parent->color = 0;
					s->left->color = 0;
					rightRotate(x->parent);
					x = root;
				}
			} 
		}
		x->color = 0;
	}


	void rbTransplant(NodePtr u, NodePtr v){
		if (u->parent == nullptr) {
			root = v;
		} else if (u == u->parent->left){
			u->parent->left = v;
		} else {
			u->parent->right = v;
		}
		v->parent = u->parent;
	}

	void deleteNodeHelper(NodePtr node, int key) {
		NodePtr z = TNULL;
		NodePtr x, y;
		while (node != TNULL){
			if (node->data == key) {
				z = node;
			}

			if (node->data <= key) {
				node = node->right;
			} else {
				node = node->left;
			}
		}

		y = z;
		int y_original_color = y->color;
		if (z->left == TNULL) {
			x = z->right;
			rbTransplant(z, z->right);
		} else if (z->right == TNULL) {
			x = z->left;
			rbTransplant(z, z->left);
		} else {
			y = minimum(z->left);
			// cout<<"y :"<<y->data<<endl;
			y_original_color = y->color;
			x = y->left;
			if (y->parent == z) {
				x->parent = y;
			} else {
				rbTransplant(y, y->left);
				y->left = z->left;
				y->left->parent = y;
			}

			rbTransplant(z, y);
			y->right = z->right;
			y->right->parent = y;
			y->color = z->color;
		}
		delete z;
		if (y_original_color == 0){
			fixDelete(x);
		}
	}
	
	// fix the red-black tree
	void fixInsert(NodePtr k){
		NodePtr u;
		while (k->parent->color == 1) {
			if (k->parent == k->parent->parent->right) {
				u = k->parent->parent->left; 
				if (u->color == 1) {

					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				} else {
					if (k == k->parent->left) {

						k = k->parent;
						rightRotate(k);
					}

					k->parent->color = 0;
					k->parent->parent->color = 1;
					leftRotate(k->parent->parent);
				}
			} else {
				u = k->parent->parent->right;

				if (u->color == 1) {

					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;	
				} else {
					if (k == k->parent->right) {

						k = k->parent;
						leftRotate(k);
					}

					k->parent->color = 0;
					k->parent->parent->color = 1;
					rightRotate(k->parent->parent);
				}
			}
			if (k == root) {
				break;
			}
		}
		root->color = 0;
	}


public:
	RBTree() {
		TNULL = new Node;
		TNULL->color = 0;
		TNULL->left = nullptr;
		TNULL->right = nullptr;
		root = TNULL;
	}

	NodePtr searchTree(int k) {
		return searchTreeHelper(this->root, k);
	}

	NodePtr minimum(NodePtr node) {
		while (node->left != TNULL) {
			node = node->left;
		}
		return node;
	}

	void leftRotate(NodePtr x) {
		NodePtr y = x->right;
		x->right = y->left;
		if (y->left != TNULL) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		} else if (x == x->parent->left) {
			x->parent->left = y;
		} else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	void rightRotate(NodePtr x) {
		NodePtr y = x->left;
		x->left = y->right;
		if (y->right != TNULL) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		} else if (x == x->parent->right) {
			x->parent->right = y;
		} else {
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}

	void insert(int key) {
		NodePtr node = new Node;
		node->parent = nullptr;
		node->data = key;
		node->left = TNULL;
		node->right = TNULL;
		node->color = 1; // new node must be red

		NodePtr y = nullptr;
		NodePtr x = this->root;

		while (x != TNULL) {
			y = x;
			if (node->data < x->data) {
				x = x->left;
			} else {
				x = x->right;
			}
		}

		// y is parent of x
		node->parent = y;
		if (y == nullptr) {
			root = node;
		} else if (node->data < y->data) {
			y->left = node;
		} else {
			y->right = node;
		}

		// if new node is a root node, simply return
		if (node->parent == nullptr){
			node->color = 0;
			return;
		}

		// if the grandparent is null, simply return
		if (node->parent->parent == nullptr) {
			return;
		}

		fixInsert(node);
	}

	NodePtr getRoot(){
		return this->root;
	}

	void deleteNode(int data) {
		deleteNodeHelper(this->root, data);
	}

	void prettyPrint(bool checkSearch , int searchInt) {
		queue<Node *> q1, q2; 
		NodePtr helpNull= new Node;
		helpNull->data=0;
		int counter1 = 0;
		int counter2=0;
			if (root == NULL) 
				return; 

			q1.push(root); 

			while (!q1.empty() || !q2.empty()) 
			{ 
				while (!q1.empty()) 
				{ 

					if (q1.front()->left != NULL) {
						q2.push(q1.front()->left); 
			}

			if(q1.front()->left==NULL && q1.front()->data!=0){
				q2.push(helpNull);
			}

					if (q1.front()->right != NULL){ 
						q2.push(q1.front()->right); 
			}

			if(q1.front()->right==NULL && q1.front()->data!=0){
				q2.push(helpNull);
			}
			if(q1.front()->data==0){
				cout<<" N";
			}
					else if(q1.front()->data!=0){
				counter1++;

				if(q1.front()->color==0){
				cout<<" " << q1.front()->data <<"B"; 
				}
				if(q1.front()->color==1){
				cout<<" " << q1.front()->data <<"R"; 
				}
				if(checkSearch && q1.front()->data==searchInt){
					cout<<"*";
				}

			}
					q1.pop(); 
				} 
			for(int i=0 ;i < counter1 ; i++){
			if(i==0){cout<<"\n";}
			cout<<"/ \\ ";
			}
				cout << "\n"; 
			counter1=0;
				while (!q2.empty()) 
				{ 

					if (q2.front()->left != NULL){ 
						q1.push(q2.front()->left); 
			}
			if(q2.front()->left==NULL && q2.front()->data!=0){
				q1.push(helpNull);
			}

					if (q2.front()->right != NULL){
						q1.push(q2.front()->right);
			} 
			if(q2.front()->right==NULL && q2.front()->data!=0){
				q1.push(helpNull);
			}
			if(q2.front()->data==0){
				cout<<" N";
			}
			else if(q2.front()->data!=0){

			if(q2.front()->color==0){
					cout<<" " << q2.front()->data << "B"; 
				}
			if(q2.front()->color==1){
					cout<<" " << q2.front()->data << "R"; 
				}
			if(checkSearch && q2.front()->data==searchInt){
					cout<<"*";
				}
					counter2++;
			}
					q2.pop(); 
				} 
			for(int i=0 ; i<counter2 ; i++){
			if(i==0){cout<<"\n";}
			cout<<"/ \\ ";
			}
				cout << "\n"; 
			counter2=0;
			} 
	}

};

int main() {
	RBTree bst;
	string x;
	int n;
	vector<string> commandVec;
	vector<int> intVec; 
	while(x!="q"){
		cin >> x ;
		commandVec.push_back(x);
		if(x=="q"){break;}
		cin >> n;
		intVec.push_back(n);
	}

	for(int i=0 ; i<intVec.size() ; i++){

		if(commandVec[i]=="i"){
			bst.insert(intVec[i]);
			bst.prettyPrint(false,0);
			cout<<endl;
		}

		if(commandVec[i]=="d"){
			bst.deleteNode(intVec[i]);
			bst.prettyPrint(false,0);
			cout<<endl;
		}

		if(commandVec[i]=="s"){
			if(bst.searchTree(intVec[i])->data==0){
				cout<<"INVALID"<<endl;
			}
			else{
				bst.prettyPrint(true,intVec[i]);
			}
		}
		
	}
	return 0;
}