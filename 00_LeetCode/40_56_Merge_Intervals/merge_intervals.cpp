#include <iostream>
#include <vector>
#include <algorithm>


/*
	==============
	=== MEDIUM ===
	==============

	===========================
	56) Merge Intervals
	===========================

	============
	Description:
	============

	Given an array of "intervals" where intervals[i] = [start_i, end_i],
	merge all overlapping intervals, and return an array of the non-overlapping
	intervals that cover all the intervals in the input.

	====================================================================
	FUNCTION: vector<vector<int>> merge(vector<vector<int>>& intervals);
	====================================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  intervals = [[1, 3], [2, 6], [8, 10], [15, 18]]
	Output: [[1, 6], [8, 10], [15, 18]]

	--- Example 2 ---
	Input:  intervals = [[1, 4], [4, 5]]
	Output: [[1, 5]]

	*** Constraints ***
	1 <= intervals.lenght <= 10^4
	intervals[i].lenght == 2
	0 <= start_i <= end_i <= 10^4

*/



/*
	------------
	--- IDEA ---
	------------

	Since intervals can be unsorted inside "intervals" vector(but 0th one is
	always smaller than 1st within the interval itself).

	So we make a "indexes" array which sorts initial indexes of intervals
	by every interval's first element(the smaller one).

	We iterate until we get to "n - 2nd" element since we are always checking
	one interval next to the current.

	We check if current interval's right element is bigger than its (sorted)
	next left element of its interval. If it is pick a bigger end of interval
	since a whole interval can be inside the other.

	Example:
	[1, 10]
	[2, 5]

	We iterate through sorted indexes and therefore through our interval in the
	right order and as long as the right element is bigger than its very next
	interval's left element, we increment 'i' by one and check further.

	Once we reach the end or once we find that current interval's right is not
	bigger than its very next interval's left, we stop and push:
	[minimal found left element, maximum found right element]

	However if certain interval don't overlap with its very next, just push
	that whole interval in the results vector.

*/



/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution{
public:
	std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& intervals)
	{
		// Base case
		if (intervals.size() == 1)
			return {intervals[0]};

		int n = intervals.size();

		int indexes[n];
		for (int i = 0; i < n; i++)
			indexes[i] = i;

		std::sort(indexes, indexes + n, [&](int n1, int n2){ return intervals[n1][0] < intervals[n2][0]; });

		std::vector<std::vector<int>> results;
		bool last_included = false;
		int i = 0;

		while (i < n - 1)
		{
			if (intervals[indexes[i]][1] >= intervals[indexes[i + 1]][0])
			{
				int start = intervals[indexes[i]][0];
				int end   = intervals[indexes[i]][1];

				while (i < n - 1 && end >= intervals[indexes[i + 1]][0])
				{
					start = std::min(start, intervals[indexes[i + 1]][0]);
					end   = std::max(end, intervals[indexes[i + 1]][1]);
					i++;
				}

				if (i == n - 1)
					last_included = true;

				std::vector<int> vec;
				vec.push_back(start);
				vec.push_back(end);

				results.push_back(vec);

			}
			else
				results.push_back(intervals[indexes[i]]);

			i++;
		}

		if (!last_included)
			results.push_back(intervals[indexes[i]]);

		return results;
	}
};

int
main()
{
	Solution sol;

	/* Example 1 */
	// std::vector<std::vector<int>> intervals = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};

	/* Example 2 */
	// std::vector<std::vector<int>> intervals = {{1, 4}, {4, 5}};

	/* Example 3 */
	// std::vector<std::vector<int>> intervals = {{1, 3}, {2, 6}, {5, 10}, {9, 18}};

	/* Example 4 */
	// std::vector<std::vector<int>> intervals = {{1, 2}, {3, 6}, {5, 10}, {9, 18}};

	/* Example 5 */
	// std::vector<std::vector<int>> intervals = {{1, 2}, {3, 6}, {5, 10}, {11, 18}};

	/* Example 6 */
	// std::vector<std::vector<int>> intervals = {{1, 4}, {0, 4}};

	/* Example 7 */
	// std::vector<std::vector<int>> intervals = {{1, 4}, {0, 1}};

	/* Example 8 */
	// std::vector<std::vector<int>> intervals = {{3, 6}, {9, 18}, {1, 2}, {5, 10}};

	/* Example 9 */
	// std::vector<std::vector<int>> intervals = {{1, 4}, {2, 3}};

	/* Example 10 */
	std::vector<std::vector<int>> intervals = {{2,3},{4,5},{6,7},{8,9},{1,10}};

	std::cout << "\n\t=======================";
	std::cout << "\n\t=== MERGE INTERVALS ===";
	std::cout << "\n\t=======================\n\n";


	/* Write Output */
	bool first = true;
	std::cout << "\n\tIntervals: [";
	for (auto x: intervals)
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
	std::cout << "]\n\n";


	std::vector<std::vector<int>> results = sol.merge(intervals);

	first = true;
	std::cout << "\n\tIntervals: [";
	for (auto x: results)
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
	std::cout << "]\n\n";

	return 0;
}
