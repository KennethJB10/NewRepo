#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
    struct TrieNode* root;
    
};
struct TrieNode
{
    struct TrieNode* children[26];
    int flag;
};
struct TrieNode* createNode(){
    struct TrieNode* newNode = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    if(newNode){
        newNode->flag = 0;
        for(int i = 0; i<26; i++){
            newNode->children[i] = NULL;
        }
    }
    return newNode;
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie* newTrie = (struct Trie*) malloc(sizeof(struct Trie));
    if(newTrie){
        newTrie->root = createNode();
    }
    return newTrie;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    struct TrieNode* current = pTrie->root;
    int length = strlen(word);

    for( int i = 0; i< length; i++){
        int index = word[i]-'a'; // going off lowercase letters

        if(!current->children[index]){
            current->children[index] = createNode(); // if child does exsit creat a new node
        }

        current = current->children[index];        
    }

    // last node will be marked
    current->flag = 1;
}


// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct TrieNode* current = pTrie->root;
    int length = strlen(word);


    for(int i = 0; i<length; i++){
        int index = word[i] - 'a';

        if(!current->children[index]){
            return 0;
        }

        current = current->children[index];
    }

    // word is present in the Trie
    if(current->flag){
        return 1;//found
    }else{
        return 0;// not found
    }
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if(pTrie){
        for(int i = 0; i< 26; i++){
            if(pTrie->root->children[i])
                deallocateTrie(pTrie->root);
            
        }
        free(pTrie->root);
        free(pTrie);
    }
    
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE* fp = fopen(filename, "r");
    if(!fp){
        fprintf(stderr, "could not open file %s", filename);
    }

    char** words = (char**) malloc(256 *sizeof(char*));
    if(!words){
        fprintf(stderr, "Failed allocation");
    }

    int num = 0;
    char word[256];

    while(fgets(word, sizeof(word), fp)){
        size_t len = strlen(word);
        if(len > 0 && word[len -1] == '\n'){
            word[len -1] = '\0';
        }

        words[num] = strdup(word);
        if(!words[num]){
            fprintf(stderr,"failed allocation \n");
        }
        num++;
    }
    fclose(fp);
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie->root);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}