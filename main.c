#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Trie {
    int num;
    struct Trie* next[26];
};

// takes in a word to insert
void insert(struct Trie **ppTrie, char *word){

    struct Trie *temp = *ppTrie; // temp node will be the new thing added
    if (temp == NULL) { // if there is nothing in the trie to start, like the root is empty, then create a new node to hold its place
        temp = (struct Trie *) malloc(sizeof(struct Trie));
        temp->num = 0;

        for(int i=0; i<26; i++) {
            temp->next[i] = NULL;
        }
        *ppTrie = temp; // setting temp to the ppTrie for traversal
    }
    for(int i=0; i<strlen(word); i++) {
        int nextIndex = word[i] - 'a'; // finding index of the current letter
        if(temp->next[nextIndex]==NULL) {
            temp->next[nextIndex] = (struct Trie*) malloc(sizeof(struct Trie));
            temp->next[nextIndex]->num=0;
            for(int j=0; j<26; j++) {
                temp->next[nextIndex]->next[j] = NULL;
            }
        }
        temp = temp->next[nextIndex];
    }
    temp->num++;
}


int numberOfOccurances(struct Trie *pTrie, char *word){
    if(pTrie==NULL) { // if there is nothing in the trie, it must be null, therefore there is no occurence
        return 0;
    }
    struct Trie *temp = pTrie; // another temp variable to traverse
    for(int i=0; i<strlen(word); i++) {
        int nextIndex = word[i] - 'a';
        if(temp->next[nextIndex]==NULL) {
            return 0;
        }
        temp = temp->next[nextIndex];

    }
    return temp->num;

}

struct Trie *deallocateTrie(struct Trie *pTrie){ // freeing the data
    if (pTrie == NULL) {
        return NULL; // no need to free nonexistant data
    }

    for (int i = 0; i < 26; i++) {
        pTrie->next[i] = deallocateTrie(pTrie->next[i]);
    }

    free(pTrie);
    return NULL;
}

int main(void)
{
    int words;
    printf("How many words in dictionary?\n");
    scanf("%d", &words);
    struct Trie *trie = NULL;
    char word[101];
    for (int i = 0; i < words; i++) {
        scanf(" %s", word);
        insert(&trie, word);
    }
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i=0;i<5;i++)
    {
        printf("\t%s : %d\n",pWords[i], numberOfOccurances(trie, pWords[i]));
    }
    trie = deallocateTrie(trie);
    if (trie != NULL)
        printf("There is an error in this program\n");
    return 0;
}






