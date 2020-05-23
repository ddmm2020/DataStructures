/*
 * @Descripttion: Graph application
 * @version: 
 * @Author: ddmm
 * @Date: 2020-05-19 15:09:09
 * @LastEditors: ddmm
 * @LastEditTime: 2020-05-23 21:55:09
 */ 

#include<bits/stdc++.h>

using namespace::std;

struct Vex{
    int num;//景点编号
    string name;//景点名称
    string desp;//景点描述

    Vex& operator=(Vex& tmp)
    {
        num=tmp.num;
        name=tmp.name;
        desp=tmp.desp;
        return *this;
    }
    Vex(int num,string name,string desp):num(num),name(name),desp(desp){};
    //Vex(uint8_t num,char name[20],char desp[1024]):num(num),name(name),desp(desp){};

    // Vex(int tnum,char tname[20],char tdesp[1024]){
    //     num =tnum;
    //     memcpy(name,tname,20);
    //     memcpy(desp,tdesp,1024);
    //     //printf("插入第%d个节点成功",num);
    // };
    Vex(){};
};

struct Path{
    int length;
    vector<int> path;
    int sum_w;
    Path(int length, const vector<int> &path) : length(length), path(path) {}
    bool operator<(const Path&rhs)const{
        if(length!=rhs.length) return length<rhs.length;
        for(int i=0;i<length;i++){
            if(path[i]!=rhs.path[i])
                return path[i]<rhs.path[i];
        }
    }
};

struct Edge{
    int vex1;
    int vex2;
    int weight;
    Edge& operator<<(Edge& temp)
    {
        vex1=temp.vex1;
        vex2=temp.vex2;
        weight=temp.weight;
        return *this;
    }
    Edge(int vex1,int vex2,int weight):vex1(vex1),vex2(vex2),weight(weight){};
    Edge(){};
};

// typedef struct Path{
//     uint8_t vexs[20];
//     Path*next;
// }*pathList;

class CGraph{
private:
    int m_aAdjMatrix[20][20];//邻接矩阵
    Vex m_aVexs[20];//顶点信息数组
    Edge m_aEdges[100];//边信息数组
    int m_aEdgeNum;//边的个数
    int m_nVexNum;//当前图的顶点个数
    unordered_map<int,string> id_to_string;
    vector<int> visited;
    vector<int> stack;
    vector<Path> paths;
    int path_num=0;
    int depth;
   

public:

    void Init();
    void loadVex();
    void loadPath();
    bool InsertVex();
    bool InsertEdge(Edge sEdge);
    Vex GetVex(int nVex);
    int GetVexnum();
    void ShowVex();
    // int FindEdge(int nVex);
    int FindEdge();
    void config();
    void DFS(vector<int> &visited,vector<int>&stack,int start_num,int end_num,int depth);
    void DFSTraverse();
    //int FindShortestPath();
    void Dijkstra();
    void Floyd();
    void FindMinTree();
};


