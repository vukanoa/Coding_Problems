#include <iostream>

/*
	============
	=== EASY ===
	============

	===========================
	412) Fizz Buzz
	===========================

	============
	Description:
	============

	Given an integer n, return a string array answer (1-indexed) where:

	answer[i] == "FizzBuzz" if i is divisible by 3 and 5.
	answer[i] == "Fizz" if i is divisible by 3.
	answer[i] == "Buzz" if i is divisible by 5.
	answer[i] == i (as a string) if none of the above conditions are true.

	=========================================
	FUNCTION: vector<string> fizzBuzz(int n);
	=========================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: n = 3
	Output: ["1","2","Fizz"]

	--- Example 2 ---
	Input: n = 5
	Output: ["1","2","Fizz","4","Buzz"]

	--- Example 3 ---
	Input: n = 15
	Output: ["1","2","Fizz","4","Buzz","Fizz","7","8","Fizz","Buzz","11","Fizz","13","14","FizzBuzz"]

	*** Constraints ***
	1 <= n <= 10^4

*/


/*
	------------
	--- IDEA ---
	------------

	I really don't see a point of this Problem. It is literally said in the
	Description what they want. You don't have to "come up" with a Solution.

	I really don't know why this question exists at all.
	
*/

/* Time  Beats: 100% */
/* Space Beats: 27.36% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    vector<string> fizzBuzz(int n)
    {
        std::vector<std::string> results;

        for (int i = 1; i <= n; i++)
        {
            if (i % 3 == 0 && i % 5 == 0)
                results.push_back("FizzBuzz");
            else if (i % 3 == 0)
                results.push_back("Fizz");
            else if (i % 5 == 0)
                results.push_back("Buzz");
            else
                results.push_back(std::to_string(i));
        }

        return results;
    }
};
