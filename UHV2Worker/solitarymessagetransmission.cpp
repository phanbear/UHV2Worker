#include "solitarymessagetransmission.h"

SolitaryMessageTransmission::SolitaryMessageTransmission(UHV2WorkerVarSet *VarSet, quint16 WriteTimeOutInMilisecond)
    : VarSetPtr(VarSet), TimeOut4WriteInMilisecond(WriteTimeOutInMilisecond)
{
    anDebug("=> Construct A New State !");
}

SolitaryMessageTransmission::~SolitaryMessageTransmission()
{
    VarSetPtr = Q_NULLPTR;
    delete VarSetPtr;
}

void SolitaryMessageTransmission::onEntry(QEvent *)
{
    anDebug("=> Enter State ...");
    qApp->processEvents();
    while (VarSetPtr->PendingMessageList->size())
    {
        if (VarSetPtr->PendingMessageList->last()->size())
            break;
        else
            VarSetPtr->PendingMessageList->remove(VarSetPtr->PendingMessageList->lastKey());
    }
    if (VarSetPtr->PendingMessageList->size())
    {
        VarSetPtr->lastTransmittedMessagePriority = VarSetPtr->PendingMessageList->lastKey();
        VarSetPtr->lastTransmittedMessage = VarSetPtr->PendingMessageList->last()->takeFirst();
        if (VarSetPtr->lastTransmittedMessage)
        {
            VarSetPtr->SerialPort->write(*(VarSetPtr->lastTransmittedMessage->first));
            if (VarSetPtr->SerialPort->waitForBytesWritten(TimeOut4WriteInMilisecond))
            {
                anDebug("=> Successfully Write Message !");
                emit VarSetPtr->Out(QVariant::fromValue(UHV2WorkerVarSet::AnUHV2PrioritizedCommandMessage),
                                    new QVariant(QVariant::fromValue(UHV2WorkerVarSet::PrioritizedCommandMessage(VarSetPtr->lastTransmittedMessagePriority, VarSetPtr->lastTransmittedMessage))));
            }
            else
            {
                anDebug("=> Writing Message Timed Out !");
                VarSetPtr->lastTransmittedMessage = Q_NULLPTR;
                emit VarSetPtr->Out(QVariant::fromValue(UHV2WorkerVarSet::MessageSendTimedOut));
            }
            emit VarSetPtr->DirectStateTransitionRequest("MessageReceiveAndEmitOut");
        }
    }
    else
    {
        anDebug("=> Wait For A Message !");
    }
}
