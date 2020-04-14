#include <iostream>
#include "queue"
using namespace std;
struct edge{
    int node1;
    int node2;
    int weight;

    friend bool operator >(const struct edge &edge1, const struct edge &edge2);
};
inline bool operator > (const struct edge &edge1, const struct edge &edge2){
    return edge1.weight > edge2.weight;
}

//node table[2000];
int rank_arr[2001];
int father[2001];
int cnt_arr[2001];
edge edge_queue[2000008];

priority_queue<edge,vector<edge>,greater<edge>> pq;
int find( int temp){
    int cur=temp;
    while(father[cur]!=cur){
        cur=father[cur];
    }
    father[temp]=cur;
    return cur;
}

int merge(int node1,int node2){
    int cnt=0;
    int father_node1=find(node1);
    int father_node2=find(node2);

    if(rank_arr[father_node1]>rank_arr[father_node2]){
        father[father_node2]=father_node1;
        cnt_arr[father_node1]+=cnt_arr[father_node2];
        cnt=cnt_arr[father_node1];
    }
    else{
        father[father_node1]=father_node2;
        cnt_arr[father_node2]+=cnt_arr[father_node1];
        cnt=cnt_arr[father_node2];
    }
    if(rank_arr[father_node1]==rank_arr[father_node2] && father_node1!=father_node2){
        rank_arr[father_node2]++;
    }
    return cnt;
}

long long kruskal(int size,int num){

    long long cnt=0;
    while(!pq.empty()) {
        edge edge_curr = pq.top();
        pq.pop();
        int node1 = edge_curr.node1;
        int node2 = edge_curr.node2;
        if (find(node1) != find(node2)) {//不在一个集合
            cnt += edge_curr.weight;
            int node_cnt = merge(node1, node2);
            if (node_cnt == num)break;
        }

    }
    return cnt;

}

int main() {
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    int m,n,temp;
    int size=0;
    cin >> m;

    for (int i = 1; i <=m; ++i) {
        rank_arr[i]=1;
        father[i]=i;
        cnt_arr[i]=1;
        for (int j = i; j <= m; ++j) {
            cin >> temp;
            edge &edge_cur=edge_queue[size++];
            edge_cur.weight=temp;
            edge_cur.node1=i-1;
            edge_cur.node2=j;
            pq.push(edge_cur);
        }
    }
    long long ans=kruskal(size,m);
    cout << ans <<endl;
    return 0;
}