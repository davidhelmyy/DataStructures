#include <iostream>
#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> node;


void addNode(vector<vector<node>> &graph,int x, int y, int price)
{
    graph[x].push_back(make_pair(y,price));
    graph[y].push_back(make_pair(x,price));
}



pair<vector<int>,int> searchForCheapest(vector<vector<node>> &graph,int start,int finish,int m)
{
    vector<pair<int,int>> prices(graph.size(),make_pair(INT_MAX,INT_MAX));
    priority_queue<pair<int,int>,vector <pair<int,int>>,greater<pair<int,int>>> pqueue;

    prices[start]=make_pair(0,INT_MAX);              /// price,previous
    pqueue.push(make_pair(0,start));                /// price,city
    int cost=0;
    int previous=0;

    vector<int> route;

    while(!pqueue.empty())
    {
        int temp=pqueue.top().second;
        pqueue.pop();

        for(auto x: graph[temp])
        {
            int v=x.first;
            int price=x.second;
            if(temp!=start)
                price+=m;

            if(prices[v].first>prices[temp].first+price)
            {
                prices[v]=make_pair(prices[temp].first+price,temp);
                pqueue.push(make_pair(prices[v].first,v));

            }

        }

    }

    cost=prices[finish].first;
    previous=prices[finish].second;
    route.push_back(finish);


    while(previous!=INT_MAX)
    {

        route.push_back(previous);
        previous=prices[previous].second;

    }
    return make_pair(route,cost);

}


void printRoute(pair<vector<int>,int> temp)
{
    vector<int> *arr=&temp.first;
    int cost=temp.second;
    int time=0;
    cout<<"\nThe route with minimum cost is:  ";
    for(auto itr=arr->rbegin(); itr!=arr->rend(); itr++)
      {
          cout<<*itr ;
            if(itr+1!=arr->rend())
                    cout<< "  ->  ";

      }


    cout<<"\nTotal Cost: " <<cost;

}

void cheapestFlight(vector<vector<node>> &graph,int start,int finish,int m)
{

     printRoute(searchForCheapest(graph,start,finish,m));
}


void readFile(vector<vector<node>> &graph,int &start,int &finish,int&m,char* filename)
{

    freopen(filename,"r",stdin);
    int v,i,cost,hr;
    cin>>m>>v>>i;
    graph.resize(v+1);
    while(i--!=0)
    {
        cin>>start>>finish>>hr>>cost;
        addNode(graph,start,finish,cost+(hr*m));

    }
    cin>>start>>finish;



}

void problem_3()
{
    vector<vector<node>> graph;
    int start,finish,m;
    int v,i,cost,hr;
    cout<<"please enter amount M:\n";
    cin>>m;
    cout<<"\nplease enter number of cities:\n";
    cin>>v;
    cout<<"\nplease enter number of routes:\n";
    cin>>i;
    graph.resize(v+1);
    cout<<"\nplease enter source , destination time and cost for each route:\n";
    while(i--!=0)
    {
        cin>>start>>finish>>hr>>cost;
        addNode(graph,start,finish,cost+(hr*m));

    }
    cout<<"please enter source city:\n";
    cin>>start;
    cout<<"\nplease enter destination city:\n";
    cin>>finish;
    cout<<"-----------------------------------------";
    cheapestFlight(graph,start,finish,m);


}


int main(int argc,char** argv)
{
    if(argc!=2)
    {
        cout<< "Error reading file!";
        exit(0);
    }
        problem_3();

    return 0;
}
