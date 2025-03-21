#include <string>
#include "vmt.hpp"

void* Create_Material(__int8 shouldIgnoreZ, __int8 isLit, __int8 isWireframe)
{
	static __int32 Created = 0;

	static std::string Tmp
	{
		"\"%s\"\
		\n{\
		\n\t\"$basetexture\" \"vgui/white_additive\"\
		\n\t\"$envmap\" \"\"\
		\n\t\"$model\" \"1\"\
		\n\t\"$flat\" \"0\"\
		\n\t\"$nocull\" \"0\"\
		\n\t\"$selfillum\" \"1\"\
		\n\t\"$halflambert\" \"1\"\
		\n\t\"$nofog\" \"0\"\
		\n\t\"$ignorez\" \"%i\"\
		\n\t\"$znearer\" \"0\"\
		\n\t\"$wireframe\" \"%i\"\
        \n}\n"
	};

	char Material[512];
	sprintf(Material, Tmp.c_str(), (isLit == 1 ? "VertexLitGeneric" : "UnlitGeneric"), (shouldIgnoreZ) ? 1 : 0, (isWireframe) ? 1 : 0);

	char Name[512];
	sprintf(Name, "#Error_Chams%i.vmt", Created);
	++Created;

	void* Key_Values = __builtin_malloc(36);

	using Key_Values_Type = void(__thiscall*)(void* Key_Values, char* Name);

	Key_Values_Type(539108192)(Key_Values, (char*)(isLit == 1 ? "VertexLitGeneric" : "UnlitGeneric"));

	using Load_From_Buffer_Type = __int8(__thiscall*)(void* Key_Values, char*, char*, void*, char*);

	Load_From_Buffer_Type(539119808)(Key_Values, Name, Material, nullptr, nullptr);

	using Create_Material_Type = void* (__thiscall*)(void* Material_System, char* Name, void* Key_Values);

	void* Created_Material = Create_Material_Type(*(unsigned __int32*)(**(unsigned __int32**)608277768 + 492))(*(void**)608277768, Name, Key_Values);

	return Created_Material;
}

void* Original_Draw_Model_Caller;

void __thiscall Redirected_Draw_Model(void* Studio_Render, void* Model_Info, void* a, void* b, void* d, __int32 Unknown_Parameter_6)
{
	static void* CoveredLit = Create_Material(true, true, false);
	static void* OpenLit = Create_Material(false, true, false);
	//static void* CoveredFlat = Create_Material(true, false, false);
	//static void* OpenFlat = Create_Material(false, false, false);

	void* Local_Player = *(void**)607867332;

	if (!Local_Player)
		return (decltype(&Redirected_Draw_Model)(Original_Draw_Model_Caller))(Studio_Render, Model_Info, a, b, d, Unknown_Parameter_6);

	void* Entity = *(void**)((unsigned __int32)Model_Info + 24);

	if (!Entity)
		return (decltype(&Redirected_Draw_Model)(Original_Draw_Model_Caller))(Studio_Render, Model_Info, a, b, d, Unknown_Parameter_6);

	void* Model = (*(void* (__thiscall**)(void*))(*(unsigned __int32*)Entity + 32))(Entity);

	using Get_Model_Name_Type = char* (__thiscall*)(void* Model_Info, void* Model);

	char* Model_Name = Get_Model_Name_Type(537875232)(*(void**)607906436, Model);

	using Forced_Material_Override_Type = void(__thiscall*)(void* Model_Render, void* Material, __int32 Type);

	using Set_Color_Modulation_Type = void(__thiscall*)(void* Render_View, float*);

	if (strstr(Model_Name, "models/player"))
	{
		if (*(__int32*)((unsigned __int32)Entity + 144) != *(__int32*)((unsigned __int32)Local_Player + 144))
		{
			float Color[4] = { };

			float Color2[4] = { };

			Color[0] = 1.f; 

			Color[1] = 0.f; 

			Color[2] = 0.f; 

			Color[3] = 1.f;

			Set_Color_Modulation_Type(738205648)(Studio_Render, Color);

			Forced_Material_Override_Type(738227264)(Studio_Render, CoveredLit, 0);

			(decltype(&Redirected_Draw_Model)(Original_Draw_Model_Caller))(Studio_Render, Model_Info, a, b, d, Unknown_Parameter_6);

			Color2[0] = 1.f;

			Color2[1] = 1.f;  

			Color2[2] = 0.f;  

			Color2[3] = 1.f;

			Set_Color_Modulation_Type(738205648)(Studio_Render, Color2);

			Forced_Material_Override_Type(738227264)(Studio_Render, OpenLit, 0);
		}
	}
	else
		Forced_Material_Override_Type(738227264)(Studio_Render, nullptr, 0);

	(decltype(&Redirected_Draw_Model)(Original_Draw_Model_Caller))(Studio_Render, Model_Info, a, b, d, Unknown_Parameter_6);

	Forced_Material_Override_Type(738227264)(Studio_Render, nullptr, 0);
}