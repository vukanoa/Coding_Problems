#include <iostream>


/*
	============
	=== HARD ===
	============
	
	============================
	25) Reverse Nodes in k-Group
	============================
	
	============
	Description:
	============

	Given the "head" of a linked list, reverse the nodes of the list "k" at a
	time, and return the modified list.

	"k" is a positive integer and is less than or equal to the length of the
	linked list. If the number of nodes is not a multiple of "k" then left-out
	nodes, in the end, should remain as it is.

	You may not alter the values in the list's nodes, only nodes themselves
	may be changed.
	
	=========================================================
	FUNCTION: ListNode* reverseKGroup(ListNode* head, int k);
	=========================================================
	
	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================
	
	--- Example 1 ---
	Input:  head = [1, 2, 3, 4, 5], k = 2
	Output: [2, 1, 4, 3, 5]
	
	--- Example 2 ---
	Input:  head = [1, 2, 3, 4, 5], k = 3
	Output: [3, 2, 1, 4, 5]
	
	*** Constraints ***
	The number of nodes in the list is "n".
	1 <= k <= n <= 5000
	0 <= Node.val <= 1000

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
	void reverse_list(struct ListNode** head, struct ListNode** tail, struct ListNode** rem, int k)
	{
		struct ListNode* prev = nullptr;
		struct ListNode* curr = (*head);
		struct ListNode* next = (*head);

		(*tail) = (*head);
		(*rem) = nullptr;

		while (curr && k--)
		{
			if (curr == (*head))
				(*tail) = curr;

			if (k == 0)
				(*rem) = next->next;

			next = next->next;

			curr->next = prev;
			prev = curr;
			curr = next;
		}

		(*head) = prev;
	}

	struct ListNode* reverseKGroup(struct ListNode* head, int k)
	{
		if (k == 1 || head == nullptr)
			return head; // Return Original List

		int n = 0;
		struct ListNode* local_head = head;
		struct ListNode* ultimate_head = head;

		while (local_head)
		{
			n++;
			local_head = local_head->next;
		}
		local_head = head;

		int remaining_nodes = n;
		bool first = true;

		/*
			3 -> 2 -> 1 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9
			               ^
						   |
			   -------------
			   |
			local_head

			It's the head of a sublist that we're trying to reverse.
			Sublist:
				4 -> 5 -> 6
			in this case (k = 3)
		*/

		while (remaining_nodes >= k)
		{
			struct ListNode* tail = nullptr;
			struct ListNode* rem = nullptr; // Remainder
			reverse_list(&local_head, &tail, &rem, k);

			if (first)
			{
				ultimate_head = local_head;
				first = false;
			}
			else if (k < n)
				head->next = local_head;

			tail->next = rem;
			head = tail;
			local_head = head->next;

			remaining_nodes = remaining_nodes - k;

			// print_list(ultimate_head);
		}

		return ultimate_head;
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	// struct ListNode five (5);
	// struct ListNode four (4, &five);
	// struct ListNode three(3, &four);
	// struct ListNode two  (2, &three);
	// struct ListNode one  (1, &two);

	// struct ListNode* head = &one;
	// int k = 2;


	/* Example 2 */
	// struct ListNode five (5);
	// struct ListNode four (4, &five);
	// struct ListNode three(3, &four);
	// struct ListNode two  (2, &three);
	// struct ListNode one  (1, &two);

	// struct ListNode* head = &one;
	// int k = 3;


	/* Example 3 */
	// struct ListNode nine (9);
	// struct ListNode eight(8, &nine);
	// struct ListNode seven(7, &eight);
	// struct ListNode six  (6, &seven);
	// struct ListNode five (5, &six);
	// struct ListNode four (4, &five);
	// struct ListNode three(3, &four);
	// struct ListNode two  (2, &three);
	// struct ListNode one  (1, &two);

	// struct ListNode* head = &one;
	// int k = 3;


	/* Example 4 */
	struct ListNode eleven(11);
	struct ListNode ten   (10, &eleven);
	struct ListNode nine  (9,  &ten);
	struct ListNode eight (8,  &nine);
	struct ListNode seven (7,  &eight);
	struct ListNode six   (6,  &seven);
	struct ListNode five  (5,  &six);
	struct ListNode four  (4,  &five);
	struct ListNode three (3,  &four);
	struct ListNode two   (2,  &three);
	struct ListNode one   (1,  &two);

	struct ListNode* head = &one;
	int k = 3;


	/* Example 5 */
	// struct ListNode eleven(11);
	// struct ListNode ten   (10, &eleven);
	// struct ListNode nine  (9,  &ten);
	// struct ListNode eight (8,  &nine);
	// struct ListNode seven (7,  &eight);
	// struct ListNode six   (6,  &seven);
	// struct ListNode five  (5,  &six);
	// struct ListNode four  (4,  &five);
	// struct ListNode three (3,  &four);
	// struct ListNode two   (2,  &three);
	// struct ListNode one   (1,  &two);

	// struct ListNode* head = &one;
	// int k = 2;


	/* Example 6 */
	// struct ListNode eleven(11);
	// struct ListNode ten   (10, &eleven);
	// struct ListNode nine  (9,  &ten);
	// struct ListNode eight (8,  &nine);
	// struct ListNode seven (7,  &eight);
	// struct ListNode six   (6,  &seven);
	// struct ListNode five  (5,  &six);
	// struct ListNode four  (4,  &five);
	// struct ListNode three (3,  &four);
	// struct ListNode two   (2,  &three);
	// struct ListNode one   (1,  &two);

	// struct ListNode* head = &one;
	// int k = 1;


	/* Example 7 */
	// struct ListNode* head = nullptr;
	// int k = 3;
	


	std::cout << "\n\t================================";
	std::cout << "\n\t=== REVERSE NODES IN K-GROUP ===";
	std::cout << "\n\t================================\n\n";

	std::cout << "\n\tOriginal List:";
	print_list(head);

	std::cout << "\n\t\t*** Reversing Nodes in K-Group (k = " << k << ") ***\n\n";
	head = sol.reverseKGroup(head, k);

	std::cout << "\n\tModified List:";
	print_list(head);

	return 0;
}
