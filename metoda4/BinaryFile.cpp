#include "BinaryFile.h"
#include <iostream>

BinaryFile::BinaryFile(std::string name, unsigned char mode) :mode(mode)
{
    if(mode == MODE_READ)
    {
        file = std::move(std::fstream(name, file.binary | file.in));
    }
    else if(mode == MODE_WRITE)
    {
        file = std::move(std::fstream(name, file.binary | file.out));
    }
    else if(mode == MODE_MODIFY)
    {
        file = std::move(std::fstream(name, file.binary | file.in | file.out));
    }

    if(!file.is_open())
    {
        std::cout<<"file open error"<<std::endl;
        exit(250);
    }
}

void BinaryFile::prepareFile(unsigned long long num)
{
    if(mode == MODE_WRITE)
    {
        ControlPoint cp;
        cp.cost=65535;
        cp.u = 0.0f;
        size_t p = 1;
        for(unsigned long long i =0; i < num; i++)
        {
            //cp.u = i;
            file.write(reinterpret_cast<char*>(&cp), sizeof(cp));
            if(i>=p*0.1*num)
            {
                std::cout<<p*10<<std::endl;
                p++;
            }
        }
        std::cout<<"End prepare File"<<std::endl;
    }
}

ControlPoint BinaryFile::getControlPoint(unsigned long long num)
{
    if(mode == MODE_READ)
    {
        ControlPoint cp;

        file.seekg (num*sizeof(cp), file.beg);
        file.read(reinterpret_cast<char*>(&cp), sizeof cp);
        //std::cout<<cp.u<<"\t"<<cp.cost<<std::endl;

        return cp;
    }
}

void BinaryFile::setControlPoint(unsigned long long num,ControlPoint cp)
{
    if(mode == MODE_MODIFY)
    {
        file.seekp (num*sizeof(cp), file.beg);
        file.write(reinterpret_cast<char*>(&cp), sizeof(cp));
    }
}
