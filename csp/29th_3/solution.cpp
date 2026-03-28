#include <bits/stdc++.h>
using namespace std;
#define int  long long
#define N 500100
#define M 5010
const int inf = 1e18, mod = 998244353;
#define ec " "
int n, m;
const int MAXN = 2505;
const int MAX_LEN = 2505;

// 用户结构体
struct User {
    int dn;
    vector<pair<int, int>> attrs;
    bool operator<(const User& other) const {
        return dn < other.dn;
    }
};

// 语法树节点
struct Node {
    char type;
    int ls, rs;
    int attr, val;
} tr[MAX_LEN];

int n, m;
int tot = 0;
vector<User> users;

// 倒排索引
unordered_map<int, bitset<MAXN>> has_attr;
unordered_map<long long, bitset<MAXN>> has_attr_val;

// 将属性和值打包成一个 long long 作为 key
long long make_key(int attr, int val) {
    return ((long long)attr << 32) | val;
}

// O(L) 零拷贝建树
int build(const string& s, int& pos) {
    int u = ++tot;
    if (s[pos] == '&' || s[pos] == '|') {
        tr[u].type = s[pos];
        pos += 2; // 跳过 '&' 和 '('
        tr[u].ls = build(s, pos);
        pos += 2; // 跳过 ')' 和 '('
        tr[u].rs = build(s, pos);
        pos += 1; // 跳过 ')'
    }
    else {
        int attr = 0;
        while (pos < s.length() && isdigit(s[pos])) {
            attr = attr * 10 + (s[pos] - '0');
            pos++;
        }

        tr[u].type = s[pos]; // ':' 或 '~'
        pos++;

        int val = 0;
        while (pos < s.length() && isdigit(s[pos])) {
            val = val * 10 + (s[pos] - '0');
            pos++;
        }

        tr[u].attr = attr;
        tr[u].val = val;
    }
    return u;
}

// 返回符合该子树条件的 bitset
bitset<MAXN> dfs(int u) {
    if (tr[u].type == '&') {
        return dfs(tr[u].ls) & dfs(tr[u].rs);
    }
    else if (tr[u].type == '|') {
        return dfs(tr[u].ls) | dfs(tr[u].rs);
    }
    else {
        long long key = make_key(tr[u].attr, tr[u].val);
        if (tr[u].type == ':') {
            // 返回包含该属性且值相等的集合
            if (has_attr_val.count(key)) return has_attr_val[key];
            return bitset<MAXN>(); // 空集
        }
        else {
            // 返回包含该属性，且值不相等的集合
            bitset<MAXN> res;
            if (has_attr.count(tr[u].attr)) {
                res = has_attr[tr[u].attr];
                if (has_attr_val.count(key)) {
                    // 从有该属性的人中，剔除掉等于该值的人 (按位异或 / 差集)
                    res ^= has_attr_val[key];
                }
            }
            return res;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n;
    users.resize(n);
    for (int i = 0; i < n; i++) {
        int t;
        cin >> users[i].dn >> t;
        for (int j = 0; j < t; j++) {
            int u, v;
            cin >> u >> v;
            users[i].attrs.push_back({ u, v });
        }
    }

    // 1. 按 DN 排序，此时数组下标 0~(n-1) 就是用户的内部 ID
    sort(users.begin(), users.end());

    // 2. 构建倒排索引 (核心算法改变)
    for (int i = 0; i < n; i++) {
        for (auto& p : users[i].attrs) {
            int attr = p.first;
            int val = p.second;
            has_attr[attr].set(i); // 用户 i 拥有 attr 属性
            has_attr_val[make_key(attr, val)].set(i); // 用户 i 拥有 attr 且值为 val
        }
    }

    cin >> m;
    string s;
    for (int i = 0; i < m; i++) {
        cin >> s;
        tot = 0;
        int pos = 0;
        int root = build(s, pos);

        // 3. 树形 DP 求出全量满足条件的 bitset
        bitset<MAXN> res = dfs(root);

        // 4. 解析 bitset 输出结果
        bool first = true;
        for (int j = 0; j < n; j++) {
            if (res.test(j)) { // 第 j 位为 1 说明内部 ID 为 j 的用户满足条件
                if (!first) cout << " ";
                cout << users[j].dn;
                first = false;
            }
        }
        cout << "\n";
    }

    return 0;
}