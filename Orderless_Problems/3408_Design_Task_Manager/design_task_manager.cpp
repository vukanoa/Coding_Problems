/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    3408) Design Task Manager
    ===========================

    ============
    Description:
    ============

    There is a task management system that allows users to manage their tasks,
    each associated with a priority. The system should efficiently handle
    adding, modifying, executing, and removing tasks.

    Implement the TaskManager class:

    TaskManager(vector<vector<int>>& tasks) initializes the task manager with a
    list of user-task-priority triples. Each element in the input list is of
    the form [userId, taskId, priority], which adds a task to the specified
    user with the given priority.

    void add(int userId, int taskId, int priority) adds a task with the
    specified taskId and priority to the user with userId. It is guaranteed that
    taskId does not exist in the system.

    void edit(int taskId, int newPriority) updates the priority of the existing
    taskId to newPriority. It is guaranteed that taskId exists in the
    system.

    void rmv(int taskId) removes the task identified by taskId from the system.
    It is guaranteed that taskId exists in the system.

    int execTop() executes the task with the highest priority across all users.
    If there are multiple tasks with the same highest priority, execute the one
    with the highest taskId. After executing, the taskId is removed from
    the system. Return the userId associated with the executed task. If no
    tasks are available, return -1.

    =====
    Note: that a user may be assigned multiple tasks.
    =====

    ===============================
    CLASS:
    class TaskManager {
    public:
        TaskManager(vector<vector<int>>& tasks)
        {

        }

        void add(int userId, int taskId, int priority)
        {

        }

        void edit(int taskId, int newPriority)
        {

        }

        void rmv(int taskId)
        {

        }

        int execTop()
        {

        }
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:
    ["TaskManager", "add", "edit", "execTop", "rmv", "add", "execTop"]
    [[[[1, 101, 10], [2, 102, 20], [3, 103, 15]]], [4, 104, 5], [102, 8], [], [101], [5, 105, 15], []]

    Output:
    [null, null, null, 3, null, null, 5]

    Explanation
    TaskManager taskManager = new TaskManager([[1, 101, 10], [2, 102, 20], [3, 103, 15]]); // Initializes with three tasks for Users 1, 2, and 3.
    taskManager.add(4, 104, 5); // Adds task 104 with priority 5 for User 4.
    taskManager.edit(102, 8); // Updates priority of task 102 to 8.
    taskManager.execTop(); // return 3. Executes task 103 for User 3.
    taskManager.rmv(101); // Removes task 101 from the system.
    taskManager.add(5, 105, 15); // Adds task 105 with priority 15 for User 5.
    taskManager.execTop(); // return 5. Executes task 105 for User 5.


    *** Constraints ***
    1 <= tasks.length <= 10^5
    0 <= userId <= 10^5
    0 <= taskId <= 10^5
    0 <= priority <= 10^9
    0 <= newPriority <= 10^9
    At most 2 * 10^5 calls will be made in total to add, edit, rmv, and execTop methods.

*/

#include <vector>
#include <map>
#include <unordered_map>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 65.20% */
/* Space Beats: 67.20% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class TaskManager {
private:
    struct Task {
        int user_id, task_id, priority;

        // Default constructor
        Task() : user_id(0), task_id(0), priority(0) {}

        // Parameterized constructor
        Task(int userId, int taskId, int priority)
            : user_id(userId), task_id(taskId), priority(priority) {}

        // Define the comparison operator to maintain the correct order in the sorted container
        bool operator<(const Task& other) const
        {
            if (priority != other.priority)
            {
                return priority > other.priority; // Higher priority comes first
            }

            return task_id > other.task_id; // If priority is the same, higher taskId comes first
        }

        // Define the copy constructor
        Task(const Task& other) = default;

        // Define the move constructor
        Task(Task&& other) noexcept = default;

        // Define the copy assignment operator
        Task& operator=(const Task& other) = default;

        // Define the move assignment operator
        Task& operator=(Task&& other) noexcept = default;
    };

    map<Task, int> sorted_map_tasks;
    unordered_map<int, Task> umap_tasks;

public:
    TaskManager(vector<vector<int>>& tasks)
    {
        for (auto& task : tasks)
        {
            int user_id = task[0], task_id = task[1], priority = task[2];
            add(user_id, task_id, priority);
        }
    }

    // O(logN)
    void add(int user_id, int task_id, int priority)
    {
        Task task(user_id, task_id, priority);
        sorted_map_tasks[task] = user_id;
        umap_tasks[task_id] = task;
    }

    // O(logN)
    void edit(int task_id, int new_priority)
    {
        auto task_iterator = umap_tasks.find(task_id);

        if (task_iterator != umap_tasks.end())
        {
            Task task = task_iterator->second;

            sorted_map_tasks.erase(task);

            task.priority = new_priority;
            sorted_map_tasks[task] = task.user_id;
            umap_tasks[task_id] = task;
        }
    }

    // O(logN)
    void rmv(int taskId)
    {
        auto it = umap_tasks.find(taskId);
        if (it != umap_tasks.end())
        {
            Task task = it->second;
            sorted_map_tasks.erase(task);
            umap_tasks.erase(taskId);
        }
    }

    // O(logN)
    int execTop()
    {
        if (sorted_map_tasks.empty())
            return -1;

        auto topTask = sorted_map_tasks.begin();
        Task top = topTask->first;
        sorted_map_tasks.erase(topTask);
        umap_tasks.erase(top.task_id);

        return top.user_id;
    }
};
