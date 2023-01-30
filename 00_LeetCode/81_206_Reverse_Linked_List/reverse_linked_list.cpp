#include <iostream>

/*
	============
	=== EASY ===
	============

	===========================
	206) Reverse Linked List
	===========================

	============
	Description:
	============

	Given the "head" of a singly-linked list, reverse the list, and return the
	reversed list.

	================================================
	FUNCTION: ListNode* reverseList(ListNode* head);
	================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  head = [1, 2, 3, 4, 5]
	Output: [5, 4, 3, 2, 1]

	--- Example 2 ---
	Input:  head = [1, 2]
	Output: [2, 1]

	--- Example 3 ---
	Input:  []
	Output: []

	*** Constraints ***
	The number of nodes in the list is the range [, 5000]
	-5000 <= Node.val <= 5000

	Follow-up: a linked list can be reversed either iterateively or
	recursively. Could you implement both?

*/


// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


class Solution{
public:
	ListNode* reverseList(ListNode* head)
	{
		ListNode* prev = nullptr;
		ListNode* curr = head;
		ListNode* next = head;

		while (curr != nullptr)
		{
			next = curr->next;

			curr->next = prev;
			prev = curr;
			curr = next;
		}

		return prev;
	}
};


class Solution_Recursion{
public:
	ListNode* reverseList(ListNode* head)
	{
		ListNode* prev = nullptr;
		ListNode* curr = head;

		reverseListRecursively(&prev, &curr);

        return prev;
	}

	void reverseListRecursively(ListNode** prev, ListNode** curr)
	{
		if ((*curr) == nullptr)
			return;

		ListNode* next = (*curr)->next;
		(*curr)->next = (*prev);
		(*prev) = (*curr);
		(*curr) = next;

		reverseListRecursively(prev, curr);
	}
};


void
print_list(struct ListNode* head)
{
	std::cout << "\n\t\t[";

	bool first = true;
	while (head)
	{
		if (!first)
			std::cout << " -> ";
		else
			first = false;

		std::cout << head->val;
		head = head->next;
	}

	std::cout << "]\n\n";
}


int
main()
{
	Solution sol;

	/* Example 1 */
	ListNode one(1);
	ListNode two(2);
	ListNode three(3);
	ListNode four(4);
	ListNode five(5);

	one.next = &two;
	two.next = &three;
	three.next = &four;
	four.next = &five;

	ListNode* head = &one;



	/* Example 2 */
	// ListNode one(1);
	// ListNode two(2);

	// one.next = &two;

	// ListNode* head = &one;



	/* Example 3 */
	// ListNode* head = nullptr;


	std::cout << "\n\t===========================";
	std::cout << "\n\t=== REVERSE LINKED LIST ===";
	std::cout << "\n\t===========================\n";


	/* Write Input */
	std::cout << "\n\tBefore:";
	print_list(head);

	/* Solution */
	head = sol.reverseList(head);

	/* Write Outpu */
	std::cout << "\n\tAfter:";
	print_list(head);

	return 0;
}
