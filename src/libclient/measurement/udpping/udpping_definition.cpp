#include "udpping_definition.h"

UdpPingDefinition::UdpPingDefinition(const QString &url, const quint32 &count, const quint32 &interval, const quint32 &receiveTimeout,
                  const int &ttl, const quint16 &destinationPort, const quint16 &sourcePort, const quint32 &payload)
    : url(url),
    count(count),
    interval(interval),
    receiveTimeout(receiveTimeout),
    ttl(ttl),
    destinationPort(destinationPort),
    sourcePort(sourcePort),
    payload(payload)
{

}

UdpPingDefinition::~UdpPingDefinition()
{

}

UdpPingDefinitionPtr UdpPingDefinition::fromVariant(const QVariant &variant)
{
    QVariantMap map = variant.toMap();
    return UdpPingDefinitionPtr(new UdpPingDefinition(map.value("url").toString(),
                                                      map.value("count").toUInt(),
                                                      map.value("interval").toUInt(),
                                                      map.value("receiveTimeout").toUInt(),
                                                      map.value("ttl").toInt(),
                                                      map.value("destinationPort").toUInt(),
                                                      map.value("sourcePort").toUInt(),
                                                      map.value("payload").toUInt()));
}

QVariant UdpPingDefinition::toVariant() const
{
    QVariantMap map;
    map.insert("url", url);
    map.insert("count", count);
    map.insert("interval", interval);
    map.insert("receiveTimeout", receiveTimeout);
    map.insert("ttl", ttl);
    map.insert("destinationPort", destinationPort);
    map.insert("sourcePort", sourcePort);
    map.insert("payload", payload);
    return map;
}