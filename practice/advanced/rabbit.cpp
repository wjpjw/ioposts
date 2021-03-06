/*
题意：给定一串环形数，两个兔子可以任选一个起点一个向左跳，一个向右跳，不可回头，两个兔子每次跳的位置数字要相同，并且可以在同一个位置上，求最多可以跳多少次。

思路：放了一个环上，如果从起点反向之后，每次跳的位置的数字相同，我们把他们的相遇位置切开，可以发现是一个回文串。

所以问题就是一个环求最长的回文串了。按照平常的思路，倍增这个串，然后正常求就可以了。

有一个问题就是对于偶数长度的时候，如第二组样例，我们可以把他看成n-1的串，最终跳到了1上。
*/
