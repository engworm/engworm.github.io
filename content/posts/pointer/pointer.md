---
title: "参照でできること（初級編）"
date: 2022-05-06T19:05:57+09:00
draft: true
---

C++の学習をしていると，「参照ってなんだ？」となります．
そこで，まずは参照でできることをサクッとみてみましょう．

## 参照とは

参照というのはピンとしない名前だなって思います．
わかりやすく説明するなら，参照とはエイリアス（別名）のことです．
下のコードをみてください．

```
double *data;
data = new double[10];

double *&x = data;
```

dataはdoubleを指すポインタ型で，doubleを10個格納できる配列の先頭を指しています．
xはdoubleを指すポインタの別名（参照）というわけです．
次のコードをみると，

```
*(x+1) = 4.6;
cout << *(data+1) << endl;  // 4.6

x[1] = 2.;
cout << data[1] << endl;    // 2
```

1段目のコードではxのポインタに1（8Byte分）を足したものを逆参照し，値を代入しています．
ここでいう逆参照とは，日常用語としての逆参照のことです．
2段目のコードは略した書き方で，このように書くこともできます．

さて，参照は別名なのだと思うと，参照型が必ず初期化しなければならない理由がわかりますね．
存在しないものに名前をつけることはできませんから．

## 参考文献
