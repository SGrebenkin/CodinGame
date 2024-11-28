#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Returns true if point is inside the triangle
bool pnpoly(const vector<pair<int, int>>& triag, int x, int y) {
    int ctr = 0;
    for (int i = 0; i < triag.size(); ++i) {
        int iy = triag[i].first;
        int ix = triag[i].second;
        int jy = triag[(i + 1) % triag.size()].first;
        int jx = triag[(i + 1) % triag.size()].second;

        // calculate vector product
        int res = (x - ix) * (jy - iy) - (y - iy) * (jx - ix);
        if (res == 0)
            return true;

        // save sign of vector product
        // if the point is inside the triangle, all
        // vector products should have the same sign
        ctr += (res >= 0) ? 1 : ((res <= 0) ? -1 : 0);
    }

    // check vector product after traversal
    if (abs(ctr) == 3)
        return true;

    return false;
}

int main()
{
    int hi;
    int wi;
    cin >> hi >> wi; cin.ignore();
    string style;
    getline(cin, style);
    int how_many_triangles;
    cin >> how_many_triangles; cin.ignore();

    vector<vector<char>> board;
    for (int i = 0; i < hi; ++i)
        board.push_back(vector<char>(wi, '*'));

    for (int i = 0; i < how_many_triangles; i++) {
        int x_1, y_1, x_2, y_2, x_3, y_3;
        cin >> x_1 >> y_1 >> x_2 >> y_2 >> x_3 >> y_3; cin.ignore();

        vector<pair<int, int>> triag{ {y_1, x_1}, {y_2, x_2}, {y_3, x_3} };

        int x_min = max(min({ x_1, x_2, x_3 }), 0);
        int y_min = max(min({ y_1, y_2, y_3 }), 0);
        int x_max = min(max({ x_1, x_2, x_3 }), wi - 1);
        int y_max = min(max({ y_1, y_2, y_3 }), hi - 1);

        for (int i = x_min; i <= x_max; ++i)
            for (int j = y_min; j <= y_max; ++j) {
                if (pnpoly(triag, i, j)) {
                    if (board[j][i] == '*')
                        board[j][i] = ' ';
                    else
                        board[j][i] = '*';
                }
            }
    }

    for (int j = 0; j < board.size(); ++j) {
        for (int i = 0; i < board[j].size(); ++i) {
            cout << board[j][i];
            if (style.compare("expanded") == 0 && i != board[j].size() - 1)
                cout << " ";
        }

        cout << endl;
    }

    return 0;
}
