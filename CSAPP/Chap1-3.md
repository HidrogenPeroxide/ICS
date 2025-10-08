## 第一章 计算机系统漫游

- 只由ASCII码构成的文件为「文本文件」，其余都为二进制文件
  - `hello.c`是文本文件

`hello.c` -(预处理器cpp)->`hello.l -(编译器ccl)->` `hello.s` -(汇编器as) -> `hello.o` -(链接器ld) -> `hello`

- `printf`函数存储在 `printf.o`文件中，链接器负责合并 `*.o`

---

### ALU（计算逻辑单元)

控制单元（CU)发指令，ALU从**寄存器**中获取操作数

- 算数运算
- 逻辑运算：与、或、非、异或（XOR)
- 移位与比较
  - 逻辑移位（for unsigned)
  - 算数移位（for int, 右移时补符号位)

---

### 并发与并行

- 线程级并发，指令级并行，单指令多数据并行

---

## 第二章 信息的表示和处理

### 信息存储

- 8位块（字节，byte)作为最小可寻址的存储器单位

  - 地址能精确定位的存储单元 0x1000 = 第1000个byte
- 16进制、10进制与2进制转化

  - `0x` 前缀 = 16进制
  - `0b` 前缀 = 2进制

```c
scanf("%d", &num);
printf("0x%X\n", num); // 转化为16进制，大写A-F
```

- 字长（32位、64位)

  - 字长为w，虚拟地址$ 0-2^w$
- 数据大小

| C声明              | 32 位 | 64 位 |
| ------------------ | ----- | ----- |
| char               | 1     | 1     |
| short int          | 2     | 2     |
| int                | 4     | 4     |
| **long int** | 4     | 8     |
| long long int      | 8     | 8     |
| char *             | 4     | 8     |
| float              | 4     | 4     |
| double             | 8     | 8     |

---

**byte ordering 字节序**

- 大端（big endian)：最低权重字节 LOB 占据高地址
  - Internet，Java
- 小端（little endian)：
  - x86，ARM，RISC-V

---

**C语言位级运算**

- 逐位操作二进制数
- `|` (OR), `&` (AND), `~` (NOT), `^` (XOR)

---

### 整数表示

- 64位中：

  - INT_MAX = $2^{32} -1$, LONG_MAX = LLONG_MAX = $2^{64} -1$
- 32位中：

  - INT_MAX = LONG_MAX
- 无符号数

$$
B2U(X) = \sum_{i=0}^{w-1} x_i \cdot 2^i
$$

- 带符号数（补码 = 反码 + 1 = $2^w$ + 负数)
  - 补码MSB位表示整数符号（1 for negative，0 for nonnegative)
    - $T_{\min} = -2^{w-1}$：100...0
      - 一般写作 -2147483647-1 避免字面量溢出
    - $T_{\\max} = 2^{w-1} - 1$：011...1

$$
B2T(X) = -x_{w-1}\cdot 2^{\,w-1} + \sum_{i=0}^{w-2} x_i \cdot 2^i
$$

- 反码：（最高位权重 + 1)
  - 最高位表示正负，其余位取反

$$
B2O_w(X) = -x_{w-1}(2^{w-1} - 1) + \sum^{w-2} x_i \cdot 2^i
$$

- 原码：最高位表示正负，其余不变（B2S)

---

### 有符号数、无符号数的转换

- 「按位取反+1」代替减法

  - $x - y = x + (\~y) + 1$
- 无符号数与带符号数混合使用时默认为无符号数
- 常数默认带符号数（无后缀U)

  - -1 < 0（signed)
  - -1 > 0U（unsigned)
- 模运算、按位运算使用unsigned

---

**四则运算**

- 补码加法溢出：放弃进位时MSB可能改变
- 无符号数$\div 2^w$：`return x >> w`
- 带符号数$\div 2^w$：算数右移时舍入错误（-706.5 -> -707)

  - 偏置量（bias)：$(x + 2^w - 1) \div 2^w $
- 常数乘法：2的幂次分解 -> 移位实现

---

### 浮点数表示

- IEEE 754标准
  - 只能精确表示$x \div 2^y$的数

$$
d = \sum_{i = -n}^m{10^i} \times d_i
$$

$$
\text{Value} = (-1)^S \times (1.\text{Fraction}) \times 2^{(E - \text{bias})}
$$

- 符号、尾数、阶码：
  - 符号（sign）：决定正负数
  - 尾数（significand）：二进制小数（1~2-epsilon或0~1-epsilon）
  - 阶码（exponent）：浮点数加权2的E次幂
- 单精度浮点数（float)
  - 1 + 8 + 23 = 32byte
- 双精度浮点数（double)
  - 1 + 11 + 52 = 64byte
- 半精度浮点数
  - 1 + 5 + 10
  - BF16：1 + 8 + 7（深度学习)

|  s   | exp       |          frac           |            |
| :--: | --------- | :---------------------: | ---------- |
|  s   | !=0&!=255 |            f            | 规格化数   |
|  s   | 0000 0000 |            f            | 非规格化数 |
|  s   | 1111 1111 | 00000000000000000000000 | 无穷大     |
|  s   | 1111 1111 |           !=0           | NaN        |

---

## 第三章 程序的机器级表示

| 后缀 | 类型     | 数据大小        |
| ---- | -------- | --------------- |
| B    | BYTE     | 1byte           |
| W    | WORD     | 2bytes (16bits) |
| L    | LONG     | 4bytes          |
| Q    | QUADWORD | 8bytes          |

---

### 访问信息

#### 寻址

- 操作数（operand）：

  - 立即数（immediate）：`$0x1F`, `$-577`

  - 寄存器（register）：`%rax`
    - x86-64：16个通用寄存器

  - 存储器（memory）：`M[Addr]`，可以是`Imm`, `(E_a)`

- 寻址模式
  - `disp`通常是`Imm`

```scss
disp(base, index, scale)
```

```csharp
Effective Address = disp + base + index * scale
```

---

#### MOV指令

- 零扩展&符号扩展：放入更大寄存器时
  - 零扩展：unsigned（无符号数），用0扩充高位
    - 0000 1010 -> 0000 0000 0000 1010
  - 符号扩展：signed，最高位（符号位）的值复制到所有新扩展的高位
    - 1000 1010 -> 1111 1111 1111 1000 1010

- mov

```asm
mov src, dst
```

`mov $imm, %rax` 支持 64 位立即数， `mov $imm, (%rax)` 只能32 位立即数（自动零扩展）

- movs：符号扩展
  - `movswq` : 符号扩展，W（双字，16位）到Q（64位）

```
movs[src_type][dst_type] src, dst
```

- movz：0扩展

- movabsq, movsd*

---

#### 简单的栈s

- `%rsp`：栈指针，指向当前栈顶
- `%rbp`：栈帧基址（base pointer）访问局部变量

```asm
pushq %rbp      # 保存旧栈帧
movq %rsp, %rbp # 建立新栈帧
subl $16, %rsp  # 为局部变量开辟16字节空间
```

---

### 算术与逻辑操作

加载有效地址，一元操作，二元操作，移位

#### leal指令

