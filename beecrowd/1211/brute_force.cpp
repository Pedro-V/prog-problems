#include <bits/stdc++.h>
using namespace std;

int len_common_prefix(const string& s1, const string& s2) {
  int i = 0;
  while (s1[i] == s2[i]) i++;
  return i;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int num_phones;
  string phone;

  cin >> num_phones;
  while (!cin.eof()) {
    vector<string> phones;
    for (int i = 0; i < num_phones; i++) {
      cin >> phone;
      phones.push_back(phone);
    }
    sort(phones.begin(), phones.end());

    int saved_chars = 0;
    for (int i = 1; i < phones.size(); i++)
      saved_chars += len_common_prefix(phones[i-1], phones[i]);
    cout << saved_chars << '\n';

    cin >> num_phones;
  }
}
