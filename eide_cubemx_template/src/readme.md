# src 文件夹说明

这里存放源代码

如果你修改了 startup_xxx.s 文件，为防止 CubeMX 覆盖，建议将新的文件放到这个文件夹中，然后在 eide 中排除原来的 .s 文件的编译

## 文件命名规则

c 文件：aaa_bbb.c

c++ 文件：aaa_bbb.cpp

对于可以让 .c 包含的头文件，以 .h 结尾

对于只能让 .cpp 包含的头文件，以 .hpp 结尾

示例：

```cpp
// user_main.h
// 该文件没有使用 c++ 特有的语法，.c 和 .cpp 都可以包含它，因此后缀名为 .h

#pragma once // 防止重复包含

// 下面 3 行和最后 3 行可以使得在这两部分之间声明的函数可以同时在 c 和 c++ 中调用
// 具体原理请自行搜索
#ifdef __cplusplus
extern "C" {
#endif

void StartDefaultTask(void const *argument);

#ifdef __cplusplus
}
#endif
```

```cpp
// byte_driver.hpp
// 该文件使用了 c++ 特有的语法，只有 .cpp 都可以包含它，因此后缀名为 .hpp

#pragma once
#include <cstdint>

class ByteDriver
{
    public:
    ByteDriver()                   = default;
    ByteDriver(const ByteDriver &) = delete;
    ByteDriver(ByteDriver &&)      = default;
    ...
};
```

## 建议的目录结构：

```
src/
    user_main.cpp
    user_irq.cpp
    led/
        pwm.h
        led.h
        led.c
    chassis/
        pwm.h
        motor.hpp
        motor.cpp
        ...
    device/
        private/
            private_head_file.hpp
            ...
        button.hpp
        uart.hpp
        led.hpp
        ...
```

**说明：**

Include Path 只添加 src 目录

我们将 led, chassis, device 等文件夹看成软件包。软件包内的头文件分为两部分：

1. 需要给外部 include 的
2. 不需要给外部 include 的

将 2 部分的头文件放在 private 子目录中，这样用户不会被大量头文件扰乱

**Include 方法：**

如果 include 的文件是自己包里的文件，使用 `#include "a.hpp"` ，优先从相对路径中查找文件

如果 include 的文件是其他包中的文件，使用 `#include <package/b.hpp>`，从 Include Path 中查找文件

```cpp
// src/device/led.hpp

 // 自己包里的头文件
#include "button.hpp"                   
#include "private/private_head_file.hpp"

// 其他包中的文件
#include <led/pwm.h>
#include <chassis/pwm.h> // 这样如果出现重名的文件，也能区分
```

user_main.cpp 中也应该像这样包含： `#include <chassis/motor.hpp>`
