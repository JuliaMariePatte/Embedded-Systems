#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
#include <cmath>
#include <climits>

using namespace std;

struct Task
{
    int exec_time;
    int period;
    bool is_done;
    int index;
};

struct TaskInstance
{
    int task_id;
    int exec_time;
    int release_time;
    int deadline;
};

int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int lcm(int a, int b)
{
    return abs(a * b) / gcd(a, b);
}

int main()
{
    // Task definition
    Task Task1 = {2, 10, false, 1};
    Task Task2 = {3, 10, false, 2};
    Task Task3 = {2, 20, false, 3};
    // Task Task4 = {2, 20, false, 4};
    Task Task5 = {2, 40, false, 5};
    // Task Task6 = {2, 40, false, 6};
    // Task Task7 = {3, 80, false, 7};

    // List of tasks
    vector<Task> List_task = {Task1, Task2, Task3, Task5};

    // Extract periods for hyperperiod calculation
    vector<int> periods;
    for (const auto &task : List_task)
    {
        periods.push_back(task.period);
    }

    // Compute the LCM (hyperperiod)
    int hyperperiod = accumulate(periods.begin(), periods.end(), 1, lcm);
    cout << "Hyperperiod = " << hyperperiod << endl;

    // Generate instances of each task
    vector<TaskInstance> task_instances;
    for (const auto &task : List_task)
    {
        int num_instances = hyperperiod / task.period;
        for (int i = 0; i < num_instances; ++i)
        {
            int release_time = i * task.period;
            int deadline = (i + 1) * task.period;
            task_instances.push_back({task.index, task.exec_time, release_time, deadline});
        }
    }

    // Function to check if a schedule is valid
    auto is_valid_schedule = [](const vector<TaskInstance> &schedule)
    {
        int current_time = 0;
        for (const auto &task : schedule)
        {
            if (current_time < task.release_time)
            {
                current_time = task.release_time;
            }
            if (current_time + task.exec_time > task.deadline)
            {
                return false;
            }
            current_time += task.exec_time;
        }
        return true;
    };

    // Function to calculate total waiting time
    auto calculate_total_waiting_time = [](const vector<TaskInstance> &schedule)
    {
        int current_time = 0;
        int total_waiting_time = 0;
        for (const auto &task : schedule)
        {
            if (current_time < task.release_time)
            {
                current_time = task.release_time;
            }
            total_waiting_time += current_time - task.release_time;
            current_time += task.exec_time;
        }
        return total_waiting_time;
    };

    // Generate all possible permutations using indices
    vector<int> indices(task_instances.size());
    iota(indices.begin(), indices.end(), 0); // Fills with 0, 1, ..., N-1

    vector<vector<TaskInstance>> valid_schedules;
    int min_waiting_time = INT_MAX;
    vector<TaskInstance> optimal_schedule;

    do
    {
        vector<TaskInstance> candidate;
        for (int idx : indices)
            candidate.push_back(task_instances[idx]);

        if (is_valid_schedule(candidate))
        {
            valid_schedules.push_back(candidate);
            int wait = calculate_total_waiting_time(candidate);
            if (wait < min_waiting_time)
            {
                min_waiting_time = wait;
                optimal_schedule = candidate;
            }
        }
    } while (next_permutation(indices.begin(), indices.end()));

    // Display the result
    cout << "\nBest combination with the minimum waiting time: " << endl;
    for (const auto &task : optimal_schedule)
    {
        cout << "t" << task.task_id << " " << endl;
    }

    cout << "\nTotal waiting time: " << min_waiting_time << " seconds" << endl;

    return 0;
}
