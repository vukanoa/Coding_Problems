#include <iostream>
#include <vector>

/*
	==============
	=== MEDIUM ===
	==============

	=============================
	152) Maximum Product Subarray
	=============================

	============
	Description:
	============

	Given an integer array "nums", find a subarray that has the largest
	product, and return the product.

	(A subarray is a contiguous non-empty sequence of elements within an array)

	The test cases are generated so that the answe will fit in a 32-bit
	integer.

	============================================
	FUNCTION: int maxProduct(vector<int>& nums);
	============================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  nums = [2, 3, -2, 4]
	Output: 6
	Explanation: [2, 3] has the largest product 6.

	--- Example 2 ---
	Input:  nums = [-2, 0, -1]
	Output: 0
	Explanation: The result cannot be 2, because [-2, -1] is not a subarray.

	*** Constraints ***
	1 <= nums.length <= 2* 10^4
	-10 <= nums[i] <= 10
	The product of any prefix or suffix of "nums" is guaranteed to fit in a
		32-bit integer

*/


/*
	------------
	--- IDEA ---
	------------

	It is sort of like Kadane's algorithm.
	However, we have to keep track of both highest and lowest values, even
	if we are looking for hight, or maximum, value.

	Why is that?
	Consider this example:
	array: [-1,    -2,  -9, -6]
	low:   [-18, -108,   0,  0]
	high:  [108,   18,  54,  0]

	If we were to keep only high values, then we would've had:
	array: [-1, -2, -9, -6]
	high:  [ 2, 18,  0,  0]

	In high[0] we check if current element, that is nums[0] in this case
	multiplied by high[1] is greater than high[1], that of course, would be
	false and yet we would then proceed to save the value of:
		nums[i] * nums[i + 1];
	instead.

	Thus we would make a mistake because it is true that max value of
	position 1 is 18, but the lowest value of position 1 was -108 and since
	we have integers that means we have both positive and negative elements,
	that further means that maybe multiplying a lowest value of next's
	position would actually give us the highest value globally.

	Thus we MUST have another array and that is the one consisted of lowest
	products.

	There are two edge cases:
		1. There is only one element in the entire array.
		       just return nums[0];

		2. The element itself could be "the maximum product subarray" of all
		   the products in our array "high".
		       For that reason we have to check if the element itself is
			   greater than our "max" value.

	For 2nd Example of an Edge Case, consider this example:
	array: [0, 2]
	low:   [0, 0]
	high:  [0, 0]

	If we were to only follow an algorithm and return the highest value of
	our array named "high", then we would've returned 0. But we can clearly see
	that 2 is bigger than 0, thus we would have to include a checkup in, every
	iteration, if the current element is greater than "max" and if it is update
	variable "max".

	Here are all the examples with their corresponding "low" and "high" arrays:
	Example 1
	array: [  2,   3, -2, 4]
	low:   [-48, -24, -8, 0]
	high:  [  6,   0,  0, 0]

	Example 2
	array: [-2, 0, -1]
	low:   [ 0, 0,  0]
	high:  [ 0, 0,  0]

	Example 3
	array: [   2,    7,   5, -2,  3,  0,  4]
	low:   [-560, -280, -30, -6,  0,  0,  0]
	high:  [  70,   35,   0,  0,  0,  0,  0]

	Example 4
	array: [    2,     7,    5,   -2,  3,  8,  4]
	low:   [-7770, -3885, -555, -192,  0,  0,  0]
	high:  [   70,    35,    0,    0, 96, 32,  0]

	Example 5
	array: [    2,     7,     5,  -2,    3,   8,   4, -3]
	low:   [ -420,  -210,   -30,  -6, -288, -96, -12,  0]
	high:  [40320, 20160,  2880,  576,  96,  32,   0,  0]

	Example 6
	array: [-3, -1, -1]
	low:   [-3,  0,  0]
	high:  [ 3,  1,  0]

	Example 7
	array: [0, 2]
	low:   [0, 0]
	high:  [0, 0]

	Example 8
	array: [-2,   3, -4]
	low:   [-6, -12,  0]
	high:  [24,   0,  0]

	Example 9
	array: [-1,    -2,  -9, -6]
	low:   [-18, -108,   0,  0]
	high:  [108,   18,  54,  0]

	Example 10
	array: [ 2, -1, 1, 1]
	low:   [-2, -1, 0, 0]
	high:  [ 0,  0, 1, 0]

	The Algorithm of the above explained approach would be:
	int maxProduct(std::vector<int>& nums)
	{
		int n = nums.size();

		if (n == 1)
			return nums[0];

		std::vector<int> dp_low(n, 0);
		std::vector<int> dp_high(n, 0);

		for (int i = n - 2; i >= 0; i--)
		{
			int mul_low  = nums[i] * dp_low[i + 1];
			int mul_high = nums[i] * dp_high[i + 1];
			int mul_i = nums[i] * nums[i + 1];

			int max = std::max(mul_low, mul_high);
			max = std::max(max, mul_i);

			int min = std::min(mul_low, mul_high);
			min = std::min(min, mul_i);

			dp_low[i] = min;
			dp_high[i] = max;
		}

		int max = 0;
		for (int i = 0; i < n; i++)
		{
			if (dp_high[i] > max)
				max = dp_high[i];

			if (nums[i] > max)
				max = nums[i];
		}

		return max;
	}

	We can clearly see that there is a room for optimization. It's obvious that
	we don't have two separate for loops. That's first.

	Second, and the more, and actually most, important is reducing the Space
	Complexity of the above approach from:
		O(n) to O(1)

	So how should we go about doing that?

	Well, we can clearly see that in each iteration, the only thing we're
	actually using is:
		previously calculated "low" and previously calculated "high".

	Thus we can conclude that we don't need the whole array for storing
	"high" and "low" values, but only 2 variables that will store current's
	iteration values.
	Those values will be used in the NEXT iteration BEFORE the update of both
	"high" and "low" variables.

	Thus, we end up with the implementation below.

*/


/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution{
public:
	int maxProduct(std::vector<int>& nums)
	{
		int n = nums.size();

		if (n == 1)
			return nums[0];

		int low  = 0;
		int high = 0;
		int max  = nums[n - 1];

		for (int i = n - 2; i >= 0; i--)
		{
			int mul_low  = nums[i] * low;
			int mul_high = nums[i] * high;
			int mul_i = nums[i] * nums[i + 1];

			high = std::max(mul_low, mul_high);
			high = std::max(high, mul_i);

			low  = std::min(mul_low, mul_high);
			low  = std::min(low, mul_i);

			if (high > max)
				max = high;

			if (nums[i] > max)
				max = nums[i];
		}

		return max;
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	std::vector<int> nums = {2, 3, -2, 4};

	/* Example 2 */
	// std::vector<int> nums = {-2, 0, 1};

	/* Example 3 */
	// std::vector<int> nums = {2, 7, 5, -2, 3, 0, 4};

	/* Example 4 */
	// std::vector<int> nums = {2, 7, 5, -2, 3, 8, 4};

	/* Example 5 */
	// std::vector<int> nums = {2, 7, 5, -2, 3, 8, 4, -3};

	/* Example 6 */
	// std::vector<int> nums = {-3, -1, -1};

	/* Example 7 */
	// std::vector<int> nums = {0, 2};

	/* Example 8 */
	// std::vector<int> nums = {-2, 3, -4};

	/* Example 9 */
	// std::vector<int> nums = {-1, -2, -9, -6};

	/* Example 10 */
	// std::vector<int> nums = {2, -1, 1, 1};


	std::cout << "\n\t================================";
	std::cout << "\n\t=== MAXIMUM PRODUCT SUBARRAY ===";
	std::cout << "\n\t================================\n";


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
	int product = sol.maxProduct(nums);

	/* Write Output */
	std::cout << "\n\tMax Product is: " << product << "\n\n";

	return 0;
}
