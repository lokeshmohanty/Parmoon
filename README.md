# ParMooN

## Installation

- Setup [intel oneAPI compilers](https://www.intel.com/content/www/us/en/developer/tools/oneapi/base-toolkit-download.html?packages=oneapi-toolkit&oneapi-toolkit-os=linux&oneapi-lin=offline)

```sh
# Download the installer
wget https://registrationcenter-download.intel.com/akdlm/IRC_NAS/d640da34-77cc-4ab2-8019-ac5592f4ec19/intel-oneapi-base-toolkit-2025.3.0.375_offline.sh

# Run the installer
sudo sh ./intel-oneapi-base-toolkit-2025.3.0.375_offline.sh -a --silent --cli --eula accept
```

- Install dependencies

```sh
# For Ubuntu
sudo apt update
sudo apt -y install cmake pkg-config build-essential
```

- Add the intel compilers to path

```sh
. /opt/intel/oneapi/setvars.sh
```

## Usage

- Clone this repository

```sh
git clone https://github.com/airexlab/ParMooN_CMG.git -o ParMooN
cd ParMooN
```

- Set the **main file**, **output directory** and other configuration in `UserConfig.cmake`

- Build the executable

```sh
mkdir BUILD
cd BUILD
cmake ..
make -j<number-of-processors>
```

- Run the executable file generated in the output directory

```sh
cd ../OUTPUT/CD2D
./parmoon_2D_SEQUENTIAL.exe
```
