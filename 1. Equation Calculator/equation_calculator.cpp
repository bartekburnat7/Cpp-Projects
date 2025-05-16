#include <iostream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

class equation_calculator
{
private:
    string equation;
    vector<string> translated_arr;
    
public:
    void get_input();
    void vector_translator();
    void calculate();
    equation_calculator()
    {
        get_input();
    }
};

void equation_calculator::get_input(){
    getline(cin, equation);
};

void equation_calculator::vector_translator(){
    string stack;
    for (char i:equation){
        if(i == '+' || i == '-'){
            translated_arr.push_back(stack);
            stack.clear();
            if (stack.empty()){
                translated_arr.push_back(string(1,i));
            }
        } else {
            stack.push_back(i);
        }
    };
    translated_arr.push_back(stack);
};

void equation_calculator::calculate(){
    int anwser,num;
    anwser = 0;
    string operation;
    for(string term:translated_arr){
        try{
            num = stoi(term);
            if (operation.empty()){
                anwser += num;
            } else {
                if (operation == "+"){
                    anwser += num;
                } else if(operation == "-"){
                    anwser -= num;
                }
                operation.clear();
            }
        } catch (const invalid_argument){
            if ((term==operation) && term == "-"){
                operation = "+";
            } else if(term == "+" ) {
                if (operation == "-"){
                    operation="-";
                } else {
                    operation = "+";
                }
            } else if (term == "-") {
                operation = "-";
            }
        }
    };
    cout << anwser << endl;
};

int main(){
    equation_calculator calc;
    calc.vector_translator();
    calc.calculate();
    return 0;
}