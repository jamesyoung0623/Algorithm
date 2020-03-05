// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2019/9/6 Cheng-Yun Hsieh]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    for(int i = 1;i < data.size();i++)
    {
        for(int j = 0;j<i ;j++)
        {
            if(data[i] < data[j])
            {
                int t = data[i];
                for(int k = i;k>j;k--)
                {
                    data[k] = data[k-1];
                }
                data[j] = t;
            }
        }
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data){
    QuickSortSubVector(data, 0, data.size() - 1);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high) {
    if(low != high)
    {
        Partition(data,low,high);
    }
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    int mid = (low+high)/2;
    int t = data[mid];
    vector<int> s,l;
    int a=0;
    int b=0;
    for(int i = low;i<=high;i++)
    {
        if(i != mid)
        {
            if(data[i] <= data[mid])
            {
                s.push_back(data[i]);
                a++;
            }
            else if(data[i] > data[mid])
            {
                l.push_back(data[i]);
                b++;
            }
        }
    }
    for(int i=0;i<a;i++)
    {
        data[low+i] = s[i];
    }
    data[low+a] = t;
    for(int i=0;i<b;i++)
    {
        data[low+a+1+i] = l[i];
    }
    if(a != 0)
    {
        QuickSortSubVector(data,low,low+a-1);
    }
    if(low+a<high)
    {
        QuickSortSubVector(data,low+a+1,high);
    }
    
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
   if(low != high)
   {
       int mid = (low+high)/2;
       MergeSortSubVector(data,low,mid);
       MergeSortSubVector(data,mid+1,high);
       Merge(data,low,mid,mid+1,high);
   }
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    int a = low;
    int b = middle2;
    int c = 0;
    vector<int> v;
    while(true)
    {
        if(data[a] >= data[b])
        {
            v.push_back(data[b]);
            b++;
            if(b > high)
            {
                c = 2;
                break;
            }
        }
        else if(data[a] < data[b])
        {
            v.push_back(data[a]);
            a++;
            if(a > middle1)
            {
                c = 1;
                break;
            }
        }
    }
    if(c == 1)
    {
        for(int i = b;i<=high;i++)
        {
            v.push_back(data[i]);
        }
    }
    if(c == 2)
    {
        for(int i = a;i<=middle1;i++)
        {
            v.push_back(data[i]);
        }
    }
    for(int i = low;i<=high;i++)
    {
        data[i] = v[i-low];
    }
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    int c = 0;
    int max = data[root];
    if(root <= heapSize/2)
    {
        if(data[(2*root+1)] > max && (2*root+1)<heapSize)
            {
                max = data[(2*root+1)];
                c = 1;
            }
        if(data[(2*root+2)] > max && (2*root+2)<heapSize)
            {
                max = data[2*root+2];
                c = 2;
            }
    }
    if(c==1)
    {
        swap(data[root],data[(2*root+1)]);
        MaxHeapify(data,(2*root+1));
    }
    if(c==2)
    {
        swap(data[root],data[(2*root+2)]);
        MaxHeapify(data,(2*root+2));
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); 
    for(int i = heapSize/2-1;i>=0;i--)
    {
        MaxHeapify(data,i);
    }
}
