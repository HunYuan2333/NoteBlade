# NoteBlade - VOCALOID 拆音工具

<p align="center">
    <a href="docs/API.md">API 文档</a> |
    <a href="docs/vsqx-illustrated.md">图解 VSQX</a> |
    <a href="docs/MANUAL.md">字典制作手册</a>
</p>

## 构建
### Windows 下的依赖安装

Windows 下需要以下依赖：
 - [Xmake](https://xmake.io/): 请在 https://github.com/xmake-io/xmake/releases 下载最新版本的 xmake 并安装。
 - [Visual Studio 2022](https://visualstudio.microsoft.com/): 您并不需要安装完整的 Visual Studio 2022，只需要 MSVC 编译器即可。请确保您安装了以下工具链：
   - 桌面 C++ 工作负载
   - MSVC v143 生成工具
   - C++ ATL for v143
   - Windows 11 SDK

### macOS 下的依赖安装

使用 Homebrew 安装 Xmake：

```bash
brew install xmake
```

#### Visual Studio Code 支持

如果您使用 Visual Studio Code，您需要安装以下插件：
 - [Xmake VSCode](https://marketplace.visualstudio.com/items?itemName=tboox.xmake-vscode)

**请注意：该插件仅在安装了 [Xmake](https://xmake.io/) 的情况下才能正常工作。**

如果 VSCode 对依赖报错，请按下快捷键 <kbd>Ctrl</kbd> + <kbd>Shift</kbd> + <kbd>P</kbd>，选择 `Xmake: UpdateIntellisense`。

安装了 Xmake VSCode 插件后，即可使用 VSCode 原生调试工具。如果多个调试工具可以选择，请确保选择 `xmake`。

### 构建

```bash
xmake build
xmake build && xmake run

# 如需带参数运行，请使用
xmake build && xmake run nodeblade <args>

# 例如
xmake build && xmake run nodeblade --version
```

在 macOS 上，也可使用 LLVM Debug 工具调试：
```bash
xmake build && xmake run -d
```
