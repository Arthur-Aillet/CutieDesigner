pragma ComponentBehavior: Bound
import QtQuick
import CutieDesigner.Nodes.Display

Item {
    id: mapPoints
    anchors.fill: parent
    required property MapPointsNode node

    Repeater {
        model: 17
        delegate: component
    }
    Component {
        id: component

        Rectangle {
            id: rect
            Component.onCompleted: {
                console.log("created?" + index);
            }
            required property int index
            property bool exists: index < mapPoints.node.points.length
            property bool animate: false

            onExistsChanged: {
                Qt.callLater(() => {
                    animate = exists;
                });
            }

            x: exists ? (mapPoints.node.points[index].x * mapPoints.width / 1280) - 5 : 0
            y: exists ? (mapPoints.node.points[index].y * mapPoints.height / 720) - 5 : 0
            Behavior on x {
                enabled: rect.animate
                PropertyAnimation {
                    duration: 50
                }
            }
            Behavior on y {
                enabled: rect.animate
                PropertyAnimation {
                    duration: 50
                }
            }
            width: 10
            height: 10
            color: exists ? "red" : "transparent"
        }
    }
}
