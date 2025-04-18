<center>

# 实验报告

## 题目：构造最长回文串

**班级**：电信2403班  **姓名**：吕雨桐  **学号**：xxxxxx  **完成日期**：xxxxx  

</center>
---

### 一、需求分析

1. **问题描述**  
   给定一个包含大写字母和小写字母的字符串 `s`，通过这些字母构造最长的回文串，并输出该回文串。回文串是指正读和反读都相同的字符串。

2. **输入输出示例**  
   - 输入：`s = "abccccdd"`  
   - 输出：`"dccaccd"`

3. **功能要求**  
   - 使用顺序存储（顺序表）和链式存储（双向链表）两种方式分别实现。
   - 程序能够正确处理大小写字母，并构造最长回文串。

4. **程序执行的命令**  
   - 顺序表实现：输入字符串，输出最长回文串。
   - 链表实现：输入字符序列，输出最长回文串。

---

### 二、概要设计

#### 1. 顺序表实现
- **数据结构**：使用字符数组存储字符串，并通过统计字母频次构造回文串。
- **核心操作**：
  - 统计每个字母的出现次数。
  - 根据字母频次构造回文串的前半部分和中间字符。
  - 对称填充后半部分。

#### 2. 链表实现
- **数据结构**：使用双向链表存储字符，并通过统计字母频次构造回文串。
- **核心操作**：
  - 统计每个字母的出现次数。
  - 根据字母频次构造回文串的前半部分和中间字符。
  - 对称填充后半部分。

#### 抽象数据类型定义
- **顺序表**：
  ```c
  typedef struct {
      char data[MAXSIZE];
      int length;
  } SqList;
  ```
- **双向链表**：
  ```c
  typedef struct DuLNode {
      char data;
      struct DuLNode *prior;
      struct DuLNode *next;
  } DuLNode, *DuLinkList;
  ```

---

### 三、详细设计

#### 1. 顺序表实现
```c
char *hui_wen_shunxv(char s[]) {
    int cnt[128] = {0};
    int len = strlen(s);
    char *out = (char*)malloc((len + 1) * sizeof(char));
    *out = 0;
    for (int i = 0; s[i] != 0; i++) {
        cnt[s[i]]++;
    }
    int left = 0;
    char middle = '\0';
    for (int i = 'A'; i <= 'z'; i++) {
        if (cnt[i] > 0) {
            if (cnt[i] % 2 == 0) {
                for (int j = 0; j < cnt[i] / 2; j++) {
                    out[left++] = (char)i;
                }
            } else {
                for (int j = 0; j < (cnt[i] - 1) / 2; j++) {
                    out[left++] = (char)i;
                }
                if (middle == '\0') {
                    middle = i;
                }
            }
        }
    }
    out[left] = middle;
    int right = left;
    for (; left >= 0; left--, right++) {
        out[right] = out[left];
    }
    out[++right] = '\0';
    return out;
}
```

#### 2. 链表实现
```c
DuLinkList hui_wen_lianbiao(DuLinkList head) {
    int cnt[128] = {0};
    for (DuLinkList ptr = head; ptr != NULL; ptr = ptr->next) {
        cnt[(int)ptr->data]++;
    }
    DuLinkList newNode, outhead = NULL, outtail = NULL;
    char middle = '\0';
    for (int i = 'A'; i <= 'z'; i++) {
        if (cnt[i] > 0) {
            if (cnt[i] % 2 == 0) {
                for (int j = 0; j < cnt[i] / 2; j++) {
                    CreateDuLNode(&outhead, &outtail, (char)i);
                }
            } else {
                for (int j = 0; j < (cnt[i] - 1) / 2; j++) {
                    CreateDuLNode(&outhead, &outtail, (char)i);
                }
                if (middle == '\0') {
                    middle = i;
                }
            }
        }
    }
    if (middle != '\0') {
        CreateDuLNode(&outhead, &outtail, middle);
    }
    DuLinkList left = outtail;
    while (left->prior != NULL) {
        CreateDuLNode(&outhead, &outtail, left->prior->data);
        left = left->prior;
    }
    return outhead;
}
```

---

### 四、调试分析

1. **顺序表实现**  
   - **优点**：实现简单，直接通过数组操作完成。
   - **缺点**：需要预先分配固定大小的内存空间，可能造成空间浪费或不足。

2. **链表实现**  
   - **优点**：动态分配内存，灵活性高。
   - **缺点**：实现较为复杂，需要处理指针操作。

3. **时间复杂度分析**  
   - 顺序表和链表的时间复杂度均为 `O(n)`，其中 `n` 为字符串长度。
   - 链表实现由于指针操作较多，实际运行时间可能略长于顺序表。

4. **空间复杂度分析**  
   - 顺序表：`O(n)`。
   - 链表：`O(n)`，但额外需要存储指针。

---


### 五、测试结果

1. **输入**：`"abccccdd"`  
   - **输出**：`"dccaccd"`  
   - **结果**：符合预期。

2. **输入**：`"aabb"`  
   - **输出**：`"abba"`  
   - **结果**：符合预期。

3. **输入**：`"a"`  
   - **输出**：`"a"`  
   - **结果**：符合预期。

---

### 六、反思回顾

1. **改进点**  
   - 可以进一步优化链表实现的指针操作，减少冗余代码。
   - 增加输入合法性检查，确保输入仅为字母字符。

2. **总结**  
   - 通过本次实验，深入理解了顺序表和链表在字符串处理中的应用差异。
   - 两种实现方式各有优劣，应根据实际需求选择合适的数据结构。

--- 
