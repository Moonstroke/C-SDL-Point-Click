#ifndef LOG_H
#define LOG_H

#include <stdio.h>

typedef FILE *File;
typedef char *str;
typedef const char *cstr;



/**
 * Defines the level of priority of a log message.
 * The message can be filtered out from logs if its priority level is
 * inferior to the one set in log_setfilter().
 * It will also be preceded in logs with the name of its level
 * and two separating dashes, e.g.:
 *
 *     INFO -- info message content
 */
typedef enum {
	DEBUG = 0,
	VERBOSE,
	INFO,
	WARNING,
	ERROR,

	/* those should not be used with LOG() and only refer to
	 * minimum and maximum filtering levels
	 */
	ALL = DEBUG,
	NONE = ERROR
} loglevel;


/**
 * \brief Sets the file to log messages in.
 * If none is set (this function never gets called), messages will be
 * printed to stderr.
 */
void log_setlogfile(File logfile);

/**
 * \brief Sets a priority level to filter log messages:
 * only output messages with level >= lvl
 */
void log_setfilter(loglevel filterlevel);
loglevel getfilter();

/**
 * \brief Sets the heading line to start each log message with.
 * NULL <=> no logging header
 */
void log_setheader(const str fmt);

/**
 * \brief Sets the date and time format used in the logging header (if any).
 */
void log_settimefmt(const str fmt);
const str gettimefmt();


/**
 * DO NOT USE THIS
 * The declaration is only present in header to remove some gcc warnings
 * (implicit-function-declaration stuff)
 *
 * Note to devs: not static because used by LOG & co. macros
 */
void _log(loglevel level, const str label, const str fmt, ...);


/**
 * \brief Logs a message in the file (on stderr if none was specified).
 * Uses same format than printf() et al.
 * If fmt starts with a '\n', a new line will be output just before that.
 */
#define LOG(level, fmt, args...) (_log(level, #level" -- ", fmt, ##args))


/**
 * \brief Logs a debugging message.
 */
#define debug(fmt, args...)   LOG(DEBUG, fmt, ##args)

/**
 * \brief Logs a detailled information message.
 */
#define verbose(fmt, args...) LOG(VERBOSE, fmt, ##args)

/**
 * \brief Logs a basic information message.
 */
#define info(fmt, args...)    LOG(INFO, fmt, ##args)

/**
 * \brief Logs a warning message.
 */
#define warning(fmt, args...) LOG(WARNING, fmt, ##args)

/**
 * \brief Logs an error message.
 * Use mainly before a call to exit()
 */
#define error(fmt, args...)   LOG(ERROR, fmt, ##args)


#endif /* LOG_H */
