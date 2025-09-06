#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

std::string trim(const std::string& s) {
    size_t start = 0, end = s.size();
    while (start < end && std::isspace(static_cast<unsigned char>(s[start]))) ++start;
    while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1]))) --end;
    return s.substr(start, end - start);
}

std::vector<std::string> split_at_any(const std::string& input, const std::string& delimiters) {
    std::vector<std::string> tokens;
    size_t last_pos = 0;
    for (size_t i = 0; i <= input.size(); ++i) {
        if (i == input.size() || delimiters.find(input[i]) != std::string::npos) {
            std::string token = trim(input.substr(last_pos, i - last_pos));
            if (!token.empty())
                tokens.push_back(std::move(token));
            last_pos = i + 1;
        }
    }
    return tokens;
}

int main()
{
    string actor_name;
    getline(cin, actor_name);
    int n;
    cin >> n; cin.ignore();

    // create graph
    std::unordered_map<std::string, std::unordered_set<std::string>> graph;
    for (int i = 0; i < n; i++) {
        string movie_cast;
        getline(cin, movie_cast);
        auto result = split_at_any(movie_cast, ":,");
        
        for (size_t i = 1; i < result.size() - 1; ++i) {
            for (size_t j = i + 1; j < result.size(); ++j) {
                graph[result[i]].insert(result[j]);
                graph[result[j]].insert(result[i]);
            }
        }
    }

    // traverse
    std::unordered_set<std::string> visited;
    std::queue<std::pair<std::string, int>> q;
    q.push({actor_name, 0});

    while(!q.empty()) {
        auto [name, distance] = q.front();
        q.pop();

        if (visited.contains(name))
            continue;
        visited.insert(name);

        if (name == "Kevin Bacon") {
            cout << distance << endl;
            break;
        }

        auto element = graph.find(name);
        if (element != graph.end())
            for (auto i: element->second)
                if (!visited.contains(i))
                    q.push({i, distance + 1});
    }

    return 0;
}