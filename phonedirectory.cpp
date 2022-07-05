// steps:
// 1-create a trie and insert all the strings in trie.
// 2-call get suggestions to take all the suggestions from the strings.
// 3-create a string named prefix which maintains the prefix of the output string.
// 4-take a variable 'lastchar' which stores last character of prefix.
// 5-take two pointers prev and current in which prev points to the previous node and current points to the rest nodes

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
   
    public:
        trienode *root=NULL;
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
                        //cout<<key[i]<<"inserted"<<endl;
                    }
                    current=current->children[index];
                }
                current->markasleaf();
        }
    void printsuggestions(trienode* current,  vector<string>& temp,string prefix)
{
    if(current->isterminal)
        temp.push_back(prefix);
   
    for(char ch='a' ; ch<='z' ; ch++){    
        trienode* next=current->children[ch-'a'];
        
        if(next!=NULL){
            prefix.push_back(ch);
            printsuggestions(next,temp,prefix);
            prefix.pop_back();
        }
    }
}
 vector<vector<string>> getsuggestions(string str){
    trienode* prev=root;
        
    //to store ans    
    vector<vector<string>> output;
        
    //to maintain prefix    
    string prefix="";
      
        
    for(int i=0;i<str.length();i++){
        char lastch=str[i];
        prefix.push_back(lastch);
        
        //check for lastch
        trienode* current=prev->children[lastch-'a'];
        
        //if not found
        if(current==NULL)
            break;
        
        //if found
        vector<string> temp;
        printsuggestions(current,temp,prefix);
        output.push_back(temp);        
        temp.clear();  
        prev=current;
    }
    return output;
}
};


vector<vector<string>> phoneDirectory(vector<string>&contactlist, string &querystr)
{    
   //step1-creation of trie 
   trie* t=new trie();
    
    //insert all strings
    for(int i=0;i<contactlist.size();i++){
        string str=contactlist[i];
        t->insertnode(str);
    }
    //return ans
    return t->getsuggestions(querystr);
}