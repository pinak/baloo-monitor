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

#ifndef MONITOR_H
#define MONITOR_H

#include <QObject>
#include <QString>
#include <QDBusInterface>

namespace BalooMonitor {
class Monitor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString url READ url NOTIFY urlChanged)
    Q_PROPERTY(QString suspendState READ suspendState NOTIFY suspendStateChanged)
    Q_PROPERTY(bool balooRunning READ balooState NOTIFY balooStateChanged)
public:
    Monitor(QObject* parent = 0);

    // Property readers
    QString url() const { return m_url; }
    QString suspendState() const;
    bool balooState() const { return m_balooRunning; }

    Q_INVOKABLE void toggleSuspendState();

Q_SIGNALS:
    void urlChanged();
    void suspendStateChanged();
    void balooStateChanged();

private Q_SLOTS:
    void newFile(QString url);
    void balooStarted();

private:
    QDBusConnection m_bus;

    QString m_url;

    bool m_balooRunning;
    bool m_suspended;

    QDBusInterface* m_balooInterface;

};
}
#endif // MONITOR_H
