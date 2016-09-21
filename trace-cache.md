---
title: Trace Cache
tags:
- trace cache
- microarchitecture
---


Trace cache can provide benefits in various aspects but it can also increase power consumption and complexity. Let’s discuss pros and cons of trace cache.   



(a) Discuss pros and cons of instruction trace cache in terms of power. Can trace cache increase or decrease power consumption? Do we need I-cache with a trace cache?

- It depends on the general processor design. In P4's case, if you simply replace P4's TC as IC, TC does reduce power consumption. But modern processors have many supplement for IC design, such as a uop cache, which helps the IC design more power efficient.
  - Pros:
    - TC can store decoded instructions(micro-ops). Therefore upon a TC hit, refetching and decoding power cost is saved. It saves power in cases where fetching and decoding is the bottleneck.
  - Cons:
    - Misprediction is more costly than processors without TC.
    - The decoded micro-ops are much longer than instructions.[2] Therefore TC's size is smaller than IC, implying more I/O latency and power cost.
    - TC miss rate is significantly higher than IC's miss rate[1]. A TC miss(without IC in processor) will cost L2 latency.
    - Decoding cannot be paralleled if traces are filled at fetch. Only one instruction decoded and fed to TC in one cycle. Considering its low hit rate, the TC processor behaves like a single-issued antique 40-50% of the time.[3]

- In terms of functionality, no, we don't need IC if general-purpose TC is already in the design. A TC that stores decoded ops can fully replace IC. But in terms of performance, a IC can improve performance of one-by-one fetch when there is TC miss.





(b) Discuss pros and cons of trace caches over compiler optimizations. Please show examples of code optimization effects in trace cache.

TC can work with and easily benefit from its corresponding compiler techniques.
- Pros:
  - Renaming: marks instructions which move a value from one register to another register as explicit move instructions.
  - Reassociation: unnecessary add dependency chain in a trace can be broken.
  - Scaled add instructions: add ops can be converted to add+shilft in one cycle.
  - Branch promotion: highly biased branches can be promoted to static prediction.
  - Can treat traces as an atomic operation, which enables higher level parallelization of traces. (Better concurrency programming support.)
  - Decoded ops can be reordered since the e dependencies between instructions within a trace cache line are stored explicitly.
- Cons:
  - All of these techniques are completely useless if TC's hit rate is as low as 60% while IC is usually above 90%.




(c) Discuss pros and cons of trace caches and branch predictors. Is it a good idea to turn off branch predictor?
Branch predictor should be used when TC misses, i.e., TC is being built. But TC predictor is definitely better when TC hits.
- Pros(turn off brach predictor, use TC predictor):
  - TC predictor has lower power cost and smaller prediciton latency.
  - TC predictor underlies micro-ops multi-fetch, the basis of TC design,   
- Cons:
  - Branch predictors can improve processor's performance when TC is unusable. Considering TC's high miss rate, it's reasonable to use branch prediction.
  - If a TC predictor mispredicts, unlike branch predictors, all the ops that TC loads are not discarded instantly, which is extremely costly especially when some ops are time-consuming.


(d) Discuss the benefits of trace caches in terms of pipeline depth and width.

- The pipeline can have more stages since instructions are broken into micro-ops. For example, a stage that only transports data from one place to another. So it is definitely wider.
- The traces can be optimized for pipelining, renaming and reassociation for examle, can reduce dependencies and underlie wider pipelines.
- But in terms of depth, it's only deeper when TC hits. If TC misses, the processor behaves like it's single-issued single-fetched, which will not supply enough micro-ops per cycle to form a deeper pipeline. In this case the width of pipeline becomes a major disadvantage due to not only the inefficiency but also the higher penalty for misprediction.


[1] Trace Cache: a Low Latency Approach to High Bandwidth Instruction Fetching
[2] The microarchitecture of Intel, AMD and VIA CPUs
[3] Inside Nehalem: Intel’s Future Processor and System
[4] Putting the Fill Unit to Work: Dynamic Optimizations for Trace Cache Microprocessors
