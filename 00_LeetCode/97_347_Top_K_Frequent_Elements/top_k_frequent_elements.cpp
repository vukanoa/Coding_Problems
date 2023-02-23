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



/*
	------------
	--- IDEA ---
	------------

	Step 1 is the same as in the previous(above) idea.

	Now we should simulate what Bucket Sort does, but not all the way. We do
	not have to sort it completely.

	Okay, first of all, why are we doing this?

	Consider this example:
	[1, 1, 1, 2, 2, 100]

	If we were to do the exact same thing as in Bucket Sort, we would possibly
	use waay more Space than necessary.

	If we were to store the number of occurrences of each element in a separate
	array, then in this case we would have:
	[0, 3, 2, ..., 1]
	 0  1  2      100

	That means that we have allocated 100 elements on the Stack or Heap, but
	we only use 3 slots. That is unacceptable.

	We can overcome this with a clever observation. We can see that there are
	most N(nums.size()) elements in the vector "nums".

	Since that is the case, we know for a fact that a maximum number of
	occurences that an element can have is N. (Array is consisted of a single
	element repeated N times).

	Example:
		[8, 8, 8, 8, 8]

	It is absolutely impossible to have more than N occurences. Also we can
	observe that we can have two elements occur the same amount of time.
	(Though there will always be K distinct unique elements. Meaning we will
	always have a result, we don't have to check these cases)

	The solution is to to have an array of size N(maximum possible number of
	occurences) and that for each slot, we maintain a vector of elements that
	have that number of occurences in the array "nums".

	Example:
	[5, 6, 2, 3, 4, 9, 9, 9, 6, 6, 6, 7, 7]

	Map:
		5: 1
		6: 4
		2: 1
		3: 1
		4: 1
		9: 3
		7: 2

	vector of vectors "freq" is of size N

        freq:
        [
   0:   /
   1:   [5, 2, 3, 4]
   2:   [7]
   3:   [9]
   4:   [6]
   5:   /
   6:   /
   7:   /
   8:   /
   9:   /
  10:   /
  11:   /
        ]

	After forming this "freq", we just iterate from the back and push in vector
	"ret" until ret.size() becomes k, that is until we have "pushed" k elements
	in our vector that is our return value.

*/


/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Bucket{
public:
	std::vector<int> topKFrequent(std::vector<int>& nums, int k)
	{
		std::unordered_map<int, int> map;

		// Step 1: Store frequence of all elements in map
		// O(N)
		for (int n : nums)
			map[n]++;

		// Step 2: Bucket Sort's first step
		// O(N)
		std::vector<std::vector<int>> freq(nums.size() + 1);
		for (auto it: map)
			freq[it.second].push_back(it.first);

		// Step 3: Take every item from the back until k elements are taken
		// O(K)
		std::vector<int> ret;
		for (int i = freq.size() - 1; i >= 0; i--)
		{
			for (int elem : freq[i])
			{
				ret.push_back(elem);

				if (ret.size() == k)
					return ret;
			}
		}

		return ret;
	}
};


int
main()
{
	Solution sol;
	Solution_Bucket sol_bucket;

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
	// std::vector ret = sol.topKFrequent(nums, k);
	std::vector ret = sol_bucket.topKFrequent(nums, k);


	/* Write Output */
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
