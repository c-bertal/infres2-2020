#include <stdio.h>
#include <windows.h>

int main(int argc, char *argv[])
{
	HANDLE hSelfToken = NULL;
	HANDLE hToken2 = NULL;

	OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hSelfToken);
	CreateRestrictedToken(hSelfToken, DISABLE_MAX_PRIVILEGE | LUA_TOKEN, 0, NULL, 0, NULL, 0, NULL, &hToken2);
	SetTokenInformation(hToken2, TokenSessionId, &dwSessionId, sizeof(dwSessionId));

	return 0;
}
