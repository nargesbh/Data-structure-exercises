	
#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

class Huffman_Codes
{
 struct New_Node
 {
  char data;
  size_t freq;
  New_Node* left;
  New_Node* right;
  New_Node(char data, size_t freq) : data(data),
                                 freq(freq),
left(NULL),
right(NULL)
                                 {}
 ~New_Node()
 {
   delete left;
   delete right;
 }
 };

 struct compare
 {
  bool operator()(New_Node* l, New_Node* r)
  {
    return (l->freq > r->freq);
  }
};

New_Node* top;
vector<char> huffman_char_order;
vector<string> huffman_code;
void print_Code(New_Node* root, string str)
{
if(root == NULL)
   return;

 if(root->data == '$')
 {
  print_Code(root->left, str + "1");
  print_Code(root->right, str + "0");
 }

 if(root->data != '$')
 {
  //  cout << root->data <<" : " << str << "\n";
    huffman_char_order.push_back(root->data);
    huffman_code.push_back(str);
   print_Code(root->left, str + "1");
   print_Code(root->right, str + "0");
 }
}
void decode_func(string code_str){
  string code="";
  string character="";
  for(int i=0 ; i<code_str.size() ; i++){
    code+=code_str[i];
    // cout<<"code :"<<code<<endl;
    for(int j=0 ; j<huffman_code.size() ; j++){
      if (code==huffman_code[j]){
        // cout<<"here"<<endl;
        character+=huffman_char_order[j];
        code="";
        // cout<<"character :"<<character<<endl;
        break;
      }
    }
  }
  cout<<character<<endl;
}
public:
  Huffman_Codes() {};
  ~Huffman_Codes()
  {
    delete top;
  }
  void Generate_Huffman_tree(vector<char>& data, vector<size_t>& freq, size_t size , string decode)
  {
   New_Node* left;
   New_Node* right;
   priority_queue<New_Node*, vector<New_Node*>, compare > minHeap;

for(size_t i = 0; i < size; ++i)
   {
      minHeap.push(new New_Node(data[i], freq[i]));
   }

while(minHeap.size() != 1)
    {
      left = minHeap.top();
minHeap.pop();

      right = minHeap.top();
minHeap.pop();

      top = new New_Node('$', left->freq + right->freq);
      top->left  = left;
      top->right = right;
      minHeap.push(top);
     }
    print_Code(minHeap.top(), "");
    decode_func(decode);
    // cout<<"*****"<<endl;
    // for(int i=0 ; i<huffman_code.size() ; i++){
    //   cout << huffman_char_order[i] << " ; "<< huffman_code[i]<<endl;
    // }
 }
};

 int main()
 {
  int n, f;
  char ch;
  Huffman_Codes set1;
  vector<char> data;
  vector<size_t> freq;
  // cout<<"Enter the number of elements \n";
  cin>>n;
  for (int i=0;i<n;i++)
  {
      cin>>ch>>f;
      data.insert(data.end(), ch);
      freq.insert(freq.end(), f);
  }
  string decode;
  cin>>decode;
  size_t size = data.size();
  set1.Generate_Huffman_tree(data, freq, size , decode);
  return 0;
}

	
