---
title: "参照でできること（初級編）"
date: 2022-05-06T19:05:57+09:00
draft: false
---

## 参照とは

下書き中．
C++では参照型がはじめの難関だと思います．
私はCからC++に入ったので，ポインタ型と参照型で混乱したことがあります．

わかりやすく説明するなら，参照とはエイリアス（別名）[^1]のことです．
下のコードをみてください．

```cpp
double *data;
data = new double[10];

double * &x = data;
```

dataはdoubleを指すポインタ型で，doubleを10個格納できる配列の先頭を指しています．
xはdoubleを指すポインタの別名（参照）というわけです．

```cpp
*(x+1) = 4.6;
cout << *(data+1) << endl;  // 4.6

x[1] = 2.;
cout << data[1] << endl;    // 2
```

xはポインタであることを意識するために，C likeに書いた上段とC++ likeに書いた下段を比べてみましょう．
1段目のコードではxのポインタに1（8Byte分）を足したものを逆参照し，値を代入しています．
ここでいう逆参照とは，日常用語としての逆参照のことです．
いずれにせよ，ポインタxを逆参照することで元のdataが書き換えられていることがわかります．

## 参照の威力（値渡しと参照渡し）

参照型によってどんなことができるのでしょう．

doubleをN個格納する配列valに何かしらの操作を行う関数f, g, hを次のように与えます．

```cpp
void f(const double * const arr) { 
  std::cout << arr[1] << std::endl;
}

double g(const double * const &arr) { 
  std::cout << arr[1] << std::endl;
}

double h(double * const &arr) { 
  std::cout << arr[1] << std::endl;
  arr[1] = 5.;  
}
```

[^1]:参照は別名なのだと思うと，参照型が必ず初期化しなければならない理由がわかりますね．存在しないものに名前をつけることはできませんから．

## 参考文献

[C++プログラミング入門](https://www.amazon.co.jp/C-%E3%83%97%E3%83%AD%E3%82%B0%E3%83%A9%E3%83%9F%E3%83%B3%E3%82%B0%E5%85%A5%E9%96%80-%E3%82%B0%E3%83%AC%E3%82%B4%E3%83%AA%E3%83%BC-%E3%82%B5%E3%83%86%E3%82%A3%E3%82%A2/dp/4873110637)
[図解：constとポインタと参照](https://qiita.com/yohhoy/items/feadbe1a245caadc44f7)
