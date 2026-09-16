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

        Path {
            id: pathBody1
            startX: pathCurve0.x
            startY: pathCurve0.y

            PathCurve {
                id: pathCurve8
                x: 0
                y: 0
            }
            PathCurve {
                id: pathCurve6
                x: 0
                y: 0
            }
            PathCurve {
                id: pathCurve5
                x: 0
                y: 0
            }
            PathCurve {
                id: pathCurve7
                x: 0
                y: 0
            }
            PathCurve {
                id: pathCurve9
                x: 0
                y: 0
            }
        }

        Path {
            id: pathBody2
            startX: pathCurve0.x
            startY: pathCurve0.y

            PathCurve {
                id: pathCurve56mid
                property real x5: 0
                property real x6: 0
                property real y5: 0
                property real y6: 0
                x: (x5 + x6) / 2
                y: (y5 + y6) / 2
            }
            PathCurve {
                id: pathCurve1112mid
                property real x11: 0
                property real x12: 0
                property real y11: 0
                property real y12: 0
                x: (x11 + x12) / 2
                y: (y11 + y12) / 2
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

            context.moveTo(pathBody1.startX, pathBody1.startY);
            context.beginPath();
            ABx = (pathBody1.startX - pathCurve8.x);
            ABy = (pathBody1.startY - pathCurve8.y);
            mag = Math.sqrt(ABx * ABx + ABy * ABy);
            size = mag * 0.025 + 2;
            cirleX = pathBody1.startX + ABx / mag * size;
            cirleY = pathBody1.startY + ABy / mag * size;
            context.arc(cirleX, cirleY, size, 0, 360, false);
            context.stroke();
            context.closePath();

            context.moveTo(pathCurve9.x, pathCurve9.y);
            context.beginPath();
            ABx = (pathCurve9.x - pathCurve7.x);
            ABy = (pathCurve9.y - pathCurve7.y);
            mag = Math.sqrt(ABx * ABx + ABy * ABy);
            size = mag * 0.025 + 2;
            cirleX = pathCurve9.x + ABx / mag * size;
            cirleY = pathCurve9.y + ABy / mag * size;
            context.arc(cirleX, cirleY, size, 0, 360, false);
            context.stroke();
            context.closePath();

            context.path = pathBody1;
            context.stroke();
            context.closePath();
            context.path = pathBody2;
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
                } else if (modelData.idx == 5) {
                    pathCurve56mid.x5 = x;
                    pathCurve5.x = x;
                } else if (modelData.idx == 6) {
                    pathCurve56mid.x6 = x;
                    pathCurve6.x = x;
                } else if (modelData.idx == 7) {
                    pathCurve7.x = x;
                } else if (modelData.idx == 8) {
                    pathCurve8.x = x;
                } else if (modelData.idx == 9) {
                    pathCurve9.x = x;
                } else if (modelData.idx == 10) {
                    pathBody1.startX = x;
                } else if (modelData.idx == 11) {
                    pathCurve1112mid.x11 = x;
                } else if (modelData.idx == 12) {
                    pathCurve1112mid.x12 = x;
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
                } else if (modelData.idx == 5) {
                    pathCurve56mid.y5 = y;
                    pathCurve5.y = y;
                } else if (modelData.idx == 6) {
                    pathCurve56mid.y6 = y;
                    pathCurve6.y = y;
                } else if (modelData.idx == 7) {
                    pathCurve7.y = y;
                } else if (modelData.idx == 8) {
                    pathCurve8.y = y;
                } else if (modelData.idx == 9) {
                    pathCurve9.y = y;
                } else if (modelData.idx == 10) {
                    pathBody1.startY = y;
                } else if (modelData.idx == 11) {
                    pathCurve1112mid.y11 = y;
                } else if (modelData.idx == 12) {
                    pathCurve1112mid.y12 = y;
                }
            }
            width: 10
            height: 10
            color: setColorAlpha(Qt.color("red"), confidence * 1.0)
        }
    }
}
