#include <iostream>
#include<vector>
using namespace std;

int main()
{
   cout << "Enter total size of graph : ";

    vector<int> v = {6,2,5,4,5,1,6};
    int n = v.size();
    int area = 0;

    for(int i=0;i<n;i++)
    {
        int minHeight = v[i];
        for(int j=i;i<n;j++){
            minHeight = min(minHeight,v[j]);
            int a = minHeight*(j-i+1);
            area = max(area,a);
        }
    }
    
    cout << "maximum area is : " << area;
    
    return 0;
}