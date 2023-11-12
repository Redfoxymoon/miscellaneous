#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdarg.h>

#if defined(__x86_64__)
typedef long long
#else
typedef int
#endif
(__cdecl *zw_vsprintf)(
	char *buffer,
	const char *format,
	va_list args);

int nt_sprintf(char *str, const char *format, ...)
{
	int ret;
	va_list ap;
	zw_vsprintf internal_vsprintf;
	va_start(ap, format);
	internal_vsprintf = (zw_vsprintf)GetProcAddress(GetModuleHandle(TEXT("ntdll.dll")), "vsprintf");
	ret = internal_vsprintf(str, format, ap);
	va_end(ap);
	return ret;
}

#ifdef TEST
#include <stdio.h>

int main()
{
	char buf[100];
	const char *a = "foo";
	const int b = 42;
	nt_sprintf(buf, "%s %d\n", a, b);
	printf("%s\n", buf);
	return 0;
}
#endif
