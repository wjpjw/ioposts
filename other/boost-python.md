---
title: 使用Python作C++游戏的脚本
tags:
- python
- c++
- game
---

Boost/python是无缝桥接cpp与python的最好工具。只需“exec某些python文件”，“写入读取python的全局变量”，"将c++类与函数以module形式提供给python"这3个功能就足以实现一个脚本引擎。

<!--more-->

### 脚本引擎架构设计
* 游戏加载时的init，每帧的update以及用户触摸点击事件touched。这三处可以执行对应的三个python文件，将控制权转交脚本。
* c++应该专注实现图形相关的内容，提供的抽象全部基于图形，与游戏逻辑无关。python实现游戏逻辑，比如Unit是python中的纯逻辑对象，只不过创建它时存储了c++中包含骨骼动画的SkeletonUnit指针地址，和图形对象绑定了。
* c++应该把图形相关的类、类函数、计算密集的函数导出，提供给python。python再浅包装一下c++暴露的原始接口，提供文档和默认参数，方便python开发、测试。

### boost/python的细节
* 并不是所有类都可以作为python对象的，很多类都delete掉了拷贝构造函数，这种类不能导出到python模块里，需要另写一个简单的代理类。
* 导出时随便def多少函数、变量，不影响类结构的完整导出。一个类如果所有成员变量类型都对python解释器已知，即使不导出任何方法也是可以作为python对象存储所有数据的。
* def的所有函数在python看来都是不正常的，无参数默认值，无形参，所以最好在python里包装一下顺便写个文档。
* 所有c++对象转python对象都是根据指针进行一层deep copy，把指针所指的数据复制，但不会把对象里的指针层层复制。
* 想要把指针类型转化为python object，最好不用ptr()函数，而是用reinterpret_cast<int>。
* win_sdk中定义了ssize_t，py_config.h里又define了一下，两者不统一，前者是long，后者是int，在windows下int和long等价，所以编译boost/python时要改python源码，只一处而已，问题不大。
* cpp内嵌的python解释器不会正常识别import，简单的解决办法就是在所有python的import前面加上cpp可执行文件所在的上级目录名，例如：
  ```python
    from cqscripts.core.gamelayer import *
  ```
  此外，cpp脚本引擎即使import了其他python模块也不会将cpp中定义的全局变量导入其中，需要手动导入main里的全局变量：
  ```python
  from __main__ import x
  ```

### 为何要使用脚本
现代c++非常强大，连lambda支持都完爆python，黑科技无穷无尽，写起来其实相当方便，但仍有一些缺点：
* c++需要VS或XCode支持。其他环境，例如武装到牙齿的emacs对复杂的c++项目依旧无力，IDE的整合是必需的。VS现在做的非常好用，但是特别笨重，又慢又占内存。不像编辑器打开了就写，随时随地的碎片时间可以利用起来。
* c++随便改几句，编译一下就要几分钟甚至半小时。这导致无论开发还是debug都极其痛苦。脚本语言支持的热更新不仅方便了玩家，也节约了开发者的时间。
* c++的方便高效建立在合理使用基础之上，门槛很高。即使合理使用了，还是有”声明”的额外书写代价，所以总归比脚本语言慢一些。

### Python语言作脚本的优缺点
优点：
* JS，Lua都没有完备的类，与c++的逻辑绑定需要额外抽象成本。
* JS其实很好，然而V8不支持ios设备。Boost/python支持各平台。
* Python可以很方便地序列化。
* Python作为抽象工具比较方便，语法甜，轮子也多。
* layout控制语法，看起来清爽。

缺点：
* 计算性能低：V8>Lua>Python。
* layout控制语法的设计会导致歧义、无法压缩脚本、修改代码时的麻烦。