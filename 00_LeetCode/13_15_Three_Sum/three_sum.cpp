#include <iostream>
#include <vector>
#include <algorithm>

/*
	==============
	=== MEDIUM ===
	==============
	
	===========================
	15) 3Sum
	===========================
	
	============
	Description:
	============

	Given an integer array nums, return all the triplets:
	[nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and
	num[i] + nums[j] + nums[k] == 0.
	
	=====
	Node: Notice that the solution set must not contain duplicate triplets.
	=====
	
	==========================================================
	FUNCTION: vector<vector<int>> threeSum(vector<int>& nums);
	==========================================================
	
	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================
	
	--- Example 1 ---
	Input:  nums = [-1, 0, 1, 2, -1, -4]
	Output: [[-1, -1, 2], [-1, 0, 1]]
	Explanation:
	nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0
	nums[0] + nums[2] + nums[4] = 0 + 1 + (-1) = 0
	nums[i] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0

	The distinct triples are [-1, 0, 1] and [-1, -1, 2].
	Notice that the order of the output and the order of the triplets
	does not matter.
	
	--- Example 2 ---
	Input:  nums = [0, 1, 1]
	Output: []
	Explanation: The only possible triplet does not sum up to 0.
	
	--- Example 3 ---
	Input: nums = [0, 0, 0]
	Output [[0, 0, 0]]
	Explanation: The only possible triplet sums up to 0
	
	*** Constraints ***
	3 <= nums.length <= 3000
	-10^5 <= nums[i] <= 10^5
*/

using namespace std;

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(1) or O(n), depends on the sort. Heapsort uses O(1) */
class Solution{
public:
	vector<vector<int>> threeSum(vector<int>& nums)
	{
		int n = nums.size();
		vector<vector<int>> triplets;

		// O(n * logn)
		sort(nums.begin(), nums.end());

		// O(n^2)
		for (int i = 0; i < n - 2; i++)
		{
			if (i > 0 && nums[i] == nums[i - 1])
				continue;

			int left  = i + 1;
			int right = n - 1;
			while (left < right)
			{
				int sum = nums[i] + nums[left] + nums[right];

				if (sum > 0)
					right--;
				else if (sum < 0)
					left++;
				else
				{
					std::vector<int> vec = {nums[i], nums[left], nums[right]};
					triplets.push_back(vec);

					left++;
					while (nums[left] == nums[left - 1] && left < right)
						left++;
				}
			}
		}

		return triplets;
	}

};


int
main()
{
	Solution sol;

	/* Example 1 */
	// vector<int> nums = {-1, 0, 1, 2, -1, -4};

	/* Example 2 */
	// vector<int> nums = {0, 1, 1};

	/* Example 3 */
	// vector<int> nums = {0, 0, 0};

	/* Example 4 */
	// vector<int> nums = {};

	/* Example 5 */
	vector<int> nums = {5, 2, 1, 0, -7, -3, 7, 8};

	std::cout << "\n\t=================";
	std::cout << "\n\t=== THREE SUM ===";
	std::cout << "\n\t=================\n";

	bool first = true;
	std::cout << "\n\t=== Array ===\n\t[";
	for (auto x: nums)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n\n";

	std::vector<std::vector<int>> triplets = sol.threeSum(nums);

	std::cout << "\n\t=== Triplets ===";

	if (triplets.empty())
		std::cout << "\n\t[]\n";

	int cnt = 1;
	for(auto triplet : triplets)
	{
		std::cout << "\n\t" << cnt++ << ") ";

		for (auto x : triplet)
			std::cout << x << " ";
		std::cout << "\n";
	}
	std::cout << "\n";

	return 0;
}
