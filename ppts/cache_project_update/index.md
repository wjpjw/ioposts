title: Cache Replacement Project
speaker: Jipeng Wu
url:
transition: vertical3d
files: /js/demo.js,/css/demo.css,/js/zoom.js
theme: dark
usemathjax: no

[slide]
# A Frequent-Pattern-Aware Hardware Prefecher
## Jipeng Wu

[slide]
## Project Scope Clarification
----
My original project proposal title is "A Frequent-Pattern-Aware Cache Replacement Algorithm". It's incorrect.  {:&.zoomIn}
* A cache optimzation/management solution is combination of 2 independent techniques: hardware prefetching and cache replacement policy.
* However, frequent pattern mining can only be applied in prefetching schemes which predicts cache misses in near future and fetch them into cache.

[slide]
## Background: Why Prefetching?  
----
![system-dram](/img/system-dram.png)
* SRAM can keep pace with processor memory request rates. {:&.zoomIn}
* LLC miss latency continues as a significent bottleneck.

[slide]
## Background: Why Prefetching?  
----
* A program working on a large array.  {:&.zoomIn}
  * Caching policies are defeated by such programs with low locality.
* A data block in that array is constantly referenced and updated.
  * Such capacity miss can be avoided by fectching before referenced in parallel with processor computation.


[slide]
## Existing prefechers
----
* Access Map Pattern Matching(AMPM):  {:&.zoomIn}
  * 2 bits per cache line, 4 states(untouched, demand， accessed, prefetched), no traditional history buffer;
  * AMPM only detects simple stride patterns. (like {N, N+2, N+4})
* Spatial Memory Streaming(SMS):
  * AGT(Active Generation Table): AGT entries are spatial pattern bitmaps.
  * PHT(Pattern History Table): when a AGT entry evicted, it's placed in PHT.
  * The PC+offset of the load instruction are used to look up the PHT. If there is a match, data blocks indicated by PHT entry's bitmap will be prefeched.


[slide]
## Existing prefechers
----
* Variable-Length Delta Prefecher(VLDP):
  * VLDP captures variable-length delta patterns rather than fixed-length strides.
  * Standalone buffers: Per-page Delta History Buffer, Delta Prediction Tables, Offset Prediction Tables.
  * VLDP stores at most 4 delta address records like "{1,3,2,4}" for each page.



[slide]
## How to track history
----
* The Global History Buffer:  {:&.zoomIn}
  * The GHB is a circular buffer, and each cache miss adds a new entry to the buffer.
  * The index table points to the most recent occurrence of PC in global history.
  * Therefore GHB can be looked up by PC. But the history length is 1 and this method replies on PC.
* AMMP's Per cache line based history:
  * Each cache line assigned with 2 bits to indicate its state: untouched, demand, accessed, prefetched.
  * It's not really a history buffer. It requires a walkthrough of adjacent cache lines

[slide]
## How to track history
----
* VLDP's Page-based design: {:&.zoomIn}
  * DHB Entry: (i) page number(ii) page offset of the last address accessed in this page, (iii) sequence of up to 4 recently observed deltas, (iv) the DPT level used for the latest delta prediction, (v) the number of times this page has been used, and (vi) 4 recently prefetched offsets.

* FPA design: I plan to setup a temporary global history buffer in LLC that tracks address seuqences. Additional hardware depends on pattern mining methods.

[slide]
## Delta patterns
----
Since a data access pattern can repeat across different regions of memory, it's reasonable to ignore the base address, for example, {1,2,0}={2,3,1}={-2,-1,-3}.  {:&.zoomIn}

* In an address sequence {A,A+1,A+4,A+3,A-2,B,B-1,B+3,B+1,B-1,C,C+1,C+4,C+3,C-2}, {0,1,4,3,-2} is supposed to be captured as a pattern.

[slide]
## FP-growth?
----
* Fp-growth is a lightweight frequent pattern capture method. Its fp-tree is known as one of the most compact data structure that learns from temporary global history.  

[slide]
## FP-growth + LLC
----
![fp-tree](/img/fpa.jpg)


[slide]
## Simulation Environment
----
* Simulator: CMPSIM {:&.zoomIn}
* 3 layer cache model + out-of-order 8-stage pipeline
* Non-inclusive virtual address LLC: 16K cache lines
* Cache line size: 64B
* Reserved bits per cache line: 8 bits
* Storage budget: 16K*8+1K=129K

[slide]
## Workload and Performance Evaluation
----
* Single-threaded workload generated by pin tool. {:&.zoomIn}
* Comparing FPA with AMPM(Access Map Pattern Matching) and SMS(Spatial Memory Streaming).
* Segment LRU as cache replacement policy.

[slide]
## Discussion
----
* It's possible to design a corresponding replacement policy to leverage FPA prefecher, in the future.
* How would you mine frequent patterns of variable-length sequences from the following string: {0,1,4,3,-2,0,-1,3,1,-1, ...}?

[slide]
## Discussion
----
* The problem is that the string can be segmented into variable-length sequences. And it seems that operator=() needs to be redefined for these sequences. 
  * Different length: {1,2,4,8,3} = {1,4,8,3}. {2} is probably wrapped in a if statement.  
  * Minor reordering: {1,2,4,8,3} = {2,1,4,8,3}. They might be 2 branches of the same business logic.
  * Random reordering: {1,2,4,8,3} != {2,3,4,1,8}. Coincidence.
  * Small but strong patterns: a smaller sequence repeatedly occurs, for example {0,23,1233}.
  * Delta addressing: {1,2,0}={2,3,1}={-2,-1,-3}. It increases the complexity.