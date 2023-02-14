#include <iostream>

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
		  Answers within 1-^-5 of the actual answer will be accepted.

	Follow up:
		- If all integer numbers from the s tream are in the range [0, 100],
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

	We're having sorted Doubly Linked List and we always insert in the right
	place.

	The key here is, we're always keeping pointer mid at our median.

	This is the core, everytime we add a number, we update the mid pointer
	accordingly. As you can see, this is a O(1) operation.

    void update(struct ListNode* new_node)
    {
        if (mid == nullptr)
            mid = head;
		else
		{
			if (added_after_mid)
			{
				if (size % 2 != 0) // Odd number of elements
					mid = mid->next;
			}
			else
			{
				if (size % 2 == 0)
					mid = mid->prev;
			}
		}
    }

*/


// Naive Solution
class MedianFinder {
private:
    struct ListNode{
        int val;
        struct ListNode* prev;
        struct ListNode* next;

        ListNode(int num) : val(num), next(nullptr), prev(nullptr){}
    };

    struct ListNode* head;
    struct ListNode* mid;
    unsigned size;
    bool added_after_mid;
public:
    MedianFinder()
    : mid(nullptr), head(nullptr), size(0), added_after_mid(false)
    {}

    void addNum(int num)
    {
         struct ListNode* new_node = new ListNode(num);

        // O(n)
        if (head == nullptr)
            head = new_node;
        else
        {
            if (new_node->val <= head->val)
            {
                new_node->next = head;
				head->prev = new_node;
                head = new_node;
            }
            else
            {
                struct ListNode* prev = nullptr;
                struct ListNode* curr = head;
                while (curr && curr->val < new_node->val)
                {
                    prev = curr;
                    curr = curr->next;
                }

                new_node->next = prev->next;
                prev->next = new_node;
				new_node->prev = prev;

				if (curr)
					curr->prev = new_node;
            }

        }

        size++;
        if (mid && num > mid->val)
            added_after_mid = true;
        else
            added_after_mid = false;

        update(new_node);
		std::cout << "\n\tAdded: " << num;
    }

    void update(struct ListNode* new_node)
    {
        if (mid == nullptr)
            mid = head;
		else
		{
			if (added_after_mid)
			{
				if (size % 2 != 0) // Odd number of elements
					mid = mid->next;
			}
			else
			{
				if (size % 2 == 0)
					mid = mid->prev;
			}
		}
    }

    double findMedian()
    {
        if (size & 1) // Odd number of elements
            return (double)mid->val;

        return (double)(mid->val + (mid->next)->val) / 2;
    }
};


int
main()
{
	MedianFinder* obj = new MedianFinder();

	std::cout << "\n\t====================================";
	std::cout << "\n\t=== FIND MEDIAN FROM DATA STREAM ===";
	std::cout << "\n\t====================================\n\n";


	/* Example 1 */
 	obj->addNum(1);
	obj->addNum(2);
 	double mid = obj->findMedian();
	std::cout << "\n\tMid: " << mid;

	obj->addNum(3);
 	mid = obj->findMedian();
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
