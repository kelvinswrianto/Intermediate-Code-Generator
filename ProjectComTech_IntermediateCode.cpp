
// C++ program to convert an infix expression to a 
// postfix expression using two precedence function 
#include <bits/stdc++.h>
#include <string> 
using namespace std; 

// to check if the input character 
// is an operator or a '(' 
int isOperator(char input) 
{ 
    switch (input) { 
    case '+': 
        return 1; 
    case '-': 
        return 1; 
    case '*': 
        return 1; 
    case '^': 
        return 1; 
    case '%': 
        return 1; 
    case '/': 
        return 1; 
    case '(': 
        return 1; 
    } 
    return 0; 
} 
  
// to check if the input character is an operand 
int isOperand(char input) 
{ 
    if (input >= 65 && input <= 90 
        || input >= 97 && input <= 122 || input >=48 && input <= 57 ) 
        return 1; 
    return 0; 
} 
  
// function to return precedence value 
// if operator is present in stack 
int inPrec(char input) 
{ 
    switch (input) { 
    case '+': 
    case '-': 
        return 2; 
    case '*': 
    case '%': 
    case '/': 
        return 4; 
    case '^': 
        return 5; 
    case '(': 
        return 0; 
    } 
} 
  
// function to return precedence value 
// if operator is present outside stack. 
int outPrec(char input) 
{ 
    switch (input) { 
    case '+': 
    case '-': 
        return 1; 
    case '*': 
    case '%': 
    case '/': 
        return 3; 
    case '^': 
        return 6; 
    case '(': 
        return 100; 
    } 
} 
  
// function to convert infix to postfix 
string inToPost(string input) 
{ 
    string result = "";
    stack<char> s; 
    // while input is not NULL iterate 
    int i = 0; 
    while (input[i] != '\0') { 
  
        // if character an operand 
        if (isOperand(input[i])) { 
            result += input[i];
        } 
  
        // if input is an operator, push 
        else if (isOperator(input[i])) { 
            if (s.empty() 
                || outPrec(input[i]) > inPrec(s.top())) 
                s.push(input[i]); 
            else { 
                while (!s.empty() 
                       && outPrec(input[i]) < inPrec(s.top())) { 
                    result += s.top();
                    s.pop(); 
                } 
                s.push(input[i]); 
            } 
        } 
  
        // condition for opening bracket 
        else if (input[i] == ')') { 
            while (s.top() != '(') { 
                result += s.top();
                s.pop(); 
  
                // if opening bracket not present 
                if (s.empty()) { 
                    printf("Wrong input\n"); 
                    exit(1); 
                } 
            } 
  
            // pop the opening bracket. 
            s.pop(); 
        } 
        i++; 
    } 
  
    // pop the remaining operators 
    while (!s.empty()) { 
        if (s.top() == '(') { 
            printf("\n Wrong input\n"); 
            exit(1); 
        } 
        result += s.top();
        s.pop(); 
    }
    return result;
} 

int getPriority(char C) 
{ 
    if (C == '-' || C == '+') 
        return 1; 
    else if (C == '*' || C == '/') 
        return 2; 
    else if (C == '^') 
        return 3; 
    return 0; 
} 

string inToPre(string infix) 
{ 
    // stack for operators. 
    stack<char> operators; 
  
    // stack for operands. 
    stack<string> operands; 
  
    for (int i = 0; i < infix.length(); i++) { 
  
        // If current character is an 
        // opening bracket, then 
        // push into the operators stack. 
        if (infix[i] == '(') { 
            operators.push(infix[i]); 
        } 
  
        // If current character is a 
        // closing bracket, then pop from 
        // both stacks and push result 
        // in operands stack until 
        // matching opening bracket is 
        // not found. 
        else if (infix[i] == ')') { 
            while (!operators.empty() &&  
                   operators.top() != '(') { 
  
                // operand 1 
                string op1 = operands.top(); 
                operands.pop(); 
  
                // operand 2 
                string op2 = operands.top(); 
                operands.pop(); 
  
                // operator 
                char op = operators.top(); 
                operators.pop(); 
  
                // Add operands and operator 
                // in form operator + 
                // operand1 + operand2. 
                string tmp = op + op2 + op1; 
                operands.push(tmp); 
            } 
  
            // Pop opening bracket from 
            // stack. 
            operators.pop(); 
        } 
  
        // If current character is an 
        // operand then push it into 
        // operands stack. 
        else if (!isOperator(infix[i])) { 
            operands.push(string(1, infix[i])); 
        } 
  
        // If current character is an 
        // operator, then push it into 
        // operators stack after popping 
        // high priority operators from 
        // operators stack and pushing 
        // result in operands stack. 
        else { 
            while (!operators.empty() &&  
                   getPriority(infix[i]) <=  
                     getPriority(operators.top())) { 
  
                string op1 = operands.top(); 
                operands.pop(); 
  
                string op2 = operands.top(); 
                operands.pop(); 
  
                char op = operators.top(); 
                operators.pop(); 
  
                string tmp = op + op2 + op1; 
                operands.push(tmp); 
            } 
  
            operators.push(infix[i]); 
        } 
    } 
  
    // Pop operators from operators stack 
    // until it is empty and add result 
    // of each pop operation in 
    // operands stack. 
    while (!operators.empty()) { 
        string op1 = operands.top(); 
        operands.pop(); 
  
        string op2 = operands.top(); 
        operands.pop(); 
  
        char op = operators.top(); 
        operators.pop(); 
  
        string tmp = op + op2 + op1; 
        operands.push(tmp); 
    } 
  
    // Final prefix expression is 
    // present in operands stack. 
    return operands.top(); 
} 

void TAC(string input){
    int counter = 1;
    string postfix;
    postfix = inToPost(input);
    stack<char> operands;
    for(int i=0; i<postfix.length(); i++){
        if(isOperand(postfix[i])){
            operands.push(postfix[i]);
        }
        else{
            char opd1, opd2, opt;
            char cnt1='\0', cnt2='\0';
            if(operands.top() == 't'){
                opd1 = operands.top();
                operands.pop();
                cnt1 = operands.top();
                operands.pop();
            }
            else{
                opd1 = operands.top();
                operands.pop();
            }
            if(operands.top() == 't'){
                opd2 = operands.top();
                operands.pop();
                cnt2 = operands.top();
                operands.pop();
            }
            else{
                opd2 = operands.top();
                operands.pop();
            }
            opt = postfix[i];
            cout << " t" << counter << " = " << opd2 << "" << cnt2 << " " << opt << " " << opd1 << "" << cnt1 << endl;
            char num = counter+'0';
            counter++;
            operands.push(num);
            operands.push('t');
        }
    }
}

// Driver code 
int main() 
{ 
    int inputMenu;
    while(true){
        system("cls");
        cout << " ============================" << endl;
        cout << "      Intermediate Code" << endl;
        cout << " ============================" << endl;
        cout << " 1. INFIX to POSTFIX and PREFIX converter" << endl;
        cout << " 2. INFIX to Three Address Code (TAC) converter" << endl;
        cout << " 3. Info & Help" << endl;
        cout << " 4. Exit" << endl;
        while(true){
            cout << " Choose [1..5] : ";
            cin >> inputMenu; cin.clear(); cin.sync();
            if(inputMenu >= 1 && inputMenu <= 5) break;
        }
        if(inputMenu == 1){
            system("cls");
            string input, postfix, prefix;
            cout << " =============================" << endl;
            cout << "  INFIX to POSTFIX and PREFIX" << endl;
            cout << " =============================" << endl;
            cout << endl;
            cout << " Input INFIX expression : ";
            cin >> input; cin.clear(); cin.sync();
            postfix = inToPost(input);
            prefix = inToPre(input);
            cout << endl << endl;
            cout << " RESULT" << endl;
            cout << " ===============" << endl;
            cout << " INFIX \t\t: " << input << endl;
            cout << " POSTFIX \t: " << postfix << endl;
            cout << " PREFIX \t: " << prefix << endl;
            cout << endl << endl; 
            cout << " Press enter to continue ... " << endl;
            getchar();
        }
                      
        if(inputMenu == 2){
            system("cls");
            string input;
            cout << " ===================================" << endl;
            cout << "  INFIX to Three Address Code (TAC)" << endl;
            cout << " ===================================" << endl;
            cout << endl;
            cout << " Input INFIX expression : ";
            cin >> input; cin.clear(); cin.sync();
            cout << endl << endl;
            cout << " RESULT" << endl;
            cout << " ===============" << endl;
            TAC(input);
            cout << endl << endl; 
            cout << " Press enter to continue ... " << endl;
            getchar();
        }
        if(inputMenu == 3){
            system("cls");
            cout << " Designed by : " << endl;
            cout << " - Kelvin Supranata Wangkasa Rianto " << endl;
            cout << " - Vincent Ardyan Putra " << endl;
            cout << " - Lucky Cristopher Chen" << endl;
            cout << " Press enter to continue ... " << endl;
            getchar();
        }
        if(inputMenu == 4) break;
    }
    system("cls");
    cout << " THANKS FOR USING OUR APPLICATION!" << endl;
    cout << " Press enter to exit ... " << endl;
    getchar();
    return 0; 
} 
