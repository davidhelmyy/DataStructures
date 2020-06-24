#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int getNumberOfConnections(vector<vector<int>> &graph,int start,int level)
{
    if(level<=0)
    return (level==0)? 1:0;

    vector<bool> check(graph.size()+1,false);
    queue<int> q;

    int top;
    int counter=1;
    int levelCounter=0;

    q.push(start);
    check[start]=true;

    while(!q.empty())
    {
        top=q.front();
        q.pop();
        counter--;

        for(auto x:graph[top])
        {
            if(check[x]==false)
           {
               q.push(x);
               check[x]=true;
           }
        }

        if(counter==0)
        {
            levelCounter++;

            if(levelCounter==level)
                return (q.empty())? 0:q.size();
            counter=q.size();
        }
    }
    return 0;

}


void problem_1()
{
    vector<vector<int>> graph;
    int start,level,v,i;
    cout<<"please enter number of vertices:\n";
    cin>>v;
    cout<<"please enter number of edges:\n";
    cin>>i;
    graph.resize(v+1);
    cout<<"please enter edges in the form (u v):\n";
    while(i--!=0)
    {
        cin>>start>>level;
        graph[start].push_back(level);
        graph[level].push_back(start);
    }
    cout<<"please enter edges in the form (u v):\n";
    cin>>start;
    cout<<"please enter value k :\n";
    cin>>level;

    cout<<"\nThere are "<<getNumberOfConnections(graph,start,level)<<" with "
    <<level<<" away starting from "<<start;


}

void printGraph(vector<vector<int>> &graph)
{

    for(int i=0;i<graph.size();i++)
    {
        cout<<i<<"  ->  ";
        for(auto itr=graph[i].begin();itr!=graph[i].end();itr++)
            cout<<*itr<<" -> ";
        cout<<"\n";
    }
}



int main(int argv,char** argc)
{

    if(argv!=2)
    {
        cout<<"Error loading file!";
        exit(0);
    }
    vector<vector<int>> graph;
    int start,level;
    readFromFile(graph,start,level,argc[1]);
  //  printGraph(graph);
    int x=getNumberOfConnections(graph,start,level);
    cout<<x;


    return 0;
}
