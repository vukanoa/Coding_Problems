#include <iostream>
#include <vector>
#include <queue>

/*
	==============
	=== MEDIUM ===
	==============

	=====================================
	215) Kth Largest Element in an Array
	=====================================

	============
	Description:
	============

	Given an integer array "nums" and an integer "k", return the k-th largest
	element in the array.

	Note that it is the kth largest element in the sorted order, not the kth
	distinct element.

	You must solve it in O(n) time complexity.

	=============================================================
	FUNCTION: int findKthLargest(std::vector<int>& nums, int k);
	=============================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  nums = [3, 2, 1, 5, 6, 4], k = 2
	Output: 5

	--- Example 2 ---
	Input:  nums = [3, 2, 3, 1, 2, 4, 5, 5, 6], k = 4
	Output: 4

	*** Constraints ***
	1 <= k <= nums.length <= 10^5
	-10^4 <= nums[i] <= 10^4

*/

/*
	------------
	--- IDEA ---
	------------

	Basic use of Priority Queues. Other Solutions as of 25th Septembter 2023
	do not pass all the tests.

	There is a big test-case which fails for other Solutions down below, but it
	used to work and it's good to know Quick-Select and its optimization.

*/

/* Time  Beats: 37.72% */
/* Space Beats: 10.68% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution_Basic {
public:
	int findKthLargest(std::vector<int>& nums, int k)
	{
		std::priority_queue<int> max_heap(nums.begin(), nums.end());

		for (int i = 0; i < k - 1; i++)
			max_heap.pop();

		return max_heap.top();
	}
};




/*
	------------
	--- IDEA ---
	------------

	--- Heapify Solution ---
	We can use the method "heapify" of the Heap Sort implementation to solve
	this problem.

	// Space: O(1) in either case
	Though the Time Complexity of this approach can either be:
		1. Time (n + k * logn)                       // Max Heap
		2. Time (n + (n - k + 1) * log(n - k + 1))   // Min Heap

	Depending of which of the the two is smaller.
		if (k < (n - k + 1))
			// Use a Max Heap
		else
			// Use a Min Heap

	Function "heapify" takes:
		Time:  O(logn)
		Space: O(1)

	Since it is said that:
	*** Constraints ***
	1 <= k <= nums.length <= 10^5

	that mean 'k' can be equal to "nums.length()" and in that case:
		Time: O(n + n * logn) => O(n * logn)

	Which essentially means that it is the same as the "Trivial Solution" using
	sorting and then getting "nums.size() - k"th element from the back.

	=============
	=== CODE ==== TODO: Implement "heapify" yourself
	=============

	class Solution{
	public:
		int findKthLargest(std::vector<int>& nums, int k)
		{
			std::make_heap(nums.begin(), nums.end());

			while (k > 1)
			{
				std::pop_heap(nums.begin(), nums.end());
				nums.pop_back();
				k--;
			}

			return nums[0];
		}
	};




	--- Quick-Select Solution ---

	The name comes from the fact that this Algorithm has a common denominator
	with Quick-Sort Algorithm.

	The common denominator is the "partition" function.

	Though Quick-Sort uses it to sort the entire array, thus having the average
	Time Complexity of O(n * logn)

	Whereas Quick-Select only goes to one side each time without recursively
	backtracking to process the other side as well. Thus its average Time
	Complexity is: O(n)

	However both Algorithms have the Worst Time Complexity: O(n^2)
	Though that happens rarely. That happens if the array is already sorted.

	===========================================================================
	(Couldn't we check if the array is already sorted and if it is then just
	return nums.size() - k, and if at any point of checking if it is sorted
	we find out that it's not, then and only then, perform a Quick-Select)
	
	(That way we're certain that we're going to have an O(n) Time complexity.
	Check up if it is sorted is alway O(1 * n) therefore it won't worsen the
	Time Complexity, yet it will protect us from doing a O(n^2) ever, thus it
	means that it will actually substantially improve our Time Complexity in
	the worst case-scenario.)

	Yes, we could. That's actually the way to optimize Quick-Select algorithm
	Solution_Efficient implements that on top of the Quick-select.
	===========================================================================

	Consider this first example:
		3 2 1 5 6 4

	First we're going to partition our array. Meaning that the left side of the
	pivot is going to be less than or equal to our pivot and the right side is
	going to be greater than the pivot.

	How can we make sure that the array is always going to be halfed?
	Well, it turns out that we can't.
	That's why the Worst Time Complexity is O(n^2)

	But the Average Time Complexity is going to be: O(n)

	So what are we doing? We're going to randomly pick a pivot. Let's pick
	the last element as our pivot. It's the easiest approach.
	There are some suggestions and "rules" on how to pick your pivot in the
	best way but we're not going to cover that here.

	So how does the "partition" function works?
	We're going through each element in our array and we're going to compare
	it to our pivot value.
		If (nums[j] <= pivot)
			swap(nums[i], nums[j])
			increment i
			increment j
		else
			increment j

	So the partitioning looks like this:


    I)
              # -> pivot
    3 2 1 5 6 4 // Elements
    j
    i

	(nums[j] <= pivot)?
	TRUE
		*SWAP* (nums[i] and nums[j])
		increment i
		increment j

              # -> pivot
    3 2 1 5 6 4 // Elements
      j
      i


	II)
              # -> pivot
    3 2 1 5 6 4 // Elements
      j
      i

	(nums[j] <= pivot)?
	TRUE
		*SWAP* (nums[i] and nums[j])
		increment i
		increment j

              # -> pivot
    3 2 1 5 6 4 // Elements
        j
        i



    III)
              # -> pivot
    3 2 1 5 6 4 // Elements
        j
        i

	(nums[j] <= pivot)?
	TRUE
		*SWAP* (nums[i] and nums[j])
		increment i
		increment j

              # -> pivot
    3 2 1 5 6 4 // Elements
          j
          i



    IV)
              # -> pivot
    3 2 1 5 6 4 // Elements
          j
          i

	(nums[j] <= pivot)?
	FALSE
		increment j

              # -> pivot
    3 2 1 5 6 4 // Elements
          i j


    V)
              # -> pivot
    3 2 1 5 6 4 // Elements
          i j

	(nums[j] <= pivot)?
	FALSE
		increment j

              # -> pivot
    3 2 1 5 6 4 // Elements
          i   j // Stop, j is >= right


    VI) At the end swap the pivot with nums[i]

          # -> pivot
    3 2 1 4 6 5 // Elements
          i

	It's important to emphasize that neither of the sides, left or right, are
	sorted.

	So what is the point of partitioning?

	At the end of the first Partition, all we know is that the pivot(after
	swapping it at the end with nums[i]) is at the position where all the
	elements right of it are greater than the pivot element and all the
	elements left of it are less than or equal to the pivot element.

	So what does that tell us?
	It tells us that our pivot is:
		$$$ = nums.size() - index_of_our_pivot(after swapping with nums[i])

	That means that our pivot is the $$$-th largest element in the list.

	$$$ = nums.size() - index_of_our_pivot(after swapping with nums[i])
	### = nums.size() - k // This is what we're looking for

	So:
	if (### === $$$)
		We've found the k-th largest element. Return the pivot.
	else if(### < $$$)
		we should continue in the right's portion of our pivot
	else // (### > $$$)
		continue in the left's portion of our pivot

	Or to simplify the above conditions, we can also check:
	if (k == i) // 'i' is the index of our pivot after the last swap
		We've found the k-th largest element. Return the pivot.
	else if(k < i)
		we should continue in the right's portion of our pivot
	else // (k > i)
		continue in the left's portion of our pivot


	So in our example after the partitioning:
		3 2 1 4 6 5
              #

	Our pivot "4" is at the index 3, so that means that it is:
		"nums.size() - 3"-th
	largest element in the list. Or in numbers:
		6 - 3 = 3
	that means our pivot is the 3rd largest element in the list.

	Now if we don't need the 3rd largest element(in this example), then
	keep partitioning the right side until:
		nums.size() - index_of_our_pivot(after swapping with nums[i])
			is equals to
		nums.size() - k

	i.e., until:
		(### === $$$)

	Or simpler, until:
		k == i

	Meaning - current pivot is the k-th largest element that we're looking for.
	Return that and it's done.

	With Quick-Select, we don't care about the other "half". We just keep going
	on the side we need to process and partition it further until we get to the
	above stated condition.

*/


/* Average Time  Complexity: O(n) */
/* Worst   Time  Complexity: O(n^2) */
/* Space         Complexity: O(1) */
class Solution{
private:
	int quick_select(int left, int right, std::vector<int>& nums, int k)
	{
		int pivot = nums[right];
		int i = left;

		for (int j = left; j < right; j++)
		{
			if (nums[j] <= pivot)
			{
				swap(nums[i], nums[j]);
				i++;
			}
		}
		swap(nums[i], nums[right]);

		if (k == i)
			return nums[i];
		else if (k < i)
			return quick_select(left, i - 1, nums, k);
		else // (k > i)
			return quick_select(i + 1, right, nums, k);
	}

	void swap(int& a, int& b)
	{
		int tmp = a;
		a = b;
		b = tmp;
	}

public:
	int findKthLargest(std::vector<int>& nums, int k)
	{
		if (nums.size() == 1)
			return nums[0]; // Since we're certain that k is also 1

		k = nums.size() - k; // Index in the array as if it was sorted.
		int kth = quick_select(0, nums.size() - 1, nums, k);

		return kth;
	}
};




/*
	------------
	--- IDEA ---
	------------

	To optimize Quick-Select, we should:

	===========================================================================
	Check if the array is already sorted and if it is then just
	return nums.size() - k, and if at any point of checking if it is sorted
	we find out that it's not, then and only then, perform a Quick-Select.

	That way we're certain that we're going to have an O(n) Time complexity.
	Check up if it is sorted is alway O(1 * n) therefore it won't worsen the
	Time Complexity, yet it will protect us from doing a O(n^2) ever, thus it
	means that it will actually substantially improve our Time Complexity in
	the worst case-scenario.)
	===========================================================================
	
*/

/* Time  Beats: 91.69% */
/* Space Beats: 72.98% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Efficient {
private:
	int quick_select(std::vector<int>& nums, int k, int left, int right)
	{
		int j = left;
		int i = left;
		int pivot_index = right;

		while (j < pivot_index)
		{
			if (nums[j] <= nums[pivot_index])
			{
				std::swap(nums[i], nums[j]);
				i++;
			}

			j++;
		}
		std::swap(nums[i], nums[right]);

		if (k == i)
			return nums[i];
		else if (k < i)
			return quick_select(nums, k, left, i - 1);
		else // (k > i)
			return quick_select(nums, k, i + 1, right);
	}

public:
	int findKthLargest(std::vector<int>& nums, int k)
	{
		if (nums.size() == 1)
			return nums[0]; // Since we're certain that k is also 1

		auto sorted = [&](){
			for (int i = 1; i < nums.size(); i++)
			{
				if (nums[i - 1] > nums[i])
					return false;
			}

			return true;
		};

		/* This prevents O(n^2) for Quick-Select */
		if (sorted())
			return nums[nums.size() - k];

		k = nums.size() - k; // Index in the array as if it was sorted.
		int kth = quick_select(nums, k, 0, nums.size() - 1);

		return kth;
	}
};




/*
	------------
	--- IDEA ---
	------------

	Same as above, just did NOT use the trick:
		k = nums.size() - k;
	
	So I wanted to put this here to emphasize how important that part is. If
	we leave that part out, then we have to do all of this "nonsense" with if
	statements and all these arguments.
	
*/


/* Time  Beats:  5.10% */
/* Space Beats: 99.47% */
class Solution_Difficult {
public:
	int findKthLargest(std::vector<int>& nums, int k)
	{
		/* Quick Select */
		return quick_select(nums, k, 0, nums.size() - 1);
	}

private:
	int quick_select(std::vector<int>& nums, int k, int start, int end)
	{
		int i = start;
		int j = start;
		int pivot_index = end;

		while (j < pivot_index)
		{
			if (nums[j] <= nums[pivot_index])
			{
				std::swap(nums[i], nums[j]);
				i++;
				j++;
			}
			else
				j++;
		}
		std::swap(nums[i], nums[pivot_index]);

		if (end - k + 1 == i)
			return nums[i];
		else if (end - k + 1 < i)
			return quick_select(nums, k-(pivot_index-i + 1), start, i-1);
		else // if (end - k + 1 > i)
			return quick_select(nums,   k, i+1,   end);
	}
};


int
main()
{
	Solution_Basic     sol_basic;
	Solution_Efficient sol_efficient;
	Solution_Difficult sol_difficult;


	/* Example 1 */
	std::vector<int> nums {3, 2, 1, 5, 4, 6};
	int k = 2;

	/* Example 2 */
	// std::vector<int> nums {3, 2, 3, 1, 2, 4, 5, 5, 6};
	// int k = 4;

	/* Example 3 */
	// std::vector<int> nums {1};
	// int k = 1;

	/* Example 6 */
	// std::vector<int> nums {2, 1};
	// int k = 1;

	std::cout << "\n\t=======================================";
	std::cout << "\n\t=== KTH LARGEST ELEMENT IN AN ARRAY ===";
	std::cout << "\n\t=======================================\n";


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
	int kth = sol_basic.findKthLargest(nums, k);
	// int kth = sol_efficient.findKthLargest(nums, k);
	// int kth = sol_difficult.findKthLargest(nums, k);


	/* Write Output */
	if (k == 1)
		std::cout << "\n\t" << k << "st Largest: " << kth << "\n\n";
	else if (k == 2)
		std::cout << "\n\t" << k << "nd Largest: " << kth << "\n\n";
	else if (k == 3)
		std::cout << "\n\t" << k << "rd Largest: " << kth << "\n\n";
	else
		std::cout << "\n\t" << k << "th Largest: " << kth << "\n\n";


	return 0;
}
