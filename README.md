# NoteBlade - VOCALOID 拆音工具

## 构建

此项目使用 [Xmake](https://xmake.io/) 构建，使用前请先安装 Xmake。

**Windows**

请前往 https://github.com/xmake-io/xmake/releases 下载最新版本的 xmake 并安装。

同时，您也需要安装 [Visual Studio 2022](https://visualstudio.microsoft.com/)。请确保您安装了以下工具链：
 - 桌面 C++ 工作负载
 - MSVC v143 生成工具
 - C++ ATL for v143
 - Windows 11 SDK

在 Windows 上，您需要切换到 MSVC 工具链：

```bash
# for Windows Only
xmake f --toolchain=msvc -a x86
```

然后，执行

```bash
xmake build
xmake build && xmake run # 构建并运行
xmake build && xmake run nodeblade <args>
```


**macOS**

使用 Homebrew 安装 Xmake：

```bash
brew install xmake
```

在 macOS 上，您需要切换到 clang 工具链：

```bash
# for macOS Only
xmake f --toolchain=clang
```

然后，执行

```bash
xmake build
xmake build && xmake run # 构建并运行
xmake build && xmake run nodeblade <args>
```

## 配置 VSCode

您需要配置 VSCode 才能使用。

请按照以下步骤配置：
 1. 在 VSCode 商店搜索 `XMake`，安装 `XMake` 插件。
 2. 创建 `.vscode/c_cpp_properties.json` 文件，内容如下：
     ```json
     {
         "configurations": [
             {
                 "name": "Xmake",
                 "compileCommands": ".vscode/compile_commands.json"
             }
         ],
         "version": 4
     }
     ```
  3. 按下快捷键 <kbd>Ctrl</kbd> + <kbd>Shift</kbd> + <kbd>P</kbd>，输入 `xmake update intellisense`，选择 `Xmake: UpdateIntellisense`。

此后，如果 VSCode 对依赖报错，请重复第 3 步。

## API
### Class `VSQXReader`
**原型**
```cpp
NoteBlade::VSQXReader(std::string path)
```
VSQX 读取器类 `VSQXReader` 的构造函数。

**参数**
| Parameter | Type          | Description |
| --------- | ------------- | ----------- |
| `path`    | `std::string` | VSQX 文件路径 |

### Method `VSQXReader::project`
**原型**
```cpp
NoteBlade::VSQXProject NoteBlade::VSQXReader::project()
```

返回一个 `VSQXProject` 对象，包含了 VSQX 的部分信息。

**返回值**
| Type                     | Description   |
| ------------------------ | ------------- |
| `NoteBlade::VSQXProject` | VSQX 工程对象  |

**异常**
| Exception                 | Description       |
| ------------------------- | ----------------- |
| `std::runtime_error`      | 无法打开 VSQX 文件 (在异常 `message` 中为 `ERR_XML_FILE_NOT_FOUND`) |
| `std::runtime_error`      | 解析 XML 文件出错 (在异常 `message` 中为 `ERR_XML_READ_VALUE`) |

### Method `*::display`
```cpp
void NoteBlade::VSQXProject::display()
void NoteBlade::VSQXSinger::display()
void NoteBlade::VSQXTrack::display()
void NoteBlade::VSQXPart::display()
void NoteBlade::VSQXNote::display()
```

打印对象的信息，用于调试。

### Method `VSQXProject::pre_measure`
**原型**
```cpp
VSQXUInt NoteBlade::VSQXProject::pre_measure()
```

返回 VSQX 工程在第 1 小节前的小节数。VOCALOID 默认值为 4。

VSQX 工程从第 1 小节开始，可以为虚拟歌手放置音轨。在第 1 小节之前，还有预小节，从**右**向**左**依次编号：0、-1、-2、……

假如 `pre_measure` 为 6，则在第 1 小节之前，还有 6 个预小节，编号为 0、-1、-2、-3、-4、-5。

可链式调用，如 `reader.project().pre_measure()`。

**返回值**
| Type       | Description |
| ---------- | ----------- |
| `VSQXUInt` | 预小节数    |

 - 注：`VSQXUInt` 为 `std::uint64_t` 的别名，在 x86_64 或 arm64 平台上，即为 `unsigned long long`。

### Method `VSQXProject::tick`
```cpp
VSQXUInt NoteBlade::VSQXProject::tick(VSQXUInt beat)
```

将拍子数转换为 tick 数。

`tick = beat * tick_per_beat`。

`tick_per_beat` 可能在不同工程文件中为不同值。尽管 99% 的 VSQX 文件，`tick_per_beat` 都为 480，但仍建议使用此方法进行转换。

可链式调用，如 `reader.project().tick(50)`。

**参数**
| Parameter | Type          | Description |
| --------- | ------------- | ----------- |
| `beat`    | `VSQXUInt`    | 拍子数      |

**返回值**
| Type       | Description       |
| ---------- | ----------------- |
| `VSQXUInt` | 拍子数对应的 tick 数 |

 - 注：`VSQXUInt` 为 `std::uint64_t` 的别名，在 x86_64 或 arm64 平台上，即为 `unsigned long long`。

### Method `VSQXProject::tick_per_beat`
```cpp
VSQXUInt NoteBlade::VSQXProject::tick_per_beat()
```

返回每个拍子的 tick 数。VOCALOID 默认为 480。

例如一个音符从 480 开始，时值为 960，则其实际拍子位置为 `480 / 480 = 1` 拍，时值为 `960 / 480 = 2` 拍。

`tick_per_beat` 可能在不同工程文件中为不同值。尽管 99% 的 VSQX 文件，`tick_per_beat` 都为 480，但仍建议使用此方法进行转换。

可链式调用，如 `reader.project().tick_per_beat()`。

**返回值**
| Type       | Description |
| ---------- | ----------- |
| `VSQXUInt` | 每拍的 tick 数 |

 - 注：`VSQXUInt` 为 `std::uint64_t` 的别名，在 x86_64 或 arm64 平台上，即为 `unsigned long long`。

### Method `VSQXProject::time_signture_numerator`
```cpp
VSQXUInt NoteBlade::VSQXProject::time_signture_numerator()
```

返回每小节的拍子数，即拍号的分子部分。VOCALOID 默认值为 4。

例如 4/4 拍号，每小节 4 拍，则 `time_signture_numerator` 为 4。6/8 拍号，每小节 6 拍，则 `time_signture_numerator` 为 6。

可链式调用，如 `reader.project().time_signture_numerator()`。

**返回值**
| Type       | Description |
| ---------- | ----------- |
| `VSQXUInt` | 每小节的拍子数 |

 - 注：`VSQXUInt` 为 `std::uint64_t` 的别名，在 x86_64 或 arm64 平台上，即为 `unsigned long long`。

### Method `VSQXProject::time_signture_denominator`
```cpp
VSQXUInt NoteBlade::VSQXProject::time_signture_denominator()
```

返回几分音符为一拍，即拍号的分母部分。VOCALOID 默认值为 4。

例如 4/4 拍号，四分音符为一拍，则 `time_signture_denominator` 为 4。6/8 拍号，八分音符为一拍，则 `time_signture_denominator` 为 8。

可链式调用，如 `reader.project().time_signture_denominator()`。

**返回值**
| Type       | Description |
| ---------- | ----------- |
| `VSQXUInt` | 几分音符为一拍 |

 - 注：`VSQXUInt` 为 `std::uint64_t` 的别名，在 x86_64 或 arm64 平台上，即为 `unsigned long long`。

### Method `VSQXProject::singers`
```cpp
std::vector<VSQXSinger> NoteBlade::VSQXProject::singers()
```

返回一个包含所有歌手信息的 Vector。

可链式调用，如 `reader.project().singers()`。

**返回值**
| Type                      | Description |
| ------------------------- | ----------- |
| `std::vector<VSQXSinger>` | 歌手信息的 Vector |

### Method `VSQXProject::tracks`
```cpp
std::vector<VSQXTrack> NoteBlade::VSQXProject::tracks()
```

返回一个包含所有人声轨道的 Vector。

**注意：仅包含虚拟歌手轨，不包含伴奏轨。**

可链式调用，如 `reader.project().tracks()`。

**返回值**
| Type                      | Description |
| ------------------------- | ----------- |
| `std::vector<VSQXTrack>`  | 轨道信息的 Vector |

### Method `VSQXProject::singers_size`
```cpp
VSQXUInt NoteBlade::VSQXProject::singers_size()
```

返回工程歌手表中的数量。

暂时不知道歌手表中的数量是否等于实际使用的数量。

可链式调用，如 `reader.project().singers_size()`。

**返回值**
| Type                      | Description |
| ------------------------- | ----------- |
| `VSQXUInt`                | 歌手表中的数量 |

 - 注：`VSQXUInt` 为 `std::uint64_t` 的别名，在 x86_64 或 arm64 平台上，即为 `unsigned long long`。

### Method `VSQXProject::tracks_size`
```cpp
std::vector<VSQXTrack> NoteBlade::VSQXProject::tracks_size()
```

返回工程中人声（虚拟歌手）轨的数量。

**注意：仅包含虚拟歌手轨，不包含伴奏轨。**

可链式调用，如 `reader.project().singers_size()`。

**返回值**
| Type                      | Description |
| ------------------------- | ----------- |
| `std::vector<VSQXTrack>`  | 轨道信息的 Vector |

### Method `VSQXProject::singer`
```cpp
VSQXSinger NoteBlade::VSQXProject::singer(VSQXUInt index)
```

返回歌手表中指定索引的歌手信息。

**注意：此函数返回的是从 0 开始的索引，而不是 VSQX 文件中的歌手编号 (pc 值)。要根据歌手编号获取歌手，请使用 `VSQXSinger::singer_no`。**

例如歌手列表如下：

| Index | Singer No (pc) | Singer Name |
| ----- | -------------- | ----------- |
| 0     | 3              | MikuV4C     |
| 1     | 9              | Tianyi_CHN  |

则 `reader.project().singer(0)` 返回的是 MikuV4C 的信息，`reader.project().singer(1)` 返回的是 Tianyi_CHN 的信息。传入 `3` 或 `9` 会抛出 `std::out_of_range` 异常。

可链式调用，如 `reader.project().singer(0)`。

**参数**
| Parameter | Type          | Description |
| --------- | ------------- | ----------- |
| `index`   | `VSQXUInt`    | 索引        |

**返回值**
| Type                      | Description |
| ------------------------- | ----------- |
| `VSQXSinger`              | 歌手信息    |

**异常**
| Exception                 | Description       |
| ------------------------- | ----------------- |
| `std::out_of_range`       | 找不到索引对应的歌手 |

### Method `VSQXProject::singer_no`
```cpp
VSQXSinger NoteBlade::VSQXProject::singer_no(VSQXUInt number)
```

返回歌手表中指定**歌手编号**的歌手信息。

**注意：是 VSQX 文件中的歌手编号 (pc 值)。要获取 vecotr 中的第 i 个歌手，请使用 `VSQXSinger::singer`。**

例如歌手列表如下：

| Index | Singer No (pc) | Singer Name |
| ----- | -------------- | ----------- |
| 0     | 3              | MikuV4C     |
| 1     | 9              | Tianyi_CHN  |

则 `reader.project().singer(3)` 返回的是 MikuV4C 的信息，`reader.project().singer(9)` 返回的是 Tianyi_CHN 的信息。传入 `0` 或 `1` 会抛出 `std::out_of_range` 异常。

可链式调用，如 `reader.project().singer_no(3)`。

**参数**
| Parameter | Type          | Description |
| --------- | ------------- | ----------- |
| `number`  | `VSQXUInt`    | 歌手编号    |

**返回值**
| Type                      | Description |
| ------------------------- | ----------- |
| `VSQXSinger`              | 歌手信息    |

**异常**
| Exception                 | Description       |
| ------------------------- | ----------------- |
| `std::out_of_range`       | 找不到编号对应的歌手 |

### Method `VSQXProject::track`
```cpp
VSQSTrack NoteBlade::VSQXProject::track(VSQXUInt index)
```

返回指定索引的轨道信息。

**注意：此函数返回的是从 0 开始的索引，而不是 VSQX 文件中的轨道编号。要根据轨道编号获取轨道，请使用 `VSQXSinger::track_no`。**

例如轨道列表如下：

| Index | Track No (tNo) | Displayed in VOCALOID as | Name |
| ----- | -------------- | ------------------------ | ---- |
| 0     | 6              | 1                        | 主   |
| 1     | 7              | 2                        | 和声 |

则 `reader.project().track(0)` 返回的是 `主` 轨道，`reader.project().track(1)` 返回 `和声` 轨道。传入 `6` 或 `7` 会抛出 `std::out_of_range` 异常。

**注意：Index、Track No 从 0 开始计数，但是显示在 VOCALOID 中的轨道编号从 1 开始计数。**

可链式调用，如 `reader.project().track(0)`。

**参数**
| Parameter | Type          | Description |
| --------- | ------------- | ----------- |
| `index`   | `VSQXUInt`    | 索引        |

**返回值**
| Type                      | Description |
| ------------------------- | ----------- |
| `VSQSTrack`               | 轨道信息    |

**异常**
| Exception                 | Description       |
| ------------------------- | ----------------- |
| `std::out_of_range`       | 找不到索引对应的轨道 |

### Method `VSQXProject::track_no`
```cpp
VSQSTrack NoteBlade::VSQXProject::track_no(VSQXUInt number)
```

返回指定**轨道编号**的轨道信息。

**注意：此函数的入参是 VSQX 文件中的轨道编号 (`tNo`)。要获取 vecotr 中的第 i 个轨道，请使用 `VSQXSinger::track`。**

例如轨道列表如下：

| Index | Track No (tNo) | Displayed in VOCALOID as | Name |
| ----- | -------------- | ------------------------ | ---- |
| 0     | 6              | 1                        | 主   |
| 1     | 7              | 2                        | 和声 |

则 `reader.project().track(6)` 返回的是 `主` 轨道，`reader.project().track(7)` 返回 `和声` 轨道。传入 `0` 或 `1` 会抛出 `std::out_of_range` 异常。

**注意：Index、Track No 从 0 开始计数，但是显示在 VOCALOID 中的轨道编号从 1 开始计数。**

可链式调用，如 `reader.project().track_no(6)`。

**参数**
| Parameter | Type          | Description |
| --------- | ------------- | ----------- |
| `number`  | `VSQXUInt`    | 轨道编号    |

**返回值**
| Type                      | Description |
| ------------------------- | ----------- |
| `VSQSTrack`               | 轨道信息    |

**异常**
| Exception                 | Description       |
| ------------------------- | ----------------- |
| `std::out_of_range`       | 找不到编号对应的轨道 |

### Method `VSQXProject::signer_ids`
```cpp
std::vector<VSQXUInt> NoteBlade::VSQXProject::signer_ids()
```

返回所有歌手的歌手编号 (`pc`) 的 Vector。

例如歌手列表如下：

| Index | Singer No (pc) | Singer Name |
| ----- | -------------- | ----------- |
| 0     | 3              | MikuV4C     |
| 1     | 9              | Tianyi_CHN  |

该函数会返回 `std::vector<VSQXUInt>{3, 9}`。

可链式调用，如 `reader.project().signer_ids()`。

**返回值**
| Type                      | Description |
| ------------------------- | ----------- |
| `std::vector<VSQXUInt>`   | 所有歌手的歌手编号 (`pc`) 的 Vector |

### Method `VSQXProject::track_ids`
```cpp
std::vector<VSQXUInt> NoteBlade::VSQXProject::track_ids()
```

返回所有轨道的轨道编号 (`tNo`) 的 Vector。

例如轨道列表如下：

| Index | Track No (tNo) | Displayed in VOCALOID as | Name |
| ----- | -------------- | ------------------------ | ---- |
| 0     | 6              | 1                        | 主   |
| 1     | 7              | 2                        | 和声 |

该函数会返回 `std::vector<VSQXUInt>{6, 7}`。

**注意：Index、Track No 从 0 开始计数，但是显示在 VOCALOID 中的轨道编号从 1 开始计数。**

可链式调用，如 `reader.project().track_ids()`。

**返回值**
| Type                      | Description |
| ------------------------- | ----------- |
| `std::vector<VSQXUInt>`   | 所有轨道的轨道编号 (`tNo`) 的 Vector |

### Method `VSQXSinger::number`
```cpp
VSQXUInt NoteBlade::VSQXSinger::number()
```

返回歌手的 `vVoiceTable` 编号，即 `pc` 值。

**注意：同一个虚拟歌手在不同计算机上的 VOCALOID 中，`pc` 值可能不同。请总是根据不同工程文件中的 `pc` 值来获取歌手。**

可链式调用，如 `reader.project().singer(0).number()`。

**返回值**
| Type                      | Description |
| ------------------------- | ----------- |
| `VSQXUInt`                | 歌手的 `pc` 值 |

 - 注：`VSQXUInt` 为 `std::uint64_t` 的别名，在 x86_64 或 arm64 平台上，即为 `unsigned long long`。

### Method `VSQXSinger::name`
```cpp
std::string NoteBlade::VSQXSinger::name()
```

返回歌手的名称。

**注意：此函数返回的既不是歌手的中文名称（如「洛天依」、「初音未来」），也不是歌手的 Product ID (如 `BEY8C2TZLDXHZECF`)，而是歌手的默认 Name ID （如 `Tianyi_CNH`、`Luotianyi_CHN_Meng`）。**

**注意：该值可以在 VOCALOID 中修改。**

可链式调用，如 `reader.project().singer(0).name()`。

**返回值**
| Type                      | Description |
| ------------------------- | ----------- |
| `std::string`             | 歌手名称    |

### Method `VSQXSinger::id`
```cpp
std::string NoteBlade::VSQXSinger::id()
```

返回声库的 ID。

**注意：此函数返回的既不是歌手的中文名称（如「洛天依」、「初音未来」），也不是歌手的 Name ID （如 `Tianyi_CNH`、`Luotianyi_CHN_Meng`）,而是歌手的 Product ID (如 `BEY8C2TZLDXHZECF`)。**

**注意：该值在所有 VOCALOID 声库中唯一，可以唯一地确定一个声库。同一歌手的不同声库、不同版本（如「洛天依·萌」「洛天依·凝」「洛天依V3」）的 ID 不同。**

可链式调用，如 `reader.project().singer(0).id()`。

**返回值**
| Type                      | Description |
| ------------------------- | ----------- |
| `std::string`             | 声库 ID     |

### Method `VSQXTrack::number`
```cpp
VSQXUInt NoteBlade::VSQXTrack::number()
```

返回轨道编号，即 `tNo` 值。

**注意：Index、Track No 从 0 开始计数，但是显示在 VOCALOID 中的轨道编号从 1 开始计数。**

可链式调用，如 `reader.project().track(0).number()`。

**返回值**
| Type                      | Description |
| ------------------------- | ----------- |
| `VSQXUInt`                | 轨道编号    |

 - 注：`VSQXUInt` 为 `std::uint64_t` 的别名，在 x86_64 或 arm64 平台上，即为 `unsigned long long`。

### Method `VSQXTrack::name`
```cpp
std::string NoteBlade::VSQXTrack::name()
```

返回的轨道名称。

该名称是由作者输入的，**可能存在重复。**

可链式调用，如 `reader.project().track(0).name()`。

**返回值**
| Type                      | Description |
| ------------------------- | ----------- |
| `std::string`             | 轨道名称    |

### Method `VSQXTrack::parts`
```cpp
std::vector<VSQXPart> NoteBlade::VSQXTrack::parts()
```

返回一个 Vector，包含了轨道中的 Part。

可链式调用，如 `reader.project().track(0).parts()`。

**返回值**
| Type                      | Description |
| ------------------------- | ----------- |
| `std::vector<VSQXPart>`   | 轨道中所有的 Part |

### Method `VSQXTrack::parts_size`
```cpp
VSQXUInt NoteBlade::VSQXTrack::parts_size()
```

返回轨道中的 Part 数量。

可链式调用，如 `reader.project().track(0).parts_size()`。

**返回值**
| Type                      | Description |
| ------------------------- | ----------- |
| `VSQXUInt`                | Part 数量   |

 - 注：`VSQXUInt` 为 `std::uint64_t` 的别名，在 x86_64 或 arm64 平台上，即为 `unsigned long long`。

### Method `VSQXTrack::part`
```cpp
VSQXPart NoteBlade::VSQXTrack::part(VSQXUInt index)
```

返回轨道中指定索引的 Part。从 0 开始计数。

可链式调用，如 `reader.project().track(0).part(0)`。

**参数**
| Parameter | Type          | Description |
| --------- | ------------- | ----------- |
| `index`   | `VSQXUInt`    | 索引        |

**返回值**
| Type                      | Description |
| ------------------------- | ----------- |
| `VSQXPart`                | 指定索引的 Part |

**异常**
| Exception                 | Description       |
| ------------------------- | ----------------- |
| `std::out_of_range`       | 索引超出范围        |

### Method `VSQXPart::start_tick`
```cpp
VSQXUInt NoteBlade::VSQXPart::start_tick()
```

Part 开始的 tick 数。从第 1 小节（即不包含 `pre_measure` 的小节）开始计数。

可链式调用，如 `reader.project().track(0).part(0).start_tick()`。

**返回值**
| Type                      | Description |
| ------------------------- | ----------- |
| `VSQXUInt`                | 开始的 tick |

 - 注：`VSQXUInt` 为 `std::uint64_t` 的别名，在 x86_64 或 arm64 平台上，即为 `unsigned long long`。

### Method `VSQXPart::notes_size`
```cpp
VSQXUInt NoteBlade::VSQXPart::notes_size()
```

Part 中的音符数量。**包含重叠音符。**

可链式调用，如 `reader.project().track(0).part(0).notes_size()`。

**返回值**
| Type                      | Description |
| ------------------------- | ----------- |
| `VSQXUInt`                | 音符数量    |

 - 注：`VSQXUInt` 为 `std::uint64_t` 的别名，在 x86_64 或 arm64 平台上，即为 `unsigned long long`。

### Method `VSQXPart::notes`
```cpp
std::vector<VSQXNote> NoteBlade::VSQXPart::notes()
```

返回一个包含 Part 中所有音符的 Vector。**包含重叠音符。**

可链式调用，如 `reader.project().track(0).part(0).notes()`。

**返回值**
| Type                      | Description |
| ------------------------- | ----------- |
| `std::vector<VSQXNote>`   | 所有音符的 Vector |

### Method `VSQXPart::note`
```cpp
VSQXNote NoteBlade::VSQXPart::note(VSQXUInt index)
```

返回 Part 中指定索引的音符。**包含重叠音符。**

可链式调用，如 `reader.project().track(0).part(0).note(0)`。

**参数**
| Parameter | Type          | Description |
| --------- | ------------- | ----------- |
| `index`   | `VSQXUInt`    | 索引        |

**返回值**
| Type                      | Description |
| ------------------------- | ----------- |
| `VSQXNote`                | 指定索引的音符 |

**异常**
| Exception                 | Description       |
| ------------------------- | ----------------- |
| `std::out_of_range`       | 索引超出范围        |

### Method `VSQXNote::start_tick`
```cpp
VSQXUInt NoteBlade::VSQXNote::start_tick()
```

返回相对于 part 开始的音符开始 tick 数。

例如，part 开始于 `t = 480`，音符开始于 `t = 960`，则 `start_tick` 为 `960 + 480 = 1440`。

**返回值**
| Type                      | Description |
| ------------------------- | ----------- |
| `VSQXUInt`                | 开始的 tick |

 - 注：`VSQXUInt` 为 `std::uint64_t` 的别名，在 x86_64 或 arm64 平台上，即为 `unsigned long long`。

### Method `VSQXNote::duration_tick`
```cpp
VSQXUInt NoteBlade::VSQXNote::duration_tick()
```

返回音符的时值，单位为 tick。

**返回值**
| Type                      | Description |
| ------------------------- | ----------- |
| `VSQXUInt`                | 时值        |

 - 注：`VSQXUInt` 为 `std::uint64_t` 的别名，在 x86_64 或 arm64 平台上，即为 `unsigned long long`。

### Method `VSQXNote::pitch`
```cpp
VSQXNotePitch NoteBlade::VSQXNote::pitch()
```

返回音符的音高。

音高是从 `C-2 = 0` 开始，每增加一个半音，音高加 1。`C3 = 60`。

可以使用 `NoteBlade::VSQXNotePitchName[pitch]` 来获取音高的名称。

**返回值**
| Type                      | Description |
| ------------------------- | ----------- |
| `VSQXNotePitch`           | 音高        |

### Method `VSQXNote::pitch_name`
```cpp
std::string NoteBlade::VSQXNote::pitch_name()
```

返回音符的音高名称，例如 `A2`、`F#4`、`Eb-2`。

升降记号的调性与 VOCALOID 4 编辑器一致。

字典使用相同此表记方式。

**返回值**
| Type                      | Description |
| ------------------------- | ----------- |
| `std::string`             | 音高名称    |

### Method `VSQXNote::xsampa_locked`
```cpp
bool NoteBlade::VSQXNote::xsampa_locked()
```

是否锁定音素。

如果锁定，无论歌词如何改变，始终使用 X-SAMPA 音素。

**返回值**
| Type                      | Description |
| ------------------------- | ----------- |
| `bool`                    | 是否锁定音素 |

### Method `VSQXNote::xsampa_locked`
```cpp
std::string NoteBlade::VSQXNote::xsampa()
```

音符的音素，即 X-SAMPA 音标。

**返回值**
| Type                      | Description |
| ------------------------- | ----------- |
| `std::string`             | X-SAMPA 音标 |

### Method `VSQXNote::lyric`
```cpp
std::string NoteBlade::VSQXNote::lyric()
```

音符的歌词。其可能根据不同声库语言而不同，例如中文声库为拼音，日文声库为罗马音。

如果 `xsampa_locked()` 为 `true`，则 `lyric` 会被忽略。此时不要使用此函数的返回值。

**返回值**
| Type                      | Description |
| ------------------------- | ----------- |
| `std::string`             | 音符的歌词  |

### Method `VSQXNote::pronunciation`
```cpp
std::string NoteBlade::VSQXNote::pronunciation()
```

音符实际的发音。可能是拼音、罗马音、X-SAMPA 音标或其他格式。

如果 `xsampa_locked()` 为 `true`，则 `pronunciation` 为 `xsampa()` 的返回值，否则为 `lyric()` 的返回值。

**返回值**
| Type                      | Description |
| ------------------------- | ----------- |
| `std::string`             | 音符的发音  |
