/*
    ==============
    === MEDIUM ===
    ==============

    =============================
    3433) Count Mentions Per User
    =============================

    ============
    Description:
    ============

    You are given an integer numberOfUsers representing the total number of
    users and an array events of size n x 3.

    Each events[i] can be either of the following two types:

        Message Event: ["MESSAGE", "timestampi", "mentions_stringi"]
            + This event indicates that a set of users was mentioned in a message at
              timestampi.

            + The mentions_stringi string can contain one of the following
              tokens:
                id<number>: where <number> is an integer in
                range [0,numberOfUsers - 1].

                There can be multiple ids separated by a single whitespace and
                may contain duplicates. This can mention even the offline users

                ALL: mentions all users.

                HERE: mentions all online users.


        Offline Event: ["OFFLINE", "timestampi", "idi"]
            + This event indicates that the user idi had become offline at
              timestampi for 60 time units. The user will automatically be
              online again at time timestampi + 60.

    Return an array mentions where mentions[i] represents the number of
    mentions the user with id i has across all MESSAGE events.

    All users are initially online, and if a user goes offline or comes back
    online, their status change is processed before handling any message event
    that occurs at the same timestamp.

    =====
    Note: that a user can be mentioned multiple times in a single message
          event, and each mention should be counted separately.
    =====

    =======================================================================================
    FUNCTION: vector<int> countMentions(int numberOfUsers, vector<vector<string>>& events);
    =======================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: numberOfUsers = 2, events = [["MESSAGE","10","id1 id0"],["OFFLINE","11","0"],["MESSAGE","71","HERE"]]
    Output: [2,2]
    Explanation:
    Initially, all users are online.
    At timestamp 10, id1 and id0 are mentioned. mentions = [1,1]
    At timestamp 11, id0 goes offline.
    At timestamp 71, id0 comes back online and "HERE" is mentioned. mentions = [2,2]

    --- Example 2 ---
    Input: numberOfUsers = 2, events = [["MESSAGE","10","id1 id0"],["OFFLINE","11","0"],["MESSAGE","12","ALL"]]
    Output: [2,2]
    Explanation:
    Initially, all users are online.
    At timestamp 10, id1 and id0 are mentioned. mentions = [1,1]
    At timestamp 11, id0 goes offline.
    At timestamp 12, "ALL" is mentioned. This includes offline users, so both id0 and id1 are mentioned. mentions = [2,2]

    --- Example 3 ---
    Input: numberOfUsers = 2, events = [["OFFLINE","10","0"],["MESSAGE","12","HERE"]]
    Output: [0,1]
    Explanation:
    Initially, all users are online.
    At timestamp 10, id0 goes offline.
    At timestamp 12, "HERE" is mentioned. Because id0 is still offline, they will not be mentioned. mentions = [0,1]


    *** Constraints ***
    1 <= numberOfUsers <= 100
    1 <= events.length <= 100
    events[i].length == 3
    events[i][0] will be one of MESSAGE or OFFLINE.
    1 <= int(events[i][1]) <= 10^5
    The number of id<number> mentions in any "MESSAGE" event is between 1 and 100.
    0 <= <number> <= numberOfUsers - 1
    It is guaranteed that the user id referenced in the OFFLINE event is online at the time the event occurs.

*/

#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 76.47% */
/* Space Beats: 52.94% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    vector<int> countMentions(int numberOfUsers, vector<vector<string>>& events)
    {
        const int N = events.size();
        vector<int> result(numberOfUsers, 0);

        vector<pair<int,pair<char,string>>> modified_events;

        for (int i = 0; i < N; i++)
        {
            char type = events[i][0][0] == 'M' ? 'M' : 'A';
            int timestamp = stoi(events[i][1]);
            string mentions = events[i][2];

            modified_events.push_back( {timestamp, {type, mentions}} );
        }

        // O(1) because of the Constraints
        sort(modified_events.begin(), modified_events.end());

        vector<int> offline_up_until(numberOfUsers, -1);

        for (int i = 0; i < N; i++)
        {
            int timestamp = modified_events[i].first;
            char type = modified_events[i].second.first;

            if (type == 'A') // "OFFLINE"
            {
                int user = stoi(modified_events[i].second.second);

                offline_up_until[user] = modified_events[i].first + 60 - 1;
            }
            else // "MESSAGE"
            {
                if (modified_events[i].second.second[0] == 'A')
                {
                    for (int user = 0; user < numberOfUsers; user++)
                        result[user]++;
                }
                else if (modified_events[i].second.second[0] == 'H')
                {
                    for (int user = 0; user < numberOfUsers; user++)
                    {
                        if (offline_up_until[user] == -1)
                        {
                            result[user]++;
                        }
                        else if (offline_up_until[user] < timestamp)
                        {
                            offline_up_until[user] = -1;
                            result[user]++;
                        }
                    }
                }
                else // Mentions
                {
                    istringstream iss(modified_events[i].second.second);

                    vector<int> user_ids;
                    string user_str;
                    while (iss >> user_str)
                    {
                        user_ids.push_back(stoi(user_str.substr(2)));
                    }

                    for (const int& user : user_ids)
                        result[user]++;
                }
            }
        }

        return result;
    }
};

