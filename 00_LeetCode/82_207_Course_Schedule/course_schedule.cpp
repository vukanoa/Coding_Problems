#include <iostream>
#include <vector>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	207) Course Schedule
	===========================

	============
	Description:
	============

	There are a total of "numCourses" courses you have to take, labeled from 0
	to "numCourses - 1". You are given an array "prerequisites where
	prerequisites[i] = [ai, bi] indicates that you must take course bi first
	if you want to take course ai.

	For example, the pair [0, 1], indicates that to take course 0 you have to
	first take course 1.

	Return "true" if you can finish all courses. Otherwise, return "false".

	=============================================================================
	FUNCTION: bool canFinish(int numCourses, vector<vector<int>>& prerequisites);
	=============================================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  numCourses = 2, prerequisites = [[1, 0]]
	Output: true
	Explanation: There are a total of 2 courses to take. To take course 1 you
	should have finished course 0. So it is possible.

	--- Example 2 ---
	Input:  numCourses = 2, prerequisites = [[1, 0], [0, 1]]
	Output: false
	Explanation: There are a total of 2 courses to take. To take course 1 you
	should also have finished course 1. So it is impossible.

	*** Constraints ***
	1 <= numCourses <= 2000
	0 <= prerequisites.length <= 5000
	prerequisites[i].length = 2
	0 <= ai, bi < numCourses
	All the pairs prerequisites[i] are unique.

*/


/* Time  Complexity: O(V + E) */
/* Space Complexity: O(V) */
class Solution{
private:
	bool is_cyclic(std::vector<std::vector<int>>& adj, std::vector<int>& visited, int curr)
	{
		if (visited[curr] == 2)
			return true;

		visited[curr] = 2;
		for (int i = 0; i < adj[curr].size(); i++)
		{
			if (visited[adj[curr][i]] != 1)
			{
				if (is_cyclic(adj, visited, adj[curr][i]))
					return true;
			}
		}

		visited[curr] = 1;

		return false;
	}

public:
	bool canFinish(int numCourses, std::vector<std::vector<int>>& prerequisites)
	{
		std::vector<std::vector<int>> adj(numCourses);

		// Make adjacency matrix(Directed Graph)
		for (int i = 0; i < prerequisites.size(); i++)
			adj[prerequisites[i][0]].push_back(prerequisites[i][1]);

		std::vector<int> visited(numCourses, 0);
		for (int i = 0; i < numCourses; i++)
		{
			if (visited[i] == 0)
			{
				if (is_cyclic(adj, visited, i))
					return false;
			}
		}

		return true;
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	// int numCourses = 2;
	// std::vector<std::vector<int>> prerequisites {{1, 0}};

	/* Example 2 */
	int numCourses = 2;
	std::vector<std::vector<int>> prerequisites {{1, 0}, {0, 1}};


	std::cout << "\n\t=======================";
	std::cout << "\n\t=== COURSE SCHEDULE ===";
	std::cout << "\n\t=======================\n";

	/* Write Output */
	bool first = true;
	std::cout << "\n\tPrerequisites: [";
	for (auto x: prerequisites)
	{
		if (!first)
			std::cout << ", ";

		bool first_first = true;
		std::cout << "[";
		for (const auto& xx : x)
		{
			if (!first_first)
				std::cout << ", ";

			std::cout << xx;
			first_first = false;
		}
		std::cout << "]";

		first = false;
	}
	std::cout << "]\n";

	/* Solution */
	if (sol.canFinish(numCourses, prerequisites))
		std::cout << "\n\tResult: Possible!\n\n";
	else
		std::cout << "\n\tResult: Impossible!\n\n";


	return 0;
}
