vector<int> get_ngel(vector<int>& v) { // for left
	stack<int> st;
	st.push(-1);
	int n = v.size();
	vector<int> ng(n);
	for (int i = 0; i < n; ++i) {
		while (st.top() != -1 and v[st.top()] < v[i]) {
			st.pop();
		}
		ng[i] = st.top();
		st.push(i);
	}
	return ng;
}

vector<int> get_nger(vector<int>& v) {  // for right
	stack<int> st;
	int n = v.size();
	st.push(n);
	vector<int> ng(n);
	for (int i = n - 1; i >= 0; --i) {
		while (st.top() != n and v[st.top()] < v[i]) {
			st.pop();
		}
		ng[i] = st.top();
		st.push(i);
	}
	return ng;
}
