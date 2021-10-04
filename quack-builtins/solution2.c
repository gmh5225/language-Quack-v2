int solution(int A, int B) {
  // write your code in C99 (gcc 6.2.0)
  int mul = abs(A * B);
  int res = 0;
  while (mul > 0) {
    int bin = mul % 2;
    if (bin)
      res += bin;
    mul = mul / 2;
  }

  if (A * B < 0) // negative
    res += 1; // signed bit

  return res;
}
