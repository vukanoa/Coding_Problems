#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    1898) Maximum Number Of Removable Characters
    ============================================

    ============
    Description:
    ============

    You are given two strings s and p where p is a subsequence of s. You are
    also given a distinct 0-indexed integer array removable containing a subset
    of indices of s (s is also 0-indexed).

    You want to choose an integer k (0 <= k <= removable.length) such that,
    after removing k characters from s using the first k indices in removable,
    p is still a subsequence of s. More formally, you will mark the character
    at s[removable[i]] for each 0 <= i < k, then remove all marked characters
    and check if p is still a subsequence.

    Return the maximum k you can choose such that p is still a subsequence of s
    after the removals.

    A subsequence of a string is a new string generated from the original
    string with some characters (can be none) deleted without changing the
    relative order of the remaining characters.

    ==========================================================================
    FUNCTION: int maximumRemovals(string s, string p, vector<int>& removable);
    ==========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abcacb", p = "ab", removable = [3,1,0]
    Output: 2
    Explanation: After removing the characters at indices 3 and 1, "abcacb"
                 becomes "accb".  "ab" is a subsequence of "accb".  If we
                 remove the characters at indices 3, 1, and 0, "abcacb" becomes
                 "ccb", and "ab" is no longer a subsequence.  Hence, the
                 maximum k is 2.


    --- Example 2 ---
    Input: s = "abcbddddd", p = "abcd", removable = [3,2,1,4,5,6]
    Output: 1
    Explanation: After removing the character at index 3, "abcbddddd" becomes
                 "abcddddd".  "abcd" is a subsequence of "abcddddd".


    --- Example 3 ---
    Input: s = "abcab", p = "abc", removable = [0,1,2,3,4]
    Output: 0
    Explanation: If you remove the first index in the array removable, "abc" is
                 no longer a subsequence.


    *** Constraints ***
    1 <= p.length <= s.length <= 10^5
    0 <= removable.length < s.length
    0 <= removable[i] < s.length
    p is a subsequence of s.
    s and p both consist of lowercase English letters.
    The elements in removable are distinct.

*/

/*
    ------------
    --- IDEA ---
    ------------

    There are three Implementations down below out of which
    "Solution_Modified_String_S" is a lot faster since we do not use a Hash Set
    as in the first two Solutions, but an additional string that represents a
    modified stirng s.

*/

/*
    ------------
    --- IDEA ---
    ------------

    There are two Implementations down below out of which the bottom one is a
    lot faster since we do not use a Hash Set as in the first two Solutions,
    but an additional string that represents a modified stirng s.

    Since we know that the desired 'k' is in the range: [0, removable.size()],
    we can notice that we don't have to try every 'k' value and check if p is
    still a subsequence of s and then take the biggest 'k' values where that is
    true.

    Since there is a range, we can simply use a Binary Search within that range
    and check only those 'k' values.
    If we find out that some 'k' value(which will be a 'mid' in Binary Search)
    is indeed a subsequence, then we can move our "left" pointer to mid+1(i.e.
    k + 1) and check the next range.

    In O(log n) we'll have our result.
    (Of course, in every iteration of our outer O(log n) loop, we'll have O(n)
     nested loop that cheks if tmp_s(modified s) string is still a subsequence
     of p, which, in total, makes this Solution a O(n * logn))

*/

/* Time  Beats: 19.33% */
/* Space Beats: 11.97% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution_Hash_Set {
public:
    int maximumRemovals(std::string s, std::string p, std::vector<int>& removable)
    {
        if (s.length() < p.length())
            return 0;

        int result = 0;

        int left  = 0;
        int right = removable.size() - 1;

        // O(logn)
        while (left <= right)
        {
            int mid_k = left + (right - left) / 2;

            // O(n)
            std::unordered_set<int> uset;
            for (int i = 0; i <= mid_k; i++)
                uset.insert(removable[i]);

            // O(n)
            std::string tmp_s;
            for (int i = 0; i < s.length(); i++)
            {
                if (uset.count(i))
                    continue;

                tmp_s += s[i];
            }

            // O(n)
            if (is_subsequence(tmp_s, p))
            {
                left = mid_k + 1;
                result = std::max(result, mid_k + 1);
            }
            else
                right = mid_k - 1;
        }

        return result;
    }

private:
    bool is_subsequence(std::string& tmp_s, std::string& p)
    {
        int j = -1;
        for (int i = 0; i < p.length(); i++)
        {
            while (++j < tmp_s.length())
            {
                if (tmp_s[j] == p[i])
                    break;
            }

            if (j == tmp_s.length())
                return false;
        }

        return true;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is an optimzed version of the above Solution. The optimization comes
    from the facts that we don't have to make a HashSet and then construct
    the new string, we can just construct the modified_s by replacing '#' over
    the characters which should be "removed" based by first 'k'(mid) values.

*/

/* Time  Beats: 87.30% */
/* Space Beats: 71.75% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution_Modified_String_S {
public:
    int maximumRemovals(std::string s, std::string p, std::vector<int>& removable)
    {
        int result = -1;

        int left  = 0;
        int right = removable.size() -1;

        while(left <= right)
        {
            int mid = left + (right - left) / 2;

            std::string modified_s = s;

            for(int x = 0; x < mid+1 ;x++)
                modified_s[removable[x]] = '#';

            if(is_subsequence(modified_s, p))
            {
                result = std::max(result,mid);
                left  = mid + 1;
            }
            else
                right = mid - 1;
        }

        return result + 1;
    }

private:
    bool is_subsequence(std::string& modified_s, std::string& p)
    {
        int i = 0;
        int j = 0;

        while (i < modified_s.length() && j < p.length())
        {
            if (modified_s[i] == p[j])
                j++;

            i++;
        }

        return j == p.length();
    }
};
