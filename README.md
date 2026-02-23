# BigFish - 大鱼吃小鱼

一个基于 Qt 5.12 开发的经典"大鱼吃小鱼"游戏，支持单人和双人模式。

## 游戏截图

![Game Preview](docs/screenshot.png)

## 功能特性

- **两种游戏模式**
  - 单人模式：使用 WASD 控制鱼的移动
  - 双人模式：P1 使用 WASD，P2 使用方向键

- **游戏机制**
  - 吃掉比自己体积小的鱼来成长
  - 碰到比自己体积大的鱼会失去一条命
  - 受伤后有 3 秒无敌时间（角色闪烁提示）
  - 初始 5 条命，生命值为 0 时游戏结束
  - 达到 78800 分成为"海上霸主"通关

- **完善的场景管理**
  - QStackedWidget 实现流畅场景切换
  - SceneManager 统一管理场景状态
  - 支持场景间自由切换（主界面 → 选择界面 → 游戏界面）

- **音频系统**
  - AudioManager 单例模式管理所有音频
  - Qt 5.12 兼容的 QMediaPlayer 实现
  - 背景音乐自动切换
  - 得分/扣血音效反馈

## 项目结构

```
BigFish/
├── main.cpp           # 程序入口
├── config.h           # 游戏配置常量
├── basescene.h/cpp    # 场景基类（生命周期钩子）
├── scenemanager.h/cpp # 场景管理器（场景切换）
├── audiomanager.h/cpp # 音频管理器（单例）
├── mainwindow.h/cpp   # 主窗口（QStackedWidget 容器）
├── startscene.h/cpp   # 启动场景（主界面）
├── choosescene.h/cpp  # 选择场景（单/双人）
├── playscene.h/cpp    # 游戏场景（核心逻辑）
├── player.h/cpp       # 玩家类（移动、碰撞）
├── fish.h/cpp         # 鱼类（8种等级）
├── res.qrc            # Qt 资源文件
└── BigFish.pro        # Qt 项目文件
```

## 编译说明

### 环境要求

- Qt 5.12 或更高版本
- Qt 模块：`core`, `gui`, `widgets`, `multimedia`, `multimediawidgets`
- C++11 或更高标准
- CMake 或 qmake

### 使用 Qt Creator 编译

1. 打开 Qt Creator
2. 文件 → 打开文件或项目
3. 选择 `BigFish.pro`
4. 配置项目（选择合适的 Kit）
5. 点击构建按钮（或按 `Ctrl+B`）

### 使用命令行编译

```bash
# 生成 Makefile
qmake BigFish.pro

# 编译
nmake    # Windows
make     # Linux/macOS
```

### 清理重新编译

如果遇到编译错误，建议清理后重新编译：

```bash
qmake
nmake clean
nmake
```

或在 Qt Creator 中：**Build** → **Clean All** → **Rebuild All**

## 游戏操作

### 单人模式

| 按键 | 功能 |
|------|------|
| W    | 向上移动 |
| S    | 向下移动 |
| A    | 向左移动 |
| D    | 向右移动 |
| ESC  | 暂停游戏 |

### 双人模式

| 按键 | 功能 |
|------|------|
| W    | P1 向上 |
| S    | P1 向下 |
| A    | P1 向左 |
| D    | P1 向右 |
| ↑    | P2 向上 |
| ↓    | P2 向下 |
| ←    | P2 向左 |
| →    | P2 向右 |
| ESC  | 暂停游戏 |

## 技术要点

### 场景管理架构

```
┌─────────────────────────────────────────────────────────────────┐
│                        MainWindow                                │
│  ┌───────────────────────────────────────────────────────────┐  │
│  │                   QStackedWidget                           │  │
│  │  ┌─────────────┐  ┌─────────────┐  ┌─────────────────────┐│  │
│  │  │StartScene   │  │ChooseScene  │  │     PlayScene       ││  │
│  │  └─────────────┘  └─────────────┘  └─────────────────────┘│  │
│  └───────────────────────────────────────────────────────────┘  │
│  ┌───────────────────────────────────────────────────────────┐  │
│  │              SceneManager (场景管理)                        │  │
│  └───────────────────────────────────────────────────────────┘  │
│  ┌───────────────────────────────────────────────────────────┐  │
│  │             AudioManager (音频单例)                         │  │
│  └───────────────────────────────────────────────────────────┘  │
└─────────────────────────────────────────────────────────────────┘
```

### 碰撞检测

使用椭圆碰撞检测算法（比矩形更精确）：

```cpp
QGraphicsEllipseItem ell1(x * 0.83, y * 0.83, wid * 0.71, hei * 0.71);
QGraphicsEllipseItem ell2(fish->X * 0.83, fish->Y * 0.83, fish->Wid * 0.71, fish->Hei * 0.71);
return ell1.collidesWithItem(&ell2, Qt::IntersectsItemShape);
```

### Qt 5.12 音频循环播放

Qt 5.12 没有 `setLoops()` 方法（Qt 6 才有），通过信号槽实现：

```cpp
connect(m_bgPlayer, &QMediaPlayer::mediaStatusChanged,
        this, &AudioManager::onBgMusicEnded);

void AudioManager::onBgMusicEnded() {
    if (m_bgPlayer->mediaStatus() == QMediaPlayer::EndOfMedia) {
        m_bgPlayer->play();  // 重新播放实现循环
    }
}
```

## 版本历史

### v2.0 (当前版本)

- 重构场景管理系统（QStackedWidget + SceneManager）
- 修复内存泄漏（PlayScene 不再重复创建）
- 更新音频系统（QMediaPlayer 替代已废弃的 QSound）
- 添加 3 秒无敌时间闪烁效果
- 支持场景间自由切换和返回

### v1.0 (原始版本)

- 基本游戏功能
- 单人和双人模式
- 8 种等级的鱼

## 许可证

MIT License

## 贡献

欢迎提交 Issue 和 Pull Request！

## 作者

Created with Qt 5.12
