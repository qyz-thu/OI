////
//// Created by leo_qian on 2021/10/11.
////
#include <vector>
#include <iostream>
using namespace std;
struct Node
{
    int val;
    int num_child;
    int left, right;
    Node(): val(0), num_child(0), left(-1), right(-1) {}
};
Node tree[1001];
int head = 1;
long long memory[100][50];
long long prime = 1000000007;
void insert(int);
long long get_num(Node*);
long long factorial[1024], factorial_inv[1024], inv[1024];

int main()
{
    vector<int> nums = {30,11,46,3,29,22,37,32,13,49,48,16,40,8,24,44,9,39,25,21,41,26,43,19,47,7,10,31,45,4,35,14,20,23,15,17,38,2,6,18,5,33,27,36,42,28,12,34,1};
        factorial[0] = factorial[1] = 1;
        factorial_inv[0] = factorial_inv[1] = 1;
        inv[0] = inv[1] = 1;
        for(int i=2; i < 1024; i++){
            factorial[i] = (factorial[i-1]*i) % prime;
            inv[i] = prime - (prime / i * inv[prime%i]) % prime;
            factorial_inv[i] = (factorial_inv[i-1]*inv[i]) % prime;
        }

    for (auto i: nums)
        insert(i);

    cout << (int) get_num(tree) - 1;

    return 0;
}


void insert(int k)
{
    Node* p = tree;
    while (p->val != 0)
    {
        p->num_child++;
        if (k < p->val)
        {
            if (p->left == -1)
                p->left = head++;
            p = tree + p->left;
        }
        else
        {
//            assert(k < p->val);
            if (p->right == -1)
                p->right = head++;
            p = tree + p->right;
        }
    }
    p->val = k;
}

long long C(int x, int y)
{
    int ans = factorial[x + y];
    ans = (ans * factorial_inv[x]) % prime;
    ans = (ans * factorial_inv[y]) % prime;
    return ans;
}

long long get_num(Node* p)  // returns the number of insertion for the sub-tree with p as root
{
    if (p->num_child == 0 || p->num_child == 1)
        return 1;
    else if (p->num_child == 2)
    {
        if (p->left != -1 && p->right != -1)    // have both children
            return 2;
        return 1;
    }
    if (p->left == -1)
        return get_num(tree + p->right) % prime;
    if (p->right == -1)
        return get_num(tree + p->left) % prime;
    long long left_num = get_num(tree + p->left) % prime;
    long long right_num = get_num(tree + p->right) % prime;
    int left_child = tree[p->left].num_child + 1;
    int right_child = tree[p->right].num_child + 1;
    long long sum = C(left_child, right_child) % prime;
    sum = (sum * left_num) % prime;
    sum = (sum * right_num) % prime;

    return sum;
}

//#include "stdlib.h"
//#include <vector>
//#include <iostream>
//using namespace std;
//
//#define MOD 1000000007
//#define MAXN 1024
//typedef struct Node{
//    int val;
//    int left_count,right_count;
//    struct Node *left, *right;
//}Node;
//void insert(Node *root, int val){
//    if(root->val > val){
//        if(root->left == NULL){
//            Node *newnode = (Node *)malloc(sizeof(Node));
//            newnode->val = val;
//            newnode->left = NULL;
//            newnode->right = NULL;
//            newnode->left_count = 0;
//            newnode->right_count = 0;
//            root->left = newnode;
//            root->left_count++;
//            return;
//        }else{
//            root->left_count++;
//            insert(root->left, val);
//        }
//    }else if(root->val < val){
//        if(root->right == NULL){
//            Node *newnode = (Node *)malloc(sizeof(Node));
//            newnode->val = val;
//            newnode->left = NULL;
//            newnode->right = NULL;
//            newnode->left_count = 0;
//            newnode->right_count = 0;
//            root->right = newnode;
//            root->right_count++;
//            return;
//        }else{
//            root->right_count++;
//            insert(root->right, val);
//        }
//    }
//}
//void freeNode(Node *root){
//    if(root->left)freeNode(root->left);
//    if(root->right)freeNode(root->right);
//    free(root);
//}
//long long factorial[MAXN], factorial_inv[MAXN], inv[MAXN];
//
//long long Ways(Node *root){
//    if(!root)return 1;
//    if(!root->left && !root->right)return 1;
//    if(!root->left)return Ways(root->right)%MOD;
//    if(!root->right)return Ways(root->left)%MOD;
//    long long temp = factorial[root->left_count+root->right_count];
//    temp = (temp*factorial_inv[root->left_count])%MOD;
//    temp = (temp*factorial_inv[root->right_count])%MOD; // C(l+r, l)
//    return ((temp*Ways(root->left)%MOD)*Ways(root->right))%MOD;
//}
//int main(){
//    vector<int> nums = {30,11,46,3,29,22,37,32,13,49,48,16,40,8,24,44,9,39,25,21,41,26,43,19,47,7,10,31,45,4,35,14,20,23,15,17,38,2,6,18,5,33,27,36,42,28,12,34,1};
//    factorial[0] = factorial[1] = 1;
//    factorial_inv[0] = factorial_inv[1] = 1;
//    inv[0] = inv[1] = 1;
//    for(int i=2;i<MAXN;i++){
//        factorial[i] = (factorial[i-1]*i)%MOD;
//        inv[i] = MOD - (MOD/i*inv[MOD%i])%MOD; // (i%MOD)^-1
//        factorial_inv[i] = (factorial_inv[i-1]*inv[i])%MOD;//((i!)%MOD)^-1
//    }
//    Node *root = (Node *)malloc(sizeof(Node));
//    root->val = nums[0];
//    root->left = NULL;
//    root->right = NULL;
//    root->left_count = 0;
//    root->right_count = 0;
//    for(int i=1;i<nums.size();i++){
//        insert(root, nums[i]);
//    }
//    int ret = (int)Ways(root)-1;
//    cout << Ways(root->left) << endl;
//    cout << Ways(root->right) << endl;
//    cout << ret << endl;
//    freeNode(root);
//    return 0;
//}