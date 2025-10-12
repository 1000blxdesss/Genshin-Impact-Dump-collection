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
    get_localScale = 0x11142d30,

    UnityEngine_Vector3_WorldToScreenPoint = 0x11137e10,
    UnityEngine_Camera_get_main = 0x111381f0,
    UnityEngine_Transform_get_position = 0x11142300,
    BEJFLLLFKJC_EFJJBJMJEPC = 0x71f4530,
    BEJFLLLFKJC_PNIIKPACAJM = 0x7200220,
    BEJFLLLFKJC_NJEDPEIHJEH = 0x71ebc80,
    GameObject_GetComponentByName = 0x11127990,
    InteropServices_Marshal_PtrToStringAnsi = 0x10b09790,
    SingletonManager_get_Instance = 0x51e3720,
    CollisionFlags_Move = 0x11188650,
    UnityEngine_Screen_get_width = 0x1114e390,
    UnityEngine_Screen_get_height = 0x1114e3a0,
    UnityEngine_Camera_get_pixelWidth = 0x11137780,
    UnityEngine_Camera_get_pixelHeight = 0x11137790,
};

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
        static auto fn = (fn_t)(GameBase + Offsets::UnityEngine_Vector3_WorldToScreenPoint);
        if (!fn) return Vector3{ 0,0,0 };
        return fn(__this, position);
    }
    // RVA: 0xb409b50 VA: 0x7ff7de4d9b50 public ONJBJICPCGE DPLHPDBOOND() {}
    inline void* get_main() {
        using fn_t = void* (__fastcall*)();
        static auto fn = (fn_t)(GameBase + Offsets::UnityEngine_Camera_get_main);
        if (!fn) return nullptr;
        return fn();
    }

    inline Vector3 get_position(void* _this) {
        using fn_t = Vector3(__fastcall*)(void* _this);
        static auto fn = (fn_t)(GameBase + Offsets::UnityEngine_Transform_get_position);
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
        static auto fn = (fn_t)(GameBase + Offsets::GameObject_GetComponentByName);
        if (!fn) return nullptr;
        return fn(__this, typeName);
    }

    // RVA: 0x10b09790 VA: 0x7ff7e3bd9790 public static System.String PtrToStringAnsi(System.IntPtr ptr) {}
    inline Il2CppString* PtrToStringAnsi(void* ptr) {
        using fn_t = Il2CppString * (*)(void* ptr);
        static auto fn = (fn_t)(GameBase + Offsets::InteropServices_Marshal_PtrToStringAnsi);
        if (!fn) return nullptr;
        return fn(ptr);
    }

    // RVA: 0x51e3720 VA: 0x7ff7d82b3720public static MoleMole.SingletonManager get_Instance() {}
    inline void* get_SingletonManager() {
        using fn_t = void* (*)();
        static auto fn = (fn_t)(GameBase + Offsets::SingletonManager_get_Instance);
        if (!fn) return nullptr;
        return fn();
    }
    inline int Screen_get_width() {
        using fn_t = int(*)();
        static auto fn = (fn_t)(GameBase + Offsets::UnityEngine_Screen_get_width);
        if (!fn) return 1920;
        return fn();
    }

    inline int Screen_get_height() {
        using fn_t = int(*)();
        static auto fn = (fn_t)(GameBase + Offsets::UnityEngine_Screen_get_height);
        if (!fn) return 1080;
        return fn();
    }

    inline int Camera_get_pixelWidth(void* camera) {
        using fn_t = int(__fastcall*)(void*);
        static auto fn = (fn_t)(GameBase + Offsets::UnityEngine_Camera_get_pixelWidth);
        if (!fn) return 1920;
        return fn(camera);
    }

    inline int Camera_get_pixelHeight(void* camera) {
        using fn_t = int(__fastcall*)(void*);
        static auto fn = (fn_t)(GameBase + Offsets::UnityEngine_Camera_get_pixelHeight);
        if (!fn) return 1080;
        return fn(camera);
    }

    // some vibecocoding
    inline Vector3 WorldToScreenPointCorrected(void* camera, Vector3 worldPos) {
        Vector3 screenPos = WorldToScreenPoint(camera, worldPos);

        if (screenPos.z <= 0) return screenPos;

        static int realScreenW = Screen_get_width();
        static int realScreenH = Screen_get_height();
        static int cameraPixelW = 0;
        static int cameraPixelH = 0;
        static int refreshCounter = 0;

        
        if (refreshCounter++ > 60) {
            realScreenW = Screen_get_width();
            realScreenH = Screen_get_height();
            if (camera) {
                cameraPixelW = Camera_get_pixelWidth(camera);
                cameraPixelH = Camera_get_pixelHeight(camera);
            }
            refreshCounter = 0;
        }

        if (cameraPixelW == 0 || cameraPixelH == 0) {
            cameraPixelW = realScreenW;
            cameraPixelH = realScreenH;
        }

        float scaleX = (float)realScreenW / (float)cameraPixelW;
        float scaleY = (float)realScreenH / (float)cameraPixelH;

        screenPos.x *= scaleX;
        screenPos.y *= scaleY;

        return screenPos;
    }
    // // RVA: 0x71f4530 VA: 0x7ff7da2c4530 public virtual UnityEngine.Vector3 EFJJBJMJEPC() {}
    inline Vector3 sub_1471f4530(void* __this)
    {
        using fn_t = Vector3(*)(void*);
        static auto fn = (fn_t)((uintptr_t)GameBase + Offsets::BEJFLLLFKJC_EFJJBJMJEPC);
        if (!fn) return Vector3();
        return fn(__this);
    }

    inline int64_t sub_147202AF0(void* __this)
    {
        using fn_t = int64_t(*)(void*);
        static auto fn = (fn_t)((uintptr_t)GameBase + Offsets::BEJFLLLFKJC_PNIIKPACAJM);
        if (!fn) return 0;
        return fn(__this);
    }
    // pointer to // RVA: 0x71ebc80 VA: 0x7ff7da2bbc80 public UnityEngine.GameObject NJEDPEIHJEH() {}
    inline void* get_rootGameObject(void* __this) {
        using fn_t = void* (__fastcall*)(void* __this);
        static auto fn = (fn_t)(GameBase + Offsets::BEJFLLLFKJC_NJEDPEIHJEH);
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
