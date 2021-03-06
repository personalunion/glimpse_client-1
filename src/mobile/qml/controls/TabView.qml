import QtQuick 2.0
import QtQml.Models 2.1
import mplane 1.0

Item {
    id: root

    property Item currentItem: listModel.children[currentIndex]
    property int currentIndex: 0
    default property alias content: listModel.children

    property alias contentWidth: contentView.width
    property alias contentHeight: contentView.height

    onCurrentIndexChanged: {
        listView.currentIndex = currentIndex;
        contentView.currentIndex = currentIndex;
    }

    ObjectModel {
        id: listModel

        onCountChanged: {
            var child = listModel.children[listModel.count-1];
            child.width = Qt.binding(function() { return contentView.width; });
            child.height = Qt.binding(function() { return contentView.height; });
        }
    }

    Rectangle {
        id: listViewBackground

        anchors {
            left: parent.left
            right: parent.right
        }
        height: units.gu(70)
        z: 1

        ListView {
            id: listView

            width: {
                if (root.width < contentWidth)
                    return root.width;
                else
                    return contentWidth;
            }

            currentIndex: root.currentIndex
            onCurrentIndexChanged: root.currentIndex = currentIndex

            height: parent.height
            orientation: ListView.Horizontal
            model: listModel.children
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            spacing: units.gu(15)
            boundsBehavior: ListView.StopAtBounds
            focus: true

            highlightMoveDuration: 300

            highlight: Item {
                   Rectangle {
                       height: units.gu(5)
                       width: parent.width
                       color: "#f8c580"
                   }
            }

            delegate: Label {
                id: nameText
                height: ListView.view.height
                verticalAlignment: Text.AlignVCenter
                text: model.title
                color: "#333333"
                font.pixelSize: units.gu(35)

                MouseArea {
                    anchors.fill: parent
                    onClicked: nameText.ListView.view.currentIndex = model.index
                }
            }
        }
    }

    ListView {
        id: contentView

        anchors {
            left: parent.left
            right: parent.right
            top: listViewBackground.bottom
            bottom: parent.bottom
        }

        highlightMoveDuration: 300

        currentIndex: root.currentIndex
        onCurrentIndexChanged: root.currentIndex = currentIndex

        highlightRangeMode: ListView.StrictlyEnforceRange

        snapMode: ListView.SnapOneItem
        orientation: ListView.Horizontal
        model: listModel
    }
}
