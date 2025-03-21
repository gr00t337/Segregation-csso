#include <Windows.h>

#include <TlHelp32.h>

#include <cstdio>

#include "Byte_Manager/Byte_Manager.hpp"

#include "Redirection_Manager/Redirection_Manager.hpp"

void* Engine_Module;

#include "Extended_Interface.hpp"

#include <unordered_map>

#include "Post_Network_Data_Received.hpp"

#pragma comment(lib, "WinMM.Lib")

#include "Sounds.hpp"

#include "Event_Processor.hpp"

#include "Write_Events.hpp"

#include "Shutdown.hpp"

#include "Post_Data_Update.hpp"

#include "Interpolate.hpp"

#include "Update_Animation.hpp"

#include "Compute_Torso_Rotation.hpp"

#include "Setup_Move.hpp"

#include "Fall_Damage.hpp"

#include <algorithm>

#include "Finish_Move.hpp"

#include "Item_Post_Frame.hpp"

#include "Weapon_Spread.hpp"

#include "Read_Packets.hpp"

#include "Move.hpp"

#include "Send_Move.hpp"

#include "Send_Datagram.hpp"

#include "Packet_Start.hpp"

#include <vector>

#include "Copy_Command.hpp"

#include "Draw_Crosshair.hpp"

#include "Precache.hpp"

__int32 __stdcall DllMain(HMODULE This_Module, unsigned __int32 Call_Reason, void* Reserved)
{
	if (Call_Reason == DLL_PROCESS_DETACH)
	{
		__fastfail(EXIT_SUCCESS);
	}
	else
	{
		if (Call_Reason == DLL_PROCESS_ATTACH)
		{
			if (GetModuleHandleW(L"cstrike_win64.exe") == nullptr)
			{
				void* Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

				PROCESSENTRY32W Snapshot_Entry;

				Snapshot_Entry.dwSize = sizeof(Snapshot_Entry);

				Traverse_Snapshot_Label:
				{
					if (Process32NextW(Snapshot, &Snapshot_Entry) == 0)
					{
						return 1;
					}

					if (wcscmp(Snapshot_Entry.szExeFile, L"cstrike_win64.exe") != 0)
					{
						goto Traverse_Snapshot_Label;
					}
				}

				void* Process = OpenProcess(PROCESS_ALL_ACCESS, 0, Snapshot_Entry.th32ProcessID);

				void* Remote_Path = VirtualAllocEx(Process, nullptr, 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

				wchar_t Local_Path[MAX_PATH];

				GetModuleFileNameW(This_Module, Local_Path, sizeof(Local_Path));

				WriteProcessMemory(Process, Remote_Path, Local_Path, sizeof(Local_Path), nullptr);

				WaitForSingleObject(CreateRemoteThread(Process, nullptr, 0, (LPTHREAD_START_ROUTINE)LoadLibraryW, Remote_Path, 0, nullptr), INFINITE);

				VirtualFreeEx(Process, Remote_Path, 0, MEM_RELEASE);
			}
			else
			{
				AllocConsole();

				SetConsoleTitleW(L"Segregation");

				_wfreopen(L"CONOUT$", L"w", stdout);

				SetConsoleOutputCP(65001);

				HANDLE Standard_Output_Handle = GetStdHandle(STD_OUTPUT_HANDLE);

				CONSOLE_FONT_INFOEX Console_Font_Information = { sizeof(CONSOLE_FONT_INFOEX), 0, { 0, 12 }, FF_DONTCARE, FW_NORMAL, { L"Terminal" } };

				SetCurrentConsoleFontEx(Standard_Output_Handle, 0, &Console_Font_Information);

				CONSOLE_CURSOR_INFO Console_Cursor_Information;

				Console_Cursor_Information.bVisible = 0;

				Console_Cursor_Information.dwSize = sizeof(Console_Cursor_Information);

				SetConsoleTextAttribute(Standard_Output_Handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_RED);

				SetConsoleCursorInfo(Standard_Output_Handle, &Console_Cursor_Information);

				CONSOLE_SCREEN_BUFFER_INFO Console_Screen_Buffer_Information;

				GetConsoleScreenBufferInfo(Standard_Output_Handle, &Console_Screen_Buffer_Information);

				COORD Top_Left = { };

				DWORD Characters_Written;

				FillConsoleOutputAttribute(Standard_Output_Handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_RED, Console_Screen_Buffer_Information.dwSize.X * Console_Screen_Buffer_Information.dwSize.Y, Top_Left, &Characters_Written);

				Engine_Module = GetModuleHandleW(L"engine.dll");

				_putws(L"[ + ] Delimit Interface");
				{
					unsigned __int8 Cheat_Flag_Bytes[4] = { 254, 65, 44, 195 };

					Byte_Manager::Copy_Bytes(0, (void*)((unsigned __int32)Engine_Module + 1631348), sizeof(Cheat_Flag_Bytes), Cheat_Flag_Bytes);

					*(__int8*)((void*)((unsigned __int32)Engine_Module + 7622512)) = 1;

					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int32)Engine_Module + 1848181), 1, 235);
				}

				_putws(L"[ + ] Extend Interface");
				{
					Implement_Extended_Interface();
				}

				_putws(L"[ + ] Events");
				{
					//Byte_Manager::Set_Bytes(0, (void*)((unsigned __int32)Client_Module + 766673), 1, 0);

					//Original_Post_Network_Data_Received_Caller = Redirection_Manager::Redirect_Function(0, (void*)605205024, (void*)Redirected_Post_Network_Data_Received);

					///Byte_Manager::Set_Bytes(0, (void*)((unsigned __int32)Engine_Module + 1019988), 1, 235);

					//void* Event_Listener = (void*)__builtin_malloc(sizeof(void*));

					//void* Event_Listener_Table = __builtin_malloc(sizeof(void*) * 2);

					//*(void**)((unsigned __int32)Event_Listener_Table + 4) = (void*)Event_Processor;

					//*(void**)Event_Listener = Event_Listener_Table;

					//using Add_Listener_Type = __int8(__thiscall*)(void* Event_Manager, void* Listener, char* Event, void* Unknown_Parameter);

					//Add_Listener_Type((unsigned __int32)Engine_Module + 1966272)((void*)((unsigned __int32)Engine_Module + 7750640), Event_Listener, (char*)"player_hurt", nullptr);

					//Add_Listener_Type((unsigned __int32)Engine_Module + 1966272)((void*)((unsigned __int32)Engine_Module + 7750640), Event_Listener, (char*)"player_death", nullptr);

					//Add_Listener_Type((unsigned __int32)Engine_Module + 1966272)((void*)((unsigned __int32)Engine_Module + 7750640), Event_Listener, (char*)"bullet_impact", nullptr);

					//Original_Write_Events_Caller = Redirection_Manager::Redirect_Function(2, (void*)((unsigned __int32)Engine_Module + 1973888), (void*)Redirected_Write_Events);

					Original_Shutdown_Caller = Redirection_Manager::Redirect_Function(0, (void*)((unsigned __int32)Engine_Module + 2203904), (void*)Redirected_Shutdown);

					///Original_Post_Data_Update_Caller = Redirection_Manager::Redirect_Function(1, (void*)605796576, (void*)Redirected_Post_Data_Update);
				}

				_putws(L"[ + ] Interpolation");
				{
					///Original_Interpolate_Caller = Redirection_Manager::Redirect_Function(0, (void*)604201536, (void*)Redirected_Interpolate);

					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int32)Client_Module + 6843894), 2, 0);
				}

				_putws(L"[ + ] Animations");
				{
					///Original_Update_Animation_Caller = Redirection_Manager::Redirect_Function(4, (void*)605800256, (void*)Redirected_Update_Animation);

					///Byte_Manager::Set_Bytes(0, (void*)605800287, 1, 235);

					///Byte_Manager::Set_Bytes(0, (void*)604287917, 2, 144);

					///Original_Compute_Torso_Rotation_Caller = Redirection_Manager::Redirect_Function(1, (void*)604022496, (void*)Redirected_Compute_Torso_Rotation);

					///unsigned __int8 Maintain_Sequence_Transitions_Bytes[3] = { 194, 24 };

					///Byte_Manager::Copy_Bytes(0, (void*)604206416, sizeof(Maintain_Sequence_Transitions_Bytes), Maintain_Sequence_Transitions_Bytes);

					///Byte_Manager::Set_Bytes(0, (void*)604199650, 14, 144);
				}

				_putws(L"[ + ] Prediction");
				{
					static Prediction_Descriptor_Structure Original_Prediction_Descriptor;

					Prediction_Descriptor_Structure* Prediction_Descriptor = (Prediction_Descriptor_Structure*)((unsigned __int32)Client_Module + 6890952);

					static Prediction_Field_Structure Prediction_Fields = { 1, (char*)"m_flVelocityModifier", { 40112 }, 1, 256, { }, nullptr, sizeof(float), { }, 0.005f };

					Prediction_Descriptor->Fields = &Prediction_Fields;

					Prediction_Descriptor->Size = sizeof(Prediction_Fields) / sizeof(Prediction_Field_Structure);

					Prediction_Descriptor->Parent = &Original_Prediction_Descriptor;

					///Byte_Manager::Set_Bytes(0, (void*)((unsigned __int32)Engine_Module + 991017), 13, 144);

					///Byte_Manager::Set_Bytes(0, (void*)((unsigned __int32)Engine_Module + 1026281), 5, 144);

					///Byte_Manager::Set_Bytes(0, (void*)605209595, 1, 235);

					Original_Setup_Move_Caller = Redirection_Manager::Redirect_Function(0, (void*)((unsigned __int32)Client_Module + 1811728), (void*)Redirected_Setup_Move);

					///Redirection_Manager::Redirect_Function((void*)605024544, (void*)Redirected_Fall_Damage);

					Original_Finish_Move_Caller = Redirection_Manager::Redirect_Function(1, (void*)((unsigned __int32)Client_Module + 1806880), (void*)Redirected_Finish_Move);

					///Original_Item_Post_Frame_Caller = Redirection_Manager::Redirect_Function(0, (void*)604081184, (void*)Redirected_Item_Post_Frame);

					///Byte_Manager::Set_Bytes(0, (void*)605954536, 9, 144);

					///Original_Weapon_Spread_Caller = Redirection_Manager::Redirect_Function(1, (void*)605949248, (void*)Redirected_Weapon_Spread);
				}

				_putws(L"[ + ] Network");
				{
					///Original_Read_Packets_Caller = Redirection_Manager::Redirect_Function(1, (void*)((unsigned __int32)Engine_Module + 1006704), (void*)Redirected_Read_Packets);

					///Original_Move_Caller = Redirection_Manager::Redirect_Function(0, (void*)((unsigned __int32)Engine_Module + 1005520), (void*)Redirected_Move);

					//Redirection_Manager::Redirect_Function((void*)537142224, (void*)Redirected_Send_Move);

					//Original_Send_Datagram_Caller = Redirection_Manager::Redirect_Function(4, (void*)537933616, (void*)Redirected_Send_Datagram);

					//*(__int32*)((unsigned __int32)Original_Send_Datagram_Caller + 6) = (__int32)539639430 - (__int32)Original_Send_Datagram_Caller;

					//Original_Packet_Start_Caller = Redirection_Manager::Redirect_Function(2, (void*)538164112, (void*)Redirected_Packet_Start);
				}

				_putws(L"[ + ] Input");
				{
					///Byte_Manager::Set_Bytes(0, (void*)604993824, 3, 144);

					///Original_Copy_Command_Caller = Redirection_Manager::Redirect_Function(0, (void*)604850464, (void*)Redirected_Copy_Command);
				}

				_putws(L"[ + ] View Effects");
				{
					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int32)Client_Module + 91175), 36, 144);
				}

				_putws(L"[ + ] Crosshair");
				{
					Redirection_Manager::Redirect_Function((void*)((unsigned __int32)Client_Module + 2943808), (void*)Redirected_Draw_Crosshair);
				}

				_putws(L"[ + ] Materials");
				{
					Original_Precache_Caller = Redirection_Manager::Redirect_Function(1, (void*)((unsigned __int32)GetModuleHandleW(L"materialsystem.dll") + 248032), (void*)Redirected_Precache);

					//Byte_Manager::Set_Bytes(0, (void*)((unsigned __int32)Client_Module + 2035304), 2, 144);

					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int32)Client_Module + 2134168), 1, 235);

					//Byte_Manager::Set_Bytes(0, (void*)((unsigned __int32)Client_Module + 2328912), 1, 195);

					unsigned __int8 Smoke_Bytes[3] = { 194, 8 };

					Byte_Manager::Copy_Bytes(0, (void*)((unsigned __int32)Client_Module + 3107056), sizeof(Smoke_Bytes), Smoke_Bytes);

					//Byte_Manager::Set_Bytes(0, (void*)((unsigned __int32)Client_Module + 2229392), 1, 195);
				}
			}
		}
	}

	return 1;
}