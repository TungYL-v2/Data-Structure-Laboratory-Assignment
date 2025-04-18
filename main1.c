#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXSIZE 20

typedef struct DuLNode 
{
    char data;
    struct DuLNode *prior;
    struct DuLNode *next;
}DuLNode, *DuLinkList;

char *hui_wen_shunxv(char s[]);
DuLinkList hui_wen_lianbiao(DuLinkList head);
void CreateDuLNode(DuLinkList *head,DuLinkList *tail,char inputChar);
void FreeDuLinkList(DuLinkList head);

int main(){
    /*顺序表*/
    // char s[] ="abccccdd";
    // char *out = hui_wen_shunxv(s);
    // printf("%s",out);
    // free(out);

    /*链表*/
    DuLinkList head=NULL,tail=NULL,newNode;
    char inputChar;
    while(scanf("%c",&inputChar)==1 && inputChar!='\n')
    {
        CreateDuLNode(&head,&tail,inputChar);
        //printf("%c",tail->data);
    }
    DuLinkList outhead=hui_wen_lianbiao(head);
    for(DuLinkList ptr=outhead;ptr!=NULL;ptr=ptr->next)
    {
        printf("%c",ptr->data);
    }
    FreeDuLinkList(head);
    FreeDuLinkList(outhead);
}

char *hui_wen_shunxv(char s[])
{
    int cnt[128]={0};
    int len=strlen(s);
    char *out = (char*)malloc((len+1)*sizeof(char));
    *out=0;
    for(int i=0; s[i]!=0; i++)//计算各字母数量
    {
        cnt[s[i]]++;
    }
    int left=0;//输出回文串指针
    char middle='\0';//检测中间值是否占用
    for(int i='A'; i<'z'; i++)
    {
        if(cnt[i]>0)
        {
            if(cnt[i]%2 == 0)//偶数个
            {
                for(int j=0; j<(cnt[i]/2); j++)
                {
                    out[left++]=(char)i;
                }
            }
            else
            {
                for(int j=0; j<(cnt[i]-1)/2;j++)
                {
                    out[left++]=(char)i;
                }
                if(middle == '\0')
                {
                    middle=i;
                    //out[left++]=(char)middle;
                }
            }
        }
    }
    out[left]=(char)middle;
    int right=left;
    for(; left>=0; left--,right++)
        out[right]=out[left];
    out[++right]='\0';
    return out;
}
// 释放链表内存
void FreeDuLinkList(DuLinkList head) {
    DuLinkList ptr = head;
    while (ptr != NULL) {
        DuLinkList temp = ptr;
        ptr = ptr->next;
        free(temp);
    }
}
void CreateDuLNode(DuLinkList *head,DuLinkList *tail,char inputChar)
{
    DuLinkList newNode = (DuLinkList)malloc(sizeof(DuLNode));
        newNode->data = inputChar;
        newNode->next = NULL;
        if(*tail!=NULL)
        {
            newNode->prior = *tail;
            (*tail)->next = newNode;
        }
        else 
        {
            *head = newNode;
            newNode->prior=NULL;
        }
        *tail = newNode;
}

DuLinkList hui_wen_lianbiao(DuLinkList head)
{
    int cnt[128] = {0};
    for(DuLinkList ptr=head; ptr!=NULL; ptr=ptr->next)//计算各字母数量
    {
        cnt[(int)ptr->data]++;
    }
    DuLinkList newNode,outhead=NULL,outtail=NULL;
    char middle='\0';//检测中间值是否占用
    for(int i='A'; i<'z'; i++)
    {
        if(cnt[i]>0)
        {
            if(cnt[i]%2 == 0)//偶数个
            {
                for(int j=0; j<(cnt[i]/2); j++)
                {
                    CreateDuLNode(&outhead,&outtail,(char)i);
                }
            }
            else
            {
                for(int j=0; j<(cnt[i]-1)/2;j++)
                {
                    CreateDuLNode(&outhead,&outtail,(char)i);
                }
                if(middle == '\0')
                {
                    middle=i;
                }
            }
        }
    }
    if(middle != '\0')
        CreateDuLNode(&outhead,&outtail,middle);
    DuLinkList left = outtail;//向左扫描
    while (left->prior!=NULL)
    {
        CreateDuLNode(&outhead,&outtail,left->prior->data);
        left = left->prior;
    }
    return outhead;
}