#include <napi.h>
#include <LM.h>
#include <Windows.h>

Napi::Boolean IsUserAdmin(const Napi::CallbackInfo& info){
  Napi::Env env = info.Env();

    BOOL isAdmin = FALSE;
    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
    PSID AdministratorsGroup;
    BOOL result = AllocateAndInitializeSid(&NtAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS,0,0,0,0,0,0,&AdministratorsGroup);
    if(result){
      if(!CheckTokenMembership(NULL, AdministratorsGroup, &isAdmin)){
        isAdmin = FALSE;
      }
      FreeSid(AdministratorsGroup);
    }
    return Napi::Boolean::New(env, isAdmin);

}

Napi::String Method(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  return Napi::String::New(env, "hello");
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "hello"),
              Napi::Function::New(env, Method));
  exports.Set("isUserAdmin", Napi::Function::New(env, IsUserAdmin));
  return exports;
}

NODE_API_MODULE(addon, Init);