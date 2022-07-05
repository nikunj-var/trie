//what is trie?
//A Trie is a special data structure used to store strings that can be visualized like a graph. It consists of nodes and edges. Each node consists of at max 26 children and edges connect each parent node to its children.


#include<iostream>
#include <bits/stdc++.h>
using namespace std;

//#define n 26
//trienode class
class trienode{
    public:
        trienode* children[26];
        bool isterminal;
        trienode(){
            isterminal=false;
            for(int i=0;i<26;i++){
                children[i]=NULL;
            }
        }
        void markasleaf(){
            isterminal=true;
        }
        void unmarkasleaf(){
            isterminal=false;
        }
};

//trie class
class trie{
    trienode *root;
    public:
        trie(){
            root=new trienode();
        }
        int getindex(char t){
            return t-'a';
        }

        //function to insert node in trie
        void insertnode(string key){
            if(key.empty())
                return;

                //using transform to convert into lowercase to all the characters
                transform(key.begin(),key.end(),key.begin(),::tolower);
                trienode* current=root;
                int index=0;

                //iterate the trie with the given index
                for(int i=0;i<key.length();i++){
                    index=getindex(key[i]);
                    if(current->children[index]==NULL){
                        current->children[index]=new trienode();
                        cout<<key[i]<<"inserted"<<endl;
                    }
                    current=current->children[index];
                }
                current->markasleaf();
        }
        //function to check current node has children or not
        bool hasnochildren(trienode* current){
            for(int i=0;i<26;i++){
                if(current->children[i]!=NULL)
                    return false;
            }
            return true;
        }

        //function to delete trie node
        bool deletenode(string key,trienode* current,int length,int i){
            bool deletedself=false;
            if(current==NULL)
            {
                cout<<"key doesnot exist";
                return false;
            }
            if(i==length){
                if(hasnochildren(current)){
                    delete current;
                    current=NULL;
                    deletedself=true;
                }
                else{
                    current->unmarkasleaf();
                    deletedself=false;
                }
            }
            else{
                trienode* child=current->children[getindex(key[i])];
                bool childdeleted=deletenode(key,child,length,i+1);
                if(childdeleted){
                    current->children[getindex(key[i])]=NULL;
                    if(current->isterminal)
                        deletedself=false;
                    else if(!hasnochildren(current)){
                        deletedself=false;
                    }    
                    else{
                        current=NULL;
                        deletedself=true;
                    }
                }
                else{
                    deletedself=false;
                }
            }
            return deletedself;
        }

        //function to search node
        bool searchnode(string key){
            if(key.empty())
                return false;
            transform(key.begin(),key.end(),key.begin(),::tolower);
            trienode* current=root;
            int index=0;
            for(int i=0;i<key.length();i++){
                index=getindex(key[i]);
                if(current->children[index]==NULL)
                    return false;
                current=current->children[index];    
            }    
            if(current!=NULL && current->isterminal)
                return true;
            return false;    
        }
};


int main()
{
    // Input keys (use only 'a' through 'z'
    // and lower case)
    string keys[] = {"the", "a", "there",
                    "answer", "any", "by",
                     "bye", "their" };
    int n = sizeof(keys)/sizeof(keys[0]);
    trie* root=new trie();
    for(int i=0;i<n;i++){
        root->insertnode(keys[i]);
    }
    cout<<root->searchnode("there");
}
  