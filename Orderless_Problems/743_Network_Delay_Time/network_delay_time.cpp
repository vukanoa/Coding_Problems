#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <unordered_set>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	743) Network Delay Time
	===========================

	============
	Description:
	============

	You are given a network of n nodes, labeled from 1 to n. You are also given
	times, a list of travel times as directed edges times[i] = (ui, vi, wi),
	where ui is the source node, vi is the target node, and wi is the time it
	takes for a signal to travel from source to target.

	We will send a signal from a given node k. Return the minimum time it takes
	for all the n nodes to receive the signal. If it is impossible for all the
	n nodes to receive the signal, return -1.

	=========================================================================
	FUNCTION: int networkDelayTime(vector<vector<int>>& times, int n, int k); 
	=========================================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	              1
	     1 <-------------- 2
	                       |
	                       |
	                       | 1
	                       |
	                       |
	               1       v
	     4 <-------------- 3


	Input: times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
	Output: 2




	--- Example 2 ---
	Input: times = [[1,2,1]], n = 2, k = 1
	Output: 1



	--- Example 3 ---
	Input: times = [[1,2,1]], n = 2, k = 2
	Output: -1


	*** Constraints ***
	1 <= k <= n <= 100
	1 <= times.length <= 6000
	times[i].length == 3
	1 <= ui, vi <= n
	ui != vi
	0 <= wi <= 100
	All the pairs (ui, vi) are unique. (i.e., no multiple edges.)

*/

/* Time  Beats: 88.97% */
/* Space Beats: 58.83% */

/* Time  Complexity: O(E * logV) */
/* Space Complexity: O(V) */
class Solution {
public:
	int networkDelayTime(std::vector<std::vector<int>>& times, int n, int k)
	{
		std::unordered_map<int, std::vector<std::pair<int, int>>> edges;

		// Make edges
		for (int i = 0; i < times.size(); i++)
			edges[times[i][0]].push_back({times[i][2], times[i][1]});

		auto compare_pairs = [](const std::pair<int, int>& a, const std::pair<int, int>& b){
			return a.first > b.first;
		};

		// Push {0, Starting Node} to Min Heap
		std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(compare_pairs)> min_heap(compare_pairs);
		min_heap.push({0, k});

		// Initialize set
		std::unordered_set<int> uset_visit;
		int time = 0;

		while (!min_heap.empty())
		{
			auto heap_top = min_heap.top();
			min_heap.pop();

			int curr_weight = heap_top.first;
			int curr_node   = heap_top.second;

			if (uset_visit.find(curr_node) != uset_visit.end())
				continue;

			uset_visit.insert(curr_node);
			time = std::max(time, curr_weight);

			for (const auto& entry : edges[curr_node])
			{
				int weight = entry.first;
				int node   = entry.second;

				if (uset_visit.find(node) == uset_visit.end())
					min_heap.push({curr_weight + weight, node});
			}
		}

		return uset_visit.size() == n ? time : -1;
	}
};


int
main()
{
	Solution sol;

	std::vector<std::vector<int>> times = {{2, 1, 1}, {2, 3, 1}, {3, 4, 1}};
	int n = 4;
	int k = 2;


	int res = sol.networkDelayTime(times, n, k);

	std::cout << "\n\tResult: " << res << "\n\n";

	return 0;
}

