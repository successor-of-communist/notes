#include<iostream>
#include<string.h>
using namespace std;
const int inf=1<<30;
const int MAXN = 50010;//点数
const int MAXM = 200010;//边数
struct Edge
{
    int to,next,val;
}edge[MAXM];
int head[MAXN],tot;
int Low[MAXN],DFN[MAXN],Stack[MAXN],Belong[MAXN];//Belong数组的值是1~scc
int Index,top;
int scc;//强连通分量的个数
bool Instack[MAXN];
int indeg[MAXN],outdeg[MAXN];
int cost[105];
void addedge(int u,int v,int val)
{
    edge[tot].val=val;
    edge[tot].to = v;edge[tot].next = head[u];head[u] = tot++;
}
void Tarjan(int u)
{
    int v;
    Low[u] = DFN[u] = ++Index;
    Stack[top++] = u;
    Instack[u] = true;
    for(int i = head[u];i != -1;i = edge[i].next)
    {
        v = edge[i].to;
        if( !DFN[v] )
        {
            Tarjan(v);
            if( Low[u] > Low[v] )Low[u] = Low[v];
        }
        else if(Instack[v] && Low[u] > DFN[v])
            Low[u] = DFN[v];
    }
    if(Low[u] == DFN[u])
    {
        scc++;
        do
        {
            v = Stack[--top];
            Instack[v] = false;
            Belong[v] = scc;
        }
        while( v != u);
    }
}
void solve(int N)
{
    memset(DFN,0,sizeof(DFN));
    memset(Instack,false,sizeof(Instack));
    memset(indeg,0,sizeof(indeg));
    memset(outdeg,0,sizeof(outdeg));
    Index = scc = top = 0;
    for(int i=0;i<N;i++)
        cost[i]=inf;
    for(int i = 0;i < N;i++)
        if(!DFN[i])
            Tarjan(i);
    for(int i=0;i<N;i++)
    {
        for(int j=head[i];j!=-1;j=edge[j].next)
        {
            int v=edge[j].to;
            if(Belong[i]!=Belong[v])
            {
                cost[Belong[v]]=min(cost[Belong[v]],edge[j].val);
            }
        }
    }
    int ans=0;
    for(int i=1;i<=scc;i++)
    {
        if(cost[i]!=inf)
        {
            ans+=cost[i];
        }
    }
    printf("%d\n",ans);
}
void init()
{
    tot = 0;
    memset(head,-1,sizeof(head));
}
int main(){
    int n,m,u,v,val;
    while(~scanf("%d%d",&n,&m))
    {
        init();
        while(m--)
        {
            scanf("%d%d%d",&u,&v,&val);
            addedge(u,v,val);
        }
        solve(n);
    }
    return 0;
}

