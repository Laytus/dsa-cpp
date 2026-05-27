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