import ida_bytes
import ida_search
import ida_idaapi
import ida_ida
import ida_segment


def find_pattern(pattern_string):
    byte_list = pattern_string.split()
    pattern_list = []

    for b_str in byte_list:
        if b_str == '??' or b_str == '?':
            pattern_list.append('??')
        else:
            try:
                int(b_str, 16)
                pattern_list.append(b_str)
            except ValueError:
                return ida_idaapi.BADADDR

    pattern_str = " ".join(pattern_list)
    start_addr = ida_ida.cvar.inf.min_ea
    end_addr = ida_ida.cvar.inf.max_ea

    addr = ida_search.find_binary(start_addr, end_addr, pattern_str, 16, ida_search.SEARCH_DOWN)
    return addr


def get_image_base():
    return 0x140000000


def main():
    patterns = {
        "TypeGetName_": "55 56 57 48 83 EC ? 48 8D 6C 24 ? 48 C7 45 ? ? ? ? ? 48 89 CA 0F 57 C0 0F 29 45 ? 48 C7 45 ? ? ? ? ? 48 C7 45",
        "ClassGetType_": "48 8D 41 ? C3 CC CC CC CC CC CC CC CC CC CC CC 56 57",
        "ClassGetNamespace_": "F6 81 ? ? ? ? ? 75 ? 0F B6 41 ? C1 E0 ? 3D ? ? ? ? 75 ? 8B 89 ? ? ? ? 48 8B 05",
        "ClassGetFlags_": "8B 81 ? ? ? ? C3 CC CC CC CC CC CC CC CC CC 0F B6 81 ? ? ? ? C0 E8",
        "Il2CppClassIsValueType": "0F B6 81 ? ? ? ? 24 ? C0 E8 ? C3 CC CC CC 8B 81",
        "ClassIsEnum": "0F B6 81 ? ? ? ? 24 ? C0 E8 ? C3 CC CC CC 48 8B 01",
        "ClassGetParent_": "8B 81 ? ? ? ? 48 85 C0 74 ? 48 8B 0D ? ? ? ? 48 03 01 C3 31 C0 C3 CC CC CC CC CC CC CC 8B 81",
        "ClassGetName_": "48 8B 81 ? ? ? ? C3 CC CC CC CC CC CC CC CC F6 81",
        "ClassGetMethods": "E9 ? ? ? ? CC CC CC CC CC CC CC CC CC CC CC E9 ? ? ? ? CC CC CC CC CC CC CC CC CC CC CC 48 83 EC ? C7 44 24",
        "MethodGetReturnType": "55 41 57 41 56 56 57 53 48 83 EC ? 48 8D 6C 24 ? 48 C7 45 ? ? ? ? ? 49 89 CF 48 8B 0D ? ? ? ? FF 15",
        "MethodGetName": "48 8B 51 ? 48 85 D2 74 ? 48 B8 ? ? ? ? ? ? ? ? 48 03 02",
        "MethodGetParamCount": "0F B6 41 ? C3 CC CC CC CC CC CC CC CC CC CC CC 56 48 83 EC ? 0F B6 41",
        "il2cpp_method_get_param": "56 48 83 EC ? 0F B6 41 ? 39 D0 76 ? 89 D6 48 8B 51 ? 48 85 D2 74 ? 48 B8 ? ? ? ? ? ? ? ? 48 03 42 ? 74 ? 89 F1 48 8D 0C 49 48 8B 04 C8",
        "MethodGetParamName": "56 48 83 EC ? 0F B6 41 ? 39 D0 76 ? 89 D6 48 8B 51 ? 48 85 D2 74 ? 48 B8 ? ? ? ? ? ? ? ? 48 03 42 ? 74 ? 89 F1 48 8D 0C 49 48 8B 44 C8",
        "ClassGetFields": "55 56 57 48 83 EC ? 48 8D 6C 24 ? 48 C7 45 ? ? ? ? ? 48 85 D2 74 ? 48 89 D6 48 89 CF 48 8B 02 48 85 C0 74 ? 48 83 C0 ? 48 8B 4F ? 0F B7 49",
        "FieldGetFlags": "48 B8 ? ? ? ? ? ? ? ? 48 33 01 0F B7 40",
        "FieldGetType": "48 B8 ? ? ? ? ? ? ? ? 48 33 01 C3 CC CC 4C 89 C0",
        "FieldGetName": "48 B8 ? ? ? ? ? ? ? ? 48 33 41 ? C3 CC 48 B8",
        "FieldStaticGetValue": "55 41 56 56 57 53 48 83 EC ? 48 8D 6C 24 ? 48 C7 45 ? ? ? ? ? 49 89 D6 48 89 CF 48 BE",
        "FieldGetOffset": "B8 ? ? ? ? 03 41 ? 25 ? ? ? ? C3"

    }

    image_base = get_image_base()
    print("enum Offsets {")

    for pattern_name, pattern_string in patterns.items():
        addr = find_pattern(pattern_string)
        if addr != ida_idaapi.BADADDR and addr is not None:
            rva = addr - image_base
            print(f"    {pattern_name} = 0x{rva:X}, // 0x{addr:X}")
        else:
            print(f"    {pattern_name} = 0x0, // not found")

    print("};")


if __name__ == "__main__":
    main()