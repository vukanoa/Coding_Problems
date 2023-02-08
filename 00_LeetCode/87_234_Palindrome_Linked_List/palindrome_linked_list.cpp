#include <iostream>
#include <queue>

/*
	============
	=== EASY ===
	============

	===========================
	234) Palindrome Linked List
	===========================

	============
	Description:
	============

	Given the "head" of a singly linked list, return "true" if it is a
	palindrome or "false" otherwise.

	Follow up: Could you do it in O(n) time and O(1) space?

	============================================
	FUNCTION: bool isPalindrome(ListNode* head);
	============================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  head = [1, 2, 2, 1]
	Output: true

	--- Example 2 ---
	Input:  head = [1, 2]
	Output: false

	*** Constraints ***
	The number of node sin the list is in the range [1, 10^5]
	0 <= Node.val <= 9

*/


// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


/*
	------------
	--- IDEA ---
	------------

	Push elements in queue while reversing the linked list.
	Afterwards check if the queue from 0 to n-1 have the same values as
	the reversed linked list.

*/


// Beats 98.5% Time, 70.5% Space
/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
	bool isPalindrome(ListNode* head)
	{
	    if (head->next == nullptr)
	        return true;

	    std::queue<int> queue;

	    ListNode* prev = nullptr;
	    ListNode* curr = head;
	    ListNode* next = head;

	    while (curr != nullptr)
	    {
	        queue.push(curr->val);
	        next = curr->next;

	        curr->next = prev;
	        prev = curr;
	        curr = next;
	    }

	    head = prev;

	    while (head != nullptr)
	    {
	        if (head->val == queue.front())
	        {
	            queue.pop();
	            head = head->next;
	        }
	        else
	            return false;
	    }

	    return true;
	}
};


void
print_list(struct ListNode* head)
{
	std::cout << "\n\t\t";

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

	std::cout << "\n\n";
}


int
main()
{
	Solution sol;

	/* Example 1 */
	// ListNode one_1(1);
	// ListNode two_1(2);
	// ListNode two_2(2);
	// ListNode one_2(1);

	// one_1.next = &two_1;
	// two_1.next = &two_2;
	// two_2.next = &one_2;

	// ListNode* head = &one_1;




	/* Example 2 */
	// ListNode one(1);
	// ListNode two(2);

	// one.next = &two;

	// ListNode* head = &one;




	/* Example 3 */
	ListNode one_1(1);
	ListNode two_1(2);
	ListNode three(3);
	ListNode two_2(2);
	ListNode one_2(1);

	one_1.next = &two_1;
	two_1.next = &three;
	three.next = &two_2;
	two_2.next = &one_2;

	ListNode* head = &one_1;




	std::cout << "\n\t==============================";
	std::cout << "\n\t=== PALINDROME LINKED LIST ===";
	std::cout << "\n\t==============================\n\n";


	/* Write Input */
	std::cout << "\tList:";
	print_list(head);

	/* Solution */
	if (sol.isPalindrome(head))
		std::cout << "\n\tIt is INDEED a Palindrome!\n\n";
	else
		std::cout << "\n\tIt is NOT a Palindrome!\n\n";


	return 0;
}
