// Copyright (c) <2017> <Alexander Basov>

#pragma once

#include <string.h>

#include "device.h"

Device load(const std::string &configFile = "/etc/pam_usb.conf");

