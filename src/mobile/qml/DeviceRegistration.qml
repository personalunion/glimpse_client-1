import QtQuick 2.0
import mplane 1.0
import "android"
import "controls"

ListView {
    id: root
    property string title: "Device registration"
    property string subtitle: "blah ..."

    anchors.margins: units.gu(20)
    spacing: units.gu(10)

    WebRequester {
        id: requester

        request: RegisterDeviceRequest {
            id: request
        }

        response: RegisterDeviceResponse {
            id: response
        }

        onStatusChanged: {
            switch(status) {
            case WebRequester.Running:
                console.log("Device Registration sent")
                break;
            }
        }

        onError: {
            console.log("Device Registration error: " + requester.errorString())
            errorLabel.text = requester.errorString();
        }
        onFinished: {
            console.log("Device Registration finished")
            pageStack.pop();
        }
    }

    model: VisualItemModel {
        Label {
            width: root.width
            wrapMode: Text.Wrap
            text: qsTr("Please tell us something about your device")
        }

        Button {
            text: qsTr("Register Device")
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                requester.start()
            }
        }

        Text {
            id: errorLabel
            color: "red"
            font.pixelSize: units.gu(40)
            x: text.length > 0 ? parent.width/2-errorLabel.width/2 : parent.width
            width: root.width
            wrapMode: Text.Wrap

            Behavior on x {
                NumberAnimation {
                    easing.type: Easing.InBack
                    duration: 100
                }
            }
        }

        Spinner {
            anchors.horizontalCenter: parent.horizontalCenter
            running: requester.running
        }
    }
}
