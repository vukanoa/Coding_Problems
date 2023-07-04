#include <iostream>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	251) Flatten a 2D Vector
	===========================

	============
	Description:
	============

	Design and implement an iterator to flatten a 2d vector. It should support
	the following operations: next and hasNext.

	Implement the Vector2D class:

	Vector2D(int[][] vec) initializes the object with the 2D vector vec.
	next() returns the next element from the 2D vector and moves the pointer
	one step forward. You may assume that all the calls to next are valid.
	hasNext() returns true if there are still some elements in the vector, and
	false otherwise.

	Follow up: As an added challenge, try to code it using only iterators in
	C++ or iterators in Java.

	===============================
	FUNCTION: 
	===============================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input
	["Vector2D", "next", "next", "next", "hasNext", "hasNext", "next", "hasNext"]
	[[[[1, 2], [3], [4]]], [], [], [], [], [], [], []]
	Output
	[null, 1, 2, 3, true, true, 4, false]

	Explanation
	Vector2D vector2D = new Vector2D([[1, 2], [3], [4]]);
	vector2D.next();    // return 1
	vector2D.next();    // return 2
	vector2D.next();    // return 3
	vector2D.hasNext(); // return True
	vector2D.hasNext(); // return True
	vector2D.next();    // return 4
	vector2D.hasNext(); // return False



	*** Constraints ***
	0 <= vec.length <= 200
	0 <= vec[i].length <= 500
	-500 <= vec[i][j] <= 500
	At most 105 calls will be made to next and hasNext

*/


/*
	------------
	--- IDEA ---
	------------

	Straightforward.
	
*/

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Vector2D {
public:
	Vector2D(vector<vector<int>>& vec)
	{
		for (const vector<int>& row : vec)
		{
			for (const int& x : row)
				this->vec.push_back(x);
		}
	}

	int next()
	{
		return vec[i++];
	}

	bool hasNext()
	{
		return i < vec.size();
	}

private:
	std::vector<int> vec;
	int i = 0;
};




/*
	------------
	--- IDEA ---
	------------

	Iterator.
	
*/

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Vector2D {
public:
	Vector2D(vector<vector<int>>& v)
	{
		i = v.begin();
		iEnd = v.end();
	}

	int next()
	{
		moveIterator();
		return (*i)[j++];
	}

	bool hasNext()
	{
		moveIterator();
		return i != iEnd;
	}

private:
	// (*i)[j] := current pointed value
	vector<vector<int>>::iterator i, iEnd;
	int j = 0;

	void moveIterator()
	{
		while (i != iEnd && j == (*i).size())
			++i, j = 0;
	}
};
