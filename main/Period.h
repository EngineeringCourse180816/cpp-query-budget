#ifndef CPP_OTP_PERIOD_H
#define CPP_OTP_PERIOD_H

#include "date.h"

using namespace date;

class Period {

public:
    year_month_day start;
    year_month_day end;

    Period(year_month_day start, year_month_day end) {
        this->start = start;
        this->end = end;
    }

    int getDayCount() const {
        return unsigned(end.day()) - unsigned(start.day()) + 1;
    }

};

#endif //CPP_OTP_PERIOD_H
