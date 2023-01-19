#include <iostream>

/*
	============
	=== EASY ===
	============

	===========================
	141) Linked List Cycle
	===========================

	============
	Description:
	============

	Given "head", the head of a linked list, determine if the linked list has a
	cycle in it.

	There is a cycle in a linked list if there is some node in the list that
	can be reached again by continuously following the "next" pointer.
	Internally, "pos" is used to denote the index of the node that tail's
	"next" pointer is connected to.

	Note that "pos" is not passed as a parameter.

	Return "true" if there is a cycle in the linked list. Otheriwse, return
	"false".

	========================================
	FUNCTION: bool hasCycle(ListNode *head);
	========================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  head = [3, 2, 0, -4], pos = 1
	Output: true

	--- Example 2 ---
	Input:  head = [1, 2], pos = 0
	Output: true

	--- Example 3 ---
	Input:  head = [1], pos = -1
	Output: false

	*** Constraints ***
	The number of the nodes in the list is in the range [0, 10^4]
	-10^5 <= Node.val <= 10^5
	"pos" is -1 or a valid index in the linked list

*/

// Definition for singly-linked list.
struct ListNode{
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};



/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution{
public:
	bool hasCycle(ListNode *head)
	{
		struct ListNode* slow = head;
		struct ListNode* fast = head;

		while (fast != NULL && fast->next != NULL)
		{
			slow = slow->next;
			fast = fast->next->next;

			if (slow == fast)
				break;
		}

		if (fast == NULL || fast->next == NULL)
			return false;

		return true;
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	/*
		3 -> 2 -> 0 -> -4
		^---------------|
	*/
	struct ListNode minus_four(-4);
	struct ListNode zero(0);
	struct ListNode two(2);
	struct ListNode three(3);
	minus_four.next = &three;
	zero.next       = &minus_four;
	two.next        = &zero;
	three.next      = &two;
	struct ListNode* head = &minus_four;



	/* Example 2 */
	/*
		1 -> 2
		^----|
	*/
	// struct ListNode two(2);
	// struct ListNode one(1);
	// two.next = &one;
	// one.next = &two;
	// struct ListNode* head = &one;



	/* Example 3 */
	/*
		1 -> NULL
	*/
	// struct ListNode one(1);
	// struct ListNode* head = &one;



	/* Example 4 */
	/*
								 -----
								 v   |
		1 -> 2 -> 3 -> 4 -> 5 -> 6   |
								 -----
	*/
	// struct ListNode six(6);
	// struct ListNode five(5);
	// struct ListNode four(4);
	// struct ListNode three(3);
	// struct ListNode two(2);
	// struct ListNode one(1);
	// six.next   = &six;
	// five.next  = &six;
	// four.next  = &five;
	// three.next = &four;
	// two.next   = &three;
	// one.next   = &two;
	// struct ListNode* head = &one;


	/* Example 5 */
	/*

		1 -> 2 -> 3 -> 4 -> 5 -> 6
		                    ^----|
	*/
	// struct ListNode six(6);
	// struct ListNode five(5);
	// struct ListNode four(4);
	// struct ListNode three(3);
	// struct ListNode two(2);
	// struct ListNode one(1);
	// six.next   = &five;
	// five.next  = &six;
	// four.next  = &five;
	// three.next = &four;
	// two.next   = &three;
	// one.next   = &two;
	// struct ListNode* head = &one;



	/* Example 6 */
	/*

		1 -> 2 -> 3 -> 4 -> 5 -> 6
		               ^---------|
	*/
	// struct ListNode six(6);
	// struct ListNode five(5);
	// struct ListNode four(4);
	// struct ListNode three(3);
	// struct ListNode two(2);
	// struct ListNode one(1);
	// six.next   = &four;
	// five.next  = &six;
	// four.next  = &five;
	// three.next = &four;
	// two.next   = &three;
	// one.next   = &two;
	// struct ListNode* head = &one;

	/* Example 7 */
	/*

		1 -> 2 -> 3 -> 4 -> 5 -> 6
		          ^--------------|
	*/
	// struct ListNode six(6);
	// struct ListNode five(5);
	// struct ListNode four(4);
	// struct ListNode three(3);
	// struct ListNode two(2);
	// struct ListNode one(1);
	// six.next   = &three;
	// five.next  = &six;
	// four.next  = &five;
	// three.next = &four;
	// two.next   = &three;
	// one.next   = &two;
	// struct ListNode* head = &one;


	/* Example 8 */
	/*

		1 -> 2 -> 3 -> 4 -> 5 -> 6
		     ^-------------------|
	*/
	// struct ListNode six(6);
	// struct ListNode five(5);
	// struct ListNode four(4);
	// struct ListNode three(3);
	// struct ListNode two(2);
	// struct ListNode one(1);
	// six.next   = &two;
	// five.next  = &six;
	// four.next  = &five;
	// three.next = &four;
	// two.next   = &three;
	// one.next   = &two;
	// struct ListNode* head = &one;


	/* Example 9 */
	/*

		1 -> 2 -> 3 -> 4 -> 5 -> 6
		^------------------------|
	*/
	// struct ListNode six(6);
	// struct ListNode five(5);
	// struct ListNode four(4);
	// struct ListNode three(3);
	// struct ListNode two(2);
	// struct ListNode one(1);
	// six.next   = &one;
	// five.next  = &six;
	// four.next  = &five;
	// three.next = &four;
	// two.next   = &three;
	// one.next   = &two;
	// struct ListNode* head = &one;


	std::cout << "\n\t=========================";
	std::cout << "\n\t=== LINKED LIST CYCLE ===";
	std::cout << "\n\t=========================\n\n";


	/* Solution */
	bool has_cycle = sol.hasCycle(head);

	if (has_cycle)
		std::cout << "\n\tThere is INDEED a Cycle in this Linked List!\n\n";
	else
		std::cout << "\n\tThere is NOT a Cycle in this Linked List!\n\n";

	return 0;
}
