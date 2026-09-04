pragma ComponentBehavior: Bound
import QtQuick
import CutieDesigner.Nodes.Display

Item {
    id: mapPoints
    anchors.fill: parent
    required property MapPointsNode node

    Repeater {
        id: points
        model: 17
        delegate: component
    }

    Canvas {
        id: canvas
        anchors.fill: parent

        contextType: "2d"
        Path {
            id: myPath
            startX: 0
            startY: 0

            PathCurve {
                id: pathCurve2
                x: 0
                y: 0
            }
            PathCurve {
                id: pathCurve0
                x: 0
                y: 0
            }
            PathCurve {
                id: pathCurve1
                x: 0
                y: 0
            }
            PathCurve {
                id: pathCurve3
                x: 0
                y: 0
            }
        }

        onPaint: () => {
            context.clearRect(0, 0, mapPoints.width, mapPoints.height);
            context.strokeStyle = "black";
            context.lineWidth = 2;
            context.path = myPath;
            context.stroke();
            context.closePath();

            context.moveTo(myPath.startX, myPath.startY);
            context.beginPath();
            let ABx = (myPath.startX - pathCurve2.x);
            let ABy = (myPath.startY - pathCurve2.y);
            let mag = Math.sqrt(ABx * ABx + ABy * ABy);
            let size = mag * 0.025 + 2;
            let cirleX = myPath.startX + ABx / mag * size;
            let cirleY = myPath.startY + ABy / mag * size;
            context.arc(cirleX, cirleY, size, 0, 360, false);
            context.stroke();
            context.closePath();

            context.moveTo(pathCurve3.x, pathCurve3.y);
            context.beginPath();
            ABx = (pathCurve3.x - pathCurve1.x);
            ABy = (pathCurve3.y - pathCurve1.y);
            mag = Math.sqrt(ABx * ABx + ABy * ABy);
            size = mag * 0.025 + 2;
            cirleX = pathCurve3.x + ABx / mag * size;
            cirleY = pathCurve3.y + ABy / mag * size;
            context.arc(cirleX, cirleY, size, 0, 360, false);
            context.stroke();
            context.closePath();
        }
    }

    SurfaceLoader {
        surfaceData: mapPoints.node.surface
        anchored: false
        clip: false

        width: 100
        height: 100
        x: mapPoints.node.points[0] == undefined ? 0 : (mapPoints.node.points[0].position.x * mapPoints.width / 1280.0 - 50)
        y: mapPoints.node.points[0] == undefined ? 0 : (mapPoints.node.points[0].position.y * mapPoints.height / 720.0 - 50)
    }

    Component {
        id: component

        Rectangle {
            id: rect
            required property int index
            property var confidence: modelData == undefined ? 0 : modelData.confidence
            property var modelData: mapPoints.node.points[index]

            onModelDataChanged: {
                if (modelData == undefined)
                    return;
                x = (modelData.position.x * mapPoints.width / 1280.0) - 5;
                y = (modelData.position.y * mapPoints.height / 720.0) - 5;
            }

            Behavior on x {
                SmoothedAnimation {
                    duration: 50
                }
            }

            Behavior on y {
                SmoothedAnimation {
                    duration: 50
                }
            }

            function setColorAlpha(color, alpha) {
                return Qt.hsla(color.hslHue, color.hslSaturation, color.hslLightness, alpha);
            }

            onXChanged: {
                if (modelData.idx == 0) {
                    pathCurve0.x = x;
                    canvas.requestPaint();
                } else if (modelData.idx == 1) {
                    pathCurve1.x = x;
                } else if (modelData.idx == 2) {
                    pathCurve2.x = x;
                } else if (modelData.idx == 3) {
                    pathCurve3.x = x;
                } else if (modelData.idx == 4) {
                    myPath.startX = x;
                }
            }
            onYChanged: {
                if (modelData.idx == 0) {
                    pathCurve0.y = y;
                } else if (modelData.idx == 1) {
                    pathCurve1.y = y + 5;
                } else if (modelData.idx == 2) {
                    pathCurve2.y = y;
                } else if (modelData.idx == 3) {
                    pathCurve3.y = y;
                } else if (modelData.idx == 4) {
                    myPath.startY = y;
                }
            }
            width: 10
            height: 10
            color: setColorAlpha(Qt.color("red"), confidence * 1.0)
        }
    }
}
