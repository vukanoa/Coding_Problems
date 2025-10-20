/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    385) Mini Parser
    ===========================

    ============
    Description:
    ============

    Given a string s represents the serialization of a nested list, implement a
    parser to deserialize it and return the deserialized NestedInteger.

    Each element is either an integer or a list whose elements may also be
    integers or other lists.

    ==============================================
    FUNCTION: NestedInteger deserialize(string s);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "324"
    Output: 324
    Explanation: You should return a NestedInteger object which contains a
                 single integer 324.

    --- Example 2 ---
    Input: s = "[123,[456,[789]]]"
    Output: [123,[456,[789]]]
    Explanation: Return a NestedInteger object containing a nested list with
    2 elements:
    1. An integer containing value 123.
    2. A nested list containing two elements:
        i.  An integer containing value 456.
        ii. A nested list with one element:
             a. An integer containing value 789

    *** Constraints ***
    1 <= s.length <= 5 * 10^4
    s consists of digits, square brackets "[]", negative sign '-', and commas
    ','.
    s is the serialization of valid NestedInteger.
    All the values in the input are in the range [-106, 106].

*/

#include <string>
#include <vector>
#include <sstream>
using namespace std;

// This is the interface that allows for creating nested lists.
// You should not implement it, or speculate about its implementation
class NestedInteger {
  public:
    // Constructor initializes an empty nested list.
    NestedInteger();

    // Constructor initializes a single integer.
    NestedInteger(int value);

    // Return true if this NestedInteger holds a single integer, rather than a nested list.
    bool isInteger() const;

    // Return the single integer that this NestedInteger holds, if it holds a single integer
    // The result is undefined if this NestedInteger holds a nested list
    int getInteger() const;

    // Set this NestedInteger to hold a single integer.
    void setInteger(int value);

    // Set this NestedInteger to hold a nested list and adds a nested integer to it.
    void add(const NestedInteger &ni);

    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
    const vector<NestedInteger> &getList() const;
};

class Solution {
public:
    NestedInteger deserialize(string s)
    {
        istringstream in(s);
        return deserialize(in);
    }

private:
    NestedInteger deserialize(istringstream& in)
    {
        if (in.peek() != '[')
        {
            int number;
            in >> number;

            return NestedInteger(number);
        }

        char chr;
        in >> chr; //[

        NestedInteger list;

        while (in.peek() != ']')
        {
            list.add(deserialize(in));

            if (in.peek() == ',')
                in >> chr;
        }

        in >> chr; //]
        return list;
    }
};
