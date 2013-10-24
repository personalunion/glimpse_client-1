#include "schedulerstorage.h"
#include "scheduler.h"
#include "../storage/storagepaths.h"
#include "../log/logger.h"

#include <QDir>
#include <QPointer>
#include <QDebug>
#include <QCoreApplication>
#include <QJsonDocument>

LOGGER(SchedulerStorage);

class SchedulerStorage::Private : public QObject
{
    Q_OBJECT

public:
    Private()
    : loading(false)
    , dir(StoragePaths().schedulerDirectory())
    , realTime(true)
    {
        if (!dir.exists()) {
            QDir upper = dir;
            upper.cdUp();

            if (!upper.mkdir(dir.dirName())) {
                LOG_ERROR(QString("Unable to create path %1").arg(dir.absolutePath()));
            } else {
                LOG_INFO("Scheduler storage directory created");
            }
        }
    }

    // Properties
    bool loading;

    QPointer<Scheduler> scheduler;
    QDir dir;
    bool realTime;

    // Functions
    void store(const TestDefinitionPtr &test);
    QString fileNameForTest(const TestDefinitionPtr& test) const;

public slots:
    void testAdded(const TestDefinitionPtr &test, int position);
    void testRemoved(const TestDefinitionPtr &test, int position);
};

void SchedulerStorage::Private::store(const TestDefinitionPtr& test)
{
    QJsonDocument document = QJsonDocument::fromVariant(test->toVariant());

    QFile file(dir.absoluteFilePath(fileNameForTest(test)));
    if (file.open(QIODevice::WriteOnly)) {
        file.write(document.toJson());
        file.close();
    } else {
        LOG_ERROR(QString("Unable to open file: %1").arg(file.errorString()));
    }
}

QString SchedulerStorage::Private::fileNameForTest(const TestDefinitionPtr &test) const
{
    return test->id().toString();
}

void SchedulerStorage::Private::testAdded(const TestDefinitionPtr& test, int position)
{
    Q_UNUSED(position);

    if (!realTime || loading)
        return;

    store(test);
}

void SchedulerStorage::Private::testRemoved(const TestDefinitionPtr& test, int position)
{
    Q_UNUSED(position);

    if (!realTime)
        return;

    QString fileName = fileNameForTest(test);
    if (!dir.remove(fileName)) {
        LOG_WARNING(QString("Unable to remove file: %1").arg(dir.absoluteFilePath(fileName)));
    } else {
        LOG_DEBUG(QString("Deleted file: %1").arg(dir.absoluteFilePath(fileName)));
    }
}

SchedulerStorage::SchedulerStorage(Scheduler *scheduler, QObject *parent)
: QObject(parent)
, d(new Private)
{
    d->scheduler = scheduler;

    connect(scheduler, SIGNAL(testAdded(TestDefinitionPtr,int)), d, SLOT(testAdded(TestDefinitionPtr,int)));
    connect(scheduler, SIGNAL(testRemoved(TestDefinitionPtr,int)), d, SLOT(testRemoved(TestDefinitionPtr,int)));
}

SchedulerStorage::~SchedulerStorage()
{
}

void SchedulerStorage::setRealTime(bool realTime)
{
    d->realTime = realTime;
}

bool SchedulerStorage::isRealtime() const
{
    return d->realTime;
}

void SchedulerStorage::storeData()
{
    if (d->realTime)
        return;

    foreach(const TestDefinitionPtr& test, d->scheduler->tests())
        d->store(test);
}

void SchedulerStorage::loadData()
{
    d->loading = true;

    foreach(const QString& fileName, d->dir.entryList(QDir::Files)) {
        QFile file(d->dir.absoluteFilePath(fileName));
        file.open(QIODevice::ReadOnly);

        LOG_DEBUG(QString("Reading %1: %2").arg(d->dir.absoluteFilePath(fileName)).arg(file.errorString()));

        // TODO: Error checking
        QJsonParseError error;
        QJsonDocument document = QJsonDocument::fromJson(file.readAll(), &error);

        if (error.error == QJsonParseError::NoError) {
            TestDefinitionPtr test = TestDefinition::fromVariant(document.toVariant());
            d->scheduler->enqueue(test);
        } else {
            LOG_ERROR(QString("Error reading %1: %2").arg(d->dir.absoluteFilePath(fileName)).arg(error.errorString()));
        }
    }

    d->loading = false;
}

#include "schedulerstorage.moc"
