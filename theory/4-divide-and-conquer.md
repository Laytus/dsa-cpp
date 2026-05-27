# 4. Divide-and-Conquer

- In divide-and-conquer, we solve a problem recursively, applying three steps at each level of the recursion:

    - **Divide** the problem into a number of subproblems that are smaller instances of the same problem.
    - **Conquer** the subproblems by solving them recursively. If the subproblems sizes are small enoigh, however, just solve the subproblems in a straightforward manner.
    - **Combine** the solutions to the subproblems into the solution for the original problem.

- **Recursive case**: when the subproblems are large enough to solve recursively.
- Once the subproblems become small enough that we no longer recurse, we say that the recursion *"bottoms out"* and that we have gotten down to the **base case**.
- Sometimes, in addition to subproblems that are samller instances of the same problem, we have to solve subrpoblems that are not quite the same as the original problem. We consider solving such subproblems as part of the combine step.


### Recurrences

**Recurrence**
: an equation or inequality that describes a function in terms of its values on smaller inputs.

- E.g., the worst-case running time $T(n)$ of the `MERGE-SORT` procedure by the recurrence:

$$
T(n) = \begin{cases}
   \Theta(1) &\text{if } n = 1, \\
   2 T(n/2) + \Theta(n) &\text{if } n > 1.
\end{cases}
$$

whose solution we claimed to be $T(n) = \Theta(n lg{n})$.

- Recurrences can take many forms, and divide subproblems into unequal sizes, such as a 2/3-to-1/3 split.

- Three methods for solving recurrences – that is, for obtaining asymptotic "$\Theta$" or "$O$" bounds on the solution:

    - In the **substitution method**, we guess a bound and then use mathematical induction to prove our guess correct.
    - The **recursion-tree method** converts the recurrence into a tree whose nodes represent the costs incurred at various levels of the recursion. We use techniques for bounding summations to solve the recurrence.
    - The **maste method** provides bounds for recurrences of the form:

$$
T(n) = a T(n/b) + f(n)
$$

where $a \geq 1$, $b > 1$, and $f(n)$ is a given function. 
- This characterizes a divide-and-conquer algorithm that creates $a$ *subproblems*, each of which is $1/b$ the size of the original problem, and in which the divide and combine steps together take $f(n)$ time.

- Occasionally, we shall see recurrences that are not equalities but rather inequalities. 
- Such recurrences state only an upper or lower bound on $T(n)$, so we will couch its solutions uisng $O$-notation or $\Omega$-notation.

### Technicalities in recurrences

- We usually omit statements of the boundary conditions of recurrences and assume that $T(n)$ is constant for small $n$.
- E.g., when we call `MERGE-SORT` on $n$ elements when $n$ is odd.

- When we state and solve recurrences, we often omit *floors*, *ceilings*, and *boundary conditions*.

---

## 4.1 The maximum-subarray problem

- **Maximum subarray**: the nonempty, contiguous subarray of an array whose values have the largest sum.

#### `FIND-MAXIMUM-SUBARRAY`

- **Running time:**

$$
\begin{align*}
T(n) &= \Theta(1) + 2 T(n/2) + \Theta(n) + \Theta(1) \\
     &= 2 T(n/2) + \Theta(n)
\end{align*}
$$

$$
T(n) = \begin{cases}
   \Theta(1) &\text{if } n = 1, \\
   2 T(n/2) + \Theta(n) &\text{if } n > 1.
\end{cases}
$$

- Solution: $T(n) = \Theta(n \text{lg}{n})$

---

## 4.2 Strassen's algorithm for matrix multiplication

### Strassen's method

