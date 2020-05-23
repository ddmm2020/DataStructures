/*
 * @Descripttion: Graph application
 * @version: 
 * @Author: ddmm
 * @Date: 2020-05-19 15:08:27
 * @LastEditors: ddmm
 * @LastEditTime: 2020-05-23 16:37:04
 */ 
#include<bits/stdc++.h>
#include"Graph.h"
using namespace::std;

//最大定点数
const int MAX_VERTEX_NUM=20;

const char info_file[30]="./info.txt";
const char path_file[30]="./path_info.txt";

std::vector<std::string> s_split(const std::string& in, const std::string& delim) {
    std::regex re{ delim };
    // 调用 std::vector::vector (InputIterator first, InputIterator last,const allocator_type& alloc = allocator_type()
    return std::vector<std::string> {
        std::sregex_token_iterator(in.begin(), in.end(), re, -1),
        std::sregex_token_iterator()
    };
};

void CGraph::loadVex(){//从info.txt 加载景点信息
	FILE* pf = fopen("D:/C++/dataStructures/do2/info.txt", "rb");
	if(!pf){
		cout<<"open file error!\n";
	}
	fseek(pf, 0, SEEK_END);
	int len = ftell(pf);
	//cout<<len;
	char* infoBuf = new char[len];
	fseek(pf, 0, SEEK_SET);
	fread(infoBuf, 1, len, pf);
	fclose(pf);
	m_nVexNum=0;
	int index=0;
	int temp=0;
	int vexNum=0;
	char vexName[20];
	char vexDesp[1024];
	//Vex vex=[m_nVexNum];
	int i=0;
	id_to_string.reserve(MAX_VERTEX_NUM);
	for(;i<len;i++){
		if(infoBuf[i]=='\r') {i+=2;break;}
		m_nVexNum=m_nVexNum*10+infoBuf[0]-'0';
	}

	for(;i<len;i++){
		while(infoBuf[i]!=','){
			temp=temp*10+infoBuf[i++]-'0';
		}
		m_aVexs[vexNum].num=temp;
		temp=0;
		index=0;
		while (infoBuf[++i]!=',')
		{
			m_aVexs[vexNum].name[index++]=infoBuf[i];
		}
		index=0;
		while (infoBuf[++i]!='\r')
		{
			m_aVexs[vexNum].desp[index++]=infoBuf[i];
		}
		memcpy(id_to_string[m_aVexs[vexNum].num],m_aVexs[vexNum].name,20);
		vexNum++;
		i++;
	}
	delete[] infoBuf;
}

void CGraph::loadPath(){//从path_info.txt文件加载路径信息
	FILE* path_pf = fopen("D:/C++/dataStructures/do2/path_info.txt", "rb");
	if(!path_pf){
		cout<<"open file error!\n";
	}
	fseek(path_pf, 0, SEEK_END);
	int path_file_len = ftell(path_pf);
	//cout<<len;
	char* pathBuf = new char[path_file_len];
	fseek(path_pf, 0, SEEK_SET);
	fread(pathBuf, 1, path_file_len, path_pf);
	fclose(path_pf);
	//auto str=s_split
	int u,v,w;
	m_aEdgeNum=0;
	for(int i=0;i<path_file_len;i++){
		u=v=w=0;
		while(pathBuf[i]!=','){
			u=u*10+(pathBuf[i++] - '0');
		}
		i++;
		while(pathBuf[i]!=','){
			v=v*10+(pathBuf[i++] - '0');
		}
		i++;
		while(pathBuf[i]!='\r'){
			w=w*10+(pathBuf[i++] - '0');
		}
		i++;
		Edge temp_edge(u,v,w);
		m_aEdges[m_aEdgeNum++]<<temp_edge;
		
		m_aAdjMatrix[u][v]=w;
		m_aAdjMatrix[v][u]=w;
		// cout<<u<<" "<<v<<" "<<w<<endl;

	}
	//cout<<m_aEdges[0].vex1<<" "<<m_aEdges[0].vex2<<m_aEdges[0].weight<<" ";
	delete[] pathBuf;
}

void CGraph::Init(){//用text文件信息初始化图
	//读取景点信息
    loadVex();
	//读取路径
	loadPath();
}

bool CGraph::InsertVex(Vex sVex){//插入顶点
	if(m_nVexNum==MAX_VERTEX_NUM){
		return false;
	}
	m_aVexs[m_nVexNum++]=sVex;
	Edge temp(7,0,100);
	InsertEdge(temp);
	return true;
}

bool CGraph::InsertEdge(Edge sEdge){//插入边
	if(sEdge.vex1<0||sEdge.vex1>=m_nVexNum||sEdge.vex2<0||sEdge.vex2>=m_nVexNum){
		cout<<"insert Edge error\n";
		return false;
	}
	m_aAdjMatrix[sEdge.vex1][sEdge.vex2]=sEdge.weight;
	m_aAdjMatrix[sEdge.vex2][sEdge.vex1]=sEdge.weight;
	cout<<"insert Edge success\n";
	return true;
};
void CGraph::ShowVex(){
	for(int i=0;i<m_nVexNum;i++){
		printf("景点编号：%d 名称：%s\n",m_aVexs[i].num,m_aVexs[i].name);
	}
}

Vex CGraph::GetVex(int nVex){//获取编号对应的顶点信息
	return m_aVexs[nVex];
}

int CGraph::GetVexnum(){//获取当前景点数
	return m_nVexNum;
}

int CGraph::FindEdge()//查询相邻节点
{
	cout<<"============查询节点信息===================\n";
	ShowVex();
	cout<<"请输入查询的节点\n";
	int nVex;
	cin>>nVex;
	int k=0;
	set<int> vexs;
	for(int i=0;i<m_nVexNum;i++){
		if(m_aAdjMatrix[i][nVex]!=0){
			vexs.insert(i);
			k++;
		}
		if(m_aAdjMatrix[nVex][i]!=0){
			vexs.insert(i);
			k++;
		}
	}
	cout<<"相邻景点名称\n";
	for(auto it=vexs.begin();it!=vexs.end();++it){
		cout<<id_to_string[*it]<<" ";
	}
	return vexs.size();
}

void CGraph::config(){
	int start=0,end=0;
	cout<<"\n=====查找景点路径======\n";
	cout<<"输入起点:\n";
	cin>>start;
	cout<<"输入终点:\n";
	cin>>end;
	visited=vector<int>(m_nVexNum,0);
	stack.reserve(m_nVexNum);
	depth=1;
	DFS(visited,stack,start,end,depth);
	DFSTraverse();
}

void CGraph::DFS(vector<int> &visited,vector<int>&stack,int node,int end_num,int depth){
	depth++;
	stack.push_back(node);
	visited[node]=1;
	if(node==end_num){
		path_num++;
		paths.emplace_back(depth,stack);
		stack.pop_back();
		return;
	}
	if(depth==m_nVexNum) {
		stack.pop_back(); 
		return;
	};
	for(int i=0;i<m_nVexNum;i++){
		if(m_aAdjMatrix[node][i]!=0&&visited[i]==0){
			DFS(visited,stack,i,end_num,depth);
			visited[i]=0;
		};
	}
	stack.pop_back();
	visited[node]=-1;
}
void CGraph::DFSTraverse(){// 显示查找结果

	for(auto it=paths.begin();it!=paths.end();++it){
		//cout<<(*it).length<<"\n";
		for(int i=0;i<(*it).length-1;i++){
			cout<<(*it).path[i]<<" ";
		}
		cout<<endl;
		for(int i=0;i<(*it).length-1;i++){
			cout<<id_to_string[(*it).path[i]]<<" ";
		}
		cout<<endl;
	}
}

void CGraph::Dijkstra(int start){
	printf("\n==========查询%s与附近所有景点的最短距离============\n",id_to_string[start]);
	//cout<<m_nVexNum;
	//int dij_weights[m_nVexNum];
	vector<int> dij_weights(m_nVexNum,30000);
	int passed_cnt=0;
	queue<int> q;
	vector<int> visited(m_nVexNum,0);
	visited[start]=-1;
	dij_weights[start]=0;
	//int visited[m_nVexNum]={0};
	for(int i=0;i<m_nVexNum;i++){
		if(m_aAdjMatrix[start][i]!=0){
			dij_weights[i]=min(dij_weights[i],m_aAdjMatrix[start][i]);
			visited[i]=-1;
			q.push(i);
		}
	}
	int node;
	while(!q.empty()){
		node=q.front();
		q.pop();
		for(int i=0;i<m_nVexNum;i++){
			if(m_aAdjMatrix[node][i]>0&&visited[i]==0){
				dij_weights[i]=min(dij_weights[i],dij_weights[node]+m_aAdjMatrix[node][i]);
				visited[i]=-1;
				q.push(i);
			}
		}
	}

	for(int i=0;i<m_nVexNum;i++){
		//cout<<id_to_string[start]<<"--->"<<id_to_string[i]<<"最短路程："<<dij_weights[i]<<"\n";
		cout<<start<<"--->"<<i<<"最短路程："<<dij_weights[i]<<"\n";
	}
}

void CGraph::Floyd(int start,int end){
	//assert(start!=end);
	int DP_weights[20][20];
	int path[20][20]={0};
	//m_aAdjMatrix;
	// memcpy(DP_weights,m_aAdjMatrix,20*20*sizeof(int));
	
	//初始化动态权重矩阵
	for(int i=0;i<m_nVexNum;i++){
		for(int j=0;j<m_nVexNum;j++){
			if(m_aAdjMatrix[i][j]==0){
				DP_weights[i][j]=30000;
			}
			else{
				DP_weights[i][j]=m_aAdjMatrix[i][j];
			}
			if(i==j) DP_weights[i][j]=0;
		}
	}

	//初始化路径矩阵
	for(int i=0;i<m_nVexNum;i++){
		for(int j=0;j<m_nVexNum;j++){
			path[i][j]=j;
		}
	}


	//DP 矩阵更新策略
	for(int k=0;k<m_nVexNum;k++){
		for(int i=0;i<m_nVexNum;i++){
			for(int j=0;j<m_nVexNum;j++){
				if(DP_weights[i][k]+DP_weights[k][j]<DP_weights[i][j]){
					DP_weights[i][j]=DP_weights[i][k]+DP_weights[k][j];
					path[i][j] = path[i][k]; //保存中转节点
				}
			}
		}
	}
	//路径矩阵
	// for(int i=0;i<m_nVexNum;i++){
	// 	for(int j=0;j<m_nVexNum;j++){
	// 		cout<<path[i][j]<<" ";
	// 	}cout<<endl;
	// }

	//推导经过的景点
	//所有节点的最短路径信息
	// for(int i=0;i<m_nVexNum;i++){
	// 	for(int j=0;j<m_nVexNum;j++){
	// 		cout<<i<<" ";
	// 		int temp = path[i][j];
    // 		while(temp != j) {
	// 			cout<<temp<<" ";
    //     		temp = path[temp][j];
				
    // 		}
	// 		cout<<j<<endl;
	// 	}
	// }

	cout<<"\n==========路径导航============\n";
	cout<<"起点:"<<id_to_string[start]<<"\t目标位置:"<<id_to_string[end]<<endl;
	//指定节点的路径
	int temp=path[start][end];
	cout<<"导航路径"<<id_to_string[start]<<"->";
	while (temp!=end)
	{
		cout<<id_to_string[temp]<<"->";
		temp=path[temp][end];
	}
	cout<<id_to_string[end]<<"\n总距离："<<DP_weights[start][end]<<"\n";
};


inline bool sortEdge(const Edge a, const Edge b)
{
	return a.weight<b.weight;
}

void CGraph::FindMinTree(){//Kruskal算法
	cout<<"\n========最小生成树=========\n";
	sort(m_aEdges,m_aEdges+m_aEdgeNum,sortEdge);
	vector<bool> visited(m_nVexNum,true);
	int now_edges=0;
	int price=0;
	vector<Edge> paths;
	for(int i=0;i<m_aEdgeNum;i++){
		if(visited[m_aEdges[i].vex1]||visited[m_aEdges[i].vex2]){
			now_edges++;
			price+=m_aEdges[i].weight;
			paths.push_back(m_aEdges[i]);
			visited[m_aEdges[i].vex1]=false;
			visited[m_aEdges[i].vex2]=false;
			if(now_edges==m_aEdgeNum-1) break;
		}
	}
	printf("最少修建总费用：%d\n待修建路径如下:\n",price);
	for(auto it=paths.begin();it!=paths.end();++it){
		cout<<id_to_string[(*it).vex1]<<"->"<<id_to_string[(*it).vex2]<<" "<<(*it).weight<<"\n";
	}

}

int main(){
	CGraph g=CGraph();
	g.Init();
	//sVex.num=8;
	char s1[20]="hust";
	char s2[1024]="we are 985 university";
	Vex sVex(8,s1,s2);
	// if(!g.InsertVex(sVex)){
	// 	cout<<"insert node error\n";
	// }
	// else{
	// 	cout<<"insert node success\n";
	// }
	//g.FindEdge();
	//g.config();
	g.Dijkstra(0);
	g.Floyd(0,6);
	g.FindMinTree();
	// memcpy(sVex.name,s1,20);
	// memcpy(sVex.name,s2,1024);
}

