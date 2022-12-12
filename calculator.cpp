#include <iostream> 
#include <sstream> 
#include<iomanip>
using namespace std;
class cal{
    private :
        int n;
        int stackIndex=-1;
        string* inp;
        string* stack;
        string* math_stack;
    public :
        cal();
        ~cal();
        void push(char a);
        void pop();
        string last();
        string postfixFind(string a);
        string eval_post(string a);
        double mathOperation(char op , string num1 , string num2);
};
cal :: cal(){
    cin >> n;
    inp = new string [n];
    for(int i=0 ; i<n ; i++){
        cin >> inp[i];
    }
    for(int i=0 ; i<n ; i++){
        stack = new string[250];
        stackIndex = -1;
        string postfix = postfixFind(inp[i]);
        cout <<postfix<<endl;
        string ansMath = eval_post(postfix);
        // cout <<ansMath<<endl;
        double ansdouble = stod(ansMath);
        cout <<fixed<<setprecision(3)<<  ansdouble << endl; 
        delete[] math_stack;
        delete[] stack;
    }

}
void cal::push(char a){
    stackIndex++;
    stack[stackIndex] = a;
}

void cal::pop(){
    stackIndex--;
}

string cal::last(){
    return stack[stackIndex];
}
string cal::postfixFind(string a){
    string ans="";
    for(int i=0 ; i<a.length() ; i++){
        // cout<<"i :"<<i<<endl;
        if(a[i]==*"("){
            // cout<<"1"<<endl;
            push(a[i]);
        }

        else if(a[i]==*"*" || a[i]==*"/"){
            // cout<<"2"<<endl;
            while(stackIndex!=-1 && (last()=="*" || last()=="/") ){
                ans+=last();
                pop();
            }
            push(a[i]);
        }

        else if(a[i]==*"+" || a[i]==*"-"){
            // cout<<"3"<<endl;
            while(stackIndex!=-1 && (last()=="*" || last()=="/" || last()=="+" || last()=="-")){
                // cout<<"1"<<endl;
                ans+=last();
                pop();
            }
            // cout<<"m"<<endl;
            push(a[i]);
        }

        else if(a[i]==*")"){
            // cout<<"4"<<endl;
            while(stackIndex!=-1 && (last()!="(") ){
                ans+=last();
                pop();
            }
            pop();
        }
        else{
            // cout<<"5"<<endl;
            ans+=a[i];
        }
    }
    for(int i=stackIndex ; i>-1 ; i--){
        ans+=stack[i];
    }
    return ans;
}
string cal::eval_post(string a){
    math_stack = new string[250];
    int stackIndex=0;
    int len = a.length();
    for(int i=0 ; i<len ; i++){
        if(a[i]==*"*" || a[i]==*"/" || a[i]==*"+" || a[i]==*"-"){
            double mathHelp_int = mathOperation(a[i] , math_stack[stackIndex-2] , math_stack[stackIndex-1]);
            string mathHelp_string = to_string(mathHelp_int);
            // cout <<"math help strinh :"<<mathHelp_string<<endl;
            stackIndex-=2;
            math_stack[stackIndex] = mathHelp_string;
            stackIndex++;
        }
        else{
            math_stack[stackIndex] = a[i];
            stackIndex++;
        }
        // cout <<"1"<<endl;
    }
    // cout <<"2"<<endl;
    return math_stack[0];
}
double cal::mathOperation(char op , string num1 , string num2){
    stringstream one(num1);
    double numOne=0.0;
    one>>numOne;
    stringstream two(num2);
    double numTwo=0.0;
    two>>numTwo;
    if(op==*"*"){
        return numOne * numTwo;
    }
    if(op==*"/"){
        return numOne / numTwo;
    }
    if(op==*"+"){
        return numOne + numTwo;
    }
    else{
        return numOne - numTwo;
    }
}
int main(){
    cal ans;
    return 0;
}
cal::~cal(){
    delete[] inp;
}
