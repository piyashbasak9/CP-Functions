const N = 1e6+10;
int mu[N];

void mobius() {
	mu[1] = 1;
	for (int i = 1; i < N; ++i) {
		if (mu[i]){
            for(int j = i + i; j < N; j += i) {
			    mu[j] -= mu[i];
		    }
        }
	}
}
