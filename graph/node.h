#include <iostream>

class Node{
public:
	int predecessor;
	int distance;
	Node();
};

Node::Node()
{
	predecessor = -1;
	distance = -1;
}