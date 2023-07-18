#include <iostream>
#include <vector>

/*
	==============
	=== MEDIUM ===
	==============

	=================================
	341) Flatten Nested List Iterator
	=================================

	============
	Description:
	============

	You are given a nested list of integers nestedList. Each element is either
	an integer or a list whose elements may also be integers or other lists.
	Implement an iterator to flatten it.

	Implement the NestedIterator class:

		- NestedIterator(List<NestedInteger> nestedList) Initializes the
		  iterator with the nested list nestedList.

		- int next() Returns the next integer in the nested list.

		- boolean hasNext() Returns true if there are still some integers in
		  the nested list and false otherwise.

	Your code will be tested with the following pseudocode:

	```
		initialize iterator with nestedList
		res = []
		while iterator.hasNext()
			append iterator.next() to the end of res
		return res
	```

	If res matches the expected flattened list, then your code will be judged
	as correct.

	===============================
	class NestedIterator {
	public:
		
		NestedIterator(vector<NestedInteger> &nestedList) 
		{
			
		}
		
		int next() 
		{

		}
		
		bool hasNext() 
		{

		}
	};
	===============================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: nestedList = [[1,1],2,[1,1]]
	Output: [1,1,2,1,1]
	Explanation: By calling next repeatedly until hasNext returns false, the
	order of elements returned by next should be: [1,1,2,1,1].

	--- Example 2 ---
	Input: nestedList = [1,[4,[6]]]
	Output: [1,4,6]
	Explanation: By calling next repeatedly until hasNext returns false, the
	order of elements returned by next should be: [1,4,6]

	*** Constraints ***
    1 <= nestedList.length <= 500
    The values of the integers in the nested list is in the range [-10^6, 10^6]

*/



/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */


/*
	------------
	--- IDEA ---
	------------

	Once we visualize it, it becomes obvious:

	Example: nestedList = [[1, [3, 4], [5, 6]], 2, [1, 1]]

	[    List    ,    2    ,    List    ]
	      |                      |
	      1                      1
	      |                      |
	     List - 3, 4             1
	      |
	     List - 5, 6
	


	It becomes obvious that we need to use recursion.
	Recursively push in vector "res" from which we take elements with "next()"
	function.

	"hasNext()" only checks if index is less than res.size() and returns the
	boolean value.

*/

/* Time  Beats: 98.50% */
/* Space Beats: 33.27% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class NestedIterator {
public:
    
    vector<int> res; // Store final result
    int index = 0;     // Store index
    
    void flattenList(std::vector<NestedInteger> &nestedList)
    {
        for(auto& x : nestedList)
        {
            // If x is int then push it into the vector res
            if(x.isInteger())
            {
                res.push_back(x.getInteger());
            }
            // If x is list then call the flattenList function again
            else
            {
                flattenList(x.getList());
            }
        }
    }
    
    NestedIterator(std::vector<NestedInteger> &nestedList) 
    {
        // Call the flattenList function to make the 1D array of the entire
		// nestedList
        flattenList(nestedList);
    }
    
    int next() 
    {
        // Return the value at index index
        return res[index++];   
    }
    
    bool hasNext() 
    {
        // Check whether next elements is available or not by checking if index
		// value is less than res size
        return index < res.size();   
    }
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */
