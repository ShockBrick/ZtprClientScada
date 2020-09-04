#include "clientapp.h"

ClientApp::ClientApp():ClientService()
{
    mathIndicator=&pars;
    mainWin.show();
    connect(this,&ClientApp::dataWereReceived,this,&ClientApp::updateMainWindowVector);//ClientService otrzymuje dane z serwera i dane mają być wyświetlone, więc przenoszone są do MainWnidow
    connect(&mainWin,&MainWindow::openService,this,&ClientApp::voidClientService);// Po nacisnięciu przycisku otwierane jest połączenie
    connect(this,&ClientApp::goToMainWindowWithData,&mainWin,&MainWindow::emitSignalsToDynamicChart);// przesyłane dane z MainWindow do DynamicChart
    connect(&mainWin,&MainWindow::signalStartSolveEquation,this,&ClientApp::StartPars);// wpisano wzór w interfejsie użytkownika i przesyłany jest do parsera
}

void ClientApp::StartPars()
{
    equation=mainWin.getEquation();
}

void ClientApp::updateMainWindowVector()
{
    for(auto &it:vSend)
    {
        mathIndicator->setEquatequationInfix(equation);
        mathIndicator->makeQueue();
        it.setValue(mathIndicator->countResult(it.getValue()));
    }
    mainWin.boringFunctionWriteVector(vSend);
    emit goToMainWindowWithData();
}


