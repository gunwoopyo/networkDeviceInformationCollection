#include "PortWorker.h"
#include "Router.h"

void PortWorker::portProcess() {

    for(Port &port : Router::routerPtr->ports) {
        port.fetchPortInfo();
        emit portViewProgress(Router::routerPtr);
        emit portInfoProgress(&port);


        if (secondRead == true)
            port.calculateBPSPPS();

        if (thirdRead == true)
            port.calculateLoadStatus();
    }
    emit loadInfoProgress(Router::routerPtr);

    if (secondRead == true)
        thirdRead = true;

    if (secondRead == false)
        secondRead = true;

    timer->singleShot(5000, this, &PortWorker::portProcess);
}






