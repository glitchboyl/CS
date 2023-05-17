#include <stdio.h>
#include <string.h>

int kmp(char *str, char *substr)
{
  int len = strlen(str);       // 计算文本串的长度
  int subLen = strlen(substr); // 计算模式串的长度
  if (subLen > len)            // 特判：如果模式串比文本串长，则无法匹配
  {
    return -1;
  }

  // 计算next数组
  int next[subLen];
  next[0] = 0; // 初始化next数组
  int i = 0, j;
  for (j = 1; j < subLen; j++) // 计算next数组，从1开始
  {
    // 在子串的前缀和后缀中寻找最长的相等部分
    while (i > 0 && substr[i] != substr[j]) // 如果不相等，则向前跳
    {
      i = next[i - 1];
    }
    // 如果相等，则在原有最长相同前缀的基础上加 1
    if (substr[i] == substr[j])
    {
      i++;
    }
    next[j] = i; // 保存next数组
  }

  // 在文本串中匹配子串
  i = j = 0;
  while (i < len && j < subLen)
  {
    if (str[i] == substr[j]) // 如果匹配成功，则继续匹配下一个字符
    {
      i++;
      j++;
    }
    else // 如果匹配失败，则根据next数组进行跳转
    {
      j = next[j];
      if (j == 0) // 如果j已经回到模式串起始位置，i和j同时后移
      {
        i++;
        j++;
      }
    }
  }

  // 匹配成功则返回子串在文本串中的起始下标，否则返回-1
  return (j == subLen) ? (i - j) : -1;
}

int main()
{
  char str[] = "the deep dark fantasies of van darkholme"; // 文本串
  char substr[] = "darkh";                                 // 模式串
  printf("the first occurrence index of \"%s\" in \"%s\" is %d", substr, str, kmp(str, substr));
  return 0;
}