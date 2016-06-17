#include <iostream>
#include <algorithm>
#include <fstream>
#include "graph.h"
using namespace std;

bool Graph::get_Cycle(int node,bool color[],int parnt){
	color[node]=true;
	nodes[node]->parent=parnt;
    	for (int  i= 0; i != nodes[node]->edges.size(); ++i)
    	{
        	if (!color[nodes[node]->edges[i].edge])
        	{	
           		if (get_Cycle(nodes[node]->edges[i].edge,color, node))
				return true;
        	}	
 
        	else if (nodes[node]->edges[i].edge != parnt){
			cycleNodes[0]=node;
                        cycleNodes[1]=nodes[node]->edges[i].edge;
           		return true;
		}
    	}	
    	return false;
}

bool Graph::getCycle(){
	bool color[no];
	for(int i=0;i<no;i++)
		color[i]=false;
	for(int i=0;i<no;i++){
		if(!color[i])
			if(get_Cycle(i,color,-1))
				return true;
	}
	return false;
}

Graph::Graph(int number){
	this->no=number;
	int i=0; 
	for(i;i<number;i++){
		Node* n1=new Node(0); 
		nodes.push_back(n1);
	}
}

vector<int> Graph::simplePath(int node,int parent){
	vector<int> cycle;
	int k=node;
	nodes[node]->next=parent;
	while(k!=parent){
		cycle.push_back(k);
		int p=k;
		k=nodes[k]->parent;
		nodes[k]->next=p;	
	}
	nodes[parent]->parent=node;
	cycle.push_back(k);
	return cycle;
}


void Graph::discardEdges(vector<int> cycle){
	int nextNode;
	int node;
	int min1,min2;
	int weight=1000000;
	int discard=0;
	for(int j=0;j<cycle.size();j++){
		int i=cycle[j];
		Compare comp(nodes[i]->next,nodes[i]->parent);
		vector<Edge>::iterator max=max_element(nodes[i]->edges.begin(),nodes[i]->edges.end(),comp); 
		for(int l=0;l<nodes[i]->edges.size();l++){//discard remaining outgng edges		 	
		 		if(nodes[i]->edges[l].edge == nodes[i]->parent){
		 			nextNode=l;
		 			if(nodes[i]->edges[l].weight<weight){
		 				weight=nodes[i]->edges[l].weight;
		 				min1=i;
		 				min2=l;
		 			}
		 			continue;
		 		}
		 		if(nodes[i]->edges[l].edge==nodes[i]->next){
		 			node=l;
		 			continue;
		 		}
		 		if(nodes[i]->edges[l].edge != (*max).edge){
		 			nodes[i]->edges[l].discard=1;
		 			int e1=nodes[i]->edges[l].edge;
		 			for(int c=0;c<nodes[e1]->edges.size();c++){
		 				if(nodes[e1]->edges[c].edge==i){
		 					nodes[e1]->edges[c].discard=1;
		 					(nodes[e1]->degree)--;
		 					break;
		 				}
		 			}
		 			discard++;
		 			(nodes[i]->degree)--;
		 		}
		}
		if(((*max).weight > nodes[i]->edges[node].weight) && ((*max).weight > nodes[i]->edges[nextNode].weight)){ 
			if(nodes[i]->edges[node].discard!=1 && nodes[i]->edges[nextNode].discard!=1){
				if((nodes[i]->edges[nextNode]).weight > (nodes[i]->edges[node]).weight){
					nodes[i]->edges[node].discard=1;
					int e1=nodes[i]->edges[node].edge;
		 			for(int c=0;c<nodes[e1]->edges.size();c++){
		 				if(nodes[e1]->edges[c].edge==i){
		 					nodes[e1]->edges[c].discard=1;
		 					(nodes[e1]->degree)--;
		 					break;
		 				}
		 			}				
					discard++;
				}
				else{
					nodes[i]->edges[nextNode].discard=1;
					int e1=nodes[i]->edges[nextNode].edge;
		 			for(int c=0;c<nodes[e1]->edges.size();c++){
		 				if(nodes[e1]->edges[c].edge==i){
		 					nodes[e1]->edges[c].discard=1;
		 					(nodes[e1]->degree)--;
		 					break;
		 				}
		 			}
					discard++;	
				}
				(nodes[i]->degree)--; 
			} 		
		}
		else if(((*max).weight <= nodes[i]->edges[node].weight) && ((*max).weight >= nodes[i]->edges[nextNode].weight)){
			if(nodes[i]->edges[node].discard!=1 && nodes[i]->edges[nextNode].discard!=1){
				nodes[i]->edges[nextNode].discard=1;
				int e1=nodes[i]->edges[nextNode].edge;
	 			for(int c=0;c<nodes[e1]->edges.size();c++){
	 				if(nodes[e1]->edges[c].edge==i){
	 					nodes[e1]->edges[c].discard=1;
	 					(nodes[e1]->degree)--;
	 					break;
	 				}
	 			}
				discard++;
				(nodes[i]->degree)--; 
			}
		}
		else if(((*max).weight > nodes[i]->edges[node].weight) && ((*max).weight < nodes[i]->edges[nextNode].weight)){
			if(nodes[i]->edges[node].discard!=1 && nodes[i]->edges[nextNode].discard!=1){
				nodes[i]->edges[node].discard=1;
				int e1=nodes[i]->edges[node].edge;
	 			for(int c=0;c<nodes[e1]->edges.size();c++){
	 				if(nodes[e1]->edges[c].edge==i){
	 					nodes[e1]->edges[c].discard=1;
	 					(nodes[e1]->degree)--;
	 					break;
	 				}
	 			}
				discard++;
				(nodes[i]->degree)--; 
			}
		}
		else{
			if(nodes[i]->edges[node].discard!=1 && nodes[i]->edges[nextNode].discard!=1){
				(*max).discard=1;
				int e1=(*max).edge;
	 			for(int c=0;c<nodes[e1]->edges.size();c++){
	 				if(nodes[e1]->edges[c].edge==i){
	 					nodes[e1]->edges[c].discard=1;
	 					(nodes[e1]->degree)--;
	 					break;
	 				}
	 			}
				discard++;
				(nodes[i]->degree)--; 
			}
		}
	}
	if(discard==0){
		nodes[min1]->edges[min2].discard=1;
		int e1=nodes[min1]->edges[min2].edge;
		for(int c=0;c<nodes[e1]->edges.size();c++){
			if(nodes[e1]->edges[c].edge==min1){
				nodes[e1]->edges[c].discard=1;
				(nodes[e1]->degree)--;
				break;
			}
		}
		(nodes[min1]->degree)--;
	}
}

vector<int> Graph::degreeOne(){
	vector<int> degreeOne;
	for(int i=0;i<nodes.size();i++){
		if(nodes[i]->degree==1){
			degreeOne.push_back(i);
		}
	}
	return degreeOne;
}


int Graph::dfs(int node,int color[]){
	color[node]=1;
	static int wt=0;
	for (int i = 0; i < nodes[node]->edges.size(); ++i)
	{
		int k=nodes[node]->edges[i].edge;
		if (nodes[node]->edges[i].discard!=1 && color[k]==0)
		{
			cout<<k<<"->";
			wt = wt + nodes[node]->edges[i].weight;
			dfs(k,color);
			//wt = wt + dfs(k,color);
			
		}
	}
	return wt;
}

void Graph::maxPath(vector<int> degreeOne){
	int color[no];
	int maxWt=0; 
	for(int i=0;i<no;i++)
		color[i]=0;
	for(int i=0;i<degreeOne.size();i++){
		if(color[degreeOne[i]]==0){
			if(i!=0)
				cout<<"--ferry--";
			cout<<degreeOne[i]<<"->";
			maxWt=dfs(degreeOne[i],color);	
		}		
	}
	cout<<endl;
	cout<<"Maximum weigth of the path:"<<maxWt<<endl;
}

void Graph::addEdge(int node1,int node2,int weight){
	nodes[node1-1]->visited=0;
	int k=nodes[node1-1]->degree;
	nodes[node1-1]->degree=k+1;
	Edge e1(node2-1,weight);
	nodes[node1-1]->edges.push_back(e1);
	int q=nodes[node2-1]->degree;
	nodes[node2-1]->visited=0;
	nodes[node2-1]->degree=q+1;
	Edge e2(node1-1,weight);
        nodes[node2-1]->edges.push_back(e2);
}

void Graph::Print(){
	//for printing edges
	/*for(int i=0;i<no;i++){
		for(int j=0;j<nodes[i]->edges.size();j++){
			cout<<nodes[i]->edges[j].edge<<" ";
		}
		cout<<endl;
	}*/
	for(int i=0;i<no;i++)
		cout<<i<<" "<<nodes[i]->degree<<endl;
	}

int main(int argc,char** argv){
	ifstream file;
	file.open(argv[1]);
	int number;
	file>>number;
	Graph g2(number);
	/*g1.addEdge(2,3,1);
 	g1.addEdge(2,1,3);
 	g1.addEdge(1,3,3);
	g1.addEdge(1,4,2);
	g1.addEdge(4,5,2);
	//cout<<g1.getCycle();*/
	//g1.Print();
	while(!file.eof()){
		int no1,no2,no3;
		file>>no1;
		file>>no2;
		file>>no3;
		if(file.eof())
			break;
		g2.addEdge(no1,no2,no3);	
	}
	g2.getCycle();
	vector<int> cycle=g2.simplePath(g2.cycleNodes[0],g2.cycleNodes[1]);
	g2.discardEdges(cycle);
	vector<int> degreeOne=g2.degreeOne();
	cout<<"Maximum path:";
	g2.maxPath(degreeOne);
	file.close();
 	return 0;
}
