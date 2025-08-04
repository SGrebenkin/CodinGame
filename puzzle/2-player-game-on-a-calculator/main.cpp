// https://www.codingame.com/ide/puzzle/2-player-game-on-a-calculator

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

template<class F>
int iter_prev(int x, F f) {
    if (x == 1) { f(2); f(4); f(5); }
    else if (x == 2) { f(1); f(3); f(4); f(5); f(6); }
    else if (x == 3) { f(2); f(5); f(6); }
    else if (x == 4) { f(1); f(2); f(5); f(7); f(8); }
    else if (x == 5) { f(1); f(2); f(3); f(4); f(6); f(7); f(8); f(9); }
    else if (x == 6) { f(2); f(3); f(5); f(8); f(9); }
    else if (x == 7) { f(4); f(5); f(8); }
    else if (x == 8) { f(4); f(5); f(6); f(7); f(9); }
    else if (x == 9) { f(5); f(6); f(8); }
}

int N[100011][10] = {0};

int main()
{
    int n;
    cin >> n; cin.ignore();

    for (int i = 1; i < 10; ++i)
        for (int j = 0; j < i; ++j)
            N[j][i] = 1; // 1 means "lost", initialize carefully all the items till 10

    for (int k = 0; k <= n; ++k)
        for (int i = 1; i < 10; ++i) {
            iter_prev(i, [&](int next_num){
                // Try to check the position i as we come from it and go to next_num.
                if (N[k][i] == 0) // Analyzing the current "winning" item.
                    // The item where we come from should be marked "lost" if it points to any "winning" position.
                    // We assume that players play optimally and another player will definitely choose the "winning" step.
                    N[k + next_num][next_num] = max(static_cast<int>(!N[k][i]), N[k + next_num][next_num]);
            });
        }

    bool printed = false;
    for (int i = 1; i < 10; ++i) {
        if (N[n][i] == 0) {
            if (!printed) {
                cout << i;
                printed = true;
            }
            else {
                cout << " " << i;
            }
        }
    }
}

