#include <iostream>
using namespace std;

void function(int a, int b, int c) {
  int buffer[5];
  buffer[0] = 0;
  buffer[4] = 4;
  int *p = buffer + 9; // 戻り番地  +8:BasePointer 
  
}

int main() {
  int x;

  x = 0;
  function(1,2,3);
  x = 1;
  cout << x << endl;
  return 0;
}


/************************************************
<デバック>
> gdb 実行ファイル名
> disassemble 関数名

<デバックの終了>
> q

<実行結果>
   0x00000000004007e4 <+0>:	push   %rbp
   0x00000000004007e5 <+1>:	mov    %rsp,%rbp
   0x00000000004007e8 <+4>:	mov    %edi,-0x24(%rbp)
   0x00000000004007eb <+7>:	mov    %esi,-0x28(%rbp)
   0x00000000004007ee <+10>:	mov    %edx,-0x2c(%rbp)
   0x00000000004007f1 <+13>:	movl   $0x0,-0x20(%rbp) // Array[0]
   0x00000000004007f8 <+20>:	movl   $0x4,-0x10(%rbp) // Array[4]
   0x00000000004007ff <+27>:	lea    -0x20(%rbp),%rax // Array[0]のアドレス
   0x0000000000400803 <+31>:	add    $0x24,%rax       // 変異を追加
   0x0000000000400807 <+35>:	mov    %rax,-0x8(%rbp)
   0x000000000040080b <+39>:	mov    -0x8(%rbp),%rax
   0x000000000040080f <+43>:	mov    (%rax),%eax
   0x0000000000400811 <+45>:	lea    0x1(%rax),%edx
   0x0000000000400814 <+48>:	mov    -0x8(%rbp),%rax
   0x0000000000400818 <+52>:	mov    %edx,(%rax)
   0x000000000040081a <+54>:	leaveq 
   0x000000000040081b <+55>:	retq  

************************************************/
