//question link->https://leetcode.com/problems/longest-common-prefix/

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