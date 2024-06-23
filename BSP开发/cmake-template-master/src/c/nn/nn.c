// @Author: Farmer Li, 公众号: 很酷的程序员/RealCoolEngineer
// @Date: 2021-07-12

int argmax_float(float *x, int len) {
  int   max_idx = 0;
  float p_max = x[0];
  for (int i = 1; i < len; ++i) {
    if (p_max < x[i]) {
      p_max = x[i];
      max_idx = i;
    }
  }
  return max_idx;
}
