---
title: Cache Replacement Competition Framework
tags:
- cache replacement
- microarchitecture
---

# Why, What and How
### Why CRC?
- CRC and its trace generator 'pin' are old, but it's hard to find another cmp memory simulator.
- CRC's user-visible code is well decoupled. It doesn't include any header of simulator or 3rd party libraries. Therefore, there is zero technical obstacle even without decent documentation.

<!--more-->

### The Simulation Target
CRC simulates a CMP Memory System:
- 8-staged 4-wide pipeline
- out-of-order processor
- L1-L2-L3, 3 layer caches
- perfect branch prediction

L1 has icache and dcache. L2 is dcache. L3, also called LLC, is the cache where I will try to implement novel replacement strategies.

### How CRC works
The CRC code is probably borrowed from CMP$IM.  I thought they were naturally open source but they weren't. The simulator code is a blackbox library. Only cache replacement code is user visible. So I should compile the cache replacement module, and link with CRC static lib and CRC's dependencies.

The source code provided in CRC project is actually an Intel binary tool 'pin', used to generate traces. It is a bad news for me since it's hard to hack into cache data, which is crucial for debugging and analysis.

# Build and Run
### Linux kernel version problem
I followed its readme, configured and compiled the CRC project on *Fedora 23*. This build was smooth and fast. It has some rarely seen lib dependencies, yet most are already provided. However I encountered a compatability problem.

CRC uses Intel binary tool 'pin' as trace generator. Unfortunately even the latest pin tool doesn't support Linux 4.x. So I installed *Ubuntu 12* whose kernel is 3.2, but it didn't work.

Then I realized this simulator is really old, and found that it was based on CMP$IM proposed in 2006. So I decided to install *Ubuntu 10.04*, the oldest ubuntu with package support.

On Ubuntu 10.04, the default CRC project still has some problems. I modified the 'pin' file(It's a shell script.) and supplied everything it requires.

### Generate traces
Finally, 'pin' is fed with correct version of everything. I generated one trace 'cat'. The cat.out.trace.gz is
![](/images/crc3.jpg)

'pin' can generate millions of instructions. I just minimizes the inst_nr to run a short benchmark.

To generate N-core traces, just combine N different traces.

### Run simulation
The CRC simulator can set thread number, cache configuration and replacement policy number.
![](/images/crc1.jpg)
![](/images/crc2.jpg)

# Summary
I spent quite a few hours installing older linux today. But in the end the environment was set up.

The next step is to read more on Intel's L3 caching related paper and try to implement them.

My goal is to design and implement a novel algorithm. It would probably be a variant or hybrid of big names.
