## 80x86汇编语言与C语言

### 冯诺依曼架构

- 程序计数器（PC)
  - 存储下一条指令地址，x86-64为RIP
- 条件码：存储最近执行指令的状态信息
- 内存：
  - 以字节编码的连续存储空间
  - 存放程序代码、数据/栈/堆

---

### 汇编语言

```bash
gcc -Og -S try.c
```

| 后缀 | 类型     | 数据大小        |
| ---- | -------- | --------------- |
| B    | BYTE     | 1byte           |
| W    | WORD     | 2bytes (16bits) |
| L    | LONG     | 4bytes          |
| Q    | QUADWORD | 8bytes          |

- x86-64：16个通用寄存器

---

### 数据传输

```asm
moveq Source, Dest
```

- 操作数类型：立即数（整型常数)
  - `$0x400`
- 寄存器：16个寄存器之一
  - `%rax`, `(%rax)`表示存入内存
  - `%rsp `具有特殊用途

---

### 寻址

```
D(Rb, Ri ,S) # 内存地址：Mem[Reg[Rb]+S*Reg[Ri]+D]
```

- 参数通过寄存器传递
  - 参数<7时，从左向右放入
  - 参数>=7时，前6个从左向右，之后从右向左

swap函数执行过程：

```
swap:
    movq (%rdi), %rax
    movq (%rsi), %rdx
    movq %rdx, (%rdi)
    movq %rax, (%rsi)
    ret
```

---

### 地址计算指令

```
leaq Src, Dest
```

- Src是地址计算表达式，赋值给test
