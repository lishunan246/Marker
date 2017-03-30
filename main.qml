import QtQuick 2.7
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.4

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: qsTr("Hello World")
    visibility: "Maximized"
    ToolBar {
        height: 43
        RowLayout {
            anchors.fill: parent
            ToolButton {
                iconSource: "new.png"
            }
            ToolButton {
                iconSource: "open.png"
            }
            ToolButton {
                iconSource: "save-as.png"
            }
            Item { Layout.fillWidth: true }
            CheckBox {
                text: "Enabled"
                checked: true
                Layout.alignment: Qt.AlignRight
            }
        }
    }

    RowLayout {
        id: rowLayout
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 44
        anchors.fill: parent
        Rectangle
        {
            color:"#ff0000"
            width: 150
            Layout.fillHeight: true
        }
        ColumnLayout
        {
            width: (parent.width-150)/2
            Layout.fillHeight:true
            RowLayout{
                height: 200
                Layout.fillWidth: true
                Button{
                    text: "浏览"
                    Layout.preferredWidth: 48
                }
                Text {
                    id: train_dir
                    text: qsTr("text")
                    Layout.fillWidth: true
                }
            }
            Image {
                Layout.fillHeight: true
                Layout.fillWidth: true
                id: train_image
                source: "file"
            }
        }
        ColumnLayout
        {
            width: (parent.width-150)/2
            Layout.fillHeight:true
            RowLayout{
                height: 200
                Layout.fillWidth: true
                Button{
                    text: "浏览"
                    Layout.preferredWidth: 48
                }
                Text {
                    id: label_dir
                    text: qsTr("text")
                    Layout.fillWidth: true
                }
            }
            Image {
                Layout.fillHeight: true
                Layout.fillWidth: true
                id: a
                source: "file"
            }
        }
    }
}
