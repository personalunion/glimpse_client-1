import QtQuick 2.0
import mplane 1.0
import QtQuick.Controls 1.0
import QtQuick.Window 2.0
import "android"

Rectangle {
    id: root
    width: 768
    height: 1200
    clip: true

    color: "#212126"

    property variant scheduler: client.scheduler

    Component.onCompleted: {
        // Initialize the client
        if ( !client.init() ) {
            console.log("Unable to initialize client");
            Qt.quit();
        }
    }

    // Implements back key navigation
    focus: true
    Keys.enabled: true
    Keys.onReleased: {
        if (event.key === Qt.Key_Plus)
            root.scale += 0.1
        if (event.key === Qt.Key_Minus)
            root.scale -= 0.1

        if (event.key === Qt.Key_Back) {
            if (pageStack.depth > 1) {
                pageStack.pop();
                event.accepted = true;
            } else { Qt.quit(); }
        }
    }

    Binding {
        target: statusBar
        property: "visible"
        value: client.scheduler.isStarted
    }

    Connections {
        target: client.scheduler
        onCurrentTestChanged: {
            if ( !currentTest )
                //loader.sourceComponent = undefined;
                return;
            else {
                var params = {
                    "test": currentTest
                }

                pageStack.push({item:Qt.resolvedUrl(currentTest.name + ".qml"), properties:params});
            }
        }
    }

    BorderImage {
        id: title
        border.bottom: 9
        source: "android/images/toolbar.png"
        width: parent.width
        height: 140
        z: 1

        BackButton {
            id: backButton
        }

        Text {
            id: applicationTitle
            font.pixelSize: 55
            Behavior on x { NumberAnimation{ easing.type: Easing.OutCubic} }
            x: backButton.x + backButton.width + 20
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -20
            color: "white"
            /*text: {
                var title = pageStack.currentItem.title;
                if (title)
                    return title;
                else
                    return "mPlane";
            }*/
        }

        Text {
            id: statusText
            font.pixelSize: 35
            x: applicationTitle.x + 30
            anchors.top: applicationTitle.bottom
            anchors.topMargin: -5
            color: "lightgray"
            /*text: {
                var subtitle = pageStack.currentItem.subtitle;
                if (subtitle)
                    return subtitle;
                else
                    return client.status == Client.Registered ? qsTr("Registered") : qsTr("Unregistered")
            }*/
        }
    }

    StackView {
        id: pageStack
        anchors {
            top: title.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        delegate: StackViewDelegate {
            function transitionFinished(properties)
            {
                properties.exitItem.x = 0
            }

            property Component pushTransition: StackViewTransition {
                PropertyAnimation {
                    target: enterItem
                    property: "x"
                    from: enterItem.width
                    to: 0
                    duration: 100
                }
                PropertyAnimation {
                    target: exitItem
                    property: "x"
                    from: 0
                    to: -exitItem.width
                    duration: 100
                }
            }

            property Component popTransition: StackViewTransition {
                PropertyAnimation {
                    target: enterItem
                    property: "x"
                    from: -enterItem.width
                    to: 0
                    duration: 100
                }
                PropertyAnimation {
                    target: exitItem
                    property: "x"
                    from: 0
                    to: exitItem.width
                    duration: 100
                }
            }
        }

        onCurrentItemChanged: {
            applicationTitle.text = currentItem.title;
            statusText.text = currentItem.subtitle;
        }

        /*initialItem: ListView {
            property string title: "Glimpse"
            property string subtitle: client.status == Client.Registered ? qsTr("Registered") : qsTr("Unregistered")

            model: ListModel {
                ListElement {
                    title: "Internet is not working"
                    page: "Settings.qml"
                }

                ListElement {
                    title: "Internet is slow"
                    page: "Settings.qml"
                }

                ListElement {
                    title: "Manual tests"
                    page: "Tests.qml"
                }
            }

            delegate: AndroidDelegate {
                text: title
                onClicked: pageStack.push(Qt.resolvedUrl(page))
            }
        }*/

        initialItem: Item {
            property string title: "Glimpse"
            property string subtitle: "Master server offline."

            Column {
                anchors {
                    left: parent.left
                    right: parent.right
                    top: parent.top
                    margins: 20
                }

                spacing: 50

                Button {
                    text: "Registration"
                    anchors.horizontalCenter: parent.horizontalCenter
                    style: ButtonStyle {}
                    onClicked: pageStack.push(Qt.resolvedUrl("UserRegistration.qml"))
                }

                Button {
                    text: "Login"
                    anchors.horizontalCenter: parent.horizontalCenter
                    style: ButtonStyle {}
                    onClicked: pageStack.push(Qt.resolvedUrl("Login.qml"))
                }

                Button {
                    text: "Internet is not working"
                    anchors.horizontalCenter: parent.horizontalCenter
                    style: ButtonStyle {}
                    onClicked: pageStack.push(Qt.resolvedUrl("Settings.qml"))
                }

                Button {
                    text: "Internet is slow"
                    anchors.horizontalCenter: parent.horizontalCenter
                    style: ButtonStyle {}
                    onClicked: pageStack.push(Qt.resolvedUrl("Slow.qml"))
                }

                Button {
                    text: "Speedtest"
                    anchors.horizontalCenter: parent.horizontalCenter
                    style: ButtonStyle {}
                    onClicked: client.speedTest()
                }
            }
        }
    }
}
