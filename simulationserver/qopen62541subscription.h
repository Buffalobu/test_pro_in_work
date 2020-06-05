/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtOpcUa module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL3$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QOPEN62541SUBSCRIPTION_H
#define QOPEN62541SUBSCRIPTION_H

#include "qopen62541.h"
#include <QtOpcUa/qopcuanode.h>

QT_BEGIN_NAMESPACE

class Open62541AsyncBackend;

class QOpen62541Subscription : public QObject
{
    Q_OBJECT

public:
    QOpen62541Subscription(Open62541AsyncBackend *backend, const QOpcUaMonitoringParameters &settings);
    ~QOpen62541Subscription();

    UA_UInt32 createOnServer();
    bool removeOnServer();

    void modifyMonitoring(quint64 handle, QOpcUa::NodeAttribute attr, QOpcUaMonitoringParameters::Parameter item, QVariant value);

    bool addAttributeMonitoredItem(quint64 handle, QOpcUa::NodeAttribute attr, const UA_NodeId &id, QOpcUaMonitoringParameters settings);
    bool removeAttributeMonitoredItem(quint64 handle, QOpcUa::NodeAttribute attr);

    void monitoredValueUpdated(UA_UInt32 monId, UA_DataValue *value);
    void eventReceived(UA_UInt32 monId, QVariantList list);

    void sendTimeoutNotification();

    struct MonitoredItem {
        quint64 handle;
        QOpcUa::NodeAttribute attr;
        UA_UInt32 monitoredItemId;
        UA_UInt32 clientHandle;
        QOpcUaMonitoringParameters parameters;
        MonitoredItem(quint64 h, QOpcUa::NodeAttribute a, UA_UInt32 id)
            : handle(h)
            , attr(a)
            , monitoredItemId(id)
        {}
        MonitoredItem()
            : handle(0)
            , monitoredItemId(0)
        {}
    };

    double interval() const;
    UA_UInt32 subscriptionId() const;
    int monitoredItemsCount() const;

    QOpcUaMonitoringParameters::SubscriptionType shared() const;

signals:
    void timeout(QOpen62541Subscription *sub, QVector<QPair<quint64, QOpcUa::NodeAttribute>> items);

private:
    MonitoredItem *getItemForAttribute(quint64 nodeHandle, QOpcUa::NodeAttribute attr);
    UA_ExtensionObject createFilter(const QVariant &filterData);
    void createDataChangeFilter(const QOpcUaMonitoringParameters::DataChangeFilter &filter, UA_ExtensionObject *out);
    void createEventFilter(const QOpcUaMonitoringParameters::EventFilter &filter, UA_ExtensionObject *out);
    bool convertSelectClause(const QOpcUaMonitoringParameters::EventFilter &filter,
                             UA_SimpleAttributeOperand **selectClauses, size_t *size);
    bool convertWhereClause(const QOpcUaMonitoringParameters::EventFilter &filter, UA_ContentFilter *result);

    bool modifySubscriptionParameters(quint64 nodeHandle, QOpcUa::NodeAttribute attr, const QOpcUaMonitoringParameters::Parameter &item, const QVariant &value);
    bool modifyMonitoredItemParameters(quint64 nodeHandle, QOpcUa::NodeAttribute attr, const QOpcUaMonitoringParameters::Parameter &item, const QVariant &value);
    QOpcUaEventFilterResult convertEventFilterResult(UA_ExtensionObject *obj);

    Open62541AsyncBackend *m_backend;
    double m_interval;
    UA_UInt32 m_subscriptionId;
    UA_UInt32 m_lifetimeCount;
    UA_UInt32 m_maxKeepaliveCount;
    QOpcUaMonitoringParameters::SubscriptionType m_shared;
    quint8 m_priority;
    quint32 m_maxNotificationsPerPublish;

    QHash<quint64, QHash<QOpcUa::NodeAttribute, MonitoredItem *>> m_nodeHandleToItemMapping; // Handle -> Attribute -> MonitoredItem
    QHash<UA_UInt32, MonitoredItem *> m_itemIdToItemMapping; // ItemId -> Item for fast lookup on data change

    quint32 m_clientHandle;
    bool m_timeout;
};

QT_END_NAMESPACE

#endif // QOPEN62541SUBSCRIPTION_H