#include "networkhelper.h"

#include <QNetworkInterface>
#include <QHostInfo>

/*
 * This code is based on code I found here:
 * http://qt-project.org/forums/viewreply/100389/
 */

/**
 Link Local address should be in the range
 169.254.1.0 to 169.254.254.255
 Refer :http://en.wikipedia.org/wiki/Private_network
 */
bool NetworkHelper::isLinkLocalAddress(const QHostAddress &addr)
{
    quint32 hostIpv4Addr = addr.toIPv4Address();
    quint32 rangeMin = QHostAddress("169.254.1.0").toIPv4Address();
    quint32 rangeMax = QHostAddress("169.254.254.255").toIPv4Address();
    return (hostIpv4Addr >= rangeMin && hostIpv4Addr <= rangeMax);
}

/**
 Refer: http://en.wikipedia.org/wiki/Private_network
 Private Ipv4 address ranges:
  1. 10.0.0.0 - 10.255.255.255
  2. 172.16.0.0 - 172.31.255.255
  3. 192.168.0.0 - 192.168.255.255
 */
bool NetworkHelper::isLocalIpAddress(const QHostAddress &addr)
{
    quint32 hostIpv4Addr = addr.toIPv4Address();
    quint32 range1Min = QHostAddress("10.0.0.0").toIPv4Address();
    quint32 range1Max = QHostAddress("10.255.255.255").toIPv4Address();

    quint32 range3Min = QHostAddress("172.16.0.0").toIPv4Address();
    quint32 range3Max = QHostAddress("172.31.255.255").toIPv4Address();

    quint32 range2Min = QHostAddress("192.168.0.0").toIPv4Address();
    quint32 range2Max = QHostAddress("192.168.255.255").toIPv4Address();

    return ((hostIpv4Addr >= range1Min && hostIpv4Addr <= range1Max)
            || (hostIpv4Addr >= range2Min && hostIpv4Addr <= range2Max)
            || (hostIpv4Addr >= range3Min && hostIpv4Addr <= range3Max));
}

QHostAddress NetworkHelper::localIpAddress()
{
    QHostInfo hostInfo = QHostInfo::fromName(QHostInfo::localHostName());
    QList<QHostAddress> hostNameLookupAddressList = hostInfo.addresses();
    QList<QHostAddress> interfaceAddressList = QNetworkInterface::allAddresses();

    qDebug()<<__FUNCTION__<<"hostName lookup addresses:"<<hostNameLookupAddressList;
    qDebug()<<__FUNCTION__<<"interface addresses:"<<interfaceAddressList;

    QHostAddress hostIp;
    foreach(QHostAddress addr, hostNameLookupAddressList){
        if(addr.protocol() == QAbstractSocket::IPv4Protocol && interfaceAddressList.contains(addr)){
            if(isLocalIpAddress(addr)){
                qDebug()<<__FUNCTION__<<addr<<" is local ip";
                hostIp = addr;
                break;
            }else if(isLinkLocalAddress(addr)){
                qDebug()<<__FUNCTION__<<addr<<" is Link Local Address";
                hostIp = addr;
            } else {
                qDebug() << __FUNCTION__ << addr << "is some different address";
            }
        }
    }

    return hostIp;
}