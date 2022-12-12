#include <iostream>
using namespace std;
class Node{
    public:
        int counter=0;
        Node* rightChild=NULL;
        Node* leftChild=NULL;
};
Node* make_tree(string binaryNum , Node* tree){
    Node* root = tree;
    for(int i=0 ; i<binaryNum.size() ; i++)
    {
        if(binaryNum[i]=='0'){
            if(root->leftChild==NULL)
            {
                root->leftChild = new Node;
                root = root->leftChild;
            }
            else
            {
                root = root->leftChild;
            }
        }
        if(binaryNum[i]=='1'){
            if(root->rightChild==NULL)
            {
                root->rightChild = new Node;
                root = root->rightChild;
            }
            else
            {
                root = root->rightChild;
            }
        }
    }
    root->counter = root->counter + 1;
    return tree;
}
void printPreorder(Node* head , string help){
    //cout << head->counter << endl;
    for(int i=0 ; i<head->counter ; i++)
    {
        cout << help << " ";
    }
    string help0 = help+'0';
    string help1 = help+'1';
    if(head->leftChild != NULL)
    {
        printPreorder(head->leftChild , help0 );
    }
    if(head->rightChild != NULL)
    {
        printPreorder(head->rightChild , help1 );
    }
}
int main(){
    int n;
    cin>>n;
    Node * tree = new Node ;
    string binNum;
    for(int i=0 ; i<n ;i++){
        cin>>binNum;
        tree = make_tree(binNum , tree);
    }
    string h="";
    printPreorder(tree , h);
    return 0;
}