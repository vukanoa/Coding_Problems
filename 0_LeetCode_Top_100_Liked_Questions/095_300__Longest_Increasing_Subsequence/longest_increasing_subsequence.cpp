#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map> // TLE Solution

/*
	==============
	=== MEDIUM ===
	==============

	===================================
	300) Longest Increasing Subsequence
	===================================

	============
	Description:
	============

	Given an integer array "nums", return the length of the longest strictly
	increasing subsequence.

	Follow Up: Can you come up with an algorithm that runs in O(n * logn) time
	complexity?

	=============================================
	FUNCTION: int lengthOfLIS(vector<int>& nums);
	=============================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  nums = [10, 9, 2, 5, 3, 7, 101, 18]
	Output: 4
	Explanation: The longest increasing subsequence is [2, 3, 7, 101],
	therefore the length is 4.

	--- Example 2 ---
	Input:  nums = [0, 1, 0, 3, 2, 3]
	Output: 4

	--- Example 3 ---
	Input:  [7, 7, 7, 7, 7, 7, 7]
	Output: 1

	*** Constraints ***
	1 <= nums.length <= 2500
	-10^4 <= nums[i] <= 10^4

*/


class Solution_TLE {
public:
	int lengthOfLIS(std::vector<int>& nums)
	{
		int n = nums.size();
		std::unordered_map<int, std::vector<int>> umap;
		int max = 1;

		for (int i = 0; i <= n; i++)
			umap[i] = {};

		for (int i = 0; i < nums.size(); i++)
		{
			umap[1].push_back(nums[i]);

			for (int j = i; j > 0; j--)
			{
				if (umap[j].empty())
					continue;

				bool exist = false;
				for (int k = 0; k < umap[j].size(); k++)
				{
					if (umap[j][k] < nums[i])
					{
						umap[j + 1].push_back(nums[i]);
						
						if (j + 1 > max)
							exist = true;
					}
				}

				if (exist)
					max++;
			}
		}

		return max;
	}
};




/*
	------------
	--- IDEA ---
	------------

	DFS with Cache.
	TODO
	
*/


/* Time  Beats: 35.56% */
/* Space Beats: 50.84% */
class Solution_DFS_with_Cache_DP {
public:
	int lengthOfLIS(std::vector<int>& nums)
	{
		int n = nums.size();
		std::vector<int> LIS (n, 1);

		for (int i = n - 1; i >= 0; i--)
		{
			for (int j = i + 1; j < n; j++)
			{
				if (nums[i] < nums[j])
					LIS[i] = std::max(LIS[i], 1 + LIS[j]);
			}
		}

		return *std::max_element(LIS.begin(), LIS.end());
	}
};




/*
	------------
	--- IDEA ---
	------------

	This is a classic Dynamic Programming problem.

	Let dp[i] be the longest increase subsequence of nums[0..i] where nums[i]
	is the last element of the subsequence.

	It's pretty much self-explanatory. Just simulate one example by going
	through the code and it will be clear.

*/

/* Time  Beats: 64.76% */
/* Space Beats: 69.51% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n) */
class Solution_DP{
public:
	int lengthOfLIS(std::vector<int>& nums)
	{
		int n = nums.size();
		std::vector<int> dp(n, 1);

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < i; j++)
			{
				if (nums[i] > nums[j] && dp[i] < dp[j] + 1)
					dp[i] = dp[j] + 1;
			}
		}

		return *std::max_element(dp.begin(), dp.end());
	}
};




/*
	------------
	--- IDEA ---
	------------

	Greedy with Binary Search

	Let's construct the idea from following example.

		nums = [2, 6, 8, 3, 4, 5, 1],

	let's try to build the increasing subsequences starting with an empty one

		sub1 = [].

	1. Let pick the first element, sub1 = [2]


	2. 6 is greater than the previous number.

		   sub1 = [2, 6]


	3. 8 is greater than previous number.

		   sub1 = [2, 6, 8]


	4. 3 is less than previous number, therefore we can't extend the
	   subsequence sub1, but we must keep 3 because in the future the longest
	   subsequence may start with [2, 3]. Now we have:

		sub1 = [2, 6, 8],
		sub2 = [2, 3]


	5. With 4, we can't extend sub1, but we can extend sub2, so:

		   sub1 = [2, 6, 8],
		   sub2 = [2, 3, 4]

	6. With 5, we can't extend sub1, but we can extend sub2, so:

		   sub1 = [2, 6, 8],
		   sub2 = [2, 3, 4, 5]


	7. With 1, we can't extend neither sub1 nor sub2, but we need to keep 1,
	   so:
		   sub1 = [2, 6, 8],
		   sub2 = [2, 3, 4, 5],
		   sub3 = [1]


	8. Finally, length of the longest increase subsequence = len(sub2) = 4


	~~~~~~~~~~~~
	~~~ Note ~~~
	~~~~~~~~~~~~
	Now this optimization is not intuitive to me AT ALL. If you find it hard
	to grasp, it's okay.

	In the above steps, we need to keep different "sub" arrays

		(sub1, sub2, sub3, ..., subk)

	which causes poor performance. But we are noticing that we can just keep
	one "sub" array, when new number 'x' is not greater than the last element
	of the subsequence "sub" we do a binary search to find the smallest
	element >= x in "sub", and replace with number x.


	Let's run that example again:
		
		nums = [2, 6, 8, 3, 4, 5, 1] again:

	1. Let's pick the first element,

		   sub = [2]


	2. 6 is greater than the previous number,

		   sub = [2, 6]


	3. 8 is greater than the previous number,

		   sub = [2, 6, 8]


	4. 3 is less than the previous number, so we can't extend the subsequence
	   sub. We need to find the smallest number that is >= 3 in "sub", it's 6.
	   Then we overwrite it, now:

		   sub = [2, 3, 8].


	5. 4 is less than previous number so we can't extend the subsequence sub.
	   We overwrite 8 by 4, so:

		   sub = [2, 3, 4]


	6. 5 is greater than the previous number:

		   sub = [2, 3, 4, 5]


	7. 1 is less than previous number, so we can't extend the subsequence sub,
	   We overwrite 2 by 1, so:

		   sub = [1, 3, 4, 5].


	8. Finally, length of the longest increase subsequence = len(sub) = 4

*/

/* Time  Beats:   100% */
/* Space Beats: 87.72% */

/*	Time  Complexity: O(n * logn) */
/*
	Space Complexity: O(n)
	We can achieve O(1) in space by overwriting values of "sub" into original
	"nums" array. But in order to do that we'd have to be sure that is
	permitted.
*/
class Solution_Greedy_Binary{
public:
	int lengthOfLIS(std::vector<int> &nums)
	{
		std::vector<int> sub;

		for (int& x : nums)
		{
			if (sub.empty() || sub[sub.size() - 1] < x)
				sub.push_back(x);
			else
			{
				// Search for first element e such that x <= e
				auto it = std::lower_bound(sub.begin(), sub.end(), x);
				*it = x;
			}
		}

		return sub.size();
	}
};




/*
	------------
	--- IDEA ---
	------------

	Binary Indexed Tree(Increase base of "nums" into one-basing indexing)

	- Let f[x] be the length of longest increase subsequence, where all number
	in the subsequence are <= x. This is the max element in indices [1..x] if
	we build the Binary Indexed Tree(BIT)

	- Since -10^4 <= nums[i] <= 10^4, we can convert nums into:
	      1 <= nums[i] <= 2 * 10^4 + 1 by plus base=10001 to store into the BIT

	- We build Max BIT, which has 2 operators:
		- get(idx): Return the maximum value of indices in range [1..idx].
		- update(idx, val): Update a value "val" into BIT at index "idx".

	- Iterate numbers "i" in range [0..n-1]:
		- subLongest = bit.get(nums[i] - 1) // Get longest increasing
		  // subsequence so far, which idx < nums[i], or idx <= nums[i] - 1
		- bit.update(nums[i], subLongest + 1) // Update latest longest to the
		  BIT.

	- The answer is bit.get(20001) // Maximum of all elemenst in the BIT

*/

/* Time  Beats: 95.35% */
/* Space Beats: 29.4% */

/*
	Time  Complexity: O(n * logMAX)
	where MAX <= 20000 is the difference between minimum and maximum elements
	in nums, N <= 2500 is the number of elements in array nums.
*/
/*
	Space Complexity: O(MAX)
*/
class MaxBIT {
private:
	std::vector<int> bit;

public:
	MaxBIT(int size)
	{
		bit.resize(size + 1);
	}

	int get(int idx)
	{
		int ans = 0;
		for (; idx > 0; idx -= idx & -idx)
			ans = std::max(ans, bit[idx]);

		return ans;
	}

	void update(int idx, int val)
	{
		for(; idx < bit.size(); idx += idx & -idx)
			bit[idx] = std::max(bit[idx], val);
	}

};

class Solution_BIT {
public:
	int lengthOfLIS(std::vector<int>& nums)
	{
		int base = 10001;
		MaxBIT bit(20001);

		for (int x : nums)
		{
			int subLongest = bit.get(base + x - 1);
			bit.update(base + x, subLongest + 1);
		}

		return bit.get(20001);
	}
};




/*
	------------
	--- IDEA ---
	------------

	Binary Indexed Tree(Compress nums into values [i..N])

	In previous solution(the one above this one), -10^4 <= nums[i] <= 10^4 is
	small enough, so we can store in our Binary Indexed Tree (BIT)

	Can we store when -10^9 <= nums[i] <= 10^9 is very big? In that case, we
	can compress our nums array while keeping the relative comparation order
	between numbers.

	How to compress?
		- In the nums array the length n, where n <= 2500, there are maximum n
		  different numbers.

		- We can ge the unique values of numbers in nums, and sort those values
		  in increasing order, let's name it uniqueSorted.

		- Then we traverse i in ragen [0..n-1], we get the compressed value of
		  nums[i] by looking hte index in uniqueSorted.

		- As the result, elements in nums is compressed into values in range
		  [1..N]

*/

// ##### This Solution uses the same Max BIT class as the Solution above #####

/* Time  Beats: 75.39% */
/* Space Beats: 37.24% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution_BIT_Compress {
public:
	int lengthOfLIS(std::vector<int>& nums)
	{
		int nUnique = compress(nums);
		MaxBIT bit(nUnique);

		for(int x : nums)
		{
			int subLongest = bit.get(x - 1);
			bit.update(x, subLongest + 1);
		}

		return bit.get(nUnique);
	}

	int compress(std::vector<int>& arr)
	{
		std::vector<int> uniqueSorted(arr);
		std::sort(uniqueSorted.begin(), uniqueSorted.end());
		uniqueSorted.erase(unique(uniqueSorted.begin(), uniqueSorted.end()), uniqueSorted.end()); // Remove duplicated values

		for (int& x: arr)
			x = lower_bound(uniqueSorted.begin(), uniqueSorted.end(), x) - uniqueSorted.begin() + 1;

		return uniqueSorted.size();
	}
};

int
main()
{
	Solution_DFS_with_Cache_DP sol_dfs_cache_dp;
	Solution_DP                sol_dp;
	Solution_Greedy_Binary     sol_grd_bin; // Efficient!
	Solution_BIT               sol_bit;
	Solution_BIT_Compress      sol_bit_com;


	/* Example 1 */
	std::vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};

	/* Example 2 */
	// std::vector<int> nums = {0, 1, 0, 3, 2, 3};

	/* Example 3 */
	// std::vector<int> nums = {7, 7, 7, 7, 7, 7, 7};

	std::cout << "\n\t======================================";
	std::cout << "\n\t=== LONGEST INCREASING SUBSEQUENCE ===";
	std::cout << "\n\t======================================\n";


	/* Write Input */
	bool first = true;
	std::cout << "\n\tArray: [";
	for (auto x: nums)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n";


	/* Solution */
	// int longest = sol_dfs_cache_dp.lengthOfLIS(nums);
	// int longest = sol_dp.lengthOfLIS(nums);
	int longest = sol_grd_bin.lengthOfLIS(nums);
	// int longest = sol_bit.lengthOfLIS(nums);
	// int longest = sol_bit_com.lengthOfLIS(nums);


	std::cout << "\n\tLongest Increasing Subsequence: " << longest << "\n\n";

	return 0;
}