#include <stdio.h>
#include <string.h>
#include <malloc.h>
#define MAX_VERTEX 100				//����������
#define vertexData int
typedef struct ArcNode{
	int adjvex;						//�û�ָ�򶥵��λ��
	struct ArcNode *nextarc;		//ָ����һ������ָ��
}ArcNode;							//�����
typedef struct{
	vertexData data;				//��������
	int intdegree;					//�ö�������
	ArcNode *firstarc;				//ָ��ö����һ������ָ��
}vertexnode,Adjlist[100];			//������
typedef struct {
	Adjlist vextives;				//�����ڽӱ�
	int vexnum,arcnum;				//ͼ�Ķ������ͻ���
}ALgraph;
int show[MAX_VERTEX];				//��������������
int g = 0;							//��¼�Ƿ����ж��㶼������
int t= 0;							//������еĸ���
int visited[MAX_VERTEX];			//��Ƕ����Ƿ񱻷��ʣ�0��ʾδ�����ʣ�1��ʾ�����ʣ�
ALgraph creatgraph(){				//����ͼ
	int m,n,i,j,k;					//m�Ƕ��������n�ǻ��ĸ���
	Adjlist G;						//������Ϣ
	ArcNode *L;						//����Ϣ
	printf("�����붥����:");
	scanf("%d",&m);
	printf("��˳�����붥������:\n");
	for( i=1;i<=m;i++){				//��ʼ��
		scanf("%d",&G[i].data);		//���붥������
		G[i].intdegree = 0;			//�����0
		G[i].firstarc = NULL;		//��������ڽӵ��ÿ�
	}
	printf("���������:");
	scanf("%d",&n);
	printf("������ߵ���Ϣ:\n");
	for( i=1;i<=n;i++){				//�Աߵ���Ϣ���м�¼
		scanf("%d %d",&j,&k);
		L = (ArcNode *)malloc(sizeof(ArcNode));
		L->adjvex = k;
		L->nextarc = G[j].firstarc;
		G[j].firstarc = L;
		G[k].intdegree++;			//ÿ��һ���߶�����ȼ�1
	}
	ALgraph al;						//������ͼ
	for( i=1;i<=m;i++){
		al.vextives[i]=G[i];
	}
	al.vexnum = m;
	al.arcnum = n;
	return al;
}
void TopoSort(ALgraph G,int i){		//��������
	int j;
	ArcNode *s;						//��¼�����
	show[++g]=G.vextives[i].data;					//�Ѷ���浽�����������
	visited[i]=1;					//��Ǹ�Ϊ�ѷ���
	s=G.vextives[i].firstarc;
	while(s!=NULL){					//��ؽ����ȼ�1
		int a=s->adjvex;
		G.vextives[a].intdegree--;
		s=s->nextarc;
	}
	for(j=1;j<=G.vexnum;j++){		//�����δ���������Ϊ0�ļ����ݹ�
		if((visited[j]==0)&&G.vextives[j].intdegree==0)
			TopoSort(G,j);
	}
	if(g==G.vexnum){				//������ж��㶼��show�������
		for(j=1;j<=g;j++){
			printf("V%d ",show[j]);
		}
		printf("\n");
		t++;
	}
	visited[i]=0;					//�Ѹõ���Ϊδ����
	while(s!=NULL){					//�ָ���ض�������
		int a=s->adjvex;
		G.vextives[a].intdegree++;
		s=s->nextarc;
	}
	g--;
} 
int main(){
	ALgraph alg;
	alg = creatgraph();
	for(int i=1;i<MAX_VERTEX;i++)	//��ʼ�����ʱ�־Ϊδ����
		visited[i]=0;
	for(int j=1;j<alg.vexnum;j++)	//�������
		if(alg.vextives[j].intdegree==0&&visited[j]==0)
			TopoSort(alg,j);
		if(t==0)
			printf("��ͼ���ڻ�");
		else
			printf("\n������%d����������\n",t); 
		return 0;
}
