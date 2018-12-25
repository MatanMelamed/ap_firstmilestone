#include "DataReaderServer.h"

int asd() {
    VarManager manager;
    DataReaderServer server = DataReaderServer(&manager);
    server.LoadPaths();

    manager.SetVarValue("x", 0);
    manager.Bind("x",
                 "\"/instrumentation/airspeed-indicator/indicated-speed-kt\"");

    string buffer = "8.00000,1.00000,2.00000,3.00000\n4.00000,5.00";
    string c;
    string l;
    server.Try(buffer, c, l);
    cout << manager.GetValue("x");
    buffer = "000,6.00000,7.00000\n8.00000,";
    server.Try(buffer, c, l);
    cout << manager.GetValue("x");
    cin.get();
}

