///////////////////////////////////////////////////////////////////////////////
// 
// Author:           Kyle Gordon
// Email:            kylekgordon@gmail.com
// Label:            P04
// Title:            Processing in Trie Tree Time
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
//      getch.hpp     : read in input from keyboard without display
/////////////////////////////////////////////////////////////////////////////////

#include "getch.hpp"
#include "termcolor.hpp"
#include "JsonFacade.hpp"
#include "timer.hpp"
#include <fstream>
#include <iostream>
#include <time.h>
#include <vector>

using namespace std;

const int ALPHABET_SIZE = 26; 


struct wordNode 
{ 
    struct wordNode *children[ALPHABET_SIZE]; 
  
    // isEndOfWord is true if the node represents 
    // end of a word 
    bool isEndOfWord; 
}; 

// Returns new node of the trie(initialized to NULLs) 
struct wordNode *getNode(void) 
{ 
    struct wordNode *pNode =  new wordNode; 
  
    pNode->isEndOfWord = false; 
  
    for (int i = 0; i < ALPHABET_SIZE; i++) 
        pNode->children[i] = NULL; 
  
    return pNode; 
} 
  
// If not present, inserts key into trie 
// If the key is prefix of trie node, just 
// marks leaf node 
void insert(struct wordNode *root, string substring) 
{ 
    struct wordNode *pCrawl = root; 
  
    for (int i = 0; i < substring.length(); i++) 
    { 
        int index = substring[i] - 'a'; 
        if (!pCrawl->children[index]) 
            pCrawl->children[index] = getNode(); 
  
        pCrawl = pCrawl->children[index]; 
    } 
  
    // mark last node as leaf 
    pCrawl->isEndOfWord = true; 
} 

// function to check if current node is leaf node or not
bool isLeafNode(struct wordNode* root)
{
    return root->isEndOfWord != false;
}

/**
 * Description:
 *      Finds partial matches in the linked list of strings and returns them.
 * Params:
 *      string substring - substring to search for in each word
 * 
 * Returns:
 *      print out  substring
 */
bool findWord(struct wordNode *root, string substring, int level) 
{ 
    struct wordNode *pCrawl = root;
    
    // If node is leaf node, it indicates end
    // of string, so a null character is added
    // and string is displayed
    if (isLeafNode(root))
    {
        pCrawl->children[level] = NULL;
        cout << substring << endl;
    }

  //loop through list
	Timer F;
	F.Start();
    for (int i = 0; i < substring.length(); i++) 
    { 
        int index = substring[i] - 'a'; 
        if (!pCrawl->children[index])
        {
            return false;
        }
        else
        {
            for (i = 0; i < ALPHABET_SIZE; i++)
            {
         
            substring[level] = i + 'a';
            findWord(root->children[i], substring, level + 1);
            }
        }
  
        pCrawl = pCrawl->children[index];
        
    }
    
    F.End();
//	
//	if(matches.size() != 0){
//	cout << fixed << matches.size() << " words found in " << setprecision(3) << termcolor::red << F.Seconds()  << termcolor::reset << " seconds" << endl;
//	cout << "Words Found: ";
//    cout << termcolor::green;
//	// This prints out all found matches
//    if(matches.size() > 10)
//    {
//        for (int i = 0; i < 10 ; i++) 
//		{
//            cout << matches[i] << " ";
//        }
//	}
//	else
//	{
//		for (int i = 0; i < matches.size() ; i++) 
//		{
//            cout << matches[i] << " ";
//        }
//	}
//	
//	}else
//	{
//		cout << termcolor::red << "No word found!" << endl;
//	}
//    cout << termcolor::reset << endl
//        << endl;
//	
//	}
//  
    return (pCrawl != NULL && pCrawl->isEndOfWord); 
}

//void findWord(struct wordNode* root,string substring, int depth){
//    if (depth == length(substring)){
//        suffix = empty_string
//        printWord(suffix, substring, root)
//    } else {
//        letter = prefix[depth]
//        if (node.hasChild(letter)){
//            findWord(prefix, root.getChild(letter), depth+1)
//        } else { // no word with the correct prefix
//            return
//        }
//    }
//}
//
//void printWord(suffix, substring, root){
//    if (root.isCompleteWord){
//        cout << (substring + suffix) << endl;
//    }
//    for each letter c in the alphabet {
//        if (root.hasChild(c)){
//            printWord( suffix + c,substring, root.getChild(c))
//        }
//    }
//}



	

int main() {
    char k;                 	// holder for character being typed
    string word = "";       	// var to concatenate letters to

    vector<string> dictionaryW, dictionaryD, temp; // array of words and definition
    vector<string> matches; 	// any matches found in vector of animals
    
	JsonFacade J("dict_w_defs.json");
   	temp = J.getKeys();
    dictionaryW = J.getKeys();
   int j = 0;
   int i = 0;
	
    int n = J.getSize();
	

    cout << temp[120];

system("pause");
    Timer T;   // create a timer
    T.Start(); // start it
    struct wordNode *root = getNode();
     // Construct trie
    for (int i = 120; i < 400; i++)
		//cout << dictionaryW[50];
    	insert(root, dictionaryW[i]);
    	
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
            int level = 0;
            findWord(root, word, level);
           
            
            //display(root, word, level);
        }
    }
    return 0;
}
