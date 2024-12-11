#include <bits/stdc++.h>
using namespace std;

struct DefaultDict {
  unordered_map<int, int> data;

  int& operator[](const int& key) {
    if (!data.contains(key))
      data[key] = 0;
    return data[key];
  }
};

vector<pair<int, int>> counting_sort(const DefaultDict& table, int high = 200) {
  vector<pair<int, int>> res;
  for (int i = 0; i <= high; i++) {
    auto p = table.data.find(i);
    if (p != table.data.end())
      res.push_back(*p);
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int tc = 0, num_residencies, people, consump, avg_residence;
  float avg;

  cin >> num_residencies;
  while (num_residencies != 0) {
    DefaultDict num_residents_with_avg;
    int total_people = 0, total_consump = 0;

    tc++;
    if (tc != 1)
      cout << '\n';

    for (int i = 0; i < num_residencies; i++) {
      cin >> people >> consump;
      total_people += people;
      total_consump += consump;
      avg_residence = consump / people;
      num_residents_with_avg[avg_residence] += people;
    }
    avg = static_cast<float>(total_consump) / total_people;
    avg = int(avg * 100) / 100.0f;
    auto vals = counting_sort(num_residents_with_avg);

    cout << "Cidade# " << tc << ":\n";
    for (int i = 0; i < vals.size(); i++) {
      cout << vals[i].second << '-' << vals[i].first;
      if (i < vals.size() - 1)
        cout << ' ';
      else
        cout << '\n';
    }
    cout << "Consumo medio: " << fixed << setprecision(2) << avg << " m3.\n";

    cin >> num_residencies;
  }
}
