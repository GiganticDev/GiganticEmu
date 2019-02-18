#include "ArcSDK.hpp"

#define DLL_EXPORT __declspec(dllexport)
#define EXTERN_DLL_EXPORT extern "C" DLL_EXPORT

ArcUserAccount arc_account;

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        try {
            ArcClient arc_client;
            arc_client.Connect("127.0.0.1", "11000");
            arc_client.ReadUserAccount(arc_account);
        } catch (const std::exception& error) {
            ArcPanic(error.what());
        }
    }

    return TRUE;
}

EXTERN_DLL_EXPORT void* ArcFriends() {
    return nullptr;
}

EXTERN_DLL_EXPORT void* Matchmaking() {
    return nullptr;
}

EXTERN_DLL_EXPORT void* Networking() {
    return nullptr;
}

EXTERN_DLL_EXPORT int64_t CC_GetArcID(int64_t arg1, int64_t arg2) {
    return 0;
}

EXTERN_DLL_EXPORT int64_t CC_GetArcRunningMode(uint32_t* Mode) {
    *Mode = 0;
    return 0;
}

EXTERN_DLL_EXPORT int64_t CC_GetNickName(const wchar_t* state, wchar_t* buffer, uint32_t buffer_size) {
    ArcWriteString(arc_account.nick, buffer, buffer_size);
    return 0;
}

EXTERN_DLL_EXPORT int64_t CC_GetAccountName(const wchar_t* state, wchar_t* buffer, uint32_t buffer_size) {
    ArcWriteString(arc_account.name, buffer, buffer_size);
    return 0;
}

EXTERN_DLL_EXPORT int64_t CC_GetLaunchedParameter(const wchar_t* arg1, int arg2, wchar_t* buffer, int buffer_size) {
    /*
    Retail dll writes version|username|lang to buffer. Doesnt seem necessary
    */
    ArcWriteString(L"ggc", buffer, buffer_size);
    return 0;
}

EXTERN_DLL_EXPORT int64_t CC_GetSteamTicket(int64_t arg1, uint32_t* arg2) {
    return 0;
}

EXTERN_DLL_EXPORT int64_t CC_GetToken(int64_t arg1, int64_t arg2, int64_t arg3, uint32_t* arg4, uint32_t* arg5) {
    return 0;
}

EXTERN_DLL_EXPORT int64_t CC_GetTokenEx(const wchar_t* arg1, const wchar_t* arg2, const wchar_t* arg3, wchar_t* buffer, int buffer_size) {
    /*
    Auth token sent from game client to auth server.
    Usually acquired from arc client which launches the game.
    Was formatted like this: "XHj3VK1webHFQchh"
    */
    ArcWriteString(L"zwl42ixhzshhfajvt8likv8ujkyoxlrn", buffer, buffer_size);
    return 0;
}

EXTERN_DLL_EXPORT int64_t CC_GetUserAvatarLink(int64_t arg1, wchar_t* arg2, uint32_t* arg3, int arg4) {
	return 0;
}

EXTERN_DLL_EXPORT int64_t CC_GotoUrlInOverlay(int64_t arg1, const wchar_t* arg2) {
	return 0;
}

EXTERN_DLL_EXPORT wchar_t *CC_Init(int64_t arg1, int64_t arg2, uint32_t *arg3) {
    // Never figured out what this was for, string remains the same for release build
	return L"This is our secret, probably encrypted, internal state..";
}

EXTERN_DLL_EXPORT int64_t CC_InstalledFromArc(uint32_t arg1, uint32_t arg2) {
    /*
    Checks if installed on Arc
    0x4CA00 = Ok
    */
	return 0;
}

EXTERN_DLL_EXPORT int64_t CC_InviteFriendInOverlay(int64_t arg1, int64_t* arg2) {
	return 0;
}

EXTERN_DLL_EXPORT int64_t CC_LaunchClient(const wchar_t* arg1, int arg2, int64_t arg3) {
    /*
    Checks arc status and returns an int code
    0xE0000019 = Ok
    For some reason, the "Gigantic-Core_de" build returns 0 instead
    return 0;
    */
	return 0;
}

/*
Client regiesters callback points and periodically checks for functions
Probably used for friend request in-game? Not needed, not implemented
*/
EXTERN_DLL_EXPORT int64_t CC_RegisterCallback() {
	return 0;
}

EXTERN_DLL_EXPORT int64_t CC_RunCallbacks() {
	return 0;
}

EXTERN_DLL_EXPORT int64_t CC_SetViewableRect(const wchar_t* arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4, uint32_t arg5) {
	return 0;
}

EXTERN_DLL_EXPORT int64_t CC_ShowOverlay(int64_t arg1, unsigned int arg2) {
	return 0;
}

EXTERN_DLL_EXPORT int64_t CC_UnInit(const wchar_t *arg1) {
	return 0;
}

EXTERN_DLL_EXPORT int64_t CC_UnregisterCallback() {
	return 0;
}

namespace CC_SDK {

    class DLL_EXPORT ArcID {
    private:
        wchar_t* internal_string;

    public:
        wchar_t* Get() {
            return internal_string;
        }
    };
}