#include "StatisticLogger.h"

#include <gtk/gtk.h>
#include <stdio.h>
#include <string>
#include <ctime>
#include "Util.h"

static gboolean DumpTask(gpointer data) {
    ((StatisticLogger *)data)->dump();
    return TRUE;
}

std::string GetDateTimeNowIso8601() {
    auto dt = g_date_time_new_from_unix_utc(std::time(0));
    auto cs = g_date_time_format_iso8601(dt);

    std::string s(cs);

    g_date_time_unref(dt);
    g_free(cs);

    return s;
}


void StatisticLogger::init() {
    g_timeout_add(1000*intervalSec, (GSourceFunc)DumpTask, this);
    dumpStr(GetDateTimeNowIso8601() + " start xournalpp.");
}

void StatisticLogger::finish() {
    dumpStr( (count==0? "" : (textDump() + '\n')) + GetDateTimeNowIso8601() + " stop xournalpp.");
}

std::string StatisticLogger::textDump() {
    return std::string(GetDateTimeNowIso8601()) + ' ' + std::to_string(count);
}

void StatisticLogger::log() {
    ++count;
}

void StatisticLogger::dump() {
    if (count != 0) {
        dumpStr(textDump());
        count = 0;
    }
}

void StatisticLogger::dumpStr(std::string str) {
    auto fname = Util::getConfigFile("statistic.log").str();
    FILE *f = fopen(fname.c_str(), "a");
    fputs((str + '\n').c_str(), f);
    fclose(f);
}