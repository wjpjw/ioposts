---
title: A Frequent-Pattern-Aware Cache Replacement Algorithm
tags:
- cache replacement
- big data
- microarchitecture
---

Initial Project Proposal

<!--more-->


### Introduction
- Project name: FPA(Frequent-Pattern-Aware) Cache Replacement.
- The simulator is *CMP$IM*.
- Traces are generated as single-threaded by Intel binary tool *pin*.
- 3-layer cache model. Only focus on LLC. LLC is a 16 way cache.


### Objectives
- Design and implement a high performance cache replacement algorithm FPA.
- Run simulation and analyze FPA performance.

## Project Plan
### Initial Algorithm Plan
#### Frequency Pattern Capture
FPA's frequency pattern awareness is based on two data structures:
- History DB: an in-cache database that stores long-term memory of recent address history.
  - Unlike LRU, History DB doesn't assign bits in each cache line. It's a consecutive cache block that stores a longer history records than the number of cache ways. Each record has two fields: address and FP-tree's *support*.
- FPA Tree: A FP-tree variant that maintains frequency patterns for the FPA's decision engine.
  - FPA Tree is an even more compact but less complete FP-tree(FP-Growth's data structure) variant.  It is built on History DB information by 2 scans. After built, FP-Growth algorithm can easily elicit patterns.

#### Recency Capture
Recency can be captured by a list that records every address that has been seen only *n* times, *n* < minimum support threshold of FP-Growth.

Since FPA already has a History DB that stores recent addresses and labels them with *support* count, no extra data structure is needed.

### Minimum Support Threshold
Minimum support threshold in FP-Growth defines whether a pattern is considered as frequent. It's hard to analyze its optimal value. I will do multiple experiments to find a good one.

### Storage Budget
FPA simulation is only working on LLC. Apparently no memory access is allowed for cache level algorithms. The storage is very limited.

There is 1KB LLC cache lines reserved for this algorithm. Each unreserved cache line also provides 8-bits for cacheline-associated storage.

### FPA Implementation Overhead
Since the CMP$IM simulator is not cycle-accurate, I can't measure the real world overhead. However I will do a static analysis of FPA's time complexity, comparing against LRU and ARC.

### Single-threaded traces only
I have no plan for supporting multi-application caching policy management, which is on another abstraction level. Therefore, this FPA scheme is thread-unaware and its simulation should be only fed with single-threaded traces.
