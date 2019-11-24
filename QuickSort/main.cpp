#include <iostream>
#include <bits/stdc++.h>


using namespace std;


int findMiddle(vector<int>& arr,int left,int right)
{

    int middle=left+((right-left)/2);

   if(arr[left]>arr[middle])
    swap(arr[left],arr[middle]);

   if(arr[right]>arr[middle])
    swap(arr[middle],arr[right]);

   if(arr[right]<arr[left])
    swap(arr[middle],arr[left]);


   return arr[left];

    }




void insertionSort(vector<int> &arr,int left,int right)
{

    for(int i=left+1;i<right;++i)
    {

        for(int j=i;j>left;--j)
        {
            if(arr[j]<arr[j-1])
                swap(arr[j],arr[j-1]);
            else
                break;

        }


    }

}


int makeReady(vector<int> &arr,int left,int right)
{
    int middle=findMiddle(arr,left,right);

    int last=right-1;

    right-=2;

    while(left<right)
    {
        while(arr[left]<middle)
            ++left;

        while(arr[right]>middle)
            --right;

        swap(arr[left++],arr[right--]);

    }

    swap(arr[last],arr[left]);

    return left;




}


void QuickSort(vector<int> &arr,int left,int right)
{


    if(left-right<=9)
    insertionSort(arr,left,right);

    else
       {
        int part=makeReady(arr,left,right);
        QuickSort(arr,left,part-1);
        QuickSort(arr,part+1,right);

    }



}



void display(vector<int>& arr)
{
  for(int i=0;i<arr.size();++i)
    cout<< arr[i]<<'\n';

}




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
   generateVector(arr,50);

    QuickSort(arr,0,arr.size());
    display(arr);


    return 0;
}
