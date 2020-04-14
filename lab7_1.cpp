#include <iostream>
#include "algorithm"
#include "queue"
using namespace std;

struct node{
    int cnt;
    node *set;
    int val;
    int rank;
};

struct edge{
    node *node1;
    node *node2;
    int weight;

    friend bool operator >(const struct edge &edge1, const struct edge &edge2);
};
inline bool operator > (const struct edge &edge1, const struct edge &edge2){
    return edge1.weight > edge2.weight;
}


node table[1000][1000];

edge edge_queue[2000000];

priority_queue<edge,vector<edge>,greater<edge>> pq;
node * find( node *temp){
    node *cur=temp;
    while(cur->set!=cur){
        cur=cur->set;
    }
    temp->set=cur;
    return cur;
}

int merge(node *node1,node *node2){
    int cnt=0;
    node *father_node1=find(node1);
    node *father_node2=find(node2);

    if(father_node1->rank>father_node2->rank){
        father_node2->set=father_node1;
        father_node1->cnt+=father_node2->cnt;
        cnt=father_node1->cnt;
    }
    else{
        father_node1->set=father_node2;
        father_node2->cnt+=father_node1->cnt;
        cnt=father_node2->cnt;
    }
    if(father_node1->rank==father_node2->rank && father_node1!=father_node2){
        father_node2->rank++;
    }
    return cnt;
}

long long kruskal(int size,int num){

    long long cnt=0;
    while(!pq.empty()) {
        edge edge_curr = pq.top();
        pq.pop();
        node *node1 = edge_curr.node1;
        node *node2 = edge_curr.node2;
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
    cin >> n;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> temp;
            node &cur_node=table[i][j];
            cur_node.set=&cur_node;
            cur_node.cnt=1;
            cur_node.val=temp;
            cur_node.rank=1;
            if(i>0){//current node and the node in its head
                edge &cur_edge=edge_queue[size++];
                cur_edge.node1=&table[i-1][j];
                cur_edge.node2=&table[i][j];
                cur_edge.weight=table[i-1][j].val^table[i][j].val;
                pq.push(cur_edge);
            }

            if(j>0){//current node and the node in its left
                edge &cur_edge=edge_queue[size++];
                cur_edge.node1=&table[i][j-1];
                cur_edge.node2=&table[i][j];
                cur_edge.weight=table[i][j-1].val^table[i][j].val;
                pq.push(cur_edge);
            }

        }
    }
    long long ans=kruskal(size,m*n);
    cout << ans <<endl;

    return 0;
}
