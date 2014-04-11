import QtQuick 2.0
import picviewer 1.0

Rectangle
{
    id: backRect
    width: 800
    height: 600
    color: "black"

    PicViewer
    {
        id: picViewer
        objectName: "QmlPic"
        width: backRect.width
        height: backRect.height
        anchors.verticalCenter: parent.verticalCenter
    }

    Image
    {
        id: leftButt
        objectName: "leftButton"
        source: "qrc:/img/resources/leftButton.png"

        width: 40
        height: 40
        x: backRect.x + 20
        opacity: 0
        anchors.verticalCenter: backRect.verticalCenter

        signal clickedLeftButt()

        MouseArea
        {
            id: leftButtonArea
            anchors.fill: leftButt
            onClicked: leftButt.clickedLeftButt();
        }
    }

    Image
    {
        id: rightButt
        objectName: "rightButton"
        source: "qrc:/img/resources/rightButton.png"

        width: 40
        height: 40
        x: backRect.width - width - 20
        opacity: 0
        anchors.verticalCenter: backRect.verticalCenter

        signal clickedRightButt()

        MouseArea
        {
            id: rightButtonArea
            anchors.fill: rightButt
            onClicked: rightButt.clickedRightButt();
        }
    }

    AnimatedImage
    {
        id: animLoad
        objectName: "animLoading"
        source: "qrc:/img/resources/loading.gif"
        anchors.centerIn: backRect
        opacity: 0
        width: 50
        height: 50

        function showLoading()
        {
            opacity = 1.0;
        }
        function hideLoading()
        {
            opacity = 0.0;
        }

    }
}
