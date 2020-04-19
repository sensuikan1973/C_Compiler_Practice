#include "9cc.h"

// NOTE: '_' も含む
static bool is_alpha(char *ch) {
  return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || ch == '_';
}

static bool is_alpha_or_num(char *ch) {
  return is_alpha(ch) || ('0' <= ch && ch <= '9');
}

static bool is_prefix(char *str, char *prefix) {
  return strncmp(prefix, str, strlen(prefix)) == 0;
}

// 新しいトークンを作成してcurに繋げる
static Token *new_token(TokenKind kind, Token *cur, char *str, int len) {
  Token *tok = calloc(1, sizeof(Token));
  tok->kind = kind;
  tok->str = str;
  tok->len = len;
  cur->next = tok;
  return tok;
}

// 入力値(user_input)をトークナイズする
Token *tokenize() {
  char *p = user_input;
  Token head;
  head.next = NULL;
  Token *cur = &head;

  while (*p) {
    // 空白文字をスキップ
    if (isspace(*p)) {
      p++;
      continue;
    }

    // return
    if (strncmp(p, "return", 6) == 0 &&
        !is_alpha_or_num(p[6]) // "returnX" みたいなのは許さない
    ) {
      cur = new_token(TK_RESERVED, cur, p, 6);
      p += 6;
      continue;
    }

    if (is_prefix(p, "==") || is_prefix(p, "!=") || is_prefix(p, ">=") ||
        is_prefix(p, "<=")) {
      cur = new_token(TK_RESERVED, cur, p, 2);
      p += 2;
      continue;
    }

    if (*p == '+' || *p == '-' || *p == '*' || *p == '/' || *p == '(' ||
        *p == ')' || *p == '<' || *p == '>' || *p == ';' || *p == '=') {
      cur = new_token(TK_RESERVED, cur, p++, 1);
      continue;
    }

    // 数値
    if (isdigit(*p)) {
      cur = new_token(TK_NUM, cur, p, 0);
      cur->val = strtol(p, &p, 10);
      // digit の場合、長さなんぞどうでもいので、cur->len は埋めてない
      continue;
    }

    // 変数
    if (is_alpha(*p)) {
      char *str = p++;
      while (is_alpha_or_num(*p)) {
        p++;
      }
      cur = new_token(TK_IDENT, cur, str, p - str);
      continue;
    }

    error_at(p, "トークナイズできません");
  }

  new_token(TK_EOF, cur, p, 0);
  return head.next;
}
