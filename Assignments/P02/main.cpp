///////////////////////////////////////////////////////////////////////////////
// 
// Author:           Kyle Gordon
// Email:            kylekgordon@gmail.com
// Label:            P02
// Title:            Processing in Linear Time
// Course:           3013-Algorithms
// Semester:         Spring 2021
//
// Description:
// 	This program uses a "getch" function which means "get character".
// 	However, getch does not print the character to the terminal, it 
//	lets you decide what to do based on what character you are pressing.
// 
//Some integer values for some keys:
//     LowerCase Letters   = 97(a) -> 122(z)
//     UpperCase Letters   = 65(A) -> 90(Z)
//     Enter Key           = 10
//     Space Bar           = 32
//      
//      Arrow Keys          = Have same values as some letters
//                            so we can't distinguish between 
//                            the two (in this context).
// Usage:
//      Run the program and it reads the dictionary from the file dict_w_defs.json.
//
// Files:     
//      main.cpp    : driver program
//		timer.hpp       : used to time operation functionality
//      JsonFacade.hpp  : helper class for json.hpp class from NLOHMANN
//      mygetch.hpp     : read in input from keyboard without display
/////////////////////////////////////////////////////////////////////////////////

#include "getch.hpp"
#include "termcolor.hpp"
#include "JsonFacade.hpp"
#include "timer.hpp"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct wordNode {
    string Word;            //word in dictionary
    string Definition;      //definition of word (not used)
    wordNode* Next;     	// Link to next node
	//constructor			
    wordNode()
    {
    	Word = " ";;
    	Next = NULL;
	}
	
    // constructor
    wordNode(string S) 
	{
        Word = S;
        Next = NULL;
    }
};

 /**
 * Class Dictionary
 * 
 * Description:
 *      Used to create the linked list using words from the json dictionary
 * 
 * Public Methods:
 *      - constructors:
 *          Dictionary            : default constructor
 *          Dictionary(vector<string>)
 *                                : overload constructor 
 *                                with vectors for disctionary
 * 
 * Private Methods:
 *      - A list of 
 *      - each private method
 *      - with return types
 * 
 * Usage: 
 * 
 *      - examples of how
 *      - to use your class 
 *      
 */

class Dictionary
{
	private:
		int size;
		wordNode * head; //pointer
    	wordNode * curr;
	
	public:
		Dictionary() //constructor
		{
			head = curr = NULL;
			size = 0;
		}
		
		Dictionary(vector<string> wordsD) //constructor
		{
			head = new wordNode();
			curr = head;
			
			for(int i = 0; i <wordsD.size();i++)
			{
				curr ->Next= new wordNode(wordsD[i]);
				curr = curr -> Next;
			}
		}

/**
 * Description:
 *      Finds partial matches in the linked list of strings and returns them.
 * Params:
 *      string substring - substring to search for in each word
 * 
 * Returns:
 *      print out of the vector<string> matches- holding all the matches to substring
 */
		
	void findWord(string substring) 
	{
    curr = head->Next;
	
	string word;
	vector<string> matches; //vector<string> matches;
	int found = 1;
	int num = 0;
	
	//loop through list
	Timer F;
	F.Start();
	while(curr->Next != NULL) 
	{ 
		word = curr->Word;
			//compare current word at index to current searched string
		if (word.compare(0, substring.size(), substring) == 0)
		{
			matches.push_back(word);
		}
		curr = curr->Next;
	}
	F.End();
	
	if(matches.size() != 0){
	cout << fixed << matches.size() << " words found in " << setprecision(3) << termcolor::red << F.Seconds()  << termcolor::reset << " seconds" << endl;
	cout << "Words Found: ";
    cout << termcolor::green;
	// This prints out all found matches
    if(matches.size() > 10)
    {
        for (int i = 0; i < 10 ; i++) 
		{
            cout << matches[i] << " ";
        }
	}
	else
	{
		for (int i = 0; i < matches.size() ; i++) 
		{
            cout << matches[i] << " ";
        }
	}
	
	}else
	{
		cout << termcolor::red << "No word found!" << endl;
	}
    cout << termcolor::reset << endl
        << endl;
	
	}	
};

int main() {
    char k;                 	// holder for character being typed
    string word = "";       	// var to concatenate letters to

    vector<string> dictionaryW, dictionaryD; // array of words and definition
    vector<string> matches; 	// any matches found in vector of animals
    JsonFacade J("dict_w_defs.json");
    
   	dictionaryW = J.getKeys();
   	//dictionaryD = J.getValue();
    
    Timer T;   // create a timer
    T.Start(); // start it
    Dictionary W(dictionaryW);
    T.End(); // end the current timer

    // print out how long it took to load the dictionary file
    cout << T.Seconds() << " seconds to read in and print json" << endl;
    cout << T.MilliSeconds() << " milli to read in and print json" << endl
        << endl;

    cout << "Type keys to seach for words. Type capital Z to quit." << endl
        << endl;

    // While capital Z is not typed keep looping
    while ((k = getch()) != 'Z') {
        
        // Tests for a backspace and if pressed deletes
        // last letter from "word".
        if ((int)k == 127) {
            if (word.size() > 0) {
                word = word.substr(0, word.size() - 1);
            }
        } else {
            // Make sure a letter was pressed and only letter
            if (!isalpha(k)) {
                cout << "Letters only!" << endl;
                continue;
            }

            // We know its a letter, lets make sure its lowercase.
            // Any letter with ascii value < 97 is capital so we
            // lower it.
            if ((int)k < 97) {
                k += 32;
            }
            word += k; // append char to word
            
        }

     
        if ((int)k != 32) 
		{ 	// if k is not a space print it
            cout << "Keypressed: " << termcolor::on_yellow << termcolor::blue << k << " = " << (int)k << termcolor::reset << endl;
            cout << "Current Substr: " << termcolor::red << word << termcolor::reset << endl;
			
        	// This finds and puts out all found matches
			W.findWord(word);
		
        }
    }
    return 0;
}
