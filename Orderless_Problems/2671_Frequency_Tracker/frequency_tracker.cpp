/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    2671) Frequency Tracker
    ===========================

    ============
    Description:
    ============


    Design a data structure that keeps track of the values in it and answers
    some queries regarding their frequencies.

    Implement the FrequencyTracker class.

        + FrequencyTracker(): Initializes the FrequencyTracker object with an
          empty array initially.

        + void add(int number): Adds number to the data structure.

        + void deleteOne(int number): Deletes one occurrence of number from the
          data structure. The data structure may not contain number, and in
          this case nothing is deleted.

        + bool hasFrequency(int frequency): Returns true if there is a number
          in the data structure that occurs frequency number of times,
          otherwise, it returns false.


    ===============================
    CLASS:
    class FrequencyTracker {
    public:
        FrequencyTracker()
        {
            
        }
        
        void add(int number)
        {

        }
        
        void deleteOne(int number)
        {

        }
        
        bool hasFrequency(int frequency)
        {

        }
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input
    ["FrequencyTracker", "add", "add", "hasFrequency"]
    [[], [3], [3], [2]]
    Output
    [null, null, null, true]

    Explanation
    FrequencyTracker frequencyTracker = new FrequencyTracker();
    frequencyTracker.add(3); // The data structure now contains [3]
    frequencyTracker.add(3); // The data structure now contains [3, 3]
    frequencyTracker.hasFrequency(2); // Returns true, because 3 occurs twice


    --- Example 2 ---
    Input
    ["FrequencyTracker", "add", "deleteOne", "hasFrequency"]
    [[], [1], [1], [1]]
    Output
    [null, null, null, false]

    Explanation
    FrequencyTracker frequencyTracker = new FrequencyTracker();
    frequencyTracker.add(1); // The data structure now contains [1]
    frequencyTracker.deleteOne(1); // The data structure becomes empty []
    frequencyTracker.hasFrequency(1); // Returns false, because the data
    structure is empty


    --- Example 3 ---
    Input
    ["FrequencyTracker", "hasFrequency", "add", "hasFrequency"]
    [[], [2], [3], [1]]
    Output
    [null, false, null, true]

    Explanation
    FrequencyTracker frequencyTracker = new FrequencyTracker();
    frequencyTracker.hasFrequency(2); // Returns false, because the data
    structure is empty
    frequencyTracker.add(3); // The data structure now contains [3]
    frequencyTracker.hasFrequency(1); // Returns true, because 3 occurs once


    *** Constraints ***
    1 <= number <= 10^5
    1 <= frequency <= 10^5
    At most, 2 * 10^5 calls will be made to add, deleteOne, and hasFrequency in
    total.

*/

#include <unordered_map>
#include <unordered_set>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 42.68% */
/* Space Beats: 26.83% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(N) */
class FrequencyTracker {
private:
    unordered_map<int, int> num_to_freq;
    unordered_map<int, unordered_set<int>> freq_to_num;

public:
    FrequencyTracker()
    {
        
    }
    
    void add(int number)
    {
        if (num_to_freq.find(number) == num_to_freq.end())
        {
            num_to_freq[number] = 1;
            freq_to_num[1].insert(number);
        }
        else
        {
            int curr_freq = num_to_freq[number];

            // Delete it from curr_freq
            freq_to_num[curr_freq].erase(number);

            // Erase this frequency if this was the only number with that freq
            if (freq_to_num[curr_freq].empty())
                freq_to_num.erase(curr_freq);

            freq_to_num[curr_freq + 1].insert(number);
            num_to_freq[number] = curr_freq + 1;
        }
    }
    
    void deleteOne(int number)
    {
        if (num_to_freq.find(number) == num_to_freq.end())
            return;

        int curr_freq = num_to_freq[number];

        // Delete it from curr_freq
        freq_to_num[curr_freq].erase(number);

        // Erase this frequency if this was the only number with that freq
        if (freq_to_num[curr_freq].empty())
            freq_to_num.erase(curr_freq);

        if (curr_freq - 1 > 0)
        {
            freq_to_num[curr_freq - 1].insert(number);
            num_to_freq[number] = curr_freq - 1;
        }
        else
            num_to_freq.erase(number);
    }
    
    bool hasFrequency(int frequency)
    {
        return freq_to_num.find(frequency) != freq_to_num.end();
    }
};
