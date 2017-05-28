#include "graph/graph.h"
#include <stdio.h>
int main(void){
	UnweightedGraph g(8);
	g.AddEdge(0, 1);
	g.AddEdge(1, 0);	g.AddEdge(1, 4);	g.AddEdge(1, 5);
	g.AddEdge(2, 3);	g.AddEdge(2, 4);	g.AddEdge(2, 5);
	g.AddEdge(3, 2);	g.AddEdge(3, 6);
	g.AddEdge(4, 1);	g.AddEdge(4, 2);
	g.AddEdge(5, 1);	g.AddEdge(5, 2);	g.AddEdge(5, 6);
	g.AddEdge(6, 3);	g.AddEdge(6, 5);

	vector<Node> bfsInfo = g.GetShortestPathsFrom(3);
	int i;

	cout << "###################" << endl;
	cout << "#### Test Case ####" << endl;
	cout << "###################" << endl;
	g.ShowGraph();

	cout << endl;
	cout << "############################" << endl;
	cout << "#### Result: Source = 3 ####" << endl;
	cout << "############################" << endl;
	g.ShowShortestPathsFrom(3, AL_DFS);

	cout << endl;
	cout << "###################" << endl;
	cout << "#### Traversal ####" << endl;
	cout << "###################" << endl;
	g.ShowTraversal(3);
	getchar();

	return 1;
}
