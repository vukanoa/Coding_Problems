#include <iostream>
#include <vector>
#include <unordered_set>

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

	We have to check if this Graph is a Valid Tree.
	We can have something like this:

	              X
	             / \
	            X   X
	
	Let's say this is a shape of our Graph.
	Does this count as a Valid Tree? Yes!

	However, if we were to add one more edge, like this:

	              X
	             / \
	            X - X
	
	Does this count as a Valid Tree? No!
	Trees don't have cycles(loops) in them. That's what being a Tree means.
	In this problem they don't tell us that, but you should know that
	definition yourself.

	So Trees don't have loops, but there's one more condition in order it to be
	a Tree:
	        A Tree needs to be connected
	
	Consider this:

	              X
	             /  
	            X   X

	Does this count as a Valid Tree? No!
	This is not a Tree because every node has to be connected.

	To summarize - For it to be a Valid Tree:
	        1. We can't have loops inside this Graph
			2. All nodes have to be connected.
	
	Also it's worth pointing out, just in case, that a Tree doesn't have to be
	a BST or Binary Tree in general. Any node can have infinite amount of
	children.

	~~~~~~~~~~~~~~~~
	~~~ Solution ~~~
	~~~~~~~~~~~~~~~~

	First of all, we have to represent this Graph using an adjacency list
	because it will be easier to traverse this Graph and check if it is indeed
	a Valid Tree.

	Example 1:

	           0
	         / | \
	        1  2  3
	        |
	        4
	
	Is this a Valid Tree? Yes it is.
	But what kind of Algorithm can we use to determine that?

	Since now we have an adjacency list of our Graph:
	        0 : 1, 2, 3
	        1 : 0, 4
	        2 : 0
	        3 : 0
	        4 : 1
	
	For all nodes to be connected we can perform a DFS on any node. Each time
	we visit a node we'll put it in a set.
	After we finish the traversal, if set.size() is equal to n, that means that
	all of the nodes were visited which further means that all the nodes are
	indeed connected.

	We DON'T iterate through an entire adjacency list! We only start from any
	node and traverse from it. It they are all connected, our set will be
	equal to n at the end.

	We'll always start with 0 since that is the smallest value. If we had only
	one node in the entire Graph, the value would be 0. If we had two, values
	would be 0 and 1. And so on.

	So if the Graph is not empty, we'll start our DFS with a 0 node.

	But there is one problem - What if there really is a loop inside? In that
	case we would never traverse the entire Graph and we'd get a TLE.

	To prevent getting a TLE if there really is a loop inside, we have to use
	a set named "visited" to check if current node we're on was already
	traversed.

	However, there's one problem with it - Consider the same example as above:

	           0
	         / | \
	        1  2  3
	        |
	        4
	
	Adjacency List:
	        0 : 1, 2, 3
	        1 : 0, 4
	        2 : 0
	        3 : 0
	        4 : 1

	We start from 0, we check if we've already visited 0. We're not, therefore
	we push it inside of our set called "visited".

	Now we're trying to do a DFS on 0's neighbors which are: 1, 2, 3.

	First, we're on node 1.

	Have we already visited 1? No, therefore push it in our set "visited"

	Now do a DFS on 1's neighbors, which in this case, is only node 0.

	This a problem I was talking about. If we were to do a DFS on 0, we would
	conclude that there is a Loop inside of this Graph, while there really is
	not.

	So how do we handle this case?
	We have to keep track of the previous node. That's it.

	Once we're on the node 1, previous node is a node which from we've jump to
	the current node, in this case it's node 0. We've jumped on this node 1
	from 0's neighbors listed in its adjacency list.

	Therefore, we have to ignore the "previous node" in current node's list of
	adjacent nodes.

	We'll do that by passing a "prev_node" in the function DFS, and while
	iterating through the list of neighbors, if prev_node matches one of the
	neighbors in current node's adjacency list, just ignore that with
	"continue" inside the "for" loop we're using to traverse the neighbors of
	the current node.

	
	But what if we really had a Loop inside?
	           0
	         / | \
	        1  2  3
	        |    /
	        4___/
	
	Adjacency List:
	        0 : 1, 2, 3
	        1 : 0, 4
	        2 : 0
	        3 : 0, 4
	        4 : 1, 3

	Once we're on node 4, we'd ignore node 1 in 4's adjacency list of neighbors
	because node 1 is 4's previous node.

	But once we get to 4's neighbor of node 3, we'd do a DFS on it.

	Now the current node is a node 3.

	If we try to traverse 3's neighbors, we would do a DFS on node 0(again),
	since 0 is not 3's previous node(that is node 4).

	So now the current node would be node 0. We would immediately check if 0
	has already been visited and since it has, that indicated that we have
	found a loop, therefore we return "true" which tells us that there really
	is a loop inside this Graph.

	That's the whole Idea.

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

		// DFS
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
