#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if DEBUG
#define DEBUG_PRINT()                                                          \
  do {                                                                         \
    printf("error at %s:%d\n", __FILE__, __LINE__);                            \
  } while (0);
#else
#define DEBUG_PRINT() ;
#endif

// トークンの種類
typedef enum {
  TK_RESERVED, // 記号
  TK_IDENT,    // 識別子
  TK_NUM,      // 整数トークン
  TK_EOF,      // 入力の終わりを表すトークン
} TokenKind;

// トークン型
typedef struct Token Token;
struct Token {
  TokenKind kind; // トークンの型
  Token *next;    // 次の入力トークン
  int val;        // kindがTK_NUMの場合、その数値
  char *str;      // トークン文字列
  int len; // トークンの長さ。トークンでなければ 0 を入れる。
};

// 抽象構文木のノードの種類
typedef enum {
  ND_ADD,        // +
  ND_SUB,        // -
  ND_MUL,        // *
  ND_DIV,        // /
  ND_ASSIGN,     // = 代入
  ND_LVAR,       // ローカル変数
  ND_NUM,        // 整数
  ND_EQ,         // ==
  ND_NOT_EQ,     // !=
  ND_LESS,       // <
  ND_LESS_OR_EQ, // <=
} NodeKind;

// 抽象構文木のノードの型
typedef struct Node Node;
struct Node {
  NodeKind kind; // ノードの型
  Node *lhs;     // 左辺
  Node *rhs;     // 右辺

  // NOTE: kind が ND_NUM の場合のみ使う
  int val;

  // kind が ND_LVAR の場合のみ使う
  // NOTE:
  // ローカル変数のベースポインタからのオフセットを表す。
  // 今のところ、ローカル変数は名前で決まる固定の位置にあるものとしているから。
  // 変数 'a' は RBP-8, 'b' は RBP-16
  // という感じで固定するとしているので、オフセットは構文解析の段階で決定できる。
  int offset;
};

/* 関数定義 */
void error(char *fmt, ...);
void error_at(char *loc, char *fmt, ...);

void gen(Node *node);

Token *tokenize();
Node *program();

/* グローバル変数 */

// 入力プログラム
char *user_input;

// 現在着目しているトークン
Token *token;

// セミコロン区切りで複数の式を書けるように、パース結果の Node を保存
// 末尾は NULL で表現するものとする
Node *code[100]; // 仮なので、雑に 100
