---
title: 安全计算系统
tags:
- 学术
- 技术
---

# 安全计算系统的基本概念
### What is Computer Security(gassbook-c1)
####SECRECY, INTEGRITY, AND DENIAL OF SERVICE
1. Secrecy/Confidentiality：protecting the information from disclosure to unauthorized parties.
2. Integrity: protecting information from being modified by unauthorized parties.
3. Denial of service: 可能是机器故障导致信息损失。

计算安全主要研究的是secrecy，信息不泄露。至于信息的integrity主要是指信息没被修改，实际上在商业软件中更常用，不过没多少研究者感兴趣，还好integrity需要的技术和secrecy差不多。至于denial of service虽然也是信息安全的话题，却不再讨论范围内，原因是软件正确性这一话题太难了，大多数情况下根本实现不了。

<!--more-->

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






# Design principles and hardware/low level mechanisms
