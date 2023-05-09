#include <iostream>
#include <vector>
#include <climits>

/*
	==============
	=== MEDIUM ===
	==============

	=========================================
	153) Find Minimum in Rotated Sorted Array
	=========================================

	============
	Description:
	============

	Suppose an array of length "n" sorted in ascending order is rotated between
	1 and n times. For ecample, the array "nums" = [0, 1, 2, 4, 5, 6, 7] might
	become:
		[4, 5, 6, 7, 0, 1, 2] if it was rotated 4 times
		[0, 1, 2, 4, 5, 6, 7] if it was rotated 7 times

	Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time
	results in the array [a[n-1], a[0], a[1], a[2], ..., a[n-2]].

	Given the sorted rotated array "nums" of unique elements, return the
	minimum element of this array.

	You must write an algorithm that runs in O(log n) time.

	=========================================
	FUNCTION: int findMin(vector<int>& nums);
	=========================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  nums = [3, 4, 5, 1, 2]
	Output: 1

	--- Example 2 ---
	Input:  nums = [4, 5, 6, 7, 0, 1, 2]
	Output: 0

	--- Example 3 ---
	Input:  [11, 13, 15, 17]
	Output: 11

	*** Constraints ***
	n = nums.length
	1 <= n <= 5000
	-5000 <= nums[i] <= 5000
	All the integers of "nums" are unique.
	"nums" is sorted and rotated between 1 and n times.

*/


/*
	------------
	--- IDEA ---
	------------

	*** Binary Search (Recursively) ***
	
	============
	=== NOTE ===
	============
	This Solution is here just to practice Binary Search recursively.
	It's much easier to look at the last Solution down below for it is the
	most easier to understand.


	At the very beginning we assign the nums[0] as the minimum value.

	Then we forward an entire array in a helper function called: binary_search
	This is a bit of a tweaked version of a binary search, but it is highly
	reminiscent.

	Consider this example:
		[4, 5, 6, 7, 0, 1, 2]
		 0  1  2  3  4  5  6

	First, we check the edge case - If that is the only element.

	Second, we check if the current nums[start] is less than nums[end] if that
	is the case then it's over, just check if the nums[start] is less than
	the current minimum and return min from the findMind function.

	Third, if nums[end] > nums[start] then that means the array/subarray we are
	currently checking is rotated. That further means that we have to divide
	this one and repeat the process either on its left or its right part of the
	current array/subarray.

	So how do we decide where to go?
	Again, consider this example:
		[4, 5, 6, 7, 0, 1, 2]
		 0  1  2  3  4  5  6

	We will then calculate 4 positions:
		1. left_start
		2. left_end
		3. right_start
		4. right_end

	if we find out that nums[left_start] is less than nums[left_end] then that
	means that left subarray is completely sorted which further means that our
	desired minimum value is certainly not there. Therefore, we should proceed
	our search in the other, right, half of this array/subarray.

	And vice-versa.

	And the end of the recursion we have our minimum value stored in our
	variable "min", so we return that from our function "findMin".

*/

/* Time  Beats:   100% */
/* Space Beats: 28.14% */

/* Time  Complexity: O(logn) */
/* Space Complexity: O(1) */
class Solution_BS_Recursively {
public:
	void binary_search(std::vector<int>& nums, int start, int end, int& min)
	{
		if (start == end)
		{
			if (nums[start] < min)
				min = nums[start];
		}
		else if(nums[start] < nums[end])
		{
			if (nums[start] < min)
				min = nums[start];
		}
		else
		{
			int left_start  = start;
			int left_end    = (start + end) / 2;
			int right_start = left_end + 1;
			int right_end   = end;

			if (nums[left_start] > nums[left_end]) // Process left subarray
				binary_search(nums, left_start, left_end, min);
			else // Process right subarray
				binary_search(nums, right_start, right_end, min);
		}
	}

	int findMin(std::vector<int>& nums)
	{
		int min = nums[0];

		int start = 0;
		int end = nums.size() - 1;

		binary_search(nums, start, end, min);

		return min;
	}
};




/*
	------------
	--- IDEA ---
	------------

	*** Binary Search (Iteratively) ***

	If there is a single element in the "nums" array, return nums[0]
	immediately.

	If nums[0] is less than nums[n - 1], return nums[0] as well.

	Let's consider this example again:
		[4, 5, 6, 7, 0, 1, 2]
		 0  1  2  3  4  5  6

	nums[0] is greater than nums[end] which indicates that the array is
	rotated.
	This means there is a point in the array at which you would notice a
	change. This is the point which we call "Inflection Point".

	    increase          decrease
	    ------------->   --------->
	    [4 | 5 | 6 | 7 | 0 | 1 | 2]
	     0   1   2   3   4   5   6
	                   ^
	                   |
	Inflection Point ---

	In this modified version of binary search, we are looking for this point.
		- All the elements to the left of inflection point are greater than
		  the first element of the array.

		- All the elements to the right of the inflection point are less than
		  the first element of the array.

	So the algorithm goes - We find a mid position(index) and then we check:
		1. if mid's right is smaller than the current "mid", that is - we have
		   found the "Inflection Point", thus return nums[mid + 1];

		2. If not, we check if mid's left is greater than the current
		   nums[mid], that is - we have found the "Inflection point", thus
		   return nums[mid].

	If neither of those two things is true, check if:
		nums[mid] is greater than nums[0]

	If it is    , then check the right subarray. [0, mid - 1]
	If it is NOT, then check the left  subarray. [mid + 1, n - 1]

	Algorithm:
		1. Find the "mid" element of the array

		2. If "mid" element > first element of the array, this means that we
		   need to look for the inflection point on the right of "mid".

		3. If "mid" element < first element of the array, this means that we
		   need to look for the Inflection Point on the left of "mid".

		4. We stop our search(while loop) when we find the inflection point,
		   when either of the two conditions is satisfied:
		       a) nums[mid] > nums[mid + 1]
		           Hence, nums[mid + 1] is the smallest.

			   b) nums[mid - 1] > nums[mid]
			       Hence, nums[mid] is the smallest.

	
*/

/* Time  Beats: 100% */
/* Space Beats: 74.40% */

/* Time  Complexity: O(logn) */
/* Space Complexity: O(1) */
class Solution_BS_Iteratively {
public:
	int findMin(std::vector<int>& nums)
	{
		if (nums.size() == 1)
			return nums[0];

		int left = 0;
		int right = nums.size() - 1;

		if (nums[right] > nums[0])
			return nums[0];

		// Binary Search
		while (right >= left)
		{
			int mid = left + (right - left) / 2;

			if (nums[mid] > nums[mid + 1])
				return nums[mid + 1];

			if (nums[mid - 1] > nums[mid])
				return nums[mid];

			if (nums[mid] > nums[0])
				left = mid + 1;
			else
				right = mid - 1;
		}

		return INT_MAX;
	}
};




/*
	------------
	--- IDEA ---
	------------

	Simplest explanation:

	Example 1:
	[8, 9, 1, 2, 3, 4, 5, 6, 7]

	Example 2:
	[9, 1, 2, 3, 4, 5, 6, 7, 8]

	In each step of the Binary Search, check if the nums[mid] is:
		1) less    than nums[right], or
		2) greater than nums[right].

	However, there's an edge case: When there are only two elements remaining,
	i.e. left and right indexes are next to each other.

	In that case if you try to calculate mid index, you will endlessly be in a
	loop, thus at every step of this Binary Search algorithm we have to check
	if nums[mid] == nums[left] or if nums[mid] == nums[right].
	
	If that is the case, i.e. left and right indexes are next to each other,
	then return lesser of the two remaining elements.

	Try simulating the above two examples with the below written code and you
	will get a feel of how this works. It's pretty self-explanatory.

*/

/* Time  Beats:   100% */
/* Space Beats: 74.40% */
class Solution_BS_Short {
public:
	int findMin(std::vector<int>& nums)
	{
		if (nums.size() == 1)
			return nums[0];

		int left  = 0;
		int right = nums.size() - 1;

		/* Binary Search */
		while (left < right)
		{
			int mid = (left + right) / 2;

			if (nums[mid] == nums[left] || nums[mid] == nums[right])
				return std::min(nums[left], nums[right]);
			else if (nums[mid] < nums[right])
				right = mid;
			else if (nums[mid] > nums[right])
				left = mid;
		}

		return -5001; // -5000 <= nums[i] <= 5000
	}
};


int
main()
{
	Solution_BS_Recursively sol_rec;
	Solution_BS_Iteratively sol_iter;
	Solution_BS_Short       sol_short;


	/* Example 1 */
	// std::vector<int> nums = {3, 4, 5, 1, 2};

	/* Example 2 */
	std::vector<int> nums = {4, 5, 6, 7, 0, 1, 2};

	/* Example 3 */
	// std::vector<int> nums = {11, 13, 15, 17};

	/* Example 4 */
	// std::vector<int> nums = {2, 1};

	/* Example 5 */
	// std::vector<int> nums = {2, 3, 4, 1};

	/* Example 6 */
	// std::vector<int> nums = {5};

	/* Example 7 */
	// std::vector<int> nums = {1, 2, 3, 4, 5};

	/* Example 8 */
	// std::vector<int> nums = {5, 1, 2, 3, 4};

	/* Example 9 */
	// std::vector<int> nums = {4, 5, 1, 2, 3};

	/* Example 10 */
	// std::vector<int> nums = {3, 4, 5, 1, 2};

	/* Example 11 */
	// std::vector<int> nums = {2, 3, 4, 5, 1};


	std::cout << "\n\t============================================";
	std::cout << "\n\t=== FIND MINIMUM IN ROTATED SORTED ARRAY ===";
	std::cout << "\n\t============================================\n";


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
	// int min = sol_rec.findMin(nums);
	// int min = sol_iter.findMin(nums);
	int min = sol_short.findMin(nums);


	/* Write Output */
	std::cout << "\n\tMinimum is: " << min << "\n\n";


	return 0;
}
