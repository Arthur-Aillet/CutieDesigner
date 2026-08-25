import QtQuick
import QtQuick.Layouts

import NodeEditor

Item {
    id: nodeView

    property DataFlowContext dataFlowContext
    property alias graphicsView: graphicsView

    Layout.fillWidth: true
    Layout.fillHeight: true

    DefaultControlsView {
        id: graphicsView
        height: parent.height - timeline.height
        anchors.left: parent.left
        anchors.right: parent.right
        dataFlowContext: nodeView.dataFlowContext
    }

    Timeline {
        id: timeline
        anchors.top: graphicsView.bottom
        anchors.left: parent.left
        anchors.right: parent.right
    }
}
