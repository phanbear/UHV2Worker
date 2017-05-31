#ifndef SERIALPORTINFOVALIDATION_H
#define SERIALPORTINFOVALIDATION_H

#include <QState>
#include <QSerialPortInfo>
#include "uhv2worker.h"

class SerialPortInfoValidation : public QState
{
public:
    SerialPortInfoValidation(UHV2Worker * parent, UHV2WorkerVarSet *VarSet);
    ~SerialPortInfoValidation();
protected:
    void onEntry(QEvent *) override;
private:
    UHV2Worker * parentPtr = Q_NULLPTR;
    UHV2WorkerVarSet *VarSetPtr = Q_NULLPTR;
};

#endif // SERIALPORTINFOVALIDATION_H