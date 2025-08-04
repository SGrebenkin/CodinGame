#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


int main()
{
    int n;
    cin >> n; cin.ignore();
    long long dp[101] = {0};

    vector<long long> values;
    for (int i = 0; i < n; i++) {
        long long housevalue;
        cin >> housevalue; cin.ignore();

        values.push_back(housevalue >= 0 ? housevalue : 0);
    }

    dp[0] = values[0];
    dp[1] = values[1];
    dp[2] = max(dp[1], values[2] + dp[0]);
    for (int i = 3; i < n; ++i)
        dp[i] = max(max(dp[i - 2], dp[i - 3]) + values[i], dp[i - 1]);

    cout << dp[n - 1] << endl;
    return 0;
}