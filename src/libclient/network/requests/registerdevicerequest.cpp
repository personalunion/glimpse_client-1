#include "registerdevicerequest.h"
#include "types.h"

// TODO: Adjust types
#if defined(Q_OS_WIN)
#define OS "Windows"
#define TYPE RegisterDeviceRequest::Workstation
#elif defined(Q_OS_ANDROID)
#define OS "Android"
#define TYPE RegisterDeviceRequest::Phone
#elif defined(Q_OS_LINUX)
#define OS "Linux"
#define TYPE RegisterDeviceRequest::Workstation
#elif defined(Q_OS_MAC)
#define OS "Mac OS X"
#define TYPE RegisterDeviceRequest::Workstation
#endif

class RegisterDeviceRequest::Private
{
public:
    Private()
    : dataPlanDownlink(0)
    , deviceType(TYPE)
    , dataPlanUplink(0)
    {
    }

    QString dataPlanName;
    RegisterDeviceRequest::ProviderTechnology providerTechnology;
    QString deviceName;
    QString platform;
    RegisterDeviceRequest::DeviceType deviceType;
    QString provider;
    int maxAllowedTraffic;
    int dataPlanDownlink;
    int dataPlanUplink;
    QUuid deviceId;
};

RegisterDeviceRequest::RegisterDeviceRequest(QObject *parent)
: Request(parent)
, d(new Private)
{
}

RegisterDeviceRequest::~RegisterDeviceRequest()
{
    delete d;
}

QString RegisterDeviceRequest::dataPlanName() const {
  return d->dataPlanName;
}

void RegisterDeviceRequest::setDataPlanName(const QString& dataPlanName) {
  if (d->dataPlanName != dataPlanName) {
    d->dataPlanName = dataPlanName;
    emit dataPlanNameChanged(dataPlanName);
  }
}

RegisterDeviceRequest::ProviderTechnology RegisterDeviceRequest::providerTechnology() const {
  return d->providerTechnology;
}

void RegisterDeviceRequest::setProviderTechnology(ProviderTechnology providerTechnology) {
  if (d->providerTechnology != providerTechnology) {
    d->providerTechnology = providerTechnology;
    emit providerTechnologyChanged(providerTechnology);
  }
}

QString RegisterDeviceRequest::deviceName() const {
  return d->deviceName;
}

void RegisterDeviceRequest::setDeviceName(const QString& deviceName) {
  if (d->deviceName != deviceName) {
    d->deviceName = deviceName;
    emit deviceNameChanged(deviceName);
  }
}

QString RegisterDeviceRequest::platform() const {
  return d->platform;
}

void RegisterDeviceRequest::setPlatform(const QString& platform) {
  if (d->platform != platform) {
    d->platform = platform;
    emit platformChanged(platform);
  }
}

RegisterDeviceRequest::DeviceType RegisterDeviceRequest::deviceType() const {
  return d->deviceType;
}

void RegisterDeviceRequest::setDeviceType(DeviceType deviceType) {
  if (d->deviceType != deviceType) {
    d->deviceType = deviceType;
    emit deviceTypeChanged(deviceType);
  }
}

QString RegisterDeviceRequest::provider() const {
  return d->provider;
}

void RegisterDeviceRequest::setProvider(const QString& provider) {
  if (d->provider != provider) {
    d->provider = provider;
    emit providerChanged(provider);
  }
}

int RegisterDeviceRequest::maxAllowedTraffic() const {
  return d->maxAllowedTraffic;
}

void RegisterDeviceRequest::setMaxAllowedTraffic(int maxAllowedTraffic) {
  if (d->maxAllowedTraffic != maxAllowedTraffic) {
    d->maxAllowedTraffic = maxAllowedTraffic;
    emit maxAllowedTrafficChanged(maxAllowedTraffic);
  }
}

int RegisterDeviceRequest::dataPlanDownlink() const {
  return d->dataPlanDownlink;
}

void RegisterDeviceRequest::setDataPlanDownlink(int dataPlanDownlink) {
  if (d->dataPlanDownlink != dataPlanDownlink) {
    d->dataPlanDownlink = dataPlanDownlink;
    emit dataPlanDownlinkChanged(dataPlanDownlink);
  }
}

int RegisterDeviceRequest::dataPlanUplink() const {
  return d->dataPlanUplink;
}

void RegisterDeviceRequest::setDataPlanUplink(int dataPlanUplink) {
  if (d->dataPlanUplink != dataPlanUplink) {
    d->dataPlanUplink = dataPlanUplink;
    emit dataPlanUplinkChanged(dataPlanUplink);
  }
}

/*QUuid RegisterDeviceRequest::deviceId() const {
  return d->deviceId;
}*/

/*void RegisterDeviceRequest::setDeviceId(const QUuid& deviceId) {
  if (d->deviceId != deviceId) {
    d->deviceId = deviceId;
    emit deviceIdChanged(deviceId);
  }
}*/

QVariant RegisterDeviceRequest::toVariant() const {
  QVariantMap data;
  data.insert("data_plan_name", dataPlanName());
  data.insert("provider_technology", enumToString(RegisterDeviceRequest, "ProviderTechnology", providerTechnology()));
  data.insert("session_id", sessionId());
  data.insert("device_name", deviceName());
  data.insert("platform", platform());
  data.insert("device_type", enumToString(RegisterDeviceRequest, "DeviceType", deviceType()));
  data.insert("provider", provider());
  data.insert("max_allowed_traffic", maxAllowedTraffic());
  data.insert("data_plan_downlink", dataPlanDownlink());
  data.insert("data_plan_uplink", dataPlanUplink());
  data.insert("device_id", deviceId());
  data.insert("session_id", sessionId());
  return data;
}