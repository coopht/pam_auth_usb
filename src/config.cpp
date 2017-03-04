
/*
 * Configuration file contains serialized representation of Device class
 */
#include "config.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include "usb_device.h"

using std::string;

static inline bool isLineOK(const string &s) {
    return (s.length() > 0
            &&  !std::all_of(s.begin(),s.end(),[](char c) { return std::isspace(c); })
            &&  (s[0] != '#'));
}

static inline bool equal(const string &s1, const string &s2) {
    return s2.compare(0, s1.size(), s1) == 0;
}

// TODO: remove trailing spaces
// removes leading spaces
static inline string & trim(string &s)
{
    s.erase(s.begin(),find_if_not(s.begin(),s.end(),[](int c){return isspace(c);}));
    return s;
}


Device load(const string &configFile) {
    std::ifstream inFile(configFile);
    Device d;

    if (inFile) {
        std::string line;
        while (std::getline(inFile, line)) {
            if (isLineOK(line)) {
                size_t eq = line.find('=');
                if (eq == string::npos){
                    continue;
                }

                string param = line.substr(0, eq);
                string value = line.substr(eq + 1, line.length());
                value = trim(value);

                if (!isLineOK(value)) {
                    std::cerr << "WARNING: No value is not set for '"
                              << param << "'" << std::endl;
                    continue;
                }
                if (equal("manufacturer", param)) {
                    d.setManufacturer(value);
                }
                else if (equal("product", param)) {
                    d.setProduct(value);
                }
                else if (equal("serialNumber", param)) {
                    d.setSerialNumber(value);
                }
                else if (equal("idVendor", param)) {
                    d.setIdVendor(stoi(value, nullptr,16));
                }
                else if (equal("idProduct", param)) {
                    d.setIdPorduct(stoi(value, nullptr,16));
                }
                else {
                    std::cerr << "unknown parameter [" << param << "]" << std::endl;
                }
            }
        }
    }
    else {
        std::cerr << "Cannot open config file." << std::endl;
    }
    return d;
}
