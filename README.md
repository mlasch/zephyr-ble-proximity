# ble-proximity
This is a scanner for the Bluetooth Low Energy based Apple/Google exposure notification protocol for embedded devices.

More information about the protocol specification: https://www.apple.com/covid19/contacttracing


## Build

Get west workspace
```
$ git clone https://github.com/mlasch/zephyr-ble-proximity.git
```

Fetch requrired files
```
$ cd zephyr-ble-proximity
$ west update
```

Build the `ble-proximity` application for a specific board. The selected board should support Bluetooth of course.

```
$ west build -b nrf52840dk_nrf52840 ble-proximity 
```
or
```
$ west build -b bbc_microbit ble-proximity
```

