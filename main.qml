import QtQuick 2.7
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.0
import Qt.labs.folderlistmodel 2.1
import QtQuick.Controls.Material 2.0

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: (marker.filename?marker.filename:"Marker")+(marker.dirty?"*":"")
    visibility: "Maximized"
    onClosing:
    {
        if(marker.dirty)
            marker.saveImageB();
    }

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
            Text {
                id: text1
                text: qsTr("画笔大小")
                font.pixelSize: 12
            }

            SpinBox {
                id: spinBox3
                maximumValue: 99
                minimumValue: 0
                value: marker.penSize
                onValueChanged: marker.penSize = value
            }

            Text {
                id: text2
                text: qsTr("R")
                font.pixelSize: 12
            }

            SpinBox {
                id: spinBox2
                maximumValue: 255
                minimumValue: 0
                value: marker.r
                onValueChanged: marker.r = value
            }

            Text {
                id: text4
                text: qsTr("G")
                font.pixelSize: 12
            }

            SpinBox {
                id: spinBox1
                maximumValue: 255
                minimumValue: 0
                value: marker.g
                onValueChanged: marker.g = value
            }

            Text {
                id: text3
                text: qsTr("B")
                font.pixelSize: 12
            }

            SpinBox {
                id: spinBox
                maximumValue: 255
                minimumValue: 0
                value: marker.b
                onValueChanged: marker.b = value
            }
        }
    }

    RowLayout {
        id: rowLayout
        spacing: 0
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
                image_a.refresh();
                image_b.refresh();
            }

            model: folderModel
            delegate: fileDelegate
        }
        ColumnLayout
        {
            width: (parent.width-150)/2
            Layout.minimumWidth: (parent.width-150)/2
            Layout.maximumWidth: (parent.width-150)/2
            Layout.fillWidth: true
            spacing: 0
            Layout.fillHeight:true
            RowLayout{
                height: 200
                spacing: 0
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
            Image {
                property int xpos
                property int ypos
                property bool drawing: false
                Layout.fillHeight: true
                Layout.fillWidth: true
                id: image_a
                source:"image://image/a"
                cache: false
                fillMode: Image.PreserveAspectFit

                function refresh(){
                    var t=source;
                    source="";
                    source=t;
                    console.log(t+" refreshed.");
                    marker.realWidth=image_a.paintedWidth;
                    marker.realHeight=image_a.paintedHeight;
                }

                MouseArea
                {
                    anchors.centerIn: parent
                    width: image_a.paintedWidth
                    height: image_a.paintedHeight

                    onPressed: {
                        image_a.xpos = mouseX
                        image_a.ypos = mouseY
                        image_a.drawing=true;
                        marker.draw(image_a.xpos,image_a.y.pos);
                        image_a.refresh();
                        image_b.refresh();
                    }
                    onReleased:
                    {
                        image_a.drawing=false;
                    }

                    onMouseXChanged: {
                        image_a.xpos = mouseX
                        image_a.ypos = mouseY
                        if(image_a.drawing)
                        {
                            marker.draw(image_a.xpos,image_a.ypos);
                            image_a.refresh();
                            image_b.refresh();
                        }
                    }
                    onMouseYChanged: {
                        image_a.xpos = mouseX
                        image_a.ypos = mouseY
                        if(image_a.drawing)
                        {
                            marker.draw(image_a.xpos,image_a.ypos);
                            image_a.refresh();
                            image_b.refresh();
                        }
                    }
                }
            }
        }
        ColumnLayout
        {
            width: (parent.width-150)/2
            Layout.minimumWidth: (parent.width-150)/2
            Layout.maximumWidth: (parent.width-150)/2
            Layout.fillWidth: true
            spacing: 0
            Layout.fillHeight:true
            RowLayout{
                height: 200
                spacing: 0
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
                source:"image://image/b"
                cache: false

                fillMode: Image.PreserveAspectFit

                function refresh(){

                    var t=source;

                    source="";

                    source=t;

                    console.log(t+" refreshed.");

                }
            }
        }
    }
}
