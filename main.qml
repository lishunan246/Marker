import QtQuick 2.7
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.0
import Qt.labs.folderlistmodel 2.1

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: qsTr("Hello World")
    visibility: "Maximized"

    FileDialog {
        id: fileDialogA
        title: "Please choose a file"
        folder: shortcuts.home
        onAccepted: {
            console.log("You chose: " + fileDialogA.fileUrls)
            marker.aDir=fileDialogA.folder;
        }
        onRejected: {
            console.log("Canceled")

        }
        selectFolder: true
        Component.onCompleted: visible = false
    }

    FileDialog {
        id: fileDialogB
        title: "Please choose a file"
        folder: shortcuts.home
        onAccepted: {
            console.log("You chose: " + fileDialogB.fileUrls)
            marker.bDir=fileDialogB.folder;
        }
        onRejected: {
            console.log("Canceled")

        }
        selectFolder: true
        Component.onCompleted: visible = false
    }

    ToolBar {
        height: 43
        RowLayout {
            anchors.fill: parent
            ToolButton {

            }
            ToolButton {

            }
            ToolButton {

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
        anchors.topMargin: 49
        anchors.fill: parent
        ListView
        {
            id:images
            width: 150
            Layout.fillHeight: true
            highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
            FolderListModel {
                id: folderModel
                folder: marker.aDir
                showDirs: false
                nameFilters: [ "*.png", "*.jpg" ,"*.bmp","*.jpeg"]
            }

            Component {
                id: fileDelegate

                Text {

                    text: fileName
                    MouseArea{
                        anchors.fill: parent
                        onClicked: images.currentIndex=index
                    }
                }
            }
            onCurrentItemChanged: {
                marker.filename=folderModel.get(currentIndex,"fileName");
                console.log(marker.filename);
            }

            model: folderModel
            delegate: fileDelegate
        }
        ColumnLayout
        {
            width: (parent.width-150)/2
            Layout.fillHeight:true
            RowLayout{
                height: 200
                Layout.fillWidth: true
                width: parent.width
                Button{
                    text: "浏览"
                    Layout.preferredWidth: 48
                    onClicked: {
                        fileDialogA.open();

                    }
                }
                Text {
                    id: train_dir
                    text: marker.aDir
                    Layout.fillWidth: true
                }
            }
            Canvas {
                property int xpos
                property int ypos
                Layout.fillHeight: true
                Layout.fillWidth: true
                id: image_a
                onPaint: {
                    var ctx = getContext("2d");
                    ctx.fillStyle = "red";
                    ctx.fillRect(xpos-1, ypos-1, 3, 3);
                }
                MouseArea
                {
                    anchors.fill:parent
                    onPressed: {
                        xpos = mouseX
                        ypos = mouseY
                        image_a.requestPaint()
                    }
                    onReleased:
                    {
                        image_a.
                    }

                    onMouseXChanged: {
                        xpos = mouseX
                        ypos = mouseY
                        image_a.requestPaint()
                    }
                    onMouseYChanged: {
                        xpos = mouseX
                        ypos = mouseY
                        image_a.requestPaint()
                    }
                }
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
                    onClicked: fileDialogB.open();
                }
                Text {
                    id: label_dir
                    text: marker.bDir
                    Layout.fillWidth: true
                }
            }
            Image {
                Layout.fillHeight: true
                Layout.fillWidth: true
                id: image_b
            }
        }
    }
}
