#pragma once

#include <QtQuick/QQuickPaintedItem>
#include <libusb.h>
#include "aasdk/USB/USBHub.hpp"
#include "aasdk/USB/USBWrapper.hpp"
#include "aasdk/USB/AccessoryModeQueryChainFactory.hpp"
#include "aasdk/USB/AccessoryModeQueryFactory.hpp"
#include <thread>
#include "aasdk/USB/ConnectedAccessoriesEnumerator.hpp"

class OpenAutoConnector : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT
    Q_DISABLE_COPY(OpenAutoConnector)

public:
    explicit OpenAutoConnector(QQuickItem *parent = nullptr);
    ~OpenAutoConnector() override;

    Q_INVOKABLE void start();
    void stop();

signals:
    void deviceConnected();

private:
    void aoapDeviceHandler(aasdk::usb::DeviceHandle deviceHandle);
    boost::asio::io_service ioService;
    boost::asio::io_service::work work;
    boost::asio::io_service::strand strand;
    libusb_context* usbContext;
    aasdk::usb::USBWrapper usbWrapper;
    aasdk::usb::IUSBHub::Pointer usbHub;
    aasdk::usb::AccessoryModeQueryFactory accessoryModeQueryFactory;
    aasdk::usb::AccessoryModeQueryChainFactory accessoryModeQueryChainFactory;
    aasdk::usb::IConnectedAccessoriesEnumerator::Pointer connectedAccessoriesEnumerator;
    
    std::vector<std::thread> threadPool;

};