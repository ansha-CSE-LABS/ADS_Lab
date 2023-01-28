#include <bits/stdc++.h>
using namespace std;
void printPosNegPairs(vector<int> &Arr)
{
    int n = Arr.size();
    unordered_map<int, int> hash_table;
    cout<<"The positive and negative pairs are:"<<endl;
    for (int i = 0; i < n; i++)
    {
        hash_table[Arr[i]]++;
    }
    for (int i = 0; i < n; i++)
    {
        if (hash_table[-Arr[i]] == 1)
        {
            if (Arr[i] <= 0)
            {
                cout << Arr[i] << " " << (-Arr[i]) << " "<<endl;
            }
            else
            {
                cout << (-Arr[i]) << " " << Arr[i] << " "<<endl;
            }
            hash_table[Arr[i]]--;
            hash_table[-Arr[i]]--;
        }
    }
    cout << endl;
    return;
}
int main()
{
     vector<int> Arr;
    cout<<"Enter the Array Size: ";
    int n;
    cin>>n;
    cout<<"Enter the Elements in the Array"<<endl;
    for(int i=0;i<n;i++)
    {
     int a;
     cin>>a;
    Arr.push_back(a);
    }
    printPosNegPairs(Arr);
    return 0;
}
