---
title: 微处理器结构
tags:
- microarchitecture
---
文献整理。
<!--more-->


### out of order scheduler
fetch, decode, issue(in order);
exec, write(out of order);
commit(in order);

### component of scheduler
- buffer for unexecuted instructions, called "scheduler entries", "issue queue" or "reservation station"
- method for tracking state of dependencies(resolved or not)
- method for choosing between multiple ready instructions competing for the same resource
- method for notification of dependency resolution


### data-capture vs non-data-capture scheduler
- data-capture: scheduler里存放指令的拷贝，不必再从ROB或PRF里取。虽有ROB，但仍要再拷贝一份。
- non-data-capture连ROB都没，直接从PRF里取指令。


### LSQ
load之前store过的value，直接从LSQ取。

### store是特殊的
store cannot retire. 要保证memory consistency可能会引发ROB、pipeline阻塞。

有一种设计是store不写入cache，直接进入memory或L2。

两个store之间的load可以ooo。
