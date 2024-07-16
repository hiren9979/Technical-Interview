#include <iostream>
#include<algorithm>
#include<vector>
using namespace std;

int longestCommonSubsequence(const string&s1,const string& s2,int m,int n){
    if(m==0 || n==0)
        return 0;
    if(s1[m-1] == s2[n-1]){
        return 1+longestCommonSubsequence(s1,s2,m-1,n-1);
    }
    else{
        return max(longestCommonSubsequence(s1,s2,m,n-1),longestCommonSubsequence(s1,s2,m-1,n));
    }
}

int main() {

    string s1 = "ABCDGH";
    string s2 = "AEDFHR";
    
    int m = s1.size();
    int n = s2.size();
    
    cout << longestCommonSubsequence(s1,s2,m,n);
    
	return 0;
}