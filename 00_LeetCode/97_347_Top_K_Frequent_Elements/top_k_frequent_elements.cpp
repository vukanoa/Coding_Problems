#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

/*
	==============
	=== MEDIUM ===
	==============

	============================
	347) Top K Frequent Elements
	============================

	============
	Description:
	============

	Given an integer array "nums" and an integer 'k', return the k most
	frequent elements. You may return the answer in any order.

	Follow up: Your algorithm's time complexity must be better than O(n * logn)
	(where n is the array's size)

	=============================================================
	FUNCTION: vector<int> topKFrequent(vector<int>& nums, int k);
	=============================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  nums = [1, 1, 1, 2, 2, 3], k = 2
	Output: [1, 2]

	--- Example 2 ---
	Input:  nums = [1], k = 1
	Output: [1]

	*** Constraints ***
	1 <= nums.length <= 10^5
	-10^4 <= nums[i] <= 10^4
	k is in the range [1, the number of unique elements in the array]
	It is guaranteed that the answer is unique.

*/


/*
	------------
	--- IDEA ---
	------------

	First we need to store the number of occurrences of each number and we do
	that by storing frequencies in a hash map for each number.

	If we were to sort that hash map by value, that would've take O(N * logN)
	which is prohibited by the Problem description.
	(Your algorithm's time complexity must be better than O(N * logN))

	So how can we "sort" our Hash Map without sorting so that we can extract
	top k elements from it?
	Heap!

	Making a Heap from a vector will take O(N)
	Popping an element from the Heap is O(logN)

	Since we have to take only top K elements, we will pop from the Heap
	exactly K times.

	O(N + N + K * logN)

	That makes this Algorithm O(K * logN) which is better than O(N * logN)
	since K is almost always less than N by a large margin.

	It's important to note that the absolutely worst Time Complexity of this
	Algorithm can indeed be O(N * logN) but that happens very rarely that we
	can conclude the complexity is: O(K * logN)

*/



/* Time  Complexity: O(K * logN) */
/* Space Complexity: O(N) */
class Solution{
private:
	struct Node{
		int num;
		int freq;

		Node (int a, int b)
			: num(a), freq(b) {}
	};

	struct Compare {
		bool operator() (Node const& a, Node const& b)
		{
			return a.freq < b.freq;
		}
	};

public:
	std::vector<int> topKFrequent(std::vector<int>& nums, int k)
	{
		std::unordered_map<int, int> map; // Key->Number ... Value->Freq

		// Step 1: Store frequence of all elements in map
		// O(N)
		for (int n : nums)
			map[n]++;

		// Step 2: Now build a Heap
		// Compare defines a max-heap based on frequency
		// O(N)
		std::priority_queue<struct Node, std::vector<struct Node>, struct Compare> heap;
		for (auto it: map)
			heap.push(Node(it.first, it.second));

		std::vector<int> ret;

		// Step 3: Pop top K elements and store the numbers in "ret" vector
		// O(K * logN)
		while (k--)
		{
			struct Node tmp = heap.top();
			heap.pop();
			ret.push_back(tmp.num);
		}

		return ret;
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	// std::vector<int> nums = {1, 1, 1, 2, 2, 3};
	// int k = 2;

	/* Example 2 */
	// std::vector<int> nums = {1};
	// int k = 1;

	/* Example 3 */
	std::vector<int> nums = {5, 6, 2, 3, 4, 9, 9, 9, 6, 6, 6, 7, 7};
	int k = 3;


	std::cout << "\n\t===============================";
	std::cout << "\n\t=== TOP K FREQUENT ELEMENTS ===";
	std::cout << "\n\t===============================\n";

	/* Write Input */
	std::cout << "\n\tK = " << k;

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
	std::vector ret = sol.topKFrequent(nums, k);


	first = true;
	if (k > 1)
		std::cout << "\n\tTop " << k << " Frequent elements: [";
	else
		std::cout << "\n\tTop Frequent element: [";

	for (auto x: ret)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n\n";


	return 0;
}
