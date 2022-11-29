#include <iostream>


/*
	==============
	=== MEDIUM ===
	==============
	
	===========================
	24) Swap Nodes in Pairs
	===========================
	
	============
	Description:
	============

	Given a linked list, swap every two adjacent nodes and return its head.
	You must solve the problem without modifying the values in the list's
	nodes(i.e., only nodes themselves may be changed.)
	
	==============================================
	FUNCTION: ListNode* swapPairs(ListNode* head);
	==============================================
	
	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================
	
	--- Example 1 ---
	Input:  head = [1, 2, 3, 4]
	Output: [2, 1, 4, 3]

	1 -> 2 -> 3 -> 4
	2 -> 1 -> 4 -> 3

	
	--- Example 2 ---
	Input:  head = []
	Output: []
	

	--- Example 3 ---
	Input:  head = [1]
	Output: [1]
	
	*** Constraints ***
	The number of nodes in the list is in the range [0, 100].
	0 <= Node.val <= 100

*/


// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


void
print_list(struct ListNode* head)
{
	std::cout << "\n\t[";

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

class Solution{
public:
	struct ListNode*
	swap_every_two(struct ListNode* first_prev, struct ListNode* first, struct ListNode* second)
	{
		first->next = second->next;
		second->next = first;

		if (first_prev)
			first_prev->next = second;
		
		return second;
	}

	struct ListNode*
	swapPairs(struct ListNode* head)
	{
		if (head == nullptr)
			return head;
		else if (head->next == nullptr)
			return head;

		head = swap_every_two(nullptr, head, head->next);
		struct ListNode* tmp = head->next;

		while (tmp->next)
		{
			if (tmp->next == nullptr || tmp->next->next == nullptr)
				return head;

			tmp = swap_every_two(tmp, tmp->next, tmp->next->next);
			tmp = tmp->next;
		}

		return head;
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	// struct ListNode four (4);
	// struct ListNode three(3, &four);
	// struct ListNode two  (2, &three);
	// struct ListNode one  (1, &two);
	// struct ListNode* head = &one;

	/* Example 2 */
	// struct ListNode* head = nullptr;

	/* Example 3 */
	// struct ListNode one(1);
	// struct ListNode* head = &one;

	/* Example 4 */
	// struct ListNode five (5);
	// struct ListNode four (4, &five);
	// struct ListNode three(3, &four);
	// struct ListNode two  (2, &three);
	// struct ListNode one  (1, &two);
	// struct ListNode* head = &one;

	/* Example 5 */
	struct ListNode six  (6);
	struct ListNode five (5, &six);
	struct ListNode four (4, &five);
	struct ListNode three(3, &four);
	struct ListNode two  (2, &three);
	struct ListNode one  (1, &two);
	struct ListNode* head = &one;

	std::cout << "\n\t===========================";
	std::cout << "\n\t=== SWAP NODES IN PAIRS ===";
	std::cout << "\n\t===========================\n\n";

	std::cout << "\n\tOriginal List:";
	print_list(head);

	head = sol.swapPairs(head);

	std::cout << "\n\tAfter Swapping:";
	print_list(head);

	return 0;
}
