---
title: Archlinux试玩
---

Archlinux的安装是手动的，从中能学到一些东西，不过本质上与其他发行版是一样的，不涉及内核修改编译这种真正的定制。装了gnome后，和其他linux发行版感觉差不多。

<!--more-->

### 配置工具
1. dhcpcd：一个dhcp客户端。dhcp服务器一般就在局域网的路由器上，用于自动分配正确ip给各个机器。dhcpcd.conf里可以设置静态路由，hostname，static profile等。
2. 启动或关闭服务：systemctl start/stop example.service
3. pacman：-Syy，同步数据库；-S elinks，安装elinks；-Ss xxx，搜索xxx；-R是删包。
4. fdisk或gdisk /dev/sda就可以进入partition界面，创建partition table。操作相当简单。
5. lsblk查看bulk device的挂载情况。
6. fstab配置挂载，locale.conf配置语言。
