# Chap 2: Memory Hierarchy Design

## Quick Review
* Multiple words, called a `block`, each cache block includes a `tag` to indicate which memory address it corresponds to.
* `set` is a group of blocks in the cache.
* `n` blocks in a set, the cache placement is called `n-way set associative`
* One block per set, called `direct-mapped`.
* Just one set called `fully associative`.
* Caching data only read is easy, caching writes is more difficult.
How can the copy in the cache and memory be kept consistent?
* Write through
* Write back
