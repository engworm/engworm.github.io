---
title: "参照でできること（初級編）"
date: 2022-05-18T00:38:31+09:00
draft: false
---

## 参照とは

C++では参照型がはじめの難関だと思います．
私はCからC++に入ったのでポインタには慣れていましたが，参照型は長年パッとしませんでした．
配列を題材に参照について試行錯誤してみようと思います．

さて，わかりやすく説明するなら参照とはエイリアス（別名）[^1]のことです．
下のコードをみてください．

```cpp
double *data;
data = new double[10];

double * &x = data;
```

dataはdoubleを指すポインタ型で，doubleを10個格納できる配列の先頭を指しています．
つまり，xはdoubleを指すポインタの別名（参照）というわけです．

```cpp
*(x+1) = 4.6;
cout << *(data+1) << endl;  // 4.6

x[1] = 2.;
cout << data[1] << endl;    // 2
```

xはポインタであることを意識するために，C likeに書いた上段とC++ likeに書いた下段を比べてみましょう．
上段のコードではxのポインタに1（8Byte分）を足したものを逆参照し，値を代入しています．
下段はそれを簡略化して書いただけです．
いずれにせよ，ポインタxを逆参照することで元のdataが書き換えられていることがわかります．

## 参照使い方の例

参照型によってどんなことができるのでしょう．
具体的な例でみていきましょう．

doubleをN個格納する配列dataに，以下のような操作を行う関数show, plusoneを与えます．

- showはdataの要素を改行しながら表示する
- plusoneはdataの要素全てに1を足して上書きする

```cpp
#include <iostream>

void show(double * arr) { 
  for (int i = 0; i < N; ++i) {
    std::cout << arr[i] << std::endl;
  }
  return;
}

void plusone(double * &arr) { 
  for (int i = 0; i < N; ++i) {
    arr[i] += 1.;
  }
  return;
}

int main() {
  double *data = nullptr;
  data = new double[2];

  // dataは適当に初期化する
  data[0] = 1.3;
  data[1] = 2.9;

  show(data); // 1.3, 2.9

  plusone(data);
  show(data); // 2.3, 3.9;

  return 0;
}

```

showではポインタ型を引数として渡しているのでポインタ渡し，
plusoneでは（ポインタの）参照型を引数として渡しているので参照渡しを夫々しています．
下段では，doubleを指すポインタの別名（参照）がarrなので，arrを触ると元のdataの要素が+1されていますね．

## 中級編に向かって

初級編では，配列における参照型の使い方を1つおみせしました．
ポインタの参照というのは便利なものですので，これに慣れることがはじめのステップなのだと思います．

しかし，この問題はまだまだここからです．
参考文献にあげている
[C++プログラミング入門](https://www.amazon.co.jp/C-%E3%83%97%E3%83%AD%E3%82%B0%E3%83%A9%E3%83%9F%E3%83%B3%E3%82%B0%E5%85%A5%E9%96%80-%E3%82%B0%E3%83%AC%E3%82%B4%E3%83%AA%E3%83%BC-%E3%82%B5%E3%83%86%E3%82%A3%E3%82%A2/dp/4873110637)
では以下のように書かれています．

>> しかし，参照は入力の手間を省くためにC++に導入されたのではありません。C++では、抽象化が行われる関係上、ユーザに関数が呼び出されていることを明示的に知らせずに関数が起動される必要があるために、参照が導入されたのです。

最近なんとなくわかってきたような気はしますが，きちんと言語化できるレベルには達していません．
これからも参照型については注目して勉強していこうと思います．

## 数値計算に役立つTips: 動的配列

配列の確保には，new delete を使って配列を動的に確保するやり方と，静的に確保するやり方があります．
初学者のころ，静的配列として非常に大きな配列を取ろうとしてエラーになり，とても迷った経験があります．

```cpp
double *data1;
data1 = new double[10];

double data2[10];
```

data1もdata2も，double型を10個格納できる配列の先頭を指すアドレスが入っている点は同じです．
配列をdata2に渡したときに配列がポインタに退化しているのです．

それからshowとplusoneについても補足しておきます．
これらには，安全のためconst修飾を下に示すように適切に付けなければなりません．
nullptrチェックも必要です．

```cpp
void show(const double * const arr) { 
  if (arr == nullptr) return;
  for (int i = 0; i < N; ++i) {
    std::cout << arr[i] << std::endl;
  }
  return;
}

void plusone(double * const &arr) { 
  if (arr == nullptr) return;
  for (int i = 0; i < N; ++i) {
    arr[i] += 1.;
  }
  return;
}
```

const修飾がどう掛かってくるのかということについては，参考文献の
[図解：constとポインタと参照](https://qiita.com/yohhoy/items/feadbe1a245caadc44f7)
をみてください．

[^1]:参照は別名なのだと思うと，参照型が必ず初期化されなければならない理由がわかりますね．存在しないものに名前をつけることはできませんから．

[^2]:この方が好きですが読みづらいので，普段は省略して書いています．

## 参考文献

[C++プログラミング入門](https://www.amazon.co.jp/C-%E3%83%97%E3%83%AD%E3%82%B0%E3%83%A9%E3%83%9F%E3%83%B3%E3%82%B0%E5%85%A5%E9%96%80-%E3%82%B0%E3%83%AC%E3%82%B4%E3%83%AA%E3%83%BC-%E3%82%B5%E3%83%86%E3%82%A3%E3%82%A2/dp/4873110637)

[図解：constとポインタと参照](https://qiita.com/yohhoy/items/feadbe1a245caadc44f7)
