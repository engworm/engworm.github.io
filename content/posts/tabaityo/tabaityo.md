---
title: "はじめての多倍長計算"
date: 2022-06-30T21:19:09+09:00
draft: false
---

## 多倍長計算とは

## 暗黙のキャスト

C++ライブラリboostによるコードをみてみましょう．

```cpp
  int x = 3.14;
  std::cout << x << std::endl; // 3

  boost::multiprecision::cpp_dec_float_100 p("3.14");
  int y = p; // error: cannot convert
  std::cout << y << endl;
```
