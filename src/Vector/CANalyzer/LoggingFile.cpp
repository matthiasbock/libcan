
#ifdef ENABLE_VECTOR

#include <Vector/CANalyzer/LoggingFile.h>


CANalyzerLoggingFile::CANalyzerLoggingFile()
   :CANAdapter(),
    f(0)
{
    adapter_type = ADAPTER_LOGFILE;
}


CANalyzerLoggingFile::CANalyzerLoggingFile(char* filename)
   :CANalyzerLoggingFile()
{
    parseFile(filename);
}


CANalyzerLoggingFile::~CANalyzerLoggingFile() {}


bool CANalyzerLoggingFile::parseFile(char* filename)
{
    // TODO
    return false;
}


#endif
