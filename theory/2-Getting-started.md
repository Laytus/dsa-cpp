# 2. Getting Started

## 2.1 Insetion sort

**Input**: A sequence of $n$ numbers $\langle a_1, a_2, \dots, a_n \rangle$.

**Output**: A permutation (reordering) $\langle a'_1, a'_2, \dots, a'_n \rangle$ of the input sequence such that $a'_1 \leq a'_2 \leq \dots a'_n$.

The numbers that we wish to sort are also known as the **keys**.

The **searching problem**:

**Input**: A sequence of $n$ numbers $A = \langle a_1, a_2, \dots, a_n \rangle$ and a value $\nu$.

**Output**: An index $i$ such that $\nu = A[i]$ or the special value $\text{NIL}$ if $\nu$ does not appear in $A$.

* **`linear search`**

---

## 2.2 Analyzing algorithms

- Predicting the resources that the algorithms requires.
- Occasionally, resources such as *memory*, *communication bandwidth*, or *computer hardware* are of primary concern, but most often it is *computational time* that we want to measure.

- We shall assume ageneric one-processor, **random-access machine (RAM)** model of computation as our implementation technology.
- In the RAM model, instructions are executed one after another, with no concurrent operations.
- The RAM model contains instructions commonly found in real computers:
    - arithmetic (such as *add*, *substract*, *multiply*, *divide*, *remainder*, *floor*, *ceiling*)
    - data movement (*load*, *store*, *copy*)
    - control (*conditional and unconditional branch*, *subroutine call and return*)
- Each such instruction takes a *constant amount of time*.
- The data types in the RAM model are **integer** and **floating point** (for storing real numbers).

* Memory hierarchy (model caches or virtual memory)

**Input size**
: for many problems, the most natural measure is the *number of items in the input* – for example, the array size $n$ for sorting.
: for many other problems, the best measure is the *total number of bits* needed to represent the input in ordinary binary notation.
: sometimes, it is more appropriate to describe the input with two numbers rather than one. For instance, if the input to an algorithm is a graph, the input size can be described by the numbers of verices and edges in the graph.

**Running time** of an algorithm
: the number of primitive operations or "steps" executed.

Notion of **step**
: a constant amount of time is required to execute each line of our code. One line may take a different amount of time than another line, but we shall assume that each execution of the $i$th line takes time $c_i$, where $c_i$ is a constant.

- **Worst-case running time**
- **Average-case running time**

- **Rate of growth** or **Order of growth**:
    - We consider only the leading term of a formula, since the lower-order term are relatively insignificant for large values of $n$.
    - We also ignore the leading term's constant coefficient, since constant factors are less significant than the rate of growth in determining computational efficienty for large inputs.
    - We shall use $\Theta(*)$-notation (pronunced "theta of $*$")


## 2.3 Designing algorithms

### The divide-and-conquer approach

- **Recursive** in structure
- Three steps at each level of the recursion:
    - **Divide** the problem into a number of subproblems that are smaller instances of the same problem.
    - **Conquer** the subproblems by solving them recursively. If the subproblem sizes are samll enough, however, just solve the subproblems in a straighforward manner.
    - **Combine** the solutions to the subproblmes into the solution for the original problem.


- The **merge sort** algorithm closely follows the divide-and conquer paradigm:
    - **Divide:** Divide the $n$-element sequence to be sorted into two subsequences of $n/2$ elements each.
    - **Conquer:** Sort the two subsequences recursively using merge sort.
    - **Combine:** Merge the two sorted subsequences to produce the sorted answer.
    - The recursion "bottoms out" when the sequence to be sorted has length $1$, in which case there is no work to be done.