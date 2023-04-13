#include <iostream>
#include <vector>


/*
	==============
	=== MEDIUM ===
	==============

	===========================
	54) Spiral Matrix
	===========================

	============
	Description:
	============

	Given an m x n matrix, return all elements of the matrix in spiral order.

	===============================================================
	FUNCTION: vector<int> spiralOrder(vector<vector<int>>& matrix);
	===============================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  matrix = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
	Output: [1, 2, 3, 6, 9, 8, 7, 4, 5]

	--- Example 2 ---
	Input:  matrix = [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12]]
	Output: [1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7]

	*** Constraints ***
	m == matrix.length
	n == matrix[i].length
	1 <= m, n <= 10
	-100 <= matrix[i][j] <= 100

*/


/*
	------------
	--- IDEA ---
	------------

	Consider "Example 3"(my example):
		 1  2  3  4  5
		 6  7  8  9 10
		11 12 13 14 15
		16 17 18 19 20

	We can notice that we are always traversing in the same order:
		1. From left to right
		2. From up downwards
		3. From right to left
		4. From down upwards

	We have one array with starting points in each's direction.
	We only memorize the starting index of a "part" that is moving.

	For firection 1 and 3, that is horizontal moving, thus we only add/subtract
	column:
		matrix [fixed][moving(++ | --)];

	On the other hand, directions 2 and 4 add/subtract rows;
		matrix [moving(++ | --)][fixed]


	Now we have to notice a pattern on each direction considering their
	"next iteration".
	What do I mean?

	In the above example, the "first iteration" for direction "from left to
	right" is:
		1 2 3 4 5

	The second one for the same direction("from left to right") is:
		7 8 9

	If we were to consider an example with more rows and more columns it would
	have been even easier to spot a pattern.

	Anyhow, the pattern is that, for now, for direction "from left to right"
	starting position(of index that is moving, that is a column) increments,
	while the limit(end), or the position until we iterate, decreases.

	Previously we have iterated while "i" was less than N and now we want
	to decrease that limit so that in the next iteration it stops BEFORE
	N - 1.

	Similar patterns can be detected for the remaining three directions.
	Each one differs in the combination of these 2 aspects:
		1. "next iteration" position starts incremented/decremented from the
		   current starting position of its moving part.

		2. "next iteration" limit(end) needs to be incremented/decremented from
		   the current limit(end) of its moving part.

	Of course, we have to take care in which of our 4 positions we are since
	for the 1 & 2 we increment columns or rows positions, respectively, while
	for the 3 & 4 we decrement columns or rows positions, respectively.

	Also we can't forget that 1 & 3 are moving horizontally, while 2 & 4 are
	moving vertically.

*/


/* Time  Beats: 100% */
/* Space Beats: 34.40% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n * m) */
class Solution{
public:
	std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix)
	{
		int m = matrix.size();
		int n = matrix[0].size();

		// Base case
		if (matrix.size() == 1)
			return {matrix[0]};

		/*
			0 - to the right
			1 - downwards
			2 - to the left
			3 - upwards
		*/
		unsigned direction = 0;
		std::vector<int> starts = {0,  1, n - 2, m - 2};
		std::vector<int> ends   = {n,  m,   0  ,   1  };

		std::vector<int> order;
		int traversed = 0;
		int i;

		while (traversed < matrix.size() * matrix[0].size())
		{
			switch (direction)
			{
				case 0:
					i = starts[direction];
					while (i < ends[direction])
					{
						order.push_back(matrix[starts[direction]][i++]);
						traversed++;
					}

					starts[direction]++;
					ends[direction]--;
					break;

				case 1:
					i = starts[direction];
					while (i < ends[direction])
					{
						order.push_back(matrix[i++][ends[0]]);
						traversed++;
					}

					starts[direction]++;
					ends[direction]--;
					break;

				case 2:
					i = starts[direction];
					while (i >= ends[direction])
					{
						order.push_back(matrix[ends[1]][i--]);
						traversed++;
					}

					starts[direction]--;
					ends[direction]++;
					break;

				case 3:
					i = starts[direction];
					while (i >= ends[direction])
					{
						order.push_back(matrix[i--][ends[2] - 1]);
						traversed++;
					}

					starts[direction]--;
					ends[direction]++;
					break;
			}

			direction = (direction + 1) % 4;
		}

		return order;
	}
};




/*
	------------
	--- IDEA ---
	------------

	When traversing the matrix in the spiral order, at any time we follow one
	out of the following four directions: Right, Down, Left, Up.

	Suppose we are working ona a 5x3 matrix as such:
	 '0'  1  2  3  4  5
	      6  7  8  9 10
	     11 12 13 14 15

	Imagine a cursor stars off at (0, -1), i.e. the position at '0', then we
	can achieve the spiral order by doing the following:
		1. Go right 5 times
		2. Go down  2 times
		3. Go left  4 times
		4. Go Up    1 times
		5. Go right 3 times
		6. Go down  0 times -> quit

	Notice that the directions we choose always follow the order:
		Right -> Down -> Left -> Up

	(#)
	And for horizontal movements, the number of shifts follows: {5, 4, 3}, and
	vertical movements follows {2, 1, 0}.

	Thus, we can make use of a direction matrix that records the offest for all
	directions, then an array of two elements that stores the number of shifts
	for horizontal and vertical movements, respectively. This way, we really
	just need one for loop instead of four.

	Another good thing about this implementation is that: If later we decided
	to do spiral traversal on a different direction(e.g. Counterclockwise),
	then we only need to change the Direction matrix; the main loop does not
	need to be touched.


	In other words:
	"While loop" statement checks if there are any more steps left in one of
	the two possible directions - either horizontally or vertically.

	There are 4 directions possible:
		0 - Right
		1 - Down
		2 - Left
		3 - Up

	"direction_steps" denotes the step in each dimension, that is first and
	second, that is row and column, respctively.

	direction_steps = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

	Right - "row" is fixed  , "column" increments
	Down  - "row" increments, "column" is fixed
	Left  - "row" is fixed  , "column" decrements
	Up    - "row" decrements, "column" is fixed

	When we finish processing each element in the current direction(out of 4)
	we decrement the number of elements needed to be processed in
	horizontal/vertical direction, as we have mentioned already. (#)

	And we change direction. If we increment the last direction(4th one)
	we will go out of bounds, so we have to mod with the number of dirctions,
	which is 4.

*/


/* Time  Beats: 100% */
/* Space Beats: 74.41% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n * m) */
class Solution_improved{
public:
	std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix)
	{
		/*
			m = rows;
			n = columns;
		*/
		int m = matrix.size();
		int n = matrix[0].size();

		// Base case
		if (matrix.size() == 1)
			return {matrix[0]};

		std::vector<std::vector<int>> direction_steps = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
		std::vector<int> order;

		std::vector<int> num_of_steps = {n, m - 1};

		int direction = 0; // 0 & 2 - horizontal, 1 & 3 - vertical
		int row = 0;
		int col = -1;

		while (num_of_steps[direction % 2])
		{
			for (int i = 0; i < num_of_steps[direction % 2]; i++)
			{
				row += direction_steps[direction][0];
				col += direction_steps[direction][1];

				order.push_back(matrix[row][col]);
			}

			num_of_steps[direction % 2]--;
			direction = (direction + 1) % 4;
		}

		return order;
	}
};


void
print_matrix(std::vector<std::vector<int>>& matrix)
{
	printf("\tMatrix:\n\t\t");
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[0].size(); j++)
			printf("%2d ", matrix[i][j]);

		printf("\n\t\t");
	}
	printf("\n");
}


int
main()
{
	// Solution sol;
	Solution_improved sol_improved;

	/* Example 1 */
	std::vector<std::vector<int>> matrix = {
	                                        { 1,  2,  3},
	                                        { 4,  5,  6},
	                                        { 7,  8,  9},
	                                       };


	/* Example 2 */
	// std::vector<std::vector<int>> matrix = {
	//                                         { 1,  2,  3, 4},
	//                                         { 5,  6,  7, 8},
	//                                         { 9, 10, 11, 12},
	//                                        };


	/* Example 3 */
	// std::vector<std::vector<int>> matrix = {
	//                                         { 1,  2,  3,  4,  5},
	//                                         { 6,  7,  8,  9, 10},
	//                                         {11, 12, 13, 14, 15},
	//                                         {16, 17, 18, 19, 20}
	//                                        };


	std::cout << "\n\t=====================";
	std::cout << "\n\t=== SPIRAL MATRIX ===";
	std::cout << "\n\t=====================\n\n";


	/* Write Input */
	print_matrix(matrix);


	/* Solution */
	// std::vector<int> order = sol.spiralOrder(matrix);
	std::vector<int> order = sol_improved.spiralOrder(matrix);


	/* Write Output */
	std::cout << "\n\tSpiral order:\n\t\t ";
	for(const auto& x : order)
		std::cout << x << " ";

	std::cout << "\n\n\n";

	return 0;
}
