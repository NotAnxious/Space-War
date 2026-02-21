#Space-War

## 📖 项目简介
此项目是一个想要还原远古的space-war游戏，是一个vs里的控制台程序(C++)。

## 📁 项目结构

```
Space-War             # 项目文件夹
├── .git/             # git文件夹
├── .vs/              # vscode文件夹
├── .vscode/          # 也是vscode文件夹¿
├── Space-War/        # 解决方案
│   ├── Space-War.vcxproj.user # 用户特定配置文件
│   ├── Space-War.vcxproj.filters # 项目配制文件
│   ├── Space-War.vcxproj # 项目配制文件
│   ├── x64/
│   └── src/          # 代码文件
│       ├── include/   # 依赖库
│       │  ├── GLFW/  # GLFW库
│       │  ├── glm/   # glm库
│       │  ├── opencv2/ # opencv库
│       │  ├── SOIL2/ # SOIL2库
│       │  ├── spdlog/ # spdlog库
│       │  ├── glad.h # glad库
│       │  └── khrplatform.h
│       ├── lib/      # lib链接库
│       ├── bullet.h  # 关于子弹的函数
│       ├── ene.h     # 关于敌方飞船的函数
│       ├── glad.c    # glad函数的实现
│       ├── image.h   # 前端函数
│       ├── main.cpp  # 主程序
│       ├── main.h    # 杂七杂八的函数
│       ├── resource.h # Microsoft Visual C++ 生成的包含文件
│       └── ship.h    # 关于我方飞船的函数
├── x64/debug/        # 编译结果
│   ├── png/          # 素材
│   ├── Space-War.ilk
│   ├── Space-War.pdb
│   ├── Space-War.log
│   ├── Space-War.exe # 应用程序
│   ├── glew32.dll
│   ├── glfw3.dll
│   ├── opencv_videoio_ffmpeg4120_64.dll
│   ├── opencv_world4120.dll
│   └── opencv_world4120d.dll
├── .gitattributes    # 大文件追踪
├── README.md         # 你正在的看这个
└── Space-War.slnx    # 解决方案文件
```

## 🧪 开发指南
💾 克隆仓库
```
git clone https://github.com/NotAnxious/Space-War.git
```

📀 项目依赖
这个项目依赖 glew,glad,GLFW,glm,json,opencv2,SOIL2,spdlog。





