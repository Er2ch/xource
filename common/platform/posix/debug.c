/* Debugger detection
 * (c) Er2 2023 <er2@dismail.de>
 * Zlib License
 */

#include "port.h"
#include "common/system.h"
#if PLAT_APPLE
# include <mach/mach.h>
# include <sysctl.h>
#elif PLAT_BSD
# include <sys/user.h>
# include <sys/proc.h>
# include <sys/sysctl.h>
#elif PLAT_LINUX
# include <string.h>
# include <fcntl.h>
#endif

LIB_EXPORT
xbool Sys_DebuggerPresent() {
#if PLAT_APPLE || PLAT_FBSD
	struct kinfo_proc info;
	size_t size;
	int mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_PID, getpid()};
# if PLAT_APPLE
	info.kp_proc.p_flag = 0;
# endif

	size = sizeof(info);
	sysctl(mib, 4, &info, &size, NULL, 0);

# if PLAT_APPLE
	return !!(info.kp_proc.p_flag & P_TRACED);
# else
	return !!(info.ki_flag & P_TRACED);
# endif
#elif PLAT_LINUX
	string buf;
	int len, fd;
	char *str;
	static const char tracerPid[] = "TracerPid:";

	fd = open("/proc/self/status", O_RDONLY, S_IRUSR);
	if (fd == -1) return false; // can't detect

	len = read(fd, buf, MAX_STRING - 1);
	close(fd);

	if (len <= 0) return false;

	buf[len] = '\0';
	str = strstr(buf, tracerPid);
	if (!str) return false;
	return !!X_atoi(str + sizeof(tracerPid));
#else
# warning "TODO: Sys_DebuggerPresent()"
	return false;
#endif
}

