///////////////////////////////////////////////////////////////////////////////
// 
// Author:           Kyle Gordon
// Email:            kylekgordon@gmail.com
// Label:            P01
// Title:            STACK RESIZE
// Course:           3013-Algorithms
// Semester:         Spring 2021
//
// Description:
//      This program implements a class that allows a stack to be generated and used just
//      like an array. It loads the data and check if even or odd. Odd numbers are pushed
//      to stack, while the reading of an even number causes the top element of the stack
//      to pop. It allowings the user to "push" items onto the top of the stack, 
//      as well as "pop" items off the end of our stack.
//
// Usage:
//      Run the program and it reads the numbers from the file nums_test.dat.
//
// Files:     
//      main.cpp    : driver program
/////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

/**
 * ArrayStack
 *
 * Description:
 *      Array based stack
 *
 * Public Methods:
 *      - See class below
 *
 * Usage:
 *      - See main program
 *
 */
class ArrayStack {
private:
    int* A;           // pointer to array of int's
    int size;         // current stack size
    int top;          // top of stack
    int sized;        // stack resized #
    int maxsize;      // maximum size obtained

public:
    /**
     * ArrayStack
     *
     * Description:
     *      Constructor no params
     *
     * Params:
     *     - None
     *
     * Returns:
     *     - NULL
     */
    ArrayStack() {
        size = 10;
        A = new int[size];
        top = -1;
        sized = 0;
        maxsize = 0;
    }

    /**
     * ArrayStack
     *
     * Description:
     *      Constructor size param
     *
     * Params:
     *     - int size
     *
     * Returns:
     *     - NULL
     */
    ArrayStack(int s) {
        size = s;
        A = new int[s];
        top = -1;
        sized = 0;
        maxsize = 0;
    }

    /**
     * Public bool: Empty
     *
     * Description:
     *      Stack empty?
     *
     * Params:
     *      NULL
     *
     * Returns:
     *      [bool] true = empty
     */
    bool Empty() {
        return (top <= size * (15/100));
    }

    /**
     * Public bool: Full
     *
     * Description:
     *      Stack full?
     *
     * Params:
     *      NULL
     *
     * Returns:
     *      [bool] true = full
     */
    bool Full() {
        return (top >= size - 1);
    }

    /**
     * Public int: Peek
     *
     * Description:
     *      Returns top value without altering the stack
     *
     * Params:
     *      NULL
     *
     * Returns:
     *      [int] top value if any
     */

 /*   bool underHalf() {
        if (ArrayStack.size <= size)
        return ();
    }*/

    int Peek() {
        if (!Empty()) {
            return A[top];
        }

        return -99; // some sentinel value
                    // not a good solution
    }

    /**
     * Public int: Pop
     *
     * Description:
     *      Returns top value and removes it from stack
     *
     * Params:
     *      NULL
     *
     * Returns:
     *      [int] top value if any
     */
    int Pop() {
        if (!Empty()) {        
            return A[top--];           
        }
        return -99; // some sentinel value
                    // not a good solution
    }

    /**
     * Public void: Print
     *
     * Description:
     *      Prints stack to standard out
     *
     * Params:
     *      NULL
     *
     * Returns:
     *      NULL
     */
    void Print(int pushcount) {
        for (int i = 0; i <= top; i++) {
            cout << A[i] << " ";
        }
    }

    /**
     * Public void: Display
     *
     * Description:
     *      Outputs read from tracking
     *
     * Params:
     *      NULL
     *
     * Returns:
     *      NULL
     */
    void Display() {

        cout << endl;
        cout << "#######################################################################" << endl;
        cout << "Assignment 4 - Resizing the stack" << endl;
        cout << "CMPS 3013" << endl;
        cout << "Kyle Gordon" << endl;
        cout << endl;
        cout << "Max Stack Size: " << maxsize << endl;
        cout << "End Stack Size: " << size << endl;;
        cout << "Stack Resized: " << sized << " times" << endl;
        cout << "#######################################################################" << endl;

    }

    /**
     * Public bool: Push
     *
     * Description:
     *      Adds an item to top of stack
     *
     * Params:
     *      [int] : item to be added
     *
     * Returns:
     *      [bool] ; success = true
     */
    bool Push(int x) {
        if (Full()) {
            ContainerGrow();
        }

        if (!Full()) {
            A[++top] = x;
            
            return true;            
        }
        return false;
    }

    /**
     * Public void: ContainerGrow
     *
     * Description:
     *      Resizes the container for the stack by doubling
     *      its capacity
     *
     * Params:
     *      NULL
     *
     * Returns:
     *      NULL
     */
    void ContainerGrow() {
        int newSize = size * 2;       // double size of original
        int* B = new int[newSize];  // allocate new memory
        for (int i = 0; i < size; i++) {    // copy values to new array
            B[i] = A[i];
        }

        delete[] A;                // delete old array

        size = newSize;             // save new size

        maxsize = size;

        A = B;                      // reset array pointer

        static unsigned int pushcount = 0;
        pushcount++;
        //cout << "Count: " << pushcount << endl;
        sized = pushcount;

        }

    /**
     * Public void: ContainerGrow
     *
     * Description:
     *      Resizes the container for the stack by doubling
     *      its capacity
     *
     * Params:
     *      NULL
     *
     * Returns:
     *      NULL
     */
    void ContainerShrink() {
        int newSize = size / 2;       // half size of original
        int* C = new int[newSize];  // allocate new memory

        for (int i = 0; i < size; i++) {    // copy values to new array
            C[i] = A[i];
        }

        delete[] A;                // delete old array

        size = newSize;             // save new size

        A = C;                      // reset array pointer
    }

};

int main() {
    ArrayStack stack;
    
    int r = 0;

    ifstream fin("nums_test.dat");
    int num = 0;
    int max = 10;
    int count = 0;
    int evens = 0;
    int odds = 0;
    int last = 0;
   
        while (!fin.eof())
        {
            fin >> num;
            if (num % 2 == 0) {
                count++;
                evens++;
                last = 0;
                if (!stack.Push(num))
                {
                    cout << "Push failed" << endl;
                }
            }
            else {
                count--;
                odds++;
                last = 1;
                stack.Pop();
                
            }

            if (count >= max) {
                max *= 1.75;
            }
            
        }

        //cout << max << " " << evens << " " << odds << endl;
        cout << endl;

        stack.Display(); //Display Call

count = 0;
while (!stack.Empty())
{
    int x = stack.Pop();
    count++;
}
int fcount = count + 1;

if (fcount < size/2)
{
    stack.ContainerShrink();
}

}
