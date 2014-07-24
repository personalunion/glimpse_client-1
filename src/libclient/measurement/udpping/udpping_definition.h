#ifndef UDPPING_DEFINITION_H
#define UDPPING_DEFINITION_H

#include "../measurementdefinition.h"
#include "../../types.h"
#include <QAbstractSocket>

class UdpPingDefinition;

typedef QSharedPointer<UdpPingDefinition> UdpPingDefinitionPtr;
typedef QList<UdpPingDefinitionPtr> UdpPingDefinitionList;

class UdpPingDefinition : public MeasurementDefinition
{
public:
    ~UdpPingDefinition();
    UdpPingDefinition(const QString &host, const quint32 &count, const quint32 &interval, const quint32 &receiveTimeout,
                      const int &ttl, const quint16 &destinationPort, const quint16 &sourcePort, const quint32 &payload,
                      const ping::PingType &pingType);

    // Storage
    static UdpPingDefinitionPtr fromVariant(const QVariant &variant);

    // Getters
    QString host;
    quint32 count;
    quint32 interval;
    quint32 receiveTimeout;
    int ttl;
    quint16 destinationPort;
    quint16 sourcePort;
    quint32 payload;
    ping::PingType pingType;

    // Serializable interface
    QVariant toVariant() const;
};

#endif // UDPPING_DEFINITION_H
