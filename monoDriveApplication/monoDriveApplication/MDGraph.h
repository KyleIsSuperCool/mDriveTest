#pragma once
#include <vector>

using namespace std;

//Nodes contained by MDGraph
struct MDNode
{
	//Index in MDGraph.m_MyNodes
	int m_Index;

	//Connected Nodes defined by their Index in MDGraph.m_MyNodes
	vector<int> m_ConnectedNodeIndexes;

	//Bool used to keep track of looping paths
	bool m_UniqueSearchComplete;
};

//Graph used to find connections betweeen its MDNodes.
class MDGraph
{
	//All of the nodes in the graph, in order of their Index
	vector<MDNode> m_MyNodes;

	//The vector filled and used for finding unique Paths. 
	vector<int> m_UniqueSearchVector;

public:

	//Adds a node to m_MyNodes
	void AddNode(MDNode _newNode);

	//Creates the graph
	void CreateGraph(string _FileName);

	//Prints every path for every node in m_MyNodes
	void PrintEveryPath();

	//Prints every path for a single node in m_MyNodes
	void PrintASpecifcPath(int _Index);

private:

	//Prints whatever we have in m_UniqueSearchVector 
	void PrintUniqueSearch(bool _Looping);

	//Recursive Function
	//Finds every path of the given Index, then prints
	void FindUniquePath(int _Index);
};