#include <iostream>
#include <vector>
#include <algorithm> // For Heap

/*
	============
	=== HARD ===
	============

	=================================
	295) Find Median from Data Stream
	=================================

	============
	Description:
	============

	The median is the middle value in an ordered integer list. If the size of
	the list is even, there is no middle value, and the median is the mean of
	the two middles values.

		- For example, for arr = [2, 3, 4], the median is 3.
		- For example, for arr = [2, 3], the median is (2 + 3) / 2 = 2.5

	Implement the MedianFinder class:

		- MedianFinder() initializes the MedianFinder object.
		- void addnum(int num) adds the integer "num" from the data stream to
		  the data structure.
		- double findMedian() returns the median of all elements so far.
		  Answers within 10^-5 of the actual answer will be accepted.

	Follow up:
		- If all integer numbers from the stream are in the range [0, 100],
		  how would you optimize your solution?

		- If 99% of all integer numbers from the stream are in the range
		  [0, 100], how would you optimize your solution?

	===============================
	CLASS:
	class MedianFinder{
	public:
		MedianFinder() {}

		void addNum(int num) {}

		double findMedian()
	};
	===============================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:
	["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
	[[], [1], [2], [], [3], []]
	Output:
	[null, null, null, 1.5, null, 2.0]

	*** Constraints ***
	-10^5 <= num <= 10^5
	There will be at least one element in the data structure before calling
	  "findMedian"
	At most 5 * 10^4 calls will be made to "addNum" and "findMedian"

*/


/*
	------------
	--- IDEA ---
	------------

	TODO
	
*/

/* Time  Beats: 86.25% */
/* Space Beats: 73.42% */

/*
	Time  Complexity:
		1.
			addNum: O(logn)

		2.
			findMedian: O(1)
*/
/*
	Space Complexity: O(1)
		1.
			addNum: O(1)

		2.
			findMedian: O(1)
*/
class MedianFinder{
public:
	MedianFinder() : size(0)
	{}

	void addNum(int num)
	{
		left.push_back(num);
		std::push_heap(left.begin(), left.end()); // O(logn)

		if (!left.empty() && !right.empty() && left.front() > right.front())
		{
			std::pop_heap(left.begin(), left.end()); // O(logn)

			int top = left.back(); // O(1)
			left.pop_back();       // O(1)

			right.push_back(top);  // O(1)
			std::push_heap(right.begin(), right.end(), std::greater<>{}); // O(logn)
		}

		int difference = left.size() - right.size();

		if (std::abs(difference) > 1) // They are not approximately of same size
		{
			if (left.size() > right.size())
			{
				std::pop_heap(left.begin(), left.end()); // O(logn)

				int top = left.back(); // O(1)
				left.pop_back();       // O(1)
				
				right.push_back(top);  // (1)
				std::push_heap(right.begin(), right.end(), std::greater<>{}); // O(logn)
			}
			else
			{
				std::pop_heap(right.begin(), right.end(), std::greater<>{}); // O(logn)

				int top = right.back(); // O(1)
				right.pop_back();       // O(1)

				left.push_back(top);    // O(1)
				std::push_heap(left.begin(), left.end()); // O(logn)
			}
		}

		size++;
	}

	double findMedian()
	{
		if (size & 1) // Odd size of elements
		{
			if (left.size() > right.size())
				return left.front();
			else
				return right.front();
		}
		else
		{
			return (left.front() + right.front()) / 2.0;
		}
	}

private:
	std::vector<int> left;  // small Heap (MAX Heap)
	std::vector<int> right; // large Heap (MIN Heap)

	int size;
};


void
print_stream(std::vector<int>& stream)
{
	bool first = true;
	std::cout << "\n\n\tCurrent Stream: [";
	for (auto x: stream)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]";

}


int
main()
{
	MedianFinder* obj = new MedianFinder();

	std::cout << "\n\t====================================";
	std::cout << "\n\t=== FIND MEDIAN FROM DATA STREAM ===";
	std::cout << "\n\t====================================";

	// For printing
	std::vector<int> stream;

	/* Example 1 */
 	obj->addNum(1);
	stream.push_back(1);
	obj->addNum(2);
	stream.push_back(2);

 	double mid = obj->findMedian();
	print_stream(stream);
	std::cout << "\n\tMid: " << mid;


	obj->addNum(3);
	stream.push_back(3);

 	mid = obj->findMedian();
	print_stream(stream);
	std::cout << "\n\tMid: " << mid;




	/* Example 2 */
 	// obj->addNum(6);
 	// double mid = obj->findMedian();
	// std::cout << "\n\tMid: " << mid << "\n\n";

	// obj->addNum(10);
 	// mid = obj->findMedian();
	// std::cout << "\n\tMid: " << mid << "\n\n";

	// obj->addNum(2);
 	// mid = obj->findMedian();
	// std::cout << "\n\tMid: " << mid << "\n\n";

	// obj->addNum(6);
 	// mid = obj->findMedian();
	// std::cout << "\n\tMid: " << mid << "\n\n";

	// obj->addNum(5);
 	// mid = obj->findMedian();
	// std::cout << "\n\tMid: " << mid << "\n\n";

	// obj->addNum(0);
 	// mid = obj->findMedian();
	// std::cout << "\n\tMid: " << mid << "\n\n";

	// obj->addNum(6);
 	// mid = obj->findMedian();
	// std::cout << "\n\tMid: " << mid << "\n\n";

	// obj->addNum(3);
 	// mid = obj->findMedian();
	// std::cout << "\n\tMid: " << mid << "\n\n";

	// obj->addNum(1);
 	// mid = obj->findMedian();
	// std::cout << "\n\tMid: " << mid << "\n\n";

	// obj->addNum(0);
 	// mid = obj->findMedian();
	// std::cout << "\n\tMid: " << mid << "\n\n";





	/* Example 2 */
 	// obj->addNum(-1);
 	// double mid = obj->findMedian();
	// std::cout << "\n\tMid: " << mid << "\n\n";

	// obj->addNum(-2);
 	// mid = obj->findMedian();
	// std::cout << "\n\tMid: " << mid << "\n\n";

	// obj->addNum(-3);
 	// mid = obj->findMedian();
	// std::cout << "\n\tMid: " << mid << "\n\n";

	// obj->addNum(-4);
 	// mid = obj->findMedian();
	// std::cout << "\n\tMid: " << mid << "\n\n";

	// obj->addNum(-5);
 	// mid = obj->findMedian();
	// std::cout << "\n\tMid: " << mid << "\n\n";




	/* Example 3 */
 	// obj->addNum(0);
 	// double mid = obj->findMedian();
	// std::cout << "\n\tMid: " << mid << "\n\n";

	// obj->addNum(0);
 	// mid = obj->findMedian();
	// std::cout << "\n\tMid: " << mid << "\n\n";

	std::cout << "\n\n";


	return 0;
}
