// Arvinbayar Jamsranjav
// CS211 Project5
// Fall 2019

#include "ajamsr2proj5.h"

// default constructor/init
//..
myStack::myStack()
{
    init();
}

// initial for stack
// ...
void myStack::init()
{
    size = 2;
    inUse = 0;
    arr = new int[size];
    for(int i =0; i<size; i++) {
        arr[i] = 0;
    }
}

// function to get the top value
// ...
int myStack::findingTop()
{
    if(inUse == 0) {
        return -999;
    }
    else {
        return arr[inUse-1];
    }
}

// function that checks if it's empty or not
// ...
bool myStack::isEmpty(){
    if(inUse == 0) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

// function that pushes number to the stack
// also grows if its full
// ...
void myStack::push(int inputVal)
{
    if(inUse == size) {
        int *temp;
        temp = arr;
        size = size + 2;
        for(int i = 0; i < inUse; i++) {
            temp[i] = arr[i];
        }
        arr = temp;
    }
    arr[inUse] = inputVal;
    inUse++;
}

// function that pushes operand to the stack
// also grows if its full
// ...
void myStack::push(char _operand)
{
    if(inUse == size) {
        int *temp1;
        temp1 = arr;
        size = size + 2;
        for(int i = 0; i < inUse; i++) {
            temp1[i] = arr[i];
        }
        arr = temp1;
    }
    
    arr[inUse] = _operand;
    inUse++; 
    
}

// function that pops from top of the stack
// decrementing inuse by 1
// ...
void myStack::pop()
{
    if(isEmpty() == 1 && debugMode == TRUE) {
        printf("Error message: Can't pop it's empty\n");
    }
    else {
        inUse--;
    }
}

// function that cleans my stack
// ...
void myStack::resetMyStack()
{
    size = 2;
    inUse = 0;
    delete[] arr;
    arr = new int[size];
}

// function that evaluates the expression
// ...
int popAndEval(myStack &numberStack, myStack &opStack)
{
    int result;      // to save the result after operand
    int num1, num2;  // 2 values on num stack
    char operOnTop;  // operand on the top of operand stack
    
    // getting top operand saving to another variable
    // and pop
    operOnTop = opStack.findingTop();
    opStack.pop();
    // getting top num saving to another variable
    // and pop
    num2 = numberStack.findingTop();
    if(num2 == -999) {
        if(debugMode == TRUE) {
            printf("Error message: The value stack is empty.\n");
        }
        return -999;
    }
    numberStack.pop();
    // getting top num saving to another variable
    // and pop
    num1 = numberStack.findingTop();
    if(num1 == -999) {
        if(debugMode == TRUE) {
            printf("Error message: The value stack is empty.\n");
        }
        return -999;
    }
    numberStack.pop();
    // evaluation    
    if(operOnTop == '*') {
        result = num2 * num1;
    }
    
    else if(operOnTop == '/') {
        result = num1 / num2;
    }
    
    else if(operOnTop == '+') {
        result = num2 + num1;
    }
    
    else if(operOnTop == '-') {
        result = num1 - num2;
    }
    
    else {
        return -999;
    }
    // push result to the stack
    numberStack.push(result);
 
    return 1;
    
}


// reads token pushes to 2 different stacks
// evaluates the result
// prints the result and error messages
// ...
void processExpression (Token inputToken, TokenReader *tr)
{
 /**********************************************/
 /* Declare both stack head pointers here      */
 myStack numberStack;
 myStack opStack;
 int incorrectOperand = 0;  // used to decide if my operand is correct or not
                            // boolean works too
 int countNum = 0;
 int countOperand = 0;
    
 /* Loop until the expression reaches its End */
 while (inputToken.equalsType(EOLN) == false)
   {
    /* The expression contain a VALUE */
    if (inputToken.equalsType(VALUE))
      {
      countNum++;
       /* make this a debugMode statement */
       if(debugMode == TRUE) {
           printf ("Val: %d\n", inputToken.getValue() );
       }
       numberStack.push(inputToken.getValue()); 
      }

    /* The expression contains an OPERATOR */
    if (inputToken.equalsType(OPERATOR))
      {
       /* make this a debugMode statement */
       if(debugMode == TRUE) {
           printf ("OP: %c\n", inputToken.getOperator() );   
       }
          if(inputToken.getOperator() == '('){
              opStack.push(inputToken.getOperator());
          }

          if(inputToken.getOperator() == '+' || inputToken.getOperator() == '-') {
              while((!opStack.isEmpty()) && (opStack.findingTop() == '+' || opStack.findingTop() == '-' ||
                                             opStack.findingTop() == '*' || opStack.findingTop() == '/')){
                  popAndEval(numberStack, opStack);
              } 
              opStack.push(inputToken.getOperator());
              countOperand++;
          }  
          
         if(inputToken.getOperator() == '*' || inputToken.getOperator() == '/') {
              while(!opStack.isEmpty() && (opStack.findingTop() == '*' || opStack.findingTop() == '/')) {
                  popAndEval(numberStack, opStack);
              } 
              opStack.push(inputToken.getOperator());
              countOperand++;
          } 
          
          if(inputToken.getOperator() == ')') {
                while(!opStack.isEmpty() && opStack.findingTop() != '(') {
                    popAndEval(numberStack, opStack);
                }
              
                if(opStack.isEmpty()) {
                    printf("Error message: Operand stack is empty.\n");
                }
                else {
                    opStack.pop();
                }
          }
      }
      // if its not operator and value type
      // incorrectOperand change to 1 
      // used to display error message
      else if (!inputToken.equalsType(OPERATOR) && !inputToken.equalsType(VALUE)){
         incorrectOperand = 1;
     } 
     
    /* get next token from input */
    inputToken = tr->getNextToken ();
   }
   
   while(!opStack.isEmpty()) {
       popAndEval(numberStack, opStack);
   }
   // storing top value to the variable
   // also pop to make my stack empty 
   int answer = numberStack.findingTop();
   numberStack.pop();
    
   if(incorrectOperand == 1) { 
        printf("Error message: Wrong operand was used. Fix your expression.\n");  
   } 
    
   else if(countNum < 2 || countOperand < 1) {
       printf("Error message: Fix your expression. \n");
   }
    
   else if (incorrectOperand == 0 && numberStack.isEmpty()) {
       printf("Result is: %d\n", answer); 
   }

   else if(!numberStack.isEmpty()) {
       printf("Error message: The number stack is not empty. Fix your expression.\n");
   } 
    
   // cleaning my stacks     
   numberStack.resetMyStack();
   opStack.resetMyStack();
}

int main(int argc, char *argv[])
{
    /***************************************************************/
    /* Add code for checking command line arguments for debug mode */
    
    for(int i = 0; i <argc; i++) {
        if(strcmp(argv[i], "-d") == 0)
            debugMode = TRUE;
    }
    
    if(debugMode==TRUE) {
        printf("Debugging Information\n");
    }
    
    Token inputToken;
    TokenReader tr;

    printf ("Starting Expression Evaluation Program\n");
    printf ("Enter Expression: ");


    inputToken = tr.getNextToken ();

    while (inputToken.equalsType(QUIT) == false)
    {
      /* check first Token on Line of input */
      if(inputToken.equalsType(HELP))
      {
       printCommands();
       tr.clearToEoln();
      }
      else if(inputToken.equalsType(ERROR))
      {
       printf ("Invalid Input - For a list of valid commands, type ?\n");
       tr.clearToEoln();
      }
      else if(inputToken.equalsType(EOLN))
      {
       printf ("Blank Line - Do Nothing\n");
       /* blank line - do nothing */
      }
      else
      {
       processExpression(inputToken, &tr);
      }

      printf ("\nEnter Expression: ");
      inputToken = tr.getNextToken ();
    } 
    
  printf ("Quitting Program\n");
  return 1;
}