# 11. Hash Tables

## 1. Direct-address tables

- We assume that no two elements have the same key

- Dynamic set: we use an array or `direct-address table`
- **Slot:** each position on the set. Corresponds to a **key**.

```
DIRECT-ADDRESS-SEARCH(T, k)
    return T[k]
```

```
DIRECT-ADDRESS-INSERT(T, k)
    T[x.key] = x
```

```
DIRECT-ADDRESS-DELETE(T, k)
    T[x.key] = NIL
```

- Each of these operations take only $O(1)$ time.

---

## 2. Hash tables

- Set `K` of keys strored in a dictionary is much smaller than the universe `U` of all possible keys.
- A hash table requires much less storage.

- An element is stored in slot `h(k)`.
- A **hash function `h`** is used to compute the slot from the key `k`.
- `h` maps the universe `U` of keys into the slots of a **hash table** $T[0 \dots m - 1]$

$$
h: U \rightarrow \lbrace 0, 1, \dots, m - 1 \rbrace
$$

- The size `m` of the hash table is typically much less than $|U|$
- An element with key $k$ ***hashes*** to slot $h(k)$
- $h(k)$ is the ***hash value*** of key $k$.

- ***Collision:*** two key may hash to the same slot.

- Because $|U| > m$ there must be at least two keys that produce the same hash value.

### Independent uniform hashing

### Collision resolution by chaining

- ***Chaining:*** we place all the elements that hash to the same slot into the same linked list.

```
CHAINED-HASH-INSERT(T, x)
    insert x at the head of list T[h(x.key)]
```

```
CHAINED-HASH-SEARCH(T, k)
    search for an element with key k in list T[h(k)]
```

```
CHAINED-HASH-DELETE(T, x)
    delete x from the list T[h(x.key)]
```

Worst-case running times:
- *Insertion*: $O(1)$.
- *Searching*: proportional to the length of the list.
- *Delete*: $O(1)$, if the lists are doubly linked.

- *Singly linked list*:

```cpp
struct Node {
    int key;
    Node* next;
}
```

- *Doubly linked list*:

```cpp
struct Node {
    int key;
    Node* prev;
    Node* next;
}
```

### Analysis of hashing with chaining

- **Load factor $\alpha$:** $n/m$, for a given hash table $T$ with $m$ slots that stores $n$ elements.
    - This is the average number of elements stored in a chain.
    - $\alpha$ can be less, qual equal to, or greater than 1.

- The worst-case behavior of hashing with chaining is *terrible*: all $n$ keys hash to the same slot, creating a list of length $n$.
- The worst-case time for searching is $\Theta(n)$ plus the time to compute the hash funciton.
- The average-case performance of hashing depends on how well the hash function $h$ distributes the set of keys to be stored among the $m$ slots, on the average.

- **Simple uniform hashing:*** Any given element is equally likely to hash into any of the $m$ slots, independently of where any other element has hashed to.

***Theorem 1:***
: In a hash table with chaining, an **unsuccessful search** takes *average-case time* $\Theta(1 + \alpha)$.

***Theorem 2:***
: In a hash table with chaining, an **successful search** takes *average-case time* $\Theta(1 + \alpha)$, under the assumption of *simple uniform hashing*.

*Both theorems consider the time for computing the hash funciton $\Theta(1)$.*

- If the number of hash-table slots are at least proportional to the number of elements in the table:
    - We hace $n = O(m)$
    - $\alpha = n / m = O(m) / m = O(1)$
- Thus, *searching* takes *constant time* on *average*.

- Then, we can support *all dictionary operations* in $O(1)$ time on *average*.

---

## 3. Hash functions

- A good hash funciton satisfies the assumption of simple uniform hashing:
    - each key is equally likely to hash to any of the $m$ slots, independently of where any other key has hashed to.

- **static hashing**
- **random hashing**

- A hash funciton is designed to handle keys that are one of the following two types:
    - A shor nonnegative integer that fits in a $w$-bit machine word. Typical valyes for $w$ would be 32 or 64.
    - A short vector of nonnegative integers, each of bounded size. For example, each element might be an 8-bit byte, in which case the vector is often called a (byte) string. The vector might be of variable length.

### 3.1 Static hashing

#### The division method

- We map a key $k$ into one of $m$ slots by taking the remainder of $k$ divided by $m$.

$$
h(k) = k mod m
$$

- Avoid certain values of $m$:
    - $m$ should not be a *power of 2*, since if $m = 2^p$, then $h(k)$ is just the $p$ lowest-order bits of $k$.
- A prime not too close to an exact power of 2 is often a good choice for $m$,

#### The multiplication method

- Operates in two steps:
    - Multiply the key $k$ by a constant $A$ in the range $0 < A < 1$, and extract the fractional part of $kA$.
    - Multiply this value by $m$ and take the floor of the result.

$$
h(k) = \lfloor m(kA \text{ mod } 1) \rfloor
$$

- "$kA \text{mod} 1$" means the fractional part of $kA$, that is, $kA - \lfloor kA \rfloor$

- An advantage is that the value of $m$ is not critical.
- We typically choose it to be a power of 2 ($m = 2^p$ for some integer $p$).

- Knuth suggestion:

$$
A \approx (\sqrt{5} - 1) / 2 = 0.6180339887\dots
$$

- Given key $k$, $w$ bits and $m$ number of slots:

$$
m = 2^p
$$

$$
A = s / 2^w \approx (\sqrt{5} - 1) / 2
$$

$$
k \cdot s = r_1 2^w + r_0
$$

- The desired $p$-bit hash value consists of the $p$ most significant bits of $r_0$.

$$
h(k) = r0 >> (w - p)
$$

- Equivalent to:

$$
\text{floor}(2^p \cdot \text{fractional\_part}(kA))
$$

#### The multiply-shift method

Special case:

- The number **$m$ of hash-table slots** is an *exact power of 2*
    - $m = 2^l$, for some integer $l$
- $l \leq w$ and $w$ is the *number of bits in a machine word*
- We choose a $w$-bit positive integer $a = A 2^w$, where $0 < A < 1$, so $0 < a < 2^w$
- We assume that a key $k$ fits into a single $w$-bit word

$$
\begin{align*}
k \cdot a &= k \cdot A 2^w \\
&= r1 2^w + r0 \text{ (2$w$ bit value)}
\end{align*}
$$

$$
h_a(k) = (k a \text{ mod } 2^w) >>> (w - l)
$$

- $r1$: high-order $w$-bit word
- $r0$: low-order $w$-bit word
- $>>>$: logical right shift

- Even thought this method is fast, it doesn't provide any guarantee of good average-case performance.


### 3.2 Random hashing

**Random hashing**
: Choose the hash function *randomly* in a way that is *independent* of the keys that are actually going to be stored.

- At the beginning of the execution: select the hash function at random, from a carefully designed class of functions

- $H$: finite collection of hash functions that map a given universe $U$ of keys into the range $\{ 0, 1, \dots, m - 1 \}$
    - **Universal** collection, if for each pair of distinct keys $k, l \in U$, the number of hash functions $h \in H$ for which $h(k) = h(l)$ is at most $|H| / m$.
    - In other words: with a hash function randomly chosen from $H$, the chance of a collision between distinct keys $k$ and $l$ is no more than the chance $1 / m$ of a collision if $h(k)$ and $h(l)$ were randomly and independently chosen from the set $\{0, 1, \dots, m - 1\}$.

**Theorem 3**
: A hash function $h$ chosen randomly.
: Used to hash $n$ keys into a table $T$ of size $m$.
: Using chaining to resolve collisions.
: If key $k$ is *not in the table*, the expected length $E[n_{h(k)}]$ of the list that the $k$ hashes to is at most the load factor $\alpha = n / m$.
: If the key $k$ is *in the table*, then the expected length $E[n_{h(k)}]$ of the list containing key $k$ is at most $1 + \alpha$.

- By cleverly randomizing the choice of hash function at run time, we guarantee that we can process every sequence of operations with a good average-case running time.

**Corollary 4**
: Using *universal hashing* and *collision resolution by chaining* in an initially empty table with $m$ slots.
: It takes expected time $\Theta(n)$ to handle any sequence of $n$ `INSERT`, `SEARCH`, and `DELETE` operations containing $O(m)$ `INSERT` operations.

- `INSERT` and `DELETE` operations take constant time.
- By Theorem 3, expected time for each `SEARCH` operation is $O(1)$.
- By linearity of expectectations, the expected time for the entire sequence of $n$ operations is $O(n)$.
- Since each operation takes $\Omega(1)$ time, the $\Theta(n)$ bound follows.

#### Designing a universal class of hash functions

- Choose a **primer number $p$** large enough so that every possible key $k$ is in the range 0 to $p - 1$, inclusive.
- $\Z_p$ denote the set $\{0, 1, \dots, p - 1\}$
- $\Z_p^*$ denote the set $\{1, 2, \dots, p - 1\}$
- We can solve equations modulo $p$
- We assume that the size of the universe of keys is greater than the number of slots in the hash table: $p > m$.
- Hash function $h_ab$ for any $a \in \Z_p^*$ and any $a \in \Z_p$, using a linear transformation followed by reductions modulo $p$ and the modulo $m$:

$$
h_{ab}(k) = ((ak + b) mod p) mod m
$$

- With $a = 3$, $b = 4$, $p = 17$, $m = 6$ and $k = 8$:

$$
h_{34}(8) = ((3 \cdot 8 + 4) mod 17) mod 6 = 5
$$

- The family of all such hash functions is:

$$
H_{pm} = \{h_{ab} : a \in \Z_p^* \text{ and } b \in \Z_p\}
$$

- Each $h_{ab}$ maps $\Z_p$ to $\Z_m$
- The size of $m$ of the output range is arbitrary, not necessarily prime.
- Since we have $p - 1$ choices for $a$ and $p$ choices for $b$, the collection $H_{pm}$ contains $p(p - 1)$ hash functions.

**Theorem 5**
: The class $H_{pm}$ of hash functions is universal.

---

## 4. Open addressing

- All elements occupy the hash table itself.

---

---

## C++ STL hash-based containers

C++ provides hash-table-based containers in the Standard Template Library (STL):

```cpp
#include <unordered_set>
#include <unordered_map>
```

These containers are called `unordered` because they do not maintain their elements in sorted order. Internally, they organize elements using hashing.

### `std::unordered_set`

`std::unordered_set<T>` stores unique keys of type `T`.

It is useful when we only need to know whether a key exists in the set.

```cpp
#include <unordered_set>

std::unordered_set<std::size_t> keys;

keys.insert(8);
keys.insert(14);
keys.insert(25);

bool has_14 = keys.contains(14);

keys.erase(14);
```

Conceptually, this is similar to a hash table that supports:

```text
insert(key)
search(key)
delete(key)
```

It stores the key itself, without an associated value.

Average-case running times:

- `insert`: $O(1)$
- `contains` / `find`: $O(1)$
- `erase`: $O(1)$

Worst-case running times can degrade to $O(n)$ if many keys collide.

### `std::unordered_map`

`std::unordered_map<Key, Value>` stores key-value pairs.

It is useful when a key is associated with some data.

```cpp
#include <unordered_map>
#include <string>

std::unordered_map<std::size_t, std::string> names;

names[8] = "eight";
names[14] = "fourteen";
names[25] = "twenty-five";

std::string value = names.at(14);

names.erase(14);
```

Here:

```text
key   = std::size_t
value = std::string
```

Conceptually:

```text
8  -> "eight"
14 -> "fourteen"
25 -> "twenty-five"
```

This is similar to a dictionary or map implemented with hashing.

Average-case running times:

- `insert`: $O(1)$
- `operator[]`: $O(1)$ average access/insertion
- `at`: $O(1)$ average access
- `contains` / `find`: $O(1)$
- `erase`: $O(1)$

Worst-case running times can degrade to $O(n)$.

### `find`, `contains`, and iterators

Since C++20, we can use `contains`:

```cpp
if (keys.contains(14)) {
    // key exists
}
```

A more general approach is `find`:

```cpp
auto it = names.find(14);

if (it != names.end()) {
    std::size_t key = it->first;
    std::string value = it->second;
}
```

For `std::unordered_map`, each iterator points to a key-value pair:

```cpp
it->first   // key
it->second  // value
```

For `std::unordered_set`, each iterator points directly to a key.

### Load factor and buckets

The STL exposes some hash-table-related information:

```cpp
std::unordered_set<std::size_t> keys;

keys.insert(8);
keys.insert(14);
keys.insert(25);

float alpha = keys.load_factor();
std::size_t buckets = keys.bucket_count();
```

The load factor corresponds to the CLRS concept:

$$
\alpha = n / m
$$

where:

- $n$ is the number of stored elements.
- $m$ is the number of buckets.

In STL terms:

```text
n = container.size()
m = container.bucket_count()
```

A larger load factor generally means more expected collisions.

The container can automatically increase the number of buckets through rehashing.

### Relation with CLRS hash tables

The STL containers are practical implementations of the same general ideas studied in CLRS:

- A key is transformed by a hash function.
- The hash value determines where the element is stored.
- Collisions must be resolved internally.
- Operations are expected $O(1)$ under good hashing assumptions.

However, the STL abstracts away most implementation details. We normally do not directly manage:

- the hash table array,
- collision chains,
- probing sequences,
- sentinel states,
- deleted markers,
- manual resizing.

For example:

```cpp
std::unordered_set<std::size_t> set;
std::unordered_map<std::size_t, std::string> map;
```

are the high-level STL equivalents of hash-based dictionaries.

### When to use each container

Use `std::unordered_set` when the key itself is the stored data:

```cpp
std::unordered_set<std::size_t> visited_nodes;
```

Use `std::unordered_map` when each key has associated data:

```cpp
std::unordered_map<std::size_t, std::string> student_names;
```

Summary:

| Container | Stores | Example use case |
|---|---|---|
| `std::unordered_set<T>` | unique keys | checking whether an ID exists |
| `std::unordered_map<K, V>` | key-value pairs | mapping an ID to an object or value |