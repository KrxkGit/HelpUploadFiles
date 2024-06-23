# 🍕HelpUploadFiles

 ![GitHub license](https://img.shields.io/github/license/KrxkGit/HelpUploadFiles) ![GitHub last commit](https://img.shields.io/github/last-commit/KrxkGit/HelpUploadFiles/dev) [![GitHub stars](https://img.shields.io/github/stars/KrxkGit/HelpUploadFiles.svg?style=social)](https://github.com/KrxkGit/HelpUploadFiles)

## 🍺简介 - Introduction

***HelpUploadFiles （星空上传助手）*** 是一款  **辅助上传** 工具。我们知道，*git* 提供了 **.gitignore** 文件用于根据规则忽略某些文件的上传，但是这个功能仅限于 *git*，还有很多场景涉及**文件的上传**，比如我们可能需要将某些文件上传到网盘，但是大部分网盘并不具备 ***根据规则忽略指定文件*** 的功能，这十分不方便。另外，还存在着许许多多的上传文件的场景，此时，***HelpUploadFiles*** 油然而生！

***HelpUploadFiles*** is an **auxiliary upload** tool. We know that *git* provides a **.gitignore** file for ignoring certain files from being uploaded based on rules, but this feature is limited to *git*. There are many scenarios involving **file uploads**, such as when we might need to upload certain files to cloud storage. However, most cloud storage services do not have the capability to **ignore specified files based on rules**, which is quite inconvenient. Additionally, there are numerous scenarios for uploading files. At this point, ***HelpUploadFiles*** comes into play!

由于对于单个文件，不需要特别的规则进行忽略上传，故 ***HelpUploadFiles*** 主要是针对 ***文件夹*** 的上传场景。

Since there are no special rules required to ignore uploading for individual files, HelpUploadFiles is primarily aimed at scenarios involving folder uploads.

## 🧡Star History

[![Star History Chart](https://api.star-history.com/svg?repos=KrxkGit/HelpUploadFiles&type=Date)](https://star-history.com/#KrxkGit/HelpUploadFiles&Date)

## 🔥软件包的获取

1. 可前往 *Actions* 区下载最新特性 **HelpUploadFiles** 包。
2. 可前往 *Releases* 区下载稳定版本的 **HelpUploadFiles** 包。

## 🔥Package Acquisition

1. You can go to the *Actions* section to download the latest feature package **HelpUploadFiles**.
2. You can go to the *Releases* section to download the stable version of the **HelpUploadFiles** package.

## 🍺文件上传概念的推广 -  Expansion of File Upload Concepts

***HelpUploadFiles*** 涉及的文件上传并不仅仅局限于将本机文件上传到网盘这种场景，在 ***HelpUploadFiles*** 中，凡是需要 **将某个文件夹发送到某一个接口** 的操作均可推广为文件上传。

The file upload involved with HelpUploadFiles is not limited to scenarios of uploading local files to cloud storage. In HelpUploadFiles, any operation that involves sending a folder to a specific interface can be generalized as file uploading.

以下场景均可视文件上传概念的推广：

1. 将本机文件夹上传到**网盘**。
2. 将本机文件夹发送到**另一台设备**（如局域网内设备、服务器对象存储服务等）。
3. 将本机文件夹发送到**压缩软件**等接口。



The following scenarios can be considered as expanded concepts of file uploading:

1. Uploading a local folder to cloud storage.
2. Sending a local folder to another device (such as devices within a local area network, server object storage services, etc.).
3. Sending a local folder to interfaces of compression software, etc.

## 🍻验证通过的应用场景 - Verified Application Scenarios

以下场景均已验证通过：

1. **Chromium 浏览器** 涉及的文件夹上传
2. **Edge 浏览器** 涉及的文件夹上传
3. 百度网盘客户端
4. 腾讯微云客户端
5. 阿里网盘
6. 天翼网盘客户端
7. 中国移动硬盘客户端
8. 联通网盘
9. 谷歌云端硬盘
10. 小飞机网盘
11. 奶牛快传
12. 123云盘
13. 华为云对象存储服务 OBS
14. 阿里云对象存储服务 OSS
15. 腾讯云对象存储服务 COS
16. LocalSend
17. Send Anywhere 客户端
18. WinSCP
19. 7z、Bandizip、360压缩等压缩软件



The following scenarios have been verified and are operational:

1. Folder uploads involving the Chromium browser.
2. Folder uploads involving the Edge browser.
3. Baidu Cloud client.
4. Tencent Weiyun client.
5. Alibaba Cloud Drive.
6. Tianyi Cloud client.
7. China Mobile Hard Disk client.
8. Unicom Cloud.
9. Google Cloud Storage.
10. Little Airplane Cloud.
11. Niuniu Express.
12. 123 Cloud Storage.
13. Huawei Cloud Object Storage Service OBS.
14. Alibaba Cloud Object Storage Service OSS.
15. Tencent Cloud Object Storage Service COS.
16. LocalSend.
17. Send Anywhere client.
18. WinSCP.
19. Compression software such as 7z, Bandizip, 360 Compression, etc.

## 📍使用注意事项

1. ***HelpUploadFiles*** 分为 ***32位*** 与 ***64位***  两个版本，需要根据不同的上传接口选择不同的版本，如目前百度网盘客户端是32位的，则需要使用32位版本的 ***HelpUploadFiles***；而64位系统的Edge浏览器是64位程序，则需要使用64位版本的 ***HelpUploadFiles***。
2. 目前版本(v1.0.3)仅支持同时拦截一个进程的文件上传行为，值得注意的是 ***32位 与 64位版本 加起来一共能同时拦截一个进程***。且 ***添加/移除*** 忽略列表的操作 **仅对当前拦截的进程有效，若切换进程，即使重新注入，也需要重新添加忽略列表（移除后重新添加），否则将无效。** 这是由于目前采用的进程通信方案导致的。
3. 对于下方输入框手动输入的忽略规则，将采用 **C++ 正则表达式规则**。
4. 对于拖拽上传的文件，将自动进行转义使其符合 **C++正则表达式规则**。

## 📍Usage Notes

1. HelpUploadFiles comes in two versions: 32-bit and 64-bit. You need to select the appropriate version based on the upload interface, such as using the 32-bit version of HelpUploadFiles for the 32-bit Baidu Cloud client, while the 64-bit Edge browser on a 64-bit system is a 64-bit program, requiring the 64-bit version of HelpUploadFiles.

2. The current version (v1.0.2) only supports intercepting the file upload behavior of one process at a time. It's important to note that the 32-bit and 64-bit versions combined can only intercept one process simultaneously. Additionally, operations to add/remove the ignore list only take effect for the currently intercepted process. If you switch processes, even with a re-injection, you will need to re-add the ignore list (remove and then re-add), otherwise, it will be ineffective. This is due to the process communication scheme currently in use.

3. For manual input of ignore rules in the input box below, C++ regular expression rules will be used.

4. For files uploaded by dragging and dropping, automatic escaping will be performed to conform to C++ regular expression rules.

## ✨使用步骤（以百度网盘为例，其它应用类似）- **Usage Steps (using Baidu Cloud as an example, other applications are similar)**

1. 打开百度网盘。

   Open Baidu Cloud.

   ![百度网盘](https://github.com/KrxkGit/HelpUploadFiles/blob/main/documents/imgs/1.jpg)

2. 🔑打开 ***HelpUploadFiles***，长按鼠标左键，光标将改变表明程序进入捕获状态，此时将鼠标移动到百度网盘主窗口再松开鼠标左键，下图红框处的提示文字也随之改变为 将要**捕获的窗口的标题**（若标题为空则为窗口类名）。

   Open HelpUploadFiles, press and hold the left mouse button, the cursor will change indicating that the program has entered the capture state. Move the mouse to the main window of Baidu Cloud and release the left mouse button. The prompt text in the red box below will also change to the title of the window to be captured (if the title is empty, it will be the window class name).

   ![image-20240427053601352](https://github.com/KrxkGit/HelpUploadFiles/blob/main/documents/imgs/2.jpg)

3. 此时会提示是否注入赋能模块到百度网盘，点击确认，百度网盘将打开一个对话框告知 **赋能模块注入成功**（这个对话框是由百度网盘所在进程产生的，一个显然的提示是**对话框的图标是百度网盘的图标**），即表明模块注入成功。如果没有提示赋能模块注入成功，有以下两种可能：

   At this point, you will be prompted whether to inject the empowerment module into Baidu Cloud. Click confirm, and Baidu Cloud will open a dialog box informing you of the successful injection of the empowerment module (this dialog box is generated by the Baidu Cloud process, and an obvious indication is that the dialog box icon is the Baidu Cloud icon), indicating that the module injection is successful. If there is no prompt for a successful empowerment module injection, there are two possibilities:

   - 赋能模块在之前已经注入，此次注入为重复注入。

   - 赋能模块注入失败，这表明功能将**不可用**。

     

   - The empowerment module has already been injected before, and this injection is a repeat.
   - The empowerment module injection failed, which means the function will not be available.
     Please ensure that you click the "OK" button on the "Successful Empowerment Module Injection" message box before proceeding to the next step.

   ![image-20240427054456616](https://github.com/KrxkGit/HelpUploadFiles/blob/main/documents/imgs/3.jpg)

   ![image-20240427054258394](https://github.com/KrxkGit/HelpUploadFiles/blob/main/documents/imgs/4.jpg)

   > 请确保在进行下一步前点击 **赋能模块注入成功** 消息框的**确定键**。
   >
   > Please ensure that you click the **OK button** on the **Successful Empowerment Module Injection** message box before proceeding to the next step.

4. **添加忽略规则（基于C++正则表达式规则）**

   **Add ignore rules (based on C++ regular expression rules).**

   有两种方式可以添加忽略规则：

   There are two ways to add ignore rules:

   - 可通过将文件拖拽到忽略文件列表。（拖拽文件会自动完成转义，以自动适配正则表达式规则）。
   - 在下方输入框手动输入正则表达式并点击 “**忽略**” 按钮添加（回车也可以）。

   

   - You can drag and drop files into the ignore file list. (Dragging files will automatically complete the escaping to automatically adapt to regular expression rules).
   - Manually enter the regular expression in the input box below and click the "Ignore" button to add (pressing Enter is also possible).

   如果需要移除忽略规则，可先选中忽略列表框中的忽略规则，然后点击按钮 "**移除**"即可。

   If you need to remove an ignore rule, select the ignore rule in the ignore list box and then click the "Remove" button.

   如下图，我添加了两条忽略规则用以忽略：

   As shown in the figure below, I have added two ignore rules to ignore:

   - .idea 文件夹
   - node_modules 文件夹

   

   - The `.idea` folder
   - The `node_modules` folder

   ![image-20240427055311356](https://github.com/KrxkGit/HelpUploadFiles/blob/main/documents/imgs/5.jpg)

5. **上传文件**

   Upload file

将需要上传的文件夹拖拽到百度网盘（其它方式也可以）完成上传。匹配忽略规则的文件将不会被上传。

Upload files by dragging the folder you need to upload to Baidu Cloud (other methods are also possible) to complete the upload. Files that match the ignore rules will not be uploaded.

<img src="https://github.com/KrxkGit/HelpUploadFiles/blob/main/documents/imgs/6.jpg" alt="image-20240427055606539"  />

![image-20240427055655356](https://github.com/KrxkGit/HelpUploadFiles/blob/main/documents/imgs/7.jpg)

## ⭐关键步骤分析与经验 - Key Step Analysis and Experience

上述步骤的 第 2 步是关键步骤，决定了程序能否达到预期效果。

该步骤要考虑两个问题：

1. 使用哪个版本的***HelpUploadFiles***
2. 捕获哪个窗口（即鼠标移动到哪个窗口再松开）



Step 2 above is the key step, determining whether the program can achieve the expected results.

This step requires considering two issues:

1. Which version of HelpUploadFiles to use
2. Which window to capture (i.e., which window to move the mouse to and then release)

### 🌛分析使用哪个版本的 ***HelpUploadFiles*** - Analysis of Which Version of HelpUploadFiles to Use

- 可通过任务管理器查看要拦截的程序（如百度网盘）是什么版本，然后采用对应版本的 ***HelpUploadFiles***
- 但这也不是绝对的，有些 64位程序 需要使用 32位版本的 ***HelpUploadFiles***，在64位方案不可行时可考虑验证此方案。(如下文的 ***WinSCP*** )

- You can check the version of the program you want to intercept (such as Baidu Cloud) through Task Manager, and then use the corresponding version of HelpUploadFiles.

- However, this is not absolute. Some 64-bit programs require the use of the 32-bit version of HelpUploadFiles. If the 64-bit solution is not feasible, you can consider verifying this scheme (as with WinSCP below).


### 🌜使用经验汇总 - Usage Experience Summary

#### 🌈使用 32位（x86）版本

|         程序          |                      捕获窗口                      |
| :-------------------: | :------------------------------------------------: |
|    百度网盘客户端     |           主窗口 或 拖拽上传悬浮窗口均可           |
|    腾讯微云客户端     | ❗ **QQ主窗口**（注意此处比较特殊，非腾讯微云窗口） |
|       天翼网盘        |           主窗口 或 拖拽上传悬浮窗口均可           |
|     中国移动硬盘      |           主窗口 或 拖拽上传悬浮窗口均可           |
|        WinSCP         |           主窗口 或 拖拽上传悬浮窗口均可           |
| 360压缩等32位压缩工具 |                  压缩菜单弹出窗口                  |
| Send Anywhere 客户端  |                       主窗口                       |

#### 🌈 **Using the 32-bit (x86) Version**

|                      Program                       |                        Capture Window                        |
| :------------------------------------------------: | :----------------------------------------------------------: |
|                 Baidu Cloud Client                 | Main window or drag-and-drop upload floating window both work |
|               Tencent Weiyun Client                | ❗ QQ Main window (note that this is special, not the Tencent Weiyun window) |
|                    Tianyi Cloud                    | Main window or drag-and-drop upload floating window both work |
|               China Mobile Hard Disk               | Main window or drag-and-drop upload floating window both work |
|                       WinSCP                       | Main window or drag-and-drop upload floating window both work |
| 360 Compression and other 32-bit compression tools |                Compression menu pop-up window                |
|                Send Anywhere Client                |                         Main window                          |

#### 🌈使用 64位 （x64）版本

|               程序                |     捕获窗口     |
| :-------------------------------: | :--------------: |
|        **Chromium 浏览器**        |     网页页面     |
|          **Edge 浏览器**          |     网页页面     |
|          奶牛快传网页版           |     网页页面     |
|         小飞机网盘网页版          |     网页页面     |
|          阿里网盘网页版           |     网页页面     |
|           123云盘网页版           |     网页页面     |
|          联通网盘网页版           |     网页页面     |
|        谷歌云端硬盘网页版         |     网页页面     |
| 华为云对象存储服务 OBS 控制台网页 |     网页页面     |
| 阿里云对象存储服务 OSS 控制台网页 |     网页页面     |
| 腾讯云对象存储服务 COS 控制台网页 |     网页页面     |
|             LocalSend             |      主窗口      |
|    7z、Bandizip 等64位压缩工具    | 压缩菜单弹出窗口 |

#### 🌈 **Using the 64-bit (x64) Version**

|                       Program                        |         Capture Window         |
| :--------------------------------------------------: | :----------------------------: |
|                   Chromium Browser                   |            Web page            |
|                     Edge Browser                     |            Web page            |
|              Niuniu Express Web Version              |            Web page            |
|          Little Airplane Cloud Web Version           |            Web page            |
|           Alibaba Cloud Drive Web Version            |            Web page            |
|            123 Cloud Storage Web Version             |            Web page            |
|               Unicom Cloud Web Version               |            Web page            |
|           Google Cloud Storage Web Version           |            Web page            |
| Huawei Cloud Object Storage Service OBS Console Web  |            Web page            |
| Alibaba Cloud Object Storage Service OSS Console Web |            Web page            |
| Tencent Cloud Object Storage Service COS Console Web |            Web page            |
|                      LocalSend                       |          Main window           |
|   7z, Bandizip, and other 64-bit compression tools   | Compression menu pop-up window |

## 🍗操作视频演示（以7z压缩软件为例）- Operation Video Demonstration (using 7z compression software as an example)

<img src="https://github.com/KrxkGit/HelpUploadFiles/blob/main/documents/imgs/8.gif" alt="演示视频" style="zoom: 80%;" />

## 🌭C++正则表达式附录 - C++ Regular Expression Appendix

正则表达式是一种用于描述字符串模式的工具，它可以帮助您在文本中进行搜索、匹配、替换等操作。以下是一些常用的正则表达式规则和符号：

1. 字符类别：
   - `\d`：匹配任意一个数字字符，相当于 `[0-9]`。
   - `\D`：匹配任意一个非数字字符，相当于 `[^0-9]`。
   - `\w`：匹配任意一个字母、数字或下划线字符，相当于 `[a-zA-Z0-9_]`。
   - `\W`：匹配任意一个非字母、数字或下划线字符，相当于 `[^a-zA-Z0-9_]`。
   - `\s`：匹配任意一个空白字符，包括空格、制表符、换行符等。
   - `\S`：匹配任意一个非空白字符。
2. 重复次数：
   - `*`：匹配前面的字符零次或多次。
   - `+`：匹配前面的字符一次或多次。
   - `?`：匹配前面的字符零次或一次。
   - `{n}`：匹配前面的字符恰好 n 次。
   - `{n,}`：匹配前面的字符至少 n 次。
   - `{n,m}`：匹配前面的字符至少 n 次，最多 m 次。
3. 边界匹配：
   - `^`：匹配字符串的开头。
   - `$`：匹配字符串的结尾。
   - `\b`：匹配单词边界。
4. 分组和引用：
   - `()`：将其中的字符视为一个整体，可以用于分组操作。
   - `\1`, `\2`, ...：引用分组中的匹配结果。
5. 特殊字符转义：
   - `\`：用于转义特殊字符，例如 `\.` 表示匹配点字符 `.`。
6. 其他常用符号：
   - `|`：表示或操作，匹配两者之一。
   - `.`：匹配任意一个字符，除了换行符。



Regular expressions are tools used to describe string patterns that can help you perform operations such as search, match, and replace in text. Here are some common regular expression rules and symbols:

Character Categories:

- `\d`: Matches any digit character, equivalent to `[0-9]`.
- `\D`: Matches any non-digit character, equivalent to `[^0-9]`.
- `\w`: Matches any letter, digit, or underscore character, equivalent to `[a-zA-Z0-9_]`.
- `\W`: Matches any non-letter, non-digit, or non-underscore character, equivalent to `[^a-zA-Z0-9_]`.
- `\s`: Matches any whitespace character, including spaces, tabs, and newlines.
- `\S`: Matches any non-whitespace character.

Repeat Counts:

- `*`: Matches the preceding character zero or more times.
- `+`: Matches the preceding character one or more times.
- `?`: Matches the preceding character zero or one time.
- `{n}`: Matches the preceding character exactly n times.
- `{n,}`: Matches the preceding character at least n times.
- `{n,m}`: Matches the preceding character at least n times, but no more than m times.

Boundary Matches:

- `^`: Matches the beginning of a string.
- `$`: Matches the end of a string.
- `\b`: Matches a word boundary.

Grouping and Referencing:

- `()`: Treats the characters within as a group for operations.
- `\1, \2, ...`: Refer to the match results of the grouped matches.

Special Character Escaping:

- `\`: Used to escape special characters, for example, `\.` represents a match for the dot character.

Other Common Symbols:

- `|`: Represents an OR operation, matching either of the two.
- `.`: Matches any character except for a newline.


## 🧊v1.0.4 新增功能 - v1.0.4 New Features

### 🥤简介 - Introduction

新版本增添了基于进程 id 注入赋能模块到进程的功能,主要可用于注入一些不存在可见窗口的进程。其中选择 32位还是 64 位版本 HelpUploadFiles 的策略与基于窗口捕获方案相同。

The new version has added the functionality to inject an empowerment module into a process based on the process ID, which can primarily be used for injecting into processes that do not have visible windows. The strategy for selecting whether to use the 32-bit or 64-bit version of HelpUploadFiles is the same as the one based on the window capture scheme.

### 🥤使用步骤 - Usage Steps

#### 🍷通过任务管理器获取进程 id -  Obtain the Process ID through Task Manager

通过任务管理器查看需要注入的进程 id号。

Use the Task Manager to view the process ID that needs to be injected.

![image-20240509222044400](https://github.com/KrxkGit/HelpUploadFiles/blob/main/documents/imgs/10.jpg)

#### 🍷根据进程id注入进程 - Inject into the Process Based on the Process ID

选择合适版本 (x86/x64) 的 **HelpUploadFiles** 完成注入。

Choose the appropriate version (x86/x64) of **HelpUploadFiles** to complete the injection.

![image-20240509221813136](https://github.com/KrxkGit/HelpUploadFiles/blob/main/documents/imgs/9.jpg)

![image-20240509222322638](https://github.com/KrxkGit/HelpUploadFiles/blob/main/documents/imgs/11.jpg)

## 🧊v1.0.5 新增功能 - v1.0.5 New Features

此版本新增忽略列表导入与导出功能。

This version adds the functionality of importing and exporting an ignore list.


## 🟡已发现的不完全适用情况 - Known Partially Incompatible Situations

- 比特球网盘 未完全兼容，存在目录创建失败问题。
- BitBalloon Cloud Storage is not fully compatible, with issues such as directory creation failure.