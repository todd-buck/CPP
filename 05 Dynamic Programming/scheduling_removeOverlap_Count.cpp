/*
Description:
    Given a 2D array of jobs represented by the interval {start, endl}, return the number of jobs to remove

Time Complexity: 
    O(n lg n) due to sorting algorithm used
    
Space Complexity:
    O(1), only utilize constant space to store local variables
*/

#include <iostream>

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

int removeOverlap(deque<deque<int>> jobs) {
    sort(jobs.begin(),jobs.end(),sortByJobEndAsc);
    
    int numberOfJobs = 0;
    int potentialJob = jobs[0][1];

    for(int i = 1; i < jobs.size(); i++) {
        if(jobs[i][0] < potentialJob) {
            numberOfJobs++;
            potentialJob = jobs[i][1];
        }
    }

    return numberOfJobs;
}

int main() {

    deque<deque<int>> jobs = {
        {1,2},
        {2,3},
        {3,4},
        {1,3},
        {1,5}
    };

    int numberOfJobsToRemove = removeOverlap(jobs);

    cout << "Nomber Of Jobs To Remove: " << numberOfJobsToRemove << endl;

    return 0;
}