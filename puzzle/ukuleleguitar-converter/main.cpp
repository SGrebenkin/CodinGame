#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;


void generate_next_frets(map<string, string>& m){
    vector<string> seq{ "CX", "CX#", "DX", "DX#", "EX", "FX", "FX#", "GX", "GX#", "AX", "AX#", "BX"};

    string prev = "";
    for (int i = 0; i < 10; ++i) {
        for (auto s: seq) {
            string replaced = s.replace(1, 1, to_string(i));
            if (prev.size() > 0)
                m.emplace(prev, replaced);
            prev = replaced;
        }
    }
}

int main()
{
    string mode;
    getline(cin, mode);

    int n;
    cin >> n; cin.ignore();

    map<string, string> next_frets;
    generate_next_frets(next_frets);

    map<string, string> guitar_comb_to_fret;
    map<string, set<string>> guitar;
    vector<string> strings_guitar{"E4", "B3", "G3", "D3", "A2", "E2"};
    for (int j = 0; j < strings_guitar.size(); ++j) {
        string init_comb = to_string(j) + "/0";
        string next_fret = strings_guitar[j];

        for (int i = 0; i < 22; ++i) {
            string comb = to_string(j) + "/" + to_string(i);
            guitar_comb_to_fret.emplace(comb, next_fret);

            auto it = guitar.find(next_fret);
            if (it == guitar.end())
                guitar.emplace(next_fret, set{comb});
            else
                it->second.insert(comb);

            next_fret = next_frets[next_fret];
        }
    }

    map<string, string> ukulele_comb_to_fret;
    map<string, set<string>> ukulele;
    vector<string> strings_ukulele{"A4", "E4", "C4", "G4"};
    for (int j = 0; j < strings_ukulele.size(); ++j) {
        string init_comb = to_string(j) + "/0";
        string next_fret = strings_ukulele[j];

        for (int i = 0; i < 16; ++i) {
            string comb = to_string(j) + "/" + to_string(i);
            ukulele_comb_to_fret.emplace(comb, next_fret);

            auto it = ukulele.find(next_fret);
            if (it == ukulele.end())
                ukulele.emplace(next_fret, set{comb});
            else
                it->second.insert(comb);

            next_fret = next_frets[next_fret];
        }
    }

    for (int i = 0; i < n; i++) {
        int str;
        int fret;
        cin >> str >> fret;
        cin.ignore();

        string comb = to_string(str) + "/" + to_string(fret);
        const auto& set_comb_to_fret = (mode.compare("guitar") == 0) ? ukulele[guitar_comb_to_fret[comb]] : guitar[ukulele_comb_to_fret[comb]];
        if (set_comb_to_fret.empty())
            cout << "no match";
        else {
            bool init = true;
            for (auto s: set_comb_to_fret)
                if (init) {
                    cout << s;
                    init = false;
                }
                else
                    cout << " " << s;
        }

        cout << endl;
    }

    return 0;
}