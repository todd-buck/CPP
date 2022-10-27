/*
Description:
    Given a 2D array representing the width of various balloons, return the minimum number of arrows needed to pop every balloon
Time Complexity: 
    O(n lg n) due to sorting algorithm used
Space Complexity:
    O(1), only utilize constant space to store local variables
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

int popBalloons(deque<deque<int>> &balloons) {
    int arrows = 0;
    int potentialArrow = 0;

    sort(balloons.begin(), balloons.end(), sortByJobEndAsc);

    for(int i = 0; i < balloons.size(); i++) {
        if(arrows == 0 || balloons[i][0] > potentialArrow) {
            arrows++;
            potentialArrow = balloons[i][1];
        }
    }

    return arrows;

}

int main() {

    deque<deque<int>> balloons = {
        {10,16},
        {2,8},
        {1,6},
        {7,12},
    };

    int minArrows = popBalloons(balloons);

    cout << "Fewest Arrows to Pop Balloons: " << minArrows << endl;

    return 0;
}