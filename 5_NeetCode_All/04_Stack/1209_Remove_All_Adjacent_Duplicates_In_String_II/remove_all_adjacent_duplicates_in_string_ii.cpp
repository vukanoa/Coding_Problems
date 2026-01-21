#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    =================================================
    1209) Remove All Adjacent Duplicates in String II
    =================================================

    ============
    Description:
    ============

    You are given a string s and an integer k, a k duplicate removal consists
    of choosing k adjacent and equal letters from s and removing them, causing
    the left and the right side of the deleted substring to concatenate
    together.

    We repeatedly make k duplicate removals on s until we no longer can.

    Return the final string after all such duplicate removals have been made.
    It is guaranteed that the answer is unique.

    ===================================================
    FUNCTION: string removeDuplicates(string s, int k);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abcd", k = 2
    Output: "abcd"
    Explanation: There's nothing to delete.

    --- Example 2 ---
    Input: s = "deeedbbcccbdaa", k = 3
    Output: "aa"
    Explanation:
    First delete "eee" and "ccc", get "ddbbbdaa"
    Then delete "bbb", get "dddaa"
    Finally delete "ddd", get "aa"

    --- Example 3 ---
    Input: s = "pbbcggttciiippooaais", k = 2
    Output: "ps"


    *** Constraints ***
    1 <= s.length <= 10^5
    2 <= k <= 10^4
    s only contains lowercase English letters.

*/

/*
    ------------
    --- IDEA ---
    ------------

    This one is the most intuitive to me, however the "Solution_Stack_1" is
    a more optimized way of writing this Solution, so make sure you take a look
    at that one as well.

    Idea is pretty simple - We'll push pairs onto the stack {chr, i-th cons.}

    i-th cons. means "i-th consecutive". We are contuing how many consecutive
    letters are on top of the stack. Once i-th cons. reaches k-1 and current
    chr is the same letter, than we have to pop all those letters from the
    stack.

*******************************************************************************
********************************** SIMULATION *********************************
*******************************************************************************

                        Input: s = "deeedbbcccbdaa", k = 3

       Stack:
    -----------------------------------------------
    |
    -----------------------------------------------

------------------------------------------------------------------------------

    1. i = 0

        s = "deeedbbcccbdaa", k = 3
             i

           Stack:
        -----------------------------------------------
        | {d,1} |                                        // Added
        -----------------------------------------------

------------------------------------------------------------------------------

    2. i = 1

        s = "deeedbbcccbdaa", k = 3
              i

           Stack:
        -----------------------------------------------
        | {d,1} | {e,1} |                                // Added
        -----------------------------------------------

------------------------------------------------------------------------------

    3. i = 2

        s = "deeedbbcccbdaa", k = 3
               i

           Stack:
        -----------------------------------------------
        | {d,1} | {e,1} | {e,2} |                        // Added
        -----------------------------------------------

------------------------------------------------------------------------------

    4. i = 3

        s = "deeedbbcccbdaa", k = 3
                i

           Stack:
        -----------------------------------------------
        | {d,1} | {e,1} | {e,2} |                        // Pop
        -----------------------------------------------
        -----------------------------------------------
        | {d,1} | {e,1}                                  // Pop
        -----------------------------------------------
        -----------------------------------------------
        | {d,1} |
        -----------------------------------------------

------------------------------------------------------------------------------

    5. i = 4

        s = "deeedbbcccbdaa", k = 3
                 i

           Stack:
        -----------------------------------------------
        | {d,1} | {d,2} |                                // Added
        -----------------------------------------------

------------------------------------------------------------------------------

    6. i = 5

        s = "deeedbbcccbdaa", k = 3
                  i

           Stack:
        -----------------------------------------------
        | {d,1} | {d,2} | {b,1} |                        // Added
        -----------------------------------------------

------------------------------------------------------------------------------

    7. i = 6

        s = "deeedbbcccbdaa", k = 3
                   i

           Stack:
        -----------------------------------------------
        | {d,1} | {d,2} | {b,1} | {b,2} |                // Added
        -----------------------------------------------

-------------------------------------------------------------------------------

    8. i = 7

        s = "deeedbbcccbdaa", k = 3
                    i

           Stack:
        -----------------------------------------------
        | {d,1} | {d,2} | {b,1} | {b,2} | {c,1} |        // Added
        -----------------------------------------------

-------------------------------------------------------------------------------

    9. i = 8

        s = "deeedbbcccbdaa", k = 3
                     i

           Stack:
        -----------------------------------------------------------
        | {d,1} | {d,2} | {b,1} | {b,2} | {c,1} | {c,2} |            // Added
        -----------------------------------------------------------

-------------------------------------------------------------------------------

    10. i = 9

        s = "deeedbbcccbdaa", k = 3
                      i

           Stack:
        -----------------------------------------------------------
        | {d,1} | {d,2} | {b,1} | {b,2} | {c,1} | {c,2} |            // Pop
        -----------------------------------------------------------
        -----------------------------------------------------------
        | {d,1} | {d,2} | {b,1} | {b,2} | {c,1} |                    // Pop
        -----------------------------------------------------------
        -----------------------------------------------------------
        | {d,1} | {d,2} | {b,1} | {b,2} |
        -----------------------------------------------------------

-------------------------------------------------------------------------------

    11. i = 10

        s = "deeedbbcccbdaa", k = 3
                       i

           Stack:
        -----------------------------------------------------------
        | {d,1} | {d,2} | {b,1} | {b,2} |                            // Pop
        -----------------------------------------------------------
        -----------------------------------------------------------
        | {d,1} | {d,2} | {b,1} |                                    // Pop
        -----------------------------------------------------------
        -----------------------------------------------------------
        | {d,1} | {d,2} |
        -----------------------------------------------------------

-------------------------------------------------------------------------------

    12. i = 11

        s = "deeedbbcccbdaa", k = 3
                        i

           Stack:
        -----------------------------------------------------------
        | {d,1} | {d,2} |                                            // Pop
        -----------------------------------------------------------
        -----------------------------------------------------------
        | {d,1}                                                      // Pop
        -----------------------------------------------------------
        -----------------------------------------------------------
        |
        -----------------------------------------------------------

------------------------------------------------------------------------------

    13. i = 12

        s = "deeedbbcccbdaa", k = 3
                         i

           Stack:
        -----------------------------------------------
        | {a,1} |                                        // Added
        -----------------------------------------------

------------------------------------------------------------------------------

    14. i = 13

        s = "deeedbbcccbdaa", k = 3
                          i

           Stack:
        -----------------------------------------------
        | {a,1} | {a,2}                                  // Added
        -----------------------------------------------

------------------------------------------------------------------------------

    Now transform characters on the stack to a string and then REVERSE it.
    [Don't forget this step. In this example it doesn't matter, however in
     most it will matter, therefore you MUST reverse the string]

    Output: "aa"

*/

/* Time  Beats: 53.16% */
/* Space Beats: 15.37% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Stack_Messy {
public:
    std::string removeDuplicates(std::string s, int k)
    {
        std::stack<std::pair<char, int>> stack;

        for (char& chr : s)
        {
            int count = 1;

            if (stack.empty() || stack.top().first != chr)
                stack.push({chr, count});
            else
            {
                count += stack.top().second;

                if (count == k)
                {
                    for (int i = 0; i < k-1; i++)
                        stack.pop();
                }
                else
                    stack.push({chr, count});
            }
        }

        std::ostringstream out;
        while (!stack.empty())
        {
            out << stack.top().first;
            stack.pop();
        }
        std::string result = out.str();
        std::reverse(result.begin(), result.end());

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Almost equivalent to the above Solution, however it's implemented in a much
    smarter way.

    Here is the Simulation:

*******************************************************************************
********************************** SIMULATION *********************************
*******************************************************************************

                        Input: s = "deeedbbcccbdaa", k = 3

       Stack:
    -----------------------------------------------
    |
    -----------------------------------------------

------------------------------------------------------------------------------

    1. i = 0

        s = "deeedbbcccbdaa", k = 3
             i


           Stack:
        ------------------------
        | {d,1}                   // Added
        ------------------------

------------------------------------------------------------------------------

    2. i = 1

        s = "deeedbbcccbdaa", k = 3
              i


           Stack:
        ------------------------
        | {d,1} | {e,1}           // Added
        ------------------------

------------------------------------------------------------------------------

    3. i = 2

        s = "deeedbbcccbdaa", k = 3
               i


           Stack:
        ------------------------
        | {d,1} | {e,2}          // Increment top().second
        ------------------------

------------------------------------------------------------------------------

    4. i = 3

        s = "deeedbbcccbdaa", k = 3
                i


           Stack:
        ------------------------
        | {d,1} | {e,3}          // Increment top().second
        ------------------------


        Since top.second() == k, we pop from the stack.

           Stack:
        ------------------------
        | {d,1} | {e,3}           // Pop
        ------------------------
        ------------------------
        | {d,1} |
        ------------------------

------------------------------------------------------------------------------

    5. i = 4

        s = "deeedbbcccbdaa", k = 3
                 i


           Stack:
        ------------------------
        | {d,2} |                 // Added
        ------------------------

------------------------------------------------------------------------------

    6. i = 5

        s = "deeedbbcccbdaa", k = 3
                  i


           Stack:
        ------------------------
        | {d,2} | {b,1}           // Added
        ------------------------

------------------------------------------------------------------------------

    7. i = 6

        s = "deeedbbcccbdaa", k = 3
                   i


           Stack:
        ------------------------
        | {d,2} | {b,2}          // Increment top().second
        ------------------------

------------------------------------------------------------------------------

    8. i = 7

        s = "deeedbbcccbdaa", k = 3
                    i


           Stack:
        --------------------------
        | {d,2} | {b,2} | {c,1} |  // Added
        --------------------------

------------------------------------------------------------------------------

    8. i = 7

        s = "deeedbbcccbdaa", k = 3
                     i

           Stack:
        --------------------------
        | {d,2} | {b,2} | {c,2} |  // Increment top().second)
        --------------------------

------------------------------------------------------------------------------

    9. i = 8

        s = "deeedbbcccbdaa", k = 3
                      i

           Stack:
        --------------------------
        | {d,2} | {b,2} | {c,3} |  // Increment top().second
        --------------------------


        Since top.second() == k, we pop from the stack.

           Stack:
        --------------------------
        | {d,2} | {b,2} | {c,3} |  // Pop
        --------------------------

        --------------------------
        | {d,2} | {b,2} |
        --------------------------

------------------------------------------------------------------------------

    10. i = 9

        s = "deeedbbcccbdaa", k = 3
                       i

           Stack:
        --------------------------
        | {d,2} | {b,3} |          // Increment top().second
        --------------------------


        Since top.second() == k, we pop from the stack.

           Stack:
        --------------------------
        | {d,2} | {b,3}            // Pop
        --------------------------
        --------------------------
        | {d,2} |
        --------------------------

------------------------------------------------------------------------------

    11. i = 10

        s = "deeedbbcccbdaa", k = 3
                        i

           Stack:
        --------------------------
        | {d,3} |                  // Increment top().second
        --------------------------

        Since top.second() == k, we pop from the stack.

           Stack:
        --------------------------
        | {d,3} |                  // Pop
        --------------------------
        --------------------------
        |
        --------------------------

------------------------------------------------------------------------------

    12. i = 11

        s = "deeedbbcccbdaa", k = 3
                         i

           Stack:
        --------------------------
        | {a,1} |                  // Added
        --------------------------

------------------------------------------------------------------------------

    13. i = 12

        s = "deeedbbcccbdaa", k = 3
                          i

           Stack:
        --------------------------
        | {a,2} |                  // Increment top().second
        --------------------------

------------------------------------------------------------------------------

    At the end, again, you MUST construct a string and then you MUST(!!!!)
    Reverse it!

    Output: "aa"

*/

/* Time  Beats: 60.25% */
/* Space Beats: 65.66% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Stack_1 {
public:
    std::string removeDuplicates(std::string s, int k)
    {
        std::stack<std::pair<char, int>> stack;

        for (int i = 0; i < s.length(); i++)
        {
            if (stack.empty() || stack.top().first != s[i])
                stack.push(std::make_pair(s[i], 1));
            else
                stack.top().second++;

            if (stack.top().second == k)
                stack.pop();
        }

        std::ostringstream out;
        while (!stack.empty())
        {
            for (int i = 0; i < stack.top().second; i++)
                out << stack.top().first;

            stack.pop();
        }
        std::string str = out.str();
        std::reverse(str.begin(), str.end());

        return str;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 93.98% */
/* Space Beats: 52.78% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Stack_2 {
public:
    std::string removeDuplicates(std::string s, int k)
    {
        // So that we don't have to check if !stack.empty()
        std::vector<std::pair<int, char>> stack = {{0, '#'}};

        for (char& c: s)
        {
            if (stack.back().second != c)
                stack.push_back({1, c});
            else if (++stack.back().first == k)
                stack.pop_back();
        }

        std::string result;
        for (auto& pair : stack)
            result.append(pair.first, pair.second);

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 97.16% */
/* Space Beats: 39.08% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Two_Pointers {
public:
    std::string removeDuplicates(std::string s, int k)
    {
        std::vector<int> count(s.length());

        int i = 0;
        for (int j = 0; j < s.length(); j++, i++)
        {
            s[i] = s[j];
            count[i] = (i > 0 && s[i-1] == s[j]) ? count[i-1]+1 : 1;

            if (count[i] == k)
                i -= k;
        }

        return s.substr(0, i);
    }
};
