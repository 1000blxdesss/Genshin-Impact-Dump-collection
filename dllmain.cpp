#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define STB_IMAGE_IMPLEMENTATION
#include <Windows.h>
#include "Logger/Logger.h"
#include "MinHook/include/MinHook.h"
#include <sstream>
#include <chrono>
#include <thread>
#include <mutex>
#include <vector>
#include <fstream>
#include <algorithm>
#include <memory>
#include <map>
#include "UnityUtils/il2cpp-api-types.h"
#include "UnityUtils/il2cpp-tabledefs.h"
#include "UnityUtils/il2cpp-class.h"
#include <codecvt>
#include <regex>
#include <d3d11.h>
#include "GUI/kiero.h"
#include "GUI/ImGui/imgui_impl_dx11.h"
#include "GUI/ImGui/imgui_impl_win32.h"
#include <set>
#include "utils/obfa.h"
#include <wincodec.h> 
#include <mmsystem.h>
#include <digitalv.h>
#pragma comment(lib, "winmm.lib")
#include "utils/stb_image.h"
#include <unordered_map>



//offsets
enum Offsets {
    TypeGetName_ = 0x3F4FA0, // 0x1403F4FA0
    ClassGetType_ = 0x3F42C0, // 0x1403F42C0
    ClassGetNamespace_ = 0x3F41B0, // 0x1403F41B0
    ClassGetFlags_ = 0x3F4250, // 0x1403F4250
    Il2CppClassIsValueType = 0x3F4240, // 0x1403F4240
    ClassIsEnum = 0x3F4390, // 0x1403F4390
    ClassGetParent_ = 0x3F41F0, // 0x1403F41F0
    ClassGetName_ = 0x3F41A0, // 0x1403F41A0
    ClassGetMethods = 0x3F4160, // 0x1403F4160
    MethodGetReturnType = 0x4763C0, // 0x1404763C0
    MethodGetName = 0x3F4AC0, // 0x1403F4B2F
    MethodGetParamCount = 0x3F4B10, // 0x1403F4B10
    il2cpp_method_get_param1 = 0x3F4B20, // 0x1403F4B20
    MethodGetParamName = 0x3F4C20, // 0x1403F4C20
    ClassGetFields = 0x45E900, // 0x14045E900
    FieldGetFlags = 0x3F4520, // 0x1403F4520
    FieldGetType = 0x3F4560, // 0x1403F43A0
    FieldGetName = 0x3F4510, // 0x1403F4510
    FieldStaticGetValue = 0x46AB40, // 0x14046AB40
    FieldGetOffset = 0x3F4550, // 0x1403F4550
    FromIl2CppType1 = 0x3F42B0,
    ClassFromName = 0x4AE0A0,
    OFJHCHDOJGL = 0xb3f39f0,
    Find = 0x11127fd0,
    GetChild = 0x111445e0,
    GetChildCount = 0x111445f0,
    get_gameObject = 0x111280d0,
    get_active = 0x11127d20,
    get_name = 0x1113ed40,
    get_transform = 0x11127cf0,
    set_collisionDetectionMode = 0x11194e70,
    Transform_get_forward = 0x11142b20,
    Transform_get_right = 0x11142780,
    Transform_get_up = 0x11142950,
    Rigidbody_get_position = 0x11195100,
    Time_get_deltaTime = 0x1112a3d0,
    Rigidbody_set_velocity = 0x11194cd0,
    Rigidbody_MovePosition = 0x11195210,
    set_enabled = 0x111192b0,
    get_enabled = 0x111192a0,
    set_position = 0x11142360,
    GetSingletonInstance = 0x51e3660,
    get_eulerAngles = 0x11142420,
    set_eulerAngles = 0x11142560,
    Rotate = 0x11143ad0,
    get_velocity = 0x11194c70,
    set_velocity2 = 0x11194cd0,
    KEJFKEBJBBP = 0x71dd830,
    set_speed = 0x11114b20,
    AGLLPMOLOBE = 0xb402770,
    DGOFICCGJCN = 0x6e030,
    set_localScale = 0x11142d90,
    get_localScale = 0x11142d30
};

enum UnityOffest
{
    UnityEngine_Vector3_WorldToScreenPoint = 0x11137e10,
    UnityEngine_Camera_get_main = 0x111381f0,
    UnityEngine_Transform_get_position = 0x11142300,
    BEJFLLLFKJC_EFJJBJMJEPC = 0x71f4530,
    BEJFLLLFKJC_PNIIKPACAJM = 0x7200220,
    BEJFLLLFKJC_NJEDPEIHJEH = 0x71ebc80,
    GameObject_GetComponentByName = 0x11127990,
    InteropServices_Marshal_PtrToStringAnsi = 0x10b09790,
    SingletonManager_get_Instance = 0x51e3720,
    CollisionFlags_Move = 0x11188650
    
};

enum HookOffsets 
{
    BEJFLLLFKJC_ADBNDFCIION = 0x71d1b80,
    BEJFLLLFKJC_ACGLIMPHAIC = 0x7200bc0,
    BEJFLLLFKJC_BHAAEAGOGLF = 0x7203820,
    DNEFDLJAEBM_BPMDIBJJFKF = 0xcc16550,
    KBBLJHGMNLJ_IJEGLKJBGMB = 0x943f230,
    LHMDIPAIAAK_CHOJPBDPNGJ = 0xaa61e30,
    EEIMHEGPLAE_DCAHCDGAPKD = 0x8588430,
    EEIMHEGPLAE_GAIEPJNEFGM = 0x858da90,
    Update_hook = 0x9d1a340,
    LateTick_hook = 0x9440790,
    KDHNELOMKLG_hook = 0x658c890

};

enum CollisionFlags {
    None = 0,
    Sides = 1,
    Above = 2,
    Below = 4
};

// stucts
struct Vector3 {
    float x = 0, y = 0, z = 0;
    float distance(Vector3 b) const {
        return sqrt(
            pow(x - b.x, 2) + pow(y - b.y, 2) + pow(z - b.z, 2)
        );
    }
    
    bool zero() { return (x == 0 && y == 0 && z == 0); }
    Vector3 operator *(float k) { return { x * k, y * k, z * k }; }
    Vector3 operator -(Vector3 B) { return { x - B.x, y - B.y, z - B.z }; }
    Vector3 operator +(Vector3 B) { return { x + B.x, y + B.y, z + B.z }; }
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
    Vector3() {}

    static Vector3 Null() {
        return { 0, 0, 0 };
    }
};

struct EntityData {
    uint32_t runtimeID;
    std::string name;
    std::string type;
    Vector3 position;
    uint32_t configID;
    std::string entityType;
    bool isActive;
    bool isTickable;
    bool isRendering;
    //std::chrono::steady_clock::time_point lastUpdate;
};


struct ChestData {
    Vector3 position;
    std::string name;
    std::string entityType;
    bool isActive;
};


struct TrailPoint {
    Vector3 position;
    float lifetime = 0.0f;
    float alpha = 1.0f;
};

struct EnemyData {
    Vector3 position;
    std::string name;
    std::string entityType;
    bool isActive;
    uint32_t runtimeID;
    uint32_t configID;
};

// struct Entity
//[INFO] ToStringRelease ->[BaseEntity] Name: 
// Type:OEPFIDAGHJI 
// runtimeID : 150994977 
// configID : 90000002 
// isActive : True 
// isTickable : True 
// isEntityReady : True 
// entityType : Team 
// isLoaded : True 
// excelConfig : / 90000002 
// jsonConfig : KFNIOBAOFCD 
// preRuntimeID : 150994977 
// questID : 0 
// campID : 0 
// GetScenePropID : 0 
// isRendering : null 
// GetPosition : (2412.2, 209.4, -1286.0) 
// GetNearestAvatarDistanceSqr : 0.7592997

// globals
uintptr_t GameBase = NULL;
static std::vector<void*> g_hooks;
ID3D11Device* g_device11 = nullptr;
ID3D11DeviceContext* g_context11 = nullptr;
ID3D11RenderTargetView* g_renderTarget11 = nullptr;
std::vector<Vector3> entityPositions;
static WNDPROC g_OriginalWndProc = nullptr;
static bool g_ShowMenu = false;
static ID3D11ShaderResourceView* g_BackgroundTexture = nullptr;
std::map<std::string, ID3D11ShaderResourceView*> g_EspTextures;
std::map<std::string, ImVec2> g_EspTextureSizes;
std::vector<EntityData> g_EntityList;
std::map<void*, ChestData> g_ChestMap;
ID3D11SamplerState* g_pSamplerLinear = nullptr;
ID3D11SamplerState* g_pSamplerPoint = nullptr;
std::vector<TrailPoint> g_PlayerTrail;
std::unordered_map<void*, EnemyData> g_EnemyMap;
const int MAX_TRAIL_POINTS = 30;
const float TRAIL_ADD_INTERVAL = 0.05f;
const float TRAIL_FADE_TIME = 1.5f;


ID3D11ShaderResourceView* g_MyTexture = nullptr;
int g_TextureWidth = 0;
int g_TextureHeight = 0;

// proto
void RenderFPSOverlay();
void RenderChestESP(void* camera);
void HookWindowProc();
bool LoadTextureFromFile(const char* file_name, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);
void noClip();
void TestFunction();
void RenderEnemyESP(void* camera);
void DrawKillAuraRadius(void* camera);
void drawRayCastHit(Vector3 enemyPos, Vector3 playerPos);
void Floatinggggggg();
void DrawPlayerTrail(void* camera);
void AddTrailPoint(Vector3 position);
void DrawSkeletonESP(void* camera);

namespace UnityUtils 
{
    //pointer to method Il2CppClass* il2cpp_class_from_name(const Il2CppImage* image, const char* namespaze, const char *name)
    //55 41 57 41 56 41 55 41 54 56 57 53 48 83 EC ? 48 8D 6C 24 ? 0F 29 75 ? 48 C7 45 ? ? ? ? ? 4D 89 C4 48 89 55
    inline Il2CppClass* il2cpp_class_from_name(const Il2CppImage* image, const char* namespaze, const char* name) {
        if (!image || !namespaze || !name) return nullptr;
        using fn_t = Il2CppClass * (__fastcall*)(const Il2CppImage*, const char*, const char*);
        static auto fn = (fn_t)(GameBase + ClassFromName);
        if (!fn) return nullptr;
        return fn(image, namespaze, name);
    }

    inline Vector3 WorldToScreenPoint(void* __this, Vector3 position)
    {
        using fn_t = Vector3(__fastcall*)(void* __this, Vector3 position);
        static auto fn = (fn_t)(GameBase + UnityOffest::UnityEngine_Vector3_WorldToScreenPoint);
        if (!fn) return Vector3{ 0,0,0 };
        return fn(__this, position);
    }
    // RVA: 0xb409b50 VA: 0x7ff7de4d9b50 public ONJBJICPCGE DPLHPDBOOND() {}
    inline void* get_main() {
        using fn_t = void* (__fastcall*)();
        static auto fn = (fn_t)(GameBase + UnityOffest::UnityEngine_Camera_get_main);
        if (!fn) return nullptr;
        return fn();
    }

    inline Vector3 get_position(void* _this) {
        using fn_t = Vector3(__fastcall*)(void* _this);
        static auto fn = (fn_t)(GameBase + UnityOffest::UnityEngine_Transform_get_position);
        if (!fn) return Vector3{ 0,0,0 };
        return fn(_this);
    }

    std::string Utf16ToUtf8(const char16_t* data, int32_t len) {
        if (!data || len <= 0) return {};
        int needed = WideCharToMultiByte(CP_UTF8, 0, (LPCWCH)data, len, NULL, 0, NULL, NULL);
        if (needed <= 0) return {};
        std::string out; out.resize(needed);
        WideCharToMultiByte(CP_UTF8, 0, (LPCWCH)data, len, out.data(), needed, NULL, NULL);
        return out;
    }

    // RVA: 0x11127990 VA: 0x7ff7e41f7990 internal UnityEngine.Component GetComponentByName(System.String type) {}
    inline void* GetComponentByName(void* __this, Il2CppString* typeName) {
        using fn_t = void* (__fastcall*)(void* __this, Il2CppString* typeName);
        static auto fn = (fn_t)(GameBase + UnityOffest::GameObject_GetComponentByName);
        if (!fn) return nullptr;
        return fn(__this, typeName);
    }

    // RVA: 0x10b09790 VA: 0x7ff7e3bd9790 public static System.String PtrToStringAnsi(System.IntPtr ptr) {}
    inline Il2CppString* PtrToStringAnsi(void* ptr) {
        using fn_t = Il2CppString * (*)(void* ptr);
        static auto fn = (fn_t)(GameBase + UnityOffest::InteropServices_Marshal_PtrToStringAnsi);
        if (!fn) return nullptr;
        return fn(ptr);
    }

    // RVA: 0x51e3720 VA: 0x7ff7d82b3720public static MoleMole.SingletonManager get_Instance() {}
    inline void* get_SingletonManager() {
        using fn_t = void* (*)();
        static auto fn = (fn_t)(GameBase + UnityOffest::SingletonManager_get_Instance);
        if (!fn) return nullptr;
        return fn();
    }
    

}

namespace Huina 
{
    // // RVA: 0x71f4530 VA: 0x7ff7da2c4530 public virtual UnityEngine.Vector3 EFJJBJMJEPC() {}
    inline Vector3 sub_1471f4530(void* __this)
    {
        using fn_t = Vector3(*)(void*);
        static auto fn = (fn_t)((uintptr_t)GameBase + UnityOffest::BEJFLLLFKJC_EFJJBJMJEPC);
        if (!fn) return Vector3();
        return fn(__this);
    }

    inline int64_t sub_147202AF0(void* __this)
    {
        using fn_t = int64_t(*)(void*);
        static auto fn = (fn_t)((uintptr_t)GameBase + UnityOffest::BEJFLLLFKJC_PNIIKPACAJM);
        if (!fn) return 0;
        return fn(__this);
    }
    // pointer to // RVA: 0x71ebc80 VA: 0x7ff7da2bbc80 public UnityEngine.GameObject NJEDPEIHJEH() {}
    inline void* get_rootGameObject(void* __this) {
        using fn_t = void* (__fastcall*)(void* __this);
        static auto fn = (fn_t)(GameBase + UnityOffest::BEJFLLLFKJC_NJEDPEIHJEH);
        if (!fn) return nullptr;
        return fn(__this);
    }

    inline void* OFJHCHDOJGL(void* __this) { // GetLocalAvatarEntity()
        using fn_t = void* (__fastcall*)(void* __this);
        static auto fn = (fn_t)(GameBase + Offsets::OFJHCHDOJGL);
        if (!fn) return nullptr;
        return fn(__this);
    }
    // pointer to // RVA: 0x11127fd0 VA: 0x7ff7e41f7fd0 public static UnityEngine.GameObject Find(System.String name) {}
    inline void* Find(Il2CppString* name) {
        using fn_t = void* (__fastcall*)(Il2CppString* name);
        static auto fn = (fn_t)(GameBase + Offsets::Find);
        if (!fn) return nullptr;
        Il2CppString* str = UnityUtils::PtrToStringAnsi((void*)name);
        return fn(str);
    }
    // pointer to // RVA: 0x111445e0 VA: 0x7ff7e42145e0 public UnityEngine.Transform GetChild(System.Int32 index) {}
    inline void* GetChild(void* transform, int index) {
        using fn_t = void* (__fastcall*)(void* __this, int index);
        static auto fn = (fn_t)(GameBase + Offsets::GetChild);
        if (!fn) return nullptr;
        return fn(transform, index);
    }
    // RVA: 0x111445f0 VA: 0x7ff7e42145f0 public System.Int32 GetChildCount() {}
    inline int GetChildCount(void* transform) {
        using fn_t = int(__fastcall*)(void* __this);
        static auto fn = (fn_t)(GameBase + Offsets::GetChildCount);
        if (!fn) return 0;
        return fn(transform);
    }
    // RVA: 0x111280d0 VA: 0x7ff7e41f80d0 public UnityEngine.GameObject get_gameObject() {}
    inline void* get_gameObject(void* component) {
        using fn_t = void* (__fastcall*)(void* __this);
        static auto fn = (fn_t)(GameBase + Offsets::get_gameObject);
        if (!fn) return nullptr;
        return fn(component);
    }
    // RVA: 0x11127d20 VA: 0x7ff7e41f7d20 public System.Boolean get_active() {}
    inline bool get_active(void* gameObject) {
        using fn_t = bool(__fastcall*)(void* __this);
        static auto fn = (fn_t)(GameBase + Offsets::get_active);
        if (!fn) return false;
        return fn(gameObject);
    }
    // RVA: 0x1113ed40 VA: 0x7ff7e420ed40 public System.String get_name() {}
    inline Il2CppString* get_name(void* gameObject) {
        using fn_t = Il2CppString * (__fastcall*)(void* __this);
        static auto fn = (fn_t)(GameBase + Offsets::get_name);
        if (!fn) return nullptr;
        return fn(gameObject);
    }
    // RVA: 0x11127cf0 VA: 0x7ff7e41f7cf0 public UnityEngine.Transform get_transform() {}
    inline void* get_transform(void* gameObject) {
        using fn_t = void* (__fastcall*)(void* __this);
        static auto fn = (fn_t)(GameBase + Offsets::get_transform);
        if (!fn) return nullptr;
        return fn(gameObject);
    }
    // RVA: 0x11194e70 VA: 0x7ff7e4264e70 public System.Void set_collisionDetectionMode(UnityEngine.CollisionDetectionMode value) {}
    inline void set_collisionDetectionMode(void* rigidbody, int value) {
        using fn_t = void(__fastcall*)(void* __this, int value);
        static auto fn = (fn_t)(GameBase + Offsets::set_collisionDetectionMode);
        if (!fn) return;
        fn(rigidbody, value);
    }
    // RVA: 0x11142b20 VA: 0x7ff7e4212b20 public UnityEngine.Vector3 get_forward() {}
    inline Vector3 Transform_get_forward(void* transform) {
        using fn_t = Vector3(__fastcall*)(void* __this);
        static auto fn = (fn_t)(GameBase + Offsets::Transform_get_forward);
        if (!fn) return Vector3{};
        return fn(transform);
    }
    // RVA: 0x11142780 VA: 0x7ff7e4212780 public UnityEngine.Vector3 get_right() {}
    inline Vector3 Transform_get_right(void* transform) {
        using fn_t = Vector3(__fastcall*)(void* __this);
        static auto fn = (fn_t)(GameBase + Offsets::Transform_get_right);
        if (!fn) return Vector3{};
        return fn(transform);
    }
    // RVA: 0x11142950 VA: 0x7ff7e4212950 public UnityEngine.Vector3 get_up() {}
    inline Vector3 Transform_get_up(void* transform) {
        using fn_t = Vector3(__fastcall*)(void* __this);
        static auto fn = (fn_t)(GameBase + Offsets::Transform_get_up);
        if (!fn) return Vector3{};
        return fn(transform);
    }
    // RVA: 0x11195100 VA: 0x7ff7e4265100 public UnityEngine.Vector3 get_position() {}
    inline Vector3 Rigidbody_get_position(void* transform) {
        using fn_t = Vector3(__fastcall*)(void* __this);
        static auto fn = (fn_t)(GameBase + Offsets::Rigidbody_get_position);
        if (!fn) return Vector3{};
        return fn(transform);
    }
    // RVA: 0x1112a3d0 VA: 0x7ff7e41fa3d0 public static System.Single get_deltaTime() {}
    inline float Time_get_deltaTime() {
        using fn_t = float(__fastcall*)();
        static auto fn = (fn_t)(GameBase + Offsets::Time_get_deltaTime);
        if (!fn) return 0.0f;
        return fn();
    }
    // RVA: 0x11194cd0 VA: 0x7ff7e4264cd0 public System.Void set_velocity(UnityEngine.Vector3 value) {}
    inline void Rigidbody_set_velocity(void* rigidbody, Vector3 value) {
        using fn_t = void(__fastcall*)(void* __this, Vector3 value);
        static auto fn = (fn_t)(GameBase + Offsets::Rigidbody_set_velocity);
        if (!fn) return;
        fn(rigidbody, value);
    }
    // RVA: 0x11195210 VA: 0x7ff7e4265210 public System.Void MovePosition(UnityEngine.Vector3 position) {}
    inline void Rigidbody_MovePosition(void* rigidbody, Vector3 position) {
        using fn_t = void(__fastcall*)(void* __this, Vector3 position);
        static auto fn = (fn_t)(GameBase + Offsets::Rigidbody_MovePosition);
        if (!fn) return;
        fn(rigidbody, position);
    }

    // RVA: 0x111192b0 VA: 0x7ff7e41e92b0 public System.Void set_enabled(System.Boolean value) {}
    inline void set_enabled(void* collider, bool value) {
        using fn_t = void(__fastcall*)(void* __this, bool value);
        static auto fn = (fn_t)(GameBase + Offsets::set_enabled);
        if (!fn) return;
        fn(collider, value);
    }
    // RVA: 0x111192a0 VA: 0x7ff7e41e92a0 public System.Boolean get_enabled() {}
    inline bool get_enabled(void* collider) {
        using fn_t = bool(__fastcall*)(void* __this);
        static auto fn = (fn_t)(GameBase + Offsets::get_enabled);
        if (!fn) return false;
        return fn(collider);
    }
    // RVA: 0x11142360 VA: 0x7ff7e4212360 public System.Void set_position(UnityEngine.Vector3 value) {}
    inline void set_position(void* transform, Vector3 value) {
        using fn_t = void(__fastcall*)(void* __this, Vector3 value);
        static auto fn = (fn_t)(GameBase + Offsets::set_position);
        if (!fn) return;
        fn(transform, value);
    }

    // RVA: 0x51e3660 VA: 0x7ff7d82b3660  
    inline void* GetSingletonInstance(void* singletonManager, Il2CppString* typeName) {
        using fn_t = void* (__fastcall*)(void* singletonManager, Il2CppString* typeName);
        static auto fn = (fn_t)(GameBase + Offsets::GetSingletonInstance);
        if (!fn) return nullptr;
        return fn(singletonManager, typeName);
    }

    inline void* GetEntityManager() {
        void* singletonManager = UnityUtils::get_SingletonManager();
        if (!singletonManager) return nullptr;
        Il2CppString* entityManagerName = UnityUtils::PtrToStringAnsi((void*)"CACMBFKPFIC");
        return GetSingletonInstance(singletonManager, entityManagerName);
    }
    //
    inline Vector3 get_eulerAngles(void* transform) {
        using fn_t = Vector3(__fastcall*)(void* __this);
        static auto fn = (fn_t)(GameBase + Offsets::get_eulerAngles);
        if (!fn) return Vector3();
        return fn(transform);
    }

    inline void set_eulerAngles(void* transform, Vector3 angles) {
        using fn_t = void(__fastcall*)(void* __this, Vector3 angles);
        static auto fn = (fn_t)(GameBase + Offsets::set_eulerAngles);
        if (!fn) return;
        fn(transform, angles);
    }

    inline void Rotate(void* transform, Vector3 axis, float angle) {
        using fn_t = void(__fastcall*)(void* __this, Vector3 axis, float angle);
        static auto fn = (fn_t)(GameBase + Offsets::Rotate);
        if (!fn) return;
        fn(transform, axis, angle);
    }
    // RVA: 0x11194c70 VA: 0x7ff7e4264c70 public UnityEngine.Vector3 get_velocity() {}
    inline Vector3 get_velocity(void* rigidbody) {
        using fn_t = Vector3(__fastcall*)(void* __this);
        static auto fn = (fn_t)(GameBase + Offsets::get_velocity);
        if (!fn) return Vector3{};
        return fn(rigidbody);
    }

    // RVA: 0x11194cd0 VA: 0x7ff7e4264cd0 public System.Void set_velocity(UnityEngine.Vector3 value) {}
    inline void set_velocity2(void* rigidbody, Vector3 value) {
        using fn_t = void(__fastcall*)(void* __this, Vector3 value);
        static auto fn = (fn_t)(GameBase + Offsets::set_velocity2);
        if (!fn) return;
        fn(rigidbody, value);
    }
    // RVA: 0x71dd830 VA: 0x7ff7da2ad830 public UnityEngine.Animator KEJFKEBJBBP() {}
    inline void* KEJFKEBJBBP(void* __this) { // GetAnimator
        using fn_t = void* (__fastcall*)(void* __this);
        static auto fn = (fn_t)(GameBase + Offsets::KEJFKEBJBBP);
        if (!fn) return nullptr;
        return fn(__this);
    }
    // RVA: 0x11114b20 VA: 0x7ff7e41e4b20 public System.Void set_speed(System.Single value) {}
    inline void set_speed(void* animator, float value) {
        using fn_t = void(__fastcall*)(void* __this, float value);
        static auto fn = (fn_t)(GameBase + Offsets::set_speed);
        if (!fn) return;
        fn(animator, value);
    }
    // RVA: 0xb402770 VA: 0x7ff7de4d2770 public System.Collections.Generic.List<BEJFLLLFKJC> AGLLPMOLOBE() {}
    inline void* AGLLPMOLOBE(void* __this) { // GetEntities
        using fn_t = void* (__fastcall*)(void* __this);
        static auto fn = (fn_t)(GameBase + Offsets::AGLLPMOLOBE);
        if (!fn) return nullptr;
        return fn(__this);
    }
    // RVA: 0x6e030 VA: 0x7ff7d313e030 public System.Single DGOFICCGJCN() {}
    inline float DGOFICCGJCN(void* __this) { // get_value
        using fn_t = float(__fastcall*)(void* __this);
        static auto fn = (fn_t)(GameBase + Offsets::DGOFICCGJCN);
        if (!fn) return 0.0f;
        return fn(__this);
    }
    // RVA: 0x11142d90 VA: 0x7ff7e4212d90 public System.Void set_localScale(UnityEngine.Vector3 value) {}
    inline void set_localScale(void* transform, Vector3 value) {
        using fn_t = void(__fastcall*)(void* __this, Vector3 value);
        static auto fn = (fn_t)(GameBase + Offsets::set_localScale);
        if (!fn) return;
        fn(transform, value);
    }
    // RVA: 0x11142d30 VA: 0x7ff7e4212d30 public UnityEngine.Vector3 get_localScale() {}
    inline Vector3 get_localScale(void* transform) {
        using fn_t = Vector3(__fastcall*)(void* __this);
        static auto fn = (fn_t)(GameBase + Offsets::get_localScale);
        if (!fn) return Vector3{};
        return fn(transform);
    }
}

namespace GuiState
{
    struct CombatFlags {
        bool infStamina = true;
        bool attackMultiplier = true;
        bool infUltimate = true;
        bool infE = true;
        int damageCount = 20;
		bool killaura = false;
		float killauraRange = 5.0f;
        ImVec4 killauraColorCenter = ImVec4(0.31f, 0.16f, 0.63f, 1.0f);  
        ImVec4 killauraColorEdge = ImVec4(0.78f, 0.55f, 1.0f, 1.0f);
        bool fakeRayCastHit = false;
        bool trailGlow = true;
        ImVec4 trailColor = ImVec4(0.5f, 0.0f, 1.0f, 1.0f);
        float trailWidth = 3.0f;
        bool enableTrail = false;
    };

   

    struct MovementFlags {
        bool sprintCD = true;
		bool noclip = false;
        int noclipSpeed = 20;
		float speedMultiplier = 1.5f;
		bool speed = true;
		bool harkoSpin = false;
		float harkoSpinSpeed = 5.0f;
		bool FakeFloating = false;
		float FakeFloatingHeight = 0.0f;
    };

    struct DebugFlags
    {
        float g_ImageScale = 1.0f;
        float g_ImagePosX = 0.0f;
        float g_ImagePosY = 0.0f;
        float g_ImageRotation = 0.0f;
        float g_ImageAlpha = 1.0f;
        bool g_ShowImageSettings = false;


        float textureScale = 0.5f;
        float texturePosX = 0.0f;
        float texturePosY = 0.0f;
        bool lockAspectRatio = true;
        ImVec2 customSize = ImVec2(200, 200);

        bool useAsBackground = true;        
        float backgroundAlpha = 0.3f;      
        float backgroundScale = 1.5f;       
        float backgroundOffsetX = 0.0f;     
        float backgroundOffsetY = 0.0f;    
        bool tileBackground = false;
    };

    struct StaminaFlags {
        
       
        int staminaThreshold = 3; 
        int restoreValue = 10000;

        bool enablePersistentStamina = true;    // 10011
        bool enableTemporaryStamina = true;     // 10012  
        bool enableDiveStamina = true;          // 10050

    };

    struct VisualFlags {
        bool showChestESP = true;
        bool showDebugInfo = true;
        bool showFPS = true;
        bool showList = true;
        float espDistance = 100.0f;
        int espSize = 8;
        ImVec4 espColor = ImVec4(1.0f, 0.84f, 0.0f, 1.0f);

        struct ESPObject {
            std::string name;
            bool enabled = true;
            ImVec4 color;
            int size = 8;
            float maxDistance = 100.0f;
        };

        std::map<std::string, ESPObject> espObjects = {
            {"Chest", {"Chest", true, ImVec4(1.0f, 0.84f, 0.0f, 1.0f), 8, 100.0f}},
            {"Enemy", {"Enemy", false, ImVec4(1.0f, 0.0f, 0.0f, 1.0f), 6, 50.0f}},
            {"NPC", {"NPC", false, ImVec4(0.0f, 1.0f, 0.0f, 1.0f), 6, 80.0f}},
            {"Resource", {"Resource", false, ImVec4(0.0f, 0.5f, 1.0f, 1.0f), 5, 30.0f}},
            {"Player", {"Player", false, ImVec4(1.0f, 1.0f, 0.0f, 1.0f), 7, 200.0f}},
            {"Animal", {"Animal", false, ImVec4(0.5f, 0.3f, 0.1f, 1.0f), 4, 40.0f}}
        };
    };
    
    inline CombatFlags combat;
    inline VisualFlags visual;
    inline MovementFlags movement;
    inline DebugFlags debug;
    inline StaminaFlags stamina;
    inline int selectedTab = 0;
}

namespace GUI
{
    enum class Tab {
        Combat = 0,
        Movement = 1,
        Visual = 2,
        Debug = 3
    };

    inline Tab currentTab = Tab::Combat;
    inline bool isVisible = false;
}

// init/trash funcs
void initIl2cp() {
    GameBase = (uintptr_t)GetModuleHandleA(NULL);
}

void SetCustomStyle() {
    ImGuiStyle& style = ImGui::GetStyle();
    style.FrameRounding = 12.0f;
    style.WindowRounding = 15.0f;
    style.GrabRounding = 10.0f;
    style.ChildRounding = 12.0f;
    style.ItemSpacing = ImVec2(10, 10);
    style.FramePadding = ImVec2(12, 6);

    ImVec4* colors = style.Colors;
    colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.70f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.85f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    colors[ImGuiCol_Button] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
    colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    colors[ImGuiCol_Border] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    colors[ImGuiCol_Tab] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);
    colors[ImGuiCol_TabActive] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(1.0f, 1.0f, 1.0f, 0.8f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.0f, 1.0f, 1.0f, 0.9f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    colors[ImGuiCol_CheckMark] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    colors[ImGuiCol_Header] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.8f, 0.8f, 0.8f, 1.0f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    colors[ImGuiCol_Separator] = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.7f, 0.7f, 0.7f, 1.0f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.7f, 0.7f, 0.7f, 1.0f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    colors[ImGuiCol_PlotLines] = ImVec4(0.8f, 0.8f, 0.8f, 1.0f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.8f, 0.8f, 0.8f, 1.0f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
}
void PlayHitSound()
{
    const char* soundPath = "C:\\Users\\guick\\Downloads\\skeethitsound.mp3";
    std::string command = "open \"" + std::string(soundPath) + "\" type mpegvideo alias hitSound";
    mciSendStringA(command.c_str(), NULL, 0, NULL);
}




void CreateSamplerStates() {
    if (!g_device11) return;

    D3D11_SAMPLER_DESC samplerDesc;
    ZeroMemory(&samplerDesc, sizeof(samplerDesc));
    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    samplerDesc.MinLOD = 0;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
    g_device11->CreateSamplerState(&samplerDesc, &g_pSamplerLinear);
    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    g_device11->CreateSamplerState(&samplerDesc, &g_pSamplerPoint);
}
bool LoadTextureFromMemory(const void* data, size_t data_size, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
{
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load_from_memory((const unsigned char*)data, (int)data_size, &image_width, &image_height, NULL, 4);
    if (image_data == NULL)
        return false;
    D3D11_TEXTURE2D_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Width = image_width;
    desc.Height = image_height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc.CPUAccessFlags = 0;

    ID3D11Texture2D* pTexture = NULL;
    D3D11_SUBRESOURCE_DATA subResource;
    subResource.pSysMem = image_data;
    subResource.SysMemPitch = desc.Width * 4;
    subResource.SysMemSlicePitch = 0;
    HRESULT hr = g_device11->CreateTexture2D(&desc, &subResource, &pTexture);

    if (FAILED(hr)) {
        stbi_image_free(image_data);
        return false;
    }

    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    ZeroMemory(&srvDesc, sizeof(srvDesc));
    srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = desc.MipLevels;
    srvDesc.Texture2D.MostDetailedMip = 0;

    hr = g_device11->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
    pTexture->Release();

    if (FAILED(hr)) {
        stbi_image_free(image_data);
        return false;
    }

    *out_width = image_width;
    *out_height = image_height;
    stbi_image_free(image_data);

    return true;
}

bool LoadEspTextures() {
    std::map<std::string, const char*> texturePaths = {
        {"Chest", "C:\\Users\\guick\\Downloads\\Chest_ICO.png"},
       /* {"Enemy", "C:\\marker.png"},
        {"NPC", "C:\\marker.png"},
        {"Resource", "C:\\marker.png"},
        {"Player", "C:\\marker.png"},
        {"Animal", "C:\\marker.png"}*/
    };

    for (const auto& [type, path] : texturePaths) {
        int width, height;
        ID3D11ShaderResourceView* texture = nullptr;

        if (LoadTextureFromFile(path, &texture, &width, &height)) {
            g_EspTextures[type] = texture;
            g_EspTextureSizes[type] = ImVec2(width, height);
            Logger::log_info("Loaded texture for: " + type);
        }
        else {
            Logger::log_err("Failed to load texture for: " + type);
        }
    }

    return !g_EspTextures.empty();
}


bool LoadTextureFromFile(const char* file_name, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
{
    FILE* f = fopen(file_name, "rb");
    if (f == NULL)
        return false;
    fseek(f, 0, SEEK_END);
    size_t file_size = (size_t)ftell(f);
    if (file_size == -1)
        return false;
    fseek(f, 0, SEEK_SET);
    void* file_data = IM_ALLOC(file_size);
    fread(file_data, 1, file_size, f);
    fclose(f);
    bool ret = LoadTextureFromMemory(file_data, file_size, out_srv, out_width, out_height);
    IM_FREE(file_data);
    return ret;
}

// чисто функция позора
EnemyData ParseEnemyInfo(const std::string& logLine, const Vector3& pos) {
    EnemyData enemy;
    std::regex patterns[] = {
        std::regex(R"(runtimeID:(\d+))"),
        std::regex(R"(configID:(\d+))"),
        std::regex(R"(entityType:([^\s]+))"),
    };
    std::smatch match;

    if (std::regex_search(logLine, match, patterns[0])) {
        enemy.runtimeID = std::stoul(match[1].str());
    }
    if (std::regex_search(logLine, match, patterns[1])) {
        enemy.configID = std::stoul(match[1].str());
    }
    if (std::regex_search(logLine, match, patterns[2])) {
        enemy.entityType = match[1].str();
    }

    enemy.isActive = logLine.find("isActive:True") != std::string::npos;
    enemy.position = pos;

    size_t nameStart = logLine.find("Name:");
    if (nameStart != std::string::npos) {
        size_t nameEnd = logLine.find(" ", nameStart);
        if (nameEnd != std::string::npos) {
            enemy.name = logLine.substr(nameStart + 5, nameEnd - nameStart - 5);
        }
    }

    return enemy;
}


void RenderGUI() {
    void* camera = UnityUtils::get_main();
    if (!camera) return;

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    SetCustomStyle();

    static bool lastShiftState = false;
    bool currentShiftState = GetAsyncKeyState(VK_RSHIFT) & 0x8000;
    if (currentShiftState && !lastShiftState) {
        g_ShowMenu = !g_ShowMenu;
    }
    lastShiftState = currentShiftState;

    if (g_ShowMenu) {
        ImGui::SetNextWindowSize(ImVec2(600, 500), ImGuiCond_Always);
        ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_FirstUseEver);

        if (ImGui::Begin("Huina Client", &g_ShowMenu,
            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)) {

            if (g_MyTexture && GuiState::debug.useAsBackground && GuiState::debug.backgroundAlpha > 0.0f) {
                ImVec2 windowPos = ImGui::GetWindowPos();
                ImVec2 windowSize = ImGui::GetWindowSize();
                ImDrawList* windowDrawList = ImGui::GetWindowDrawList();
                ImVec2 backgroundSize;
                if (GuiState::debug.lockAspectRatio) {
                    float scale = GuiState::debug.backgroundScale;
                    backgroundSize = ImVec2(g_TextureWidth * scale, g_TextureHeight * scale);
                }
                else {
                    backgroundSize = ImVec2(windowSize.x * GuiState::debug.backgroundScale,
                        windowSize.y * GuiState::debug.backgroundScale);
                }

                ImVec2 backgroundPos = ImVec2(
                    windowPos.x + (windowSize.x - backgroundSize.x) * 0.5f + GuiState::debug.backgroundOffsetX,
                    windowPos.y + (windowSize.y - backgroundSize.y) * 0.5f + GuiState::debug.backgroundOffsetY
                );

                windowDrawList->AddImage(
                    (ImTextureID)(intptr_t)g_MyTexture,
                    backgroundPos,
                    ImVec2(backgroundPos.x + backgroundSize.x, backgroundPos.y + backgroundSize.y),
                    ImVec2(0, 0), ImVec2(1, 1),
                    ImColor(1.0f, 1.0f, 1.0f, GuiState::debug.backgroundAlpha)
                );
            }

            // Табы
            if (ImGui::BeginTabBar("MainTabs")) {
                // Combat Tab
                if (ImGui::BeginTabItem("Combat")) {
                    ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.5f, 1.0f), "Combat Features");
                    ImGui::Separator();

                    if (ImGui::TreeNodeEx("Attack Multiplier", ImGuiTreeNodeFlags_Framed))
                    {
                        ImGui::Checkbox("Attack Multiplier", &GuiState::combat.attackMultiplier);
                        if (GuiState::combat.attackMultiplier) 
                        {
                            ImGui::SliderInt("Multiplier Count", &GuiState::combat.damageCount, 1, 100);
                        }
                        ImGui::TreePop();
                    }
                    
                    if (ImGui::TreeNodeEx("Skills", ImGuiTreeNodeFlags_Framed))
                    {
                        ImGui::Checkbox("Delete CD", &GuiState::combat.infE);
                        ImGui::Checkbox("Inf Q", &GuiState::combat.infUltimate);
                        ImGui::TreePop();
                    }
                    if (ImGui::TreeNodeEx("Kill Aura", ImGuiTreeNodeFlags_Framed))
                    {
                        ImGui::Checkbox("Enable", &GuiState::combat.killaura);
						if (GuiState::combat.killaura)
						{
							ImGui::SliderFloat("Range", &GuiState::combat.killauraRange, 1.0f, 200.0f);
							ImGui::Checkbox("RayCast Hit", &GuiState::combat.fakeRayCastHit);
						}
                        ImGui::TreePop();
                    }
                   

                    ImGui::EndTabItem();
                }

                // Movement Tab
                if (ImGui::BeginTabItem("Movement")) {
                    ImGui::TextColored(ImVec4(0.5f, 1.0f, 0.5f, 1.0f), "Movement Features");
                    ImGui::Separator();

                    if (ImGui::TreeNodeEx("Sprint Settings", ImGuiTreeNodeFlags_Framed)) 
                    {

                        ImGui::Checkbox("Infinite Stamina", &GuiState::combat.infStamina);

                        ImGui::SliderInt("Restore Threshold", &GuiState::stamina.staminaThreshold, 0, 10000);
                        ImGui::SliderInt("Restore Value", &GuiState::stamina.restoreValue, 0, 10000);

						ImGui::Checkbox("Floating", &GuiState::movement.FakeFloating);
						ImGui::SliderFloat("Floating Height", &GuiState::movement.FakeFloatingHeight, -10.0f, 10.0f);


                        ImGui::Separator();

                        // Типы стамины
                        ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.2f, 1.0f), "Stamina Types:");
                        ImGui::Checkbox("Persistent Stamina (10011)", &GuiState::stamina.enablePersistentStamina);
                        ImGui::Checkbox("Temporary Stamina (10012)", &GuiState::stamina.enableTemporaryStamina);
                        ImGui::Checkbox("Dive Stamina (10050)", &GuiState::stamina.enableDiveStamina);

                        ImGui::Separator();
                        ImGui::Checkbox("No sprint CD", &GuiState::movement.sprintCD);
                        ImGui::Separator();
                        ImGui::TreePop();
                    }

                    if (ImGui::TreeNodeEx("Movement", ImGuiTreeNodeFlags_Framed))
                    {
						ImGui::Checkbox("Noclip", &GuiState::movement.noclip);
						ImGui::SliderInt("Noclip Speed", &GuiState::movement.noclipSpeed, 0, 100);
                        ImGui::Separator();
						ImGui::Checkbox("Speed Multiplier", &GuiState::movement.speed);
						ImGui::SliderFloat("Speed Value", &GuiState::movement.speedMultiplier, 1.0f, 5.0f);
                        ImGui::Separator();
						ImGui::Checkbox("Spin))", &GuiState::movement.harkoSpin);
                        ImGui::SliderFloat("Speed Spin", &GuiState::movement.harkoSpinSpeed, 0.0f, 15.0f);
						ImGui::TreePop();
					}

                    ImGui::EndTabItem();
                }

                // Visual Tab
                if (ImGui::BeginTabItem("Visual")) {
                    ImGui::TextColored(ImVec4(0.5f, 0.5f, 1.0f, 1.0f), "Visual Features");
                    ImGui::Separator();

                    if (ImGui::TreeNodeEx("Overlay", ImGuiTreeNodeFlags_Framed))
                    {
                        ImGui::Checkbox("Show FPS", &GuiState::visual.showFPS);
                        ImGui::Checkbox("Array List", &GuiState::visual.showList);
                        ImGui::Checkbox("Enable Trail", &GuiState::combat.enableTrail);

                        if (GuiState::combat.enableTrail) {
                            ImGui::ColorEdit4("Trail Color", (float*)&GuiState::combat.trailColor);
                            ImGui::SliderFloat("Trail Width", &GuiState::combat.trailWidth, 1.0f, 10.0f);
                            ImGui::Checkbox("Glow Effect", &GuiState::combat.trailGlow);

                            if (ImGui::Button("Clear Trail")) {
                                g_PlayerTrail.clear();
                            }
                        }
                        ImGui::TreePop();
                    }

                    if (ImGui::TreeNodeEx("ESP", ImGuiTreeNodeFlags_Framed))
                    {
                        static bool espEnabled = true;
                        ImGui::Checkbox("Enable ESP", &espEnabled);

                        ImGui::Separator();
                        ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.2f, 1.0f), "Object Types:");

                        if (ImGui::BeginTable("ESPObjects", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
                        {
                            ImGui::TableSetupColumn("Type");
                            ImGui::TableSetupColumn("Enabled");
                            ImGui::TableSetupColumn("Color");
                            ImGui::TableHeadersRow();

                            for (auto& [name, obj] : GuiState::visual.espObjects)
                            {
                                ImGui::TableNextRow();

                                // название
                                ImGui::TableSetColumnIndex(0);
                                ImGui::Text("%s", name.c_str());

                                // чето вкл/выкл
                                ImGui::TableSetColumnIndex(1);
                                ImGui::Checkbox(("##" + name).c_str(), &obj.enabled);

                                // цвет
                                ImGui::TableSetColumnIndex(2);
                                ImGui::ColorEdit4(("##Color" + name).c_str(), (float*)&obj.color,
                                    ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
                            }

                            ImGui::EndTable();
                        }

                        ImGui::Separator();
                        ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.2f, 1.0f), "Selected Object Settings:");

                        static std::string selectedObject = "Chest";
                        if (GuiState::visual.espObjects.find(selectedObject) != GuiState::visual.espObjects.end())
                        {
                            auto& obj = GuiState::visual.espObjects[selectedObject];

                            if (ImGui::BeginCombo("Edit Object", selectedObject.c_str()))
                            {
                                for (const auto& [name, _] : GuiState::visual.espObjects)
                                {
                                    if (ImGui::Selectable(name.c_str(), selectedObject == name))
                                        selectedObject = name;
                                }
                                ImGui::EndCombo();
                            }

                            ImGui::SliderInt("Size", &obj.size, 2, 20);
                            ImGui::ColorEdit4("Color", (float*)&obj.color);
                        }

                        ImGui::Separator();
                        if (ImGui::Button("Enable All")) {
                            for (auto& [_, obj] : GuiState::visual.espObjects)
                                obj.enabled = true;
                        }
                        ImGui::SameLine();
                        if (ImGui::Button("Disable All")) {
                            for (auto& [_, obj] : GuiState::visual.espObjects)
                                obj.enabled = false;
                        }
                        ImGui::SameLine();
                        if (ImGui::Button("Reset Colors")) {
                            GuiState::visual.espObjects["Chest"].color = ImVec4(1.0f, 0.84f, 0.0f, 1.0f);
                            GuiState::visual.espObjects["Enemy"].color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
                            GuiState::visual.espObjects["NPC"].color = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
                            GuiState::visual.espObjects["Resource"].color = ImVec4(0.0f, 0.5f, 1.0f, 1.0f);
                            GuiState::visual.espObjects["Player"].color = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
                            GuiState::visual.espObjects["Animal"].color = ImVec4(0.5f, 0.3f, 0.1f, 1.0f);
                        }

                        ImGui::TreePop();
                    }

                    

                    ImGui::EndTabItem();
                }

                // Debug Tab
                if (ImGui::BeginTabItem("Debug"))
                {
                    ImGui::TextColored(ImVec4(1.0f, 0.8f, 0.0f, 1.0f), "Debug Information");
                    ImGui::Separator();

                    ImGui::Text("Game Base: 0x%p", (void*)GameBase);
                    ImGui::Text("Chests: %d", g_ChestMap.size());
                    ImGui::Text("Hooks: %d", g_hooks.size());
                    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);

                    ImGui::Separator();
                    ImGui::Checkbox("Show Image Settings", &GuiState::debug.g_ShowImageSettings);

                   
                    if (GuiState::debug.g_ShowImageSettings) {
                        ImGui::TextColored(ImVec4(0.5f, 0.8f, 1.0f, 1.0f), "Background Settings");

                        ImGui::Checkbox("Use as Background", &GuiState::debug.useAsBackground);

                        if (GuiState::debug.useAsBackground) {
                            ImGui::SliderFloat("Background Alpha", &GuiState::debug.backgroundAlpha, 0.0f, 1.0f, "%.2f");
                            ImGui::SliderFloat("Background Scale", &GuiState::debug.backgroundScale, 0.1f, 3.0f, "%.2f");
                            ImGui::SliderFloat("Offset X", &GuiState::debug.backgroundOffsetX, -500.0f, 500.0f, "%.0f");
                            ImGui::SliderFloat("Offset Y", &GuiState::debug.backgroundOffsetY, -500.0f, 500.0f, "%.0f");

                            if (ImGui::TreeNode("Background Preview")) {
                                ImVec2 previewSize(200, 200 * g_TextureHeight / (float)g_TextureWidth);
                                ImGui::Image((ImTextureID)(intptr_t)g_MyTexture, previewSize);
                                ImGui::TreePop();
                            }
                        }

                        ImGui::Separator();
                        ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.2f, 1.0f), "Texture Test Settings");

                       

                        if (!GuiState::debug.lockAspectRatio) {
                            ImGui::SliderFloat("Custom Width", &GuiState::debug.customSize.x, 50.0f, 500.0f, "%.0f");
                            ImGui::SliderFloat("Custom Height", &GuiState::debug.customSize.y, 50.0f, 500.0f, "%.0f");
                        }

                        if (ImGui::Button("Reset Background")) {
                            GuiState::debug.backgroundAlpha = 0.3f;
                            GuiState::debug.backgroundScale = 1.5f;
                            GuiState::debug.backgroundOffsetX = 0.0f;
                            GuiState::debug.backgroundOffsetY = 0.0f;
                            GuiState::debug.tileBackground = false;
                        }
                        ImGui::SameLine();
                        if (ImGui::Button("Reset All")) {
                            GuiState::debug.textureScale = 0.5f;
                            GuiState::debug.texturePosX = 0.0f;
                            GuiState::debug.texturePosY = 0.0f;
                            GuiState::debug.lockAspectRatio = true;
                            GuiState::debug.customSize = ImVec2(200, 200);
                            GuiState::debug.g_ImageAlpha = 1.0f;

                            GuiState::debug.useAsBackground = true;
                            GuiState::debug.backgroundAlpha = 0.3f;
                            GuiState::debug.backgroundScale = 1.5f;
                            GuiState::debug.backgroundOffsetX = 0.0f;
                            GuiState::debug.backgroundOffsetY = 0.0f;
                            GuiState::debug.tileBackground = false;
                        }
                    }
                    ImGui::Separator();
					

                    if (ImGui::Button("Test")) 
                    {
						TestFunction();
                    }
                    
                    
					
                    ImGui::EndTabItem();
                }

                ImGui::EndTabBar();
            } 

            ImGui::Separator();
            ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "RSHIFT: Menu | END: Unload");

            ImGui::End();
        }
    }
    if (GuiState::combat.killaura) {
        DrawKillAuraRadius(camera);
    }

    if (GuiState::visual.showChestESP) {
        DrawSkeletonESP(camera);// RenderEnemyESP(camera);//RenderChestESP(camera);
    }

    if (GuiState::movement.FakeFloating) 
    {
        Floatinggggggg();
    }

    if (GuiState::combat.enableTrail) {
        DrawPlayerTrail(camera);
    }

    if (GuiState::visual.showFPS) {
        RenderFPSOverlay();
    }

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

HRESULT(__stdcall* oPresent11)(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags);
HRESULT __stdcall hkPresent11(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags) {
    static bool initialized = false;
    static bool imguiInitialized = false;
    static bool textureLoaded = false;
    static bool espTexturesLoaded = false;

    

    if (!initialized && SUCCEEDED(swapChain->GetDevice(__uuidof(ID3D11Device), (void**)&g_device11))) {
        g_device11->GetImmediateContext(&g_context11);

        ID3D11Texture2D* backBuffer;
        swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
        g_device11->CreateRenderTargetView(backBuffer, nullptr, &g_renderTarget11);
        backBuffer->Release();

        initialized = true;
        Logger::log_info("DX11 initialized");
        CreateSamplerStates();
    }

    if (initialized && !imguiInitialized) {
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        (void)io;


        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
        io.IniFilename = nullptr;  

        DXGI_SWAP_CHAIN_DESC desc;
        swapChain->GetDesc(&desc);
        HWND gameWindow = desc.OutputWindow;
   
        ImGui_ImplWin32_Init(gameWindow);
        ImGui_ImplDX11_Init(g_device11, g_context11);


        HookWindowProc();
        SetCustomStyle();

        if (initialized && !textureLoaded) {
            
            const char* imagePath = "C:\\Users\\guick\\Downloads\\pngwing.com.png"; 

            if (LoadTextureFromFile(imagePath, &g_MyTexture, &g_TextureWidth, &g_TextureHeight)) {
                Logger::log_info("Texture loaded successfully");
                textureLoaded = true;
            }
            else {
                Logger::log_err("Failed to load texture");
                textureLoaded = true; 
            }
        }
       
        imguiInitialized = true;
        Logger::log_info("All Proc hooks initialized");
    }

    if (initialized && imguiInitialized && textureLoaded && !espTexturesLoaded) {
        try {
            LoadEspTextures();
            espTexturesLoaded = true;
            Logger::log_info("ESP textures loading attempted");
        }
        catch (...) {
            Logger::log_err("Exception during ESP texture loading");
            espTexturesLoaded = true;
        }
    }


    RenderGUI();

    return oPresent11(swapChain, syncInterval, flags);
}


extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


LRESULT WINAPI HookedWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam) && g_ShowMenu) {
        return 1;
    }

    switch (msg) {
    case WM_KEYDOWN:
        if (wParam == VK_RSHIFT) {
            g_ShowMenu = !g_ShowMenu;

            ImGuiIO& io = ImGui::GetIO();
            io.MouseDrawCursor = g_ShowMenu;

            if (g_ShowMenu) {
                ShowCursor(TRUE);
                ClipCursor(nullptr);
            }
            else {
                ShowCursor(FALSE);
                RECT rect;
                GetClientRect(hWnd, &rect);
                POINT topLeft = { rect.left, rect.top };
                POINT bottomRight = { rect.right, rect.bottom };
                ClientToScreen(hWnd, &topLeft);
                ClientToScreen(hWnd, &bottomRight);
                RECT gameRect = { topLeft.x, topLeft.y, bottomRight.x, bottomRight.y };
                ClipCursor(&gameRect);
            }
            return 0;
        }

        if (!g_ShowMenu) {
            break;
        }
        break;

    case WM_MOUSEMOVE:
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_RBUTTONDOWN:
    case WM_RBUTTONUP:
    case WM_MBUTTONDOWN:
    case WM_MBUTTONUP:
    case WM_MOUSEWHEEL:
        if (g_ShowMenu) {
            return 1;
        }
        break;

    case WM_SETCURSOR:
        if (g_ShowMenu) {
            SetCursor(LoadCursor(NULL, IDC_ARROW));
            return 1;
        }
        break;

    case WM_KILLFOCUS:
        g_ShowMenu = false;
        break;
    }

    return CallWindowProc(g_OriginalWndProc, hWnd, msg, wParam, lParam);
}

void HookWindowProc() {
    HWND gameWindow = FindWindowA("UnityWndClass", nullptr);
    if (!gameWindow) {
        gameWindow = FindWindowA(nullptr, "Genshin Impact");
    }

    if (gameWindow) {
        g_OriginalWndProc = (WNDPROC)SetWindowLongPtr(gameWindow, GWLP_WNDPROC, (LONG_PTR)HookedWndProc);
    }
    else {
        Logger::log_err("Game window not found"); // ???????
    }
}


// Main funcs
ChestData ParseEntityInfo(const std::string& logLine, const Vector3& pos) {
    ChestData chest;
    std::regex patterns[] = {
        std::regex(R"(Name:([^\s]+))"),
        std::regex(R"(entityType:([^\s]+))"),
    };
    std::smatch match;

    if (std::regex_search(logLine, match, patterns[0])) {
        chest.name = match[1].str();
    }
    if (std::regex_search(logLine, match, patterns[1])) {
        chest.entityType = match[1].str();
    }

    chest.isActive = logLine.find("isActive:True") != std::string::npos;
    chest.position = pos;
    return chest;
}
std::set<void*> g_OpenedChests;

//void* (*MHPCHKLMBLI_original)(void* __this);
//void* MHPCHKLMBLI_hook(void* __this) {
//   
//   
//
//    return MHPCHKLMBLI_original(__this);
//}
//
//inline void* GetSingletonInstance(void* __this, Il2CppString* typeName) {
//    using fn_t = void* (__fastcall*)(void* __this, Il2CppString* typeName);
//    static auto fn = (fn_t)(GameBase + 0x51e3660);
//    if (!fn) return nullptr;
//    return fn(__this, typeName);
//}

void RenderChestESP(void* camera) {
    if (!camera || g_ChestMap.empty()) return;

    try {
        ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
        if (!draw_list) return;

        ImVec2 screenSize = ImGui::GetIO().DisplaySize;
        if (screenSize.x <= 0 || screenSize.y <= 0) return;

        if (g_pSamplerPoint) {
            g_context11->PSSetSamplers(0, 1, &g_pSamplerPoint);
        }

        for (const auto& pair : g_ChestMap) {
            try {
                const auto& chest = pair.second;

                auto espIt = GuiState::visual.espObjects.find("Chest");
                if (espIt == GuiState::visual.espObjects.end() || !espIt->second.enabled) {
                    continue;
                }

                Vector3 screenPos = UnityUtils::WorldToScreenPoint(camera, chest.position);

                if (screenPos.z > 1.0f) {
                    float x = screenPos.x;
                    float y = screenSize.y - screenPos.y;

                    if (x >= -100 && x <= screenSize.x + 100 && y >= -100 && y <= screenSize.y + 100) {
                        const auto& espObj = espIt->second;

                        auto textureIt = g_EspTextures.find("Chest");
                        if (textureIt != g_EspTextures.end() && textureIt->second) {
                            float baseSize = 64.0f;
                            float sizeMultiplier = espObj.size / 8.0f;
                            float finalSize = baseSize * sizeMultiplier;

                            Vector3 cameraPos = { 0, 0, 0 }; 
                            float distance = chest.position.distance(cameraPos);
                            float distanceScale = max(0.5f, min(2.0f, 100.0f / max(distance, 10.0f)));

                            finalSize *= distanceScale;

                            ImVec2 imageSize = ImVec2(finalSize, finalSize);
                            ImVec2 imagePos = ImVec2(x - finalSize / 2, y - finalSize / 2);

                            draw_list->AddImage(
                                (ImTextureID)(intptr_t)textureIt->second,
                                imagePos,
                                ImVec2(imagePos.x + imageSize.x, imagePos.y + imageSize.y),
                                ImVec2(0, 0), 
                                ImVec2(1, 1),
                                ImColor(espObj.color.x, espObj.color.y, espObj.color.z, espObj.color.w)
                            );
                        }
                        else {
                            draw_list->AddCircleFilled(ImVec2(x, y), espObj.size, ImColor(espObj.color));
                        }


						Vector3 cameraPos = UnityUtils::get_position(UnityUtils::GetComponentByName(camera, UnityUtils::PtrToStringAnsi((void*)("Transform"))));
						float distance = chest.position.distance(cameraPos);
						if (!distance) continue;
                        std::string finalStr = chest.name.empty() ? "Chest" : chest.name.c_str();
						finalStr += " [" + std::to_string((int)distance) + "m]";
						float distFromCenter = sqrt((x - screenSize.x / 2) * (x - screenSize.x / 2) +
                            (y - screenSize.y / 2) * (y - screenSize.y / 2));
                        if (distFromCenter < 400) 
                        {
							draw_list->AddText(ImVec2(x + 20, y - 15), IM_COL32(255, 255, 255, 255), finalStr.c_str());
                          /*  draw_list->AddText(ImVec2(x + 20, y - 15), IM_COL32(255, 255, 255, 255),
                                chest.name.empty() ? "Chest" : chest.name.c_str());*/
                        }
                    }
                }
            }
            catch (...) {
                continue;
            }
        }

        if (g_pSamplerLinear) {
            g_context11->PSSetSamplers(0, 1, &g_pSamplerLinear);
        }
    }
    catch (...) {
        Logger::log_err("Exception in RenderChestESP. WOW!");
        return;
    }
}



void RenderFPSOverlay() {
    ImGui::SetNextWindowPos(ImVec2(10, 10));
    ImGui::Begin("FPS", nullptr,
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground);
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
    ImGui::End();
}


void* (*ACGLIMPHAIC_original)(void* __this);
void* ACGLIMPHAIC_hook(void* __this) {
    auto it = g_ChestMap.find(__this);
    if (it != g_ChestMap.end()) {
        g_ChestMap.erase(it);
    }
    g_OpenedChests.insert(__this);
    return ACGLIMPHAIC_original(__this);
}

void* (*BHAAEAGOGLF_original)(void* __this);
void* BHAAEAGOGLF_hook(void* __this) {
    auto it = g_ChestMap.find(__this);
    if (it != g_ChestMap.end()) {
        g_ChestMap.erase(it);
    }
    g_OpenedChests.insert(__this);
    return BHAAEAGOGLF_original(__this);
}


//// strings
////pointer to RVA: 0x71e1950 VA: 0x7ff7da2b1950 public System.String EBENIJMCIGB() {}
//inline int64_t EBENIJMCIGB(void* __this) {
//	using fn_t = int64_t (*)(void*);
//	static auto fn = (fn_t)((uintptr_t)GameBase + 0x7200220);
//	if (!fn) return 0;
//	return fn(__this);
//}
//
//
//
//// RVA: 0x71f9910 VA: 0x7ff7da2c9910
////public System.String ECMKNDPHMLK() {}
//inline int64_t* ECMKNDPHMLK(void* __this) {
//	using fn_t = int64_t * (*)(void*);
//	static auto fn = (fn_t)((uintptr_t)GameBase + 0x71f9910);
//	if (!fn) return nullptr;
//	return fn(__this);
//}
//
//// RVA: 0x7200220 VA: 0x7ff7da2d0220 // WTF 
////public System.String PNIIKPACAJM() {}
//inline int64_t* PNIIKPACAJM(void* __this) {
//	using fn_t = int64_t * (*)(void*);
//	static auto fn = (fn_t)((uintptr_t)GameBase + 0x7200220);
//	if (!fn) return nullptr;
//	return fn(__this);
//}
//
//// RVA: 0x7202af0 VA: 0x7ff7da2d2af0
////public System.String LNNKIOALIIG() {}

//RVA: 0xb3f39f0 VA: 0x7ff7de4c39f0 public LBAGOLPNECG OFJHCHDOJGL() {}



void* localPlayer = nullptr;

//hook to // RVA: 0x71d1b80 VA: 0x7ff7da2a1b80 public System.Void ADBNDFCIION() {}
void* (*ADBNDFCIION_original)(void* __this);
void* ADBNDFCIION_hook(void* __this) {
   /* if (g_OpenedChests.find(__this) != g_OpenedChests.end()) {
        return ADBNDFCIION_original(__this);
    }*/
	localPlayer = Huina::OFJHCHDOJGL(__this);
    auto entityGameObject = Huina::get_rootGameObject(__this);
    if (!entityGameObject) return ADBNDFCIION_original(__this);

    auto transform = UnityUtils::GetComponentByName(entityGameObject, UnityUtils::PtrToStringAnsi((void*)("Transform")));
    if (!transform) return ADBNDFCIION_original(__this);

    Vector3 pos = UnityUtils::get_position(transform);
    int64_t ret = Huina::sub_147202AF0(__this);
    if (ret != 0) {
        Il2CppString* s = reinterpret_cast<Il2CppString*>((void*)ret);
        if (s && s->length > 0) {
            std::string utf8 = UnityUtils::Utf16ToUtf8(s->chars, s->length);
            
        
			//if (utf8.find("Monster") != std::string::npos) 
   //         {
			//
   //         EnemyData enemyData = ParseEnemyInfo(utf8, pos);
   //         if (!enemyData.isActive) {
   //             g_EnemyMap.erase(__this);
   //         }
   //         else {
   //             g_EnemyMap[__this] = enemyData;
   //             Logger::log_info("Enemy Found: " + enemyData.name + " Type: " + enemyData.entityType +
   //                 " at " + std::to_string((int)pos.x) + ", " +
   //                 std::to_string((int)pos.y) + ", " +
   //                 std::to_string((int)pos.z));
   //         
   //     }
			//}
			//else


           /* if (utf8.find("Chest") != std::string::npos) {
                ChestData chestData = ParseEntityInfo(utf8, pos);

                if (!chestData.isActive) {
                    g_ChestMap.erase(__this);
                }
                else {
                    g_ChestMap[__this] = chestData;
                }
            }*/
        }
    }
	return ADBNDFCIION_original(__this);
}
// hook // RVA: 0xcc16550 VA: 0x7ff7dfce6550 public virtual System.Void BPMDIBJJFKF(System.UInt32 KJJPJFNIPPO, System.Int64 MMLPIIDGCJD, HGEBEPHCCGJ DACAPNLIJLJ) {}
void* (*BPMDIBJJFKF_original)(void* , uint32_t, int64_t, void*);
void* BPMDIBJJFKF_hook(void* __this, uint32_t a, int64_t b, void* c)
{

    if (!GuiState::combat.infStamina) {
        return BPMDIBJJFKF_original(__this, a, b, c);
    }

    if (a == 10011 && GuiState::stamina.enablePersistentStamina)
    {
        if (b <= GuiState::stamina.staminaThreshold) {
            b = GuiState::stamina.restoreValue;
        }
    }
    else if (a == 10012 && GuiState::stamina.enableTemporaryStamina)
    {
        if (b <= GuiState::stamina.staminaThreshold) {
            b = GuiState::stamina.restoreValue;
        }
    }
    else if (a == 10050 && GuiState::stamina.enableDiveStamina)
    {
        if (b <= GuiState::stamina.staminaThreshold) {
            b = GuiState::stamina.restoreValue;
        }
    }

    return BPMDIBJJFKF_original(__this, a, b, c);
}


// hook // RVA: 0xaa61e30 VA: 0x7ff7ddb31e30 public System.Void CHOJPBDPNGJ(System.UInt32 OBBGEEHEJKP, IIOGGHPECKN MBBDBMKAFFL) {}
void* (*CHOJPBDPNGJ_original)(void* __this, uint32_t, void*);
void* CHOJPBDPNGJ_hook(void* __this, uint32_t attackeeRuntimeID, void* attackResult) 
{
    if (GuiState::combat.attackMultiplier) 
    {
        for (int i = 0;i < GuiState::combat.damageCount;i++)CHOJPBDPNGJ_original(__this, attackeeRuntimeID, attackResult);
    }
    
    return CHOJPBDPNGJ_original(__this, attackeeRuntimeID, attackResult);
}

// hook // RVA: 0x8588430 VA: 0x7ff7db658430 private System.Void DCAHCDGAPKD(System.Single NHGNMEFNADN) {}
void* (*DCAHCDGAPKD_original)(void* __this, float);
void* DCAHCDGAPKD_hook(void* __this, float a) {
    if (GuiState::combat.infE) a = 0.9f;
	return DCAHCDGAPKD_original(__this, a);
}
// hook // RVA: 0x943f230 VA: 0x7ff7dc50f230 public System.Void IJEGLKJBGMB(System.Single NHGNMEFNADN) {}
void* (*IJEGLKJBGMB_original)(void* __this, float);
void* IJEGLKJBGMB_hook(void* __this, float a) {
    if (GuiState::movement.sprintCD)a = 0.5f;
	return IJEGLKJBGMB_original(__this, a);
}

// hoot // RVA: 0x858c7c0 VA: 0x7ff7db65c7c0 public System.Boolean IHILHPOAPCK() {}
bool (*GAIEPJNEFGM_original)(void* __this);
bool GAIEPJNEFGM_hook(void* __this) {
    if (GuiState::combat.infUltimate)return true; 
    return GAIEPJNEFGM_original(__this);
}



void hook_function(uint64_t offset, LPVOID detour, void* original) {
    MH_STATUS create_hook = MH_CreateHook((LPVOID)(GameBase + offset), detour, (LPVOID*)original);
    if (create_hook == MH_OK) {
        MH_EnableHook((LPVOID)(GameBase + offset));
        g_hooks.push_back((LPVOID)(GameBase + offset));
    }
    else {
        std::stringstream hexified;
        hexified << std::hex << offset;
        Logger::log_err("Min failed to hook to offset 0x" + hexified.str() + "! (Status: " + std::to_string(create_hook) + ")");
    }
}

// 
//inline Quaternion get_rotation(void* transform) {
//    using fn_t = Quaternion(__fastcall*)(void* __this);
//    static auto fn = (fn_t)(GameBase + 0x11142520);
//    if (!fn) return Quaternion();
//    return fn(transform);
//}
//
////
//inline void set_rotation(void* transform, Quaternion rotation) {
//    using fn_t = void(__fastcall*)(void* __this, Quaternion rotation);
//    static auto fn = (fn_t)(GameBase + 0x111425c0);
//    if (!fn) return;
//    fn(transform, rotation);
//}
//void InstantKillEnemy(void* entity) {
//    auto entityGameObject = Huina::get_rootGameObject(entity);
//    if (!entityGameObject) return;
//
//
//    auto combat = UnityUtils::GetComponentByName(entityGameObject,
//        UnityUtils::PtrToStringAnsi((void*)("LHMDIPAIAAK")));
//    if (!combat) { Logger::log_info("Component not found"); return; }
//	Logger::log_info("Component found");
//    //// CombatProperty
//    //void* combatProp = *(void**)((uintptr_t)combat + 0x148);
//    //if (!combatProp) return;
//
//    // HP SafeFloat
// //   void* hpSafeFloat = *(void**)((uintptr_t)combat + 0x20);
// //   if (!hpSafeFloat) return;
//
// //   
// //   float currentHP = DGOFICCGJCN(hpSafeFloat);
//	//Logger::log_info("Enemy Current HP: " + std::to_string((int)currentHP));
//}

void RenderEnemyESP(void* camera) {
    if (!camera) return;

    try {
        ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
        if (!draw_list) return;

        ImVec2 screenSize = ImGui::GetIO().DisplaySize;
        if (screenSize.x <= 0 || screenSize.y <= 0) return;

        auto entityManager = Huina::GetEntityManager();
        if (!entityManager) return;

        auto entitiesList = Huina::AGLLPMOLOBE(entityManager);
        if (!entitiesList) return;

        struct GenericList {
            void* klass;
            void* monitor;
            void* items;
            int32_t size;
            int32_t version;
        };

        auto list = reinterpret_cast<GenericList*>(entitiesList);
        auto itemsArray = reinterpret_cast<Il2CppArray*>(list->items);

        if (!itemsArray) return;

        for (int i = 0; i < list->size; i++) {
            void* entity = itemsArray->vector[i];
            if (!entity) continue;

            //if (GetAsyncKeyState('F') & 0x8000) {
            //    InstantKillEnemy(entity);
            //}

            auto entityGameObject = Huina::get_rootGameObject(entity);
            if (!entityGameObject) continue;

            auto transform = UnityUtils::GetComponentByName(entityGameObject,
                UnityUtils::PtrToStringAnsi((void*)("Transform")));
            if (!transform) continue;

            int64_t ret = Huina::sub_147202AF0(entity);
            if (ret == 0) continue;

            Il2CppString* s = reinterpret_cast<Il2CppString*>((void*)ret);
            if (!s || s->length <= 0) continue;

            std::string utf8 = UnityUtils::Utf16ToUtf8(s->chars, s->length);

            if (utf8.find("Monster") == std::string::npos && utf8.find("Enemy") == std::string::npos)
                continue;

            Vector3 pos = UnityUtils::get_position(transform);

            Vector3 screenPos = UnityUtils::WorldToScreenPoint(camera, pos);

            if (screenPos.z > 1.0f) {
                float x = screenPos.x;
                float y = screenSize.y - screenPos.y;

                if (x >= -100 && x <= screenSize.x + 100 && y >= -100 && y <= screenSize.y + 100) {
                    draw_list->AddCircleFilled(ImVec2(x, y), 10, IM_COL32(255, 255, 0, 255));
                }
            }
        }
    }
    catch (...) {
        return;
    }
}

void* FindBoneByName(void* transform, const char* boneName) {
    if (!transform) return nullptr;

    auto gameObject = Huina::get_gameObject(transform);
    if (!gameObject) return nullptr;

    Il2CppString* nameStr = Huina::get_name(gameObject);
    if (nameStr) {
        std::string name = UnityUtils::Utf16ToUtf8(nameStr->chars, nameStr->length);
        if (name.find(boneName) != std::string::npos) {
            return transform;
        }
    }

    int childCount = Huina::GetChildCount(transform);
    for (int i = 0; i < childCount; i++) {
        void* child = Huina::GetChild(transform, i);
        void* found = FindBoneByName(child, boneName);
        if (found) return found;
    }

    return nullptr;
}


struct BoneConnection {
    std::string startBone;
    std::string endBone;
};

std::vector<BoneConnection> g_SkeletonConnections = {
    // Голова и шея
    {"Bip001 Head", "Bip001 Neck"},
    {"Bip001 Neck", "Bip001 Spine2"},

    // Позвоночник
    {"Bip001 Spine2", "Bip001 Spine1"},
    {"Bip001 Spine1", "Bip001 Spine"},
    {"Bip001 Spine", "Bip001 Pelvis"},

    // левая рука (я ей дро..)
    {"Bip001 Spine2", "Bip001 L Clavicle"},
    {"Bip001 L Clavicle", "Bip001 L UpperArm"},
    {"Bip001 L UpperArm", "Bip001 L Forearm"},
    {"Bip001 L Forearm", "Bip001 L Hand"},

    // правая рука  
    {"Bip001 Spine2", "Bip001 R Clavicle"},
    {"Bip001 R Clavicle", "Bip001 R UpperArm"},
    {"Bip001 R UpperArm", "Bip001 R Forearm"},
    {"Bip001 R Forearm", "Bip001 R Hand"},

    // левая нога
    {"Bip001 Pelvis", "Bip001 L Thigh"},
    {"Bip001 L Thigh", "Bip001 L Calf"},
    {"Bip001 L Calf", "Bip001 L Foot"},

    // правая нога
    {"Bip001 Pelvis", "Bip001 R Thigh"},
    {"Bip001 R Thigh", "Bip001 R Calf"},
    {"Bip001 R Calf", "Bip001 R Foot"}

    // КИШКИ
};

struct SkeletonESP {
    bool enabled = false;
    ImVec4 boneColor = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
    float boneThickness = 2.0f;
    float maxDistance = 100.0f;
};

SkeletonESP g_SkeletonESP;
Vector3 GetBonePosition(void* rootTransform, const std::string& boneName) {
    void* bone = FindBoneByName(rootTransform, boneName.c_str());
    if (!bone) return Vector3{ 0, 0, 0 };

    return UnityUtils::get_position(bone);
}
// RVA: 0xb409b50 VA: 0x7ff7de4d9b50 public ONJBJICPCGE DPLHPDBOOND() {}
inline void* DPLHPDBOOND(void* __this) 
{
    static auto fn = (void* (__fastcall*)(void* __this))(GameBase + 0xb409b50);
    if (!fn) return nullptr;
    return fn(__this);
}

void DrawSkeletonESP(void* camera) 
{
    if ( !camera) return;


    auto entityManager = Huina::GetEntityManager();
    if (!entityManager) {
        Logger::log_err("EntityManager not found");
        return;
    }

    auto localAvatar = Huina::OFJHCHDOJGL(entityManager);
    if (!localAvatar) {
        Logger::log_err("LocalAvatarEntity not found");
        return;
    }

    void* cam = DPLHPDBOOND(entityManager);
    if (!cam) {
        Logger::log_err("CameraEntity not found");
        return;
    }

    auto cameraGameObject = Huina::get_rootGameObject(cam);
    if (!cameraGameObject) {
        Logger::log_err("Camera GameObject not found");
        return;
    }


    void* actualCamera = UnityUtils::GetComponentByName(cameraGameObject,
        UnityUtils::PtrToStringAnsi((void*)"Camera"));
    if (!actualCamera) {
        Logger::log_err("Camera component not found");
        return;
    }

    auto gameObject = Huina::get_rootGameObject(localAvatar);
    if (!gameObject) {
        Logger::log_err("Avatar GameObject not found");
        return;
    }
   
    auto rootTransform = UnityUtils::GetComponentByName(gameObject,
        UnityUtils::PtrToStringAnsi((void*)("Transform")));
    if (!rootTransform) return;

    Vector3 entityPos = UnityUtils::get_position(rootTransform);


    auto localGameObject = Huina::get_rootGameObject(localAvatar);
    if (!localGameObject) return;

    auto localTransform = UnityUtils::GetComponentByName(localGameObject,
        UnityUtils::PtrToStringAnsi((void*)("Transform")));
    if (!localTransform) return;

    Vector3 localPos = UnityUtils::get_position(localTransform);
    float distance = localPos.distance(entityPos);

    if (distance > g_SkeletonESP.maxDistance) return;

    ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
    if (!draw_list) return;

    ImVec2 screenSize = ImGui::GetIO().DisplaySize;
    ImU32 boneColor = ImColor(g_SkeletonESP.boneColor);

    for (const auto& connection : g_SkeletonConnections) {
        Vector3 startPos = GetBonePosition(rootTransform, connection.startBone);
        Vector3 endPos = GetBonePosition(rootTransform, connection.endBone);

        if (startPos.zero() || endPos.zero()) continue;

        Vector3 startScreen = UnityUtils::WorldToScreenPoint(actualCamera, startPos);
        Vector3 endScreen = UnityUtils::WorldToScreenPoint(actualCamera, endPos);

        if (startScreen.z > 1.0f && endScreen.z > 1.0f) {
            ImVec2 start = ImVec2(startScreen.x, screenSize.y - startScreen.y);
            ImVec2 end = ImVec2(endScreen.x, screenSize.y - endScreen.y);

            draw_list->AddLine(start, end, boneColor, g_SkeletonESP.boneThickness);
        }
    }
}

void COCK()
{

    auto entityManager = Huina::GetEntityManager();
    if (!entityManager) return;

    auto localAvatar = Huina::OFJHCHDOJGL(entityManager);
    if (!localAvatar) return;

    auto avatarGameObject = Huina::get_rootGameObject(localAvatar);
    if (!avatarGameObject) return;


    auto rootTransform = UnityUtils::GetComponentByName(avatarGameObject,
        UnityUtils::PtrToStringAnsi((void*)("Transform")));
    if (!rootTransform) {
        Logger::log_err("Root Transform not found");
        return;
    }

    void* leftBreast = FindBoneByName(rootTransform, "Breast L");
    void* rightBreast = FindBoneByName(rootTransform, "Breast R");

    if (!leftBreast && !rightBreast) {
        leftBreast = FindBoneByName(rootTransform, "+Breast L");
        rightBreast = FindBoneByName(rootTransform, "+Breast R");
    }

    if (leftBreast && rightBreast) 
    {

        Vector3 currentScale = Huina::get_localScale(leftBreast);
        Vector3 bigBoobsScale = { 3.0f, 3.0f, 3.0f };

        Huina::set_localScale(leftBreast, bigBoobsScale);
        Huina::set_localScale(rightBreast, bigBoobsScale);

        
    }
    else {
        Logger::log_err("Breast bones not found! :(( booba ");

        
    }

    void* pelvis = FindBoneByName(rootTransform, "Pelvis"); //penis
    if (pelvis) {
        Vector3 pelvisScale = Huina::get_localScale(pelvis);
        pelvisScale.x *= 1.5f;
        pelvisScale.z *= 1.5f;
        Huina::set_localScale(pelvis, pelvisScale);
    }

 
    void* leftThigh = FindBoneByName(rootTransform, "L Thigh");
    void* rightThigh = FindBoneByName(rootTransform, "R Thigh");

    if (leftThigh && rightThigh) {
        Vector3 thighScale = { 1.3f, 1.3f, 1.3f };
        Huina::set_localScale(leftThigh, thighScale);
        Huina::set_localScale(rightThigh, thighScale);
    }
}
void TestFunction() {}
void SpinHero() 
{
    auto entityManager = Huina::GetEntityManager();
    if (!entityManager) return;

    auto localAvatar = Huina::OFJHCHDOJGL(entityManager);
    if (!localAvatar) return;


    auto avatarGameObject = Huina::get_rootGameObject(localAvatar);
    if (!avatarGameObject) return;

    auto avatarTransform = UnityUtils::GetComponentByName(avatarGameObject,
        UnityUtils::PtrToStringAnsi((void*)("Transform")));
    if (!avatarTransform) return;

	/*auto getRigidbody = UnityUtils::GetComponentByName(avatarGameObject,
		UnityUtils::PtrToStringAnsi((void*)("Rigidbody")));*/

    static float rotationAngle = 0.0f;
    rotationAngle += GuiState::movement.harkoSpinSpeed; 
    if (rotationAngle > 360.0f) rotationAngle = 0.0f;


    Vector3 newRotation = { 0, rotationAngle, 0 }; 
	//Vector3 zzxc = { rotationAngle ,rotationAngle ,rotationAngle };
    Huina::set_eulerAngles(avatarTransform, newRotation);
	//set_velocity2(getRigidbody, zzxc);
}

void SpeedChange()
{
    auto entityManager = Huina::GetEntityManager();
    if (!entityManager) return;

    auto localAvatar = Huina::OFJHCHDOJGL(entityManager);
    if (!localAvatar) return;

    auto avatarGameObject = Huina::get_rootGameObject(localAvatar);
    if (!avatarGameObject) return;

    auto rigidbody = UnityUtils::GetComponentByName(avatarGameObject,
        UnityUtils::PtrToStringAnsi((void*)("Rigidbody")));
    if (!rigidbody) return;
	// Get Animator
	auto animator = Huina::KEJFKEBJBBP(localAvatar);
	if (!animator) return;
	if (GuiState::movement.speed)
	{
		
        Huina::set_speed(animator, GuiState::movement.speedMultiplier);
	}
    
}

void Floatinggggggg() 
{
	auto entityManager = Huina::GetEntityManager();
	if (!entityManager) return;
	auto localAvatar = Huina::OFJHCHDOJGL(entityManager);
	if (!localAvatar) return;
	auto avatarGameObject = Huina::get_rootGameObject(localAvatar);
	if (!avatarGameObject) return;
	auto rigidbody = UnityUtils::GetComponentByName(avatarGameObject,
		UnityUtils::PtrToStringAnsi((void*)("Rigidbody")));
	if (!rigidbody) return;
	Vector3 vel = Huina::get_velocity(rigidbody);
	Vector3 newVel = { vel.x * GuiState::movement.FakeFloatingHeight, vel.y*GuiState::movement.FakeFloatingHeight, vel.z* GuiState::movement.FakeFloatingHeight };
    Huina::set_velocity2(rigidbody, newVel);
}

void noClip()
{
    auto entityManager = Huina::GetEntityManager();
    if (!entityManager) return;

    auto localAvatar = Huina::OFJHCHDOJGL(entityManager);
    if (!localAvatar) return;

    auto avatarGameObject = Huina::get_rootGameObject(localAvatar);
    if (!avatarGameObject) return;

    auto avatarTransform = UnityUtils::GetComponentByName(avatarGameObject,
        UnityUtils::PtrToStringAnsi((void*)("Transform")));
    if (!avatarTransform) return;

    auto rigidbody = UnityUtils::GetComponentByName(avatarGameObject,
        UnityUtils::PtrToStringAnsi((void*)("Rigidbody")));

    auto cameraEntity = UnityUtils::get_main();
    if (!cameraEntity) return;

    auto cameraTransform = UnityUtils::GetComponentByName(cameraEntity,
        UnityUtils::PtrToStringAnsi((void*)("Transform")));
    if (!cameraTransform) return;

    
    if (rigidbody && !GuiState::movement.noclip) {

        Huina::set_collisionDetectionMode(rigidbody, 1);
        Huina::set_enabled(rigidbody, true);
    }
    else if (rigidbody) {
        Huina::set_collisionDetectionMode(rigidbody, 0);
        Huina::set_enabled(rigidbody, false);
    }

    if (!GuiState::movement.noclip) return;

    Vector3 currentPos = UnityUtils::get_position(avatarTransform);
    if (currentPos.zero()) return;

    Vector3 dir = {};

   /* if (ImGui::IsKeyDown(ImGuiKey_W)) dir = dir + Transform_get_forward(avatarTransform);
    if (ImGui::IsKeyDown(ImGuiKey_S)) dir = dir - Transform_get_forward(avatarTransform);
    if (ImGui::IsKeyDown(ImGuiKey_D)) dir = dir + Transform_get_right(avatarTransform);
    if (ImGui::IsKeyDown(ImGuiKey_A)) dir = dir - Transform_get_right(avatarTransform);
    if (ImGui::IsKeyDown(ImGuiKey_Space)) dir = dir + Transform_get_up(avatarTransform);
    if (ImGui::IsKeyDown(ImGuiKey_LeftShift)) dir = dir - Transform_get_up(avatarTransform);*/
    if (ImGui::IsKeyDown(ImGuiKey_W)) dir = dir + Huina::Transform_get_forward(cameraTransform);
    if (ImGui::IsKeyDown(ImGuiKey_S)) dir = dir - Huina::Transform_get_forward(cameraTransform);
    if (ImGui::IsKeyDown(ImGuiKey_D)) dir = dir + Huina::Transform_get_right(cameraTransform);
    if (ImGui::IsKeyDown(ImGuiKey_A)) dir = dir - Huina::Transform_get_right(cameraTransform);
    if (ImGui::IsKeyDown(ImGuiKey_Space)) dir = dir + Huina::Transform_get_up(cameraTransform);
    if (ImGui::IsKeyDown(ImGuiKey_LeftShift)) dir = dir - Huina::Transform_get_up(cameraTransform);



    if (dir.zero()) return;

    float deltaTime = Huina::Time_get_deltaTime();
    Vector3 moveDelta = dir * GuiState::movement.noclipSpeed * deltaTime;


    Vector3 newPos = currentPos + moveDelta;


    if (rigidbody) {
        Huina::Rigidbody_MovePosition(rigidbody, newPos);
    }
    else {
        Huina::set_position(avatarTransform, newPos);
    }


    
}

////hook to // RVA: 0x9d1a340 VA: 0x7ff7dcdea340 private System.Void Update() {}
inline void* (*Update_original)(void* __this);

inline void* Update_hook_(void* __this)
{
  
    auto result = Update_original(__this);
	

	
 
    return result;
}
//hook to // RVA: 0x9440790 VA: 0x7ff7dc510790 public override System.Void LateTick(System.Single NHGNMEFNADN) {}
inline void (*LateTick_original)(void* __this, float);
inline void LateTick_hook_(void* __this, float a)
{
    if (GuiState::movement.harkoSpin)
    {
        SpinHero();
    }
    COCK();
	if (GuiState::movement.speedMultiplier != 1.0f)
	{
		SpeedChange();
	}
    if (GuiState::combat.enableTrail) {
        auto entityManager = Huina::GetEntityManager();
        if (entityManager) {
            auto localAvatar = Huina::OFJHCHDOJGL(entityManager);
            if (localAvatar) {
                auto avatarGameObject = Huina::get_rootGameObject(localAvatar);
                if (avatarGameObject) {
                    auto avatarTransform = UnityUtils::GetComponentByName(avatarGameObject,
                        UnityUtils::PtrToStringAnsi((void*)("Transform")));
                    if (avatarTransform) {
                        Vector3 currentPos = UnityUtils::get_position(avatarTransform);
                        currentPos.y += 0.5f;
                        AddTrailPoint(currentPos);
                    }
                }
            }
        }
    }
	if (GuiState::movement.noclip)
	{
        noClip();
        return;
        
	}
   
    LateTick_original(__this, a);
	
}
// get public UnityEngine.Vector3 position; // 0x10 from MoleMole.MoveSyncTask
// //get protected MoleMole.MoveSyncTask MKFJEFAOLOH; // 0x148 __this+0x148
//hook // RVA: 0x658d3b0 VA: 0x7ff7d965d3b0 private System.Void KDHNELOMKLG() {}
struct Quaternion {
    float x;
    float y;
    float z;
    float w;
};
struct MoveSyncTask {
    struct Vector3 position;
    struct Vector3 velocity;
    struct Vector3 forward;
    struct Vector3 up;
    struct Quaternion rotation;
    int32_t motion;
    int32_t paramNumber;
    struct Vector3 param0;
    struct Vector3 param1;
    struct Vector3 param2;
    struct Vector3 param3;
    uint32_t time;
    uint32_t reliableSeq;
    uint32_t clientSequenceId;
    uint32_t subSequenceId;
    bool reliable;
    bool isFake;
    struct Vector3 refPosition;
    uint32_t refEntityId;
    uint32_t refEntityTimestamp;
    bool hasValue;
    struct Vector3 positionRS;
    struct Vector3 positionRSLocal;
    uint32_t randomDelay;
    int32_t frameCountWhenAddTask;
};

Vector3 currentPlayerPos = { 0,0,0 };
Vector3 currentPosFix = { 0,0,0 };
Vector3 currentEnemyPosFix = { 0,0,0 };
struct KillAuraLine {
    Vector3 startPos;
    Vector3 endPos;
    float alpha = 1.0f;
    float lifetime = 0.0f;
    bool isActive = true;
};

std::vector<KillAuraLine> g_KillAuraLines;
void AddHitLine(Vector3 startPos, Vector3 endPos) {
    if (!GuiState::combat.fakeRayCastHit) return;

    KillAuraLine newLine;
    newLine.startPos = startPos;
    newLine.endPos = endPos;
    newLine.alpha = 1.0f;
    newLine.lifetime = 0.0f;
    newLine.isActive = true;

    g_KillAuraLines.push_back(newLine);
}

inline void* (*KDHNELOMKLG_original)(void* __this);
inline void* KDHNELOMKLG_hook_(void* __this)
{
    MoveSyncTask* moveSyncTask = (MoveSyncTask*)((uintptr_t)__this + 0x148);
    
  
    // fld protected KLHBHFIDCGG OCMBDPICNAD; // 0x18 from GMLOEPALBOG (BaseComponentPlugin)
    void* baseComponentPlugin = *(void**)((uintptr_t)__this + 0x18);
    // fld public System.UInt32 INBMEOGACCC; // 0x14 from KLHBHFIDCGG (runrimeID)
    uint32_t entityId = *(uint32_t*)((uintptr_t)baseComponentPlugin + 0x14);
    //Logger::log_info("EntityId: " + std::to_string(entityId)+"position: "+ std::to_string(moveSyncTask->position.x));
    // protected BEJFLLLFKJC HBFJBCOHDIJ; // 0x28
    void* baseEntity = *(void**)((uintptr_t)baseComponentPlugin + 0x28);
    int64_t ret = Huina::sub_147202AF0(baseEntity);
    if (ret != 0) {
        Il2CppString* s = reinterpret_cast<Il2CppString*>((void*)ret);
        if (s && s->length > 0) {
            std::string utf8 = UnityUtils::Utf16ToUtf8(s->chars, s->length);

            if (utf8.find("entityType:Avatar") != std::string::npos)
            {
				currentPlayerPos = moveSyncTask->position;
                auto avatarGameObject = Huina::get_rootGameObject(baseEntity);
				if (!avatarGameObject) return KDHNELOMKLG_original(__this);
				auto avatarTransform = UnityUtils::GetComponentByName(avatarGameObject,
					UnityUtils::PtrToStringAnsi((void*)("Transform")));
				if (!avatarTransform) return KDHNELOMKLG_original(__this);
				currentPosFix = UnityUtils::get_position(avatarTransform);
				if (currentPosFix.zero()) return KDHNELOMKLG_original(__this);
	
                return KDHNELOMKLG_original(__this);
            }
			    auto otherEntityGameObject = Huina::get_rootGameObject(baseEntity);
			    if (!otherEntityGameObject) return KDHNELOMKLG_original(__this);
			    auto otherEntityTransform = UnityUtils::GetComponentByName(otherEntityGameObject,
				    UnityUtils::PtrToStringAnsi((void*)("Transform")));
			    if (!otherEntityTransform) return KDHNELOMKLG_original(__this);
			    currentEnemyPosFix = UnityUtils::get_position(otherEntityTransform);
			
                float distance = currentPlayerPos.distance(moveSyncTask->position);


                if (GuiState::combat.killaura && distance <= GuiState::combat.killauraRange)
                {
                    if (GuiState::combat.fakeRayCastHit) {
                        Vector3 raisedPlayerPos = currentPosFix;
                        raisedPlayerPos.y += 1.5f;
                        AddHitLine(raisedPlayerPos, currentEnemyPosFix);
                    }
                    //drawRayCastHit(currentEnemyPosFix, currentPosFix);

                    moveSyncTask->position.x = 1000000.0f;
                    moveSyncTask->position.y = 1000000.0f;
                    moveSyncTask->position.z = 1000000.0f;

					/*moveSyncTask->positionRSLocal.x = 1000000.0f;
					moveSyncTask->positionRSLocal.y = 1000000.0f;
					moveSyncTask->positionRSLocal.z = 1000000.0f;

					moveSyncTask->positionRS.x = 1000000.0f;
					moveSyncTask->positionRS.y = 1000000.0f;
					moveSyncTask->positionRS.z = 1000000.0f;*/

					PlayHitSound();
                }
            
        }
    }
        
    return KDHNELOMKLG_original(__this);
}
void DrawKillAuraLines(void* camera) {
    if (!camera || g_KillAuraLines.empty()) return;

    ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
    if (!draw_list) return;

    ImVec2 screenSize = ImGui::GetIO().DisplaySize;

    for (auto it = g_KillAuraLines.begin(); it != g_KillAuraLines.end(); ) {
        KillAuraLine& line = *it;

        line.lifetime += ImGui::GetIO().DeltaTime;
        line.alpha = 1.0f - (line.lifetime / 9.0f);

        if (line.alpha <= 0.0f) {
            it = g_KillAuraLines.erase(it);
            continue;
        }

        Vector3 startScreen = UnityUtils::WorldToScreenPoint(camera, line.startPos);
        Vector3 endScreen = UnityUtils::WorldToScreenPoint(camera, line.endPos);

        if (startScreen.z > 1.0f && endScreen.z > 1.0f) {
            ImVec2 start = ImVec2(startScreen.x, screenSize.y - startScreen.y);
            ImVec2 end = ImVec2(endScreen.x, screenSize.y - endScreen.y);

            int outerAlpha = (int)(60 * line.alpha);
            draw_list->AddLine(start, end, IM_COL32(160, 80, 255, outerAlpha), 15.0f);

            // 2. внешн. свечение
            int outerAlpha2 = (int)(80 * line.alpha);
            draw_list->AddLine(start, end, IM_COL32(180, 100, 255, outerAlpha2), 10.0f);

            // 3. ср. свечение  
            int midAlpha = (int)(150 * line.alpha);
            draw_list->AddLine(start, end, IM_COL32(200, 120, 255, midAlpha), 6.0f);

            // 4. внутр. свечение
            int innerAlpha = (int)(200 * line.alpha);
            draw_list->AddLine(start, end, IM_COL32(220, 140, 255, innerAlpha), 4.0f);

            // 5. яркая хуйня внутри линии
            int coreAlpha = (int)(255 * line.alpha);
            draw_list->AddLine(start, end, IM_COL32(240, 160, 255, coreAlpha), 2.0f);

            draw_list->AddLine(start, end, IM_COL32(255, 255, 255, coreAlpha), 1.0f);

            // 7. Прост точки
            draw_list->AddCircleFilled(start, 6.0f, IM_COL32(180, 100, 255, outerAlpha));
            draw_list->AddCircleFilled(start, 4.0f, IM_COL32(220, 140, 255, innerAlpha));
            draw_list->AddCircleFilled(start, 2.0f, IM_COL32(255, 255, 255, coreAlpha));

            draw_list->AddCircleFilled(end, 6.0f, IM_COL32(180, 100, 255, outerAlpha));
            draw_list->AddCircleFilled(end, 4.0f, IM_COL32(220, 140, 255, innerAlpha));
            draw_list->AddCircleFilled(end, 2.0f, IM_COL32(255, 255, 255, coreAlpha));

            // 8. искорки
            static float sparkTime = 0.0f;
            sparkTime += ImGui::GetIO().DeltaTime;
            if (sparkTime > 0.05f) {
                sparkTime = 0.0f;
                for (int i = 0; i < 3; i++) {
                    float t = (float)rand() / RAND_MAX;
                    ImVec2 sparkPos = ImVec2(
                        start.x + (end.x - start.x) * t,
                        start.y + (end.y - start.y) * t
                    );
                    float sparkOffsetX = (rand() % 10 - 5) * line.alpha;
                    float sparkOffsetY = (rand() % 10 - 5) * line.alpha;
                    draw_list->AddCircleFilled(
                        ImVec2(sparkPos.x + sparkOffsetX, sparkPos.y + sparkOffsetY),
                        2.0f,
                        IM_COL32(255, 255, 255, (int)(200 * line.alpha))
                    );
                }
            }
        }

        ++it;
    }
}
void CleanKillAuraLines() {
    static auto lastCleanTime = std::chrono::steady_clock::now();
    auto now = std::chrono::steady_clock::now();

    if (std::chrono::duration_cast<std::chrono::seconds>(now - lastCleanTime).count() >= 15) {
        g_KillAuraLines.erase(
            std::remove_if(g_KillAuraLines.begin(), g_KillAuraLines.end(),
                [](const KillAuraLine& line) { return !line.isActive || line.alpha <= 0.0f; }),
            g_KillAuraLines.end()
        );
        lastCleanTime = now;
    }
}
void DrawKillAuraRadius(void* camera)
{
    if (!camera) return;
    CleanKillAuraLines();
    DrawKillAuraLines(camera);

    auto entityManager = Huina::GetEntityManager();
    if (!entityManager) return;

    auto localAvatar = Huina::OFJHCHDOJGL(entityManager);
    if (!localAvatar) return;

    auto avatarGameObject = Huina::get_rootGameObject(localAvatar);
    if (!avatarGameObject) return;

    auto avatarTransform = UnityUtils::GetComponentByName(avatarGameObject,
        UnityUtils::PtrToStringAnsi((void*)("Transform")));
    if (!avatarTransform) return;

    Vector3 currentPos = UnityUtils::get_position(avatarTransform);
    if (currentPos.zero()) return;

    ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
    if (!draw_list) return;

    ImVec2 screenSize = ImGui::GetIO().DisplaySize;

    float height = 0.0f;
    int segments = 64;

    std::vector<ImVec2> circlePoints;

    for (int i = 0; i <= segments; i++) {
        float angle = (i * 360.0f / segments) * (3.14159f / 180.0f);

        Vector3 worldPoint = {
            currentPos.x + GuiState::combat.killauraRange * cos(angle),
            currentPos.y + height,
            currentPos.z + GuiState::combat.killauraRange * sin(angle)
        };

        Vector3 screenPoint = UnityUtils::WorldToScreenPoint(camera, worldPoint);

        if (screenPoint.z > 1.0f) {
            circlePoints.push_back(ImVec2(
                screenPoint.x,
                screenSize.y - screenPoint.y
            ));
        }
    }

    if (circlePoints.size() < 3) return;


    Vector3 centerScreen = UnityUtils::WorldToScreenPoint(camera, currentPos);
    if (centerScreen.z <= 1.0f) return;

    ImVec2 center = ImVec2(centerScreen.x, screenSize.y - centerScreen.y);

    static float pulseTime = 0.0f;
    pulseTime += 0.08f;
    float pulse = (sin(pulseTime * 2.0f) + 1.0f) * 0.5f;

    int gradientLayers = 12;
    float gradientWidth = 0.20f;

    for (int layer = 0; layer < gradientLayers; layer++) {

        float outerRadiusFactor = 1.0f - (float)layer / gradientLayers * gradientWidth;
        float innerRadiusFactor = 1.0f - (float)(layer + 1) / gradientLayers * gradientWidth;

        float colorIntensity = (float)layer / gradientLayers;

        int r = (int)(200 - 120 * colorIntensity);
        int g = (int)(140 - 100 * colorIntensity);
        int b = (int)(255 - 95 * colorIntensity);
        int alpha = (int)(60 * (1.0f - colorIntensity * 0.7f));

        ImU32 fillColor = IM_COL32(r, g, b, alpha);

        std::vector<ImVec2> outerRing;
        std::vector<ImVec2> innerRing;

        for (int i = 0; i <= segments; i++) {
            float angle = (i * 360.0f / segments) * (3.14159f / 180.0f);

            Vector3 outerWorld = {
                currentPos.x + GuiState::combat.killauraRange * outerRadiusFactor * cos(angle),
                currentPos.y + height,
                currentPos.z + GuiState::combat.killauraRange * outerRadiusFactor * sin(angle)
            };
            Vector3 outerScreen = UnityUtils::WorldToScreenPoint(camera, outerWorld);

            Vector3 innerWorld = {
                currentPos.x + GuiState::combat.killauraRange * innerRadiusFactor * cos(angle),
                currentPos.y + height,
                currentPos.z + GuiState::combat.killauraRange * innerRadiusFactor * sin(angle)
            };
            Vector3 innerScreen = UnityUtils::WorldToScreenPoint(camera, innerWorld);

            if (outerScreen.z > 1.0f && innerScreen.z > 1.0f) {
                outerRing.push_back(ImVec2(outerScreen.x, screenSize.y - outerScreen.y));
                innerRing.push_back(ImVec2(innerScreen.x, screenSize.y - innerScreen.y));
            }
        }
        if (outerRing.size() > 2 && innerRing.size() > 2) {
            for (size_t i = 0; i < outerRing.size() - 1; i++) {
                draw_list->AddQuadFilled(
                    outerRing[i],
                    outerRing[i + 1],
                    innerRing[i + 1],
                    innerRing[i],
                    fillColor
                );
            }
        }
    }
    int bloomAlpha = (int)(30 * (0.6f + pulse * 0.4f));
    ImU32 bloomGlow = IM_COL32(180, 120, 255, bloomAlpha);
    for (size_t i = 0; i < circlePoints.size() - 1; i++) {
        draw_list->AddLine(circlePoints[i], circlePoints[i + 1], bloomGlow, 10.0f);
    }
    draw_list->AddLine(circlePoints.back(), circlePoints[0], bloomGlow, 10.0f);
    int midAlpha = (int)(80 * (0.7f + pulse * 0.3f));
    ImU32 midGlow = IM_COL32(200, 140, 255, midAlpha);
    for (size_t i = 0; i < circlePoints.size() - 1; i++) {
        draw_list->AddLine(circlePoints[i], circlePoints[i + 1], midGlow, 5.0f);
    }
    draw_list->AddLine(circlePoints.back(), circlePoints[0], midGlow, 5.0f);
    int coreAlpha = (int)(150 * (0.8f + pulse * 0.2f));
    ImU32 innerGlow = IM_COL32(220, 160, 255, coreAlpha);
    for (size_t i = 0; i < circlePoints.size() - 1; i++) {
        draw_list->AddLine(circlePoints[i], circlePoints[i + 1], innerGlow, 3.0f);
    }
    draw_list->AddLine(circlePoints.back(), circlePoints[0], innerGlow, 3.0f);

    ImU32 sharpEdge = IM_COL32(255, 255, 255, 255);
    for (size_t i = 0; i < circlePoints.size() - 1; i++) {
        draw_list->AddLine(circlePoints[i], circlePoints[i + 1], sharpEdge, 1.5f);
    }
    draw_list->AddLine(circlePoints.back(), circlePoints[0], sharpEdge, 1.5f);
    draw_list->AddCircleFilled(center, 3.0f, IM_COL32(255, 255, 255, 200));
}
void drawRayCastHit(Vector3 enemyPos, Vector3 playerPos)
{
    if (GuiState::combat.fakeRayCastHit)
    {
        ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
        if (!draw_list) return;
        ImVec2 screenSize = ImGui::GetIO().DisplaySize;

        
        Vector3 enemyScreen = UnityUtils::WorldToScreenPoint(UnityUtils::get_main(), enemyPos);
        Vector3 playerScreen = UnityUtils::WorldToScreenPoint(UnityUtils::get_main(), playerPos);

        
            draw_list->AddLine(
                ImVec2(enemyScreen.x, screenSize.y - enemyScreen.y),
                ImVec2(playerScreen.x, screenSize.y - playerScreen.y),
                IM_COL32(255, 0, 255, 255),
                20.0f
            );
        
    }
}
void DrawPlayerTrail(void* camera) {
    if (!camera || g_PlayerTrail.empty()) return;

    ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
    if (!draw_list) return;

    ImVec2 screenSize = ImGui::GetIO().DisplaySize;
    float deltaTime = ImGui::GetIO().DeltaTime;

    std::vector<ImVec2> screenPoints;
    std::vector<float> alphas;

    for (auto it = g_PlayerTrail.begin(); it != g_PlayerTrail.end(); ) {
        TrailPoint& point = *it;
        point.lifetime += deltaTime;
        point.alpha = 1.0f - (point.lifetime / TRAIL_FADE_TIME);

        if (point.alpha <= 0.0f) {
            it = g_PlayerTrail.erase(it);
            continue;
        }

        Vector3 screenPos = UnityUtils::WorldToScreenPoint(camera, point.position);
        if (screenPos.z > 1.0f) {
            screenPoints.push_back(ImVec2(screenPos.x, screenSize.y - screenPos.y));
            alphas.push_back(point.alpha);
        }

        ++it;
    }

    if (screenPoints.size() < 2) return;
    ImU32 baseColor = ImColor(
        GuiState::combat.trailColor.x,
        GuiState::combat.trailColor.y,
        GuiState::combat.trailColor.z,
        1.0f
    );

    int r = (baseColor >> 0) & 0xFF;
    int g = (baseColor >> 8) & 0xFF;
    int b = (baseColor >> 16) & 0xFF;
    for (size_t i = 0; i < screenPoints.size() - 1; i++) {
        float avgAlpha = (alphas[i] + alphas[i + 1]) * 0.5f;
        float width = GuiState::combat.trailWidth * avgAlpha;

        if (GuiState::combat.trailGlow) {
            int outerAlpha = (int)(50 * avgAlpha);
            draw_list->AddLine(screenPoints[i], screenPoints[i + 1],
                IM_COL32(r, g, b, outerAlpha), width * 3.0f);

            int midAlpha = (int)(120 * avgAlpha);
            draw_list->AddLine(screenPoints[i], screenPoints[i + 1],
                IM_COL32(r, g, b, midAlpha), width * 2.0f);
        }

        int coreAlpha = (int)(255 * avgAlpha);
        draw_list->AddLine(screenPoints[i], screenPoints[i + 1],
            IM_COL32(r, g, b, coreAlpha), width);
        if (GuiState::combat.trailGlow) {
            draw_list->AddLine(screenPoints[i], screenPoints[i + 1],
                IM_COL32(255, 255, 255, coreAlpha / 2), width * 0.5f);
        }
    }
}
void AddTrailPoint(Vector3 position) {
    static float lastAddTime = 0.0f;
    float currentTime = ImGui::GetTime();
    if (currentTime - lastAddTime < TRAIL_ADD_INTERVAL) return;
    lastAddTime = currentTime;

    TrailPoint newPoint;
    newPoint.position = position;
    newPoint.lifetime = 0.0f;
    newPoint.alpha = 1.0f;

    g_PlayerTrail.push_back(newPoint);
    if (g_PlayerTrail.size() > MAX_TRAIL_POINTS) {
        g_PlayerTrail.erase(g_PlayerTrail.begin());
    }
}
void init_hooks() {
    MH_STATUS status = MH_Initialize();
    if (status != MH_OK) {
        Logger::log_err("Min initialization failed! Status: " + std::to_string(status));
        return;
    }
    Logger::log_info("Min initialized successfully!");

    //UpdateTick
	//hook_function(0x71f3f60, &MHPCHKLMBLI_hook, &MHPCHKLMBLI_original);
    hook_function(HookOffsets::BEJFLLLFKJC_ADBNDFCIION, &ADBNDFCIION_hook, &ADBNDFCIION_original);
	hook_function(HookOffsets::Update_hook, &Update_hook_, &Update_original);
	hook_function(HookOffsets::LateTick_hook, &LateTick_hook_, &LateTick_original);
    //Clean
 //   hook_function(HookOffsets::BEJFLLLFKJC_ACGLIMPHAIC, &ACGLIMPHAIC_hook, &ACGLIMPHAIC_original);
 //   hook_function(HookOffsets::BEJFLLLFKJC_BHAAEAGOGLF, &BHAAEAGOGLF_hook, &BHAAEAGOGLF_original);
 //   
 //   //movement
	hook_function(HookOffsets::DNEFDLJAEBM_BPMDIBJJFKF, &BPMDIBJJFKF_hook, &BPMDIBJJFKF_original); // inf stamina
	hook_function(HookOffsets::KBBLJHGMNLJ_IJEGLKJBGMB, &IJEGLKJBGMB_hook, &IJEGLKJBGMB_original); // cd
    //idk
	hook_function(HookOffsets::KDHNELOMKLG_hook, &KDHNELOMKLG_hook_, &KDHNELOMKLG_original);

 //   //attack
    hook_function(HookOffsets::LHMDIPAIAAK_CHOJPBDPNGJ, &CHOJPBDPNGJ_hook,&CHOJPBDPNGJ_original); // multi hit
	hook_function(HookOffsets::EEIMHEGPLAE_DCAHCDGAPKD, &DCAHCDGAPKD_hook, &DCAHCDGAPKD_original); // TickSkillCd
	hook_function(HookOffsets::EEIMHEGPLAE_GAIEPJNEFGM, &GAIEPJNEFGM_hook, &GAIEPJNEFGM_original); // inf ult
 
    Logger::log_info(OBFUSCATE("All hooks created"));
}



void Cleanup() {
    Logger::log_info("Cleaning up...");

    g_ShowMenu = false;
    if (ImGui::GetCurrentContext()) {
        ImGui::GetIO().MouseDrawCursor = false;
    }

    HWND gameWindow = FindWindowA("UnityWndClass", nullptr);
    if (!gameWindow) {
        gameWindow = FindWindowA(nullptr, "Genshin Impact");
    }

    if (gameWindow && g_OriginalWndProc) {
        SetWindowLongPtr(gameWindow, GWLP_WNDPROC, (LONG_PTR)g_OriginalWndProc);
        Logger::log_info("WindowProc hook restored");

        ClipCursor(nullptr);
        while (ShowCursor(TRUE) < 0);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    if (ImGui::GetCurrentContext()) {
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
        Logger::log_info("ImGui shutdown complete");
    }

    MH_DisableHook(MH_ALL_HOOKS);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    for (void* hookAddress : g_hooks) {
        MH_RemoveHook(hookAddress);
    }
    g_hooks.clear();

    MH_Uninitialize();
    Logger::log_info("MinHook cleanup complete");

    Logger::log_info("Cleanup completed successfully");
}

DWORD WINAPI UnloadThread(LPVOID param) {
    Sleep(500);
    FreeLibraryAndExitThread((HMODULE)param, 0);
    return 0;
}


DWORD WINAPI MainThread(LPVOID lpReserved) {
    AllocConsole();
    FILE* console;
    freopen_s(&console, "CONOUT$", "w", stdout);
    Logger::console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(Logger::console, 0x000F);

    initIl2cp();
    init_hooks();
   
    

    std::thread([&]() {
        while (true) {
            if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success) {
                while (kiero::bind(8, (void**)&oPresent11, hkPresent11) != kiero::Status::Success) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(200));
                }
                Logger::log_info("Using DX11");
                
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        }).detach();

    Logger::log_info("Press END to unload...");
    while (true) {
		if (GetAsyncKeyState(VK_END)) break;
		
		
    }
	
    Cleanup();
    if (console) fclose(console);
    FreeConsole();
    CreateThread(nullptr, 0, UnloadThread, lpReserved, 0, nullptr);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(module);
        CreateThread(nullptr, 0, MainThread, module, 0, nullptr);
    }
    return TRUE;
}