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

// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

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

/**
* Description:
*       If not present, inserts key into trie
*       If the key is prefix of trie node, just marks leaf node 
* Params:
*      string word - substring to search for in each word
*
* Returns:
*      trie tree
*/
void insert(struct wordNode *root, const string word) 
{ 
    struct wordNode *pCrawl = root; 
  
    for (int i = 0; i < word.length(); i++) 
    { 
        int index = CHAR_TO_INDEX(word[i]); //int index = word[i] - 'a'; 
        if (!pCrawl->children[index]) 
            pCrawl->children[index] = getNode(); 
  
        pCrawl = pCrawl->children[index]; 
    } 
  
    // mark last node as leaf 
    pCrawl->isEndOfWord = true; 
} 

/**
 * Description:
 *     function to check if current node is leaf node or not
 * Params:
 *      root - current node
 *
 * Returns:
 *      true or false (0 or 1)
 */
// 
bool isLeafNode(struct wordNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return 0;
    return 1;
    //return root->isEndOfWord != false;
}

/**
 * Description:
 *      Recursive function to print finding for given
 *      node
 * Params:
 *      string substring - substring to search for in each word
 *
 * Returns:
 *      print out substring
 */
void recTrie(struct wordNode* root, string substring)
{
    int count = 0;
    // found a string in Trie with the given prefix
    if (root->isEndOfWord)
    {
        cout << termcolor::green;
        cout << substring << " ";
        
    }

    // All children struct node pointers are NULL
    if (isLeafNode(root))
        return;

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i])
        {
            // append current character to currPrefix string
            substring.push_back(97 + i);

            // recur over the rest
            recTrie(root->children[i], substring);
            // remove last character
            substring.pop_back();
        }
    }
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
int findWord(wordNode *root, const string substring)
{ 
    struct wordNode *pCrawl = root;
    int i;

    int n = substring.length();
    // If node is leaf node, it indicates end
    // of string, so a null character is added
    // and string is displayed
	Timer F;
	F.Start();
    for (i = 0; i < n; i++) 
    { 
        int index = CHAR_TO_INDEX(substring[i]);  //int index = substring[i] - 'a'; 
        if (!pCrawl->children[index])
        {
            return 0;
        }
        else
        {
            pCrawl = pCrawl->children[index];
        }
    }
   
    // If prefix is present as a word.
    bool isWord = (pCrawl->isEndOfWord == true);

    // If prefix is last node of tree (has no
    // children)
    bool isLast = isLeafNode(pCrawl);
    
    F.End();
    cout << fixed << "Words found in " << setprecision(3) << termcolor::red << F.Seconds() 
        << termcolor::reset << " seconds" << endl;
    cout << "Words Found: ";
    
    // If prefix is present as a word, but
    // there is no subtree below the last
    // matching node.
    if (isWord && isLast)
    {

        cout << substring << " ";
        return -1;
    }

    // If there are are nodes below last
    // matching character.
    if (!isLast)
    {
        string prefix = substring;
        recTrie(pCrawl, prefix);
       
        return 1;
    }
   
}


int main() {
    char k;                 	// holder for character being typed
    string word = "";       	// var to concatenate letters to

    vector<string> dictionaryW, dictionaryD; // array of words and definition
    vector<string> matches; 	// any matches found in vector of matches
    
	JsonFacade J("dict_w_defs.json");

    dictionaryW = J.getKeys();
	
    int n = J.getSize();

    //cout << dictionaryW[n-1] << endl;
    //cout << n << endl;
    system("pause");
    Timer T;   // create a timer
    T.Start(); // start it
    struct wordNode *root = getNode();
     // Construct trie
    for (int i = 120; i < n-1; i++)
    {
        insert(root, dictionaryW[i]);
    }
    	
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
        
            cout << termcolor::reset << endl << endl;
            cout << "Keypressed: " << termcolor::on_yellow << termcolor::blue << k << " = " << (int)k 
                << termcolor::reset << endl;
            cout << "Current Substr: " << termcolor::red << word << termcolor::reset << endl;
            
        	// This finds and puts out all found matches
            //int level = 0;
            int find = findWord(root, word);
           
            if (find == -1)
                cout << "No other strings found with this prefix" << endl;

            else if (find == 0)
                cout << "No string found with this prefix" << endl;
        }
    }
    return 0;
}
