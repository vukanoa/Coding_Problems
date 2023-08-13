#include <iostream>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	178) Graph Valid Tree
	===========================

	============
	Description:
	============

	Given n nodes labeled from 0 to n-1 and a list of undirected edges(each h
	edge is a pair of nodes), write a function to check whether these edges
	make u a valid p tree.

	=====
	Node: You can assume that no duplicate edges will appear in edges. Since
	      all edges are undirected, [0, 1] is the same as [1, 0] and thus will
	      not appear together in edge s.
	=====

	==============================================================
	FUNCTION: bool validTree(int n, vector<pair<int, int>> edges);
	==============================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: n = 5, edges = [[0, 1], [0, 2], [0, 3], [1, 4]]
	Output: true

	--- Example 2 ---
	Input: n = 0, edges = []
	Output: true

	--- Example 3 ---
	Input: n = 5, edges = [[0, 2], [0, 3], [1, 4]]
	Output: false
	Explanation: 1 and 4 aren't connected to the rest of the Graph

	*** Constraints ***
	Uknown
*/

/*
	------------
	--- IDEA ---
	------------

	TODO

*/

/* Time  Complexity: O(E + V) */
/* Space Complexity: O(E + V) */
class Solution{
private:
	static const int default_previous_node = -1;

public:
	bool validTree(int n, std::vector<std::pair<int, int>> edges)
	{
		if (n == 0)
			return true; // Empty Graph does count as a Valid Tree

		std::vector<std::vector<int>> adj_list;
		std::unordered_set<int> uset_visited;

		// Represent Graph using adjacency list
		for (const auto& edge : edges)
		{
			adj_list[edge.first].push_back(edge.second);
			adj_list[edge.second].push_back(edge.first);
		}

		// If all are connected
		bool loop = dfs(0, adj_list, uset_visited, default_previous_node);

		// If there is a Loop or Not all n nodes are connected
		if (loop || uset_visited.size() < n)
			return false;

		return true; // This Graph is a Valid Tree
	}

private:
	void dfs(int curr_node,
	         std::vector<std::vector<int>& adj_list,
	         std::unordered_set<int>& uset_visited,
	         int prev_node)
	{
		// There is a loop
		if (uset_visited.find(curr_node) != uset_visited.end())
			return true;

		uset_visited.insert(curr_node);

		for (const auto& i : adj_list[curr_node])
		{
			// Ignore previous node in adjacency list
			if (i == prev_node)
				continue;

			// There is a loop
			if (dfs(i, adj_list, uset_visited, curr_node))
				return true;
		}

		return false;
	}
};
