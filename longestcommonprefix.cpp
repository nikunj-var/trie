//question link->https://leetcode.com/problems/longest-common-prefix/


//APPROACH 1
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string ans="";
        int n=strs.size();
        
        //for traversing all characters of first string
        for(int i=0;i<strs[0].size();i++){
            char ch=strs[0][i];
            bool match=true;
        
            //for comparing of character with rest of the string
            for(int j=1;j<n;j++){
                
                //not match
                if(strs[j].size()<i || ch!=strs[j][i]){
                    match=false;
                    break;
                }
            }
     
            if(match==false)
                break;
            else
                ans+=ch;
        }
        return ans;
    }
};


//APPROACH2-SOLUTION USING TRIE


//create trienode class
class trienode{
  public:
    char data;
    trienode* children[26];
    int childcount;
    int isterminal;
    trienode(){
       // data=ch;
        for(int i=0;i<26;i++){
            children[i]=NULL;
        }
        childcount=0;
        isterminal=false;
    }
     void markasleaf(){
            isterminal=true;
        }
        void unmarkasleaf(){
            isterminal=false;
        }
};

//create trie class and in insert function increase the childcount of the string
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
                        current->childcount++;
                    }
                    current=current->children[index];
                }
                current->markasleaf();
        }
    
    //function to store the longest common prefix
    void lcp(string str,string& ans){
     for(int i=0;i<str.length();i++){
         char ch=str[i];
         if(root->childcount==1){
             ans.push_back(ch);
             int index=ch-'a';
             root=root->children[index];
         }
         else{
             break;
         }
         if(root->isterminal)
             break;
        }   
    }
};

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
       trie *t=new trie();
          string ans="";
        
        //if there is any string empty then there is no longest common prefix string
         for(int i=0;i<strs.size();i++){
             if(strs[i].size()==0)
                 return ans;
         }
        
        //insert every element in trie
        for(int i=0;i<strs.size();i++){
            t->insertnode(strs[i]);
        }
        string first=strs[0];
      
        t->lcp(first,ans);
        
        return ans;
    }
};