#include "node.h"
#include <vector>
#include <cmath>
#include "compare.h"
using namespace std;

// structure of graph
class Graph{
 private:
	int no; //number of nodes
	vector<Node*> nodes;
 public:
 	int cycleNodes[2]; 
 	Graph(int no);
	void addEdge(int node1,int node2,int weight);//adds edges to the graph
	void Print();
	int dfs(int node,int color[]);
	void discardEdges(vector<int> cycle);
	vector<int> degreeOne();//returns nodes with degree one
	void maxPath(vector<int> degreeOne);// returns the path with maximum weight which may or may not include ferry 
	vector<int> simplePath(int node,int parent);//returns cycle in the graph
	bool get_Cycle(int node,bool visited[],int parent);
	bool getCycle();
	~Graph();
};

Graph::~Graph(){
	for(int i=0;i<no;i++)
		delete(nodes[i]);
}
