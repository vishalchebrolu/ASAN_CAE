#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>
#define CHILDREN 63

struct TrieNode {
   struct TrieNode* child[CHILDREN];
   int index;
};

struct IndexNode {
   int parentIndex;
   int size;
   char **ptrAddr;
};

void init(struct IndexNode* Indices, int ptrCount) {
   for(int i = 0;i < ptrCount; i++) {
	Indices[i].parentIndex = -2;
 	Indices[i].size = 0;
	Indices[i].ptrAddr = NULL;
   }
   return;
}

int recvrFree(struct TrieNode* head, struct IndexNode* Indices, int ptrCount, char* ptrName)
{
   int j = getIndex(head, ptrName);
   int toFree = j;
   if(Indices[j].parentIndex == -2)
	return 1;
   else if(Indices[j].parentIndex >= 0)
	toFree = Indices[j].parentIndex;
   for(int i = 0; i < ptrCount;i++) {
	if(Indices[i].parentIndex == toFree) {
	    Indices[i].parentIndex = -2;
	    Indices[i].size = 0;
	} 
   }
   Indices[toFree].parentIndex = -2;
   Indices[toFree].size = 0;
   free(*Indices[toFree].ptrAddr);
   return 0;
}

void setRealloc(struct IndexNode* Indices,int ptrCount, int val, char* newAddr) {
   for(int i = 0;i < ptrCount;i++) {
	if(Indices[i].parentIndex == val) {
	   *Indices[i].ptrAddr = newAddr;
	   Indices[i].size *= 2;
	}
   }
   return;
}
struct TrieNode* getNode()
{
   struct TrieNode* nw = malloc(sizeof(struct TrieNode));
   for(int i = 0; i < CHILDREN;i++)
   {
	nw->child[i] = NULL;
   }
   nw->index = -1;
   return nw;
}

void insert(struct TrieNode* Head, char* str, int* index, struct IndexNode* Indices, char** ptrAddr)
{
   int n = strlen(str), offset;
   struct TrieNode* Crawl = Head;
   for(int i = 0;i < n;i++) {
        char ch = str[i];
        if(isupper(ch))
            offset = ch - 65;
        else if(islower(ch))
            offset = ch - 71;
        else if(isdigit(ch))
            offset = ch + 4;
        else if(ch == '_')
            offset = 62;
        if(!Crawl->child[offset])
             Crawl->child[offset] = getNode();
        Crawl = Crawl->child[offset];
   }
   Crawl->index = *index;
   Indices[*index].parentIndex = -2;
   Indices[*index].size = 0;
   Indices[*index].ptrAddr = ptrAddr;
   *index = *index + 1;
   return;
}

int  getIndex(struct TrieNode* head, char* str)
{
   int n = strlen(str), offset;
   struct TrieNode* Crawl = head;
   for(int i = 0;i < n;i++) {
	char ch = str[i];
        if(isupper(ch)) 
            offset = ch - 65;
        else if(islower(ch))
            offset = ch - 71;
        else if(isdigit(ch))
            offset = ch + 4;
        else if(ch == '_')
            offset = 62;
        else
	    return -1;
	if(!Crawl->child[offset])
	    return -1;
        Crawl = Crawl->child[offset];
   }
   return Crawl->index;
}
