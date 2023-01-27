#include <iostream>

/*
	============
	=== EASY ===
	============

	=====================================
	160) Intersection of Two Linked Lists
	=====================================

	============
	Description:
	============

	Given the heads of two singly linked-lists "headA" and "headB", return the
	node at which the two lists intersect. If the two linked lists have no
	intersection at all, return null.

	For example, the following two linked lists begin to intersect at node c1:

	A:       a1 -> a2 --\
	                     \
	                      ---> c1 -> c2 -> c3
	                     /
	B: b1 -> b2 -> b3 --/

	The test cases are generated such that there are no cycles anywhere in the
	entire linked structure.

	=====
	Note: that the linked lists must retain their original structure after the
	===== functions returns.

	Custom Judge:

	THe input to the judge are given as follows(your program is not given these
	inputs):
		- "intersectVal"
			The value of the node where the intersection occurs.

		- "listA"
			The first linked list.

		- "listB"
			The second linked list.

		- "skipA"
			The number of nodes to skip ahead in "listA" (starting from the
			head) to get to the intersected node.

		- "skipB"
			The number of nodes to skip ahead in "listB" (starting from the
			head) to get to the intersected node.

	The judge will then create the linked structure based on these inputs and
	pass two heads, "headA" and "headB" to your program. If you correctly
	return the intersected node, then your solution will be accepted.

	==========================================================================
	FUNCTION: ListNode* getIntersectionNode(ListNode *headA, ListNode *headB);
	==========================================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	A:         4 -> 1 --\
	                     \
	                      ---> 8 -> 4 -> 5
	                     /
	B:    5 -> 6 -> 1 --/

	Input:
		intersectVal = 8, ListA = [4, 1, 8, 4, 5], listB = [5, 6, 1, 8, 4, 5],
		skipA = 2, skipB = 3

	Output: Intersected at '8'
	Explanation: The Intersected node's value is 8(note that this must not be 0
	if the two lists intersect).
	From the head of A, it reads as [4, 1, 8, 4, 5]. From the head of B, it
	reads as [5, 6, 1, 8, 4, 5]. There are 2 nodes before the intersected node
	in A; There are 3 nodes before the intersected node in B.

	- Note that the intersected node's value is not 1 because the nodes with
	value 1 in A and B (2nd node in A and 3rd node in B) are different node
	references. In other words, they point to two different locations in
	memory, while the nodes with value 8 in A and B (3rd node in A and 4th node
	in B) point to the same location in memory.


	--- Example 2 ---
	A:    1 -> 9 -> 1 --\
	                     \
	                      ---> 2 -> 4
	                     /
	B:              3 --/

	Input:
		intersectVal = 2, listA = [1, 9, 1, 2, 4], listB = [3, 2, 4],
		skipA = 3, skipB = 1
	Output: Intersected at '2'
	Explanation: The intersected node's value is 2 (note that this must not be
	0 if the two lists intersect).
	From the head of A, it reads as [1, 9, 1, 2, 4]. From the head of B, it
	reads as [3, 2, 4]. There are 3 nodes before the intersected node in A;
	There are 1 node before the intersected node in B.

	--- Example 3 ---
	A:    2 -> 6 -> 4

	B:         1 -> 5

	Input:
		intersectVal = 0, listA = [2, 6, 4], listB = [1, 5],
		skipA = 3, skipB = 2

	Output: No intersection
	Explanation: From the head of A, it reads as [2, 6, 4]. From the head of
	B, it reads as [1, 5]. Since the two lists do not intersect, intersectVal
	must be 0, while skipA and skipB can be arbitrary values.
	Explanation: The two lists do not intersect, so return null.

	*** Constraints ***
	The number of nodes of "listA" is in the "m".
	The number of nodes of "listB" is in the "n".
	1 <= m, n <= 3 * 10^4
	1 <= Node.val <= 10^5
	0 <= skipA < m
	0 <= skipB < n
	intersectVal is 0 if "listA" and "listB" do not intersect.
	intersectVal == listA[skipA] == listB[skipB] if listA and listB intersect.

	Follow up: Could you write a solution that runs in O(m + n) time and use
	only O(1) memory?

*/


// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


/*
	------------
	--- IDEA ---
	------------

	Iterate through the first  list and count the number of nodes in it.
	Iterate through the second list and count the number of nodes in it.

	If, say, the first is longer than the second, subtract the number of nodes
	of second from the number of nodes of first(the longer one).
	When you have that difference, move the pointer of head of that longer
	linked list by that difference.

	Now just iterate one by one and if the intersection exists, at one point
	they will be pointing at the same address. Return that node.

	If we get to the end of the list without finding that intersection, then
	return NULL;

	Consider this first example:
	  headA ----
	           |
	           v
	A:         4 -> 1 --\
	                     \
	                      ---> 8 -> 4 -> 5
	                     /
	B:    5 -> 6 -> 1 --/
	      ^
	      |
 headB ----

	There are 5 nodes in the first list.
	There are 6 nodes in the second list.

	6 > 5
		difference = 1

	That means that we should start 1 node away from the head of that, longer,
	list.

	We use tmpA and tmpB to iterate through the first and second list
	respectively.
	Now this example looks like this:


	  tmpA ----------
	               /
	              /
	  headA ---- /
	           |/
	           v
	A:         4 -> 1 --\
	                     \
	                      ---> 8 -> 4 -> 5
	                     /
	B:    5 -> 6 -> 1 --/
	      ^    ^
	      |    |
	   headB   |
	           |
	tmpB -------

	Not moving both tmpA and tmpB at the same pace, one by one, they will be
	pointing at the Node 8 and once we compare their pointers, or rather the
	addresses, we will find out that they are indeed pointing at the same node
	and thus will return the intersection node 8.

*/


/* Time  Complexity: O(m + n) */
/* Space Complexity: O(1) */
class Solution {
public:
	ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
	{
		int m = 0; // Number of nodes in listA
		int n = 0; // Number of nodes in listB

		ListNode *tmpA = headA;
		while (tmpA != NULL)
		{
			m++;
			tmpA = tmpA->next;
		}

		ListNode* tmpB = headB;
		while (tmpB != NULL)
		{
			n++;
			tmpB = tmpB->next;
		}

		tmpA = headA;
		tmpB = headB;

		if (m > n)
		{
			int diff = m - n;

			while (diff--)
				tmpA = tmpA->next;

		}
		else if (n > m)
		{
			int diff = n - m;

			while (diff--)
				tmpB = tmpB->next;
		}

		ListNode* intersect = NULL;
		while (tmpA && tmpB)
		{
			// Comparing the addresses, not values
			if (tmpA == tmpB)
			{
				intersect = tmpA;
				break;
			}

			tmpA = tmpA->next;
			tmpB = tmpB->next;
		}

		return intersect;
	}
};

int
main()
{
	Solution sol;

	/* Example 1 */
	/*
		A:         4 -> 1 --\
							 \
							  ---> 8 -> 4 -> 5
							 /
		B:    5 -> 6 -> 1 --/
	*/
	// Nodes in listA before the Intesection
	ListNode four_A(4);
	ListNode one_A(1);

	// Nodes in listB before the Intesection
	ListNode five_B(5);
	ListNode six_B(6);
	ListNode one_B(1);

	// Nodes from the Intersection point onwards
	ListNode eight_inter(8);
	ListNode four_inter(4);
	ListNode five_inter(5);

	// Link nodes in list A before the Intersection
	four_A.next = &one_A;
	one_A.next = &eight_inter;

	// Link nodes in list B before the Intersection
	five_B.next = &six_B;
	six_B.next = &one_B;
	one_B.next = &eight_inter;

	// Link nodes from the Intersection node onwards
	eight_inter.next = &four_inter;
	four_inter.next = &five_inter;

	ListNode *headA = &four_A;
	ListNode *headB = &five_B;



	/* Example 2 */
	/*
		A:    1 -> 9 -> 1 --\
							 \
							  ---> 2 -> 4
							 /
		B:              3 --/
	*/
	// // Nodes in listA before the Intesection
	// ListNode one_A(1);
	// ListNode nine_A(9);
	// ListNode one_A_2(1);

	// // Nodes in listB before the Intesection
	// ListNode three_B(3);

	// // Nodes from the Intersection point onwards
	// ListNode two_inter(2);
	// ListNode four_inter(4);

	// // Link nodes in list A before the Intersection
	// one_A.next = &nine_A;
	// nine_A.next = &one_A_2;
	// one_A_2.next = &two_inter;

	// // Link nodes in list B before the Intersection
	// three_B.next = &two_inter;

	// // Link nodes from the Intersection node onwards
	// two_inter.next = &four_inter;

	// ListNode *headA = &one_A;
	// ListNode *headB = &three_B;


	/* Example 3 */
	/*
		A:    2 -> 6 -> 4

		B:         1 -> 5
	*/
	// // Nodes in listA before the Intesection
	// ListNode two_A(2);
	// ListNode six_A(6);
	// ListNode four_A(4);

	// // Nodes in listB before the Intesection
	// ListNode one_B(1);
	// ListNode five_B(5);

	// // There is no Intersection and thus no linking with Intersection

	// // Link nodes in listA
	// two_A.next = &six_A;
	// six_A.next = &four_A;

	// // Link nodes in listB
	// one_B.next = &five_B;

	// ListNode *headA = &two_A;
	// ListNode *headB = &one_B;


	std::cout << "\n\t========================================";
	std::cout << "\n\t=== INTERSECTION OF TWO LINKED LISTS ===";
	std::cout << "\n\t========================================\n";

	/* Solution */
	ListNode* intersection = sol.getIntersectionNode(headA, headB);

	if (intersection)
		std::cout << "\n\tIntersection at Node: " << intersection->val;
	else
		std::cout << "\n\tThese two lists do NOT Intersect!";

	std::cout << "\n\n";

	return 0;
}
