#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

//defining structure of the node.
typedef struct firstTrie{
    struct firstTrie* children[26];
    bool isCompleted;
}trie;

//declaring root as global so that initial pointer can be accessed anywhere.
trie* root;

//it will initialize the values of the node.
void initialize(trie* treeNode){
    for(int i = 0; i < 26; i++){
        treeNode -> children[i] = NULL;
    }
    treeNode -> isCompleted = false;
}

//In this we declare a child and at the root's children array at that index
//we will allocate the memory and store the charater and do same until the word ends.
//when word complete we change the isCompleted to true for that index so that later we can find it is 
// a word not a prefix.
bool insert_trie(char name[45]){

    //allocate memory to root
    root = malloc(sizeof(trie));
    if(root == NULL)
        printf("Root cannot be initialized\n");
    //initializing the root
    initialize(root);

    int length = strlen(name);
    int index;

    trie* child = root;

    //it will traverse on every word in the name array and store it in trie.
    int i = 0;
    for(i = 0; i < length; i++){

        //it will find the index of the word.
        index = (int)name[i] - (int)'a';

        //if the index at that word's place is null it means no word exist there and we can
        // store our word there.
        if(child -> children[index] == NULL){

            //hence we have to store the word we have to allocate the memory 
            //and have to initialize it as null.
            child -> children[index] = malloc(sizeof(trie));
            if(child -> children[index] == NULL)
                printf("child's children array at index %d cannot be initialized\n", index);
                initialize(child -> children[index]);
        }

        //after storing we will move to that children
        child = child -> children[index];
    }

    //after storing all the words we maintain a isCompleted variable which 
    //will tell us that fors is finished.
    child -> isCompleted = true;

    return (i == length);
}

//it will find whether the word is present in our trie/data or not.
bool find(char fname[45]){
    int len = strlen(fname);
    trie* child = root;
    int ind;
    for(int i = 0; i <len; i++){
        ind = (int)tolower(fname[i] - (int)'a');

        child = child -> children[ind];
        if(child == NULL){
            return false;
        }
    }
    return (child -> isCompleted);
}

int main(){
    char name[45];
    char fname[45];
    printf("Enter string to insert:\n");
    scanf("%s", name);

    if(insert_trie(name))
        printf("%s Inserted\n", name);
    else
        printf("Error!!\n");

    printf("Enter string to find:\n");
    scanf("%s", fname);

    if(find(fname))
        printf("%s found!!", fname);
    else
        printf("%s not found!!", fname);
    return 0;
}