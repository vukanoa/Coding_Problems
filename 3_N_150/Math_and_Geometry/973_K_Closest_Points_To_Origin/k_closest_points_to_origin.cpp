#include <iostream>
#include <vector>
#include <algorithm>

/*
	==============
	=== MEDIUM ===
	==============

	===============================
	973) K Closest Points to Origin
	===============================

	============
	Description:
	============

	Given an array of points where points[i] = [xi, yi] represents a point on
	the X-Y plane and an integer k, return the k closest points to the origin
	(0, 0).

	The distance between two points on the X-Y plane is the Euclidean distance
	(i.e., √(x1 - x2)^2 + (y1 - y2)^2).

	You may return the answer in any order. The answer is guaranteed to be
	unique (except for the order that it is in).

	===========================================================================
	FUNCTION: vector<vector<int>> kClosest(vector<vector<int>>& points, int k);
	===========================================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: points = [[1,3],[-2,2]], k = 1
	Output: [[-2,2]]
	Explanation:
	The distance between (1, 3) and the origin is sqrt(10).
	The distance between (-2, 2) and the origin is sqrt(8).
	Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.
	We only want the closest k = 1 points from the origin, so the answer is
	just [[-2,2]].


	--- Example 2 ---
	Input: points = [[3,3],[5,-1],[-2,4]], k = 2
	Output: [[3,3],[-2,4]]
	Explanation: The answer [[-2,4],[3,3]] would also be accepted.


	*** Constraints ***
	1 <= k <= points.length <= 10^4
	-10^4 <= xi, yi <= 104

*/

/*
	------------
	--- IDEA ---
	------------

	Since we're looking for the distance between point P and Origin(0, 0), we
	don't really have to use this formula: √(x1 - x2)^2 + (y1 - y2)^2).

	Actually we do, but we don't need to pass x2 and y2 since they are always
	going to be 0.

	So when we're calculating the distance between point P and Origin(0, 0), we
	can do it like this: √x1^2 + y1^2).

	We calculate the distance for each point and store it in a vector of pairs
	named "distances":
	distances = ( {<distance>, [xi, yi]}, {<distance>, [xi, yi]}, ...)

	After we're doing processing each point, we sort it by the first value,
	i.e. "distance".

	Then just iterate from 0 to k and push Points to vector "results".

*/

/* Time  Beats: 56.04% */
/* Space Beats: 24.83% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution {
public:
	std::vector<std::vector<int>> kClosest(std::vector<std::vector<int>>& points, int k)
	{
		std::vector<std::pair<double, std::vector<int>>> distances;

		for (auto& point : points)
			distances.push_back({euclidean_distance(point[0], point[1]), point});

		std::sort(distances.begin(), distances.end());

		std::vector<std::vector<int>> results;
		int i = 0;
		while (i < k)
			results.push_back(distances[i++].second);

		return results;
	}

private:
	double euclidean_distance(int& x1, int& y1)
	{
		return sqrt(x1*x1 + y1*y1);
	}
};
