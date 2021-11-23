<h1 style="text-align: center"> __builtin_ </h1>



GCC 编译器提供了一系列以 `__builtin_` 开头的函数，方便我们使用。

- `__builtin_ffs(x)`：返回 `x` 中最后一个为 `1` 的位是从后向前的第几位。

  ```cpp
  cout << __builtin_ffs(4) << endl;
  // 3
  ```

- `__builtin_popcount(x)`：`x` 中 `1` 的个数。

  ```cpp
  cout << __builtin_popcount(233) << endl; // 233d = 1110,1001b
  // 5
  ```

- `__builtin_ctz(x)`：`x` 末尾 `0` 的个数。

  ```cpp
  cout << __builtin_ctz(4) << endl;
  // 2
  ```

  注：`__builtin_ctz(x)` 和 `__builtin_ffs(x) - 1` 的值相同

- `_builtin_clz(x)`：`x` 前导 `0` 的个数。

  ```cpp
  cout << __builtin_clz(233) << endl;
  // 24
  ```

- `__builtin_parity(x)`：`x` 中 `1` 的奇偶性。

  ```cpp
  cout << __builtin_parity(233) << endl;
  // 1
  ```

- `uint16_t __builtin_bswap16 (uint16_t x)`

  `uint32_t __builtin_bswap32 (uint32_t x)`：以字节为单位，翻转字节排列的顺序

  ```cpp
  cout << __builtin_bswap16(693) << endl; // 693d = 10,1011,0101b
  // 46338    --> 46388d = 1011,0101,0000,0010b
  
  cout << __builtin_bswap32(9876152) << endl; // 9876152d = 1001,0110,1011,0010,1011,1000
  // 3098711552    --> 3098711552d = 1011,1000,1011,0010,1001,0110,0000,0000b
  ```

