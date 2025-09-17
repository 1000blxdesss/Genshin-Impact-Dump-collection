#define GetTypeDefinition 0x5391B0
#define TypeGetName 0x4C2710 // Type::GetName
#define ClassGetType 0x4C1A00 // Il2CppClass::GetType
#define ClassGetNamespace 0x4C1900 // Il2CppClass::GetNamespace
#define ClassGetFlags 0x4C1A10 // Il2CppClass::GetFlags
#define IsValueType 0x4C1990
#define IsEnum 0x4C1AD0
#define ClassGetParent 0x4C1940
#define ClassGetName 0x4C18F0
#define GetMethods 0x4C18B0
#define GetReturnType 0x544020//0x4C4020
#define GetName 0x4C2150
#define GetParam 0x4C21A0
#define get_idk 0x4C21B0
#define GetParamName 0x4C22B0
#define GetFieldIterator 0x52C640
#define GetFlagsF 0x4C1C60
#define GetTypeF 0x4C1CA0
#define GetNameF 0x4C1C50
#define GetValueSF 0x538810
#define GetFieldOffset 0x4C1C90

#define m_ptr 0x8 // Il2CppMethodPointer
#define m_getFlags 0x2a

// UNITY GARBAGE

    // functions //
// __int64 __fastcall GetTypeDefinition(int _ECX) (1: 55 41 57 41 56 48 0F BF EF) (2: 56 57 48 83 EC ? 48 89 CF 0F BE 49)+32 - __int64 __fastcall FromIl2CppType(_QWORD *a1, __int64 a2)
inline Il2CppClass* GetTypeInfoFromTypeDefinitionIndex(TypeDefinitionIndex index) {
    if (index < 0) return nullptr;
    static const auto fn = (Il2CppClass * (__fastcall*)(int))(GameBase + GetTypeDefinition);
    if (!fn) return nullptr;
    return fn(index);
}
//unsigned __int64 __fastcall sub_1404C2710(__int64 a1) (1: 55 56 57 48 83 EC ? 48 8D 6C 24 ? 48 C7 45 ? ? ? ? ? 48 89 CA 0F 57 C0 0F 29 45 ? 48 C7 45 ? ? ? ? ? 48 C7 45)
inline char* TypeGetName_(const Il2CppType* type) {
    if (!type) return nullptr;
    static  auto fn = ( char* (__fastcall*)(const Il2CppType*))(GameBase + TypeGetName);
    if (!fn) return nullptr;
    return fn(type);
}
//__int64 __fastcall sub_1404C1A00(__int64 a1) (1: 48 8D 41 ? C3 CC CC CC CC CC CC CC CC CC CC CC 56 57)
inline const Il2CppType* ClassGetType_(Il2CppClass* klass) {
	if (!klass) return nullptr;
	static const auto fn = (const Il2CppType * (__fastcall*)(Il2CppClass*))(GameBase + ClassGetType);
	if (!fn) return nullptr;
	return fn(klass);
}
//const char* __fastcall GetNameSpace(__int64 a1) (1: F6 81 ? ? ? ? ? 75 ? 0F B6 41 ? C1 E0 ? 3D ? ? ? ? 75 ? 8B 89 ? ? ? ? 48 8B 05)
inline const char* ClassGetNamespace_(Il2CppClass* klass) {
	if (!klass) return nullptr;
	static const auto fn = (const char* (__fastcall*)(Il2CppClass*))(GameBase + ClassGetNamespace);
	if (!fn) return nullptr;
	return fn(klass);
}   
//__int64 __fastcall il2cpp_class_get_flags(__int64 a1) (1: 8B 81 ? ? ? ? C3 CC CC CC CC CC CC CC CC CC 0F B6 81 ? ? ? ? C0 E8)
inline int ClassGetFlags_(const Il2CppClass* klass) { // большие сиськи это хорошо или плохо? 
	if (!klass) return 0;
	static const auto fn = (bool(__fastcall*)(const Il2CppClass*))(GameBase + ClassGetFlags);
	if (!fn) return 0;
	return fn(klass);
}
//char __fastcall sub_1404C1990(__int64 a1) (1: 0F B6 81 ? ? ? ? 24 ? C0 E8 ? C3 CC CC CC 8B 81)
inline bool Il2CppClassIsValueType(const Il2CppClass* klass) {
	if (!klass) return false;
	static const auto fn = (bool(__fastcall*)(const Il2CppClass*))(GameBase + IsValueType);
	if (!fn) return false;
	return fn(klass);
}
//char __fastcall sub_1404C1AD0(__int64 a1) (1: 0F B6 81 ? ? ? ? 24 ? C0 E8 ? C3 CC CC CC 48 8B 01)
inline bool ClassIsEnum(const Il2CppClass* klass) {
	if (!klass) return false;
	static const auto fn = (bool(__fastcall*)(const Il2CppClass*))(GameBase + IsEnum);
	if (!fn) return false;
	return fn(klass);
}
//__int64 __fastcall sub_1404C1940(__int64 a1) (1: 8B 81 ? ? ? ? 48 85 C0 74 ? 48 8B 0D ? ? ? ? 48 03 01 C3 31 C0 C3 CC CC CC CC CC CC CC 8B 81)
inline Il2CppClass* ClassGetParent_(Il2CppClass* klass) {
	if (!klass) return nullptr;
	static const auto fn = (Il2CppClass * (__fastcall*)(Il2CppClass*))(GameBase + ClassGetParent);
	if (!fn) return nullptr;
	return fn(klass);
}
//__int64 __fastcall sub_1404C18F0(__int64 a1) (1: 48 8B 81 ? ? ? ? C3 CC CC CC CC CC CC CC CC F6 81)
inline const char* ClassGetName_(Il2CppClass* klass) {
	if (!klass) return nullptr;
	static const auto fn = (const char* (__fastcall*)(Il2CppClass*))(GameBase + ClassGetName);
	if (!fn) return nullptr;
	return fn(klass);
}
//__int64 __fastcall j_GetMethods(__int64 a1, unsigned __int64 *a2) (1: E9 ? ? ? ? CC CC CC CC CC CC CC CC CC CC CC E9 ? ? ? ? CC CC CC CC CC CC CC CC CC CC CC 48 83 EC ? C7 44 24)
inline const uint8_t* ClassGetMethods(Il2CppClass* klass, void** iter) {
	if (!klass || !iter) return nullptr;
	static const auto fn = (const uint8_t * (__fastcall*)(Il2CppClass*, void**))(GameBase + GetMethods);
	if (!fn) return nullptr;
	return fn(klass, iter);
}
//__int64 __fastcall sub_140544020(__int64 a1) (1: 55 41 57 41 56 56 57 53 48 83 EC ? 48 8D 6C 24 ? 48 C7 45 ? ? ? ? ? 49 89 CF 48 8B 0D ? ? ? ? FF 15)
inline Il2CppType* MethodGetReturnType(const uint8_t* method) {
    if (!method) return nullptr;
    static const auto fn = (Il2CppType * (__fastcall*)(const uint8_t*))(GameBase + GetReturnType);
    if (!fn) return nullptr;
    return fn(method);
}
//__int64 __fastcall sub_1404C2150(__int64 a1) (1: 48 8B 51 ? 48 85 D2 74 ? 48 B8 ? ? ? ? ? ? ? ? 48 03 02)
inline const char* MethodGetName(const uint8_t* method) {
	if (!method) return nullptr;
	static const auto fn = (const char* (__fastcall*)(const uint8_t*))(GameBase + GetName);
	if (!fn) return nullptr;
	return fn(method);
}
//__int64 __fastcall il2cpp_method_get_param_count(__int64 a1) (1: 0F B6 41 ? C3 CC CC CC CC CC CC CC CC CC CC CC 56 48 83 EC ? 0F B6 41)
inline uint32_t MethodGetParamCount(const uint8_t* method) {
    if (!method) return 0;
    static const auto fn = (uint32_t(__fastcall*)(const uint8_t*))(GameBase + GetParam);
    if (!fn) return 0;
    return fn(method);
}
//__int64 __fastcall il2cpp_method_get_param(__int64 a1, unsigned int a2) (1: 56 48 83 EC ? 0F B6 41 ? 39 D0 76 ? 89 D6 48 8B 51 ? 48 85 D2 74 ? 48 B8 ? ? ? ? ? ? ? ? 48 03 42 ? 74 ? 89 F1 48 8D 0C 49 48 8B 04 C8)
inline Il2CppType* il2cpp_method_get_param(const uint8_t* method, uint32_t index) {
	if (!method) return nullptr;
	static const auto fn = (Il2CppType * (__fastcall*)(const uint8_t*, uint32_t))(GameBase + get_idk);
	if (!fn) return nullptr;
	return fn(method, index);
}
//__int64 __fastcall sub_1404C22B0(__int64 a1, unsigned int a2) (1: 56 48 83 EC ? 0F B6 41 ? 39 D0 76 ? 89 D6 48 8B 51 ? 48 85 D2 74 ? 48 B8 ? ? ? ? ? ? ? ? 48 03 42 ? 74 ? 89 F1 48 8D 0C 49 48 8B 44 C8)
inline const char* MethodGetParamName(const uint8_t* method, uint32_t index) {
    if (!method) return nullptr;
    static const auto fn = (const char* (__fastcall*)(const uint8_t*, uint32_t))(GameBase + GetParamName);
    if (!fn) return nullptr;
    return fn(method, index);
}
//unsigned __int64 __fastcall GetFields(__int64 a1, unsigned __int64 *a2) (1: 55 56 57 48 83 EC ? 48 8D 6C 24 ? 48 C7 45 ? ? ? ? ? 48 85 D2 74 ? 48 89 D6 48 89 CF 48 8B 02 48 85 C0 74 ? 48 83 C0 ? 48 8B 4F ? 0F B7 49)
inline uintptr_t* ClassGetFields(Il2CppClass* klass, void** iter) {
	if (!klass || !iter) return nullptr;
	static const auto fn = (uintptr_t * (__fastcall*)(Il2CppClass*, void**))(GameBase + GetFieldIterator);
	if (!fn) return nullptr;
	return fn(klass, iter);
}
//__int64 __fastcall sub_1404C1C60(_QWORD *a1) (1: 48 B8 ? ? ? ? ? ? ? ? 48 33 01 0F B7 40)
inline uint64_t FieldGetFlags(uintptr_t* field) {
	if (!field) return 0;
	static const auto fn = (uint64_t(__fastcall*)(uintptr_t*))(GameBase + GetFlagsF);
	if (!fn) return 0;
	return fn(field);
}
//__int64 __fastcall sub_1404C1CA0(_QWORD *a1) (1: 48 B8 ? ? ? ? ? ? ? ? 48 33 01 C3 CC CC 4C 89 C0)
inline const Il2CppType* FieldGetType(uintptr_t* field) 
{
	if (!field) return nullptr;
	static const auto fn = (const Il2CppType * (__fastcall*)(uintptr_t*))(GameBase + GetTypeF);
	if (!fn) return nullptr;
	return fn(field);
}
//__int64 __fastcall sub_1404C1C50(__int64 a1) (1: 48 B8 ? ? ? ? ? ? ? ? 48 33 41 ? C3 CC 48 B8)
inline const char* FieldGetName(uintptr_t* field) 
{
	if (!field) return nullptr;
	static const auto fn = (const char* (__fastcall*)(uintptr_t*))(GameBase + GetNameF);
	if (!fn) return nullptr;
	return fn(field);
}
//__int64 __fastcall sub_140538810(unsigned __int64 a1, __int64 a2, __int64 a3, __int64 a4) (1:55 41 56 56 57 53 48 83 EC ? 48 8D 6C 24 ? 48 C7 45 ? ? ? ? ? 49 89 D6 48 89 CF 48 BE)
inline void FieldStaticGetValue(uintptr_t* field, void* value) 
{
	if (!field || !value) return;
	using fn_t = void(__fastcall*)(uintptr_t*, void*);
	static auto fn = (fn_t)(GameBase + GetValueSF);
	if (!fn) return;
	return fn(field, value);
}
//__int64 __fastcall il2cpp_field_get_offset(__int64 a1) (1: B8 ? ? ? ? 03 41 ? 25 ? ? ? ? C3)
inline size_t FieldGetOffset(uintptr_t* field) 
{
	if (!field) return 0;
	static const auto fn = (size_t(__fastcall*)(uintptr_t*))(GameBase + GetFieldOffset);
	if (!fn) return 0;
	return fn(field);
}

:) hello