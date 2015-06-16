/*
 * This file is part of the KDE Baloo Project
 * Copyright (C) 2015  Pinak Ahuja <pinak.ahuja@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) version 3, or any
 * later version accepted by the membership of KDE e.V. (or its
 * successor approved by the membership of KDE e.V.), which shall
 * act as a proxy defined in Section 6 of version 3 of the license.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "monitor.h"

#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusConnectionInterface>
#include <QDebug>

using namespace BalooMonitor;
Monitor::Monitor(QObject *parent)
    : QObject(parent)
    , m_bus(QDBusConnection::sessionBus())
    , m_balooInterface(0)
{
    m_bus.connect("", "/contentindexer", "org.kde.baloo", "startedWithFile", this, SLOT(newFile(QString)));
    //TODO: export signal from baloo to let the monitor know it has started and connect it to balooStarted()

    if (m_bus.interface()->isServiceRegistered(QLatin1String("org.kde.baloo"))) {
        // baloo is already running
        balooStarted();
    } else {
        m_balooRunning = false;
    }
}

void Monitor::newFile(QString url)
{
    m_url = url;
    Q_EMIT urlChanged();
}

QString Monitor::suspendState() const
{
    return m_suspended ?  QStringLiteral("Resume") : QStringLiteral("Suspend");
}

void Monitor::toggleSuspendState()
{
    Q_ASSERT(m_balooInterface != 0);

    QString method;
    if (m_suspended) {
        method = QStringLiteral("resume");
        m_suspended = false;
    } else {
        method = QStringLiteral("suspend");
        m_suspended = true;
    }

    m_balooInterface->call(method);
    Q_EMIT suspendStateChanged();
}

void Monitor::balooStarted()
{
    /*
     * TODO: send a dbus signal to baloo to let it know montitor is running,
     * use that signal in baloo to enable exporting urls being indexed
     */

    m_balooRunning = true;

    //TODO: use interface generated from XML file
    m_balooInterface = new QDBusInterface(QStringLiteral("org.kde.baloo"),
                                            QStringLiteral("/indexer"),
                                            QStringLiteral("org.kde.baloo"),
                                            m_bus,
                                            this);

    QDBusReply<bool> suspended = m_balooInterface->call("isSuspended");
    m_suspended = suspended.value();

    Q_EMIT balooStateChanged();
    Q_EMIT suspendStateChanged();
}


