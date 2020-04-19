#include "9cc.h"

#define DEBUG

int main(int argc, char **argv) {
  DEBUG_PRINT();
  if (argc != 2) {
    error("引数の個数が正しくありません");
    return 1;
  }

  user_input = argv[1];
  token = tokenize(argv[1]);
  program();

  // アセンブリの前半部分を出力
  printf(".intel_syntax noprefix\n");
  printf(".global main\n");
  printf("main:\n");

  // プロローグ
  // 変数 26 個分の領域を確保
  printf("  push rbp\n");
  printf("  mov rbp, rsp\n");
  printf("  sub rsp, %d\n", 8 * 26);

  // 抽象構文木を下りながらコード作成
  for (int i = 0; code[i]; i++) {
    gen(code[i]);

    // 式の評価結果としてスタックに1つの値が残っているはずなので、スタックが溢れないように
    // pop しておく
    printf("  pop rax\n");
  }

  // エピローグ
  // 最後の式の結果が RAX に残ってるので、それが返り値になる
  printf("  mov rsp, rbp\n");
  printf("  pop rbp\n");
  printf("  ret\n");
  return 0;
}
