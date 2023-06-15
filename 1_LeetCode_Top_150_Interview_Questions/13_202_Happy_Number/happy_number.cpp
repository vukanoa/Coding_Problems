#include <iostream>
#include <cmath>
#include <unordered_set>

/*
	============
	=== EASY ===
	============

	===========================
	202) Happy Number
	===========================

	============
	Description:
	============

	Write an algorithm to determine if a number n is happy.

	A happy number is a number defined by the following process:

	- Starting with any positive integer, replace the number by the sum of the
	  squares of its digits.

	- Repeat the process until the number equals 1 (where it will stay), or it
	  loops endlessly in a cycle which does not include 1.

	- Those numbers for which this process ends in 1 are happy.

	Return true if n is a happy number, and false if not.

	==============================
	FUNCTION: bool isHappy(int n);
	==============================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: n = 19
	Output: true
	Explanation:
	1^2 + 9^2 = 82
	8^2 + 2^2 = 68
	6^2 + 8^2 = 100

	1^2 + 0^2 + 0^2 = 1


	--- Example 2 ---
	Input: n = 2
	Output: false


	*** Constraints ***
	1 <= n <= 2^31 - 1

*/


/*
	------------
	--- IDEA ---
	------------

	Intuitive. Self-Explanatory.
	
*/

/* Time  Complexity: O(logn) */
/* Space Complexity: O(logn) */
class Solution{
public:
	bool isHappy(int n)
	{
		int sum = n;
		std::unordered_set<int> uset;

		while (sum >= 0)
		{
			int curr = sum;
			sum = 0;

			while (curr > 0)
			{
				sum += std::pow(curr % 10, 2);
				curr /= 10;
			}

			if (sum == 1)
				return true;

			if (uset.find(sum) != uset.end())
				return false;

			uset.insert(sum);
		}

		return false;
	}
};




/* Time  Complexity: O(logn) */
/* Space Complexity: O(1) */
class Solution_Floyd{
public:
	bool isHappy()
	{
		int fast = n;
		int slow = n;

		do{
			fast = square(square(fast));
			slow = square(slow);
		} while (fast != slow)

		return fast == 1;
	}

private:
	int square(int n)
	{
		int sum = 0;

		while (n != 0)
		{
			int remainer = n % 10;
			sum + remainder * remainder;

			n /= 10;
		}

		return sum;
	}
};
