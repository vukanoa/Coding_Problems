#include <iostream>
#include <vector>
#include <unordered_map>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	560) Subarray Sum Equals K
	===========================

	============
	Description:
	============

	Given an array of integers "nums" and an integer 'k', return the total
	number of subarrays whose sum equals to 'k'.

	A subarray is a contiguous non-empty sequence of elements within an array.

	====================================================
	FUNCTION: int subarraySum(vector<int>& nums, int k);
	====================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  nums = [1, 1, 1], k = 2
	Output: 2

	--- Example 2 ---
	Input:  nums = [1, 2, 3], k = 3
	Output: 2

	*** Constraints ***
	1 <= nums.length <= 2 * 10^4
	-1000 <= nums[i] <= 1000
	-10^7 <= k <= 10^7

*/


/*
	------------
	--- IDEA ---
	------------

	This approach, while a bit optimized, is still a Brute Force Solution.

	Consider this example:
		[-1, 1, 0, 1, -1]

	If we were to calculate every subbaray starting with index 0, we would get
	[-1, 0, 0, 1, 0]
	  0  1  2  3  4

	Now if we wanted to calculate every subbaray starting with index 0, we can
	immediately notice that we're doing a repeated work.
	For example:
		Subarray [1, 0, 1] of original array [-1, 1, 0, 1, -1]

	We can see that we do a repeated work since subarray (1, 3) is a subarray
	(0, 3) minus nums[0];

	So every time we're calculating subarray we can use the previous row, thus
	we don't even have to use a matrix, but it's easier for explanation since
	this is not an optimal solution anyway.

	We would only have elemets on the right diagonal and above inside the
	matrix dp.

	DP:

		   | -1  |  1  |  0  |  1  | -1  |
		---+-----+-----+-----+-----+------
		-1 |  -1 |  0  |  0  |  1  |  0  |
		---+-----+-----+-----+-----+------
		 1 |     |  1  |  1  |  2  |  1  |
		---+-----+-----+-----+-----+------
		 0 |     |     |  0  |  1  |  0  |
		---+-----+-----+-----+-----+------
		 1 |     |     |     |  1  |  0  |
		---+-----+-----+-----+-----+------
		-1 |     |     |     |     | -1  |

	You can clearly see that, for example:
		dp[2][3] = d[2 - 1][3] - nums[2- 1]

	However, this is still an O(N^2) approach, it's still Brute Force.

*/


/* Brute Force, a bit optimized, but still Brute Force */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N^2) */
class Solution_Brute_DP {
public:
    int subarraySum(std::vector<int>& nums, int k)
    {
        if (nums.size() == 1)
        {
            if (nums[0] == k)
                return 1;

            return 0;
        }

        int n = nums.size();
		std::vector<std::vector<int>> dp(n, std::vector<int>(n));

        dp[0][0] = nums[0];
        int count = (nums[0] == k) ? 1 : 0;

        for (int j = 1; j < n; j++)
        {
            dp[0][j] = nums[j] + dp[0][j - 1];

            if (dp[0][j] == k)
                count++;
        }

        for (int i = 1; i < n; i++)
        {
            for (int j = i; j < n; j++)
            {
                if (i == j)
                    dp[i][j] = nums[i];
                else
                    dp[i][j] = dp[i - 1][j] - nums[i - 1];

                if (dp[i][j] == k)
                    count++;
            }
        }

        return count;
    }
};







/*
	------------
	--- IDEA ---
	------------

	Consider this example:
		[1, 1, 1, 1, 1, 1], k = 3

	We are increasing the "window" by one place at a time. So:
		 0  1  2  3  4  5
		[1, 1, 1, 1, 1, 1]
		 #
		 #  #
		 #  #  #
		 #  #  #  #

	Look at last subarray of length 4.

	So far Sum = 4
	So what are we looking here?
	Can we chop off some prefix of this subarray a prefix such that we can make
	this Sum(= 4) match our given k?

	The answer is yes.
	We can calculate it:

	Sum = 4
	Sum - k => 4 - 3 = 1

	If we can chop off a prefix of 1 we will still have a contiguous subarray
	that will exactly match k.

	Now the only question is: Does there exist a prefix in this subarray(not
	in the entire array), but in the portion(subbaray 0 - 4 inclusively)
	we're currently on, starting with the beginning that we can remove, because
	remember that we want a contiguous subarray.

	Can we chop-off a prefix that has an exact value of 1?
	We can if we maintain a Hash Map:

		{Prefix : Count }
		|       |       |
		|       |       |
		|       |       |
		|       |       |
		|       |       |

	If every time we compute a prefix and we add it to our Hash Map and count
	how many prefixes have a value of 1.
	And the reason we're counting is, remember that we could possibly have
	negative values, for example:
		 0   1  2  3  4  5
		[1, -1, 1, 1, 1, 1]

	There could be multiple prefixes that sum up to 1. So that's why we have
	to count it in our Hash Map.

	Contiguous Sum equals to one is:
		Index 0 (1)
		Index 0 + index 1 + index 2 (1 + (-1) + 1)

	But also, we cannot just count every prefix before we actually start
	building up our result, we have to do it simultaneously.

	Why?
	Consider this:
		 0   1  2  3  4  5
		[1, -1, 1, 1, -1, 1]

	If we were to calculate prefixes beforehand, then our count wouldn't be
	right because we would remove subarrays that sum up, in this case, to 1
	but come afterwards.

	Look at this:
		 0   1  2  3   4   5
		[1, -1, 1, 3, -1, -1], k = 3
		 #   #  #  #

		 In this case, before-hand calculated Hash Map would look like:

		{Prefix : Count }
		|   1   |  3    | // Ind 0, (ind 0 + ind 1, ind 2), (ind 0+1+2+3+4+5)
		|  .... | ....  |
		|  .... | ....  |
		|  .... | ....  |
		|  .... | ....  |

	So we would't "Chop-off" a prefix of
		(ind 0+1+2+3+4+5)

	From a subbarray:
		(Ind 0+1+2+3)

	That would be fallacious, thus we have to form this prefix Hash Map only
	while we're going through the array, since we do a O(n) approach.

	So when we're at this point:
		 0  1  2  3  4  5
		[1, 1, 1, 1, 1, 1]
		 #  #  #  #

	We only want to remove the prefixes that are a subarray of the #'ed part,
	which is only Index 0.

	Only subbarray that are starting from the beginning and are smaller than
	the current subarray.

	Index 0 is a subbarray to our currently checking [0 - 3] subarray thus
	since subbaray of index 0 ({1}) is equal to 1, and current sum is equal to
	4 then:
		sum - k = 1 and 1 exists in the prefixes Hash Map once, we say that
		there is "count" times to sum up to k value, so far.

	So if key of:
		sum - k
	doesn't exist in the Hash Map then insert that key and set its count to 1.

	However, if it indeed does exist then add "count" value to our result that
	is counting the total amount of ways we can contiguously summing get a
	value of k.

	Also, at the beginning it's important to put key 0 inside the Hash Map and
	immediately set its value to 1.

	Why?
	Basically we're saying - There is an empty Prefix that sum up to 0.
		 0  1  2  3  4  5
		[1, 1, 1, 1, 1, 1], k = 1
		 #

		current_sum = 1
		k = 1

		current_sum - k => 1 - 1 = 0

		Check if 0 exist in the Hash Map. If we didn't add this as our base
		case then at this point instead of adding 1 way to the total ways
		of contiguously summing up to k, we would just insert: {0 : 1} in our
		Hash Map.

		That would give us the wrong result at the end. That's why we must do
		this base case beforehand.



##################################################################
########################## ALGORITHM #############################
##################################################################


	Let's walk through the Algorithm:
		 0   1  2  3  4  5
		[1, -1, 1, 1, 1, 1], k = 3

		{Prefix : Count }
		|   0   |   1   |
		|       |       |
		|       |       |
		|       |       |
		|       |       |



------------------------------------------------------------------



	1)
		 0   1  2  3  4  5
		[1, -1, 1, 1, 1, 1], k = 3
		 #

		sum = 1
		k = 3
			sum - k => 1 - 3 = -2

		Do we have a -2 in our Prefix Map that we can potentially remove from
		this subbarray which would give us a total sum as the target k?
			No, we don't.

		if (-2 exist in HasMap)
			total += hashmap[-2];

		// Anyway, we must do this
		if (sum exist in HashMap)
			hashmap[sum]++;
		else
			hashmap.insert({1 : 1}); // We add our curent sum, i.e. prefix

		{Prefix : Count }
		|   0   |   1   |
		|   1   |   1   | // Added
		|       |       |
		|       |       |
		|       |       |




------------------------------------------------------------------



	2)
		 0   1  2  3  4  5
		[1, -1, 1, 1, 1, 1], k = 3
		 #   #

		sum = 0
		k = 3
			sum - k => 0 - 3 = -3

		Do we have a -3 in our Prefix Map that we can potentially remove from
		this subbarray which would give us a total sum as the target k?
			No, we don't.

		if (-3 exist in HasMap)
			total += hashmap[-3];

		// Anyway, we must do this
		if (sum exist in HashMap)
			hashmap[sum]++;
		else
			hashmap.insert({0 : 1}); // We add our curent sum, i.e. new prefix


		{Prefix : Count }
		|   0   |   2   | // Increase count, since current sum is 0
		|   1   |   1   |
		|       |       |
		|       |       |
		|       |       |



------------------------------------------------------------------



	3)
		 0   1  2  3  4  5
		[1, -1, 1, 1, 1, 1], k = 3
		 #   #  #

		sum = 1
		k = 3
			sum - k => 1 - 3 = -2

		Do we have a -2 in our Prefix Map that we can potentially remove from
		this subbarray which would give us a total sum as the target k?
			No, we don't.


		if (-2 exist in HasMap)
			total += hashmap[-2];

		// Anyway, we must do this
		if (sum exist in HashMap)
			hashmap[sum]++;
		else
			hashmap.insert({1 : 1}); // We add our curent sum, i.e. new prefix


		{Prefix : Count }
		|   0   |   2   |
		|   1   |   2   | // Increase count, since current sum is 1
		|       |       |
		|       |       |
		|       |       |


		What this actually tells us:
			{Prefix : Count }
			|   1   |   2   | // Increase count, since current sum is 1

		is that there are now 2 ways, withing the current "window"(we are
		currently at index 2) that sum up to 1:
			1) Index 0 alone
			2) Index 0 + index 1 + index 2



------------------------------------------------------------------


	4)
		 0   1  2  3  4  5
		[1, -1, 1, 1, 1, 1], k = 3
		 #   #  #  #

		sum = 2
		k = 3
			sum - k => 2 - 3 = -1

		Do we have a -1 in our Prefix Map that we can potentially remove from
		this subbarray which would give us a total sum as the target k?


		if (-1 exist in HasMap)
			total += hashmap[-1];

		// Anyway, we must do this
		if (sum exist in HashMap)
			hashmap[sum]++;
		else
			hashmap.insert({2 : 1}); // We add our curent sum, i.e. new prefix


		{Prefix : Count }
		|   0   |   2   |
		|   1   |   2   |
		|   2   |   1   | // Added
		|       |       |
		|       |       |



------------------------------------------------------------------


	5)
		 0   1  2  3  4  5
		[1, -1, 1, 1, 1, 1], k = 3
		 #   #  #  #  #

		sum = 3
		k = 3
			sum - k => 3 - 3 = 0

		Do we have a 0 in our Prefix Map that we can potentially remove from
		this subbarray which would give us a total sum as the target k?
			Yes, we do!


		if (-1 exist in HasMap)
			total += hashmap[-1]; // hashmap[0] is equal to 2

		// Anyway, we must do this
		if (sum exist in HashMap)
			hashmap[sum]++;
		else
			hashmap.insert({3 : 1});

		So what did we do?
			 0   1  2  3  4  5
			[1, -1, 1, 1, 1, 1], k = 3
			 #   #  #  #  #

			Entire sum of these first 5 contiguous elements is equal to 3.
			Then 3 -3 = 0

			That means we need to remove a "zero-sum subarray" from this
			current subarray to get out to the target k.

			So let's count how many subarrays can we remove and still be equal
			to target k.

     Empty  [1, -1, 1, 1, 1, 1]
     -----   #   #  #  #  #
        ^
        |
1-st ---|    // First we remove "Empty prefix", thus ind 0 + 1 + 2 + 3 + 4 == k


          -------
          |     |
          |     v
          |  ______ ~~~~~~~~    Now this sums up to k = 3
          |  [1, -1, 1, 1, 1, 1]
          |   #   #  #  #  #
          |
2-sn  ----|  // Then we remove Subbarray [0 - 1] Inclusive

		total =+ hashmap[0] => total = 2

		And then add this to hashmap:
			hashmap.insert({3 : 1})


		{Prefix : Count }
		|   0   |   2   |
		|   1   |   2   |
		|   2   |   1   |
		|   3   |   1   | // Added
		|       |       |


------------------------------------------------------------------

	6)
		 0   1  2  3  4  5
		[1, -1, 1, 1, 1, 1], k = 3
		 #   #  #  #  #  #

		sum = 4
		k = 3
			sum - k => 4 - 3 = 1

		Do we have a 1 in our Prefix Map that we can potentially remove from
		this subbarray which would give us a total sum as the target k?
			Yes, we do!


		if (1 exist in HasMap)
			total += hashmap[1];

		// Anyway, we must do this
		if (sum exist in HashMap)
			hashmap[sum]++;
		else
			hashmap.insert({4 : 1}); // We add our curent sum, i.e. new prefix


	How many subbarrays sum up to 1, which when we remove we will end up with
	our target value k?


          -----
          |   |
          |   v
          |  ___  ~~~~~~~~~~~~~ Now this sums up to target k = 3
          |  [1, -1, 1, 1, 1, 1]
          |   #   #  #  #  #  #
          |
1-st  ----|  // First we remove subarray starting and ending with at index 0



          -------
          |     |
          |     v
          |  _________  ~~~~~~~ Now this sums up to target k = 3
          |  [1, -1, 1, 1, 1, 1]
          |   #   #  #  #  #  #
          |
2-nd  ----|  // Then we remove Subbarray [0 - 2] Inclusive

		total =+ hashmap[1] => total = 4

		And then add this to hashmap:
			hashmap.insert({4 : 1})

		{Prefix : Count }
		|   0   |   2   |
		|   1   |   2   |
		|   2   |   1   |
		|   3   |   1   |
		|   4   |   1   | // Added

	At the very end we return "total" as the final answer.
*/


/* Time  Beats: 96.4% */
/* Space Beats: 46.7% */
/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution{
public:
	int subarraySum(std::vector<int>& nums, int k)
	{
		int ret = 0;
		int curr_sum = 0;

		std::unordered_map<int, int> prefix_sums;
		prefix_sums = {{0, 1}};

		for (auto& n : nums)
		{
			curr_sum += n;
			int diff = curr_sum - k;

			if (prefix_sums.find(diff) != prefix_sums.end())
				ret += prefix_sums[diff];

			prefix_sums[curr_sum]++;
		}

		return ret;
	}
};


int
main()
{
	Solution_Brute_DP sol_brute;
	Solution sol;

	/* Example 1 */
	// std::vector<int> nums = {1, 1, 1};
	// int k = 2;

	/* Example 2 */
	// std::vector<int> nums = {1, 2, 3};
	// int k = 3;

	/* Example 3 */
	std::vector<int> nums = {-1, 1, 0, 1, -1};
	int k = 0;

	std::cout << "\n\t=============================";
	std::cout << "\n\t=== SUBARRAY SUM EQUALS K ===";
	std::cout << "\n\t=============================\n";

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
	std::cout << "]";
	std::cout << "\n\tK = " << k << "\n";

	/* Solution */
	// int count = sol_brute.subarraySum(nums, k);
	int count = sol_brute.subarraySum(nums, k);

	/* Write Output */
	std::cout << "\n\tOutput: " << count << "\n\n";

	return 0;
}
