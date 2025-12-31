# ParMooN

## Installation

- Setup intel [oneAPI compilers](https://www.intel.com/content/www/us/en/developer/tools/oneapi/onemkl-download.html)

```sh
# For Ubuntu

## Download the installer
wget https://registrationcenter-download.intel.com/akdlm/IRC_NAS/2ad98b49-1fb2-4294-ab3d-6889b434ebd3/intel-onemkl-2025.3.0.462_offline.sh

## Run the installer
sudo sh ./intel-onemkl-2025.3.0.462_offline.sh
```

- Add the intel compilers to path

```sh
. /opt/intel/oneapi/setvars.sh
```

## Usage

- Clone this repository

```sh
git clone https://github.com/airexlab/ParMooN_CMG.git
cd ParMooN_CMG
```

- Set the main file, output directory and other configuration in `UserConfig.cmake`

- Build the executable

```sh
mkdir build
cd build
cmake ..
make -j<number-of-processors>
```

- Run the executable file generated in the output directory

```sh
cd ../../ParMooN_Output/CD2D
./parmoon_2D_SEQUENTIAL.exe
```
