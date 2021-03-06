#include "logging.h"

#ifdef _WIN32

#include <string>
#include <sstream>
#include "../socket/logger.h"
#include "../sound/logger.h"

namespace logger {

	using CodeConv::tstring; using std::string;

	static HMODULE logger = nullptr;
	static CHRPPROC fpInitLogger = nullptr;
	static TCHRPPROC fpTraceC, fpDebugC, fpInfoC, fpWarnC, fpErrorC, fpFatalC = nullptr;

	int initLogger() {
		HMODULE lg = nullptr;
		lg = LoadLibrary(_T("logger.dll"));
		if (lg == nullptr) return (-1);
		mihajong_socket::logger::setLoggerLib(lg);
		sound::logger::setLoggerLib(lg);

		fpInitLogger = (CHRPPROC)GetProcAddress(lg, (LPCSTR)"initLogger");
		if (lg == nullptr) return (-2);

		if (!(fpTraceC = (TCHRPPROC)GetProcAddress(lg, (LPCSTR)"trace"))) return (-3);
		if (!(fpDebugC = (TCHRPPROC)GetProcAddress(lg, (LPCSTR)"debug"))) return (-3);
		if (!(fpInfoC = (TCHRPPROC)GetProcAddress(lg, (LPCSTR)"info"))) return (-3);
		if (!(fpWarnC = (TCHRPPROC)GetProcAddress(lg, (LPCSTR)"warn"))) return (-3);
		if (!(fpErrorC = (TCHRPPROC)GetProcAddress(lg, (LPCSTR)"error"))) return (-3);
		if (!(fpFatalC = (TCHRPPROC)GetProcAddress(lg, (LPCSTR)"fatal"))) return (-3);
#ifdef MJCORE_EXPORTS
		std::ostringstream fname;
		fname << "debug" << GetCurrentProcessId() << ".log";
		(*fpInitLogger)(fname.str().c_str());
#endif
		logger = lg;
		return 0;
	}

	tstring posPrefix(const char* file, int line, tstring msg) {
		CodeConv::tostringstream o;
		o << _T("(")
			<< ( (CodeConv::EnsureTStr(file).rfind(_T("\\"))) == string::npos ?
			file : file + (CodeConv::EnsureTStr(file).rfind(_T("\\"))) + 1 )
			<< _T(":") << line << _T(") ") << msg << std::flush;
		return tstring(o.str());
	}
	tstring posPrefix(const char* file, int line, LPCTSTR msg) {
		CodeConv::tostringstream o;
		o << _T("(")
			<< ( (CodeConv::EnsureTStr(file).rfind(_T("\\"))) == string::npos ?
			file : file + (CodeConv::EnsureTStr(file).rfind(_T("\\"))) + 1 )
			<< _T(":") << line << _T(") ") << msg << std::flush;
		return tstring(o.str());
	}

	void trace_msg(LPCTSTR msg) { if (logger) (*fpTraceC)(msg); }
	void debug_msg(LPCTSTR msg) { if (logger) (*fpDebugC)(msg); }
	void info_msg(LPCTSTR msg) { if (logger) (*fpInfoC)(msg); }
	void warn_msg(LPCTSTR msg) { if (logger) (*fpWarnC)(msg); }
	void error_msg(LPCTSTR msg) { if (logger) (*fpErrorC)(msg); }
	void fatal_msg(LPCTSTR msg) { if (logger) (*fpFatalC)(msg); }

}

#endif /*_WIN32*/
