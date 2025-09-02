# Dovecot 从 Git 仓库构建指南

## 概述

本文档介绍如何从 [Dovecot 官方 Git 仓库](https://github.com/dovecot/core) 构建 Dovecot 邮件服务器。

## 从 Git 仓库构建

有时，我们可能会直接从 Dovecot 的开发"农场"——Git 仓库获取源代码。如果这样做，需要额外的准备步骤，因为 `configure` 脚本和 `Makefile` 不会立即可用。

`INSTALL.md` 文件提到了这一点：

```markdown
从 git 构建时，需要先运行 `./autogen.sh`。
```

`./autogen.sh` 是一个脚本，用于生成 `configure` 脚本和其他构建过程所需的文件。可以将其视为准备"烘焙工具"，并确保"食谱指令"是最新的，然后才能开始检查食材。

## 构建步骤

如果从 Git 获取代码，我们的步骤将是：

```bash
# 1. 克隆仓库
git clone https://github.com/dovecot/core.git
cd core

# 2. 运行 autogen.sh 生成构建文件
./autogen.sh

# 3. 配置构建
./configure

# 4. 编译
make

# 5. 安装
sudo make install
```

## 步骤说明

1. **克隆仓库**: 从 GitHub 获取最新的源代码
2. **运行 autogen.sh**: 生成 configure 脚本和其他构建所需的文件
3. **配置**: 检查系统依赖并生成 Makefile
4. **编译**: 编译源代码
5. **安装**: 将编译好的文件安装到系统中

**重要提醒**: 首先运行 `./autogen.sh` 来设置一切，然后按照标准的三步流程（configure、make、make install）进行。

## 相关链接

- [Dovecot 官方网站](https://www.dovecot.org/)
- [Dovecot GitHub 仓库](https://github.com/dovecot/core)
- [Dovecot 官方文档](https://doc.dovecot.org)

## 许可证

Dovecot 使用多种许可证：
- LGPL-2.1
- MIT
- 其他许可证（详见 COPYING 文件）
