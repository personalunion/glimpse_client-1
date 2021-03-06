#ifndef UPNP_H
#define UPNP_H

#include "../measurement.h"
#include "upnp_definition.h"
#include <miniupnpc/miniupnpc.h>

#include <QStringList>
#include <QTimer>

class UPnP : public Measurement
{
    Q_OBJECT
    Q_ENUMS(DataType)

public:
    explicit UPnP(QObject *parent = 0);
    ~UPnP();
    // Measurement interface
    Status status() const;
    enum DataType
    {
        ExternalIpAddress,
        LanIpAddress,
        LinkLayerMaxUpload,
        LinkLayerMaxDownload,
        TotalBytesSent,
        TotalBytesReceived,
        TotalPacketsSent,
        TotalPacketsReceived,
        ConnectionType,
        NatType,
        Status,
        Uptime,
        LastConnectionError,
        NumberOfPortMappings,
        FirewallEnabled,
        InboundPinholeAllowed,
        ModelName,
        Manufacturer,
        FriendlyName,
        ControlUrl,
        EventSubUrl,
        ScpdUrl,
        ServiceType,
        FoundContent,
        URL,
        RootDescUrl,
        UDN
    };
    typedef QHash<DataType, QVariant> UPnPHash;


    bool prepare(NetworkManager *networkManager, const MeasurementDefinitionPtr &measurementDefinition);
    bool start();
    bool stop();
    Result result() const;
    QList<UPnPHash> goThroughDeviceList(UPNPDev * list);
    QList<UPnPHash> quickDevicesCheck(UPNPDev * list);

signals:
    void done();

private:
    QList<UPnPHash> results;
    QVariantList additional_res;

    UPnPDefinitionPtr definition;
    bool m_mediaServerSearch;
};

#endif // UPNP_H
