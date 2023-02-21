#include <iostream>
#include <vector>
#include <deque>

/*
	============
	=== HARD ===
	============

	===========================
	239) Sliding Window Maximum
	===========================

	============
	Description:
	============

	You are given an array of integers "nums", there is a sliding window of
	size 'k' which is moving from the very left of the array to the very right.
	You can only see the 'k' numbers in the window. Each time the sliding
	window moves right by one position.

	Return the max sliding window.

	=================================================================
	FUNCTION: vector<int> maxSlidingWindow(vector<int>& nums, int k);
	=================================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  nums = [1, 3, -1, -3, 5, 3, 6, 7], k = 3
	Output: [3, 3, 5, 5, 6, 7]
	Window position                     Max
	---------------                    -----
   [1   3  -1] -3   5   3   6   7        3
    1  [3  -1  -3]  5   3   6   7        3
    1   3 [-1  -3   5]  4   6   7        5
    1   3  -1 [-3   5   4]  6   7        5
    1   3  -1  -3  [5   4   6]  7        6
    1   3  -1  -3   5  [4   6   7]       7

	--- Example 2 ---
	Input:  nums = [1], k = 1
	Output: [1]

	*** Constraints ***
	1 <= nums.length <= 10^5
	-10^4 <= nums[i] <= 10^4
	1 <= k <= nums.length

*/



/*
	------------
	--- IDEA ---
	------------

	Let's start with:


	============================
	=== Brute Force Solution ===
	============================

	We can write a nested loop, the outer loop goes through each window and
	the inner loop finds the max within the window. This is O(N^2) time
	complexity.

	To optimize on brute force, we can either reduce outer or inner loop
	complexity. Since we have toe examine each element at least once(there's no
	way to find the maximum if we don't know what the values are), there is not
	much we can do for outer loop. So we have to work on the inner loop.

	*** Preserving inner elements maximum ***
	Currently, to get the max of the sliding window, we look at each element in
	the window and compare them. Analogous to sliding window sum problem (given
	an array and a window size, return the sum of each window), when a window
	slides, only two elements change - the leftmost gets removed and a new
	element gets added to the right.

	Everything in the middle(let's call them "inner elements") is unchanged,
	and the maximum element among these inner elements are unchanged as well.
	They key to reducing inner loop complexity is to persist the maximum of
	the inner elements as we slide the window. Ideally, we want to be able to
	access the maximum element in less than O(n) time and updating it in less
	than O(n) time.


	===================================
	=== Balanced Binary Search Tree ===
	===================================

	One way to achieve this goal is to save the window elements in a
	self-balancing binary tree. Because it's self-balancing, the depth of the
	tree is guaranteed to be O(logN) so lookup, getting max, insert and delete
	are all O(logN) operations.
	Every time we slide the window, we remove the node that's out of the window
	and add the one that comes into the window to the tree. Overall, this gives
	us O(N * logK) since the number of tree nodes is K and we slide max N times

	This is pretty good already, but can we do better?

	*** Larger elements entering window invalidates smaller elements ***
	A question we can ask ourselves is "do we need to keep all the window
	elements in our state?".
	An important observation is for two elements:
		arr[left] and arr[right]
	where:
		left < right

	arr[left] leaves the window earlier as we slide. If arr[right] is larger
	than arr[left], then there is no point keeping arr[left] in our state
	since arr[right] is always gonna be larger during the time arr[left] is in
	the window. Therefore, arr[left] can never be the maximum.


	=======================
	=== Monotonic Deque ===
	=======================

	Here we introduce an interesting data structure. It's a deque with an
	interesting property - the elements in the deque from head to tail are in
	decreasing order (hence the name monotonic)

	To achieve this property, we modify the push operation so that:
		*Before we push an element into the deque, we first pop everything
		smaller than it out of the deque.

	This enfroces the decreasing order.

	The time complexity is O(N). This is because each element in the original
	array can be pushed into and popped out of the deque only once.

	The key why monotonic deque works is it stores both magnitude and position
	information. From head to tail, the elements get smaller and further to the
	right of the array.
*/


/* Time  Complexity: O(n) */
/* Space Complexity: O(k) */
class Solution{
public:
	std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k)
	{
		std::deque<int> deque; // Stores indices
		std::vector<int> output;   // Stores result

		for (int i = 0; i < nums.size(); i++)
		{
			while (!deque.empty() && nums[deque.back()] <= nums[i])
				deque.pop_back();

            deque.push_back(i);

            // Remove first element if it's outside the window
            if (deque.front() == i - k)
                deque.pop_front();

			/*
				If window has 'k' elements add to results
				(first k-1 windows have < k elements because we start from
				 empty window and add 1 element each iteration)
			*/
            if (i >= k - 1)
                output.push_back(nums[deque.front()]);
		}

        return output;
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	std::vector<int> nums {1, 3, -1, -3, 5, 3, 6, 7};
	int k = 3;

	/* Example 2 */
	// std::vector<int> nums {1};
	// int k = 1;

	/* Example 3 */
	// std::vector<int> nums {1, 3, -1, -3, 5, 3, 6, 7};
	// int k = 4;

	std::cout << "\n\t==============================";
	std::cout << "\n\t=== SLIDING WINDOW MAXIMUM ===";
	std::cout << "\n\t==============================\n";


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
	std::cout << "]\n";


	/* Solution */
	std::vector<int> output = sol.maxSlidingWindow(nums, k);


	/* Write Output */
	first = true;
	std::cout << "\n\tOutput: [";
	for (auto x: output)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n\n";


	return 0;
}
