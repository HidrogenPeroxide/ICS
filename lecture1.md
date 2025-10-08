# 整数

1Byte = 8bit = 8二进制位

---

**machine word 机器字**（一次整数运算所能处理的二进制数据的位数)

- 数据地址长度（x86-64支持256TB)
- 地址按byte定位
  - 相邻地址相差4（32位)、8（64位)
  - 取最低byte编址为地址「一个地址指向一个byte」

---

**byte ordering 字节序**

- 大端（big endian)：最低权重字节 LOB 占据高地址
  - Internet，Java
- 小端（little endian)：
  - x86，ARM，RISC-V

---

**整数的二进制编码方式**

- 无符号数

$$
B2U(X) = \sum_{i=0}^{w-1} x_i \cdot 2^i
$$

- 带符号数（补码 = 绝对值各位取反 + 1 = $2^w$ + 负数)
  - 补码MSB位表示整数符号（1 for negative，0 for nonnegative)
    - $T_{\min} = -2^{w-1}$：100...0
    - $T_{\\max} = 2^{w-1} - 1$：011...1

$$
B2T(X) = -x_{w-1}\cdot 2^{\,w-1} + \sum_{i=0}^{w-2} x_i \cdot 2^i
$$

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
  -
