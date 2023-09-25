#include <iostream>
#include <vector>
#include <queue>

/*
	============
	=== EASY ===
	============

	====================================
	703) Kth Largest Element In a Stream
	====================================

	============
	Description:
	============

	Design a class to find the kth largest element in a stream. Note that it is
	the kth largest element in the sorted order, not the kth distinct element.

	Implement KthLargest class:

		KthLargest(int k, int[] nums) Initializes the object with the integer k
		and the stream of integers nums.  int add(int val) Appends the integer
		val to the stream and returns the element representing the kth largest
		element in the stream.


	,===============================
	CLASS:
	class KthLargest {
	public:
		KthLargest(int k, vector<int>& nums)
		{}
		
		int add(int val)
		{}
	};

	===============================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================


	--- Example 1 ---
	Input
	["KthLargest", "add", "add", "add", "add", "add"]
	[[3, [4, 5, 8, 2]], [3], [5], [10], [9], [4]]
	Output
	[null, 4, 5, 5, 8, 8]

	Explanation
	KthLargest kthLargest = new KthLargest(3, [4, 5, 8, 2]);
	kthLargest.add(3);   // return 4
	kthLargest.add(5);   // return 5
	kthLargest.add(10);  // return 5
	kthLargest.add(9);   // return 8
	kthLargest.add(4);   // return 8


	*** Constraints ***
	1 <= k <= 10^4
	0 <= nums.length <= 10^4
	-10^4 <= nums[i] <= 10^4
	-10^4 <= val <= 10^4
	At most 10^4 calls will be made to add.
	It is guaranteed that there will be at least k elements in the array when
	you search for the kth element.

*/

/* Time  Beats: 93.72% */
/* Space Beats: 19.98% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class KthLargest {
public:
	// O(n * logn)
    KthLargest(int k, vector<int>& nums)
        : min_heap(nums.begin(), nums.end()), k(k)
    {
        while (min_heap.size() > k)
            min_heap.pop();
    }

	// O(logn)
    int add(int val)
    {
        min_heap.push(val);

        if (min_heap.size() > k)
            min_heap.pop();
        
        return min_heap.top();
    }

private:
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;
	int k;
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */
