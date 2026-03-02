# 🚀 Space War

一个基于 OpenGL 的太空战争游戏，具有飞船控制、敌人生成和碰撞检测等功能。

## ⭐ 项目特点

- 🎮 流畅的飞船控制
- 👾 随机生成的敌方飞船
- 💥 碰撞检测系统
- 🎯 射击机制
- 📱 响应式窗口大小
- 🌌 太空背景效果

## 💻 技术栈

- **图形库**：OpenGL (GLEW, GLAD, GLFW)
- **数学库**：GLM
- **图像处理**：OpenCV
- **纹理加载**：SOIL2
- **日志系统**：spdlog
- **配置文件**：JSON

## 📋 系统要求

- Windows 10/11
- Visual Studio 2019 或更高版本
- C++17 支持
- 支持 OpenGL 3.3 或更高版本的显卡

## 📦 安装步骤

### 1. 克隆项目

```bash
git clone https://github.com/NotAnxious/Space-War.git
cd Space-War
```

### 2. 安装依赖

项目依赖以下库：
- GLEW
- GLAD
- GLFW
- GLM
- JSON
- OpenCV 2
- SOIL2
- spdlog

### 3. 编译项目

使用 Visual Studio 打开解决方案文件：

```
Space-War.sln
```

选择 Release 配置，然后构建项目。

## 🎮 游戏控制

| 按键 | 功能 |
|------|------|
| A/D | 飞船移动 |
| 空格键 | 射击 |
| ESC | 退出游戏 |

## ⚙️ 游戏机制

### 敌人系统
- 每秒钟有 50% 的概率生成敌方飞船
- 敌方飞船从屏幕顶部向下移动
- 当敌方飞船飞出屏幕底部时会被自动删除

### 碰撞检测
- 玩家飞船与敌方飞船的碰撞
- 子弹与敌方飞船的碰撞

## 📁 项目结构

```
Space-War/
├── src/                 # 源代码
│   ├── main.cpp         # 主入口
│   ├── ship.h           # 玩家飞船头文件
│   ├── ene.h            # 敌方飞船头文件
│   └──  bullet.h         # 子弹头文件
├── README.md            # 你正在阅读的文件
└── Space-War.sln        # Visual Studio 解决方案
```

## ▶️ 运行游戏

编译完成后，运行生成的可执行文件：

```bash
# 在 Release 目录下
Space-War.exe
```

## 🌟 未来计划

- [ ] 添加音效系统
- [ ] 实现游戏菜单
- [ ] 添加多种敌人类型
- [ ] 实现关卡系统
- [ ] 添加计分系统
- [ ] 优化性能

## 📄 许可证

本项目采用 MIT 许可证。详见 LICENSE 文件。

## 🤝 贡献
我们欢迎所有形式的贡献，包括但不限于：

- 报告 bug
- 建议新功能
- 提交代码改进
- 完善文档
- 翻译文档（如果有需要）
- 绘制素材

### 贡献流程

1. Fork 本项目
2. 创建新分支 (`git checkout -b feature/AmazingFeature`)
3. 提交更改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 打开 Pull Request

### 贡献注意事项

- 请确保代码符合项目的编码规范
- 代码样式请参考C++官方样式
- 更新 README.md 中的相关内容
- 提交前请运行测试

## 📧 联系作者

- GitHub: [NotAnxious](https://github.com/NotAnxious)
- Email: jinlu920@163.com

##  🙏 鸣谢

- [GLFW](https://www.glfw.org/) - 用于创建窗口和处理输入
- [GLEW](http://glew.sourceforge.net/) - 用于加载 OpenGL 扩展
- [GLAD](https://glad.dav1d.de/) - 用于加载 OpenGL 函数指针
- [GLM](https://glm.g-truc.net/0.9.9/index.html) - 用于数学计算
- [JSON](https://github.com/nlohmann/json) - 用于配置文件解析
- [OpenCV](https://opencv.org/) - 用于图像处理
- [SOIL2](https://github.com/soil2/soil2) - 用于加载纹理
- [spdlog](https://github.com/gabime/spdlog) - 用于日志记录
- [Visual Studio](https://visualstudio.microsoft.com/) - 用于开发环境
- [Trae CN](https://www.trae.cn/) - 帮我修了好多BUG

## ⚠️ 注意事项
部分图片素材来源于AI生成，仅供学习和参考。

---
make with NotAnxious
如果觉得项目有用，请给个 🌟 吧！