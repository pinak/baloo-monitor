import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1

ApplicationWindow {
    title: qsTr("Baloo Monitor")
    width: 640
    height: 480
    visible: true


    Text {
        anchors.top: parent.top
        anchors.margins: 10
        x: 10
        id: url
        text: "Indexing: " + monitor.url
    }


    RowLayout {
        spacing: 20
        anchors.top: url.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 10

        ProgressBar {
            id: progress
            x: 10
            Layout.fillWidth: true
            indeterminate: true
        }

        Button {
            id: toggleButton
            text: monitor.state
            onClicked: monitor.toggleState()
        }
    }
}
