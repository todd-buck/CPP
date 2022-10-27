/*
Description:
    Given a 2D array of jobs represented by the interval {start, endl}, return a 2D array of overlapping jobs to remove

Time Complexity: 
    O(n lg n) due to sorting algorithm used
    
Space Complexity:
    O(n^2) to return pontial jobs to remove (worst case: all jobs except for one are removed, slightly less than O(n^2) memory to store all jobs passed in)
*/

#include <iostream>
#include <deque>

using namespace std;

static bool sortByJobStartAsc(deque<int> &a, deque<int> &b) {
    return a[0] < b[0];
}

static bool sortByJobStartDesc(deque<int> &a, deque<int> &b) {
    return a[0] > b[0];
}

static bool sortByJobEndAsc(deque<int> &a, deque<int> &b) {
    return a[1] < b[1];
}

static bool sortByJobEndDesc(deque<int> &a, deque<int> &b) {
    return a[1] > b[1];
}

deque<deque<int>> removeOverlap(deque<deque<int>> jobs) {
    deque<deque<int>> jobsToRemove;

    sort(jobs.begin(),jobs.end(),sortByJobEndAsc);
    
    int numberOfJobs = 0;
    int potentialJob = jobs[0][1];

    for(int i = 1; i < jobs.size(); i++) {
        if(jobs[i][0] < potentialJob) {
            jobsToRemove.push_back(jobs[i]);
            potentialJob = jobs[i][1];
        }
    }

    return jobsToRemove;
}

int main() {

    deque<deque<int>> jobs = {
        {1,2},
        {2,3},
        {3,4},
        {1,3},
        {1,5}
    };

    deque<deque<int>> ListOfJobsToRemove = removeOverlap(jobs);

    cout << "Jobs To Remove:\n";
    cout << "{\n";
    for(deque<int> jobsToRemove: ListOfJobsToRemove) {
        cout << "\t{";
        for(int interval: jobsToRemove) {
            cout << interval;
            if(interval != jobsToRemove[jobsToRemove.size() - 1]) cout << ",";
        }
        cout << "}";
        if(jobsToRemove != ListOfJobsToRemove[ListOfJobsToRemove.size() - 1]) cout << ",";
        cout << endl;
    }
    cout << "}\n";

    return 0;
}