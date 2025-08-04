#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define N 20

using namespace std;


int traversal(int _maze[N][N], int _traverse[N][N], int i, int j, int n, int prev_cur){
    if (i < 0 || j < 0 || i >= n || j >= n)
        return 0;

    int new_cur = _maze[i][j];
    if (prev_cur - new_cur > 1)
        return 0;

    if (_traverse[i][j] >= 4)
        return 0;

    _traverse[i][j]++;


    if (new_cur == 0)
        return 1;

    return traversal(_maze, _traverse, i+1, j, n, new_cur) ||
        traversal(_maze, _traverse, i, j+1, n, new_cur) ||
        traversal(_maze, _traverse, i-1, j, n, new_cur) ||
        traversal(_maze, _traverse, i, j-1, n, new_cur);
}


int main()
{
    int n;
    cin >> n;
    cin.ignore();
    int maze[N][N]={0};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int elevation;
            cin >> elevation; cin.ignore();
            maze[i][j] = elevation;
        }
    }

    int traverse[N][N]={0};
    if (traversal(maze, traverse, n/2, n/2, n, maze[n/2][n/2]))
        cout << "yes" << endl;
    else
        cout << "no" << endl;

    return 0;
}