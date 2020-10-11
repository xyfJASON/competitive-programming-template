<h1 style="text-align: center"> min_25筛 </h1>

<h2 style="text-align: center"> Extended Eratosthenes Sieve </h2>



解决**一类积性函数**前缀和问题。

要求满足：$f(p)$ 是一个关于 $p$ 的低次多项式，可以快速求值；$f(p^c)$ 可以快速求值。



**Notation**：

- $p$：某质数
- $x/y$：$\left\lfloor\frac{x}{y}\right\rfloor$ 
- $\text{isprime}(n)=\begin{cases}1&n\,是质数\\0&n\,不是质数\end{cases}$ 
- $p_k$：第 $k$ 小的质数，特别定义 $p_0=1$. 
- $\text{lpf}(n)$：$n$ 的最小质因数，特别定义 $\text{lpf}(1)=1$. 
- $F_\text{prime}(n):=\sum\limits_{2\leqslant p\leqslant n}f(p)$. 即 $n$ 以内的所有质数处函数值之和。
- $F_k(n):=\sum\limits_{i=2}^n[p_k\leqslant \text{lpf}(i)]f(i)$. 即 $2\sim n$ 中最小质因数大于等于 $p_k$ 的那些数的函数值之和。



**Idea**：

我们需要的前缀和即是 $F_1(n)+f(1)=F_1(n)+1$. 

对于 $F_k(n)$，枚举最小质因数及其次数可得递推式：
$$
\begin{align}
F_k(n)&=\sum_{i=2}^n[p_k\leqslant \text{lpf}(i)]f(i)\\
&=\sum_{\substack{i\geqslant k\\p_i^2\leqslant n}}\sum_{\substack{c\geqslant 1\\p_i^c\leqslant n}}f(p_i^c)\Big(F_{i+1}(n/p_i^c)+[c>1]\Big)+\sum_{\substack{i\geqslant k\\p_i\leqslant n}}f(p_i)\\
&=\sum_{\substack{i\geqslant k\\p_i^2\leqslant n}}\left[\sum_{\substack{c\geqslant 1\\p_i^c\leqslant n}}f(p_i^c)F_{i+1}(n/p_i^c)+\sum_{\substack{c>1\\p_i^c\leqslant n}}f(p_i^c)\right]+F_{\text{prime}}(n)-F_{\text{prime}}(p_{k-1})\\
&=\sum_{\substack{i\geqslant k\\p_i^2\leqslant n}}\sum_{\substack{c\geqslant 1\\p_i^{c+1}\leqslant n}}\Big(f(p_i^c)F_{i+1}(n/p_i^c)+f(p_i^{c+1})\Big)+F_{\text{prime}}(n)-F_{\text{prime}}(p_{k-1})
\end{align}
$$

> 第二行：根据最小质因数的若干次方可以将所有数不多不漏地进行分类（这里若干次方指最多能到的次数，即剩下的数最小质因数应变大），这里枚举 $p_i^c$ 作为“最小质因数的若干次方”，提出该公因数，剩下：$F_{i+1}(n/p_i^c)+1$。而我们在这里把质数单独拿出来放在最后处理。
>
> 第三行：内和式分配律
>
> 第四行：进行一个简单的变量代换，再合并，这里需要注意一点：
> $$
> \sum\limits_{\substack{c\geqslant 1\\p_i^c\leqslant n}}f(p_i^c)F_{i+1}(n/p_i^c)=\sum\limits_{\substack{c\geqslant 1\\p_i^{c+1}\leqslant n}}f(p_i^c)F_{i+1}(n/p_i^c)
> $$
> 因为对于 $p_i^c\leqslant n$ 且 $p_i^{c+1}>n$ 的那些 $p_i$ 而言，必有 $p_i^cp_{i+1}>p_i^{c+1}>n$，所以 $n/p_i^c$ 没有比 $p_i$ 更大的质因子了，也即 $F_{i+1}(n/p_i^c)=0$. 

假若我们已经求得 $F_{\text{prime}}(n)$，那么递归可解 $F_k(n)$. 

<br>

我们现在考虑如何计算 $F_\text{prime}(n)$. 注意，根据上述 $F_k(n)$ 的推导，我们实际要求的是 $F_\text{prime}$ 在 $n,\frac{n}{2},\cdots,\frac{n}{\sqrt{n}},\sqrt{n},\cdots,2,1$ 这 $O(\sqrt{n})$ 个位置处的值（ $F_\text{prime}(p_k)$ 可以预处理）。

设 $f(p)$ 是一个关于 $p$ 的低次多项式 $f(p)=\sum\limits_ia_ip^{c_i}$，那么 $F_{\text{prime}}(n)=\sum\limits_{2\leqslant p\leqslant n}f(p)=\sum\limits_ia_i\sum\limits_{2\leqslant p\leqslant n}p^{c_i}$，分开考虑每个 $i$ 的答案，问题转化为：给定 $n,s$，求 $\sum\limits_{2\leqslant p\leqslant n}p^s$. 

设 $G_k(n):=\sum\limits_{i=1}^n[p_k<\text{lpf}(i)\or \text{isprime}(i)]i^s$，即<u>当线性筛筛完 $p_k$ 时，剩下的没被筛到的所有数的 $i^s$ 和</u>（没被筛到的数包括所有质数以及最小质因数 $>p_k$ 的合数）。于是我们有：
$$
\begin{cases}
G_k(n)=G_{k-1}(n)&p_k^2>n\\
G_k(n)=G_{k-1}(n)-p_k^s\left[G_{k-1}(n/p_k)-G_{k-1}(p_{k-1})\right]&p_k^2\leqslant n
\end{cases}
$$
边界条件：$G_0(n)=\sum\limits_{2\leqslant i\leqslant n}i^k$. 

> 第一种情况，$p_k^2>n$，那么 $p_k$ 这个数不会筛掉任何一个数，所以 $G_k(n)=G_{k-1}(n)$. 
>
> 第二种情况，$p_k^2\leqslant n$，那么 $p_k$ 会把最小质因数是 $p_k$ 的那些合数筛掉，即从 $G_{k-1}(n)$ 中减去这些数的贡献。它们的贡献都有一个 $p_k^s$ 因子，提出来，括号内的部分容斥一下：（所有以 $p_k$ 为最小质因子的合数的贡献加上质数的贡献）减去（ $p_1\sim p_{k-1}$ 这些质数的贡献）。前者是 $G_{k-1}(n/p_k)$，后者是 $G_{k-1}(p_{k-1})=\sum\limits_{i=1}^{k-1}p_i^s$. 

而我们要求的便是：$G_K(n)=\sum\limits_{2\leqslant p\leqslant n}p^s$，其中 $p_K$ 是最大的小于 $\sqrt{n}$ 的质数。



**Complexity**：$O(n^{1-\epsilon})$ 



## 解题步骤

1. 考察所求积性函数在质数处的值 $f(p)$，写作 $p$ 的多项式；
2. 线性筛将筛出 $\sqrt n$ 以内的质数，预处理 $s$ 次方前缀和，其中 $s$ 是多项式每一项的次数；
3. 对多项式每一项



## 莫比乌斯函数前缀和