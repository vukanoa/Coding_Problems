/*
    ==============
    === MEDIUM ===
    ==============

    =================================
    3709) Design Exams Scores Tracker
    =================================

    ============
    Description:
    ============


    Alice frequently takes exams and wants to track her scores and calculate
    the total scores over specific time periods.

    Implement the ExamTracker class:

        + ExamTracker(): Initializes the ExamTracker object.

        + void record(int time, int score): Alice takes a new exam at time time
        and achieves the score score.

        + long long totalScore(int startTime, int endTime): Returns an integer
          that represents the total score of all exams taken by Alice between
          startTime and endTime (inclusive). If there are no recorded exams
          taken by Alice within the specified time interval, return 0.

    It is guaranteed that the function calls are made in chronological order.
    That is,

        Calls to record() will be made with strictly increasing time.

        Alice will never ask for total scores that require information from the
        future. That is, if the latest record() is called with time = t, then
        totalScore() will always be called with startTime <= endTime <= t.

    ===============================
    FUNCTION:  
    class ExamTracker {
    public:
        ExamTracker() {
            
        }
        
        void record(int time, int score) {
            
        }
        
        long long totalScore(int startTime, int endTime) {
            
        }
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:
    ["ExamTracker", "record", "totalScore", "record", "totalScore", "totalScore", "totalScore", "totalScore"]
    [[], [1, 98], [1, 1], [5, 99], [1, 3], [1, 5], [3, 4], [2, 5]]

    Output:
    [null, null, 98, null, 98, 197, 0, 99]

    Explanation
    ExamTracker examTracker = new ExamTracker();
    examTracker.record(1, 98); // Alice takes a new exam at time 1, scoring 98.
    examTracker.totalScore(1, 1); // Between time 1 and time 1, Alice took 1 exam at time 1, scoring 98. The total score is 98.
    examTracker.record(5, 99); // Alice takes a new exam at time 5, scoring 99.
    examTracker.totalScore(1, 3); // Between time 1 and time 3, Alice took 1 exam at time 1, scoring 98. The total score is 98.
    examTracker.totalScore(1, 5); // Between time 1 and time 5, Alice took 2 exams at time 1 and 5, scoring 98 and 99. The total score is 98 + 99 = 197.
    examTracker.totalScore(3, 4); // Alice did not take any exam between time 3 and time 4. Therefore, the answer is 0.
    examTracker.totalScore(2, 5); // Between time 2 and time 5, Alice took 1 exam at time 5, scoring 99. The total score is 99.



    *** Constraints ***
    1 <= time <= 10^9
    1 <= score <= 10^9
    1 <= startTime <= endTime <= t, where t is the value of time from the most recent call of record().
    Calls of record() will be made with strictly increasing time.
    After ExamTracker(), the first function call will always be record().
    At most 105 calls will be made in total to record() and totalScore().

*/

#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 14.44% */
/* Space Beats: 42.78% */

/* Time  Complexity: O(10^5 * log(total_score_calls)) */ // At most 10^5 calls
/* Space Complexity: O(10^5)                          */
class ExamTracker {
public:
    ExamTracker()
    {
        
    }
    
    void record(int time, int score)
    {
        if (prefix_sum.empty())
            prefix_sum.push_back( {time, 1LL * score} );
        else
            prefix_sum.push_back( {time, 1LL * score + prefix_sum.back().second});
    }
    
    long long totalScore(int startTime, int endTime)
    {
        auto it_start = lower_bound(prefix_sum.begin(), prefix_sum.end(), startTime, [](const auto& other, int value){
            return other.first < value;
        });

        auto it_end   = upper_bound(prefix_sum.begin(), prefix_sum.end(), endTime, [](int value, const auto& other){
            return value < other.first;
        });

        if (it_end == prefix_sum.begin())
            return 0LL;
        
        --it_end; // Move it back by one

        if (it_end->first < startTime)
            return 0LL;

        if (it_start == prefix_sum.begin())
            return it_end->second;

        return it_end->second - (std::prev(it_start)->second);
    }

private:
    vector<pair<int,long long>> prefix_sum;
};

/**
 * Your ExamTracker object will be instantiated and called as such:
 * ExamTracker* obj = new ExamTracker();
 * obj->record(time,score);
 * long long param_2 = obj->totalScore(startTime,endTime);
 */




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 35.29% */
/* Space Beats: 87.17% */

/* Time  Complexity: O(10^5 * log(total_score_calls)) */ // At most 10^5 calls
/* Space Complexity: O(10^5)                          */
class ExamTracker_2 {
public:
    void record(int time, int score)
    {
        times.push_back(time);

        if (scores_prefix_sum.empty())
            scores_prefix_sum.push_back(1LL * score);
        else
            scores_prefix_sum.push_back(1LL * score + scores_prefix_sum.back());
    }

    long long totalScore(int startTime, int endTime)
    {
        int left  = lower_bound(times.begin(), times.end(), startTime) - times.begin();
        int right = upper_bound(times.begin(), times.end(), endTime  ) - times.begin();
        --right; // Move one back

        if (left > right)
            return 0;

        long long result = scores_prefix_sum[right];

        if (left > 0)
            result -= scores_prefix_sum[left - 1];

        return result;
    }

private:
    vector<long long> scores_prefix_sum;
    vector<int> times;
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 31.55% */
/* Space Beats: 67.38% */

/* Time  Complexity: O(10^5 * log(total_score_calls)) */ // At most 10^5 calls
/* Space Complexity: O(10^5)                          */
class ExamTracker_3 {
public:
    void record(int time, int score)
    {
        times.push_back(time);
        scores_prefix_sum.push_back(scores_prefix_sum.back() + score);
    }

    long long totalScore(int startTime, int endTime)
    {
        int left  = lower_bound(times.begin(), times.end(), startTime) - times.begin();
        int right = upper_bound(times.begin(), times.end(), endTime  ) - times.begin();

        return scores_prefix_sum[right - 1] - scores_prefix_sum[left - 1];
    }

private:
    vector<long long> scores_prefix_sum{0};
    vector<int> times{0};
};
