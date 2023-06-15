#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

/*
	==============
	=== MEDIUM ===
	==============
	
	===========================
	16) 3Sum Closest
	===========================
	
	============
	Description:
	============

	Given an integer array nums of length n and an integer target, find three
	integers in nums such that the sum is closest to target.

	Return the sum of the three integers.

	=====
	Node: You may assume that each input would have exactly one solution.
	=====
	
	=========================================================
	FUNCTION: threeSumClosest(vector<int>& nums, int target);
	=========================================================
	
	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================
	
	--- Example 1 ---
	Input: nums = [-1, 2, 1, -4], target = 1
	Output: 2
	
	--- Example 2 ---
	Input: nums = [0, 0, 0], target = 1
	
	*** Constraints ***
	3 <= nums.length <= 500
	-1000 <= nums[i] <= 1000
	-10^4 <= target <= 10^4

*/

using namespace std;

/*
	IDEA: Fix the left element and for the other two, do two pointers technique
*/


/* Time  Beats: 73.77% */
/* Space Beats: 98.91% */
/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n) or O(1) based on the Sort  */
class Solution{
public:
	int threeSumClosest(vector<int>& nums, int target)
	{
		int n = nums.size();
		int closest = nums[0] + nums[1] + nums[n - 1];

		// O(n * logn)
		sort(nums.begin(), nums.end());

		// O(n^2)
		for (int i = 0; i < n - 2; i++)
		{
			int left = i + 1;
			int right  = n - 1;

			while (left < right)
			{
				int sum = nums[i] + nums[left] + nums[right];

				if (sum == target)
					return sum;
				else if (sum > target)
					right--;
				else
					left++;

				if (abs(sum - target) < abs(closest - target))
					closest = sum;
			}
		}

		return closest;
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	int target = 1;
	vector<int> nums {-1, 2, 1, -4};

	/* Example 2 */
	// int target = -2;
	// vector<int> nums = {4, 0, 5, -5, 3, 3, 0, -4, -5}; 

	/* Example 3 */
	// int target = 0;
	// vector<int> nums = {0, 0, 0}; 

	/* Example 4 */
	// int target = -7580;
	// vector<int> nums {445,891,901,-869,-747,-750,112,411,-236,443,-759,-480,
	// 				723,-702,624,-556,-763,-806,-682,-831,449,62,718,398,-937,
	// 				-353,-968,497,504,-94,494,79,-26,430,-766,439,87,899,-216,
	// 				18,-3,844,-160,351,646,-361,-375,-689,255,546,-846,294,
	// 				-964,382,-998,-994,545,-162,-13,-519,-833,533,-975,974,
	// 				920,-768,877,911,895,677,-625,-246,-355,639,499,-668,-117,
	// 				807,662,-821,-264,525,428,-675,-917,-664,-933,-620,-844,
	// 				784,-462,228,736,637,-424,395,345,-977,-980,-608,-258,-64,
	// 				64,831,591,-780,-358,691,310,866,529,156,821,-461,369,832,
	// 				-808,-16,92,-734,-485,776,192,-206,168,447,-54,-544,-192,
	// 				864,-653,-868,97,337,-902,-108,-752,695,711,-802,-823,537,
	// 				341,-477,-861,-169,77,-276,-815,-836,849,-524,-516,273,
	// 				-273,423,-102,260,-213,-197,-932,81,-248,409,-694,681,900,
	// 				-897,978,714,455,946,559,388,623,-839,-830,-935,-391,320,
	// 				-552,-755,-458,-728,583,663,-131,-727,-372,576,476,947,
	// 				220,-331,-124,39,-753,-963,284,76,-715,673,325,342,-152,
	// 				-841,-79,495,5,389,-295,-925,181,-29,68,231,-574,-78,403,
	// 				763,981,-148,-911,-711,998,-338,589,-565,-324,-673,-290,
	// 				477,-825,472,431,-386,219,-247,-798,202,417,-698,164,396,
	// 				851,-356,-527,-785,-126,-437,919,670,-644,-33,-811,602,
	// 				-606,-116,-988,-837,13,956,780,674,798,435,441,264,709,
	// 				953,232,-683,-120,318,-924,-985,-505,-232,-889,816,-564,
	// 				-428,-427,-543,-10,625,454,-626,-58,486,-92,-618,-260,
	// 				-443,577,527,949,245,-569,-285,-672,-573,-431,363,-733,
	// 				-369,843,373,-572,721,-860,526,-680,479,618,598,887,-243,
	// 				535,660,758,-71,266,-311,-528,283,-602,-24,114,-934,580,
	// 				-435,-871,-993,-319,25,-274,859,-389,-96,375,692,-749,381,
	// 				560,513,982,463,-592,336,-214,-460,374,850,-859,387,-879,
	// 				205,-511,468,6,432,-268,10,103,-507,-226,-228,-326,-515,
	// 				-422,-582,241,347,-414,-143,923,874,-89,297,-912,291,912,
	// 				-65,161,-822,-784,-230,456,-553,556,-832,421};

	std::cout << "\n\t=========================";
	std::cout << "\n\t=== THREE SUM CLOSEST ===";
	std::cout << "\n\t=========================\n";

	/* Write Input */
	bool first = true;
	std::cout << "\n\tArray:  [";
	for (auto x: nums)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]";

	std::cout << "\n\tTarget: " << target << "\n";

	/* Solution */
	int closest = sol.threeSumClosest(nums, target);

	/* Write Output */
	std::cout << "\n\tClosest sum to target: " << closest << "\n\n";

	return 0;
}