# NoteBlade - VOCALOID 拆音工具

<p align="center">
    <a href="docs/API.md">API 文档</a> |
    <a href="docs/vsqx-illustrated.md">图解 VSQX</a> |
    <a href="docs/MANUAL.md">字典制作手册</a>
</p>

## 构建
### 工具链要求
#### Windows
 - [Xmake](https://xmake.io/): 请在 https://github.com/xmake-io/xmake/releases 下载最新版本的 xmake 并安装。
 - [Visual Studio 2022](https://visualstudio.microsoft.com/): 您并不需要安装完整的 Visual Studio 2022，只需要 MSVC 编译器即可。请确保您安装了以下工具链：
   - 桌面 C++ 工作负载
   - MSVC v143 生成工具
   - C++ ATL for v143
   - Windows 11 SDK

#### macOS
使用 Homebrew 安装 Xmake：
```bash
brew install xmake
```

### 构建
请先切换到 `release` 构建模式：
```bash
xmake f -m release
```

然后执行构建命令：
```bash
xmake build
```
该命令会自动下载依赖、选择合适的工具链并构建。

### 故障排除
若 Xmake 运行报错，请添加参数 `-v` 以获得更详细的日志。例如：
```bash
xmake build -v
```

#### 清除缓存
部分错误是由于构建缓存引起。您可以尝试清除缓存，注意清除缓存会清空您下载的所有依赖和当前 xmake 工作模式。
```bash
# Windows
rd /S /Q .xmake %USERPROFILE%\AppData\Local\Temp\.xmake %USERPROFILE%\AppData\Local\.xmake

# macOS
rm -rf .xmake ~/.xmake
```

#### SSL 错误
若您处于中国大陆，出现此错误请使用代理下载依赖。请在重新下载依赖前使用前文所述方法清除缓存。

设置代理，以代理端口在 7890 为例：

```shell
# Windows
set http_proxy=http://127.0.0.1:7890
set https_proxy=http://127.0.0.1:7890
xmake build

# macOS
export http_proxy=http://127.0.0.1:7890
export https_proxy=http://127.0.0.1:7890
xmake build
```

## 参与开发
### IDE 集成
#### Visual Studio Code
如果您使用 Visual Studio Code，您需要安装以下插件：
 - [Xmake VSCode](https://marketplace.visualstudio.com/items?itemName=tboox.xmake-vscode)

**请注意：该插件仅在安装了 [Xmake](https://xmake.io/) 的情况下才能正常工作。**

如果 VSCode 对依赖报错，请按下快捷键 <kbd>Ctrl</kbd> + <kbd>Shift</kbd> + <kbd>P</kbd>，选择 `Xmake: UpdateIntellisense`。

#### CLion
请安装 [XMake](https://plugins.jetbrains.com/plugin/10156-xmake) 插件。

### 调试
安装了 Xmake VSCode 插件后，即可使用 VSCode 原生调试工具。如果多个调试工具可以选择，请确保选择 `xmake`。

在 macOS 上，也可使用 LLVM Debug 工具调试：
```bash
xmake build && xmake run -d
```
