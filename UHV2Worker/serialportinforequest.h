#ifndef SERIALPORTINFOREQUEST_H
#define SERIALPORTINFOREQUEST_H

#include <QState>
#include <QTimer>
#include "anlogger.h"
#include "uhv2workervarset.h"

class SerialPortInfoRequest : public QState
{
public:
    SerialPortInfoRequest(UHV2WorkerVarSet *VarSet, quint32 TimerIntervalInMilisecond = 0);
protected:
    void onEntry(QEvent *) override;
    void onExit(QEvent *) override;
private:
    QTimer timer;
    quint32 TimerIntervalMSecs = 0;
};

#endif // SERIALPORTINFOREQUEST_H
