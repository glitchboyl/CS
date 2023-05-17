#include <stdio.h>
#include <string.h>

// 朴素模式匹配字符串算法（即暴力解法）
int SubIndex(char *str, char *substr)
{
  int len = strlen(str);       // 计算字符串长度
  int subLen = strlen(substr); // 计算子串长度

  if (subLen > len) // 如果子串长度超过了字符串长度，则返回-1
    return -1;

  int i = 0, j = 0;             // 对于字符串和子串，一个从头开始，一个从第一位开始
  while (i < len && j < subLen) // 当字符串或子串还没扫描完时循环执行
  {
    if (str[i] == substr[j]) // 若字符匹配成功，继续进行下一位的匹配
    {
      i++; // 字符串指针向前移动一位
      j++; // 子串指针向前移动一位
    }
    else // 若匹配失败
    {
      i = i - j + 1; // 字符串指针回退到上一次匹配的下一位，即下一个位置开始
      j = 0;         // 子串指针重置为0
    }
  }

  if (j == subLen) // 扫描完整个子串，说明匹配成功，返回子串首位在字符串中的下标
    return i - subLen;
  else // 否则匹配失败，返回-1
    return -1;
}

int main()
{
  char str[] = "the deep dark fantasy";
  char substr[] = "deep";

  // 调用函数并输出结果
  printf("the first occurrence index of \"%s\" in \"%s\" is %d", substr, str, SubIndex(str, substr));
  return 0;
}
