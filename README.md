# pjson - JSON Parser in C

This README provides a comprehensive guide to the project, including its features, installation steps, and usage.

---

**pjson** is a simple command-line tool written in C for parsing JSON files and retrieving values based on keys.

## Table of Contents
  - [Introduction](#introduction)
  - [Features](#features)
  - [Updates](#updates)
  - [Dependencies](#dependencies)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
    - [Clone the repository](#clone-the-repository)
    - [Compile the program](#compile-the-program)
    - [Install the program](#install-the-program)
  - [Uninstallation](#uninstallation)
  - [Usage](#usage)
  - [Help](#help)
  - [Files](#files)
  - [Customize](#customize)
    - [Color Schemes](#color-schemes)
  - [Examples](#examples)
    - [Integrating 'pjson' with Bash Scripts](#integrating-pjson-with-bash-scripts)
  - [Advantages](#advantages)
  - [License](#license)

## Introduction

**pjson** is a lightweight and efficient C program for parsing JSON files.
It allows retrieval of values based on specific keys and is ideal for configuration management and automation scripts.
Additionally, it supports syntax highlighting for JSON file contents.

![GitHub Release](https://img.shields.io/github/v/release/AntiSecTech/pjson?display_name=release)
![GitHub License](https://img.shields.io/github/license/AntiSecTech/pjson)
![GitHub Downloads (all assets, all releases)](https://img.shields.io/github/downloads/AntiSecTech/pjson/total)


---

## Features

- **Minimal Dependencies:** Only requires the `jansson` library.
- **High Performance:** Written in C for speed and efficiency.
- **Ease of Use:** Simple command-line interface for easy integration.
- **Parse** JSON files.
- **Retrieve nested values** using dot notation for keys.
- **Syntax highlighting** for file content.
- **Changeable color themes** for syntax highlighting.

---

## Updates

This release is currently in version: **1.0.0**
Please refer to the `changelog` for all information on current changes.

You can view it [here](https://github.com/AntiSecTech/pjson/blob/main/CHANGELOG.md).

![GitHub Release](https://img.shields.io/github/v/release/AntiSecTech/pjson?display_name=release)
![GitHub Tag](https://img.shields.io/github/v/tag/AntiSecTech/pjson)

---

## Dependencies

The `jansson` library is required to compile this project.
It can be installed on Linux systems using package managers.

### Linux:

```sh
sudo apt-get update
sudo apt-get install libjansson-dev   # for Debian/Ubuntu
sudo dnf install jansson-devel        # for Fedora
sudo pacman -S jansson                # for Arch Linux
```

---

## Prerequisites

To compile the C program, you need to have the `GCC` compiler installed on your system.

### Linux:
```sh
sudo apt-get update
sudo apt-get install gcc   # for Debian/Ubuntu
sudo dnf install gcc       # for Fedora
sudo pacman -S gcc          # for Arch Linux
```

---

## Installation
### Clone the repository:
```sh
git clone https://github.com/AntiSecTech/pjson.git
cd pjson
```
### Compile the program:
```sh
make compile
```
### Install the program:
```sh
sudo make install
```
If you do not install the program and only compile the binary, you must **create a link for the configuration file** [`pjson.json`](https://github.com/AntiSecTech/pjson/blob/main/pjson.json) so that it can be read by the binary.
```sh
sudo ln -s -r pjson.json /etc
```
If you have any further questions about the `Make` process, please refer to the source code of the [Makefile](https://github.com/AntiSecTech/pjson/blob/main/Makefile).

---

## Uninstallation
```sh
cd pjson
sudo make uninstall
```
---

## Usage
```sh
   pjson <file.json> [<key>]
```

---

## Help
The following options are available to help you use **pjson**.

**Built-in**
```sh
   pjson --help
```
***Overview***
|Command|Option|Argument|Optional Argument|Description|
|---|---|---|---|---|
| pjson | | | | Show the usage |
| pjson | | <File.json> | | Show content of <`File.json`> |
| pjson | | <File.json> | \<Key> | Show the value from <`Key`> |
| pjson | -h \| --help | | | Show the help |
| pjson | -v | | | Show version number |
| pjson | --version | | | Show detailed version information |


**Manpage**

To open the manual, use the following command:
```sh
   man pjson
```

---

## Files
Here you will find a small overview of the files used and their locations.
|Filename|Filetype|Project Path|Install Path|Description|
|---|---|---|---|---|
| pjson	| binary | ./pjson | /usr/local/bin | Executable binary |
| pjson.c | plaintext | ./pjson | | Source code |
| pjson.json | json | ./pjson | /etc | Configuration |
| pjson.1 | troff | ./pjson | /usr/local/man/man1 | Manpage |

---

## Customize
The program utilizes [`pygmentize`](https://pygments.org/) to provide syntax highlighting for JSON files.
By default, it uses the color scheme specified in the [`pjson.json`](https://github.com/AntiSecTech/pjson/blob/main/pjson.json) file.
Users can customize the color scheme by modifying this configuration file.

Open the [`pjson.json`](https://github.com/AntiSecTech/pjson/blob/main/pjson.json) file located in the same directory as the program.
Locate the **scheme** field under the **Config** section.
Change its value to your desired Pygments color scheme.
```json
{
  "Config": {
    "scheme": "default"
  }
}
```
For example, you can change the color scheme to `monokai`:
```json
{
  "Config": {
    "scheme": "monokai"
  }
}
```
After editing the configuration file, the new color scheme will be applied automatically.

### Color Schemes
[`Pygments`](https://pygments.org/) offers a wide variety of color schemes. Some popular options include:
 - monokai
 - autumn
 - github-dark

 For a full list of available styles, you can use the following command:
 ```sh
 pygmentize -L styles
 ```

---

 ## Examples
 Given the following JSON file [`test.json`](https://github.com/AntiSecTech/pjson/blob/main/test.json):
```json
{
  "main-key": {
    "keyword": "value",
    "sub-key": {
      "inner-sub-keyword": "value"
    }
  },
  "next-key": {
    "keyword": "another-value",
    "inner-sub": {
      "keyword": "nested values"
    }
  }
}
```
Retrieve the following keys:

 - main-key.keyword
 - next-key.keyword
 - next-key.inner-sub.keyword
```sh
   pjson test.json main-key.keyword
   pjson test.json next-key.keyword
   pjson test.json next-key.inner-sub.keyword
```
Output:
```sh
   value
   another-value
   nested values
```

### Integrating 'pjson' with Bash Scripts
One of the primary advantages of **pjson** is its seamless integration with Bash scripts.
This allows for dynamic reading and setting of configuration parameters directly within your scripts.

**Example Bash Script:**
```sh
   #!/bin/bash

   # Parse JSON file and store values in variables
   config_file="config.json"
   key=$(pjson $config_file Property.Key)

   # Use the parsed values
   echo "Value: $key"
```
```json
{
  "Property": {
    "Key": "value"
  }
}
```
Output:
```sh
   Value: value
```

---

## Advantages
 - **Efficiency:** Written in C, pjson provides high-speed parsing capabilities, reducing overhead in scripts.
 - **Simplicity:** With its straightforward command-line interface, pjson can be easily integrated into existing workflows and automation scripts.
 - **Flexibility:** Able to parse any standard JSON file, making it versatile for various applications and configurations.

---

## License
This project is licensed under the [`MIT License`](https://github.com/AntiSecTech/pjson/blob/main/LICENSE). See the [LICENSE](https://raw.githubusercontent.com/AntiSecTech/pjson/main/LICENSE) file for more details.
