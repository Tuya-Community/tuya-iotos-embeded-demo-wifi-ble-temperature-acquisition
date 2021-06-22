# Tuya IoTOS Embedded Wi-Fi & Bluetooth LE Temperature Data Logger

[English](./README.md) | [中文](./README_zh.md)

## Overview

In this demo, we will show you how to prototype a temperature data logger with a B3950 temperature sensor and make it IoT-enabled. Based on the [Tuya IoT Platform](https://iot.tuya.com/), we use Tuya's Wi-Fi and Bluetooth LE combo module, SDK, and the Tuya Smart app to connect the temperature data logger to the cloud. This way, you can view the detected ambient temperature on the mobile app.

## Get started

### Compile and flash

+ Download [Tuya IoTOS Embedded Wi-Fi & Bluetooth LE SDK](https://github.com/tuya/tuya-iotos-embeded-sdk-wifi-ble-bk7231n).

+ Clone this demo to the `app` folder in the downloaded SDK.

  ```bash
  $ cd apps
  $ git clone https://registry.code.tuya-inc.top/hardware_developer/tuya-iotos-embeded-demo-wifi-ble-temperature-acquisition.git
  ```
+ Run the following command in the SDK root directory to start compiling.

  ```bash
  sh build_app.sh apps/bk7231n_temperature_demo bk7231n_temperature_demo 1.0.0 
  ```

+ For more information about flashing and authorization, see [Flash Firmware to and Authorize WB Series Modules](https://developer.tuya.com/en/docs/iot/device-development/burn-and-authorization/burn-and-authorize-wifi-ble-modules/burn-and-authorize-wb-series-modules?id=Ka78f4pttsytd).


### File introduction

```
├── src	
|    ├── app_driver
|    |    └── tuya_b3950.c            // Temperature sensor driver
|    ├── tuya_device.c             // Entry file of the application layer
|    └── tuya_app_temperature.c            // Main application layer
|
├── include 			  // Header directory
|    ├── app_driver
|    |    └──tuya_b3950.h
|    ├── tuya_device.h
|    └── tuya_app_temperature.h
|
└── output              // Production
```



### Entry to application

Entry file: `tuya_device.c`

Function: `device_init()`

+ Call `tuya_iot_wf_soc_dev_init_param()` for SDK initialization to configure working mode and pairing mode, register callbacks, and save the firmware key and PID.
+ Call `tuya_iot_reg_get_wf_nw_stat_cb()` to register callback of device network status.
+ Call the initialization function `app_b3950_init()` in the application layer.



### Data point (DP)

+ Send DP data: `dev_obj_dp_cb() -> deal_dp_proc()`
+ Report DP data: `dev_report_dp_json_async()`

| Function name | OPERATE_RET dev_report_dp_json_async(IN CONST CHAR_T *dev_id,IN CONST TY_OBJ_DP_S *dp_data,IN CONST UINT_T cnt) |
|	---|---|
| devid | For gateways and devices built with the MCU or SoC, the `devid` is NULL. For sub-devices, the `devid` is `sub-device_id`. |
| dp_data | The name of DP struct array |
| cnt | The number of elements in the DP struct array |
| Return | `OPRT_OK`: success. Other values: failure. |

### Pin configuration

| B3950 |  |
| --- | --- |
| `TUYA_ADC2` | ADC |

## Reference

[Tuya Project Hub](https://developer.tuya.com/demo)

## Technical support

You can get support from Tuya with the following methods:

+ [Service & Support](https://service.console.tuya.com)
+ [Tuya IoT Developer Platform](https://developer.tuya.com/en/)
+ [Help Center](https://support.tuya.com/en/help)

