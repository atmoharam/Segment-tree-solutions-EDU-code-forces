#include <iostream>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
const ll template_array_size = 1e6 + 4265;
const ll Mod = 1e9 + 7;

struct node{
    ll x ;
};

node retNode = {0};


node merge (node left , node right){
    node temp ;
    temp.x = left.x + right.x ;
    return temp;
}

class SegmentTree{

private:
    int n ;
    vector<node> Tree ;
    vector<ll> a ;

    void build(int parent , int left , int right){

        if(left == right){
            Tree[parent].x = a[left];
            return;
        }
        int mid = (left + right) / 2 ;
        build(parent * 2 , left , mid);
        build(parent * 2 + 1 , mid +1 , right);
        Tree[parent] = merge(Tree[parent*2] , Tree[parent*2 + 1]);
    }

    void update(int parent , int left , int right , int index , int value){

        if(left == right){
            Tree[parent].x = value ;
            a[left] = value;
            return;
        }

        int mid = (left + right) / 2 ;

        if(index <= mid)
        {
            update(parent * 2 , left , mid , index , value);
        }
        else{
            update(parent * 2 + 1 , mid + 1 , right , index , value);
        }
        Tree[parent] = merge(Tree[parent*2] , Tree[parent*2 + 1]);
    }

    node query (int parent , int left , int right , int qLeft , int qRight){

        if(qRight < left || qLeft > right){
            return retNode ;
        }
        if(left >= qLeft && qRight >= right){
            return Tree[parent];
        }
        int mid = (left + right) / 2 ;

        node lefNode = query(parent * 2 , left , mid , qLeft , qRight);
        node rightNode = query(parent * 2 + 1 , mid + 1 , right , qLeft , qRight);

        return merge(lefNode , rightNode);
    }

    int findTh(int parent , int left , int right , int k){

        if(left == right){
            return left;
        }
        int mid = (left + right) / 2 ;
        if(Tree[parent * 2 ].x >= k){
            return findTh(parent * 2 , left , mid , k);
        }
        else{
            return findTh(parent * 2 + 1 , mid +1 , right , k - Tree[parent * 2].x);
        }
    }

public:

    SegmentTree (vector<ll> a , int x){
        this->a = a ;
        this->n = x ;
        Tree.assign(4 * n * 2 , retNode);
        build(1 , 0 , n - 1 );
    }

    void update(int index , int value){
        update(1 , 0 , n - 1 , index , value);
    }

    node query(int qLeft , int qRight){
        return query(1 , 0 , n- 1 , qLeft  , qRight);
    }

    int findTh(int k){
        return findTh(1 , 0 , n - 1 , k);
    }

};

int n , q , x , t , c ;
signed main() {
    ios::sync_with_stdio(0); cin.tie(0);

    cin >> n >> q;
    vector<ll> a(n , 0);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    SegmentTree segmentTree(a, n );

    while (q--) {
        cin >> c >> x;
        if(c == 1){
            segmentTree.update(x , 1 - a[x]);
            a[x] = 1 - a[x];
        }
        else{
            cout << segmentTree.findTh(x + 1  )  << '\n';
        }
    }
    return 0;
}
