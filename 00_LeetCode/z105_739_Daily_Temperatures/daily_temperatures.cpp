#include <iostream>
#include <vector>
#include <stack>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	739) Daily Temperatures
	===========================

	============
	Description:
	============

	Given an array of integers "temperatures" represents the daily
	temperatures, return an array "answer" such that answer[i] is the number of
	days you have to wait after the i-th day to get a warmer temperature. If
	there is no future day for which this is possible, keep answer[i] == 0
	instead.

	===================================================================
	FUNCTION: vector<int> dailyTemperatures(vector<int>& temperatures);
	===================================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  temperatures = [73, 74, 75, 71, 69, 72, 76, 73]
	Output: [1, 1, 4, 2, 1, 1, 0, 0]

	--- Example 2 ---
	Input:  temperatures = [30, 40, 50, 60],
	Output: [1, 1, 1, 0]

	--- Example 3 ---
	Input:  temperatures = [30, 60, 90]
	Output: [1, 1, 0]

	*** Constraints ***
	1 <= temperatures.length <= 10^5
	30 <= temperatures[i] <= 100

*/


/*
	------------
	--- IDEA ---
	------------

	The whole idea is - Monotonic Stack.
	Classic Monotonic Stack problem.

	Simulation of the Algorithm is self-explanatory

	Algorithm:
	Before start:
		temp = [73, 74, 75, 71, 69, 72, 76, 73]
		ret  = [ 0,  0,  0,  0,  0,  0,  0,  0]
		stck = | Empty                        |


	1)
                 0   1   2   3   4   5   6   7
        temp = [73, 74, 75, 71, 69, 72, 76, 73]
   ------------- i
   |
   |                      0   1   2   3   4   5   6   7
   |    Before : ret  = [ 0,  0,  0,  0,  0,  0,  0,  0]
   |    After  : ret  = [ 0,  0,  0,  0,  0,  0,  0,  0]
   |
   |
   |	while(!stack.empty() && temp[stack.top()] < temp[i])
   |	{
   |		ret[stack.top()] = i - stack.top();
   |		stack.pop();
   |	}
   |    stack.push(i);
   |
   |    Before : stck = | Empty                        |
   |    After  : stck = | 0                            |
   |                      ^
   |                      |
   |______________________|



	2)
                 0   1   2   3   4   5   6   7
        temp = [73, 74, 75, 71, 69, 72, 76, 73]
   ----------------- i
   |
   |                      0   1   2   3   4   5   6   7
   |    Before : ret  = [ 0,  0,  0,  0,  0,  0,  0,  0]
   |    After  : ret  = [ 1,  0,  0,  0,  0,  0,  0,  0]
   |                      ^
   |
   |	while(!stack.empty() && temp[stack.top()] < temp[i])
   |	{
   |		ret[stack.top()] = i - stack.top();
   |		stack.pop();
   |	}
   |    stack.push(i);
   |
   |    Before : stck = | 0                            |
   |    After  : stck = | 1                            |
   |                      ^
   |                      |
   |______________________|




	3)
                 0   1   2   3   4   5   6   7
        temp = [73, 74, 75, 71, 69, 72, 76, 73]
   --------------------- i
   |
   |                      0   1   2   3   4   5   6   7
   |    Before : ret  = [ 1,  0,  0,  0,  0,  0,  0,  0]
   |    After  : ret  = [ 1,  1,  0,  0,  0,  0,  0,  0]
   |                          ^
   |
   |	while(!stack.empty() && temp[stack.top()] < temp[i])
   |	{
   |		ret[stack.top()] = i - stack.top();
   |		stack.pop();
   |	}
   |    stack.push(i);
   |
   |    Before : stck = | 1                            |
   |    After  : stck = | 2                            |
   |                      ^
   |                      |
   |______________________|



	4)
                 0   1   2   3   4   5   6   7
        temp = [73, 74, 75, 71, 69, 72, 76, 73]
   ------------------------- i
   |
   |                      0   1   2   3   4   5   6   7
   |    Before : ret  = [ 1,  1,  0,  0,  0,  0,  0,  0]
   |    After  : ret  = [ 1,  1,  0,  0,  0,  0,  0,  0]
   |
   |
   |	while(!stack.empty() && temp[stack.top()] < temp[i])
   |	{
   |		ret[stack.top()] = i - stack.top();
   |		stack.pop();
   |	}
   |    stack.push(i);
   |
   |    Before : stck = | 2                            |
   |    After  : stck = | 2 | 3                        |
   |                          ^
   |                          |
   |__________________________|




	5)
                 0   1   2   3   4   5   6   7
        temp = [73, 74, 75, 71, 69, 72, 76, 73]
   ----------------------------- i
   |
   |                      0   1   2   3   4   5   6   7
   |    Before : ret  = [ 1,  1,  0,  0,  0,  0,  0,  0]
   |    After  : ret  = [ 1,  1,  0,  0,  0,  0,  0,  0]
   |
   |
   |	while(!stack.empty() && temp[stack.top()] < temp[i])
   |	{
   |		ret[stack.top()] = i - stack.top();
   |		stack.pop();
   |	}
   |    stack.push(i);
   |
   |    Before : stck = | 2 | 3                        |
   |    After  : stck = | 2 | 3 | 4                    |
   |                              ^
   |                              |
   |______________________________|



	6)
                 0   1   2   3   4   5   6   7
        temp = [73, 74, 75, 71, 69, 72, 76, 73]
   --------------------------------- i
   |
   |                      0   1   2   3   4   5   6   7
   |    Before : ret  = [ 1,  1,  0,  0,  0,  0,  0,  0]
   |    After  : ret  = [ 1,  1,  0,  2,  1,  0,  0,  0]
   |                                  ^   ^
   |
   |	while(!stack.empty() && temp[stack.top()] < temp[i])
   |	{
   |		ret[stack.top()] = i - stack.top();
   |		stack.pop();
   |	}
   |    stack.push(i);
   |
   |    Before : stck = | 2 | 3 | 4                    |
   |    After  : stck = | 2 | 5                        |
   |                          ^
   |                          |
   |__________________________|




	7)
                 0   1   2   3   4   5   6   7
        temp = [73, 74, 75, 71, 69, 72, 76, 73]
   ------------------------------------- i
   |
   |                      0   1   2   3   4   5   6   7
   |    Before : ret  = [ 1,  1,  0,  2,  1,  0,  0,  0]
   |    After  : ret  = [ 1,  1,  4,  2,  1,  1,  0,  0]
   |                              ^           ^
   |
   |	while(!stack.empty() && temp[stack.top()] < temp[i])
   |	{
   |		ret[stack.top()] = i - stack.top();
   |		stack.pop();
   |	}
   |    stack.push(i);
   |
   |    Before : stck = | 2 | 5                        |
   |    After  : stck = | 6                            |
   |                      ^
   |                      |
   |______________________|



	8)
                 0   1   2   3   4   5   6   7
        temp = [73, 74, 75, 71, 69, 72, 76, 73]
   ----------------------------------------- i
   |
   |                      0   1   2   3   4   5   6   7
   |    After  : ret  = [ 1,  1,  4,  2,  1,  1,  0,  0]
   |    After  : ret  = [ 1,  1,  4,  2,  1,  1,  0,  0]
   |
   |
   |	while(!stack.empty() && temp[stack.top()] < temp[i])
   |	{
   |		ret[stack.top()] = i - stack.top();
   |		stack.pop();
   |	}
   |    stack.push(i);
   |
   |    Before : stck = | 6                            |
   |    After  : stck = | 6 | 7                        |
   |                          ^
   |                          |
   |__________________________|

*/


/* Time  Beats: 85.73% */
/* Space Beats: 59.90% */
/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::vector<int> dailyTemperatures(std::vector<int>& temp)
	{
        int n = temp.size();
        std::stack<int> stack;
        std::vector<int> ret(n, 0);

        for(int i = 0; i < n; i++)
		{
            while(!stack.empty() && temp[stack.top()] < temp[i])
			{
                ret[stack.top()] = i - stack.top();
                stack.pop();
            }

            stack.push(i);
        }

        return ret;
    }
};


int
main()
{
	Solution sol;

	/* Example 1 */
	std::vector<int> temperatures = {73, 74, 75, 71, 69, 72, 76, 73};

	/* Example 2 */
	// std::vector<int> temperatures = {30, 40, 50, 60};

	/* Example 3 */
	// std::vector<int> temperatures = {30, 60, 90};


	std::cout << "\n\t==========================";
	std::cout << "\n\t=== DAILY TEMPERATURES ===";
	std::cout << "\n\t==========================\n";


	/* Write Input */
	bool first = true;
	std::cout << "\n\tTemperatures: [";
	for (auto x: temperatures)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n";

	/* Solution */
	std::vector<int> ret = sol.dailyTemperatures(temperatures);

	/* Write Output */
	first = true;
	std::cout << "\n\tOutput: [";
	for (auto x: ret)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n\n";

	return 0;
}
