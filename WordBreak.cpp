// A recursive program to print all possible 
// partitions of a given string into dictionary 
// words and the dictionary words are stored in a trie 
// so that accessing time is O(lengthOfLongestWord) 
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>

using namespace std; 
const int ALPHABET_SIZE = 58; 

// trie node 
struct TrieNode 
{ 
	struct TrieNode *children[ALPHABET_SIZE]; 
	bool isEndOfWord; //true if the current word marks the end of a word
}; 

// Create new trie nodes initialised to null
struct TrieNode *getNode(void) 
{ 
	struct TrieNode *pNode = new TrieNode; 

	pNode->isEndOfWord = false; 

	for (int i = 0; i < ALPHABET_SIZE; i++) 
		pNode->children[i] = NULL; 

	return pNode; 
} 

// If not present, inserts key into trie 
// If the key is prefix of trie node, just 
// marks leaf node 
void insert(struct TrieNode *root, string dictWord) 
{ 
	struct TrieNode *pCrawl = root; 

	for (unsigned int i = 0; i < dictWord.length(); i++) 
	{ 
		int ascii = dictWord[i];
		int index=0;
		if(ascii==39){
			index = 0;
		} else if(ascii==46){
			index = 1;
		}else if(ascii==33){
			index = 2;
		}else if(ascii==63){
			index = 3;
		}else if(ascii==59){
			index = 4;
		}else if(ascii==44){
			index = 5;
		}else if(ascii>=65 && ascii <=90){
			index = dictWord[i]-'A'+6;
		}else if(ascii>=97 && ascii<=122){
			index = dictWord[i]-'a'+32;
		}
		if (!pCrawl->children[index]) 
			pCrawl->children[index] = getNode(); 

		pCrawl = pCrawl->children[index]; 
	} 

	// mark last node as end of word 
	pCrawl->isEndOfWord = true; 
} 

// Returns true if word is present in trie
bool search(struct TrieNode *root, string dictWord) 
{ 
	struct TrieNode *pHead = root; 

	for (unsigned int i = 0; i < dictWord.length(); i++) 
	{ 
		int ascii = dictWord[i];
		int index=0;
		if(ascii==39){
			index = 0;
		} else if(ascii==46){
			index = 1;
		}else if(ascii==33){
			index = 2;
		}else if(ascii==63){
			index = 3;
		}else if(ascii==59){
			index = 4;
		}else if(ascii==44){
			index = 5;
		}else if(ascii>=65 && ascii <=90){
			index = dictWord[i]-'A'+6;
		}else if(ascii>=97 && ascii<=122){
			index = dictWord[i]-'a'+32;
		}
		if (!pHead->children[index]) 
			return false; 

		pHead = pHead->children[index]; 
	} 

	return (pHead != NULL && pHead->isEndOfWord); 
} 

void wordBreakUtil(string str, int size, string result, TrieNode *root); 

// Prints all possible word breaks of given string 
void wordBreak(string str, TrieNode *root) 
{ 
	wordBreakUtil(str, str.size(), "", root); 
} 

// result store the current prefix with spaces 
void wordBreakUtil(string str, int n, string result, TrieNode *root) 
{  
	for (int i=1; i<=n; i++) 
	{ 
		//extract substring from 0 to i in prefix 
		string prefix = str.substr(0, i); 
		if (search(root, prefix)) 
		{ 
			// if no more elements are there, print it 
			if (i == n) 
			{ 
				// add this element to previous prefix 
				result += prefix; 
				cout << result << endl; //print result 
				return; 
			} 
			wordBreakUtil(str.substr(i, n-i), n-i, 
								result + prefix + " ",root); 
		} 
	}
} 

int main() 
{ 
	struct TrieNode *root = getNode(); 
	ifstream dict("dictionary.txt");
	string line;
	insert(root,"!");
	insert(root,"?");
	insert(root,".");
	insert(root,";");
	insert(root,",");
  while (getline(dict, line)) {
	if(line.substr(0,1).compare("#")!=0){
		if(line.size()>1)
			insert(root, line);
		else{
			if(line.substr(0,1).compare("A")==0||line.substr(0,1).compare("I")==0||line.substr(0,1).compare("A")==0)
		 	insert(root, line);
		}
	}
  }
  ifstream infile("infile.txt");
  while (getline(infile, line)) {
	  wordBreak(line,root);
  } 
	return 0; 
} 
