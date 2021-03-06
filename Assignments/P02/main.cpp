/**
 * This program uses a "getch" function which means "get character".
 * However, getch does not print the character to the terminal, it 
 * lets you decide what to do based on what character you are pressing.
 * 
 * You can test which characters are being pressed using thier ascii values. 
 * 
 * An ascii table here should be helpful 
 *      http://www.asciitable.com/
 * 
 * Some integer values for some keys:
 *      LowerCase Letters   = 97(a) -> 122(z)
 *      UpperCase Letters   = 65(A) -> 90(Z)
 *      Enter Key           = 10
 *      Space Bar           = 32
 *      
 *      Arrow Keys          = Have same values as some letters
 *                            so we can't distinguish between 
 *                            the two (in this context).
 * 
 * Code below is a basic example of using a "getch" function along with
 * searching an array of words for partial matches. 
 * 
 * https://repl.it/@rugbyprof/getchexample#main.cpp
 */

#include "getch.hpp"
#include "termcolor.hpp"
#include "JsonFacade.hpp"
#include "timer.hpp"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

/**
 * Description:
 *      Finds partial matches in an array of strings and returns them. It
 *      doesn't matter where in the string the match is.
 * Params:
 *      vector<string>  array       - array to search
 *      string          substring   - substring to search for in each word
 * 
 * Returns:
 *      vector<string> - holding all the matches to substring
 */
vector<string> findWords(vector<string> array, string substring, int pos) {
    vector<string> matches; // to hold any matches
    size_t found;           // size_t is an integer position of
                            // found item. -1 if its not found.

    for (int i = 0; i < array.size(); i++) { // loop through array
        found = array[i].find(substring);    // check for substr match
        if (found != string::npos) {         // if found >= 0 (its found then)
            matches.push_back(array[i]);     // add to matches
        }
    }

    return matches;
}

int main() {
    char k;                 // holder for character being typed
    string word = "";       // var to concatenate letters to
    vector<string> dictionary; // array of animal names
    vector<string> matches; // any matches found in vector of animals

    ofstream fout("temp.txt");

    Timer T;   // create a timer
    T.Start(); // start it
	JsonFacade J("dict_w_defs.json");   // create instance of json class
	vector<string> keys = J.getKeys();
    dictionary = keys;
	//animals = LoadAnimals("animal_names.txt");

    T.End(); // end the current timer

    // print out how long it took to load the animals file
    cout << T.Seconds() << " seconds to read in and print json" << endl;
    cout << T.MilliSeconds() << " milli to read in and print json" << endl;

    cout << "Type keys and watch what happens. Type capital Z to quit." << endl;

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

        // Find any animals in the array that partially match
        // our substr word
        T.Start(); // start it
        matches = findWords(dictionary, word, 0);
        T.End(); // end the current timer
        cout << T.Seconds() << " seconds to read in and print json" << endl;
        cout << T.MilliSeconds() << " milli to read in and print json" << endl;

        if ((int)k != 32) { // if k is not a space print it
            cout << "Keypressed: " << termcolor::on_yellow << termcolor::blue << k << " = " << (int)k << termcolor::reset << endl;
            cout << "Current Substr: " << termcolor::red << word << termcolor::reset << endl;
            cout << "Words Found: ";
            cout << termcolor::green;
            // This prints out all found matches
            for (int i = 0; i < 10; i++) {
                cout << matches[i] << " ";
            }
            cout << termcolor::reset << endl
                 << endl;
        }

    }

    return 0;
}
