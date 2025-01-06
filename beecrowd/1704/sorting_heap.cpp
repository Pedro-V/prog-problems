/*
 * Idea:
 * We will change our way of thinking about the problem, towards a backward-based way of thinking.
 * That is, we will be starting from the end of the time we have available, and then go backward in time.
 *
 * This helps because in the usual, forward way of thinking (from smallest t to highest),
 * you have to keep asking in your head which (if any) of the tasks in the *future* should be executed now.
 * But if you try to solve some problems by hand using this way, you're gonna
 * find doing all this asking is too hard!
 *
 * By changing the way of thinking to be backwards-based, we have a way of
 * thinking that is much more aligned with the nature of the problem:
 * When t is at its largest (t = H), the executed task at that time MUST be
 * from the tasks whose time equals t. Specifically, it must be the one with largest value.
 * Let this task be 'task x'.
 * When t = H - 1, the task we will execute will be the largest in the set
 * formed by the union of the tasks that have time t = H and those that have t = H - 1,
 * excluding task x. Again, let the task we pick up at this step be 'task y'.
 * When t = H - 2, the task will execute will be the largest in the set formed
 * by the tasks that have time t in {H, H-1, H-2}, excluding tasks x and y.
 * I think you get the idea.
 *
 * To implement this idea, we will use (reverse) sorting and heaps!
 * Popping the largest element of the heap is equivalent to allocating it as a task.
 * The time complexity is O(nlogn).
 */

#include <bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;

int solve(vector<ii> pairs, int h) {
  priority_queue<int> pq;
  int n = pairs.size(), sum = 0;
  int task_idx = 0, curr_time = pairs[0].first;

  for (; curr_time > 0; curr_time--) {
    while (task_idx < n && pairs[task_idx].first == curr_time)
      pq.push(pairs[task_idx++].second);
    if (!pq.empty())
      pq.pop();
  }

  while (!pq.empty()) {
    sum += pq.top();
    pq.pop();
  }
  return sum;
}

int main() {
  int n, h, i, v, t;
  while (cin >> n >> h) {
    vector<ii> pairs(n);
    for (i = 0; i < n; i++)
      cin >> pairs[i].second >> pairs[i].first;
    sort(pairs.begin(), pairs.end(), greater<ii>());
    cout << solve(pairs, h) << '\n';
  }
}
