#include <iostream>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	328) Odd Even Linked List
	===========================

	============
	Description:
	============

	Given the head of a singly linked list, group all the nodes with odd
	indices together followed by the nodes with even indices, and return the
	reordered list.

	The first node is considered odd, and the second node is even, and so on.

	Note that the relative order inside both the even and odd groups should
	remain as it was in the input.

	You must solve the problem in O(1) extra space complexity and O(n) time
	complexity.

	===============================
	FUNCTION: <++>
	===============================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
		1 --> 2 --> 3 --> 4 --> 5

		          |
		          v

		1 --> 3 --> 5 --> 2 --> 4

	Input: head = [1,2,3,4,5]
	Output: [1,3,5,2,4]




	--- Example 2 ---
		2 --> 1 --> 3 --> 5 --> 6 --> 4 --> 7

		                |
		                v

		2 --> 3 --> 6 --> 7 --> 1 --> 5 --> 4

	Input: head = [2,1,3,5,6,4,7]
	Output: [2,3,6,7,1,5,4]

	--- Example 3 ---
	<++>

	*** Constraints ***
    The number of nodes in the linked list is in the range [0, 10^4].
    -10^6 <= Node.val <= 10^6


*/


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */


/*
	------------
	--- IDEA ---
	------------

	Self-explanatory. Just look at the code.
	
*/

/* Time  Beats: 98.14% */
/* Space Beats: 99.97% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
	ListNode* oddEvenList(ListNode* head)
	{
		if (head == nullptr)
			return nullptr;

		ListNode* odd  = head;
		ListNode* even = head->next;
		ListNode* even_head = even;

		while (even != nullptr && even->next != nullptr)
		{
			odd->next = even->next;
			odd = odd->next;

			even->next = odd->next;
			even = even->next;
		}

		// Link Odd list with the Even list
		odd->next = even_head;

		return head;
	}
};
