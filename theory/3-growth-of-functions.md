# 3. Growth of Functions

## 3.1 Asymptotic notation

- We are concerned with how the running time of an algorithm icreases with the size of the input *in the limit*, as the size of the input increases without bound.
- Usually, an algorithm that is asymptotically more efficient will be the best choice for all but very small inputs.

- The functions to which we apply asymptotic notation will usually characterize the running times of algorithms.

### $\Theta$-notation

- For a given function $g(n)$, we denote by $\Theta{(g(n))}$ teh *set of functions*:

$\Theta{(g(n))}$ = {$f(n)$: there exist positive constants $c_1$, $c_2$, and $n_0$ such that $0 \leq c_1 g(n) \leq f(n) \leq c_2 g(n)$ for all $n \geq n_0$}.

- $g(n)$ is an **asymptotically tight bound** for $f(n)$.
- The definition of $\Theta{(g(n))}$ requires that every memeber $f(n) \in \Theta{(g(n))}$ be **asymptotically nonnegative**, that is, that $f(n)$ be nonnegative whenever $n$ is sufficiently large.

### $O$-notation

- When we have only an **asymptotic upper bound**, we use $O$-notation.
- For a given function $g(n)$, we denote by $O(g(n))$ (pronounced "big-oh of $g$ of $n$" or sometimes just "oh of $g$ of $n$") the set of functions:

$O(g(n))$ = {$f(n)$: there exist positive constants $c$, and $n_0$ such that $0 \leq f(n) \leq c g(n)$ for all $n \geq n_0$}.

- $\Theta{(g(n))} \sube O(g(n))$

- Since $O$-notation describes an upper bound, when we use it to bound the worst-case running time of an algorithm, we have a bound on the running time of the algorithm on every input.


### $\Omega$-notation

- $\Omega$-notation provides an **asymptotic lower bound**.

- For a given function $g(n)$, we denote by $\Omega(g(n))$ (pronounced "big-omega of $g$ of $n$" or sometimes just "omega of $g$ of $n$") the set of functions:

$\Omega(g(n))$ = {$f(n)$: there exist positive constants $c$, and $n_0$ such that $0 \leq c g(n) \leq f(n)$ for all $n \geq n_0$}.

- $\Theta{(g(n))} \sube \Omega(g(n))$

### Asymptotic notation in equations and inequalities

- In some cases, asymptotic notation appears on the left-hand side of an equation, as in:

$$
2n^2 + \Theta(n) = \Theta(n^2)
$$

- We interpret such equations using the following rule: *No matter how the anonymous functions are chosen on the left of the equal sign, there is a way to choose the anonymous functions on the right of the equal sign to make the equation valid*.


### $o$-notation

- We use $o$-notation to denote an upper bound that is not asymptotically tight. We formally define $o(g(n))$ ("little-oh of $g$ of $n$") as the set:

$o(g(n))$ = {$f(n)$ : for any positive constant $c > 0$, there exists a constant $n_0 > 0$ such that $0 \leq f(n) < cg(n)$ for all $n \geq n_0$}.

- For example, $2n = o(n^2)$, but $2n^2 \ne o(n^2)$.

- In $f(n) = o(g(n))$, the bound $0 \leq f(n) < c g(n)$ holds for *all* constants $c > 0$.
- In $o$-notation, the function $f(n)$ becomes insignificant relative to $g(n)$ as $n$ approaches infinity; that is:

$$
\lim_{n \to \infty}{\frac{f(n)}{g(n)}} = 0
$$

- The anonymous functions are restricted to be asymptotically nonnegative.


### $\omega$-notation

- By analogy, $\omega$-notation is to $\Omega$-notation as $o$-notation is to $O$-notation.
- We use $\omega$-notation to denote a lower bound that is not asymptotically tight.
- One way to define it is by:

$f(n) \in \omega(g(n))$ if and only if $g(n) \in o(f(n))$.

Formally, however, we define $\omega(g(n))$ ("little-omega of $g$ of $n$") as the set:

$\omega(g(n))$ = {$f(n)$ : for any positive constant $c > 0$, there exists a constant $n_0 > 0$ such that $0 \leq c g(n) < f(n)$ for all $n \geq n_0$}.

- The relation $f(n) = \omega(g(n))$ implies that:

$$
\lim_{n \to \infty}{\frac{f(n)}{g(n)}} = \infty
$$

- if the limit exists. That is, $f(n)$ becomes arbitrarily large relative to $g(n)$ as $n$ approaches inifinity.


### Comparing functions

#### Transitivity

$f(n) = \Theta(g(n))$ and $g(n) = \Theta(h(n))$ imply $f(n) = \Theta(h(n))$
$f(n) = O(g(n))$ and $g(n) = O(h(n))$ imply $f(n) = O(h(n))$
$f(n) = \Omega(g(n))$ and $g(n) = \Omega(h(n))$ imply $f(n) = \Omega(h(n))$
$f(n) = o(g(n))$ and $g(n) = o(h(n))$ imply $f(n) = o(h(n))$
$f(n) = \omega(g(n))$ and $g(n) = \omega(h(n))$ imply $f(n) = \omega(h(n))$

#### Reflecivity:

$f(n) = \Theta(f(n))$,
$f(n) = O(f(n))$,
$f(n) = \Omega(f(n))$,

#### Simmetry

$f(n) = \Theta(g(n))$ if and only if $g(n) = \Theta(f(n))$

#### Transpose symmetry

$f(n) = O(g(n))$ if and only if $g(n) = \Omega(f(n))$,
$f(n) = o(g(n))$ if and only if $g(n) = \omega(f(n))$,

$f(n) = O(g(n))$ is like $a \leq b$,
$f(n) = \Omega(g(n))$ is like $a \geq b$,
$f(n) = \Theta(g(n))$ is like $a = b$,
$f(n) = o(g(n))$ is like $a < b$,
$f(n) = \omega(g(n))$ is like $a > b$,

- We say that $f(n)$ is **asymptotically smaller** than $g(n)$ if $f(n) = o(g(n))$, and $f(n)$ is **asumptotically larger** than $g(n)$ if $f(n) = \omega(g(n))$.

- One property of real numbers, however, does not carry over to asymptotic notation:

**Trichotomoy:** For any two real numbers $a$ and $b$, exactly one of the following must hold: $a < b$, $a = b$, or $a > b$.

- Although any two real numbers can be compared, not all functions are asymptotically comparable.
- That is, for two functions $f(n)$ and $g(n)$, it may be the case that neither $f(n) = O(g(n))$ nor $f(n) = \Omega(g(n))$ holds.
- Example: functions $n$ and $n^{1 + \sin{n}}$.

---

## 3.2 Standard notations and common functions

#### Monotonicity

- **Monotonically increasing**: if $m \leq n$ implies $f(m) \leq f(n)$
- **Monotonically decreasing**: if $m \leq n$ implies $f(m) \geq f(n)$
- **Strictly increasing**: if $m < n$ implies $f(m) < f(n)$
- **Strictly decreasing**: if $m > n$ implies $f(m) > f(n)$

#### Floors and ceilings

- The greatest integer less than or equal to $x$ by $\lfloor x \rfloor$ ("the floor of $x$")
- The least integer greater than or equal to $x$ by $\lceil x \rceil$ ("the ceiling of $x$")

- The floor function is monotonically increasing, as is the ceiling function.

#### Modular arithmetic

- For any integer $a$ and any positive integer $n$, the value $a$ mod $n$ is the **remainder** (or **residue**) of the quotient $a / n$.

#### Polynomials

- Given a nonnegative integer $d$, a **polynomial in $n$ of degree $d$** is a function $p(n)$ of the form:

$$
p(n) = \sum^{d}_{i = 0}{a_i n^i}
$$

- Constants $a_0, a_1, \dots, a_d$ are the **coefficients** of the polynomial.
- $a_d \ne 0$.

- A polynomial is *asymptotically positive* if and only if $a_d > 0$.
- For an asymptotically positive polynomial $p(n)$ of degree $d$, we have $p(n) = \Theta(n^d)$.
- For any real constant $a \geq 0$, the function $n^a$ is monotonically increasing.
- For any real constant $a \leq 0$, the function $n^a$ is monotonically decreasing.
- We say that a function $f(n)$ is **polynomially bounded** if $f(n) = O(n^k)$ for some constant $k$.

#### Exponentials

$$
\lim_{n \to \infty}{\frac{n^b}{a^n}} = 0
$$

$$
n^b  = o(a^n)
$$

- Any exponential function with a base strictly greater than 1 grows faster than any polynomial function.

#### Logarithms

- A fucntion $f(n)$ is **polylogarithmically bounded** if $f(n) = O(lg^{k}{n})$ for some constant $k$.

$$
\lim_{n \to \infty}{\frac{lg^{b}{n}}{(2^a)^{lg{n}}}} = \lim_{n \to \infty}{\frac{lg^{b}{n}}{n^a}} = 0
$$

$$
lg^{b}{n} = o(n^a)
$$

- Any positive polynomial function grows faster than any polylogarithmic function.

#### Factorials

- **Stirling's approximation**:

$$
n! = \sqrt{2 \pi n} \left(\frac{n}{e} \right)^{n} \left(1 + \Theta{\left(\frac{1}{n} \right)} \right)
$$

- Where $e$ is the base of the natural logarithm, gives us a tighter upper bound, and a lower bound as well.

$$
\begin{align*}
n! &= o(n^n) \\
n! &= \omega(2^n) \\
lg(n!) &= \Theta(n lg{n})
\end{align*}
$$


#### Functional iteration

- $f^{(i)}(n)$ to denote the function $f(n)$ iteratively applied $i$ times to an initial value of $n$.

$$
f^{(i)}(n) = \begin{cases}
   n &\text{if } i = 0, \\
   f(f^{(i - 1)}(n)) &\text{if } i > 0.
\end{cases}
$$

##### The iterated logarithm function

- $lg^{*} n$ ("log star of $n$").
- $lg^{(i)}{n}$ is defined only if $lg^{(i - 1)}{n} > 0$.
- We define the iterated logarithm function as:

$lg^{*}{n} = min \lbrace i \geq 0 : lg^{(i)}{n} \leq 1 \rbrace$

- The iterated logarithm is a *very* slowly growing function.


#### Fibonacci numbers