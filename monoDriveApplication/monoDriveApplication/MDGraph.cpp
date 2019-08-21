#include "pch.h"
#include "MDGraph.h"
#include <iostream>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;


void MDGraph::AddNode(MDNode _newNode)
{
	m_MyNodes.push_back(_newNode);
}

void MDGraph::CreateGraph(string _FileName)
{
	//Make and read the file.
	std::ifstream file(_FileName);
	json j = json::parse(file);

	m_MyNodes.clear();


	//Add the first loop. Had trouble with this Json parser figuring out how to get it to read the file correctly. 
	MDNode firstNode;
	firstNode.m_Index = 0;
	firstNode.m_UniqueSearchComplete = false;

	for (int x = 0; x < j["start"].size(); ++x)
	{
		firstNode.m_ConnectedNodeIndexes.push_back(j["start"][x]);
	}
	AddNode(firstNode);


	//Loop through each remaining json key and make MDNodes
	for (int i = 1; i < j.size(); ++i)
	{
		string jsonKey = to_string(i);
		MDNode NewNode;
		NewNode.m_Index = i;
		NewNode.m_UniqueSearchComplete = false;
		for (int x = 0; x < j[jsonKey].size(); ++x)
		{
			NewNode.m_ConnectedNodeIndexes.push_back(j[jsonKey][x]);
		}
		AddNode(NewNode);
	}
}


void MDGraph::PrintEveryPath()
{
	for (int i = 0; i < m_MyNodes.size(); ++i)
	{
		FindUniquePath(i);
	}

}

void MDGraph::PrintASpecifcPath(int _Index)
{
	//Check if the given index in myNodes
	if (_Index < m_MyNodes.size())
	{
		FindUniquePath(_Index);
	}
	else
	{
		cout << "Thread: " << _Index << " not available.";
	}
}

void MDGraph::PrintUniqueSearch(bool _Looping)
{
	//Dont print anything if we dont have a current search
	if (m_UniqueSearchVector.size() == 0)
		return;

	std::cout << "[thread " << m_UniqueSearchVector[0] << "]: start";

	for (int i = 0; i < m_UniqueSearchVector.size(); ++i)
	{
		std::cout << " -> " << m_UniqueSearchVector[i];
	}

	if (_Looping)
	{
		std::cout << " (cycle)\n";
	}
	else
	{
		std::cout << " -> end\n";
	}
}


void MDGraph::FindUniquePath(int _Index)
{
	//Add this Node to our Search
	m_UniqueSearchVector.push_back(_Index);

	//Second time we are in this child node, we are looping
	if (m_MyNodes[_Index].m_UniqueSearchComplete)
	{
		PrintUniqueSearch(true);

		m_UniqueSearchVector.pop_back();

		return;
	}

	//End of The Line
	if (m_MyNodes[_Index].m_ConnectedNodeIndexes.size() == 0)
	{
		PrintUniqueSearch(false);

		m_UniqueSearchVector.pop_back();

		return;
	}

	//We are marking that this node is in the list.
	m_MyNodes[_Index].m_UniqueSearchComplete = true;

	for (int i = 0; i < m_MyNodes[_Index].m_ConnectedNodeIndexes.size(); ++i)
	{
		FindUniquePath(m_MyNodes[m_MyNodes[_Index].m_ConnectedNodeIndexes[i]].m_Index);
	}

	//Weve completed all paths of this node
	m_UniqueSearchVector.pop_back();

	m_MyNodes[_Index].m_UniqueSearchComplete = false;

	return;
}
