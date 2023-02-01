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


/*
	------------
	--- IDEA ---
	------------

	Consider this example:
		[[0, 1], [1, 2], [2, 3]]

	We would interpret the example as:
	In order to take Course 0, you need to take Course 1.
	In order to take Course 1, you need to take Course 2.
	In order to take Course 2, you need to take Course 3.

	If we represent this as a Graph, it looks like this:

	   1 -> 2
	   ^     \
	  /       v
	 0         3

	So if we're able to take this Course 3 without any prerequisite, then
	we would be eligible to take Course 2.
	And if you take Course 2 then you would be eligible to take Course 1.
	And if you take Course 1 then you would be eligible to take Course 0.
	And if you take Course 0, you're done. It is possible to take all the
	courses.

	Now let's assume that there was another Course:
		[[0, 1], [1, 2], [2, 3], [3, 1]]

	Now the Graph would look like this:

     --> 1 ----> 2
	 |   ^       |
	 |    \      |
	 |     \     |
	 0      3 <---

	Now there's no starting point. Let's say we start from Course 3:
	In order to take Course 3 you need to take Course 1.
	In order to take Course 1 you need to take Course 2.
	In order to take Course 2 you need to take Course 3.

	Therefore, there's a cycle and we return "false".

	This is a similar problem to Dead Lock Detection in a Single Resource
	Instance Distributed System.

	(If we have a cycle in the Graph then we will have Deadlock)
	Note: This has nothing to do with the concept of Deadlock considering
	multiple Threads)

	So we just need to find out if there's a cycle in our Directed Graph.

	This Problem can be solved using:
		Cycle Detection: Graph Coloring

	We will have a "visited" array with possible values:
	0: Unused
	1: Processed
	2: Processing

	Consider this Example:
	    3
	     \
		  -> 2
	          \
	           -> 0
	               \
	                -> 1

	So if we start from Node 2, then step by step, this will look like this:
	[0, 0, 0, 0]
	[2, 0, 0, 0]
	[2, 2, 0, 0]
	[2, 1, 0, 0]
	[1, 1, 0, 0]

	Now let's say we want to process Node 2:
	[1, 1, 0, 0]
	[1, 1, 2, 0]
	[1, 1, 1, 0]

	Now we're left only with Node 3:
	[1, 1, 1, 0]
	[1, 1, 1, 2]
	[1, 1, 1, 1] => Return "true"


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
	// int numCourses = 2;
	// std::vector<std::vector<int>> prerequisites {{1, 0}, {0, 1}};

	/* Example 3 */
	int numCourses = 4;
	std::vector<std::vector<int>> prerequisites {{0, 1}, {1, 2}, {2, 3}};

	/* Example 4 */
	// int numCourses = 4;
	// std::vector<std::vector<int>> prerequisites {{0, 1}, {1, 2}, {2, 3}, {3, 1}};



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
