# Installation
Needed packages:
- armgcc
- code
- nRF5 SDK 

After downloading nRF5 SDK, extract it to chosen directory.

## Ubuntu
Installation in Ubuntu:
* ARM-GCC
```shell
sudo apt update
sudo apt install gcc-arm-none-eabi binutils-arm-none-eabi gdb-arm-none-eabi openocd
```

* NRF SDK
```shell
cd ~/Downloads/
wget https://www.nordicsemi.com/-/media/Software-and-other-downloads/SDKs/nRF5/Binaries/nRF5SDK160098a08e2.zip
unzip nRF5SDK160098a08e2.zip -d ~/nrf5_sdk/
```

# VS Code configuration files
VSCode configuration is devided into files:
- settings.json - vscode configuration, (e.g. code formatting)
- tasks.json - tasks configuration  (e.g. make, make flash, make clean)
- c_cpp_properties.json - IntelliSense configuration (paths to find Include files, macros etc.)

Additional:
- launch.json - running and debugging configurations


# Example project
## Running project based on nRF5 SDK example
Create a directory inside the sdk directory, for example "projects" and copy the blinky example provided by SDK.

```shell
cd ~/nrf5_sdk/
mkdir projects
cd ./examples
cp -r --parents ./peripheral/blinky ../projects/
cd ../projects/peripheral/blinky
```

## Downloading basic VS Code configuration
Example configuration files are in this repository. You can either clone it with GIT or download it as an archive.

After downloading extract it to your project directory:
```shell
unzip nrf52.vscode.zip -d ~/nrf5_sdk/projects/peripheral/blinky/.vscode/
```

## Running VS Code
```shell
cd ~/nrf5_sdk/projects/peripheral/blinky
code .
```

# Confiuration adjustment
Configuration files need to be adjusted to your project. The process is rather easy, but it may depend on the complexity of your solution.
## tasks.json
In tasks file you have to set up your build configuration. For example, you may have a production or debug or multiple boards configurations.

## c_cpp_properites.json
This file configures C/C++ extension and IntelliSense engine. c_cpp_properties.json should be filled with information from the Makefile of your project/example (Makefile is usually found in your_project/pca10056/armgcc/Makefile)

It is also necessary to include path for sdk_config.h, usually:
```
"${workspaceFolder}/pca10056/blank/config/sdk_config.h"
```

### SoftDevice
If you are using SoftDevice in your project, this path usually changes to something like:
```
"${workspaceFolder}/pca10056/*s140*/config/sdk_config.h"
```

It is also very important to add SoftDevice macros for IntelliSense engine:
```
"NRF_SD_BLE_API_VERSION=7",
"S140",
"SOFTDEVICE_PRESENT"
```

# Other
This tutorial is based on:
* [Windows example](https://github.com/gera-k/VSC-Nordic-example)
* [Linux example](https://github.com/justinmklam/nrf52-blinky-demo)