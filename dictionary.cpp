// Dictionary.cpp

// This is a correct but horribly inefficient implementation of Dictionary
// functionality.  Your job is to change DictionaryImpl to a more efficient
// correct implementation.  You can change it any way you like, subject to
// restrictions in the spec (e.g., that the only C++ library container you
// are allowed to use are vector, list, stack, and queue (and string); if you
// want anything fancier, implement it yourself).

#include "Dictionary.h"
#include <string>
#include <list>
#include <vector>
#include <cctype>
#include <algorithm>
using namespace std;

void removeNonLetters(string& s);
void generateNextPermutation(string& permutation);
const int NUM_BUCKETS = 49957;



class Word
{
public:
    Word(string letters){
        data = letters;
        sorted = data;
        sort(sorted.begin(), sorted.end());
    }
    string sorted; //
    string data; //
private:
    
};

class Bucket
{
public:
    vector<Word> words;
    void add(string word)
    {
        Word letters(word);
        words.push_back(letters);
    }

    
};

int turnPrime(char a);

class DictionaryImpl
{
  public:
    DictionaryImpl() {}
    ~DictionaryImpl() {}
    int hashFunc(string& word) const
    {
        unsigned long space = 1;
        
        for(int k = 0; k < word.size(); k++)
        {
            space *= turnPrime(word[k]);        //generate unique number
        }
        
        space = space % NUM_BUCKETS;    //make within bounds of array
        return space;
     
    }
    void insert(string word);
    void lookup(string letters, void callback(string)) const;
  private:
    Bucket dict[NUM_BUCKETS];
  
};


int turnPrime(char a) //use prime numbers corresponding to each letter to create unique key
{
    switch(a)
    {
        case 'a':
            return 5;
            break;
        case 'b':
            return 71;
            break;
        case 'c':
            return 37;
            break;
        case 'd':
            return 29;
            break;
        case 'e':
            return 2;
            break;
        case 'f':
            return 53;
            break;
        case 'g':
            return 59;
            break;
        case 'h':
            return 19;
            break;
        case 'i':
            return 11;
            break;
        case 'j':
            return 83;
            break;
        case 'k':
            return 79;
            break;
        case 'l':
            return 31;
            break;
        case 'm':
            return 43;
            break;
        case 'n':
            return 13;
            break;
        case 'o':
            return 7;
            break;
        case 'p':
            return 67;
            break;
        case 'q':
            return 97;
            break;
        case 'r':
            return 23;
            break;
        case 's':
            return 17;
            break;
        case 't':
            return 3;
            break;
        case 'u':
            return 41;
            break;
        case 'v':
            return 73;
            break;
        case 'w':
            return 47;
            break;
        case 'x':
            return 89;
            break;
        case 'y':
            return 61;
            break;
        case 'z':
            return 101;
            break;
        default:
            return 0;
            
    }
    return 0;
}

void DictionaryImpl::insert(string word)
{
    removeNonLetters(word);
    if ( ! word.empty())
    {
        int space = hashFunc(word); //find Bucket
        dict[space].add(word);  //call that Bucket's add
    }
}

void DictionaryImpl::lookup(string letters, void callback(string)) const
{
    if (callback == nullptr)
        return;

    removeNonLetters(letters); //check there's still a word
    if (letters.empty())
        return;

    int space = hashFunc(letters); //find Bucket would/should belong in
    string orig = letters;
    sort(orig.begin(), orig.end()); //sort input/searched for word
    string anag;
    
    for(vector<Word>::const_iterator it = dict[space].words.begin(); it != dict[space].words.end(); it++)
    {
        anag = (*it).sorted;
       
        if(anag == orig)            //sorted anagrams should be identical: if match, callback data (non sorted)
            callback((*it).data);
    }
    
    
    
   
}
    
void removeNonLetters(string& s)
{
    string::iterator to = s.begin();
    for (string::const_iterator from = s.begin(); from != s.end(); from++)
    {
        if (isalpha(*from))
        {
            *to = tolower(*from);
            to++;
        }
    }
    s.erase(to, s.end());  // chop off everything from "to" to end.
} 


//******************** Dictionary functions **********************************

// These functions simply delegate to DictionaryImpl's functions.
// You probably don't want to change any of this code.

Dictionary::Dictionary()
{
    m_impl = new DictionaryImpl;
}

Dictionary::~Dictionary()
{
    delete m_impl;
}

void Dictionary::insert(string word)
{
    m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
    m_impl->lookup(letters, callback);
}
