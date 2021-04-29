#ifndef BINARYFILE_H
#define BINARYFILE_H

#include "ControlPoint.h"
#include <string>
#include <fstream>

class BinaryFile
{
    public:
        BinaryFile(std::string name, unsigned char mode);

        static const unsigned char MODE_READ = 0;
        static const unsigned char MODE_WRITE = 1;
        static const unsigned char MODE_MODIFY = 2;

        void prepareFile(unsigned long long num);
        ControlPoint getControlPoint(unsigned long long num);
        void setControlPoint(unsigned long long num,ControlPoint cp);

    protected:

    private:

        std::fstream file;
        unsigned char mode;
};

#endif // BINARYFILE_H
