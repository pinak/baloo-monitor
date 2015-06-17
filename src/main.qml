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

import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1

import org.kde.plasma.components 2.0 as PlasmaComponents
import org.kde.plasma.extras 2.0 as PlasmaExtras

ApplicationWindow {
    title: qsTr("Baloo Monitor")
    width: 640
    height: 480
    visible: true

    GridLayout {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 10
        visible: monitor.balooRunning

        columns: 2
        columnSpacing: 20
        rowSpacing: 20

        PlasmaComponents.Label {
            Layout.columnSpan: 2
            anchors.top: parent.top
            anchors.margins: 10
            x: 10
            id: url
            text: "Indexing: " + monitor.url
        }


        PlasmaComponents.ProgressBar {
            id: progress
            Layout.fillWidth: true
            indeterminate: true
        }

        PlasmaComponents.Button {
            id: toggleButton
            text: monitor.suspendState
            onClicked: monitor.toggleSuspendState()
        }
    }

    PlasmaExtras.Heading {
        visible: !monitor.balooRunning

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        text: qsTr("Baloo is not running!")
    }
}
