const int N = 1e6 + 10;
bool st[N];
int mu[N], prime[N], cnt, sum[N];
void getMu(int n) {
    mu[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!st[i]) {
            prime[++cnt] = i;
            mu[i] = -1;
        }
        for (int j = 1; j <= cnt && i * prime[j] <= n; j++) {
            st[i * prime[j]] = true;
            if (i % prime[j] == 0) {
                mu[i * prime[j]] = 0;
                break;
            }
            mu[i * prime[j]] = -mu[i];
        }
    }
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + mu[i];
    }
}