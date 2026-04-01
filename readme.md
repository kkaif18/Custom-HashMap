# Simple HashMap in C++

This project implements a basic **HashMap (similar to ****`std::unordered_map`****)** from scratch.

---

## What this code does

* Stores **key-value pairs**
* Supports:

  * Insert
  * Get value by key
  * Delete key
  * Check if key exists
* Works with **any data type** using templates

---

## Core Idea

The HashMap uses:

* A **vector (array)**
* Each index stores a **linked list of pairs**

This method is called **separate chaining**.

---

## How it works

### 1. Hashing

Each key is converted into an index:

```cpp
index = hash<K>{}(key) % buckets.size();
```

---

### 2. Insert

* Find the correct bucket
* If key exists → update value
* Else → add new pair
* If too many elements → rehash

---

### 3. Get

* Find the bucket using hash
* Search for the key
* Return the value if found

---

### 4. Delete

* Locate the bucket
* Traverse and remove the key-value pair
* Returns success/failure

---

### 5. Contains

* Checks if a key exists in the map

---

## Important Concepts

### Templates

```cpp
template <typename K, typename V>
```

Allows usage like:

```cpp
HashMap<string, int>
HashMap<int, string>
```

---

### Load Factor

```
load_factor = elements / buckets
```

* Controls how full the map is
* If too high → performance drops

---

### Rehashing

* Bucket size is increased (usually doubled)
* All elements are reinserted
* Keeps operations efficient

---

## Time Complexity

| Operation  | Average |
| ---------- | ------- |
| Insert     | O(1)    |
| Get        | O(1)    |
| Delete     | O(1)    |
| Worst case | O(n)    |

---

## Summary

* Custom HashMap using **vector + linked list**
* Handles collisions using chaining
* Uses rehashing to maintain performance

---

##
