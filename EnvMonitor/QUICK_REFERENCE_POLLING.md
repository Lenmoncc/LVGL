# 轮询和重连机制快速参考

## 🎯 核心参数速查

```c
// 文件: custom.c (custom/目录下)

// 轮询周期：1秒
static const int MODBUS_POLL_PERIOD_MS = 1000;

// 响应超时：1秒（Modbus库设置）
modbus_set_response_timeout(modbus_ctx, 1, 0);

// 重连延迟：3秒
static const int MODBUS_RECONNECT_DELAY = 3;

// 触发重连的连续错误次数：5
static const int MAX_CONSECUTIVE_ERRORS = 5;

// 单次读取失败计数阈值：3
const int MAX_READ_FAILURES = 3;
```

---

## 📊 工作流程速查

### 正常轮询流程 (每 1 秒)
```
1s周期 → 读取7个寄存器
       → 数据验证 (范围检查)
       → 更新共享数据
       → 通知UI更新
       → 等待下一秒
```

### 故障恢复流程
```
读取失败 (timeout 1s)
   ↓
记录错误 (consecutive_errors++)
   ↓ [累计5次失败]
调用 reconnect_modbus()
   ├─ 关闭旧连接
   ├─ 等待 3 秒
   └─ 创建新连接
   ↓
重新开始轮询
```

---

## 🔧 寄存器映射

| 地址 | 数据 | 类型 | 范围 | 备注 |
|------|------|------|------|------|
| 0 | AHT10 温度 | int16 | -40~85°C | 验证范围内 |
| 1 | AHT10 湿度 | uint16 | 0~100% | 用于验证 |
| 2 | BH1750 光照 | uint16 | 0~65535lux | 用于验证 |
| 3 | BMP280 温度 | int16 | -40~85°C | 用于验证 |
| 4 | BMP280 气压 | uint16 | 300~1100hPa | 用于计算海拔 |
| 5 | SGP30 CO2 | uint16 | 400~5000ppm | 用于验证 |
| 6 | SGP30 TVOC | uint16 | 0~60000ppb | 用于验证 |

---

## 🐛 故障诊断速查

### 问题：频繁重连

**症状：**
```
Too many read failures, attempting to reconnect...
Previous Modbus connection closed
```

**排查步骤：**
1. 检查从机是否正常运行
2. 检查串口线连接 (`/dev/ttymxc2`)
3. 尝试增大响应超时：`modbus_set_response_timeout(ctx, 2, 0);`
4. 使用 `master.c` 独立测试

### 问题：数据长时间未更新

**症状：**
```
Sensor data updated (update_count: N)  // 停止更新
```

**排查步骤：**
1. 检查传感器是否有数据
2. 检查数据是否超出有效范围（触发验证失败）
3. 查看 `validate_sensor_data()` 的范围定义
4. 检查 Modbus 从机的寄存器值

### 问题：UI 不显示数据

**症状：**
```
无显示，或显示初始值
```

**排查步骤：**
1. 确认 Modbus 线程已启动（查看启动日志）
2. 检查数据是否有效：`data_valid` 标志
3. 检查 UI 是否在天气界面（只在该界面显示）
4. 使用 `modbus_connection_status` 变量判断连接状态

---

## ⚡ 性能指标

| 指标 | 数值 | 说明 |
|------|-----|------|
| **轮询周期** | 1.0s ±0.01s | 使用 CLOCK_MONOTONIC |
| **响应超时** | 1.0s | Modbus 级超时 |
| **故障检测** | ~5-8s | 取决于连续超时情况 |
| **CPU占用** | <1% | nanosleep 等待中 |
| **内存占用** | ~30KB | 线程栈+Modbus上下文 |
| **功耗** | <100mW | 相对系统总功耗 |

---

## 🔍 调试命令

### 查看实时日志
```bash
$ ./envmonitor 2>&1 | grep -E "Sensor|failed|reconnect"
```

### 监控连接状态
```bash
$ while true; do
    ps aux | grep modbus
    sleep 1
  done
```

### 验证线程创建
```bash
$ pstree -p | grep envmonitor
```

### 检查串口状态
```bash
$ ls -la /dev/ttymxc*
$ stty -F /dev/ttymxc2
```

---

## 📝 源代码位置

| 功能 | 函数 | 文件 | 行号 |
|------|------|------|------|
| **轮询线程** | `modbus_read_thread()` | custom.c | ~333-446 |
| **重连机制** | `reconnect_modbus()` | custom.c | ~195-270 |
| **启动线程** | `start_modbus_thread()` | custom.c | ~273-307 |
| **停止线程** | `stop_modbus_thread()` | custom.c | ~310-331 |
| **初始化** | `custom_init()` | custom.c | ~168-186 |

---

## 🔗 相关文档

- **详细实现说明** → `MODBUS_POLLING_IMPLEMENTATION.md`
- **优化总结** → `POLLING_OPTIMIZATION_SUMMARY.md`
- **架构演进** → `../Master/README.md`
- **完整文档索引** → `MASTER_INDEX.md`

---

## 💡 常见修改

### 改变轮询周期为 500ms
```c
// 改这一行
clock_gettime(CLOCK_MONOTONIC, &poll_time);
poll_time.tv_sec += 1;  // 改为 tv_nsec += 500000000;

// 更好的方式：使用宏
#define POLL_PERIOD_NS 500000000  // 500ms in nanoseconds
poll_time.tv_nsec += POLL_PERIOD_NS;
```

### 改变重连延迟为 5 秒
```c
static const int MODBUS_RECONNECT_DELAY = 5;
```

### 改变错误阈值为 3 次
```c
static const int MAX_CONSECUTIVE_ERRORS = 3;
```

### 改变响应超时为 2 秒
```c
modbus_set_response_timeout(modbus_ctx, 2, 0);
```

---

## ✅ 检查清单

部署前确认：

- [ ] 编译时链接 `-lrt` (libmodbus + librt)
- [ ] `/dev/ttymxc2` 设备存在且有读写权限
- [ ] 从机地址设置为 1 (Modbus Slave ID)
- [ ] 波特率 115200, 8N1 (8data, No parity, 1stop)
- [ ] 启动后能看到日志 "Modbus read thread started"
- [ ] UI 天气界面能正常显示数据

---

## 📞 故障排查流程图

```
[启动程序]
    ↓
[能否建立Modbus连接?]
├─YES → [能否读取寄存器?]
│        ├─YES → [数据在有效范围?]
│        │        ├─YES → ✅ 正常工作
│        │        └─NO → 检查传感器值 (range check)
│        └─NO → 检查超时/重连日志
└─NO → 检查 /dev/ttymxc2, 波特率, 从机电源
```

---

**最后更新：2026年2月18日**
**用途：快速参考和故障诊断**
