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

/* Time  Beats: 60.25% */
/* Space Beats: 65.66% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
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




/* Time  Beats: 91.00% */
/* Space Beats: 26.69% */

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
