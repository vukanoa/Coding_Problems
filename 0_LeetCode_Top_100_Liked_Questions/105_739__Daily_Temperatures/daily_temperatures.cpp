#include <iostream>
#include <vector>
#include <stack>
#include <climits>

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

	Note:
		This is a BAD Solution, I just wanted to put it here just because the
		constraints are so small that we could consider this O(n) Time and O(1)
		Space so I wondered if it would pass all the tests or if it's going to
		give us a TLE.

		Hint hint: It passed. However this is such a bad solution.
		Move to the second one if you want to learn how to solve this.

	Technically, this idea seems to be efficient if you look at the Time and/or
	Space Complexity, however it's not really efficient.

	It's true that it's O(n), however that's only due to the given Constraints.

	30 <= temperatures[i] <= 100
	This is a constant. It's always 71 different temperatures that are possible
	to be in vector "temperatures".

	"map" will be temperatures with it's corresponding indices in vector
	"temperatures".

	Since we have 71 different temperatures(Starting from 30 all the way up to
	100) we can make a vector with 100 elements.

	Why 100? Because it's much easier to index. If we were to "save some space"
	we'd have to consider temperature 30 as index 0. We would always have to
	subtract 30 when indexing a vector "map" and that would be a lot harder to
	read.

	So why do we need 100 elements vector named "map"?
	We will traverse the vector "temperatures" from the last index to the first
	one.

	Everytime we visit certain temperature, we will denote that with its
	corresponding index.

	Vector "map" will first be filled with INT_MAX values that will represent
	that temperature x at index x have not been found yet traversing from the
	back of the vector.

	It's easier to "show you".

		temp = [73, 74, 75, 71, 69, 72, 76, 73]

		map =  [INT_MAX, INT_MAX, ..., INT_MAX, INT_MAX, ..., INT_MAX];
		           0        1             30       31           100
		        ^^^^^^^^^^^^^^^^^^^^^^
		             Not important
		
	Now we start traversing form the back:
		temp = [73, 74, 75, 71, 69, 72, 76, 73]
		                                     i
	
	As we're on temperature 73, we have to check every values in vector "map"
	starting from the index 74(in this case).

	Why? Because non-INT_MAX denotes that up to this point(going form right to
	left) there is a temperature that is greater than the current one.
	However we have to traverse through all of them(starting from current
	temperatures + 1) because we need to find the closest index with a greater
	temperature.

	So Simulation would look something like this:

	1.
		temp = [73, 74, 75, 71, 69, 72, 76, 73]
		                                     i

		Before:
			map =  [INT_MAX, INT_MAX, ..., INT_MAX, ..., INT_MAX, ..., INT_MAX]
					   0        1             30           73           100
					^^^^^^^^^^^^^^^^^^^^^^
						 Not important

		After:
			map =  [INT_MAX, INT_MAX, ..., INT_MAX, ...,   7    , ..., INT_MAX]
					   0        1             30          73         100
					^^^^^^^^^^^^^^^^^^^^^^
						 Not important

		Before:
			answer = [MAX, MAX, MAX, MAX, MAX, MAX, MAX, MAX]
			           0    1    2    3    4    5    6    7

		After:
			answer = [MAX, MAX, MAX, MAX, MAX, MAX, MAX, MAX]
			           0    1    2    3    4    5    6    7




	2.
		temp = [73, 74, 75, 71, 69, 72, 76, 73]
		                                 i

		Before:
			map =  [...,  7, .., INT_MAX, ..., INT_MAX]
			             73        76           100 

		After:
			map =  [...,  7, ..,    6   , ..., INT_MAX]
			             73        76           100 


		Before:
			answer = [MAX, MAX, MAX, MAX, MAX, MAX, MAX, MAX]
			           0    1    2    3    4    5    6    7

		After:
			answer = [MAX, MAX, MAX, MAX, MAX, MAX, MAX, MAX]
			           0    1    2    3    4    5    6    7





	3.
		temp = [73, 74, 75, 71, 69, 72, 76, 73]
		                             i

		Before:
			map =  [...,  INT_MAX,   7  , ..,    6   , ..., INT_MAX]
			                72       73        76           100 

		After:
			map =  [...,    5    ,   7  , ..,    6   , ..., INT_MAX]
			                72       73        76           100 


		Before:
			answer = [MAX, MAX, MAX, MAX, MAX, MAX, MAX, MAX]
			           0    1    2    3    4    5    6    7

		After:
			answer = [MAX, MAX, MAX, MAX, MAX,  6 , MAX, MAX]
			           0    1    2    3    4    5    6    7


		...

		You get the idea.

		After two for loops we will end up with this:
			answer = [1, 2, 6, 5, 5, 6, INT_MAX, INT_MAX]
			          0  1  2  3  4  5    6         7

		
		Now all we have to do is traverse through this "answer" and if it's
		INT_MAX, set it to 0 since that's what's said in the Description of a
		problem.

		And if it's not INT_MAX, then subtract current i from answer[i]:
			answer[i] = answer[i] - i;

		That way we get the righ result.
	
*/

/* Time  Beats:  5.10% */
/* Space Beats: 98.30% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Inefficient{
public:
	std::vector<int> dailyTemperatures(std::vector<int>& temperatures)
	{
		std::vector<int> map(101, INT_MAX);
		std::vector<int> answer(temperatures.size(), INT_MAX);

		for (int i = temperatures.size() - 1; i >= 0; i--)
		{
			for (int curr = temperatures[i] + 1; curr <= 100; curr++)
			{
				if (map[curr] < answer[i])
					answer[i] = map[curr];
			}

			map[temperatures[i]] = i;
		}

		for (int i = 0; i < temperatures.size(); i++)
		{
			if (answer[i] == INT_MAX)
				answer[i] = 0;
			else
				answer[i] = answer[i] - i;
		}

		return answer;
	}
};




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




/*
	------------
	--- IDEA ---
	------------

	Another way of implementing the above Solution. Maybea bit more intuitive.

*/

/* Time  Beats: 46.94% */
/* Space Beats: 63.85% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Monotonic_Stack {
public:
	std::vector<int> dailyTemperatures(std::vector<int>& temperatures)
	{
		int n = temperatures.size();

		std::vector<int> results (n, 0);

		std::stack<int> monotonic_stack;
		monotonic_stack.push(n-1);

		for (int i = n-2; i >= 0; i--)
		{
			while (!monotonic_stack.empty() && temperatures[i] >= temperatures[monotonic_stack.top()])
				monotonic_stack.pop();

			if (!monotonic_stack.empty() && temperatures[i] < temperatures[monotonic_stack.top()])
				results[i] = monotonic_stack.top() - i;

			monotonic_stack.push(i);
		}

		return results;
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
