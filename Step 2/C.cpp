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
    temp.x = max(left.x , right.x) ;
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

    int prob(int parent , int left , int right , int dd){
        if(left == right){
            if(Tree[parent].x>=dd){
                return left;
            }
            else{
               return 1e9 ;
            }
        }
        int mid = (left + right) / 2 ;
        if(Tree[parent * 2].x >= dd){
            return prob(parent*2 , left , mid , dd);
        }
        else{
            return prob(parent *2 + 1 , mid + 1 , right , dd);
        }
    }

public:

    SegmentTree (vector<ll> a , int x){
        this->a = a ;
        this->n = x ;
        Tree.assign(4 * n , retNode);
        build(1 , 0 , n - 1 );
    }

    void update(int index , int value){
        update(1 , 0 , n - 1 , index , value);
    }

    node query(int qLeft , int qRight){
        return query(1 , 0 , n- 1 , qLeft  , qRight);
    }

    int prob(int dd){
        return prob(1,0,n-1,dd);
    }

};
int n , q ;
signed main() {
    ios::sync_with_stdio(0); cin.tie(0);

    cin >> n >> q;
    vector<int> a(n) ;

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    SegmentTree segmentTree(a,n);
    while (q--)
    {
        int c ; cin >> c ;
        if(c == 1){
            int ind , val ;
            cin >> ind >> val ;
            segmentTree.update(ind,val);
        }
        else{
            int dd ;
            cin >> dd ;
            int ans = segmentTree.prob(dd) ;
            cout << (ans==1e9?-1:ans) << '\n';
        }
    }
    return 0;
}
