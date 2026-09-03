pragma ComponentBehavior: Bound
import QtQuick
import CutieDesigner.Nodes.Display

Item {
    id: mapPoints
    anchors.fill: parent
    required property MapPointsNode node

    Repeater {
        model: mapPoints.node.points
        Rectangle {
            required property int index
            x: (mapPoints.node.points[index].x * mapPoints.width / 1280) - 5
            y: (mapPoints.node.points[index].y * mapPoints.height / 720) - 5
            width: 10
            height: 10
            color: "red"
        }
    }
}
