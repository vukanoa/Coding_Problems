#include <iostream>
#include <vector>
#include <unordered_set>

/*
    ==============
    === MEDIUM ===
    ==============

    ===============================
    1980) Find Unique Binary String
    ===============================

    ============
    Description:
    ============

    Given an array of strings nums containing n unique binary strings each of
    length n, return a binary string of length n that does not appear in nums.
    If there are multiple answers, you may return any of them.

    =================================================================
    FUNCTION: string findDifferentBinaryString(vector<string>& nums);
    =================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = ["01","10"]
    Output: "11"
    Explanation: "11" does not appear in nums. "00" would also be correct.


    --- Example 2 ---
    Input: nums = ["00","01"]
    Output: "11"
    Explanation: "11" does not appear in nums. "10" would also be correct.


    --- Example 3 ---
    Input: nums = ["111","011","001"]
    Output: "101"
    Explanation: "101" does not appear in nums. "000", "010", "100", and "110"
    would also be correct.


    *** Constraints ***
    n == nums.length
    1 <= n <= 16
    nums[i].length == n
    nums[i] is either '0' or '1'.
    All the strings of nums are unique.

*/

/*
    ------------
    --- IDEA ---
    ------------

    Convert all the strings in "nums" to integers and insert it into the Set.
    Iterate from 0 to n-1 and if we find an integer from 0 to n-1 that is
    absent, we return that immediately.

    If every number from 0 to n-1 is present in the Set, then return the binary
    representation of number 'n' as a result.

*/

/* Time  Beats: 68.43% */
/* Space Beats: 61.42% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n) */
class Solution_Intuitive_Naive {
public:
    std::string findDifferentBinaryString(std::vector<std::string>& nums)
    {
        int n = nums.size();

        if (n == 1)
            return nums[0] == "0" ? "1" : "0";

        std::unordered_set<int> integers;
        for (std::string& str : nums)
            integers.insert(convertFromBinStrToInt(str));


        for (int i = 0; i < n; i++)
        {
            if (integers.find(i) == integers.end())
                return convertFromIntToBinStr(i, n);
        }

        return convertFromIntToBinStr(n, n);
    }

private:
    int convertFromBinStrToInt(std::string &str)
    {
        std::reverse(str.begin(), str.end());

        int num = 0;
        for (int i = 0; i < str.length(); i++)
            num += str[i] == '1' ? (1 << i) : 0;

        return num;
    }

    std::string convertFromIntToBinStr(int num, int n)
    {
        std::ostringstream out;

        while (n--)
        {
            if (num & 1)
                out << "1";
            else
                out << "0";

            num >>= 1;
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

    Intuition

    Cantor's diagonal argument is a mathematical proof technique used to show
    that the set of real numbers is "uncountably infinite", whereas natural
    numbers are "countably infinite".

    It's often applied in discussions related to the limitations of countable
    sets. The intuition behind Cantor's diagonal argument is crucial for
    understanding why certain sets are uncountable.

    In the context of the provided solution:

        Binary Strings as Countable Sets: If the set of binary strings
        represented by nums were countable, one might attempt to enumerate
        them.  Cantor's diagonal argument suggests that even in such an
        enumeration, we can always construct a binary string that was not in
        the original enumeration.

        Construction of a Different Binary String: The provided code aims to
        find a binary string that differs from each binary string in nums. The
        subtraction of each bit from 1 in the solution corresponds to the
        flipping of each bit (changing 0 to 1 and vice-versa).

        Assumption of Countability: The assumption that there is a countable
        list of binary strings leads to a contradiction, as the constructed
        (new) binary string differs from each enumerated string.

        Uncountability Implication: The inability to enumerate all binary
        strings suggests that the set of binary strings is uncountably
        infinite.

    In summary, the solution leverages the intuition from Cantor's diagonal
    argument to construct a binary string that is not in the assumed countable
    list, demonstrating that the set of binary strings is not countable.
    Approach

        Assumption: Suppose we have a countable list of binary strings,
        represented by the input list nums.

        Cantor's Diagonal Argument Intuition: Cantor's diagonal argument
        suggests that even in a countable list of binary strings, we can
        construct a binary string that is not in the list.

        Construction of a Different Binary String: Initialize an empty string
        result to store the result. Iterate through each binary string in nums.
        For each binary string, consider the bit at the current index. Flip the
        bit by subtracting it from 1 and append the result to the result
        string. Move to the next index and repeat the process.

        Result: The constructed result string represents a binary string that
        differs from each binary string in the assumed countable list, however
        that contradicts that the given list "nums" of binary string is
        countable.

        The inability to enumerate all binary strings suggests that the set of
        binary string is uncountably infinite.

        Return: Return the constructed result string, which is a binary string
        not present in the assumed countable list.

*/

/* Time  Beats:   100% */
/* Space Beats: 97.48% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Cantors_Diagonal {
public:
    std::string findDifferentBinaryString(std::vector<std::string>& nums)
    {
        std::string result;

        int index = 0;
        for(auto& binary_str : nums)
        {
            result += std::to_string('1' - binary_str[index]);
            index++;
        }

        return result;
    }
};
