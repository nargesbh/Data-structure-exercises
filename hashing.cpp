#include<bits/stdc++.h>
#include<stdio.h>
#include<vector>
using namespace std;
class hash1{
    private:
        int n;
        string* inputArr;
        vector<vector<string>> ans;
    public:
        hash1();
        ~hash1();
        bool checkSame(string str1 , string str2);
        int findIndex(string str);
        bool checkIndex(int index , string str1);
};
hash1 :: hash1(){
    cin>>n;
    inputArr = new string[n];
    for(int i=0 ; i<n ; i++){
        cin>>inputArr[i];
    }
    for(int j=0 ; j<n ; j++){
        ans.push_back({"$"});
    }
    for(int k=0 ; k<n ; k++){
        int ind = findIndex(inputArr[k]);
        ans[ind].push_back(inputArr[k]);
    }
    int count =0;
    for(int i=0 ; i<n ; i++){
        if(ans[i][0]!="$"){
            count++;
        }
    }
    cout<<count<<endl;
    bool chk;
    for(int i=0 ; i<n ; i++){
        chk = false;
        if (ans[i][0]!="$"){cout<<ans[i].size()<<" ";}
        for(int j=0 ; j<ans[i].size() ; j++){
            if(ans[i][j]!="$"){
                cout<<ans[i][j]<<" ";
                chk = true;
                }
        }
        if(chk){cout<<endl;}
    }
}
int hash1::findIndex(string str){
    // cout<<"string :"<<str<<endl;
    int lenStr = str.length();
    int index=0;
    string strBef = str;
    sort(str.begin() , str.end());
    // cout<<"sorted str :"<<str<<endl;
    for(int i=0 ; i<lenStr ; i++){
        index += (int(str[i]) * i) ;
    }   
    // cout<<"index:"<<index<<endl;
    for(int t=0 ; t<n ; t++){
        int mod = (index + t)%n;
        if( checkIndex(mod , strBef)){
            // cout<<"mod :"<<mod<<endl;
            return mod;
        }
    }
    return 0;
}
bool hash1 :: checkIndex(int index , string str1){
    // cout<<"str1:"<<str1<<endl;
    if(ans[index][0]=="$"){
        ans[index].pop_back();
        return 1;
    }
    bool check = checkSame(str1 , ans[index][0]);
    if(check){
        return 1;
    }
    return 0;
}
bool hash1::checkSame(string str1 , string str2){
    int n1 = str1.length(); 
    int n2 = str2.length(); 
    if (n1 != n2) 
      return false; 
  
    sort(str1.begin(), str1.end()); 
    sort(str2.begin(), str2.end()); 
  
    for (int i = 0; i < n1;  i++) 
       if (str1[i] != str2[i]) 
         return false; 
  
    return true; 
}
int main(){
    hash1 ans;
    return 0;
}
hash1 :: ~hash1(){
    delete[] inputArr;
}