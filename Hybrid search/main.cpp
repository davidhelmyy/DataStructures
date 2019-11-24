#include <iostream>
#include <bits/stdc++.h>

using namespace std;


bool harderSearch(int val,vector<int>&arr)
{
    int lo=0;
    int hi=arr.size();
    bool use_binary=false;

    while(lo-hi>=0)
    {

        int midNumber=lo+((hi-lo)/2);
        int mid= use_binary? midNumber:lo+(((hi-lo)*(val-arr[lo]))/(arr[hi]-arr[lo]));

        if(arr[mid]==val)
            return true;

        else if(arr[mid]>val)
        {
            hi=mid-1;
            use_binary=(midNumber<mid);

        }

        else
        {

            lo=mid+1;
            use_binary=(midNumber>mid);
        }




    }

    return false;

}


void generateVector(vector<int>&arr,int size)
{
    for (int i=0;i<size;++i)
    {
        arr.push_back(rand()%100);
    }
}





int main()
{
   vector<int> arr;


    freopen("Test.txt","r",stdin);

    for(int i=0;i<30;++i)
     {
         int temp;
         cin>>temp;
         arr[i]=temp;
     }

 //  cout<<harderSearch(81,arr);




    return 0;
}
