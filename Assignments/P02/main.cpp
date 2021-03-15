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
/////////////////////////////////////////////////////////////////////////////////



struct Words
{
    string Word;            //word in dictionary
    string Definition;      //definition of word
    // default constructor
    Words() 
    {
        Word = " ";
        Definition = " ";
    }
    // overloaded constructor
    Words(string w, string d)
    {
        Word = w;
        Definition = d;
    }
};


struct wordNode {
    Words Data;    // Word struct
    wordNode* Next;     // Link to next node
    // constructor
    wordNode(Words S) {
        Data = S;
        Next = NULL;
    }
};

/**
 * Description:
 *      Finds partial matches in an array of strings and returns them.
 * Params:
 *      vector<string>  array       - array to search
 *      string          substring   - substring to search for in each word
 * 
 * Returns:
 *      vector<string> - holding all the matches to substring
 */
vector<string> findWords(vector<string> array, string substring) {
    vector<string> matches; // to hold any matches
    size_t found;           // size_t is an integer position of
                            // found item. -1 if its not found.

    for (int i = 0; i < array.size(); i++) { // loop through array
        found = array[i].find(substring);    // check for substr match
        if (found != string::npos) {         // if found >= 0 (its found then)
        if(int(found) == 0){				//if word found begins with substring
		matches.push_back(array[i]);     // add to matches
		}
            
    	}
    }
    return matches;
}

int main() {
    char k;                 // holder for character being typed
    string word = "";       // var to concatenate letters to

    vector<string> dictionaryW; // array of words names
    vector<string> matches; // any matches found in vector of animals
    
    ofstream fout("temp.txt");

    Timer T;   // create a timer
    T.Start(); // start it
	
     // create instance of json class
    JsonFacade J("dict_w_defs.json");
    Words* WArray = new Words[J.getSize()];
    //cout << J.getSize();
    int i = 0;                  // init counter
    while (i < J.getSize()) {          // while more stuff to read
        
        WArray[i].Word = J.getKey(i);   // read the Word into the Words
        dictionaryW.push_back(WArray[i].Word);                        //    at array location i
        WArray[i].Definition = J.getValue(J.getKey(i));     // read the Definition into the Words
                                //    at array location i
        ++i;                    // increment our counter
    }

    T.End(); // end the current timer

    //Test Array
    //cout << WArray[10].Word << endl;
    //cout << WArray[10].Definition << endl;

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

        // Find any words in the array that partially match
        // our substr word
        T.Start(); // start it
        matches = findWords(dictionaryW, word);
        T.End(); // end the current timer
        //cout << T.Seconds() << " seconds to read in and print json" << endl;
        //cout << T.MilliSeconds() << " milli to read in and print json" << endl;

        if ((int)k != 32) { // if k is not a space print it
            cout << "Keypressed: " << termcolor::on_yellow << termcolor::blue << k << " = " << (int)k << termcolor::reset << endl;
            cout << "Current Substr: " << termcolor::red << word << termcolor::reset << endl;
            cout << fixed << matches.size() << " words found in " << setprecision(3) << termcolor::red << T.Seconds() << 
		    termcolor::reset << " seconds" << endl;
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
