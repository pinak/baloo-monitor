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

using namespace BalooMonitor;
Monitor::Monitor(QObject *parent)
    : QObject(parent)
{
    QDBusConnection bus = QDBusConnection::sessionBus();
    bus.connect("", "/contentindexer", "org.kde.baloo", "startedWithFile", this, SLOT(newFile(QString)));
    bool m_running = bus.interface()->isServiceRegistered(QLatin1String("org.kde.baloo"));
}

void Monitor::newFile(QString url)
{
    m_url = url;
    Q_EMIT urlChanged();
}

QString Monitor::state() const
{
    return m_running ?  QStringLiteral("Suspend") : QStringLiteral("Resume");
}

void Monitor::toggleState()
{
    QString method;

    if (m_running) {
        method = QStringLiteral("suspend");
        m_running = false;
    } else {
        method = QStringLiteral("resume");
        m_running = true;
    }

    QDBusMessage message = QDBusMessage::createMethodCall(QLatin1String("org.kde.baloo"),
                                                          QLatin1String("/indexer"),
                                                          QLatin1String("org.kde.baloo"),
                                                          method);
    QDBusConnection::sessionBus().call(message);
    Q_EMIT stateChanged();
}

