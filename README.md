# Menon C++ Library

## 概要
このライブラリは、C++のプログラミングにおいて簡単なことを簡単に記述できるようにすることを目指しています。

## テストプログラムの実行
付属するMakefileを用いてmakeするとテストプログラムをコンパイルし、実行します。

### MinGW-w64またはCygwinを使用する場合
MinGW-w64またはCygwinを使用する場合には、以下の内容のconfig.makを作成してtestディレクトリに配置してください。

```c++:config.mak
 LDFLAGS	=	-liconv
```
