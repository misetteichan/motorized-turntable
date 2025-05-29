# motorized-turntable

[日本語](./README_ja.md)

This is a project for an automatic rotary turntable using M5Stack Roller485Lite.  
By combining 3D printed parts and electronic components, you can build your own motorized turntable.

**Good news!** Roller485 is also supported (see the end for details!).

## Overview

This project consists of the following two main components:

1. **Firmware for M5Stack NanoC6**: Controls the M5Stack Roller485Lite and manages the rotation.
2. **3D Print Model**: Creates the turntable body and mechanical parts.

## Required Components

- M5Stack NanoC6
- M5Stack Roller485Lite
- Grove cable (1 piece) (to connect NanoC6 and Roller485Lite)
- 3D printer (for STL file output)
- 4 fixing screws (M3x5 pan head screws)
- 4 anti-slip rubber feet
- Double-sided tape or adhesive for fixing the top cover

## Setup Instructions

### Build and Install Firmware

1. Install [PlatformIO](https://platformio.org/)
2. Clone this repository
3. Open the project with PlatformIO
4. Build and upload to M5Stack NanoC6

```bash
# For PlatformIO command line
platformio run -t upload
```

### Generate and Print 3D Model

1. Install the required Python packages

```bash
cd 3dmodel
pip install -r requirements.txt
```

2. Generate the model (default diameter is 100mm)

```bash
python turntable.py --diameter 100
```

3. Print the generated STL files (`top.stl`, `bottom.stl`, `upper.stl`) with a 3D printer

## Assembly Instructions

1. Prepare the 3D printed parts
2. Attach the M5Stack NanoC6 and M5Stack Roller485Lite to the bottom, and connect them with the Grove cable
3. Assemble the top and bottom parts and fix them with the screws
4. Attach the anti-slip rubber feet to the bottom of each part
5. Attach the top cover

## How to Use

There are no switches or control panels on the main unit. Just spin it by hand to operate.

1. Connect the M5Stack NanoC6 to your PC or power adapter via USB cable for power
2. Spin the turntable by hand and it will automatically continue rotating at that speed
3. You can change the speed by spinning it by hand even during operation
4. If you stop the rotation by hand, the motor control will also stop

## Appendix: Using with Roller485

The firmware in this project works with both Roller485Lite and Roller485 as-is.  
For Roller485, please use `upper_nolite.stl` instead of `upper.stl` for the 3D model.  
There is a hole for the Grove cable on the table. If needed, edit `turntable_nolite.py` to generate a custom 3D model.

## License

This project is released under the MIT License. For details, please see the [LICENSE](LICENSE) file.

## Author

名称未設定ちゃん (misetteichan)

---
This document was created by the AI assistant Cascade.
