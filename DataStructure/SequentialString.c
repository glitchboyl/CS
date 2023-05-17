#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 255

typedef struct
{
  char *ch;   // 指向存储字符数组的指针
  int length; // 当前串长度
} SeqStr;

// 清空字符串函数
void ClearString(SeqStr *s)
{
  if (s->length > 0) // 如果当前字符串长度大于0
  {
    free(s->ch);   // 释放该串之前申请的内存空间
    s->length = 0; // 将当前串长度更新为0
  }
}

// 字符串赋值
void StringAssign(SeqStr *s, char *str)
{
  ClearString(s);                                         // 先清空字符串
  s->length = strlen(str);                                // 更新当前字符串长度
  s->ch = (char *)malloc((s->length + 1) * sizeof(char)); // 为存储字符数组动态申请内存
  strcpy(s->ch, str);                                     // 将字符串复制到字符数组中
}

// 连接两个字符串
void Concat(SeqStr *s, char *str1, char *str2)
{
  ClearString(s);                                         // 先清空字符串
  int len1 = strlen(str1);                                // 计算第一个字符串的长度
  int len2 = strlen(str2);                                // 计算第二个字符串的长度
  s->length = len1 + len2;                                // 计算新串长度
  s->ch = (char *)malloc((s->length + 1) * sizeof(char)); // 为存储字符数组申请内存
  strcpy(s->ch, str1);                                    // 将第一个字符串复制到字符数组中
  for (int i = 0; i < len2; i++)
  {
    s->ch[len1 + i] = str2[i]; // 将第二个字符串拼接到字符数组中
  }
  s->ch[s->length] = '\0'; // 字符数组末尾添加'\0'作为结束标志，构成字符串
}

// 比较两个字符串的大小
int Compare(char *str1, char *str2)
{
  int len1 = strlen(str1);
  int len2 = strlen(str2);
  // 从头到尾比较两个字符串
  for (int i = 0; i < len1 && i < len2; i++)
  {
    if (str1[i] != str2[i])     // 如果发现不同的字符
      return str1[i] - str2[i]; // 直接返回它们的差值
  }
  return len1 - len2; // 若前缀相同，则长度长的那个字符串更大
}

// 提取原串中指定位置和长度的子串
void SubString(SeqStr s, SeqStr *sub, int pos, int len)
{
  if (pos < 0 || pos >= s.length || len < 1 || len > s.length - pos) // 当输入参数错误时直接返回
    return;
  ClearString(sub);                                   // 先清空字符串
  sub->ch = (char *)malloc((len + 1) * sizeof(char)); // 为存储字符数组动态申请内存
  sub->length = len;
  for (int i = 0; i < len; i++)
  {
    sub->ch[i] = s.ch[pos + i]; // 从指定位置开始提取指定长度的子串
  }
  sub->ch[sub->length] = '\0'; // 字符数组末尾添加'\0'作为结束标志，构成字符串
}

// 查找子串在原串中第一次出现的位置
int SubIndex(SeqStr s, char *sub)
{
  int subLen = strlen(sub); // 获得子串的长度
  if (subLen > s.length)    // 如果子串长度大于原字符串长度，直接返回-1
    return -1;

  SeqStr ss;
  int i;
  // 从头到尾扫描原字符串
  for (i = 0; i <= s.length - subLen; i++)
  {
    if (s.ch[i] == sub[0]) // 如果发现子串的首字符与当前字符匹配
    {
      SubString(s, &ss, i, subLen); // 提取当前位置起始的长度为subLen的子串
      if (Compare(ss.ch, sub) == 0) // 比较子串和待查找串是否相等
      {
        break; // 如果相等，则找到，跳出循环
      }
    }
  }
  ClearString(&ss);                      // 清空子串
  return i > s.length - subLen ? -1 : i; // 若未找到，则返回-1；否则返回第一次出现的位置
}

// 打印字符串
void PrintString(SeqStr s)
{
  printf("%s\n", s.ch);
}

int main()
{
  SeqStr S;
  S.length = 0;
  StringAssign(&S, "hello world"); // 赋值第一个字符串
  PrintString(S);
  Concat(&S, "ass ", "we can"); // 拼接第二个字符串
  PrintString(S);
  char sub[] = "can";
  printf("\"%s\" index start at %d\n", sub, SubIndex(S, sub)); // 查找子串出现的位置
  SeqStr SS;
  SubString(S, &SS, 7, 3); // 提取子串
  PrintString(SS);
  int result = Compare("bsc", "bss"); // 比较两个字符串的大小
  printf(result > 0 ? "first str bigger" : result < 0 ? "second str bigger"
                                                      : "they re equal");
  return 0;
}