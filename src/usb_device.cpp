// Copyright (c) <2017> <Alexander Basov>

#include <cstring>
#include <cerrno>
#include <iostream>
#include <unistd.h>
#include <syslog.h>

#include <libusb-1.0/libusb.h>

#include "config.h"
#include "device.h"
#include "usb_device.h"


using namespace std;

static void fillDeviceInfo (libusb_device *usbDev,
                              libusb_device_handle *devHandle,
                              Device &dev)
{
    struct libusb_device_descriptor  devDesc;
    unsigned char strDesc [BUFSIZ] = {0};

    int retval = libusb_get_device_descriptor (usbDev, &devDesc);

    if (retval != LIBUSB_SUCCESS) {
        cerr << "Cannot get device descriptor" << endl;
    }

    if (devDesc.iManufacturer > 0) {
        retval = libusb_get_string_descriptor_ascii(devHandle,
                                                    devDesc.iManufacturer,
                                                    strDesc, sizeof(strDesc));
        if (retval < 0) {
            cerr << "Cannot get manufacturer" << endl;
        } else {
            dev.setManufacturer((const char*)strDesc);
        }
    }

    if (devDesc.idProduct> 0) {
        retval = libusb_get_string_descriptor_ascii(devHandle,
                                                    devDesc.iProduct,
                                                    strDesc, sizeof(strDesc));
        if (retval < 0) {
            cerr << "Cannot get product" << endl;
        } else {
            dev.setProduct((const char*)strDesc);
        }
    }

    if (devDesc.iSerialNumber > 0)
    {
        retval = libusb_get_string_descriptor_ascii(devHandle,
                                                    devDesc.iSerialNumber,
                                                    strDesc, sizeof(strDesc));
        if (retval < 0) {
            cerr << "Cannot get serialNumber" << endl;
        } else {
            dev.setSerialNumber((const char*)strDesc);
        }
    }

    dev.setIdVendor(devDesc.idVendor);
    dev.setIdPorduct(devDesc.idProduct);
}

static bool findDevice(libusb_device *dev, Device &local)
{
    libusb_device_handle *devHandle = NULL;
    int retval = libusb_open (dev, &devHandle);
    if (retval != LIBUSB_SUCCESS) {
        cerr << "Cannot open device" << endl;
        return false;
    }

    Device tmp;
    fillDeviceInfo(dev, devHandle, tmp);
    libusb_close(devHandle);
    return (tmp == local);
}

static bool isConnected(Device &local)
{
    bool isFound = false;
    static libusb_device **devices;
    ssize_t dev_count = 0;
    libusb_device *dev = NULL;

    if (libusb_init(NULL) != LIBUSB_SUCCESS) {
        std::cerr << "Cannot initialize libusb error: %d" << std::endl;
        return isFound;
    }

    dev_count = libusb_get_device_list(NULL, &devices);
    for (ssize_t j = 0; j < dev_count; ++j) {
        isFound = findDevice(devices[j], local);
        if (isFound){
            break;
        }
    }

    /* if no devices found, free list */
    if (!dev) {
        libusb_free_device_list(devices, 1);
    }
    libusb_exit(NULL);
    return isFound;
}


bool isDeviceConnected(void)
{
    Device d = load();
    return isConnected(d);
}
