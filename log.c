#include "log.h"

#include <stdarg.h>
#include <string.h>
#include <time.h>


File logfile;
str header = NULL;
//int print_datetime = -1;
str timefmt = "%c";

loglevel logfilter = ALL;





void log_setlogfile(File f) { logfile = f; }

void log_setheader(const str value) {
	header = (str)value;
	// determine if datetime should be printed
	//const int l = strlen(header) - 1;
	//if(l >= 0 && (print_datetime = header[l] == '+')) {
	//	header[l] = '\0'; // <--- SEGFAULT here
	//}
}

void log_setfilter(loglevel lvl) { logfilter = lvl; }
loglevel getfilter() { return logfilter; }

void log_settimefmt(const str fmt) { timefmt = fmt; }
const str gettimefmt() { return timefmt; }


static void printheader(File out) {
	time_t t = time(NULL);
	char date[32];
	strftime(date, 32, timefmt, localtime(&t));
	fprintf(out, "%s%s\n", header, date);
}

void _log(const loglevel lvl, const str lbl, const str fmt, ...) {
	if(logfilter <= lvl) {
		FILE *out = logfile ? logfile : stderr;
		if(*fmt == '\n')
			fputs("\n", out);
		if(header) {
			printheader(out);
		}
		fputs(lbl, out);
		va_list args;
		va_start(args, fmt);
		vfprintf(out, fmt + (*fmt == '\n'), args);
		va_end(args);
	}
}
