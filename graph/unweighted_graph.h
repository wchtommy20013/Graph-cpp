#ifndef __UNWEIGHTED_GRAPH_H
#define __UNWEIGHTED_GRAPH_H
#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <stack>
#include "node.h"

using namespace std;

static int AL_BFS = 0;
static int AL_DFS = 1;

class UnweightedGraph{	
	vector<int> *adj;

public:
	int num_vertices;

	UnweightedGraph(int num_vertices);
	void AddEdge(int vertice, int adjacent);
	void ShowGraph();
	void ShowTraversal(int source, int method);
	vector<Node> GetShortestPathsFrom(int source, int method);
	void ShowShortestPathsFrom(int source, int method);

private: 
	vector<Node> BFS(int source);
	vector<Node> DFS(int source);
	void BFSTraversal(int source);
	void DFSTraversal(int source);
};

/**
* Initializer of UnweightedGraph class
* @param num       The total number of vertices.
*/
UnweightedGraph::UnweightedGraph(int num_vertices){
	this->num_vertices = num_vertices;
	adj = new vector<int>[num_vertices];
}

/**
* This method is used to set the edges
* @param v	A vertex.
* @param a	The adjacent vertex that is directly connected to v.
*/
void UnweightedGraph::AddEdge(int v, int a){
	adj[v].push_back(a); // Add w to v¡¦s list.
}

/**
* This method is used to print the graph on stdout in a numerical way
*/
void UnweightedGraph::ShowGraph(){
	int i;
	vector<int>::iterator it;
	for (i = 0; i < this->num_vertices; i++){
		cout << i << " { ";
		for (it = this->adj[i].begin(); it != this->adj[i].end(); it++){
			cout << *it << " ";
		}
		cout << "}" << endl;
	}
}

/**
* This method is used to display the BFS/DFS traversal from source in ascending manner.
* @param source 	The source vertex.
* @param method		Either BFS or DFS
*/
void UnweightedGraph::ShowTraversal(int source, int method = AL_BFS){
	if(method == AL_BFS){
		BFSTraversal(source);
	}else{
		DFSTraversal(source);
	}
}


/**
* This method is used to retrieve the shortest path from source to every vertice in the graph with BFS/DFS for further uses.
* @param source			The source vertex.
* @param method			Either BFS or DFS
* @return vector<Node>		Set of information including distance and predecessor from source to every vertice.
*/
vector<Node> UnweightedGraph::GetShortestPathsFrom(int source, int method = AL_BFS){
	return (method == AL_BFS) ? BFS(source): DFS(source);
}

/**
* This method is used to display the shortest path from source to every vertice in the graph with BFS/DFS.
* @param source			The source vertex.
* @param method			Either BFS or DFS
*/
void UnweightedGraph::ShowShortestPathsFrom(int source, int method = AL_BFS){
	int i;
	vector<Node> bfsInfo = this->GetShortestPathsFrom(source, method);

	for (i = this->num_vertices - 1; i >= 0; i--){
		cout << "vertex " << i << ": "; 
		if(bfsInfo.back().distance == -1) 	cout << "distance = Infinity, ";
		else 					cout << "distance = " << bfsInfo.back().distance << ", "; 

		if(bfsInfo.back().predecessor == -1)	cout << "predecessor = None" << endl;
		else					cout << "predecessor = " << bfsInfo.back().predecessor << endl;
		bfsInfo.pop_back();
	}

}







//Implementations

//BFS: used for wider graphs	[The solution is not far from source]
//DFS: used for deeper graphs	[The solution might be very far from source]

vector<Node> UnweightedGraph::BFS(int source){
	//Initialize
	vector<Node> BFSInfo;

	for (int i = 0; i < this->num_vertices; i++){
		Node node;					//Every node will have a distance and predecessor of -1, indicate currently unreachable
		if (i == source) node.distance = 0;
		BFSInfo.push_back(node);
	}

	
	queue<int> queue;					//First-In-First-Out -> BFS
	queue.push(source);

	while (!queue.empty()){					//For every node 'source' in the queue
		source = queue.front();
		queue.pop();

		vector<int>::iterator i;
		for (i = adj[source].begin(); i != adj[source].end(); i++){	//Find all neighbors of the node 'source'
			int vertice = *i;

			if(BFSInfo.at(vertice).distance == -1){			//If the neighbor has not been visited [i.e. distance = -1]
				BFSInfo.at(vertice).distance = BFSInfo.at(source).distance + 1;		//Assign a distance of d(parent)+1 to the neighbor node
				BFSInfo.at(vertice).predecessor = source;				//Delare the parent of the neighbor node
				queue.push(vertice);							//Push it into the queue for further search
			}
		}
	}
	return BFSInfo;
}

vector<Node> UnweightedGraph::DFS(int source){
	vector<Node> BFSInfo;

	for (int i = 0; i < this->num_vertices; i++){
		Node node;
		if (i == source) node.distance = 0;
		BFSInfo.push_back(node);
	}


	stack<int> stack;					//First-In-Last-Out -> DFS
	stack.push(source);

	while (!stack.empty()){
		source = stack.top();
		stack.pop();

		vector<int>::iterator i;
		for (i = adj[source].begin(); i != adj[source].end(); i++){
			int vertice = *i;

			if(BFSInfo.at(vertice).distance == -1){
				BFSInfo.at(vertice).distance = BFSInfo.at(source).distance + 1;
				BFSInfo.at(vertice).predecessor = source;
				stack.push(vertice);
			}
		}
	}
	return BFSInfo;
}

void UnweightedGraph::BFSTraversal(int source){
	bool *visited = new bool[this->num_vertices];
	for (int i = 0; i < this->num_vertices; i++)
		visited[i] = false;

	queue<int> queue;

	visited[source] = true;
	queue.push(source);

	vector<int>::iterator i;

	cout << source << " ";

	bool has_value = false;
	while (!queue.empty()){
		source = queue.front();	
		queue.pop();

		
		for (i = this->adj[source].begin(); i != this->adj[source].end(); ++i){
			if (!visited[*i]){
				visited[*i] = true;
				if(!has_value){
					cout << "{ ";
					has_value = true;
				}
				cout << *i << " ";
				queue.push(*i);
			}
		}	

		if(has_value){
			cout << "}";
		}
		has_value = false;
	}
}


void UnweightedGraph::DFSTraversal(int source){
	bool *visited = new bool[this->num_vertices];
	for (int i = 0; i < this->num_vertices; i++)
		visited[i] = false;

	stack<int> stack;

	visited[source] = true;
	stack.push(source);

	vector<int>::iterator i;

	cout << source << " ";

	bool has_value = false;
	while (!stack.empty()){
		source = stack.top();	
		stack.pop();

		
		for (i = this->adj[source].begin(); i != this->adj[source].end(); ++i){
			if (!visited[*i]){
				visited[*i] = true;
				if(!has_value){
					cout << "{ ";
					has_value = true;
				}
				cout << *i << " ";
				stack.push(*i);
			}
		}	

		if(has_value){
			cout << "}";
		}
		has_value = false;
	}
}


#endif
