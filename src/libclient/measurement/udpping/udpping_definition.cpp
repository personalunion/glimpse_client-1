#include "udpping_definition.h"
#include "../../types.h"

UdpPingDefinition::UdpPingDefinition(const QString &host, const quint32 &count, const quint32 &interval,
                                     const quint32 &receiveTimeout, const int &ttl,
                                     const quint16 &destinationPort, const quint16 &sourcePort,
                                     const quint32 &payload, const QAbstractSocket::SocketType &pingType)
: host(host)
, count(count)
, interval(interval)
, receiveTimeout(receiveTimeout)
, ttl(ttl)
, destinationPort(destinationPort)
, sourcePort(sourcePort)
, payload(payload)
, pingType(pingType)
{

}

UdpPingDefinition::~UdpPingDefinition()
{

}

UdpPingDefinitionPtr UdpPingDefinition::fromVariant(const QVariant &variant)
{
    QVariantMap map = variant.toMap();
    return UdpPingDefinitionPtr(new UdpPingDefinition(map.value("host", "").toString(),
                                                      map.value("count", 3).toUInt(),
                                                      map.value("interval", 1000).toUInt(),
                                                      map.value("timeout", 1000).toUInt(),
                                                      map.value("ttl", 64).toInt(),
                                                      map.value("destination_port", 33434).toUInt(),
                                                      map.value("source_port", 33434).toUInt(),
                                                      map.value("payload", 74).toUInt(),
                                                      enumFromString(QAbstractSocket, SocketType,
                                                                     map.value("pingType",
                                                                               "UdpSocket").toString().toLatin1())));
}

QVariant UdpPingDefinition::toVariant() const
{
    QVariantMap map;
    map.insert("host", host);
    map.insert("count", count);
    map.insert("interval", interval);
    map.insert("timeout", receiveTimeout);
    map.insert("ttl", ttl);
    map.insert("destination_port", destinationPort);
    map.insert("source_port", sourcePort);
    map.insert("payload", payload);
    map.insert("pingType", enumToString(QAbstractSocket, SocketType, pingType));
    return map;
}
