#include <iostream>
#include <vector>
#include <algorithm>


/*
	==============
	=== MEDIUM ===
	==============
	
	===========================
	18) 4Sum
	===========================
	
	============
	Description:
	============

	Given an array nums of n integers, return an array of all the unique
	quadruplets [nums[a], nums[b], nums[c], nums[d]] such that:
		0 <= a, b, c, d < n
		a, b, c, and d are distinct
		nums[a] + nums[b] + nums[c] + nums[d] == target

	=====
	Node: You may return the answer in any order.
	=====
	
	=====================================================================
	FUNCTION: vector<vector<int>> fourSum(vector<int>& nums, int target);
	=====================================================================
	
	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================
	
	--- Example 1 ---
	Input:  nums = [1, 0, -1, 0, -2, 2], target = 0
	Output: [[-2, -1, 1, 2], [-2, 0, 0, 2], [-1, 0, 0, 1]]
	
	--- Example 2 ---
	Input:  nums = [2, 2, 2, 2, 2], target = 8
	Output: [[2, 2, 2, 2]]
	
	*** Constraints ***
	1 <= nums.length <= 200
	-10^9 <= nums[i] <= 10^9
	-10^9 <= target  <= 10^9

*/


using namespace std;


/* Time  Complexity: O(n^(k - 1)), or O(n^3) for 4Sum. We have k - 2 loops, and
two_sum is O(n)*/
/* Space Complexity: O(n). We need O(k) space for the recursion. k can be the
same as n in the worst case for the generalized algorithm.*/
class Solution{
public:
	vector<vector<int>>
	fourSum(vector<int>& nums, int target)
	{
		sort(nums.begin(), nums.end());
		return k_sum(nums, target, 0, 4);
	}

	vector<vector<int>>
	k_sum(vector<int>& nums, long long target, int start, int k)
	{
		vector<vector<int>> vec_results;

		if (start == nums.size())
			return vec_results;

		/*
			There are k remaining values to add to the sum.
			The average of these values is at least "target / k"
		*/
		long long average_value = target / k;

		if (nums[start] > average_value || average_value > nums.back())
			return vec_results;

		if (k == 2)
			return two_sum(nums, target, start);
		
		for (int i = start; i < nums.size(); i++)
		{
			if (i == start || nums[i - 1] != nums[i])
			{
				for (vector<int>& subset : k_sum(nums, static_cast<long long>(target) - nums[i], i + 1, k - 1))
				{
					vec_results.push_back({nums[i]});
					vec_results.back().insert(vec_results.back().end(), subset.begin(), subset.end());
				}
			}
		}

		return vec_results;
	}

	vector<vector<int>> two_sum(vector<int>& nums, long long target, int start)
	{
		vector<vector<int>> vec_results;
		int front = start;
		int rear  = nums.size() - 1;

		while (front < rear)
		{
			int sum = nums[front] + nums[rear];

			if (sum < target || (front > start && nums[front] == nums[front - 1]))
				front++;
			else if (sum > target || (rear < nums.size() - 1 && nums[rear] == nums[rear + 1]))
				rear--;
			else
				vec_results.push_back({nums[front++], nums[rear--]});
		}

		return vec_results;
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	vector<int> nums = {1, 0, -1, 0, -2, 2};
	int target = 0;

	/* Example 2 */
	// vector<int> nums = {2, 2, 2, 2, 2};
	// int target = 8;

	std::cout << "\n\t================";
	std::cout << "\n\t=== Four Sum ===";
	std::cout << "\n\t================\n";

	vector<vector<int>> vec_results = sol.fourSum(nums, target);

	cout << "\n\tOriginal Vector: ";
	for (const auto& x : nums)
		cout << x << " ";
	cout << "\n\tTarget: " << target << "\n";

	cout << "\n\tResults:";
	vector<vector<int>> ::iterator it;
	it = vec_results.begin();
	for (it; it != vec_results.end(); it++)
	{
		cout << "\n\t" << it - vec_results.begin() + 1 << ") ";
		for(vector<int>::iterator it2 = it->begin(); it2 != it->end(); ++it2)
			cout << *it2 << " ";
	}
	cout << "\n\n";

	return 0;
}
