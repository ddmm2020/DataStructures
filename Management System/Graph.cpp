/*
 * @Descripttion: Graph application
 * @version: 
 * @Author: ddmm
 * @Date: 2020-05-19 15:08:27
 * @LastEditors: ddmm
 * @LastEditTime: 2020-05-23 22:20:40
 */ 

#include<bits/stdc++.h>
#include"Graph.h"
#include <windows.h>

using namespace::std;

//最大定点数
const int MAX_VERTEX_NUM=20;

const char info_file[60]="./vex.txt";
const char path_file[60]="./path_info.txt";

std::vector<std::string> s_split(const std::string& in, const std::string& delim) {
    std::regex re{ delim };
    // 调用 std::vector::vector (InputIterator first, InputIterator last,const allocator_type& alloc = allocator_type()
    return std::vector<std::string> {
        std::sregex_token_iterator(in.begin(), in.end(), re, -1),
        std::sregex_token_iterator()
    };
};


string UTF8ToGB(const char* str)
{
	string result;
	WCHAR *strSrc;
	LPSTR szRes;
 
	//获得临时变量的大小
	int i = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	strSrc = new WCHAR[i + 1];
	MultiByteToWideChar(CP_UTF8, 0, str, -1, strSrc, i);
 
	//获得临时变量的大小
	i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);
	szRes = new CHAR[i + 1];
	WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);
 
	result = szRes;
	delete[]strSrc;
	delete[]szRes;
 
	return result;
}

void CGraph::loadVex(){//从info.txt 加载景点信息
	ifstream in;
	in.open("D:/C++/dataStructures/do2/vex.txt");
 
	string s;
	//getline(t, s);
	//out << s << "\n";
	int cnt=0;
	m_nVexNum=0;
	int num;
	string name;
	string desp;
	while (std::getline(in, s))
	{
		if(cnt++%3==0){
			num=stoi(s);
		
		}
		if(cnt++%3==2){
			desp=s;
			Vex tmp(num,name,desp);
			id_to_string[m_nVexNum]=name;
			m_aVexs[m_nVexNum++]=tmp;
		}
		name=s;
		//string str = UTF8ToGB(s.c_str()).c_str();
	}
	in.close();
	// for(int i=0;i<m_nVexNum;i++){
	// 	cout<<m_aVexs[i].num<<" "<<m_aVexs[i].name<<" "<<m_aVexs[i].desp<<endl;
	// }
}


void CGraph::loadPath(){//从path_info.txt文件加载路径信息
	FILE* path_pf = fopen("D:/C++/dataStructures/do2/path_info.txt", "rb");
	if(!path_pf){
		cout<<"打开文件失败!\n";
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

bool CGraph::InsertVex(){//插入顶点
	cout<<"\n===========添加景点==========\n";
	if(m_nVexNum==MAX_VERTEX_NUM){
		return false;
	}
	string name="东湖公园";
	string desp="小朋友，来这里一起野餐啊！";
	Vex sVex(m_nVexNum,name,desp);
	id_to_string[m_nVexNum]=name;	
	m_aVexs[m_nVexNum]=sVex;
	Edge temp(m_nVexNum++,0,100);
	InsertEdge(temp);
	return true;
}

bool CGraph::InsertEdge(Edge sEdge){//插入边
	if(sEdge.vex1<0||sEdge.vex1>=m_nVexNum||sEdge.vex2<0||sEdge.vex2>=m_nVexNum){
		cout<<"插入边信息失败！\n";
		return false;
	}
	m_aEdges[m_aEdgeNum++]<<sEdge;
	m_aAdjMatrix[sEdge.vex1][sEdge.vex2]=sEdge.weight;
	m_aAdjMatrix[sEdge.vex2][sEdge.vex1]=sEdge.weight;
	cout<<"插入边信息成功！\n";
	return true;
};
void CGraph::ShowVex(){
	for(int i=0;i<m_nVexNum;i++){
		cout<<"景点编号:"<<m_aVexs[i].num<<"\t"<<"名称:"<<m_aVexs[i].name<<endl;
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
	cout<<"============查询节点信息===================\n\n";
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
			if(i==(*it).length-2){cout<<(*it).path[i];break;}
			cout<<(*it).path[i]<<"->";
		}
		cout<<endl;
		for(int i=0;i<(*it).length-1;i++){
			if(i==(*it).length-2){
				cout<<id_to_string[(*it).path[i]];
				break;
			}
			cout<<id_to_string[(*it).path[i]]<<"->";
		}
		cout<<"\n\n";
	}
}

void CGraph::Dijkstra(){
	int start;
	cout<<"\n请输入查询景点编号\n";
	cin>>start;
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

void CGraph::Floyd(){
	int start,end;
	cout<<"\n请输入起点景点编号\n";
	cin>>start;
	cout<<"\n请输入终点景点编号\n";
	cin>>end;
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

	cout<<"\n==========路径导航============\n\n";
	cout<<"起点:"<<id_to_string[start]<<"\t目标位置:"<<id_to_string[end]<<endl;
	//指定节点的路径
	int temp=path[start][end];
	cout<<"导航路径:"<<id_to_string[start]<<"->";
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
	cout<<"系统初始化中...........\n";
	g.Init();
	cout<<"初始化成功！\n";
	while (1)
	{
		Sleep(2000);
		int cmd;
		cout<<"\n请输入指令\n1.增加景区信息\n2.查询景点周边信息\n3.DFS查询所有路径\n4.查询与其他景区最短路径\n5.开启导航\n6.最后来铺个电线\n";
		cin>>cmd;
		switch(cmd){
			case 1:g.InsertVex();break;
			case 2:g.FindEdge();break;
			case 3:g.config();break;
			case 4:g.Dijkstra();break;
			case 5:g.Floyd();break;
			case 6:g.FindMinTree();break;
		}
	}
}
