/*
    ============
    === EASY ===
    ============

    ===============================
    2932) Maximum Strong Pair XOR I
    ===============================

    ============
    Description:
    ============

    You are given a 0-indexed integer array nums. A pair of integers x and y is
    called a strong pair if it satisfies the condition:

        |x - y| <= min(x, y)

    You need to select two integers from nums such that they form a strong pair
    and their bitwise XOR is the maximum among all strong pairs in the array.

    Return the maximum XOR value out of all possible strong pairs in the array
    nums.

    =====
    Note: Note that you can pick the same integer twice to form a pair.
    =====

    ======================================================
    FUNCTION: int maximumStrongPairXor(vector<int>& nums);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,4,5]
    Output: 7
    Explanation: There are 11 strong pairs in the array nums: (1, 1), (1, 2),
    (2, 2), (2, 3), (2, 4), (3, 3), (3, 4), (3, 5), (4, 4), (4, 5) and (5, 5).
    The maximum XOR possible from these pairs is 3 XOR 4 = 7.

    --- Example 2 ---
    Input: nums = [10,100]
    Output: 0
    Explanation: There are 2 strong pairs in the array nums: (10, 10) and (100, 100).
    The maximum XOR possible from these pairs is 10 XOR 10 = 0 since the pair
    (100, 100) also gives 100 XOR 100 = 0.

    --- Example 3 ---
    Input: nums = [5,6,25,30]
    Output: 7
    Explanation: There are 6 strong pairs in the array nums: (5, 5), (5, 6),
    (6, 6), (25, 25), (25, 30) and (30, 30).
    The maximum XOR possible from these pairs is 25 XOR 30 = 7 since the only
    other non-zero XOR value is 5 XOR 6 = 3.

    *** Constraints ***
    1 <= nums.length <= 50
    1 <= nums[i] <= 100

*/

#include <algorithm>
#include <cstdlib>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Brute-Force.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  38.39% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(1)   */
class Solution {
public:
    int maximumStrongPairXor(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        for (int i = 0; i < N-1; i++)
        {
            for (int j = i+1; j < N; j++)
            {
                if (abs(nums[i] - nums[j]) <= min(nums[i], nums[j]))
                {
                    result = max(result, nums[i] ^ nums[j]);
                }
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 43.33% */
/* Space Beats: 14.00% */

/* Time  Complexity: O(32 * N * logN) */
/* Space Complexity: O(32 * N)        */
class TrieNode {
private:
    TrieNode* child_nodes[2];

public:
    bool contains_key(int bit)
    {
        return child_nodes[bit] != nullptr;
    }

    TrieNode* get_next_node(int bit)
    {
        return child_nodes[bit];
    }

    void create_link(int bit, TrieNode* node)
    {
        child_nodes[bit] = node;
    }
};

class BinaryTrie {
private:
    TrieNode* root_node = new TrieNode();

public:
    void insert_all_binary_numbers(const vector<int>& input_numbers)
    {
        for (int idx = 0; idx < input_numbers.size(); idx++)
        {
            TrieNode* curr_node = root_node;

            for (int bit_position = 31; bit_position >= 0; bit_position--)
            {
                int bit_value = (input_numbers[idx] >> bit_position) & 1;

                if ( ! curr_node->contains_key(bit_value))
                    curr_node->create_link(bit_value, new TrieNode());

                curr_node = curr_node->get_next_node(bit_value);
            }
        }
    }

    int get_maximum_xor_within_strong_pairs(const vector<int>& input_numbers)
    {
        int maximum_xor_value = 0;

        for (int curr_idx = 0; curr_idx < input_numbers.size(); curr_idx++)
        {
            TrieNode* curr_node = root_node;

            auto upper_iterator = upper_bound(input_numbers.begin() + curr_idx + 1, input_numbers.end(), 2 * input_numbers[curr_idx]);
            auto lower_iterator = lower_bound(input_numbers.begin(), input_numbers.end(), (input_numbers[curr_idx] + 1) / 2);

            int maximum_strong_number = (upper_iterator == input_numbers.end() ? input_numbers.back() : *(upper_iterator - 1));
            int minimum_strong_number = *lower_iterator;

            int current_xor_value = 0;
            int possible_strong_number = 0;

            for (int bit_position = 31; bit_position >= 0; bit_position--)
            {
                int bit_value = (input_numbers[curr_idx] >> bit_position) & 1;

                int toggled_bit = !bit_value;
                int candidate_value = possible_strong_number + (toggled_bit << bit_position);

                if (curr_node->contains_key(toggled_bit) &&
                    candidate_value <= maximum_strong_number &&
                    candidate_value >= minimum_strong_number)
                {
                    curr_node = curr_node->get_next_node(toggled_bit);
                    current_xor_value += (1 << bit_position);
                    possible_strong_number = candidate_value;
                }
                else
                {
                    if (curr_node->contains_key(bit_value))
                    {
                        curr_node = curr_node->get_next_node(bit_value);
                        possible_strong_number += (bit_value << bit_position);
                    }
                    else
                    {
                        current_xor_value = 0;
                        break;
                    }
                }
            }

            maximum_xor_value = max(maximum_xor_value, current_xor_value);
        }

        return maximum_xor_value;
    }
};

class Solution_2 {
public:
    int maximumStrongPairXor(vector<int>& input_numbers)
    {
        /* Sort */
        sort(input_numbers.begin(), input_numbers.end());

        BinaryTrie binary_trie;
        binary_trie.insert_all_binary_numbers(input_numbers);

        return binary_trie.get_maximum_xor_within_strong_pairs(input_numbers);
    }
};
