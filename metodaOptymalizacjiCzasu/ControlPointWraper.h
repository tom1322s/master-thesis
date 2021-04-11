#ifndef CONTROLPOINTWRAPER_H
#define CONTROLPOINTWRAPER_H

#include <mutex>
#include "ControlPoint.h"

class ControlPointWraper
{
    public:
        ControlPointWraper() {}
        ~ControlPointWraper() {}


        ControlPoint get()
        {
            std::lock_guard<std::mutex> lk(mut);
            return cp;
        }

        void set(const ControlPoint& cp)
        {
            std::lock_guard<std::mutex> lk(mut);
            this->cp = cp;
        }

    protected:

    private:
        mutable std::mutex mut;
        ControlPoint cp;
};

#endif // CONTROLPOINTWRAPER_H
