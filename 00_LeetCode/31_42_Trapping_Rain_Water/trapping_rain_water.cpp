#include <iostream>
#include <vector>
#include <stack>
#include <climits>


/*
	============
	=== HARD ===
	============

	===========================
	42) Trapping Rain Water
	===========================

	============
	Description:
	============

	Given "n" non-negative integers representing an elevation map where the
	width of each bar is 1, compute how much water it can trap after raining.

	=============================================
	FUNCTION: int trap(std::vector<int>& height);
	=============================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
        ^
        |
        |
        |
        |
        |               |
        |       |```````| |```|
        |   |```| |   | | | | | |
        ---------------------------------
          0 1 0 2 1 0 1 3 2 1 2 1

	                  0  1  2  3  4  5  6  7  8  9 10 11
	Input:  height = [0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]
	Output: 6




	--- Example 2 ---
        ^
        |
        |
        |           |
        | |`````````|
        | |     |   |
        | | |   | | |
        | | |   | | |
        ---------------------------------
          4 2 0 3 2 5

	Input:  height = [4, 2, 0, 3, 2, 5]
	Output: 9

	*** Constraints ***
	n == height.length
	1 <= n <= 2 * 10^4
	0 <= height[i] <= 10^5

*/


/*
	------------
	--- IDEA ---
	------------

	============
	=== O(n) ===
	============
	*** Dynamic Programming ***

	Forget how to program for a second. What does it mean to "Trap The Rain
	Water" between the bars in 2D?

	Look at an arbitrary range in the vector of bars.

        ^
        |
        |
        |
        |
        |               |
        |       |```````| |```|
        |   |```| |   | | | | | |
        ---------------------------------
          0 1 0 2 1 0 1 3 2 1 2 1
Indexes: [0 1 2 3 4 5 6 7 8 9 A B]
A = 10
B = 11

	If we want to find out that there are 4 "blocks" of water between bars of
	height:
		2 and 3, respectively
	
	How are we going to do that? How can we know that there are two bars with
	height of 1 "inside" the range, between bars 2 and 3?

	Well, we can't. We can't calculate it like that if you think about it. It's
	impossible to know what sort of and how many bars of lower heights, than
	the range we're calculating, there are.

	So, then... How do we do it?

	We can only calculate how many "blocks" of water can be ABOVE current bar.

	It means that at each bar I have to know maximum height of the bar to the
	left until THIS bar(including this one) and maximum height of the bar to
	the right, from the back of the array "height", until THIS bar.

        ^
        |
        |
        |
        |
        |               |
        |       |```````| |```|
        |   |```| |   | | | | | |
        ---------------------------------
          0 1 0 2 1 0 1 3 2 1 2 1
Indexes: [0 1 2 3 4 5 6 7 8 9 A B]
A = 10
B = 11

	Look at index 4(bar with height of 1)

	How many "blocks" of water can be above it?
	Well, let's ask our 1st question:
		1) What is the maximum height of the bar to the left until THIS bar?
		   (Including this bar)

		   It's bar of height 2 (At position 3)

	Then let's ask our 2nd question:
		2) What is the maximum height of the bar to the right, from the back of
		   the array "height", until THIS bar?
		   (Including this bar, as well)

		   It's bar of height 3 (At position 7)
	
	Then let's ask our 3rd question:
		3) What is the current height at position 4?
			
		   It's 1
	
	Then let's ask our 4th and final question:
		4) How do we calculate how many blocks of water can be above current
		   bar?

		   It's MINIMUM of "maximum height to the left" and "maximum height to
		   the right" minus height of the bar at current position.

		   min(left_max[i], right_max[i]) - height[i];
	
	Now we should do that for every single bar in our array "height".
	Since we need to find left_max & right_max for each height[i], we can do
	that in two separate for loops.
	But we're not going to do that in O(n^2) for each vector, i.e. left_max and
	right_max.
	
	We won't be calculating max bar to the left in a way that we go through the
	whole array for each index. That would be O(n^2).

	We can do that by always comparing and storing the taller bar of the two.
	So for left_max[i] we compare:
		max(left_max[i - 1], height[i]);
	and store it in left_max[i];
	
	Final part:
	We go through an entire array "height" and calculate:
		total += std::min(dp_left_max[i], dp_right_max[i] - height[i]);
	
	return total;

*/



/* Time  Beats: 86.9% */
/* Space Beats: 27.8% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_dp{
public:
	int trap(std::vector<int>& height)
	{
		// Since the very left "margin" (coordinate system) cannot hold water
		if (height.size() < 3)
			return 0;

		int n = height.size();
		std::vector<int> dp_left_max (n, 0);
		std::vector<int> dp_right_max(n, 0);

		int total = 0;

		dp_left_max[0] = height[0];
		for (int i = 1; i < n; i++)
			dp_left_max[i] = std::max(dp_left_max[i - 1], height[i]);

		dp_right_max[n - 1] = height[n - 1];
		for (int i = n - 2; i >= 0; i--)
			dp_right_max[i] = std::max(height[i], dp_right_max[i + 1]);

		for (int i = 1; i < n - 1; i++)
			total += std::min(dp_left_max[i], dp_right_max[i]) - height[i];

		return total;
	}
};



/*
	------------
	--- IDEA ---
	------------

	============
	=== O(n) ===
	============
	*** Using Stacks ***

	Instead of storing the largest bar up to an index, as in Dynamic
	Programming approach, we can use stack to keep track of the bars that are
	bounded by longer bars and hence - may store water.

	We keep a stack and iterate over the array.
	We add the index of the bar to the stack if bar is smaller than or equal to
	the bar at the top of the stack, which means that the current bar is
	bounded by the previous bar in the stack.
	If we found a bar longer than that at the top, we are sure that the bar at
	the top of the stack is bounded by the current bar and a previous bar in
	the stack, hence, we can pop and add resulting trapped water to "total".
	
*/


/* Time  Beats: 78.91% */
/* Space Beats: 38.74% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_stack{
public:
	int trap(std::vector<int>& height)
	{
		// Since the very left "margin" (coordinate system) cannot hold water
		if (height.size() < 3)
			return 0;

		int n = height.size();
		int curr_index = 0;
		int total = 0;

		std::stack<int> stack;

		while (curr_index < n)
		{
			while (!stack.empty() && height[stack.top()] < height[curr_index])
			{
				int prev_top = stack.top();
				stack.pop();

				if (stack.empty())
					break;

				int distance = curr_index - stack.top() - 1;
				int bounded = std::min(height[curr_index], height[stack.top()]) - height[prev_top];

				total += distance * bounded;
			}

			stack.push(curr_index++);
		}

		return total;
	}
};


/*
	------------
	--- IDEA ---
	------------

	============
	=== O(n) ===
	============
	*** Using Two Pointers ***

	Instead of computing left and right parts separately, we may think of some
	way to do it in one iteration.

	Example 1:
	Notice that as long as right_max[i] > left_max[i] (from element 0 to 6),
	the trapped water depends upon the left_max, and similar is the case when
	left_max[i] > right_max[i] (from element 8 to 11). So, we can say that if
	there is a larger bar at one end(say right), we are assured that the water
	trapped would be dependant on hright of bar in current direction (from
	left to right).
	As soon as we find the bar at other end(right) is smaller, we start
	iterating in opposite direction (from right to left).

	We must maintain left_max and right_max during iteration, but now we can
	do it in one iteration using two pointers, switching between the two.

	The whole idea comes down to: The way we calculate the water is:
	if we find that the current bar isn't greater than or equal to the max
	until this point, then that's the only situation in which we add water to
	"total".

	We add how much water "squares" can stack up in height and we base that
	on the maximum height of the bar until this bar we're currently on(not
	including this. Not including because in that case we won't add anything)

	Since we're doing this from left to right, now we can try doing it in the
	opposite way, but now we only add if max until this bar(from the back) is
	greater than this bar we're currently on.

	We do this using "Two Pointers" technique. We do it until left meets right,
	that is:
		while (left < right)

*/


/* Time  Beats: 46.73% */
/* Space Beats: 97.61% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_two_pointers{
public:
	int trap(std::vector<int>& height)
	{
		// Since the very left "margin" (coordinate system) cannot hold water
		if (height.size() < 3)
			return 0;

		int n = height.size();
		int total = 0;

		int left  = 0;
		int right = n - 1;
		int left_max  = 0;
		int right_max = 0;

		while (left < right)
		{
			if (height[left] < height[right])
			{
				if (height[left] >= left_max)
					left_max = height[left];
				else
					total += left_max - height[left];

				left++;
			}
			else
			{
				if (height[right] >= right_max)
					right_max = height[right];
				else
					total += right_max - height[right];

				right--;
			}
		}

		return total;
	}
};


int
main()
{
	// Solution_dp sol_dp;
	// Solution_stack sol_stack;
	Solution_two_pointers sol_two_pointers;
	/*
		Compact:

        ^
        |
        |
        |
        |
        |         |
        |    |```||`|
        |  |`|| ||||||
        ----------------------

	*/

	/* Example 1 */
	/*
		Wide: (There is 1 <Space> on the x axis)

        ^
        |
        |
        |
        |
        |                 |
        |       |```````| |```|
        |   |```| |   | | | | | |
        ---------------------------------
          0 1 0 2 1 0 1 3 2 1 2 1

        ^
        |
        |
        |
        |
        |                 |
        |       |`2`3`5`| |`6`|
        |   |`1`| | 4 | | | | | |
        ---------------------------------
          0 1 0 2 1 0 1 3 2 1 2 1

		  Result: 6
		  Going from left to right: 
		  From bar height - bar height There is x squares of water
		  From     1      -      2     There is 1
		  From     2      -      3     There is 4
		  From     2      -      2     There is 1

	*/
	// std::vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};

	/* Example 2 */
	/*
		Compact:
        ^
        |
        |
        |     |
        ||````|
        ||  | |
        ||| |||
        ||| |||
        ------------
         420325


		Wide: (There is 1 <Space> on the x axis)

        ^
        |
        |
        |           |
        | |`````````|
        | |     |   |
        | | |   | | |
        | | |   | | |
        ---------------------------------
          4 2 0 3 2 5

        ^
        |
        |
        |           |
        | |`1`3`7`8`|
        | | 2 4 | 9 |
        | | | 5 | | |
        | | | 6 | | |
        ---------------------------------
          4 2 0 3 2 5

		  Result: 9
		  Going from left to right: 
		  From bar height - bar height There is x squares of water
		  From     4      -      5     There is 9

	*/
	std::vector<int> height = {4, 2, 0, 3, 2, 5};

	std::cout << "\n\t===========================";
	std::cout << "\n\t=== TRAPPING RAIN WATER ===";
	std::cout << "\n\t===========================\n";

	/* Write Input */
	bool first = true;
	std::cout << "\n\tHeights: [";
	for (auto x: height)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n";

	/* Solution */
	// int total = sol_dp.trap(height);
	// int total = sol_stack.trap(height);
	int total = sol_two_pointers.trap(height);

	/* Write Output */
	std::cout << "\n\tTotal: " << total << "\n\n";


	return 0;
}
