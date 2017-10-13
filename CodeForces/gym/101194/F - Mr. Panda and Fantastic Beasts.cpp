#include <bits/stdc++.h>
using namespace std;
#pragma comment(linker,"/stack:1024000000,1024000000")
#define db(x) cout<<(x)<<endl
#define pc(x) putchar(x)
#define ps(x) puts(x)
#define pf(x) push_front(x)
#define pb(x) push_back(x)
#define mp(x,y) make_pair(x,y)
#define ms(x,y) memset(x,y,sizeof x)
typedef long long LL;
const double pi=acos(-1),eps=1e-9;
const LL inf=0x3f3f3f3f,mod=1e9+7,maxn=312345,logmaxn=22,maxc=128;
struct sa{
	int a[maxn],c[maxn],sa[maxn],rk[maxn],height[maxn],rmq[maxn][logmaxn],t1[maxn],t2[maxn],n,m,p,*x,*y;
	// maxn:character total length + number of strings
	// logmaxn:log2(maxn)
	// maxc:character set size
	inline void init(){
		n=p=0,m=maxc,x=t1,y=t2;
	}
	inline int toid(char c){
		// transform character(from 1)
		return c-'a'+1;
	}
	inline void insert(char *s){
		while(*s)
			a[n++]=toid(*s++);
		a[n++]=0;
	}
	inline void build(){
		for(int i=0;i<m;i++)
			c[i]=0;
		for(int i=0;i<n;i++)
			c[x[i]=a[i]]++;
		for(int i=1;i<m;i++)
			c[i]+=c[i-1];
		for(int i=n-1;~i;i--)
			sa[--c[x[i]]]=i;
		for(int k=1;k<=n&&p<n;k<<=1){
			m=p,p=0;
			for(int i=n-k;i<n;i++)
				y[p++]=i;
			for(int i=0;i<n;i++)
				if(sa[i]>=k)
					y[p++]=sa[i]-k;
			for(int i=0;i<m;i++)
				c[i]=0;
			for(int i=0;i<n;i++)
				c[x[y[i]]]++;
			for(int i=1;i<m;i++)
				c[i]+=c[i-1];
			for(int i=n-1;~i;i--)
				sa[--c[x[y[i]]]]=y[i];
			swap(x,y);
			p=0;
			for(int i=0;i<n;i++)
				x[sa[i]]=i&&y[sa[i-1]]==y[sa[i]]&&(sa[i-1]+k<n?y[sa[i-1]+k]:n)==(sa[i]+k<n?y[sa[i]+k]:n)?p-1:p++;
		}
		for(int i=0;i<n;i++)
			rk[sa[i]]=i;
		for(int i=0,k=0;i<n;i++)
			if(!rk[i])
				height[0]=0;
			else{
				if(k)
					k--;
				int j=sa[rk[i]-1];
				while(i+k<n&&j+k<n&&a[i+k]==a[j+k])
					k++;
				height[rk[i]]=k;
			}
	}
	inline void initrmq(){
		for(int i=0;i<n;i++)
			rmq[i][0]=height[i];
		for(int j=1;(1<<j)<=n;j++)
			for(int i=0;i+(1<<j)-1<n;i++)
				rmq[i][j]=min(rmq[i][j-1],rmq[i+(1<<(j-1))][j-1]);
	}
	inline int query(int l,int r){
		int k=0;
		while((1<<(k+1))<=r-l+1)
			k++;
		return min(rmq[l][k],rmq[r-(1<<k)+1][k]);
	}
	inline int ranklcp(int l,int r){
		if(l==r)
			return n-sa[l]-1;
		return query(l+1,r);
	}
	inline int lcp(int l,int r){
		return ranklcp(min(rk[l],rk[r]),max(rk[l],rk[r]));
	}
}sa;
int t,n,l,l1,m,m1,ans,pos;
char s[maxn],str[maxn];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>t;
	for(int k=1;k<=t;k++){
		sa.init();
		cin>>n>>s;
		l=strlen(s),l1=l+n,ans=inf;
		sa.insert(s);
		for(int i=1;i<n;i++){
			cin>>str;
			l1+=strlen(str);
			sa.insert(str);
		}
		sa.build();
		for(int i=n;i<l1;i++)
			if(sa.sa[i]<l){
				m=sa.height[i],m1=inf;
				for(int j=i-1;j&&sa.sa[j]<l;j--)
					m=min(m,sa.height[j]);
				for(int j=i+1;;j++){
					m1=min(m1,sa.height[j]);
					if(j>=l1){
						m1=0;
						break;
					}
					else if(sa.sa[j]>=l)
						break;
				}
				m=max(m,m1);
				if(m<ans&&m<l-sa.sa[i])
					ans=m,pos=sa.sa[i];
			}
		printf("Case #%d: ",k);
		if(ans==inf)
			ps("Impossible");
		else{
			for(int i=0;i<=ans;i++)
				pc(s[i+pos]);
			printf("\n");
		}
	}
	return 0;
}