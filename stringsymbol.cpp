#include<iostream>
#include<vector>
using namespace std;
class str{
    private :
        int n;
        string* stringArr;
        string* symbolArr;
        string* ansMake;
        string symbol;
        bool checkFinale;
    public :
        void substr(string a , string b , int index);//a is the sentence and b is symbol's string
        bool check_symbol(string* a , string symb);
        str();
        ~str();
};
str :: str(){
    // cout<<"enter n:";
    cin>>n;
    stringArr = new string[n];
    symbolArr = new string[n];
    for(int i=0 ; i<n ; i++){
        cin >> stringArr[i];
        cin >> symbolArr[i];
    }
    ansMake = new string[3];
    // substr("amime","XXX" , 0);
    for(int i=0 ; i<n ; i++){
        symbol = symbolArr[i];
        checkFinale = false;
        ansMake= new string[symbolArr[i].size()];
        substr(stringArr[i] , symbolArr[i] , 0);
        if(checkFinale){
           cout <<"Yes"<<endl;
       }
       else{
           cout<<"No"<<endl;
       }
    }
}
void str::substr(string a , string b , int index){
    // cout << "a :"<<a<<" b:"<<b<<endl;
    // cout <<"b :"<<b << endl;
    if(b.size()>1){
        for(int k=1 ; k<(a.size()-b.size()+2) ;k++){
            // cout <<"new :" <<b[0] <<" " << a.substr(0,k)<<endl; 
            ansMake[index] = a.substr(0,k);
            substr( a.substr(k,a.size()-1) , b.substr(1,b.size()-1) , index+1 );
        }
    }
    else{
        // cout << "new 2 :"<<b <<" "<<a<<endl;
        ansMake[index] = a ;
        if(check_symbol(ansMake , symbol)){
            // cout <<"yaa"<<endl;
            checkFinale = true;
        }
    }
    // cout <<"why god"<<endl;
    // cout <<endl;
}
bool str ::check_symbol(string* a , string symb){
    // cout <<"symb :"<<symb<<endl;
    // for(int i=0 ; i<3 ; i++ ){
    //     cout << a[i]<<" ";
    // }
    // cout <<endl;
    for(int i=0 ; i<symb.size() ; i++){
        for(int j=i+1 ; j<symb.size() ; j++){
            // cout<<"symbol[i] :"<<symb[i]<<endl;
            // cout<<"symb[j] :"<<symb[j]<<endl;
            if (symb[i]==symb[j] && a[i]!=a[j]){
                // cout<<"symbol[i]=symb[j] :"<<symb[i]<<endl;
                // cout <<"a[i] :"<<a[i]<<endl;
                // cout <<"a[j] :"<<a[j+1]<<endl;
                // cout <<"false"<<endl;
                return false;
            }
        }
    }
    // cout <<"true"<<endl;
    return true;
}
int main(){
    str answer;
    return 0;
}
str :: ~str(){
    delete[] stringArr;
    delete[] symbolArr;
}