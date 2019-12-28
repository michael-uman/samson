import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import com.wunderbar.app 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    MyApp {
        id: myapp
    }

    ColumnLayout {
        anchors.fill: parent

        Text {
            text: "qmlSamson " + myapp.crashCount
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.pointSize: 24; font.bold: true; font.italic: true
        }

        RowLayout {
            anchors.horizontalCenter: parent.horizontalCenter
//            height: 32
            Button {
                id: segfault
                text: "Seg Fault"
                onClicked: {
                    myapp.doSegfault()
                }
            }

            Button {
                id: dividebyzero
                text: "Divide By 0"
                onClicked: {
                    myapp.doDivideByZero()
                }
            }

            Button {
                id: abort
                text: "abort()"
                onClicked: {
                    myapp.doAbort()
                }
            }
        }
    }
}
