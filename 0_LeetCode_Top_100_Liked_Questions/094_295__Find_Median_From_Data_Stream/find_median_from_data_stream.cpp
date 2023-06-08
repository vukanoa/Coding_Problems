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

	Since the median is the middle value in an ordered, sorted, array, then
	it's going to be easy to always get a median.

	In an array where we have odd number of elemets, median is the middle index
	in a sorted array.

	In an array where we have even number of elements, median is the average of
	two middle values.

	If our array is sorted, we'll always know where that is.

	~~~~~~~~~~~~~~~~~~~~~~
	~~~ Naive Approach ~~~
	~~~~~~~~~~~~~~~~~~~~~~

	If we were to add these elements, respectively: 3, 2, 1, 4

	Each "add" would be in O(n) times in the worst case because we would have
	to "shift" every element after it:

	Let's simulate adding of these elements above:

		[3         ]

	Now when we want to add 2, in order, we have to shift 3 to the right by
	one and then put 2 where 3 was before shifting.

		[2, 3      ]

	Now add 1. We have to shift both 2 and 3 by one to the right and then put
	1 where 2 was before shifting.

		[1, 2, 3   ]

	Now Add 4. We don't have to shift anything, but we have to find the place
	where we should put 4, and as a result of that we would traverse all the
	elements in the array, thus making it O(n) again.

		[1, 2, 3, 4]

	Not findMedian is going to be easy. It's going to be O(1). Take two middle
	elements(because there are even number of elements) and add them and divide
	by 2:
		(2 + 3) / 2.0 = 2.5

	findMedian --> O(1)
	addNum     --> O(n)

	But we can clearly see that this is not an optimal approach.
	We can do better by using a different data structure.

	~~~~~~~~~~~~~~~~~~~~~~~~~~
	~~~ Efficient Approach ~~~
	~~~~~~~~~~~~~~~~~~~~~~~~~~

	How can we speed this O(n) addNum operation up?
		Heap/Priority queue!
	
	Instead of having just a single array of elements, we're going to break
	this up into two arrays. We're going to have two subsets:

	Instead of this:

		[1, 2, 3, 4]
	

	We'll have this:

		[1, 2]   [3, 4]

	And ALL elements from the "left" array are going to be less than or equal
	(<=) than ALL elements from the "right" array.

	This would make it easy to get a Median.
	But we're not just going to use two arrays, we're going to use Heaps!

	So we'll have:
		Small Heap          Large Heap
		 [1, 2]              [3, 4]

	So, how does this help?

	Small Heap will be a Max Heap, where Large Heap is going to be a Min Heap.
	It's maybe counter intuitive judging by the names, but it'll make sense.

	Since we are interested only in a MIDDLE (or two middle if there are even
	number of elements) element in the SORTED array, it's irrelevant if
	elements before and after the middle(or two middle ones) are sorted or not
	as long as the middle value is reall a middle value.

	What do I mean by this?
	Example:

		[1, 3, 5, 6, 7, 8, 9]

	Here, middle value is 6 in this SORTED array. But the only thing that is
	important here is that 6 is in the right spot. We could also have this:

		[5, 1, 3, 6, 8, 7, 9]

	And the median would be the same. We know that all the elements BEFORE the
	middle value are less than the middle value and all the elements AFTER the
	middle value are greater than the middle value.

	That highly suggests that we could use a Heap data structure.

	We're using two Heaps:
		Small Heap          Large Heap
		 [1, 2]              [3, 4]

	Small Heap --> Max Heap
	Large Heap --> Min Heap

	Why is a "Small Heap" Max Heap and "Large Heap" Min Heap?

	Since we've seen that we only need the middle values, to be in its right
	place and that ones that are less than the middle values only must be
	BEFORE the middle values, but DON'T have to be sorted, and the ones that
	are greater than the middle values only must be AFTER the middle values,
	but DON'T have to be sorted.

	That is EXACTLY what a Heap gives us:

	In a Max Heap, maximum element is in the root. And each level is just
	smallest than it's parent node, but isn't a BST.

	For example: (Binary Tree(NOT BST!!!) representation)
		_______________________
		___________9___________
		_____8___________7_____
		__5_____6_____3_____4__
		2___1__________________


	Array representation of the above example:
		[9, 8, 7, 5, 6, 3, 4, 2, 1]

	That is a Max Heap!

	As you can see, Only the Max element is Where it should be. Other elements
	are only less than the previous level, but are not "in order".
	If you were to do a "inorder" traversal through this Binary Tree, elements
	WOULD NOT be sorted, as it should be when you're doing an inorder traversal
	on a BST.

	But how will a Heap help us?

	Well, as we've said, we're going to have 2 Heaps:

		Small Heap          Large Heap
		 [1, 2]              [3, 4]

	Small Heap --> Max Heap
	Large Heap --> Min Heap

	When we want to findMedian, if there are even number of elements, then we
	are going to take Max element of "Small Heap"(which is a Max Heap) and a
	Min element of "Large Heap"(which is a Min Heap), add the together and
	divide by 2.

	If there are even number of elements, we have to see which Heap have more
	elements in it.
		If Small_heap.size() > large_heap.size() then:
			max element from a Small Heap is guaranteed to be a Median.
		else
			Min element from a Large Heap is guaranteed to be a Median.
	
	
	so that' when our Heaps are in "Equilibrium".

	Before findMedian, Heaps have to fulfill two properties:
		1. EVERY element from the "Small heap" have to be less than or equal to
		   EVERY element from the "Large heap".

		2. "Small Heap" and "Large Heap" MUST NOT differ in size more than 1.
		       Meaning, they have to be approximately of the same size. They
			   can differ in size maximally by a single element.
	
	Heap:
		Finding a max element from a Max Heap is always O(1).
		Finding a min element from a Min Heap is always O(1).

	Regular array:
	Finding a max/min element from a regular array would be O(n).


	Heap:
		Adding an element in Heap is going to be a O(log n).
	
	Regular array:
		Adding an element in a regular array would be O(n).
	
	That's how we've optimized the Naive Approach.


	
	Let's Simulate Adding a few elements in these Heaps, to see how these above
	two properties are going to influence the process.

	We are gong to add, respectively, these elements:
	add 3
	add 2
	add 7
	add 4
	add 9

	and then we are going to findMedian().

		Small Heap          Large Heap
		 []                  []

	Legend:
		 ( T ) --> True
		 ( F ) --> False


	I) ### Add 3
		Small Heap          Large Heap
		 [3]                  []

			Properties:
			 ( T ) 1. EVERY element from the "Small heap" have to be less than
			          or equal (<=) to EVERY element from the "Large heap".

			 ( T ) 2. "Small Heap" and "Large Heap" MUST NOT differ in size
			          more than 1. Meaning, they have to be approximately of
					  the same size. They can differ in size maximally by a
					  single element.




	II) ### Add 2
		Small Heap          Large Heap
		 [3, 2]              []

			Properties:
			 ( T ) 1. EVERY element from the "Small heap" have to be less than
			          or equal (<=) to EVERY element from the "Large heap".

			 ( F ) 2. "Small Heap" and "Large Heap" MUST NOT differ in size
			          more than 1. Meaning, they have to be approximately of
					  the same size. They can differ in size maximally by a
					  single element.

			Since the 2nd property is FALSE, because the absolute difference
			between the size of "Small Heap" and the size of "Large Heap" is
			greater than 1.

			We have to fix it by removing the max element from Max Heap is max
			heap is of bigger size and adding that element in Min Heap or by
			removing min element from Min Heap if min heap is of bigger size
			and adding that element in Max Heap.

			Remove max element from "Small Heap"(Max Heap) and add it to the
			"Large Heap"(Min Heap).

			Now we have this:

		Small Heap          Large Heap
		 [2]                 [3]

			Properties:
			 ( T ) 1. EVERY element from the "Small heap" have to be less than
			          or equal (<=) to EVERY element from the "Large heap".

			 ( T ) 2. "Small Heap" and "Large Heap" MUST NOT differ in size
			          more than 1. Meaning, they have to be approximately of
					  the same size. They can differ in size maximally by a
					  single element.
			
			Now both properties are fulfilled.
	



	III) ### Add 7
		Small Heap          Large Heap
		 [2, 7]              [3]
		   |
		   v
		 [7, 2]              [3]


		In "Small Heap"(Max Heap) max element is always going to be at index 0.
		First we always add it to the back, and then after the heap function
		"heapify" it "bubbles up" to the right level.

		In "Large Heap"(Min Heap) min element is always going to be at index 0.
		We add it to the back, then the heap function "heapify" "bubbles up"
		the element to the right level.

			Properties:
			 ( F ) 1. EVERY element from the "Small heap" have to be less than
			          or equal (<=) to EVERY element from the "Large heap".

			Since the 1st property is FALSE, since 7 is NOT <= 3, we don't even
			have to look at the 2nd property until we fulfill the 1st property.

			Since initially we are ALWAYS adding an element to the "Small Heap"
			it is guaranteed that if the 1st property is FALSE, we have to
			remove a max element from the "Small Heap"(Max Heap) and add it to
			the "Large Heap"(Min Heap).

			Now we have this:

		Small Heap          Large Heap
		 [2]                 [3, 7]

			Properties:
			 ( T ) 1. EVERY element from the "Small heap" have to be less than
			          or equal (<=) to EVERY element from the "Large heap".

			 ( T ) 2. "Small Heap" and "Large Heap" MUST NOT differ in size
			          more than 1. Meaning, they have to be approximately of
					  the same size. They can differ in size maximally by a
					  single element.
			
			Now both properties are fulfilled.
	



	IV) ### Add 4
		Small Heap          Large Heap
		 [2, 4]              [3, 7]
		   |
		   v
		 [4, 2]              [3, 7]


			Properties:
			 ( T ) 1. EVERY element from the "Small heap" have to be less than
			          or equal (<=) to EVERY element from the "Large heap".

			Since the 1st property is FALSE, since 4 is NOT <= 3, we don't even
			have to look at the 2nd property until we fulfill the 1st property.

			Now we remove the max element from "Small Heap"(Max Heap) and add
			it to the "Large heap"(Min Heap).

			Now we have this:

		Small Heap          Large Heap
		 [2]                 [3, 7, 4]
		  |                     |
		  v                     v
		 [2]                 [3, 4, 7]

			Properties:
			 ( T ) 1. EVERY element from the "Small heap" have to be less than
			          or equal (<=) to EVERY element from the "Large heap".

			 ( F ) 2. "Small Heap" and "Large Heap" MUST NOT differ in size
			          more than 1. Meaning, they have to be approximately of
					  the same size. They can differ in size maximally by a
					  single element.


			Now the 2nd property is FALSE. The absolute difference between
			"Small Heap" and "Large Heap" is 2, which is greater than 1, which
			means we have to equalize them and drive it to the "Equilibrium".

			
			If (small_heap.size() > large_heap.size())
				Take the max element from "Small Heap"(Max Heap) and add it to
				the "Large Heap"(Min Heap).
			else if (small_heap.size() < large_heap.size()) // This is the case
				Take the min element from "Large Heap"(Min Heap) and add it to
				the "Small Heap"(Max Heap).

			We do the "else if" option.
			We remove the min element from the "Large Heap"(Min Heap) and add
			it to the "Small Heap"(Min Heap).

			Now we have this:

		Small Heap          Large Heap
		 [2, 3]             [4, 7]
		   |                     
		   v                     
		 [3, 2]             [4, 7]

			Properties:
			 ( T ) 1. EVERY element from the "Small heap" have to be less than
			          or equal (<=) to EVERY element from the "Large heap".

			 ( T ) 2. "Small Heap" and "Large Heap" MUST NOT differ in size
			          more than 1. Meaning, they have to be approximately of
					  the same size. They can differ in size maximally by a
					  single element.
			
			Now both properties are fulfilled.




	V) ### Add 9
		Small Heap          Large Heap
		 [3, 2, 9]           [4, 7]
		     |
		     v
		 [9, 3, 2]           [4, 7]


			Properties:
			 ( T ) 1. EVERY element from the "Small heap" have to be less than
			          or equal (<=) to EVERY element from the "Large heap".

			Since the 1st property is FALSE, since 9 is NOT <= 4, we don't even
			have to look at the 2nd property until we fulfill the 1st property.

			Now we remove the max element from "Small Heap"(Max Heap) and add
			it to the "Large heap"(Min Heap).

			Now we have this:

		Small Heap          Large Heap
		 [3, 2]              [4, 7, 9]

			Properties:
			 ( T ) 1. EVERY element from the "Small heap" have to be less than
			          or equal (<=) to EVERY element from the "Large heap".

			 ( T ) 2. "Small Heap" and "Large Heap" MUST NOT differ in size
			          more than 1. Meaning, they have to be approximately of
					  the same size. They can differ in size maximally by a
					  single element.
			
			Now both properties are fulfilled.


	

	VI) findMedian()
		
		Since we have an odd number of elements, to find a Median, we have to
		take either:
			1. Max element of "Small Heap"(Max Heap) if "Small Heap"(Max Heap)
			   has more element than "Large Heap"(Min Heap).

			2. Min Element of "Large Heap"(Min Heap) if "Large Heap"(Min Heap)
			   has more element than "Small Heap"(Max Heap).

		Here it's the 2nd case, so we take the min element from the
		"Large Heap"(Min Heap), which in this case is: 4

		We are doing findMedian in O(1)

	
*/

/* Time  Beats: 86.25% */
/* Space Beats: 73.42% */

/*
	Time  Complexity:
		addNum     --> O(log n)
		findMedian --> O(1)
*/
/*
	Space Complexity: O(n)
		We don't use any extra memory then is absolutely necessary, however
		in theory it could be possible that we only use the current element
		that is being added and that we only update a single variable. So since
		that is not the case, we could consider this Solution as having an
		overall Space Complexity: O(n)
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
				
				right.push_back(top);  // O(1)
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
 	// obj->addNum(1);
	// stream.push_back(1);
	// obj->addNum(2);
	// stream.push_back(2);

 	// double mid = obj->findMedian();
	// print_stream(stream);
	// std::cout << "\n\tMid: " << mid;


	// obj->addNum(3);
	// stream.push_back(3);

 	// mid = obj->findMedian();
	// print_stream(stream);
	// std::cout << "\n\tMid: " << mid;




	/* Example 2 */
 	obj->addNum(6);
	stream.push_back(6);
 	double mid = obj->findMedian();
	print_stream(stream);
	std::cout << "\n\tMid: " << mid;

	obj->addNum(10);
	stream.push_back(10);
 	mid = obj->findMedian();
	print_stream(stream);
	std::cout << "\n\tMid: " << mid;

	obj->addNum(2);
	stream.push_back(2);
 	mid = obj->findMedian();
	print_stream(stream);
	std::cout << "\n\tMid: " << mid;

	obj->addNum(6);
	stream.push_back(6);
 	mid = obj->findMedian();
	print_stream(stream);
	std::cout << "\n\tMid: " << mid;

	obj->addNum(5);
	stream.push_back(5);
 	mid = obj->findMedian();
	print_stream(stream);
	std::cout << "\n\tMid: " << mid;

	obj->addNum(0);
	stream.push_back(0);
 	mid = obj->findMedian();
	print_stream(stream);
	std::cout << "\n\tMid: " << mid;

	obj->addNum(6);
	stream.push_back(6);
 	mid = obj->findMedian();
	print_stream(stream);
	std::cout << "\n\tMid: " << mid;

	obj->addNum(3);
	stream.push_back(3);
 	mid = obj->findMedian();
	print_stream(stream);
	std::cout << "\n\tMid: " << mid;

	obj->addNum(1);
	stream.push_back(1);
 	mid = obj->findMedian();
	print_stream(stream);
	std::cout << "\n\tMid: " << mid;

	obj->addNum(0);
	stream.push_back(0);
 	mid = obj->findMedian();
	print_stream(stream);
	std::cout << "\n\tMid: " << mid;





	/* Example 3 */
 	// obj->addNum(-1);
	// stream.push_back(-1);
 	// double mid = obj->findMedian();
	// print_stream(stream);
	// std::cout << "\n\tMid: " << mid;

	// obj->addNum(-2);
	// stream.push_back(-2);
 	// mid = obj->findMedian();
	// print_stream(stream);
	// std::cout << "\n\tMid: " << mid;

	// obj->addNum(-3);
	// stream.push_back(-3);
 	// mid = obj->findMedian();
	// print_stream(stream);
	// std::cout << "\n\tMid: " << mid;

	// obj->addNum(-4);
	// stream.push_back(-4);
 	// mid = obj->findMedian();
	// print_stream(stream);
	// std::cout << "\n\tMid: " << mid;

	// obj->addNum(-5);
	// stream.push_back(-5);
 	// mid = obj->findMedian();
	// print_stream(stream);
	// std::cout << "\n\tMid: " << mid;




	/* Example 4 */
 	// obj->addNum(0);
	// stream.push_back(0);
 	// double mid = obj->findMedian();
	// print_stream(stream);
	// std::cout << "\n\tMid: " << mid;

	// obj->addNum(0);
	// stream.push_back(0);
 	// mid = obj->findMedian();
	// print_stream(stream);
	// std::cout << "\n\tMid: " << mid;


	std::cout << "\n\n";


	return 0;
}
