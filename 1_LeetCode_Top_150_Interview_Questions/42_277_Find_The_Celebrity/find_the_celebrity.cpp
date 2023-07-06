#include <iostream>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	277) Find The Celebrity
	===========================

	============
	Description:
	============

	Suppose you are at a party with n people(labeled from - to n-1) and among
	them, there may exist one celebrity. The definition of a celebrity is that
	all the other n-1 people know him/her but he/she does not know any of them.

	Now you want to find out who the celebrity is or verify that there is not
	one. The only thing you are allowed to do is to ask questions like: "Hi, A.
	Do you know B?" to get information of whether A knows B. You may need to
	find out the celebrity (or verify there is not one) by asking as few
	quesitons as possible (in asymptotic sense).

	You are given a helper function bool knows(a, b) which tells you whether A
	knows B. Implement a function int findCelebrity(n), your function should
	minimize the number of calls to knows.

	=====
	Node: There will be exacly one celebrity if he/she is in the party. Return
	      the celebrity's label if there is a celebrity in the party. If there
		  is no celebrity, return -1;
	=====

	===================================
	FUNCTION: int findCelebrity(int n);
	===================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	

	--- Example 2 ---
	<++>

	--- Example 3 ---
	<++>

	*** Constraints ***
	<++>

*/

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution{
public:
	int findCelebrity(int n)
	{
		int candidate = 0;
		for (int i = 1; i < n; i++)
		{
			if (knows(candidate, i))
				candidate = i;
		}

		for (int i = 0; i < n; i++)
		{
			if (i != candidate && knows(candidate, i) || !knows(i, candidate))
				return -1;
		}
	
		return candidate;
	}
};
