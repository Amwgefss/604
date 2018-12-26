#include <stdio.h>
#include <string.h>
#include <malloc.h>
#define MAX_VERTEX 100				//顶点最大个数
#define vertexData int
typedef struct ArcNode{
	int adjvex;						//该弧指向顶点的位置
	struct ArcNode *nextarc;		//指向下一条弧的指针
}ArcNode;							//弧结点
typedef struct{
	vertexData data;				//顶点数据
	int intdegree;					//该顶点的入度
	ArcNode *firstarc;				//指向该顶点第一条弧的指针
}vertexnode,Adjlist[100];			//顶点结点
typedef struct {
	Adjlist vextives;				//顶点邻接表
	int vexnum,arcnum;				//图的顶点数和弧数
}ALgraph;
int show[MAX_VERTEX];				//保存等输出的序列
int g = 0;							//记录是否所有顶点都被保存
int t= 0;							//存放序列的个数
int visited[MAX_VERTEX];			//标记顶点是否被访问（0表示未被访问，1表示被访问）
ALgraph creatgraph(){				//创建图
	int m,n,i,j,k;					//m是顶点个数，n是弧的个数
	Adjlist G;						//顶点信息
	ArcNode *L;						//弧信息
	printf("请输入顶点数:");
	scanf("%d",&m);
	printf("请顺次输入顶点数据:\n");
	for( i=1;i<=m;i++){				//初始化
		scanf("%d",&G[i].data);		//输入顶点数据
		G[i].intdegree = 0;			//入度置0
		G[i].firstarc = NULL;		//各顶点的邻接点置空
	}
	printf("请输入边数:");
	scanf("%d",&n);
	printf("请输入边的信息:\n");
	for( i=1;i<=n;i++){				//对边的信息进行记录
		scanf("%d %d",&j,&k);
		L = (ArcNode *)malloc(sizeof(ArcNode));
		L->adjvex = k;
		L->nextarc = G[j].firstarc;
		G[j].firstarc = L;
		G[k].intdegree++;			//每有一条边顶点入度加1
	}
	ALgraph al;						//创建成图
	for( i=1;i<=m;i++){
		al.vextives[i]=G[i];
	}
	al.vexnum = m;
	al.arcnum = n;
	return al;
}
void TopoSort(ALgraph G,int i){		//拓扑排序
	int j;
	ArcNode *s;						//记录弧结点
	show[++g]=G.vextives[i].data;					//把顶点存到待输出数组里
	visited[i]=1;					//标记改为已访问
	s=G.vextives[i].firstarc;
	while(s!=NULL){					//相关结点入度减1
		int a=s->adjvex;
		G.vextives[a].intdegree--;
		s=s->nextarc;
	}
	for(j=1;j<=G.vexnum;j++){		//如果有未访问且入度为0的继续递归
		if((visited[j]==0)&&G.vextives[j].intdegree==0)
			TopoSort(G,j);
	}
	if(g==G.vexnum){				//如果所有顶点都在show里则输出
		for(j=1;j<=g;j++){
			printf("V%d ",show[j]);
		}
		printf("\n");
		t++;
	}
	visited[i]=0;					//把该点置为未访问
	while(s!=NULL){					//恢复相关顶点的入度
		int a=s->adjvex;
		G.vextives[a].intdegree++;
		s=s->nextarc;
	}
	g--;
} 
int main(){
	ALgraph alg;
	alg = creatgraph();
	for(int i=1;i<MAX_VERTEX;i++)	//初始化访问标志为未访问
		visited[i]=0;
	for(int j=1;j<alg.vexnum;j++)	//顶点遍历
		if(alg.vextives[j].intdegree==0&&visited[j]==0)
			TopoSort(alg,j);
		if(t==0)
			printf("此图存在环");
		else
			printf("\n网共有%d个拓扑排序\n",t); 
		return 0;
}
