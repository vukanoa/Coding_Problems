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


/*
	------------
	--- IDEA ---
	------------

	First check if head is nullptr or if head->next is nullptr because if
	there are 0 or 1 nodes in the list, respectively, we just return head in
	both cases since there isn't enough "material" to perform a swap.
	Swap requires at least 2 elements. Nodes in this case.

	If we have more than 2 nodes in the list then call function:
		relink_first_and_second(first_prev, first, second);

	That function always returns the third argument, the "second" node.
	"second" node was:
		first_prev -> first -> second
			or if "first" is the head of the list, then first_prev is nullptr:
		first -> second

	and after the function relink_first_and_second, it's:
		first_prev -> second -> first
			or if "first" is the head of the list, then first_prev is nullptr:
		second -> first

	function always returns the address of the "second" after relinking.

	So after the first call of this function, global head points to previously
	2nd node in the list. Now 1st node in the list was previously 2nd, and 2nd
	node was previously 1st.

	Let pointer "tmp" now point to 2nd node. That is current head's next.

	while tmp's next node isn't a nullptr do:
		if tmp->next or tmp->next->next is nullptr just return head.
		That means - If there is only one node left in the list that wasn't
		swapped(which means we're done since we need two nodes for swapping),
		or if there aren't any nodes yet to be swapped - again, return the head
		of the newly relinked list.

	Remember, tmp points to a node that was 1st at the beginning and now is
	2nd.

	If tmp->next or tmp->next->next is nullptr it's the same check as the one
	we did at the very beginning of this function.
	We are essentially checking if there is enough "material" for a swap. Swap
	needs two nodes to perform a swap.

	If it's the case that there are at least 2 nodes yet unswapped then:
		relink_first_and_second(tmp, tmp->next, tmp->next->next);

	The difference here is that we now have a "first_prev" node, since "first"
	isn't a head.
	Now we have:
		first_prev   ->    first    -> second
		  tmp            tmp->next    tmp->next->next

	And after the function call, we have:
		first_prev   ->    second   -> first
	                         ^
	                         |
	tmp ----------------------

	Since we called the function relink_first_and_second with tmp ponting at
	the "first_prev" which's next pointed to the first node of two that has to
	be swapped, now after the call of this function, our "tmp" points to
	"second", so we need to move it 'to the right' so that we could again
	call this function but for the next two nodes that have to be swapped.
	This is inside of a while loop.

	Before calling this function in the while loop, "tmp" has to point at
	"first_prev". So that's why we have to move "tmp" one node 'to the right'
	after the call of functions relink_first_and_second.

*/


/* Time  Beats: 100% */
/* Space Beats: 93.43% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution{
public:
	struct ListNode*
	relink_first_and_second(struct ListNode* first_prev, struct ListNode* first, struct ListNode* second)
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

		head = relink_first_and_second(nullptr, head, head->next);
		struct ListNode* tmp = head->next;

		while (tmp->next)
		{
			if (tmp->next == nullptr || tmp->next->next == nullptr)
				return head;

			tmp = relink_first_and_second(tmp, tmp->next, tmp->next->next);
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
	std::cout << "\n\t===========================\n";


	/* Write Input */
	std::cout << "\n\tOriginal List:";
	print_list(head);


	/* Solution */
	head = sol.swapPairs(head);


	/* Write Output */
	std::cout << "\n\tAfter Swapping:";
	print_list(head);

	return 0;
}
