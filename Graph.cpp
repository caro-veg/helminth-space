#include <iostream>
#include "Graph.h"

using namespace std;


Graph::Graph(vector<tuple<int, int, double> > &_connections, int _N)
{
    nodeVector.reserve(_N);
    adjacencyList.reserve(_N);

    for(int i=0; i<_N; ++i)
        nodeVector.push_back(shared_ptr<Node> (new Node()));

    linkNodes(_connections);

    for(int i=0; i<_connections.size(); ++i)
    {
        shared_ptr<Node> destination = nodeVector.at(get<1>(_connections.at(i)));
        nodeVector.at(get<0>(_connections.at(i)))->addDestinationNode(destination, get<2>(_connections.at(i)));
    }
}


Graph::Graph(int _N)
{
    nodeVector.reserve(_N);
    adjacencyList.reserve(_N);

    for(int i=0; i<_N; ++i)
        nodeVector.push_back(shared_ptr<Node> (new Node()));
}


Graph::~Graph() { }


void Graph::linkNodes(vector<tuple<int, int, double> > &_connections)
{
    for(int i=0; i<_connections.size(); ++i)
    {
        linkMap[make_pair(get<0>(_connections.at(i)), get<1>(_connections.at(i)))] = get<2>(_connections.at(i));
    }
}


void Graph::makeGrid(int _gridLength)
{
    int n=_gridLength;
    int N=n*n;
    double length = 1;  //in simplest case in grid all connections have the same length

    map<pair<int, int>, double>  connections;

    vector<int> dir{-1, 1, -n, n};

    for(int i=0; i<N; ++i)
    {
        for(int j=0; j<dir.size(); ++j)
        {
            int k = i + dir.at(j);
            if((k >= 0) & (k < N))
            {
                if(i % n == 0)
                {
                    if(k % n != (n-1))
                    {
                        pair<int, int> temp = make_pair(i, k);
                        connections[temp] = length;
                    }
                }
                else if(i % n == (n-1))
                {
                    if(k % n != 0)
                    {
                        pair<int, int> temp = make_pair(i, k);
                        connections[temp] = length;
                    }
                }
                else
                {
                    pair<int, int> temp = make_pair(i, k);
                    connections[temp] = length;
                }
            }
        }
    }

    linkMap = connections;
}

vector<shared_ptr<Node> > &Graph::getNodeVector()
{
    return nodeVector;
}


map<pair<int, int>, double> const &Graph::getLinkMap()
{
    return linkMap;
}


void Graph::printLinkMap()
{
    for(map<pair<int, int>, double>::iterator it=linkMap.begin(); it!=linkMap.end(); ++it)
    {
        cout << "{ ";


        cout << it->first.first << " " << it->first.second << " " << it->second;


        cout << "}" << endl;
    }
}
