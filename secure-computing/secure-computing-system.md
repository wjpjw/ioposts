---
title: 安全计算系统
tags:
- secure computing system
---
文献整理。
<!--more-->

# 作业一
{% pdf https://drive.google.com/file/d/0Bx7VXO4jC7TUU1piSzhmcFFqTDg/preview %}

<!--Week1---->
# 安全计算系统的基本概念
### What is Computer Security(gassbook-c1)
#### SECRECY, INTEGRITY, AND DENIAL OF SERVICE
1. Secrecy/Confidentiality：protecting the information from disclosure to unauthorized parties.
2. Integrity: protecting information from being modified by unauthorized parties.
3. Denial of service: 可能是机器故障导致信息损失。

计算安全主要研究的是secrecy，信息不泄露。至于信息的integrity主要是指信息没被修改，实际上在商业软件中更常用，不过没多少研究者感兴趣，还好integrity需要的技术和secrecy差不多。至于denial of service虽然也是信息安全的话题，却不再讨论范围内，原因是软件正确性这一话题太难了，大多数情况下根本实现不了。


#### 可信系统评价标准
美国国防部发布橙皮书：Trusted Computer System Evaluation Criteria，定义了安全概念。商用可以很容易通过加装一些addon达到C1或C2。只有军用才会追求A1或B3。
![软件安全等级](/images/secure-level.png)


### Trusted Computing
#### 1. 什么是TC?
The Trusted Computing Group (TCG)是Microsoft, Intel, IBM, HP and AMD联合提出的更加安全的PC标准。这里安全的定义颇有争议。按TCG标准做的PC从微软、intel角度来看更可信，但对PC拥有者来说反而更不可信。TCG将你的控制权更多地转移给硬件、软件提供商。TC在这些公司叫法都不一样，故意让公众对此感到混淆。

#### 2. TC做的是什么？
TC提供一个让你无权控制、更改软件的计算平台。动机源于digital rights management (DRM)。

TC使得如下可能成立，例如：
1. 卖一个只准拷贝三次的音乐。
2. 必须24小时看完的电影，即租用软件。
3. 禁止使用unlicensed software。
4. TC app可以互相依赖，non-TC app被各种歧视。
5. 让政府部门创立的doc一创建就是classified，不会泄露。
6. 远程审查，用traitor tracing的方式举报非法资源，远程删除某人机器上的音乐。
7. office可以用只有微软产品才能访问的秘钥，使得其他软件无法打开doc等。

当然TC不会立刻让以前的东西用不了，会潜移默化，逐步实施。TC-PC必须比普通PC更好用，否则无法流行。

#### 3. TC是如何工作的?

TC为以后的PC提供一个监视与举报挂载组件。第一阶段的TC倾向于使用Fritz芯片——焊在主板上的智能芯片或dongle。当前的TC倾向于五个组件：
1. Fritz芯片
2. CPU中的curtained memory机制
3. 每个TC程序中的安全内核（微软称之为“NCA”）
4. 一个操作系统安全内核（微软称之为“Nexus”）

早期TC和Fritz监视boot进程，这样只要软硬件已知，PC最终会进入可预测的状态。

目前TC将Fritz作为一个消极监视组件，存储极其开始时的hash。这个hash用硬件细节来计算。如果机器最终进入了approved state，Fritz就会把TC密钥提供给操作系统。否则极其就无法获取TC密钥，只能跑non-TC程序，读non-TC数据。

Nexus桥接了Fritz和NCA，检查硬件组件是否在TCG认可名单里，软件是否已签约，序列号是否吊销了。如果PC配置有变，则机器联网重新认证这些信息。Nexus协作curtained memory阻止TC程序读写其他TC程序的数据。这种curtained memory机制在Intel中被称为Lagrande Technology，在AMD被成为TrustZone.

当机器在approved state运行TC程序时，Fritz会通过第三方，比如Disney，对copy的合法性进行认证。Disney服务器发送加密数据和密钥，Fritz只会把密钥提供给授权程序。这样整个环境就是trustworthy的。


#### 4. TC的利益相关
Disney等娱乐公司当然是最大受益方。

Intel垄断PC芯片，想要扩张，就要扩大PC市场，保证PC的DRM是避免PC地位下降的防守策略。

Microsoft可以得益于：
1. 卖出更多正版
2. 增强用户黏性，提升换用其他软件的成本

各种安全软件提供商会血崩。

有权利掌控TC基础设施的一方会拥有强大的独裁权力，可能被滥用。


#### 云舒的观点
关于可信计算，就我的判断这确实是一个理想中的东西，解决的是真空中的球形鸡的问题，对于真实的环境毫无用处，对于其它理论的推进也毫无帮助，研究者是有意无意的骗子。做这个结论，是因为我很懂安全攻防，同时懂一点点可信计算理论。

回到技术的角度，我假设你可以在计算机里面搞个芯片，对所有的进程作签名，没签名的进程不许启动（其实这步在企业中已经是不可实现的了，假设在某些特殊特殊再特殊的部门可以实现），有用？SQL注入是怎么做的？恶意代码在数据库的进程内部直接执行了。溢出攻击怎么做的？恶意代码在攻击目标的进程内部直接执行了。XSS怎么做的？CSRF怎么做的？恶意代码是你自己在浏览器里面执行的。

why？这是冯诺伊曼计算机结构决定的，数据和指令没有分开啊大哥。可信计算通过进程级别的签名能够解决的了？你能够对CPU的每一条指令签名么？（且不说还有无数的网络攻击，ARP攻击怎么做的？交换机端口劫持怎么做的？BGP劫持怎么做的？）

你说用TPM芯片作计算机认证，OK，这个没问题。但是这对于企业安全来说，是细枝末节的细枝末节。每年有多少入侵是因为员工PC非法授权入侵的？沧海一粟。员工都是上网看了几个网站，然后就有恶意代码在浏览器里面执行了就上线了好么？用TPM作全盘加密比如微软的BitLocker，但是别人根本不依赖TPM，有没有这东西无所谓啊，而且全盘加密对企业安全重要么？有多少企业实施了？

不要想着从最底层，从BIOS层解决问题。越到底层，丢失的上下文越多，数据越失去意义。可信计算在企业中无法实施，而且即使实施了，在实质性的提升企业安全能力上面，解决不了任何问题。现在不能，将来也不能。我就是死黑可信计算，如果谁拿出可信计算在企业中的成功案例，我立马道歉。

#### 现状总结
tcg在pc上失败了，在移动领域被tee抢占风头，物联网也是悲剧，目前主流物联网安全方案都没有tcg的事。物联网上是碎片化的解决方案，各个芯片方案商方案都不一样。

可信计算无法防止对应用层漏洞的攻击，然而大部分攻击都是针对应用层的。

最新的可信计算保护的范围越来越小，不一定算严格的可信计算，如ARM的TrustZone，Intel的SGX。

<!--Week2~3---->
# 设计原则与底层实现

## 设计原则: 信息保护 (see also chapter 5 of Gasser book)
### Glossary
- Capability: In a computer system, an unforgeable ticket, which when presented can be taken as incontestable proof that the presenter is authorized to have access to the object named in the ticket.
- Certify: To check the accuracy, correctness, and completeness of a security or protection mechanism
- Confinement: Allowing a borrowed program to have access to data, while ensuring that the program cannot release the information.
- Descriptor: A protected value which is (or leads to) the physical address of some protected object.
- Domain: The set of objects that currently may be directly accessed by a principal.
- Permission: A particular form of allowed access, e.g., permission to READ as contrasted with permission to WRITE
- Prescript: A rule that must be followed before access to an object is permitted, thereby introducing an opportunity for human judgment about the need for access, so that abuse of the access is discouraged.
- Principal: The entity in a computer system to which authorizations are granted; thus the unit of accountability in a computer system.
- Propagation: When a principal, having been authorized access to some object, in turn authorizes access to another principal.
- Protected object: A data structure whose existence is known, but whose internal organization is not accessible, except by invoking the protected subsystem (q.v.) that manages it.
- Revoke: To take away previously authorized access from some principal.
- *Security: With respect to information processing systems, used to denote mechanisms and techniques that control who may use or modify the computer or the information stored in it.*
- *Privacy: The ability of an individual (or organization) to decide whether, when, and to whom personal (or organizational) information is released.*

### 基本原则
#### 三种安全侵犯的类别：
1. 未授权的信息发布。
2. 未授权的信息修改。
3. 未授权的拒绝使用。
#### 5个信息保护的功能等级：
后四个才有意义，是动态改变访问授权的系统。
1. Unprotected systems：可能有许多防错机制，但本质上完全不安全。
2. All-or-nothing systems：为用户提供隔离，使之就像在用私人pc，也有一些共享lib。
3. Controlled sharing：明确规定谁能访问哪个数据项。每个文件维护用户列表，详注读、写、执行权。
4. User-programmed sharing controls：用户可以编写protected objects+subsystem，subsystem提供protocol，完全避免外界直接访问object，可以提供更灵活复杂的数据访问控制，比如每天几点到几点允许谁查阅某文件，其他时候拒绝访问。
5. Putting strings on information：以上三种都只是在release信息的条件上做文章，这一层是在release之后仍然对信息做限制或警告，比如在文件上打印Top Secret，表明这是不允许外泄的机密文件。

#### 8个基于经验的设计原则：
- Economy of mechanism： 设计得越小越好！常规使用软件不会用到奇葩或非法路径，所以错误很难自动滚出来，所以这种代码依赖line-by-line inspection和硬件检测，程序越小越方便。
- Fail-safe defaults：用白名单，不用黑名单，这样名单不全问题不大。创建之初默认不应该给任何用户或程序任何特权。
- Complete mediation：所有访问都得查，那种记住check结果的思路很可能有问题。
- Open design：设计不应该成为秘密。安全机制不应该基于潜在攻击者的无知，因为他们说不定哪天就有知了。
- Separation of privilege：一个需要两个key来unlock的保护机制更加鲁棒也更加灵活。
- Least privilege：每个程序或用户要做某事时只需要获取最低的权限，不应获取额外的权限。
- Least common mechanism：减少那些对多个用户通用的共享机制，尤其是涉及共享变量的。
- Psychological acceptability：用户接口应该好用，不要默认地就容易出错，也要符合用户对安全机制的思维印象。

传统物理安全分析者提出的额外两点，不是完全适用信息安全：
- Work factor： 比较规避防御机制的成本与攻击者的资源，例如算算暴力破解RSA的work factor，自然是比较大的。
- Compromise recording：记录信息的compromise(不得不变的一些东西)，比如文件timestamp，有时就是被人改了的证据。

#### 虚拟机的例子（time-sharing system的地址隔离）
一个vm对几个用户来说大家都在单机，察觉不到其他人，除了性能差了点。主要隔离手段是descriptor寄存器，descriptor存放可访问的内存的base和bound。只有privilege态才能load descriptor，有一个supervisor程序在privilege态运行并模拟各个虚拟cpu。其实和OS内核态的思路一样，就是等级制度。

这个例子抽象以下就是三个防御措施：
- descriptor机制保护program界限：guard就是强制descriptor限制的硬件。带门之不可穿越之墙就是逼迫所有内存引用都要经过descriptor限制的硬件机制。descriptor的限制检查很简单，就是看看地址是否在A~B。
- privilege bit机制保护descriptor内容：查看程序是否在特权态，不是就不准访问、篡改descriptor。
- 允许非特权程序执行一个指令“开启特权态并将控制权转交给supervisor”，不允许非特权程序privilege bit为on，特权程序可以变得不特权。

#### authen系统的例子
虚拟机若与终端相连，就得身份验证，第二个例子就是authen system。常用password或不可伪造之证物（钥匙、刷脸）来单向authenticate user。问题就在于user不能authenticate系统，这样入侵者可以拦截所有user输入再转发给系统，这就是隐患。
解决方案是system和user持有相同的key，然后将交流信息encipher+decipher，这样的authen就不怕拦截转发了。
其实这个在密码学里讲了很多，mac then encrypt。

#### shared information的实现
- list-oriented，每个guard维护一个用户list，允许多个用户使用目标数据。
- ticket-oriented，guard只有一个identifier的描述，每个user有很多identifiers，或者说tickets，即门票。

### 基于Descriptor的保护系统
#### 地址隔离
内存分段，即segment，用descriptor描述。就是现代os里的东西。
#### The Capability System
##### 基本结构
capability system可以由supervisor+privilege bit实现。
##### 共享的动态授权
Sender's part:
- Sender learns receiver's principal identifier via a communication path outside the system.
- Sender transmits receiver's principal identifier to some program running inside the system under the accountability of the sender.
- Sender's program uses receiver's principal identifier to ensure that only virtual processors operating under the accountability of the receiver will be able to obtain the capability being transmitted.

Receiver's part:
- Receiver learns sender's principal identifier, via a communication path outside the system.
- Receiver transmits sender's principal identifier to some program running inside the system under the accountability of the receiver.
- Receiver's program uses the sender's principal identifier to ensure that only a virtual processor operating under the accountability of the sender could have sent the capability being received.

##### Propagation(Copy Bit!)
 A bit added to a capability (the copy bit) may be used to indicate whether or not the capability may be stored in a segment. If one user gives another user access to a capability with the copy bit OFF, then the second user could not make copies of the capability he has borrowed. Propagation would be prevented, at the price of lost flexibility.

#### 访问控制列表系统(Prescript!）
Capability system如果是ticket-oriented，那么Access Control List System必然是list-oriented。

The hierarchical control scheme might be used in a timesharing system as follows. The first access controller created is given an access control list naming one user, a system administrator. The system administrator creates several access controllers (for example, one for each department in his company) and grants permission to modify access in each controller to the department administrator. The department administrator can create additional access controllers in a tree below the one for his department, perhaps for subdepartments or individual computer users in his department. These individual users can develop any pattern of sharing they wish, through the use of access control lists in access controllers, for the segments they create. In an emergency, however, the department administrator can intevene and modify any access control list in his department. Similarly, the system administrator can intervene in case a department administrator makes a mistake or is unavailable.41


Whenever an attempt is made to modify an access control list (either by a special store instruction or by a call to a supervisor entry, depending on the implementation), the access-modifying permission of the higher level access controller regulating the access control list is checked as always. If the permission exists, the *prescript field* of the access control list that is about to be modified is examined, and some action, depending on the value found, is automatically triggered. The following list suggests some possible actions that might be triggered by the prescript value, and some external policies that can be modeled with the prescript scheme:
- No action.
- Identifier of principal making change is logged (the "audit trail").
- Change is delayed one day ("cooling-off" period).
- Change is delayed until some other principal attempts the same change ("buddy" system).
- Change is delayed until signal is received from some specific (system-designated) principal ("court order").

#### Protecting Objects Other Than Segments
[这几段以后用到再看吧，尤其是访问控制列表系统。](http://web.mit.edu/Saltzer/www/publications/protection/Descriptors.html)

## IA32的内存保护
Segment不必说，我以前写过。

Paging当时跳过了，不过IA32是提供page-level protection的：
- Restriction of addressable domain (supervisor and user modes).
- Page type (read only or read/write).

IA32的segment protection实际上已经成为一种legacy，paging开启之后，主要靠paging的protection，可以设置read-only，哪个权限下read-only。

## VM以及VM Monitor
Virtualization本质上是接口实现解耦的过程，是guest system与host之间同构(isomorphism)的构造。VM的实现就是用真实硬件+软件一起实现一个接口。

VM分类：
- Process VM：基于特定ISA开发的VM，为Application层提供虚拟ABI。缺点是不同硬件平台要重新开发，不同操作系统也要重新开发。在Process VM上，程序编译出来字节码和真实的差不多，只是没有详细的寄存器分配，然后根据ISA去跑。换平台字节码要重新编译。
- High Level Language VM：基于跨平台理念开发的VM，其实就是硬件解耦做的更好。在编译时生成更加抽象更通用的generic stack-based ISA code。这种虚拟ISA本质上就是HLLVM跑的机器码。JVM和CLI .Net是最著名的HLLVM。
- System VM：其实就是一台硬件上的的多个软件分身，每一个都感觉自己独一无二，这种感觉依赖VMM(又叫hypervisor)。

没提到bochs，qmenu这种完全模拟的，应该是接近Full emulation，所以不算virtualization。

至于VMM，实际上是运行在VM与多个客户终端间的another layer of indirection，将file、user、group、process tree、device、semaphore/shared memory/msgs全部isolate。VMM又称Hypervisor。VMM使得各个用户觉得自己拥有所有硬件，实际上是分享的。譬如用户终端在调用syscall时，VVM知道ISR在哪，相当于中介。用户的os运行在较低privilege的mode下。VVM则是kernel mode。此外，VVM还再存了一个page table，把用户的逻辑地址映射到真实machine地址上。目前Xen、KVM、OpenVZ(只有linux版，但是也好用)就是最常用的VMM，性能比Process VM高多了，又不像JVM之类的有语言限定，模拟的是系统，所以在企业界有广泛应用，可以大幅提高单个服务器主机的利用率。16GB server跑Xen虚拟给两个users，8GB。

Xen在linux上是个application， KVM是个kernel module。SmartOS是一个基于KVM的云操作系统，可以关注下。


## Chromium的体系结构
两层结构：
- browser kernel：与操作系统互动。代表user行事。它将rendering engine当做解析web内容并输出渲染后的位图文档的黑箱。输入输出依赖IPC。
- rendering engine：在一个privilege严格受限的沙盒内运行。代表web发布内容。即使入侵者利用rendering engine漏洞获取其最高权限，也会被沙盒隔离，无法读写用户的文件系统。
