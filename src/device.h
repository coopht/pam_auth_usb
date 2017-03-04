#pragma once

#include <string>

using std::string;

class Device {
    public:
        Device () :
            m_manufacturer(""),
            m_product(""),
            m_serialNumber(""),
            m_idVendor(0),
            m_idProduct(0)
            { /* empty constructor for now*/}

        const string manufacturer() const { return m_manufacturer; }
        void setManufacturer(const string &val) { m_manufacturer = val; }

        const string product() const { return m_product; }
        void setProduct(const string &val) { m_product = val; }

        const string serialNumber() const { return m_serialNumber; }
        void setSerialNumber(const string &val) { m_serialNumber = val; }

        uint16_t idProduct() const { return m_idProduct; }
        void setIdPorduct(const uint16_t val) { m_idProduct = val; }

        uint16_t idVendor() const { return m_idVendor; }
        void setIdVendor(const uint16_t val) { m_idVendor = val; }

        bool operator == (const Device &o) const {
            return (m_idVendor == o.idVendor()
                        && m_idProduct == o.idProduct()
                        && m_manufacturer == o.manufacturer()
                        && m_product == o.product()
                        && m_serialNumber == o.serialNumber());
        }

    private:
        string m_manufacturer;
        string m_product;
        string m_serialNumber;
        uint16_t m_idVendor;
        uint16_t m_idProduct;
};

