---
title: "はじめての多倍長計算"
date: 2022-06-30T21:19:09+09:00
draft: false
---

## 多倍長計算とは

私の所属する数値計算の研究室では，ことあるごとに「計算環境はパラメータの一つに過ぎない」と言われて育ちます．

計算環境として代表的なのは間違いなく倍精度環境でしょう．
これは，一般的に不動小数点を扱う環境であり，10進法で約15桁の有効桁数を持ちます．
多くの場面で使われていますね．

一方，多倍長環境は倍精度環境以上の有効桁数をもち，（計算時間と引き換えに）50桁や100桁精度の計算が可能になります．
今日は先程の格言を思い出しながら，C++/boostを用いて多倍長計算の世界を覗いてみましょう．

## double型から多倍長へのキャスト

double型から多倍長への暗黙のキャストは許されていますが，非常に注意しなければなりません．
下のコードをみてみましょう．
円周率を50桁表示させています．[^1]

[^1]:100桁で出力可能ですが，ページの横幅に入らなかったので50桁だけ表示しています．

```cpp
#include <iostream>
#include <iomanip>
#include <cmath>
#include <boost/multiprecision/cpp_dec_float.hpp>

using namespace boost::multiprecision;

constexpr int d = std::numeric_limits<double>::digits10;
constexpr int dd = std::numeric_limits<cpp_dec_float_100>::digits10;

int main() {

  cpp_dec_float_100 pi = M_PI;

  std::cout << showpoint;
  std::cout << std::setprecision(50)
             << pi << std::endl;

  return 0;
}
```

```txt
3.1415926535897931159979634685441851615905761718750
```

ん？
気づきましたでしょうか．
[暗黒通信団 円周率1,000,000桁表](https://www.amazon.co.jp/%E5%86%86%E5%91%A8%E7%8E%871000000%E6%A1%81%E8%A1%A8-%E7%89%A7%E9%87%8E-%E8%B2%B4%E6%A8%B9/dp/487310002X)
と比較すると，この円周率の17桁目以降はデタラメな値になっているのです！！[^2]

[^2]:修士1年生の頃，この暗黙のキャストによってデタラメな値になっていることに気づかないままセミナー発表に突入したことがあります．トラウマです．

正しくは下のようなコードになります．

```cpp
#include <iostream>
#include <iomanip>
#include <cmath>
#include <boost/multiprecision/cpp_dec_float.hpp>

using namespace boost::multiprecision;

constexpr int d = std::numeric_limits<double>::digits10;
constexpr int dd = std::numeric_limits<cpp_dec_float_100>::digits10;

cpp_dec_float_100 PI = boost::math::constants::pi<cpp_dec_float_100>();

int main() {

  cpp_dec_float_100 pi = PI;

  std::cout << std::showpoint;
  std::cout << std::setprecision(50)
             << PI << std::endl;

  return 0;
}
```

```txt
3.1415926535897932384626433832795028841971693993751
```

## AtCoderでみる多倍長計算

こちらの[アルゴリズと数学 演習問題集 084](https://atcoder.jp/contests/math-and-algorithm/tasks/panasonic2020_c)
の問題では多倍長計算が有効です．
多倍長環境を使うことで丸め誤差の影響が小さくなるためです．

```cpp
#include <iostream>
#include <boost/multiprecision/cpp_dec_float.hpp>

using namespace boost::multiprecision;

int main() {

  cpp_dec_float_100 a, b, c;
  std::cin >> a >> b >> c;

  a = boost::multiprecision::sqrt(a);
  b = boost::multiprecision::sqrt(b);
  c = boost::multiprecision::sqrt(c);

  if (a + b < c) std::cout << "Yes" << std::endl;
  else std::cout << "No" << std::endl;

  return 0;
}
```

## 名前空間の衝突

組み込み関数がboostの関数と衝突することがあります．
安易にusing namespace std を宣言するとコードの修正が大変になってしまいます．
下の例で，dxとddxの値が一致していることは確認しましたが，ddxのようにきちんとboost::multiprecison名前空間にあるsqrt関数を使うと明示した方が精神衛生上いいと思います．

```cpp
#include <iostream>
#include <iomanip>
#include <boost/multiprecision/cpp_dec_float.hpp>

using namespace boost::multiprecision;

constexpr int d = std::numeric_limits<double>::digits10;
constexpr int dd = std::numeric_limits<cpp_dec_float_100>::digits10;

int main() {
  cpp_dec_float_100 x("2");

  cpp_dec_float_100 dx = sqrt(x);
  cpp_dec_float_100 ddx = boost::multiprecision::sqrt(x);

  std::cout << std::setprecision(dd)
            << dx << std::endl;

  std::cout << std::setprecision(dd)
            << ddx << std::endl;

  return 0;
}
```


## まとめ

多倍長計算のコストは非常に高いので，まずは倍精度でコードを書いてテストすることが多いと思います．
しかし，上のような事情があるので，doubleをcpp_dec_float_100に書き換えれば済む話ではないのです．
1箇所でもdouble型が入ってしまうと，その他の計算をどんなに頑張っても高々16桁の有効桁数しか残りません．
他にも，多倍長浮動小数点がdoubleやintに暗黙のキャストされないというのも実装を難しく[^3]しています．
気をつけて使っていきたいですね！

[^3]:doubleからintは平気でキャストするのに！

## 参考文献

[boostjp](https://boostjp.github.io/tips/multiprec-int.html)

[暗黒通信団　円周率1,000,000桁表](https://www.amazon.co.jp/%E5%86%86%E5%91%A8%E7%8E%871000000%E6%A1%81%E8%A1%A8-%E7%89%A7%E9%87%8E-%E8%B2%B4%E6%A8%B9/dp/487310002X)
