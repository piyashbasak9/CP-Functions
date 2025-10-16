vector<int> lps(string $t){
	int m = s.length();
	vector<int> pi(m);
	for (int i = 1, j = 0; i < m; ++i) {
    while (j > 0 and t[i] != t[j]) {
      j = pi[j - 1];
    }
    if (t[i] == t[j]) ++j;
    pi[i] = j;
  }
  return pi;
}


int kmp(string &s, string &t){
	int n = s.length(), m = t.length();
	auto pi = lps(t);
	int ans = 0;
  for (int i = 0, j = 0; i < n; ++i) {
    while(j > 0 and s[i] != t[j]) {
      j = pi[j - 1];
    }
    if (s[i] == t[j]) ++j;
    if (j == m) {
      ++ans;
      j = pi[j - 1];
    }
  }
  return ans;
}
