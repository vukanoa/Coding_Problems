#include <iostream>
#include <vector>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	684) Redundant Connection
	===========================

	============
	Description:
	============

	In this problem, a tree is an undirected graph that is connected and has no
	cycles.

	You are given a graph that started as a tree with n nodes labeled from 1 to
	n, with one additional edge added. The added edge has two different
	vertices chosen from 1 to n, and was not an edge that already existed. The
	graph is represented as an array edges of length n where edges[i] = [ai,
	bi] indicates that there is an edge between nodes ai and bi in the graph.

	Return an edge that can be removed so that the resulting graph is a tree of
	n nodes. If there are multiple answers, return the answer that occurs last
	in the input.

	==========================================================================
	FUNCTION: vector<int> findRedundantConnection(vector<vector<int>>& edges);
	==========================================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---

	        1 --- 2
	        |   /
	        |  /
	        | /
	        |/
	        3

	Input: edges = [[1,2],[1,3],[2,3]]
	Output: [2,3]

	--- Example 2 ---

	        2 --- 1 --- 5
	        |     |
	        |     |
	        |     |
	        3 --- 4

	Input: edges = [[1,2],[2,3],[3,4],[1,4],[1,5]]
	Output: [1,4]


	*** Constraints ***
	n == edges.length
	3 <= n <= 1000
	edges[i].length == 2
	1 <= ai < bi <= edges.length
	ai != bi
	There are no repeated edges.
	The given graph is connected.

*/

/*
	------------
	--- IDEA ---
	------------

	TODO

	Union & Find

*/

/* Time  Beats: 90.67% */
/* Space Beats: 79.01% */

/* Time  Complexity: O(E + V) */
/* Space Complexity: O(n) */
class Solution{
public:
	std::vector<int> findRedundantConnection(std::vector<std::vector<int>>& edges)
	{
		int n = edges.size();

		std::vector<int> parents(n + 1); // We don't need 0
		std::iota(parents.begin(), parents.end(), 0);

		std::vector<int> ranks(n + 1, 1);
		std::vector<int> result;
		for (auto& edge : edges)
		{
			result = Union(edge[0], edge[1], parents, ranks);

			if (!result.empty())
				return result;
		}

		return result;
	}

private:
	int Find(int node, std::vector<int>& parents)
	{
		int tmp = node;

		while (tmp != parents[tmp])
		{
			parents[tmp] = parents[parents[tmp]];
			tmp = parents[tmp];
		}

		return tmp;
	}

	std::vector<int> Union(int node_1, int node_2, std::vector<int>& parents, std::vector<int>& ranks)
	{
		int parent_1 = Find(node_1, parents);
		int parent_2 = Find(node_2, parents);

		if (parent_1 == parent_2)
			return {node_1, node_2};

		if (ranks[parent_1] >= ranks[parent_2])
		{
			parents[parent_2] = parent_1;
			ranks[parent_1]++;
		}
		else
		{
			parents[parent_1] = parent_2;
			ranks[parent_2]++;
		}

		return {};
	}
};
