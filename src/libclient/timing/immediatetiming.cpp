#include "immediatetiming.h"
#include "client.h"
#include "controller/ntpcontroller.h"

class ImmediateTiming::Private
{
public:
};

ImmediateTiming::ImmediateTiming()
: d(new Private)
{
}

ImmediateTiming::~ImmediateTiming()
{
    delete d;
}

bool ImmediateTiming::reset()
{
    return false;
}

QDateTime ImmediateTiming::nextRun(const QDateTime &tzero) const
{
    Q_UNUSED(tzero)
    return Client::instance()->ntpController()->currentDateTime();
}

bool ImmediateTiming::isValid() const
{
    return true;
}

QVariant ImmediateTiming::toVariant() const
{
    QVariantMap resultMap;
    resultMap.insert(type(), QVariantMap());
    return resultMap;
}

TimingPtr ImmediateTiming::fromVariant(const QVariant &variant)
{
    Q_UNUSED(variant);
    return TimingPtr(new ImmediateTiming);
}

QString ImmediateTiming::type() const
{
    return "immediate";
}
