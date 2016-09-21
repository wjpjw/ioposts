/*
【题意】一个人依次参加n个舞会，每个舞会需要穿的衣服种类为ai,参加完一个舞会后可以脱衣服或者再穿一件衣服或者不做任何操作，注意，脱下的衣服不能再穿，问最少需要多少件衣服。
【思路】区间dp，dp[i][j]表示参加第i-j舞会需要的最少衣服。参加完 第i个舞会后的衣服可以脱掉或者继续穿在身上，若最优状态下是穿在身上的，则说明第i个舞会的衣服重复利用了。只需要枚举第i个舞会后，首次使用第i个舞会的衣服的时间即可。dp[i][j]=min(1+dp[i+1][j](脱掉第i个舞会的衣服),dp[i+1][k-1]+dp[k][j]) num[k]=num[i] i<k<=j;
*/

#include "wjp.h"

int dp[110][110];
int num[110];
int main()
{
	int t;
	cin>>t;

		int ca=1;
	while(t--)
	{
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>num[i];
		memset(dp,0,sizeof(dp));
		for(int len=1;len<=n;len++)
			for(int i=1;i+len-1<=n;i++)
			{
				int j=i+len-1;
				if(len==1)dp[i][j]=1;
				else{
					dp[i][j]=1+dp[i+1][j];
					for(int k=i;k<=j;k++)
					{
						if(num[i]==num[k])
							dp[i][j]=min(dp[i][j],dp[i+1][k-1]+dp[k][j]);
					}
				}
			}
		printf("Case %d: %d\n",ca++,dp[1][n]);
	}
	return 0;
}
