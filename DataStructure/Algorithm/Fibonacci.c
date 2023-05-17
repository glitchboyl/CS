#include <stdio.h>

// F(0)=1，F(1)=1, F(n)=F(n - 1)+F(n - 2)（n ≥ 2，n ∈ N*）
int fib(int n)
{
  if (n == 0 || n == 1)
    return 1;
  return fib(n - 1) + fib(n - 2);
}

int main()
{
  int n = 0;
  printf("Input n (preferably less than 10): ");
  scanf("%d", &n);
  printf("fib result: %d", fib(n));
  return 0;
}