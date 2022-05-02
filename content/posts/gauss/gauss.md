---
title: "Gaussの発散定理に関する備忘録"
date: 2022-05-02T14:02:43+09:00
draft: false
math: true
---

# はじめに

ベクトル解析で学習するGaussの発散定理は，様々な書き方の流儀があります．
初学者にとっては混乱しがちな箇所であり，最近見直す機会があったのでわかりやすくまとめておきたいと思います．

嘘は書いていないつもりですが，ごまかしている箇所はあります．
講義ノートや本と比較して検証してみてください．

## （復習）Gaussの発散定理

まずは主張を書いておきましょう．

\\(\Omega\subset \mathbb{R}^2\\)は有界領域，
\\(\partial\Omega\\)は十分滑らかとする．
このとき，\\(\overline{\Omega}\\)上で滑らかなベクトル値函数\\(\overrightarrow{F}(x,y)=\left(f_1(x,y), f_2(x,y)\right)\\)に対し，
$$
\int_{\Omega}\mathrm{div}\overrightarrow{F}(x,y)dxdy
= \int_{\partial\Omega}\overrightarrow{F}(x,y)\cdot \overrightarrow{\nu}ds
$$
が成立する．
但し，\\(\overrightarrow{\nu}\\)は\\(\partial\Omega\\)上の外向き単位法線ベクトルであり，
\\(ds\\)は\\(\partial\Omega\\)上の線素とする．

線素\\(ds\\)について説明しておきましょう．
\\(s\\)は弧長パラメータと言って，ある地点を\\(s=0\\)として測った曲線の長さを表します，
線素\\(ds\\)とは\\(s\\)の微小変化量ということです．

それから，式を読む際の注意点です．
\\(\overrightarrow{F}(x,y)\\)のことを\\(F(x)\\)としたり，
\\(dxdy\\)のことを\\(dx\\)と書くことがあります．
内積\\(\cdot\\)が省略されることもあります．
書き方の流儀が問題になると申し上げたのはここで，
ベクトル解析の分野では省略されている箇所を補って読む必要が多いのです．
複雑な箇所は慣れるまで省略せずに書きましょう．[^1]

## Stieljtes積分の形にする

境界\\(\partial\Omega\\)上の点\\((x,y)\\)は弧長パラメータ\\(s\\)を用いて\\((x(s),y(s))\\)と表すことができます．
したがって，点\\((x,y)\\)における単位接線ベクトル\\(\overrightarrow{\tau}\\)は[^2]
$$
\overrightarrow{\tau} =
\left(
\begin{array}{c}
\frac{dx}{ds} \\
\frac{dy}{ds}
\end{array}
\right)
$$
と表すことができます．
\\(\overrightarrow{\tau}\\)を負方向に\\(\pi/2\\)回転させることで，外向き単位法線ベクトル\\(\overrightarrow{\nu}\\)を
$$
\overrightarrow{\nu} =
\left(
\begin{array}{c}
\frac{dy}{ds} \\
-\frac{dx}{ds}
\end{array}
\right)
$$
と具体的に書くことができました．

Gauss発散定理の右辺に代入しましょう．
すると，
$$
\begin{aligned}
\int_{\partial\Omega}\overrightarrow{F}(x,y)\cdot \overrightarrow{\nu}ds
&= \int_{\partial\Omega}
\left(
\begin{array}{c}
f_1 \\
f_2
\end{array}
\right)
\cdot
\left(
\begin{array}{c}
\frac{dy}{ds} \\
-\frac{dx}{ds}
\end{array}
\right)ds \\
&= \int_{\partial\Omega}\left(f_1\frac{dy}{ds}-f_2\frac{dx}{ds}\right)ds \\
&= \int_{\partial\Omega}f_1dy - f_2dx
\end{aligned}
$$
となります．
これで，線素を用いた線積分だった右辺がStieltjes積分になりましたね．

## Greenの公式

\\(f_1(x,y)=Q(x,y),f_2(x,y)=-P(x,y)\\)とすると，
$$
\int_{\Omega}\left(\frac{\partial Q}{\partial x} - \frac{\partial P}{\partial y}\right)dxdy
= \int_{\partial\Omega}Pdx + Qdy
$$
となって，Greenの公式の形になりました．

## さいごに

ひとつ好きな表現を覚えておいて，一方を導けるようにしておくと安心ですね！

[^1]:私は普段ベクトルをボールド体で書きませんが，このスタンスで流体力学の講義ノートを書いて大変な目にあったことがあります．柔軟に流儀を使い分けるのがいいと思います．

[^2]:弧長パラメータ$s$を用いることで，特に"単位"接線ベクトルになります．
