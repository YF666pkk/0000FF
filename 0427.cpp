#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<list>
#include<string>
#include<map>
#include<iostream>
using namespace std;
struct ar {
	int a, b, c;
}p[10000];     //结构体 
struct data {
	int l, r, v, n;
}d[10000];     //结构体 
int f[10000];
ar cons[10000][10000];
map<string, int> m;
string m0[10000];
int arc, vec, num, sum, ans = 1, numb, rmb,tol;
int find(int v) {
	return f[v] == v ? v : find(f[v]);
}           //函数 
void join(int a, int b) {
	int t1 = find(a), t2 = find(b);
	if (t1 != t2)
		f[t2] = t1;
}            //函数 
bool cmp(ar a, ar b) {
	return a.c < b.c;
}    
void krus() {
	for (int i = 0; i < 1000; i++)
		f[i] = i;
	for (int i = 0; i < arc; i++) {
		if (p[i].c == p[i - 1].c) {
			d[num].r++;
		}
		else {
			d[++num].l = i;
			d[num].r = i;
			d[num].v = 0;
		}
		if (find(p[i].a) != find(p[i].b)) {
			join(p[i].a, p[i].b);
			d[num].v++;
			rmb += p[i].c;
			tol++;
		}
	}
}
list<ar> li;
void dfs(int x, int n, int k) {
	if (n == d[x].r + 1) {
		if (k == d[x].v) {
			sum++;
		}
		return;
	}
	int t1 = find(p[n].a), t2 = find(p[n].b);
	if (t1 != t2) {
		f[t1] = t2;
		dfs(x, n + 1, k + 1);
		f[t1] = t1;
		f[t2] = t2;
	}
	dfs(x, n + 1, k);
}                                        //DFS深度优先算法 
void dfs1(int x, int n, int k) {
	if (n == d[x].r + 1) {
		if (k == d[x].v) {
			numb++;
			int h = d[x].l;
			for (list<ar>::iterator it = li.begin(); it != li.end(); it++) {
				cons[numb][h++] = *it;
			}
		}
		return;
	}
	int t1 = find(p[n].a), t2 = find(p[n].b);
	if (t1 != t2) {
		f[t1] = t2;
		li.push_back(p[n]);
		dfs1(x, n + 1, k + 1);
		li.pop_back();
		f[t1] = t1;
		f[t2] = t2;
	}
	dfs1(x, n + 1, k);
}
int fscan(FILE* fp) {
	fscanf(fp, "%d%d", &vec, &arc);
	for (int i = 1; i <= vec; i++) {
		string s;
		s.resize(100);
		fscanf(fp, "%s", s.c_str());
		m[s] = i;
		m0[i] = s;
	}
	for (int i = 0; i < arc; i++) {
		string s1, s2;
		s1.resize(100);
		s2.resize(100);
		fscanf(fp, "%s%s%d", s1.c_str(), s2.c_str(), &p[i].c);
		p[i].a = m[s1], p[i].b = m[s2];
		if (p[i].c <= 0) {
			printf("警告输入有误(请重启系统)\n");
			return 1;
		}
	}
	return 0;
}                                   //引入fscan函数从文件中读取数据 
int scan() {
	cout << "请输入小区数量和管道总数：" << endl;
	scanf("%d%d", &vec, &arc);
	cout << "请输入小区名称（供暖公司也称为小区）: " << endl;
	for (int i = 1; i <= vec; i++) {
		string s;
		s.resize(100);
		scanf("%s", &s[0]);
		m[s] = i;
		m0[i] = s;
	}
	cout << "请输入管道所连通的小区名称，管道费用: " << endl;
	for (int i = 0; i < arc; i++) {
		string s1, s2;
		s1.resize(100);
		s2.resize(100);
		scanf("%s%s%d", &s1[0], &s2[0], &p[i].c);
		p[i].a = m[s1], p[i].b = m[s2];
		if(p[i].a<=0||p[i].b<=0||p[i].c <= 0){
			printf("警告输入有误(请重启系统)\n");
			return 1;
		}
	}
	return 0;
}
int main() {
	cout << "**********************************************" << endl;
	cout << "*           欢迎来到煤气管道铺设方案系统     *" << endl;
	cout << "*           输入1 进入手动输入方式           *" << endl;
	cout << "*           输入2 进入文件输入方式           *" << endl;
	cout << "*           输入0 退出系统                   *" << endl;
	cout << "**********************************************" << endl;
	int mode;
	while (1) {
		fflush(stdin);
		FILE* fp = fopen("syf.txt", "r");
		cin >> mode;
		num = 0, sum = 0, ans = 1, numb = 0, rmb = 0,tol=0;
		memset(cons, 0, sizeof(ar) * 10000 * 10000);
		if(fp==NULL)
		{
			printf("can not open the file!\n");
			exit(1);
		}
		if (mode == 1) {
			if (scan())
				return 0;
		}
		else if (mode == 2) {
			if (fscan(fp))
				return 0;
		}
		else {
			cout << "再见";
			return 0;
		}

		sort(p, p + arc, cmp);
		krus();
		if(tol<vec-1){
			cout << "存在不连通的小区（请重启系统）";
			return 0;
	
		}
		for (int i = 0; i < 1000; i++)
			f[i] = i;
		for (int i = 1; i <= num; i++) {
			sum = 0;
			dfs(i, d[i].l, 0);
			d[i].n = sum;
			ans *= sum;
		}
		for (int i = 1; i <= num; i++) {
			int t = ans / d[i].n;
			numb = 0;
			while (t--)
				dfs1(i, d[i].l, 0);
		}
		cout << "************************"<<endl;
		cout << "总费用:" << rmb << endl;
		for (int i = 1; i <= ans; i++) {
			cout << "铺设方式" << i << endl;
			for (int j = 0; j < arc; j++) {
				if (cons[i][j].a) {
					printf("%s %s %d\n", m0[cons[i][j].a].c_str(), m0[cons[i][j].b].c_str(), cons[i][j].c);
				}
			}
		}
		cout << "                       "<<endl;
		cout << "温馨提示：退出请输入0; "<<endl;
		cout << "          再次运行:输入1 进入手动输入方式"<<endl;
		cout << "                   输入2 进入文件输入方式"<<endl;
		fclose(fp);
	}
	return 0;
}
