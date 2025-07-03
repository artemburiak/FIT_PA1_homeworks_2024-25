#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

constexpr unsigned DOW_MON      = 0b0000'0001;
constexpr unsigned DOW_TUE      = 0b0000'0010;
constexpr unsigned DOW_WED      = 0b0000'0100;
constexpr unsigned DOW_THU      = 0b0000'1000;
constexpr unsigned DOW_FRI      = 0b0001'0000;
constexpr unsigned DOW_SAT      = 0b0010'0000;
constexpr unsigned DOW_SUN      = 0b0100'0000;
constexpr unsigned DOW_WORKDAYS = DOW_MON | DOW_TUE | DOW_WED | DOW_THU | DOW_FRI;
constexpr unsigned DOW_WEEKEND  = DOW_SAT | DOW_SUN;
constexpr unsigned DOW_ALL      = DOW_WORKDAYS | DOW_WEEKEND;

typedef struct TDate {
    unsigned m_Year;
    unsigned m_Month;
    unsigned m_Day;
} TDATE;

TDATE makeDate(unsigned y, unsigned m, unsigned d) {
    TDATE res = { y, m, d };
    return res;
}

void printDate(TDATE date) {

    printf("%04d.%02d.%02d\n", date.m_Year, date.m_Month, date.m_Day);
}

int isLeapYear(int year) {
    if (year % 4000 == 0) {
        return 0;
    }
    if (year % 400 == 0) {
        return 1;
    }
    if (year % 100 == 0) {
        return 0;
    }
    if (year % 4 == 0) {
        return 1;
    }
    return 0;
}

unsigned daysInMonth(unsigned year, unsigned month) {
    const unsigned days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    return days[month - 1] + (month == 2 && isLeapYear(year));
}

int getDayOfWeek(TDATE date) {
    int y = date.m_Year;
    int m = date.m_Month;
    int d = date.m_Day;
    
    if (m < 3) {
        m += 12;
        y--;
    }

    int K = y % 100;
    int J = y / 100;

    int h = (d + (13 * (m + 1)) / 5 + K + (K / 4) + (J / 4) + 5 * J) % 7;

    if (h==0) h=5;
    else if (h==1) h=6;
    else h -= 2;

    return h;
}

unsigned ceiling(unsigned a, unsigned b) {
    unsigned result = a / b;
    unsigned rest = a % b;

    if (rest != 0) result += 1;
    return result;
}

unsigned long daysSinceEpoch(TDATE date) {
    unsigned long days = 0;
    
    for (unsigned year = 0; year < date.m_Year; year++) {
        days += isLeapYear(year) ? 366 : 365;
    }

    for (unsigned month = 1; month < date.m_Month; month++) {
        days += daysInMonth(date.m_Year, month);
    }

    days += date.m_Day - 1;

    return days;
}

long long differenceInDays(TDATE date1, TDATE date2) {
    unsigned long days1 = daysSinceEpoch(date1);
    unsigned long days2 = daysSinceEpoch(date2);

    return abs((int)(days1 - days2));
}

void countWeekdays(int startDay, unsigned totalDays, unsigned weekdayCount[7]) {

    unsigned weeks = totalDays / 7;
    unsigned remainingDays = totalDays % 7;

    for (int i = 0; i < 7; i++) {
        weekdayCount[i] = weeks;
    }

    int currentDay = startDay;

    for (unsigned i = 0; i < remainingDays; i++) {
        weekdayCount[currentDay]++;
        currentDay = (currentDay + 1) % 7;
    }
}

int validDate(TDATE date) {
    if (date.m_Month < 1 || date.m_Month > 12 || date.m_Day < 1 || date.m_Day > 31) return 0;
    return date.m_Day <= daysInMonth(date.m_Year, date.m_Month);
}

int compareDates(TDATE a, TDATE b) {
    if (a.m_Year != b.m_Year)
        return a.m_Year - b.m_Year;
    if (a.m_Month != b.m_Month)
        return a.m_Month - b.m_Month;
    return a.m_Day - b.m_Day;
}

long long countConnections(TDATE from, TDATE to, unsigned perWorkDay, unsigned dowMask) {

    if (!validDate(from) || !validDate(to) || compareDates(from, to) > 0)
        return -1;

    unsigned startWeekday = getDayOfWeek(from);

    unsigned weekdayCount[7];
    unsigned total_days = differenceInDays(from, to);
    countWeekdays(startWeekday, total_days + 1, weekdayCount);

    unsigned count = 0;

    if (dowMask & DOW_MON) count += perWorkDay * weekdayCount[0];
    if (dowMask & DOW_TUE) count += perWorkDay * weekdayCount[1];
    if (dowMask & DOW_WED) count += perWorkDay * weekdayCount[2];
    if (dowMask & DOW_THU) count += perWorkDay * weekdayCount[3];
    if (dowMask & DOW_FRI) count += perWorkDay * weekdayCount[4];
    if (dowMask & DOW_SAT) count += ceiling(perWorkDay, 2) * weekdayCount[5];
    if (dowMask & DOW_SUN) count += ceiling(perWorkDay, 3) * weekdayCount[6];

    return count;
}

TDATE nextDay (TDATE date) {
    unsigned d = date.m_Day;
    unsigned m = date.m_Month;
    unsigned y = date.m_Year;

    if (d == 31 && m == 12) return makeDate(y+1, 1, 1);
    else if (d == daysInMonth(y, m)) return makeDate(y, m+1, 1);
    else return makeDate(y, m, d+1);

}

TDATE endDate(TDATE from, long long connections, unsigned perWorkDay, unsigned dowMask) {

    unsigned perSaturday = ceiling(perWorkDay, 2);
    unsigned perSunday = ceiling(perWorkDay, 3);
    
    TDATE end_date = from;
    TDATE previous_date;

    // Add after first assignment.
    int dayFrom = getDayOfWeek(from);
    int countConnFrom = 0;

    if ((dayFrom == 0 && dowMask & DOW_MON) || (dayFrom == 1 && dowMask & DOW_TUE) || (dayFrom == 2 && dowMask & DOW_WED) || (dayFrom == 3 && dowMask & DOW_THU) || (dayFrom == 4 && dowMask & DOW_FRI)) {
        countConnFrom = perWorkDay;
    }
    else if (dayFrom == 5 && dowMask & DOW_SAT) countConnFrom = perSaturday;
    else if (dayFrom == 6 && dowMask & DOW_SUN) countConnFrom = perSunday;
    // -----------


    if (!validDate(from) || connections < 0 || perWorkDay == 0 || dowMask == 0 || countConnFrom > connections) {
        return makeDate(0, 0, 0);
    }

    int countConnPerWeek = 0;

    if (dowMask & DOW_MON) countConnPerWeek += perWorkDay;
    if (dowMask & DOW_TUE) countConnPerWeek += perWorkDay;
    if (dowMask & DOW_WED) countConnPerWeek += perWorkDay;
    if (dowMask & DOW_THU) countConnPerWeek += perWorkDay;
    if (dowMask & DOW_FRI) countConnPerWeek += perWorkDay;
    if (dowMask & DOW_SAT) countConnPerWeek += perSaturday;
    if (dowMask & DOW_SUN) countConnPerWeek += perSunday;

    if (connections > countConnPerWeek) {
        long long howManyWeeks = connections / (long long)countConnPerWeek;

        long long conn_remove = (howManyWeeks - 1) * countConnPerWeek;
        long long days_add = (howManyWeeks - 1) * 7;

        connections -= conn_remove;

        for (int i=days_add; i > 0; i--) {
            end_date = nextDay(end_date);
        }
    }

    while (1) {

        int dayOfWeek = getDayOfWeek(end_date);

        if ((dayOfWeek == 0 && dowMask & DOW_MON) || (dayOfWeek == 1 && dowMask & DOW_TUE) || (dayOfWeek == 2 && dowMask & DOW_WED) || (dayOfWeek == 3 && dowMask & DOW_THU) || (dayOfWeek == 4 && dowMask & DOW_FRI)) {
            connections -= perWorkDay;
        }
        else if (dayOfWeek == 5 && dowMask & DOW_SAT) connections -= perSaturday;
        else if (dayOfWeek == 6 && dowMask & DOW_SUN) connections -= perSunday;

        if (connections < 0) {
            return previous_date;
        }

        else {
            previous_date = end_date;
            end_date = nextDay(end_date);
        }
    }
}

int main(void) {
    
    assert ( countConnections ( makeDate ( 2024, 10, 1 ), makeDate ( 2024, 10, 31 ), 1, DOW_ALL ) == 31 );
    assert ( countConnections ( makeDate ( 2024, 10, 1 ), makeDate ( 2024, 10, 31 ), 10, DOW_ALL ) == 266 );
    assert ( countConnections ( makeDate ( 2024, 10, 1 ), makeDate ( 2024, 10, 31 ), 1, DOW_WED ) == 5 );
    assert ( countConnections ( makeDate ( 2024, 10, 2 ), makeDate ( 2024, 10, 30 ), 1, DOW_WED ) == 5 );
    assert ( countConnections ( makeDate ( 2024, 10, 1 ), makeDate ( 2024, 10, 1 ), 10, DOW_TUE ) == 10 );
    assert ( countConnections ( makeDate ( 2024, 10, 1 ), makeDate ( 2024, 10, 1 ), 10, DOW_WED ) == 0 );
    assert ( countConnections ( makeDate ( 2024, 1, 1 ), makeDate ( 2034, 12, 31 ), 5, DOW_MON | DOW_FRI | DOW_SAT ) == 7462 );
    assert ( countConnections ( makeDate ( 2024, 1, 1 ), makeDate ( 2034, 12, 31 ), 0, DOW_MON | DOW_FRI | DOW_SAT ) == 0 );
    assert ( countConnections ( makeDate ( 2024, 1, 1 ), makeDate ( 2034, 12, 31 ), 100, 0 ) == 0 );
    assert ( countConnections ( makeDate ( 2024, 10, 10 ), makeDate ( 2024, 10, 9 ), 1, DOW_MON ) == -1 );
    assert ( countConnections ( makeDate ( 2024, 2, 29 ), makeDate ( 2024, 2, 29 ), 1, DOW_ALL ) == 1 );
    assert ( countConnections ( makeDate ( 2023, 2, 29 ), makeDate ( 2023, 2, 29 ), 1, DOW_ALL ) == -1 );
    assert ( countConnections ( makeDate ( 2100, 2, 29 ), makeDate ( 2100, 2, 29 ), 1, DOW_ALL ) == -1 );
    assert ( countConnections ( makeDate ( 2400, 2, 29 ), makeDate ( 2400, 2, 29 ), 1, DOW_ALL ) == 1 );
    assert ( countConnections ( makeDate ( 4000, 2, 29 ), makeDate ( 4000, 2, 29 ), 1, DOW_ALL ) == -1 );

    TDATE d;
    d = endDate ( makeDate ( 2024, 10, 1 ), 100, 1, DOW_ALL );
    assert ( d . m_Year == 2025 && d . m_Month == 1 && d . m_Day == 8 );
    d = endDate ( makeDate ( 2024, 10, 1 ), 100, 6, DOW_ALL );
    assert ( d . m_Year == 2024 && d . m_Month == 10 && d . m_Day == 20 );
    d = endDate ( makeDate ( 2024, 10, 1 ), 100, 1, DOW_WORKDAYS );
    assert ( d . m_Year == 2025 && d . m_Month == 2 && d . m_Day == 17 );
    d = endDate ( makeDate ( 2024, 10, 1 ), 100, 4, DOW_WORKDAYS );
    assert ( d . m_Year == 2024 && d . m_Month == 11 && d . m_Day == 4 );
    d = endDate ( makeDate ( 2024, 10, 1 ), 100, 1, DOW_THU );
    assert ( d . m_Year == 2026 && d . m_Month == 9 && d . m_Day == 2 );
    d = endDate ( makeDate ( 2024, 10, 1 ), 100, 2, DOW_THU );
    assert ( d . m_Year == 2025 && d . m_Month == 9 && d . m_Day == 17 );
    d = endDate ( makeDate ( 2024, 10, 1 ), 100, 0, DOW_THU );
    assert ( d . m_Year == 0 && d . m_Month == 0 && d . m_Day == 0 );
    d = endDate ( makeDate ( 2024, 10, 1 ), 100, 1, 0 );
    assert ( d . m_Year == 0 && d . m_Month == 0 && d . m_Day == 0 );

    d = endDate ( makeDate ( 2089, 12, 22 ), 11631, 2, DOW_ALL );
    assert ( (d . m_Year == 2108 && d . m_Month == 7 && d . m_Day == 19)  );
    d = endDate ( makeDate ( 2343, 1, 3 ), 130397, 2, DOW_ALL );
    assert ( (d . m_Year == 2551 && d . m_Month == 4 && d . m_Day == 6)  );
    d = endDate ( makeDate ( 2474, 5, 25 ), 142181, 8, DOW_ALL );
    assert ( (d . m_Year == 2532 && d . m_Month == 5 && d . m_Day == 15)  );
    return 0;
}