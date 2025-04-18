#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


int *abcCount(char s[],int n) {
    int cnt[128] = {0};
    int *pcnt = (int *)malloc(n * sizeof(int));  // 动态分配
    memset(pcnt,0,n*sizeof(int));
    //static int pcnt[26] = {0};
    int len = 0;

    // 统计字母出现次数（不区分大小写）
    for (int i = 0; s[i] != '\0'; i++) {
        if (isalpha(s[i])) {  // 检查是否为字母
            cnt[tolower(s[i])]++;  // 转换为小写并计数
            len++;
        }
    }

    // 计算权值
    for (int i = 'a', j = 0; i <= 'z'; i++, j++) {
        if(len==0) return pcnt;
        pcnt[j] = (cnt[i]*10000) / len;  // 乘以10000避免浮点数
    }

    return pcnt; 
}

typedef struct{
    int weight;
    int parent;
    int lchild;
    int rchild;
}HuffmanNode,*HuffmanTree;

HuffmanTree createHuffmanTree(int n)
{
    // 分配 n 个 HuffmanNode 的内存空间
    HuffmanTree tree = (HuffmanTree)malloc(n * sizeof(HuffmanNode));
    if (tree == NULL){
        return NULL; // 内存分配失败
    }

    // 初始化所有节点，-1为null
    for (int i = 0; i < n; i++){
        tree[i].weight = 0;
        tree[i].parent = -1;
        tree[i].lchild = -1;
        tree[i].rchild = -1;
    }

    return tree;
}

void select(HuffmanTree HT, int *s1, int *s2, int n) {
    *s1 = *s2 = -1;
    for (int i = 0; i < n; i++) {       //遍历所有treenode，n传入valid_node
        if (HT[i].parent == -1 && HT[i].weight > 0) {   //is root and valid node
            if (*s1 == -1 || HT[i].weight < HT[*s1].weight) { //s1 = null or the node < s1node
                *s2 = *s1;  //the secend min in sight
                *s1 = i;    //the min in sight
            } else if (*s2 == -1 || HT[i].weight < HT[*s2].weight) { //s1node is min and (s2 = null or the node < s2node)
                *s2 = i;
            }
        }
    }
}



void generateCodes(HuffmanTree HT, int n, char **codes) { //coding from down to top
    char *cd = (char *)malloc(n * sizeof(char));
    cd[n-1] = '\0';         //store coder
    
    for(int i = 0; i < n; i++) {
        int start = n-1;    //point the tail
        int c = i;          //point thr node
        int f = HT[i].parent; //point parent node
        
        while(f != -1) {                //the node != root
            if (HT[f].lchild == c) {    // the node ?= parent.lchild -> code 0
                cd[--start] = '0';
            } else {
                cd[--start] = '1';      //parent.rchild -> code 1
            }
            c = f;                      //update node node=node.parent
            f = HT[f].parent;           //update parent
        }
        //now start point the head of code
        codes[i] = (char *)malloc((n - start) * sizeof(char));
        strcpy(codes[i], &cd[start]);   //copy cd from cd[start] to cd[n-1]
    }
    
    free(cd);
}

char **HuffmanCode(int pcnt[],HuffmanTree HT,int n,int valid_nodes,int char_index[])
{
    //int *char_index = (int*)malloc(valid_nodes * sizeof(int)); // 存储字母表索引（a=0, b=1,...）
    for (int i = 0, j = 0; i < n; i++) {
        if (pcnt[i] > 0) {
            HT[j].weight = pcnt[i];     //将有效节点存入tree
            char_index[j] = i+'a';      // 记录第j个节点对应的字母表索引
            j++;
        }
    }

    int m = 2 * valid_nodes - 1;        //num of node in huffmanTree
    for (int i = valid_nodes; i < m; i++) {//creat huffmanTree
        int s1, s2;
        select(HT, &s1, &s2, i);
        if (s1 == -1 || s2 == -1) break;

        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
        HT[s1].parent = i;
        HT[s2].parent = i;
    }

    char **codes = (char**)malloc(valid_nodes * sizeof(char*));//二级指针存字符串
    generateCodes(HT,valid_nodes,codes);
    
    return codes;
}

int calculateWPL(HuffmanTree HT, int n, int *pcnt) {
    int wpl = 0;
    for (int i = 0; i < n; i++) {
        if (HT[i].lchild == -1 && HT[i].rchild == -1) {  // 叶子节点
            int depth = 0;
            int j = i;
            while (HT[j].parent != -1) {
                depth++;
                j = HT[j].parent;
            }
            wpl += depth * HT[i].weight;
        }
    }
    return wpl;
}

int main() {
    char s[] = "HUST EIC zhen shi hai can wo le";
    int n = 26;
    int valid_nodes = 0;

    int *pcnt = abcCount(s, n);
    for (int i = 0; i < n; i++) { //计算有效节点数
        if (pcnt[i] > 0) {
            valid_nodes++;
        }
    }
    HuffmanTree HT = createHuffmanTree(2 * valid_nodes - 1);
    
    

    // 打印权值表
    printf("Letter frequencies:\n");
    for (int i = 0; i < n; i++) {
        if (pcnt[i] > 0) {
            printf("%c: %d\n", 'a' + i, pcnt[i]);
        }
    }
    int *char_index = (int*)malloc(valid_nodes*sizeof(int));//store like char_index[0]='a'
    char **codes = HuffmanCode(pcnt, HT, n, valid_nodes, char_index);

    int WPL = calculateWPL(HT,valid_nodes,pcnt);

    //打印编码表
    if (codes != NULL) {
        printf("\nHuffman Codes:\n");
        for (int i = 0; i < valid_nodes; i++) {
                printf("%c: %s\n", char_index[i], codes[i]);
                free(codes[i]);
        }
        free(codes);
    }

    printf("\nWPL:%d",WPL);
    free(pcnt);
    free(HT);
    return 0;
}