# 数学公式

## 数列公式

### 等差数列

通项公式：$a_n = a_1 + (n-1) \times d$

求和公式：$S_n = na_1 + \frac {n(n-1)}{2}d, \, n \in N^+ $

### 等比数列

通项公式：$a_n = a_1q^{n-1}$

求和公式：$S_n = \dfrac {a_1(1-q^n)}{1-q}(q \neq 1)$

## 数论定理

### 裴蜀定理

若 a，b 是整数，且 gcd(a, b) = d，那么对于任意的整数x，y，都有 ax + by 是 d 的倍数

证明：
$ \begin {align} ax+by & = \frac {a} {d}*d*x + \frac {b} {d}*d*y \\ & = (\frac{a}{d}x + \frac {b}{d}y) * d \end {align}$

由于 d | a， 且 d | b，所以$(\frac{a}{d}x + \frac {b}{d}y)$ 也是整数，所以$ax + by = kd$成立

特别地，一定存在整数x，y，使 ax + by = d 成立。

它的一个重要推论是：a,b互质的充分必要条件是存在整数x,y使ax+by=1.

### 扩展欧几里得算法

扩展欧几里得算法：求解 ax + by = gcd(a, b) 的算法，解不唯一

当 b = 0 时，不定方程变为：ax = gcd(a, b) ，由欧几里得算法可知，此时 a = gcd(a, b)

那么此时方程的解为：x = 1，y = 0 

当 b != 0 时

$\begin {align} ax + by & = gcd(a,b) \\ & = gcd(b, a\%b)\\ & = b *x_1 + (a- \lfloor \frac{a}{b} \rfloor * b) *y_1 \\ & = a*y_1 + b*(x_1- \frac{a}{b}*y_1) \end {align}$

可以推知初始状态的x，y与上一状态x1，y1有关： 

$x = y_1 $
$y = x_1 – a/b * y_1 $

代码：

```c++
int exgcd(int a, int b, int &x, int &y) { // 扩欧算法
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x); // x, y颠倒, 直接使得 x 变成了 y, y 变成了 x
    // 此处省略了 x = y
    y -= a / b * x; // 即 y = x - a / b * y
    return d;
}
```

### 逆元

对于正整数 $a$ 和 $p$，如果有 $ax \equiv 1 \, (mod \, p) $ 那么把这个同余方程中 $x$ 的最小正整数解叫做 $a$ 模 $p$ 的逆元。一个数有逆元的充分必要条件是 $gcd(a, p) = 1$，此时逆元唯一存在。

逆元的含义：模 p 意义下，数 a 如果有逆元 x，那么除以 a 相当于乘以 x。

### 欧拉定理

**欧拉函数**：$\phi(n)$ 是1 ~ n 中与 n 互质的数的个数，$n\in N^+$ 。

**欧拉定理**：对于互质的 $a$ 和 $n$，存在 $a^{\phi(n)} \equiv 1 \, (mod \, n)$，

特别地，当 n 是质数时，该结论加强为：费马小定理

p 是质数时，$\phi(p) = p - 1$，则有 $a^{p-1} \equiv 1 \, (mod \, p)$

### 扩展欧拉定理

扩展欧拉定理：用于降幂，又称**欧拉降幂**

$a^b  \equiv \left \{ \begin{array}{c} a^{b\% \phi(n)} & gcd(a, n) = 1\\ a^b & gcd(a, n) \neq 1, \, b <\phi(n)  & (mod \ n) \\ a ^ {b \% \phi (n) + \phi(n)} & gcd(a, n) \neq 1,b \ge \phi(n) \end{array} \right. $

当 $gcd(a, n) \ne 1$ 且 $b < \phi(n)$ 时， $a ^ b = a^{b \% \phi (n)}$ 也成立，因为$\phi(n) > b$ 此时 $b \% \phi(n) = b$

### 费马小定理

**费马小定理**：如果 p 是一个质数，而整数 a 不是 p 的倍数，则有 $a^{p-1} \equiv 1 (mod \, p)$

则有：$a*a^{p-2} \equiv 1 \, (mod \, p)$，所以 a 在模 p下的逆元是 $a^{p-2}$

```c++
inv[i] = dpow(i, mod - 2);
```

### 中国剩余定理

用现代数学的语言来说明的话，中国剩余定理给出了以下的一元线性同余方程组：

$(S) : \left \{ \begin{array}{c} x \equiv a_1 (mod \ m_1) \\ x \equiv a_2 (mod \ m_2) \\ ............... \\ x \equiv a_n (mod\ m_n) \end{array} \right.$

有解的判定条件，并用构造法给出了在有解情况下解的具体形式。

中国剩余定理说明：假设整数$m_1$，$m_2$，...，$m_n$ 两两互质，则对任意的整数：$a_1$，$a_2$，...，$a_n$，方程组$(S)$有解，并且通解可以用如下方式构造得到：

设 $M = m_1 \times m_2 \times ... \times m_n = \prod_{i=1}^{m_i}$ 是整数$m_1$，$m_2$，...，$m_n$ 的乘积并设$M_i = M / m_i$，$\forall i \in \{ 1,2,...,n \}$是除了$m_i$以外的 $n-1 $个整数的乘积。

设 $t_i = M_i^{-1}$ 为 $M_i$ 模 $m_i$ 的数论倒数（ $t_i$ 为 $M_i$ 模 $m_i$ 意义下的逆元），$M_it_i \equiv 1 \ (mod \ m_i) $，$\forall i \in \{ 1,2,...,n \}$

方程组 $(S)$ 的通解形式为 $x = a_1t_1M_1 + a_2t_2M_2 + ... + a_nt_nM_n + kM = kM + \sum _{i=1}^na_it_iM_i$，$k \in Z$

在模 $M$  的意义下，方程组 $(S)$ 只有一个解：$x = (\sum _{i=1}^n a_i t_i M_i) \ mod \ M$

证明：

从假设可知，对任何 $i \in \{ 1,2,...,n \}$，由于 $\forall j \in \{ 1,2,...,n \}$，$j \neq i$，$gcd(m_i, m_j) = 1$，所以 $gcd(m_i, M_i) = 1$，这说明存在整数 $t_i$ 使得 $t_iM_i \equiv 1 \ (mod \ m_i)$，这样的 $t_i$ 叫做 $M_i$ 在模 $m_i$ 意义下的逆元。

考察乘积 $a_i t_i M_i$ 可知 $a_it_iM_i \equiv a_i*1 \equiv a_i \ (mod \ m_i)$

$\forall j \in \{ 1, 2, ... , n \}$， $j \neq i$，$a_i t_i M_i \equiv 0 \ (mod \ m_j)$

所以 $x = a_1t_1M_1 + a_2 t_2 M_2 + ... + a_n t_n M_n$ 

满足：$\forall i \in \{ 1,2,...,n \}$，$x = a_i t_i M_i + \sum_{j \neq i}^{}a_jt_jM_j \equiv a_i + \sum_{j\neq i}0 \equiv \ (mod \ m_i)$

这说明 $x$ 就是方程组 $(S)$ 的一个解。

另外，假设 $x_1$ 和 $x_2$ 都是方程组 $(S)$ 的解，那么：$\forall i \in \{ 1,2,...,n \}$，$x_1 - x_2 \equiv 0 \ (mod \ m_i)$ 而  $m_1$，$m_2$，...，$m_n$ 两两互质，这说明 $M = \prod_{i=1}^{n}m_i$ 整除 $x_1 - x_2$ . 所以方程组 $(S)$ 的任何两个解之间必然相差 $M$ 的整数倍。而另一方面，$x = a_1t_1M_1 + a_2t_2M_2 + ... + a_nt_nM_n $ 是一个解，同时所有形式为： $x = a_1t_1M_1 + a_2t_2M_2 + ... + a_nt_nM_n + kM = kM + \sum _{i=1}^na_it_iM_i$，$k \in Z$ 的整数也是方程组 $(S)$ 的解。所以方程组所有的解的集合就是：$\{ kM+ \sum_{i=1}^{n}a_it_iM_i; \ k \in Z \}$.

详细证明可见：《初等数论及其应用》

中国剩余定理扩展：可以扩展到一般情况，即不需要模数 $m_i$ 两两互质

假设已经求出 前 i - 1个方程构成的方程组的一个解是 $x_1$，另一个解是 $x_2$， 

$x' = x + t*M$

## 素数

### 唯一分解定理

任何一个大于1的自然数N，如果N不为质数，都可以唯一分解成有限个质数的乘积 $N = P_1^{a_1}P_2^{a_2}...P_n^{a_n}$。这里 $P_1<P_2<...<P_n$ 均为质数，质数 $a_i$ 均为正整数 。

### 质因数分解模板

```c++
vector<pair<int, int> > getdiv(int x) {
    vector<pair<int, int> > ans;
    for (int i = 1; i <= x; i++) {
        int cnt = 0;
        while (x % i == 0) {
            x /= i;
            cnt++;
        }
        if (cnt) ans.push_back({i, cnt});
    }
    if (x > 1) ans.push_back({x, 1});
    return ans;
    // 如果需要顺序，可以排序
}
```

### 试除法判定素数

```c++
bool is_prime(int x) {
    if (x < 2) return false;
    for (int i = 2; i <= x / i; i++)
        if (x % i == 0)
            return false;
    return true;
}
```

### 埃式筛求素数

```c++
int primes[N], cnt;     // primes[]存储所有素数
bool vis[N];         	// vis[x]存储x是否被筛掉

void get_primes(int n) {
    for (int i = 2; i <= n; i++) {
        if (vis[i]) continue;
        primes[cnt ++ ] = i;
        for (int j = i + i; j <= n; j += i)
            st[j] = true;
    }
}
```

### 线性筛求素数

```c++
int primes[N], cnt;     // primes[]存储所有素数
bool vis[N];         	// vis[x]存储x是否被筛掉

void get_primes() {
    for (int i = 2; i < N; i++) {
        if (!vis[i]) primes[cnt++] = i;
        for (int j = 0; i * primes[j] < N; j ++ ) { //
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0) break;
        }
    }
}
```

## 约数

### 试除法求所有约数

```c++
vector<int> get_divisors(int x) {
    vector<int> res;
    for (int i = 1; i <= x / i; i ++ )
        if (x % i == 0) {
            res.push_back(i);
            if (i != x / i) res.push_back(x / i);
        }
    sort(res.begin(), res.end());
    return res;
}
```

### 约数个数和约束之和

唯一分解定理： $N = P_1^{a_1} * P_2^{a_2} * ... *P_n^{a_n}$ 

约数个数公式： $(a_1 + 1) * (a_2 + 1) * ... * (a_n + 1)$ 

约数之和公式： $(P_1^0 + P_1^1 + ... + P_1^{a_1}) * ... * (P_n^0 + P_n^1 + ... + P_n^{a_n})$

## 求逆元的方法

### 扩展欧几里得算法求逆元

$ax \equiv 1 \, (mod \, m)$，则 x 为 a 模 m 的逆元

因为 ax 与 1 在 模 m 下同余，所以 ax 与 1 的差值的绝对值是一定是 m 的倍数。

则有$ax + my = 1$，由于扩展欧几里得算法可以求解$ax + by = gcd(a, b)$

所以当 $gcd(a, m) = 1$ 时，可以用扩展欧几里得算法求 a 模 m 下的逆元 x

代码：

```c++
int exgcd(int a, int b, int &x, int &y) { // 扩展欧几里得算法
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}
int get_inv(int a, int m) { // 求a在模m下的逆元，不存在返回-1
    int x, y;
    int d = exgcd(a, m, x, y);
    return d == 1 ? (x + m) % m : -1; // x + m 防止x为负数
}
```

### 费马小定理求逆元

**费马小定理**：如果 p 是一个质数，而整数 a 不是 p 的倍数，则有 $a^{p-1} \equiv 1 (mod \, p)$

则有：$a*a^{p-2} \equiv 1 \, (mod \, p)$，所以 a 在模 p下的逆元是 $a^{p-2}$

**条件**：p 是一个质数，a 不是 p 的倍数

**代码**：

```c++
inv[i] = dpow(i, mod - 2);
```

### 欧拉定理求逆元

**欧拉定理**：若a、p互素，则有$a^{\phi (p)} \equiv 1 \, (mod \, p) $（费马小定理的一般形式）

则有：$a*a^{\phi (p) - 1} \equiv 1 \, (mod \, p) $

$a^{\phi (p) - 1}$ 就是 a 在模 p 意义下的逆元

**条件**：a，p互质

### 递推求逆元（线性逆元打表）

$ii^{-1} \equiv 1 \, (mod \, p)$ ，则 $i$ 在模 p 下的逆元是 $i^{-1}$

设 $k = p / i$， $r = p \% i$，则有  $p = k * i + r$

$k * i + r \equiv 0 \, (mod \, p)$

两边同时乘以 $i^{-1}*r^{-1}$，得

$k*r^{-1}+i^{-1} \equiv 0 \, (mod \, p)$

$i^{-1} \equiv -k * r^{-1} \, (mod \, p)$

$i^{-1} \equiv -p/i*(p\%i)^{-1} \, (mod \, p)$

**代码**：

```C++
inv[1] = 1;
for (int i = 2; i <= n; i++) {
    inv[i] = (mod - mod / i) * inv[mod % i] % mod;
}
```

**注意**：

调用前要先预处理

调用的时候先对除数取mod

**适用范围**：mod数是不大的素数而且多次调用，比如卢卡斯定理。

### 通用公式求逆元

通常情况下，遇到$\frac {a}{b} mod \, m$ 的问题时，一般通过费马小定理来解决，但是只有当 $gcd(b, m) = 1$时，b的逆元才存在。

对于 $gcd(b, m) \neq 1$ 的情况，有一通用公式：$d = \frac{a}{b} mod \, m = (a \, mod \,(k*b))/b$

推到过程：

$\frac {a}{b} \, mod \, m = d$

$\frac{a}{b} = mx + d$

$a = mbx + bd$

$a = (mb)x + bd$

$a \, mod \, mb = bd$

$d = \frac {a \, mod \, kb}{b}$

之前的费马小定理和扩展欧几里得算法求逆元是有局限性的，它们都会要求a和m互素（此处的 a 和 m 是之前 ax = 1（mod m）中的 a 和 m，在这里应该是这里的 b 和 m 互素），如果不互素逆元不存在。b * m 很大的时候不适合当两者互质的时候，b 与 m 可能会很大，不适合套用一般公式，因此大部分时还是使用逆元处理。

## 欧拉函数

### 欧拉函数

小于或等于 $n$ 的正整数中与 $n$ 互质的数的个数，记作 $\phi (n)$。

欧拉函数的通式：$\phi (n) = n * \prod _{i=1}^{n}(1- \frac {1} {P_i})$，$P_i$ 是 $n$ 的质因数。

### 朴素求欧拉函数

```c++
int phi(int x) {
    int res = x;
    for (int i = 2; i <= x / i; i ++ )
        if (x % i == 0) {
            res = res / i * (i - 1);
            while (x % i == 0) x /= i;
        }
    if (x > 1) res = res / x * (x - 1);
    return res;
}
```

欧拉函数的两个重要性质

$P_j$ 是质数，$i$ 是大于 $P_j$ 的正整数。 

**①当 $i$ 与 $P_j$ 互质时，有 $\phi(i *P_j) =  \phi (i) * (P_j - 1)$；**

证明：由于 $i$ 与 $P_j$ 互质，所以 $i$ 与 $P_j$ 没有共同的因子，也即是没有共同质因子。

​			$P_j$  是质数，则 $P_j$ 一定是 $i * P_j$ 的一个质因子，且 $i$ 与 $P_j$ 没有共同质因子，所以 $i * P_j$ 唯一分解中 $P_j$ 的			指数一定是1。

​			假设 $i * P_j = P_1^{a_1} * P_2^{a_2} *...P_{j-1}^{a_{j-1}}*P_{j}*P_{j+1}^{a_{j+1}}*...*P_n^{a_n}$ 

​			则 $\phi(i * P_j) =  i * (1 - \frac{1}{P_1}) * (1 - \frac{1}{P_2}) * ... * (1 - \frac{1}{P_{j-1}}) * (1 - \frac{1}{P_{j}}) *(1 - \frac{1}{P_j+1}) * ... * (1 - \frac{1}{P_n})$

​			在 $i * P_j$ 的式子两边同时除以 $P_j$ 得到 $i = P_1^{a_1} * P_2^{a_2} *...P_{j-1}^{a_{j-1}}*P_{j+1}^{a_{j+1}}*...*P_n^{a_n}$

​			所以 $\phi (i) = i * (1 - \frac{1}{P_1}) * (1 - \frac{1}{P_2}) * ... * (1 - \frac{1}{P_{j-1}}) * (1 - \frac{1}{P_j+1}) * ... * (1 - \frac{1}{P_n})$

​			又 $P_j$ 是质数，所以 $\phi(P_j) = P_j * (1 - \frac {1}{P_j}) = P_j - 1$

​			$\phi(i * P_j) = \phi(i) * P_j * (1 - \frac{1}{P_j})= \phi (i) * \phi(P_j) = \phi(i) * (P_j - 1)$

**②当 $i$ 为 $P_j$ 的倍数时，则有 $\phi(i *P_j) =  \phi (i) * P_j$；**

证明：$i$ 是 $P_j$ 的倍数，所以 $i$ 的唯一分解中必有 $P_j$ 项，即 $i = P_1^{a_1} * P_2^{a_2} *... * P_j^{a_j}*...*P_n^{a_n}$，

​			则有 $\phi(i) = i * (1 - \frac{1}{P_1}) * (1 - \frac{1}{P_2}) * ... * (1 - \frac{1}{P_{j}}) * ... * (1 - \frac{1}{P_n})$

​			$i * P_j =  P_1^{a_1} * P_2^{a_2} *... * P_j^{a_j}*...*P_n^{a_n} * P_j= P_1^{a_1} * P_2^{a_2} *... * P_j^{a_{j+1}}*...*P_n^{a_n}$

​			所以 $\phi(i * P_j) = i * P_j *(1 - \frac{1}{P_1}) * (1 - \frac{1}{P_2}) * ... * (1 - \frac{1}{P_{j}}) * ... * (1 - \frac{1}{P_n})$

​			即：$\phi(i *P_j) =  \phi (i) * P_j$。

通过上面两个性质，我们可以从一个小数的欧拉函数推导得到一个大数的欧拉函数。

### 线性筛求欧拉函数

```c++
bool vis[N]; 			// 标记是否被筛过，被筛过则不是素数
int primes[N], phi[N]; 	// primes[j] 存储第j个质数， phi[i] 保存i的欧拉函数
void get_euler() {
    int cnt = 0; // 记录当前存储的质数的个数
    for (int i = 2; i < N; i++) {
        if (!vis[i]) primes[cnt++] = i, phi[i] = i - 1;
        for (int j = 0; j < cnt && i * primes[j] < N; j++) {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0) {
                phi[i * primes[j]] = phi[i] * primes[j];
                break;
            }
            phi[i * primes[j]]= phi[i] * (primes[j] - 1);
        }
    }
}
```

### 快速求大数欧拉函数

```c++
// 快速求大数欧拉函数模板
namespace GetPhi {
    typedef long long LL;
    LL ans = 1, Num[109], cnt;
    LL prime[15] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
    map<LL, LL> Keg;

    LL Mul(LL a, LL b, LL MOD) {
        LL tmp = a * b - (LL)((long double)a * b / MOD + 0.1) * MOD;
        return tmp < 0 ? tmp + MOD : tmp;
    }

    LL Qpow(LL a, LL b, LL MOD) {
        LL ans = 1;
        while (b) {
            if (b & 1) ans = Mul(ans, a, MOD);
            a = Mul(a, a, MOD);
            b >>= 1;
        }
        return ans;
    }

    LL gcd(LL a,LL b) {
    	return b == 0 ? a : gcd(b, a % b);
    }
	// 大数素性测试
    bool Miller_Rabin(LL n) {
        if (n == 2) return 1;
        if (n < 2 || n % 2 == 0) return 0;
        LL m = n - 1, l = 0;
        while (m % 2 == 0) m >>= 1, l++;
        for (int i = 0; i < 11; i++) {
            LL p = prime[i], w = Qpow(p, m, n);
            if (w == n-1 || w==1 || p == n) continue;
            for (int j = 1; j <= l; j++) {
                LL u = Mul(w, w, n);
                if (u == 1 && w != n - 1 && w != 1) return 0;
                w = u;
            }
            if (w != 1) return 0;
        }
        return 1;
    }
	// 大数因式分解
    LL Pollard_Rho(LL n, LL c) {
        LL x = (rand() + 1) % n, y = x, p = 1, k = 2;
        for (LL i = 1; p == 1; i++) {
            x = (Mul(x, x, n) + c) % n;
            p = x > y ? x - y : y - x;
            p = gcd(p, n);
            if (i == k) y = x, k = k + k;
        }
        return p;
    }

    void Solve(LL n) {
        if (n == 1) return;
        if (Miller_Rabin(n)) {
            if (!Keg[n]) Num[++cnt] = n;
            ++Keg[n]; return;
        }
        LL t = n;
        while (t == n) t = Pollard_Rho(n, rand() % (n - 1) + 1);
        Solve(t); Solve(n / t);
    }

    inline ll getPhiP(ll n) {
        Keg.clear();
        memset(Num, 0, sizeof Num);
        ans = 1; cnt = 0;
        Solve(n);
        for (int i = 1; i <= cnt; i++)
            ans = ans *(Num[i] - 1) * Qpow(Num[i], Keg[Num[i]] - 1, 2e18);
        return ans;
    }
} using GetPhi::getPhiP;
```



## 求幂 $a^b$

### 扩展欧拉定理求幂

适用情况：b很大，超出了 long long 的范围

```c++
ll ex_qpow(ll a, string b, ll mod) {
    ll p = phi(mod), ans = 0;
    for (ll i = 0; i < b.size(); i++) {
        ans = (ans * 10  + b[i] - '0') % p;
    }
    ans += p;
    return ans;
}
```

例题1：给定一个长度 $n$ 的数组以及若干次询问 $l$,  $r$，求 $a_{l} ^ {{a_{l+1}^{{a_{l+2}^{...}} ^{a_r} }}} mod \ m$

思路：递归降幂求解即可

```c++
ll get(ll l, ll r, ll m) { // 底数下标l，指数上限r, 模数m
    if (l == r || m == 1) return mo(a[l], m);
    return qpow(a[l], get(l + 1, r, phi(m)), m);
}
```

例题2：T组询问，每次询问给出一正整数 $p$（$p \le 1e7$），求 $2 ^ {{2^{{2^{...}} ^2 }}} mod \ p$

思路：和上一题一样，递归求解即可；递归的层次会不会很大？

​			不会，因为每次都是降幂，每次递归时模数 m 都会变成 phi(m)， 模数一直在变小，变成1时即可回递。

欧拉函数的2个性质：

① p > 2 时， $\phi(p)$ 为偶数；（通式可证）

② p 如果是偶数，$\phi (p)  \le p / 2$ ；（通式可证)

可以证明：递归层数为 $O(log \ p)$。

## 线性基

**定义：**

有一个集合 $S = \{ a_1, a_2,...,a_n\}$ ，$S$ 的线性基是满足下面条件的一个最小子集 $A = \{ a_1, a_2,...a_k \}$

$A$ 的所有子集的异或和的值域与 $T$ 的所有子集的异或和的值域相同，那么 $A$ 就是 $$ 的S线性基

**预备知识：**

1、**张成**：$S$ 的所有子集，其异或和的所有可能的结果组成的集合，为 $S$ 的张成，记作 $span(S)$。

2、**线性相关**：对于一个集合 $S$ ，如果存在一个元素 $S_j$，去除这个元素后得到的集合 $S'$ 的张成 $span(S')$中包含$S_j$，即 $S_j \in span(S')$，则称集合 $S$ 是线性相关的。如果不存在这样的 $S_j$，那么集合 $S$ 就是线性无关的。

3、**线性基**：有了上面两个名词，我们还可以这样定义线性基。

- $A \in span(S)$
- $A$ 是线性无关的

则集合A是集合S的线性基。

**性质：**

1、$A$ 是一个集合的线性基，那么它的任何真子集都不可能是线性基；

2、$S$ 中所有的向量都可以按唯一的方式表达为 $A$ 中元素的线性组合（也就是异或和）。

另一种说法的性质

- 原序列里面的任何一个数都可以由若干个线性基异或得到。
- 线性基里面任意一些数异或起来都不是0。
- 线性基里面数的个数是唯一的，并且保持性质一的前提下，数的个数是最少的。

**构造：**

我们令集合中的数为 $a[1],a[2],...,a[n]$，b[ ] 数组用来存储线性基里面的数。（下面的二进制的位数下标从0开始）

**第一种情况：**找到 $a[i]$ 的最高位，假如是第 $j$ 位，如果 $b[j]$ 还没有数，即 $b[j] = 0$，那么现在 b[ ] 数组中的数的张成肯定不包含 $a[i]$，那么我们就可以令 $b[j] = a[i]$。（然后利用已经在线性基里的最高位小于 $j$ 的把 $b[j]$ 二进制中的1给消掉，具体就是 $b[j]$ ^= $b[k]$（ $k < j$ && $b[j]$ 的第 $k$ 位为1 && $b[k] \ne 0$）,然后用同样的方法把大于 $j$ 的也消掉。这是高斯消元的步骤，主要是将上三角矩阵化为对角矩阵，即最简形式的线性基）

**第二种情况**：找到 $a[i]$ 的最高位，假如是第 $j$ 位，如果 $b[j]$ 已经有数，就判断现在线性基的张成$span(a[1], a[2],...,a[i-1])$ 包不包含 $a[i]$，如果包含，那么 $a[i]$ 就没有必要加进线性基。怎么判断呢，我们如果 $ai$ 的第 $j$ 位为 1 且 $b[j] \ne 0$，那么我们就把 $a[i]$ 的值异或上 $b[j]$，依次往后判断，直到 $ai$ 当前的最高位对应的$b[j] == 0$，就可以把 $a[i]$ 加入线性基，执行上面第一种情况的操作，或者 $a[i]$ 为0，就丢掉 $a[i]$ 。

**构造方法**

构造方法很简单，直接从高位开始往低位枚举，如果当前这位没有元素且待插入元素这位为1，则把元素插入到这里，然后退出。否则将其与该位已经存在的元素异或。

**线性基构造算法的性质**

1、任何一个元素都可以被线性基表示，且表方法唯一。
前者是线性基的性质，后者采取反证法，考虑不唯一，那么有两个子集能表示，消掉元素后得到存在两个不同的子集的异或和相等，与线性基定一矛盾。
2、线性基构造出来所需的元素等于秩。
3、构造出来线性基呈上三角矩阵，通过高斯消元（rebuild）可以将其变换为对角矩阵。

代码如下：

```c++
// 构造线性基（同时使用高斯消元化为对角矩阵，最简形式）
void create() {
    for (int i = 1; i <= n; i++) { // 遍历a数组,将每个元素插入到线性基中
        for (int j = 60; j >= 0; j--) { // 从高位到低位插入
            if ((1ll << j) & a[i]) {
                if (b[j] != 0) a[i] ^= b[j];
                else {
                    b[j] = a[i];
                    // 用下面行消掉本行
                    for (int k = j - 1; k >= 0; k--)
                        if (b[k] && ((1ll << k) & b[j]))
                            b[j] ^= b[k];
                    // 用本行消掉上行
                    for (int k = j + 1; k <= 60; k++)
                        if (((1ll << j) & b[k]))
                            b[k] ^= b[j];
                    break;
                }
            }
        }
    }
}
```

这段代码是维护一个对角矩阵，加入一行之后，先用下面的行消自己，然后再用自己去消上面的行。

我们来演示一下这个过程：

加入n = 5，a = {7,1,3,4,5}

初始矩阵： $\begin{bmatrix} &&& \end{bmatrix}$

插入7之后：$\begin{bmatrix} 1 & 1 & 1\end{bmatrix}$

插入3之后，为了维护对角矩阵，把 7 的低位消掉：$\begin{bmatrix} 1 & 0 & 0 \\ 0 & 1 & 1 \end{bmatrix}$

插入1之后，把1上面的行的低位都消掉：$\begin{bmatrix} 1 & 0 & 0 \\ 0 & 1 & 0 \\ 0 & 0 & 1 \end{bmatrix}$

然后就发现后面那几个数都已经包含在b数组的张成里了，加不进去了。

上述过程是把线性基维护成一个对角矩阵，其实我们还有一种代码量比较少的线性基的构造方法，就是只把矩阵消成上三角矩阵，这样的话同样可以知道哪一位存在于线性基内。

**模板**

```c++
struct Linebasis {
    ll p[65], b[65];
    // p数组：线性基
    // b数组：高斯消元后的线性基矩阵，从低位到高位保存
    int cnt;
    bool flag;
    // cnt：记录线性基里面有多少个数,即构造线性基需要的元素数量，也是矩阵的秩
    // 2 ^ cnt 就是这个线性基所有子集异或和能构成的不同元素的个数（包括零）
    // 从线性基的性质来看，理论上是不可以表示0的，所以理论可以表示的个数是 (2 ^ cnt) - 1
    // 如果能表示的话，则理论个数是 2 ^ cnt
    // flag：判断线性基是否能表示0
    // flag = true时，说明插入n个数时，有一个或多个数在插入过程中，插入失败，且未进行cnt++
    // 则最终结果：必有矩阵的秩cnt < n
    // 判断线性基能否表示0，方法：n的大小与秩的大小cnt是否相等，相等说明线性无关，即不能表示0 

    // 线性基初始化
    void init() {
        memset(p, 0, sizeof(p));
        memset(b, 0, sizeof(b));
        cnt = 0;
        flag = false;
    }
	
    // 线性基插入
    // 返回 false 即最后 x = 0，说明可以用已有线性基的元素表示 x，无需插入到线性基中
    // 返回 true 即最后 x > 0，不可以用已有线性基元素的元素表示 x，已经插入到线性基中
    bool insert(ll x) {
        for (int i = 62; i >= 0; i--) {
            if ((x >> i) & 1) {
                if (!p[i]) {
                    p[i] = x;
                    break;
                }
                x ^= p[i];
            }
        }
        if (x) cnt++;
        else flag = true;
        return x > 0;
    }
	
    // 线性基相加，即线性基合并
    Linebasis operator + (const Linebasis & r) const {
        Linebasis res = r;
        for (int i = 0; i <= 62; i++) {
            if (p[i]) res.insert(p[i]);
        }
        return res;
    }

    // 查询线性基可以表示的最大值
    ll querymax(ll x = 0) {
        ll res = x;
        for (int i = 62; i >= 0; i--) {
            if ((res ^ p[i]) > res) res ^= p[i];
        }
        return res;
    }
	
    // 查询线性基可以表示的最小值
    ll querymin() {
        // 特判能否表示0，能表示则最小值是0
        if (flag) return 0;
        for (int i = 0; i <= 62; i++){
            if (p[i]) return p[i];
        }
        return 0;
    }
	
    // 高斯消元重建，化成最简形式
    void rebuild() {
        for (int i = 62; i >= 0; i--) {
            for (int j = i - 1; j >= 0; j--) {
                if ((p[i] >> j) & 1) p[i] ^= p[j];
            }
        }
        cnt = 0;
        for (int i = 0; i <= 62; i++) {
            if(p[i]) b[cnt++] = p[i];
        }
    }
	
    // 查询线性基可以表示的第k小的数
    ll kthmin(ll k) {
        // flag = true，即可以表示0, k--，相当于在后面判断 k > (1ll << cnt)
        // 也可使得如果k = 1,则说明求的是第1小的数，第一小的数刚好是0
        if(flag) k--;
        ll res = 0;
        if (!k) return 0;
        if (k > (1ll << cnt) - 1ll) return -1;
        for (int i = 62; i >= 0; i--){
            if((k >> i) & 1) res ^= b[i];
        }
        return res;
    }
} sol;

int main() {
    int n, T, q;
    ll k;
    scanf("%d", &T);
    for(int kase = 1; kase <= T; kase++) {
        sol.init();
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            ll x;
            scanf("%lld", &x);
            sol.insert(x);
        }
        scanf("%d", &q);
        printf("Case #%d:\n", kase);
        sol.rebuild();
        while(q--){
            scanf("%lld", &k);
            printf("%lld\n", sol.kthmin(k));
        }
    }
    return 0;
}
```



**线性基的用途：**

### 不同异或和的个数

求出这组数的线性基，线性基里数的个数为cnt，答案就为 $2^ {cnt} $（包括0，如果n == cnt则不能表示0，需要减1）

（如果可以不任何选择元素，且不选择任何元素的结果是0的话， 答案就是 $2 ^ {cnt}$

hihocoder1723 子树统计

### 是否能异或某个值

用插入的方法判断是否能异或出某个值 x，如果不能插入，说明已有的线性基能表示 x。

### 最大值

求异或集合中的最大值

如果消成对角矩阵的话，直接把线性基中的所有元素异或起来即可。但是对于上三角矩阵，异或之前判断一下是否能变大。

还可以求一个数 x 与集合中某些数异或的最大值，只用把初值设为x就行了，单纯求最大值时最初始值设为0.

```c++
ll QueryMax(ll x) {
    ll ans = x;
    for (int i = 62; i >= 0; i--)
        if ((ans ^ b[i]) > ans)
            ans ^= b[i];
    return ans;
}
```

### 最小值

最小值就是最低位上的线性基，特殊情况，如果这个线性基能表示0，则这个最小值是0

```c++
ll QueryMin() {
	if (flag) return 0;
	for (int i = 0; i <= 62; i++)
		if (b[i]) return b[i];
	return 0;
}
```

### 第K小值

这时候用构造出的上三角矩阵就不能解决这个问题了，我们要把上三角矩阵变换成对角矩阵，然后再把不为零的都按顺序拿出来。这时候矩阵已经变成对角矩阵（至少是行最简形矩阵），我们异或上某一行的值，答案就会变大一点。我们可以想象，从一个数组 a = {8, 4, 2, 1}中选出几个，求能组成第k小的值是多少，利用二进制的性质，如果k 的二进制第 $i$ 位为 1，我们就加上数组里第 $i$ 大的数。这里的异或上一个值也会变大一点，所以可以用同样的思想。记得要特判是否存在0，方法是看 n 的大小 和 秩cnt的大小 是否相等，相等则说明线性无关，即不存在。

## 组合数

### 递推求组合数

方法：杨辉三角递推

**复杂度：**

​			预处理：$O(nm)$

​			查询：$O(1)$

```c++
ll C[N][M];
void get_Com(int n, int m, int p) {
    for (int i = 0; i <= n; i++) C[i][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
            if (C[i][j] >= p) C[i][j] -= p; // 也可直接 C[i][j] % p
        }
    }
}
```

递推的同时还能求出 组合数C 与 模数P 的大小关系

```c++
ll C[N][M];
bool isOver[N][M];
void get_Com(ll n, ll p) {
	// 递推打表求组合数C(n, k)
    // 顺带记录 C[n][m] 与 phi(p) 的比较结果 isOver
    // 便于使用欧拉降幂
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= 30; j++)
			isOver[i][j] = 0;
	for (int i = 0; i <= n; i++) C[i][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			C[i][j] = C[i - 1][j];
			C[i][j] += C[i - 1][j - 1];
			isOver[i][j] |= isOver[i - 1][j] + isOver[i - 1][j - 1];
			if (C[i][j] >= p) {
				C[i][j] -= p;
				// C[i][j] >= phi(p)
				isOver[i][j] = 1;
			}
		}
	}
}
```

### 逆元求组合数

**模板1**

适用条件：

mod 必须为质数，mod可以很大。

mod = 1e9 + 7，其他模数不一定能保证正确，可以尝试

mod = 10007 不使用，原因未知

复杂度：

​			预处理：$O(n)$

​			查询：$O(1)$

```c++
const int N = 2e6 + 10, mod = 1e9 + 7;

ll n, m;
ll fac[N], inv[N];

ll qpow(ll a, ll b) {
    ll res = 1;
    while(b) {
        if(b & 1)   res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

void init() {
    fac[0] = 1; //！！！别忘记初始化
    for(int i = 1; i < N; i++) 
        fac[i] = (fac[i - 1] * i) % mod;
    inv[N - 1] = qpow(fac[N - 1], mod - 2);
    for(int i = N - 2; i >= 0; i--)
        inv[i] = inv[i + 1] * (i + 1) % mod;
}

ll C(int n, int m) { // 组合数C(n, m)
    if (n < 0 || m < 0 || m > n) return 0;
    if (m == 0 || m == n) return 1;
    return ((fac[n] * inv[m]) % mod * inv[n - m]) % mod;
}

int main() {
	init();
	cin >> n >> m;
	cout << C(n, m) << endl;
}
```

**模板2（推荐）**

适用条件：

mod 必须为质数，mod可以很大。

理论上模数只要是质数即可。

复杂度：

​			预处理：$O(n*log(mod))$

​			查询：$O(1)$

```c++
const int N = 2e6 + 10, mod = 10007;

ll n, m;
ll fac[N], inv[N];

ll qpow(ll a, ll b) {
    ll res = 1;
    while(b) {
        if(b & 1)   res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

void init() {
	inv[0] = fac[0] = 1; 
    for(int i = 1; i < N; i++) {
       fac[i] = (fac[i - 1] * i) % mod;
       inv[i] = qpow(fac[i], mod - 2);
    } 
}

ll C(int n, int m) { // 组合数C(n, m)
    if (n < 0 || m < 0 || m > n) return 0;
    if (m == 0 || m == n) return 1;
    return ((fac[n] * inv[m]) % mod * inv[n - m]) % mod;
}

int main() {
	init();
	cin >> n >> m;
	cout << C(n, m) << endl;
}
```

**模板3**

适用条件：

mod 必须为质数，mod可以很大。

理论上模数只要是质数即可。

相比较模板2，这个模板主要用于查询少的情况。

复杂度：

​			预处理：$O(n)$

​			查询：$O(log(mod))$

```c++
const int N = 2e6 + 10, mod = 10007;

ll n, m;
ll fac[N], inv[N];

ll qpow(ll a, ll b) {
    ll res = 1;
    while(b) {
        if(b & 1)   res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

void init() {
	inv[0] = fac[0] = 1; 
    for(int i = 1; i < N; i++) {
       fac[i] = (fac[i - 1] * i) % mod;
    } 
}

void get_inv(int n, int m) {
    inv[m] = qpow(fac[m], mod - 2);
    inv[n - m] = qpow(fac[n - m], mod - 2);
}

ll C(int n, int m) { // 组合数C(n, m)
    if (n < 0 || m < 0 || m > n) return 0;
    if (m == 0 || m == n) return 1;
    get_inv(n, m);
    return ((fac[n] * inv[m]) % mod * inv[n - m]) % mod;
}

int main() {
	init();
	cin >> n >> m;
	cout << C(n, m) << endl;
}
```

