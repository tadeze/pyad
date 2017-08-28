//
// Created by tadeze on 8/25/17.
//

#include "LogWriter.hpp"

void Log::LogMsg(const std::string &msg) {
    static Log L;
    L.logMsg(msg);
}