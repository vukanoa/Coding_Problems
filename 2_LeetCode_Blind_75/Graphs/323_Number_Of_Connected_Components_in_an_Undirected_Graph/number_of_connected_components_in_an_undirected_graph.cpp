#include <iostream>
#include <vector>
#include <unordered_set>

/*
	==============
	=== MEDIUM ===
	==============

	==========================================================
	323) Number of Connected Components in an Undirected Graph
	==========================================================

	============
	Description:
	============

	You have a graph of n nodes. You are given an integer n and an array edges
	where edges[i] = [ai, bi] indicates that there is an edge between ai and bi
	in the graph.

	Return the number of components in the Graph.

	==============================================================================
	FUNCTION: int countComponents(int n, std::vector<std::pair<int, int>>& edges);
	==============================================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: n = 5, edges = [[0, 1], [1, 2], [3, 4]]
	Output: 2

	*** Constraints ***
	<Uknown>
*/

/* Time  Complexity: O(e + v) */
/* Space Complexity: O(n) */
class Solution {
public:
	int countComponents(int n, std::vector<std::pair<int, int>>& edges)
	{
		// Empty
		if (n == 0)
			return 0;

		std::vector<std::vector<int>> map(n);

		// Represent Graph using adjacency list
		for (int i = 0; i < edges.size(); i++)
		{
			std::pair<int, int> edge = edges[i];

			// Because it's an UNDIRECTED Graph
			map[edge.first].push_back(edge.second);
			map[edge.second].push_back(edge.first);
		}

		std::unordered_set<int> uset;
		int count = 0;

		for (int i = 0; i < n; i++)
			dfs(map, i, uset, count, true);

		return count;
	}

private:
	void dfs(std::vector<std::vector<int>>& map, int i, std::unordered_set<int>& uset, int& count, bool beginning)
	{
		if (uset.find(i) != uset.end())
			return;

		if (beginning)
			count++;

		uset.insert(i);

		for (int x = 0; x < map[i].size(); x++)
			dfs(map, map[i][x], uset, count, false);
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	int n = 5;
	std::vector<std::pair<int, int>> edges = {{0, 1}, {1, 2}, {3, 4}};

	/* Example 2 */
	// int n = 6;
	// std::vector<std::pair<int, int>> edges = {{0, 1}, {2, 3}, {4, 5}};

	/* Example 3 */
	// int n = 2;
	// std::vector<std::pair<int, int>> edges;

	std::cout << "\n\t==============================================================";
	std::cout << "\n\t=== NUMBER OF CONNECTED COMPONENTS IN AN UNDIRECTED GRAPH ===";
	std::cout << "\n\t==============================================================\n";

	/* Write Input */
	bool first = true;
	std::cout << "\n\tEdges: [";
	for (auto x: edges)
	{
		if (!first)
			std::cout << ", ";

		std::cout << "[";
		std::cout << x.first;
		std::cout << ",";
		std::cout << x.second;
		std::cout << "]";

		first = false;
	}
	std::cout << "]\n";


	/* Solution */
	int count = sol.countComponents(n, edges);


	/* Write Output */
	std::cout << "\n\tThe Result is: " << count << "\n\n\n";


	return 0;
}
