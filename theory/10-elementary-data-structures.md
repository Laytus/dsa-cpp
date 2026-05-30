# 10. Elementary Data Structures

### Operations on dynamic sets

- *Queries:* simply return information about the set.
- **Modifying operations:** change the set.

**`SEARCH(S, k)`**
: A *query* that, given a set `S` and a key value `k`, returns a pointer `x` to an element in `S` such that `x.key = k`, or `NIL` if no such element belongs to `S`.

**`INSERT(S, x)`**
: A *modifying operation* that augments the set `S` with the element pointed to by `x`. We usually assume that any attributes in element `x` needed by the set implementation have already been initialized.

**`DELETE(S, x)`**
: A *modifying operation* that, given a pointer `x` to an element in the set `S`, removes `x` from `S`. (Note that this operation takes a pointer to an element `x`, not a key value.)

**`MINIMUM(S)`**
: A *query* on a totally ordered set `S` that returns a pointer to the elment of `S` with the smallest key.

**`MAXIMUM(S)`**
: A *query* on a totally ordered set `S` that returns a pointer to the elment of `S` with the largest key.

**`SUCCESSOR(S, x)`**
: A *query* that, given an element `x` whose key is from a totally ordered set `S`, returns a pointer to the next larger element in `S`, or `NIL` if `x` is the maximum element.

**`SUCCESSOR(S, x)`**
: A *query* that, given an element `x` whose key is from a totally ordered set `S`, returns a pointer to the next smaller element in `S`, or `NIL` if `x` is the minimum element.


- `stack`
- `queues`
- `linked lists`
- `rooted trees`

---

## 1. Stacks and queues

- Element removed from the set by the `DELETE` operation is *prespecified*.

- `stack` --> `LIFO` (*last-in, first-out*)
- `queue` --> `FIFO` (*fast-in, first-out*)

### Stacks

- `PUSH`: Insert operation
- `POP`: Delete operation

- `S.top`

- `empty`: `S.top = 0` 
- `underflow`: attempt to pop an empty stack
- `overflows`: if `S.top` exceeds `n`

### Queue

- `ENQUEUE`: Insert operation
- `DEQUEUE`: Delete operation

- `S.head`
- `S.tail`

- `empty`: `S.tail == S.head` 
- `underflow`: attempt to dequeue an element from an empty stack
- `full`: when `Q.head = Q.tail + 1` or both `Q.head = 1` and `Q.tail = Q.lenght`

---

## 2. Linked Lists

- Data structure in which the objects are arranged in a linear order.
- The order is determined by a pointer in each object.

---

## 3. Implementing pointers and objects

### A multiple-array representation of objects

- Three *arrays*
- Each on corresponds to: `next`, `key` and `prev`
- One *variable* contains the `NIL` object

### A single-array representing of objects

- One single array where objects are stored one after the other
- The memory is located as "`pointer` + `offset`"

### Allocating and freeing objects

==garbage collector==

- `free list`

`ALLOCATE-OBJECT()`
```
if free == NIL
    error "out of space"
else x = free
    free = x.next
    return x
```

`FREE-OBJECT()`
```
x.next = free
free = x
```

- We can service several linked lists with just a single free list

---

## 4. Representing rooted trees

### Binary trees

- `p`: parent
- `left`: left child
- `right`: right child

- If `x.p` = `NIL` --> `x` is the root
- If node `x` has no left/right child --> `x.left`/`x.right` = `NIL`

- `T.root`: the root of the entire tree `T`
- If `T.root` = `NIL` --> he tree is empty

### Rooted trees with unbounded branching

- `x.p`: parent
- `x.left-child`: points to the leftmost child of node `x`
- `x.right-sibling`: points to the sibling of `x` immediately to its right

- If `x` has no children --> `x.left-child` = `NIL`
- If `x` is the rightmost child of its parent --> `x.right-sibling` = `NIL`