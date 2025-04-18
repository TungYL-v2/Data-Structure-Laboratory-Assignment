# 实验报告

## 题目：Huffman编码实现

**班级**：xxxxx  
**姓名**：xxxx  
**学号**：xxxxx  
**完成日期**：xxxxx  

---

### 一、需求分析

1. **问题描述**  
   根据给定英文文本，统计26个英文字母的出现频率，以此作为权值构建Huffman树，并为每个字母生成Huffman编码。同时计算树的带权路径长度（WPL）。

2. **输入输出**  
   - 输入：英文文本（来自指定链接或直接输入的字符串）。
   - 输出：
     - 每个字母的频率（权值）。
     - 每个字母的Huffman编码。
     - 树的带权路径长度（WPL）。

3. **功能要求**  
   - 统计字母频率。
   - 构建Huffman树。
   - 生成Huffman编码。
   - 计算WPL。

---

### 二、概要设计

#### 1. 数据结构
- **Huffman树节点**：
  ```c
  typedef struct {
      int weight;     // 权值（字母频率）
      int parent;     // 父节点索引
      int lchild;     // 左孩子索引
      int rchild;     // 右孩子索引
  } HuffmanNode, *HuffmanTree;
  ```

#### 2. 核心模块
1. **字母频率统计**：
   - 遍历文本，统计每个字母的出现次数。
   - 计算频率（权值）。

2. **Huffman树构建**：
   - 初始化所有节点。
   - 选择权值最小的两个节点合并，生成新节点，直到形成完整的树。

3. **Huffman编码生成**：
   - 从叶子节点回溯到根节点，生成每个字母的编码。

4. **WPL计算**：
   - 遍历所有叶子节点，计算路径长度与权值的乘积之和。

---

### 三、详细设计

#### 1. 字母频率统计
```c
int *abcCount(char s[], int n) {
    int cnt[128] = {0};
    int *pcnt = (int *)malloc(n * sizeof(int));
    memset(pcnt, 0, n * sizeof(int));
    int len = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if (isalpha(s[i])) {
            cnt[tolower(s[i])]++;
            len++;
        }
    }

    for (int i = 'a', j = 0; i <= 'z'; i++, j++) {
        if (len == 0) return pcnt;
        pcnt[j] = (cnt[i] * 10000) / len;  // 避免浮点数
    }

    return pcnt;
}
```

#### 2. Huffman树构建
```c
void select(HuffmanTree HT, int *s1, int *s2, int n) {
    *s1 = *s2 = -1;
    for (int i = 0; i < n; i++) {
        if (HT[i].parent == -1 && HT[i].weight > 0) {
            if (*s1 == -1 || HT[i].weight < HT[*s1].weight) {
                *s2 = *s1;
                *s1 = i;
            } else if (*s2 == -1 || HT[i].weight < HT[*s2].weight) {
                *s2 = i;
            }
        }
    }
}

HuffmanTree createHuffmanTree(int n) {
    HuffmanTree tree = (HuffmanTree)malloc(n * sizeof(HuffmanNode));
    if (tree == NULL) return NULL;

    for (int i = 0; i < n; i++) {
        tree[i].weight = 0;
        tree[i].parent = -1;
        tree[i].lchild = -1;
        tree[i].rchild = -1;
    }

    return tree;
}
```

#### 3. Huffman编码生成
```c
void generateCodes(HuffmanTree HT, int n, char **codes) {
    char *cd = (char *)malloc(n * sizeof(char));
    cd[n-1] = '\0';

    for (int i = 0; i < n; i++) {
        int start = n-1;
        int c = i;
        int f = HT[i].parent;

        while (f != -1) {
            if (HT[f].lchild == c) {
                cd[--start] = '0';
            } else {
                cd[--start] = '1';
            }
            c = f;
            f = HT[f].parent;
        }

        codes[i] = (char *)malloc((n - start) * sizeof(char));
        strcpy(codes[i], &cd[start]);
    }

    free(cd);
}
```

#### 4. WPL计算
```c
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
```

---

### 四、调试分析

1. **问题与解决**  
   - **问题1**：字母频率统计时未区分大小写。  
     **解决**：使用`tolower`函数统一转换为小写字母。  
   - **问题2**：Huffman树构建时未正确处理无效节点。  
     **解决**：在`select`函数中添加对无效节点的过滤。  

2. **时间复杂度分析**  
   - 字母频率统计：`O(n)`，其中`n`为文本长度。  
   - Huffman树构建：`O(m log m)`，其中`m`为字母种类数（26）。  
   - Huffman编码生成：`O(m)`。  
   - WPL计算：`O(m)`。  

3. **空间复杂度分析**  
   - 主要消耗在存储Huffman树和编码表，均为`O(m)`。

---

### 五、用户使用说明

1. **输入**  
   - 直接修改代码中的字符串`s`，或从文件读取文本。

2. **输出**  
   - 字母频率表。
   - Huffman编码表。
   - WPL值。

3. **示例**  
   ```c
   char s[] = "HUST EIC zhen shi hai can wo le";
   int n = 26;
   int *pcnt = abcCount(s, n);
   ```

---

### 六、测试结果

1. **输入**：`"HUST EIC zhen shi hai can wo le"`  
   - **输出**：
     ```
     Letter frequencies:
     a: 833
     c: 833
     e: 1250
     h: 1666
     i: 1250
     l: 416
     n: 833
     o: 416
     s: 833
     t: 416
     u: 416
     w: 416
     z: 416

     Huffman Codes:
     a: 1101
     c: 000
     e: 011
     h: 111
     i: 100
     l: 10100
     n: 001
     o: 10101
     s: 010
     t: 10110
     u: 10111
     w: 11000
     z: 11001

     WPL:35807
     ```
   - **结果**：符合预期。

---

### 七、反思回顾

1. **改进点**  
   - 支持从文件读取文本，提高灵活性。
   - 优化WPL计算，避免重复遍历。

2. **总结**  
   - 通过实现Huffman编码，深入理解了贪心算法在数据压缩中的应用。
   - 掌握了动态内存管理和树结构操作的技巧。

---

**附录**：完整代码见实验内容。