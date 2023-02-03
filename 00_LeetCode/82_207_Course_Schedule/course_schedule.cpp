#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

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



/*
	------------
	--- IDEA ---
	------------

	Consider this Graph represented:
		1. Adjacency Matrix
		2. ASCII picture

	1. Adjacency Matrix
	   [[5, 3], [5, 1], [7, 3], [7, 0], [6, 3], [6, 4], [3, 0], [3, 2], [4, 1]]

	2. ASCII Picture
	   2    0    1
	   |   /|   /|
	   |  / |  / |
	   | /  | /  |
	   v    |/   v
	   3----/--  4
	   | \ /| |  |
	   |  \ | |__|
	   | / \|    |
	   v    v    v
	   5    7    6

	Valid Topological Orders for this Graph would be:
		1)
		    2, 0, 1, 3, 4, 5, 7, 6 (Visual left to right, top to bottom)

		2)
		    0, 1, 2, 3, 4, 5, 6, 7 (smallest-numbered available vertex first)

		3)
		    2, 0, 1, 4, 3, 5, 7, 6 (fewest edges first)

		4)
		    2, 0, 3, 7, 1, 5, 4, 6 (largest-numbered available vertex first)

		5)
		    2, 0, 3, 1, 5, 7, 4, 6 (arbitrary)

	Kahn's Algorithm:
		Find a list of "start nodes" where there are no incoming edges and
		collect them into a set startSet(or zeroSet), at least one such node
		should exist in a non-empty ACYCLIC graph; "result" is the empty list
		that will contain the sorted elements.

		-------------------
		--- Pseudo Code ---
		-------------------

		while startSet is no empty:
			take a node "n" from "startSet"
			add "n" to the tail of "result"
			for each node "m" with an edge "e" from "n" to "m":
				mark "e" as removed
				if "m" does not have incoming edges anymore:
					add "m" into "startSet"

		if graph still has edges
			return false
		else
			return true

*/


/* This one is slower than DFS Solution*/
/* Time  Complexity: O(V + E) */
/* Space Complexity: O(V) */
class Solution_Topological{
public:
	bool canFinish(int numCourses, std::vector<std::vector<int>>& prerequisites)
	{
		int n = prerequisites.size();

		std::vector<int> indegree(numCourses, 0);


        for (int i = 0; i < prerequisites.size(); i++)
            indegree[prerequisites[i][0]]++;

		std::unordered_set<int> zeroDegree;
		for (int i = 0; i < numCourses; i++)
		{
			if (indegree[i] == 0)
				zeroDegree.insert(i);
		}

		if (zeroDegree.empty())
			return false;

		while (!zeroDegree.empty())
		{
			auto it = zeroDegree.begin();
			int course = *it;

			zeroDegree.erase(course);

			for (const auto& pre : prerequisites)
			{
				if (course == pre[1])
				{
					indegree[pre[0]]--;

					if (indegree[pre[0]] == 0)
						zeroDegree.insert(pre[0]);
				}
			}
		}

		for (int& num : indegree)
		{
			if (num != 0)
				return false;
		}

		return true;
	}
};


/* Using Queue */
/* This Topological Sort is a lot faster than the above one */
/* Time  Complexity: O(V + E) */
/* Space Complexity: O(V) */
class Solution_Topological_2{
public:
	bool canFinish(int n, std::vector<std::vector<int>>& pre)
	{
	    std::vector<std::vector<int>> adj(n, std::vector<int>());
	    std::vector<int> degree(n, 0);

	    for (int i = 0; i < pre.size(); i++)
		{
	        adj[pre[i][1]].push_back(pre[i][0]);
	        degree[pre[i][0]]++;
	    }

	    std::queue<int> q;

	    for (int i = 0; i < n; i++)
	        if (degree[i] == 0) q.push(i);

	    while (!q.empty())
		{
	        int curr = q.front(); q.pop(); n--;

	        for (auto next: adj[curr])
			{
	            if (--degree[next] == 0)
					q.push(next);
			}
	    }

	    return n == 0;
	}
};


int
main()
{
	// Solution sol;
	// Solution_Topological sol_topo;
	Solution_Topological_2 sol_topo_2;

	/* Example 1 */
	// int numCourses = 2;
	// std::vector<std::vector<int>> prerequisites {{1, 0}};

	/* Example 2 */
	// int numCourses = 2;
	// std::vector<std::vector<int>> prerequisites {{1, 0}, {0, 1}};

	/* Example 3 */
	// int numCourses = 4;
	// std::vector<std::vector<int>> prerequisites {{0, 1}, {1, 2}, {2, 3}};

	/* Example 4 */
	// int numCourses = 4;
	// std::vector<std::vector<int>> prerequisites {{0, 1}, {1, 2}, {2, 3}, {3, 1}};

	/* Example 5 */
	int numCourses = 8;
	std::vector<std::vector<int>> prerequisites {{5, 3}, {5, 1}, {7, 3}, {7, 0}, {6, 3}, {6, 4}, {3, 0}, {3, 2}, {4, 1}};



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
	// if (sol.canFinish(numCourses, prerequisites))
	// if (sol_topo.canFinish(numCourses, prerequisites))
	if (sol_topo_2.canFinish(numCourses, prerequisites))
		std::cout << "\n\tResult: Possible!\n\n";
	else
		std::cout << "\n\tResult: Impossible!\n\n";


	return 0;
}
