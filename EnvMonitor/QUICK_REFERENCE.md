# 优化快速参考卡

## 关键变量新增

| 变量 | 类型 | 说明 |
|------|------|------|
| `data_cond` | `pthread_cond_t` | 条件变量，数据变化时信号 |
| `last_display_data` | `sensor_data_t` | 上次显示的数据 |
| `modbus_connection_status` | `volatile int` | 连接状态标志 |

## 新增函数

### validate_sensor_data()
```c
bool validate_sensor_data(const sensor_data_t *data);
```
- **功能**：验证传感器数据是否在有效范围内
- **返回**：true=有效，false=无效
- **调用位置**：Modbus线程中接收数据后

### sensor_data_changed()
```c
bool sensor_data_changed(const sensor_data_t *old, const sensor_data_t *new);
```
- **功能**：检测两个数据集是否有差异
- **返回**：true=有变化，false=相同
- **调用位置**：Modbus线程和LVGL显示函数中

### reconnect_modbus()
```c
void reconnect_modbus(void);
```
- **功能**：重新建立Modbus连接
- **调用位置**：连续失败时自动调用，或手动调用恢复

## 配置常量

```c
// 在custom.c中修改这些值
const int MAX_CONSECUTIVE_ERRORS = 5;       // 触发重连的失败次数
const int MODBUS_RECONNECT_DELAY = 3;       // 重连延迟(秒)

// 在modbus_read_thread()中修改
const int MAX_READ_FAILURES = 3;            // 单次失败阈值
timeout.tv_sec += 2;  // 条件变量等待超时(秒)

// 在custom_init()中修改
lv_timer_create(lvgl_update_timer, 1000, ui);  // 定时器频率(毫秒)
```

## 传感器数据范围

修改 `sensor_ranges` 结构以适应不同的硬件：

```c
static const sensor_range_t sensor_ranges = {
    .humi_min = 0,      .humi_max = 100,        // AHT10: 0-100%
    .light_min = 0,     .light_max = 65535,     // BH1750: 0-65535 lx
    .temp_min = -40,    .temp_max = 85,         // BMP280: -40~85°C
    .press_min = 300,   .press_max = 1100,      // BMP280: 300-1100 hPa
    .co2_min = 400,     .co2_max = 5000,        // SGP30: 400-5000 ppm
    .tvoc_min = 0,      .tvoc_max = 60000       // SGP30: 0-60000 ppb
};
```

## 调试日志说明

| 日志消息 | 含义 | 处理方式 |
|---------|------|--------|
| `Connected to Modbus slave` | 连接成功 | ✓ 正常 |
| `Sensor data updated (update_count: N)` | 数据更新 | ✓ 正常 |
| `Display updated` | 显示刷新 | ✓ 正常 |
| `Received invalid sensor data` | 数据验证失败 | ⚠ 检查传感器 |
| `Modbus read failed: ...` | 通信失败 | ⚠ 检查连接 |
| `Too many read failures, attempting to reconnect...` | 自动重连 | ℹ 正在恢复 |
| `Unable to create libmodbus context` | 初始化失败 | ✗ 致命错误 |
| `Connection failed: ...` | 连接失败 | ✗ 致命错误 |

## 集成检查清单

- [ ] 编译通过，无警告
- [ ] 链接了 `-lpthread` 和 `-lmodbus` 库
- [ ] 修改了 `sensor_ranges` 以匹配实际硬件
- [ ] 验证了Modbus波特率 (115200)
- [ ] 确认了串口设备路径 (`/dev/ttymxc2`)
- [ ] 观察到"Connected to Modbus slave"日志
- [ ] 观察到"Sensor data updated"日志
- [ ] 观察到"Display updated"日志
- [ ] CPU占用 < 20%
- [ ] 内存占用稳定

## 常见问题速查

### Q: 数据不更新
**A:** 检查日志：
- 无"Connected"消息 → Modbus连接失败
- 有"Modbus read failed" → 通信问题
- 有"Received invalid sensor data" → 范围设置不对

### Q: 频繁重连
**A:** 增加超时时间：
```c
modbus_set_response_timeout(modbus_ctx, 2, 0);  // 改为2秒
```

### Q: CPU占用仍高
**A:** 调整定时器：
```c
update_timer = lv_timer_create(lvgl_update_timer, 2000, ui);  // 改为2秒
```

### Q: 内存占用持续增加
**A:** 检查是否有内存泄漏：
- 确认 `pthread_detach()` 被调用
- 检查 `modbus_free()` 在关闭时被调用

## 性能基准

预期值（在IMX6ULL上）：
- CPU占用：10-20%
- 内存占用：< 5MB
- 响应延迟：< 500ms
- 更新频率：取决于数据变化，通常1-5Hz

## 向后兼容性

✓ 所有原有接口保留
✓ 新增功能为可选
✓ 不需修改GUI框架
✓ 不需修改其他模块

## 推荐阅读顺序

1. 本文件（快速了解）
2. `OPTIMIZATION_SUMMARY_ZH.txt`（概览）
3. `OPTIMIZATION_GUIDE.md`（详细说明）
4. `DETAILED_COMPARISON.md`（代码对比）
5. `custom.h` 和 `custom.c`（源代码）
