#ifndef TIMING_H
#define TIMING_H

#include "../serializable.h"

#include <QDateTime>
#include <QSharedPointer>


class Timing;
typedef QSharedPointer<Timing> TimingPtr;

class CLIENT_API Timing : public Serializable
{
public:
    qint64 timeLeft(const QDateTime &when = QDateTime::currentDateTime()) const;
    QDateTime lastExecution();

    virtual ~Timing() {}

    virtual QString type() const = 0;
    virtual bool reset() = 0; // true = reset; false = stop execute
    virtual QDateTime nextRun(const QDateTime &tzero = QDateTime()) const = 0;
    virtual bool isValid() const = 0;

protected:
    QDateTime m_lastExecution;
};

#endif // TIMING_H
