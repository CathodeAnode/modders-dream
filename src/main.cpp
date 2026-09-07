import md.logger;

import std;

int main() {
    md::Logger logger("Main");

    logger.log<md::LogLevel::Debug>("Hello World!");

    return 0;
}
