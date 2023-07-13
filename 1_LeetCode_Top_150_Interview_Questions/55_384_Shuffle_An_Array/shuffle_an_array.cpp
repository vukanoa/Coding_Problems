#include <iostream>
#include <vector>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	384) Shuffle an Array
	===========================

	============
	Description:
	============

	Given an integer array nums, design an algorithm to randomly shuffle the
	array. All permutations of the array should be equally likely as a result
	of the shuffling.

	Implement the Solution class:

		- Solution(int[] nums) Initializes the object with the integer array
		  nums.

		- int[] reset() Resets the array to its original configuration and
		  returns it.

		- int[] shuffle() Returns a random shuffling of the array.


	===============================
	FUNCTION:
		class Solution {
		public:
			Solution(vector<int>& nums) {
				
			}
			
			vector<int> reset() {
				
			}
			
			vector<int> shuffle() {
				
			}
		};
	===============================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input
	["Solution", "shuffle", "reset", "shuffle"]
	[[[1, 2, 3]], [], [], []]
	Output
	[null, [3, 1, 2], [1, 2, 3], [1, 3, 2]]

	Explanation
	Solution solution = new Solution([1, 2, 3]);
	solution.shuffle();    // Shuffle the array [1,2,3] and return its result.
						   // Any permutation of [1,2,3] must be equally likely to be returned.
						   // Example: return [3, 1, 2]
	solution.reset();      // Resets the array back to its original configuration [1,2,3]. Return [1, 2, 3]
	solution.shuffle();    // Returns the random shuffling of array [1,2,3]. Example: return [1, 3, 2]


	*** Constraints ***
    1 <= nums.length <= 50
    -10^6 <= nums[i] <= 10^6
    All the elements of nums are unique.
    At most 10^4 calls in total will be made to reset and shuffle.

*/

/*
	------------
	--- IDEA ---
	------------

	The main thing here is that we made a shuffle in O(n) instead of O(n^2).
	How?

	Well ask yourself - How would you make a shuffle in the first place?

	Take a random index from 0 to size-1 and then push that element in another
	vector and then remove that element from the "nums" vector, so that next
	time when we take a random index from 0 to size-1, the "size" is updated.

	So to process all the elements takes O(n) time, but to remove an element
	from the array, we have to shift every element, that comes after it, to the
	left, which is also O(n).

	Since the second O(n) is within the first O(n) it means that it will happen
	O(n * n) => O(n^2)

	So, how can we optimize this?
	Well, we certainly cannot make it O(1) since we indeed have to process
	every single element in the "nums" vector once.

	So the next goal is O(n), which means that the inner removal has to be
	reduced from O(n) to O(1).

	We can use the same technique that I've used in 54_380 problem, which is
	this:
		- Swap the last element of the vector "nums" with the element we want
		  to remove and then just pop_back from the vector. This makes it O(1).
	
	That's the whole idea.

	Of course, since we have to reset it, just assign default_nums to nums once
	this function is called. (That also implies that we have to have an
	additional array which will always keep the original order of elements).

*/

/* Time  Beats: 43.92% */
/* Space Beats:  5.43% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    Solution(vector<int>& nums)
        : nums(nums), default_nums(nums)
    {}
    
    vector<int> reset()
    {
        nums = default_nums;
        return nums;
    }
    
    // Time  O(n)
    // Space O(n)
    vector<int> shuffle()
    {
        std::vector<int> tmp;

        while (nums.size() > 0)
        {
            int index = rand() % nums.size();
            tmp.push_back(nums[index]);

            nums[index] = nums.back();
            nums.pop_back();
        }

        for (int i = 0; i < tmp.size(); i++)
            nums.push_back(tmp[i]);

        return nums;
    }

private:
    std::vector<int> nums;
    std::vector<int> default_nums;
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * vector<int> param_1 = obj->reset();
 * vector<int> param_2 = obj->shuffle();
 */
/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * vector<int> param_1 = obj->reset();
 * vector<int> param_2 = obj->shuffle();
 */
