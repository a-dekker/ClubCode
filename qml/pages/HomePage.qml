import QtQuick 2.0
import Sailfish.Silica 1.0


Page
{
    id: page

    SilicaFlickable
    {
        anchors.fill: parent

        PullDownMenu
        {
            MenuItem
            {
                text: qsTr("About")
                onClicked: pageStack.push(Qt.resolvedUrl("About.qml"))
            }
            MenuItem
            {
                text: qsTr("Add a new Code")
                onClicked: pageStack.push(Qt.resolvedUrl("AddNewCodePage.qml"))
            }
        }

        SilicaListView
        {
            anchors.fill: parent
            model: main.codes
            spacing: 7
            header: PageHeader
            {
                title: qsTr("Barcodes")
            }

            VerticalScrollDecorator {
            }

            delegate: Item
            {

                width: page.width
                height: menu.active ? menu.height + 130 * mainApp.sizeRatio: 130 * mainApp.sizeRatio
                id: item

                function getFontName() {
                    if (modelData.barcodeType === "0") {
                        return "Code 128"
                    }
                    if (modelData.barcodeType === "1") {
                        return "Code EAN13"
                    }
                    if (modelData.barcodeType === "2") {
                        return "Code EAN13"
                    }
                    if (modelData.barcodeType === "3") {
                        return "Bar-Code 39"
                    }
                    if (modelData.barcodeType === "4") {
                        return "Code-93"
                    }
                    if (modelData.barcodeType === "5") {
                        return "UPC-E Short"
                    }
                }

                ContextMenu
                {
                    id: menu

                    MenuItem
                    {
                        text: qsTr("Edit")
                        onClicked: pageStack.push(Qt.resolvedUrl("EditCodePage.qml"), { current: modelData })
                    }
                    MenuItem
                    {
                        text: qsTr("Remove")
                        onClicked: Remorse.itemAction(item, "Deleting", function() { main.removeCode(modelData) } )
                    }
                }

                Rectangle
                {
                    height: 130 * mainApp.sizeRatio
                    width: parent.width
                    color: "white"


                    Label
                    {
                        color: "gray"
                        font.family: getFontName()
                        anchors.centerIn: parent
                        font.pixelSize: 100 * mainApp.sizeRatio
                        text: modelData.generateCode(modelData.code, modelData.barcodeType)
                        font.letterSpacing: 0
                        opacity: 0.3
                        anchors.verticalCenterOffset: -6
                    }

                    Column
                    {
                        anchors.centerIn: parent

                        Label
                        {
                            text: modelData.name
                            color: "black"
                            font.bold: true
                            anchors.horizontalCenter: parent.horizontalCenter
                        }

                        Label
                        {
                            text: modelData.description
                            color: "black"
                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                    }

                    BackgroundItem
                    {
                        width: parent.width
                        height: parent.height
                        onClicked: pageStack.push(Qt.resolvedUrl("ViewCodePage.qml"), { current: modelData })
                        onPressAndHold: menu.open(item)
                    }
                }
            }
        }
    }
}
