#include "Globals.h"

#include <DebugMgr.h>
#include <Logger.h>
#include <SceneMgr.h>
#include <InputMgr.hpp>
#include <TextureMgr.h>

#include <Profiler.h>

Globals gData;

Globals::Globals() : FrameCount(0)
{
	InputMgr = new ::InputMgr();
	DebugMgr = new ::DebugMgr();
	Logger = new ::Logger();
	SceneMgr = new ::SceneMgr();
	TextureMgr = new ::TextureMgr();
}

Globals::~Globals()
{
	Destroy();
}

void Globals::Init()
{
	InputMgr->Init();
	Logger->Init();
	SceneMgr->Init();
	TextureMgr->Init();
}

void Globals::Update(float deltaTime)
{
	PROFILER_EVENT_BEGIN(PROFILER_COLOR_WHITE, "Compute Input");
	InputMgr->Update(deltaTime);
	PROFILER_EVENT_END();
	PROFILER_EVENT_BEGIN(PROFILER_COLOR_ORANGE, "Update Scene");
	SceneMgr->Update(deltaTime);
	PROFILER_EVENT_END();
}

void Globals::Shut()
{
	InputMgr->Shut();
	Logger->Shut();
	SceneMgr->Shut();
	TextureMgr->Shut();
}

void Globals::Destroy()
{
	delete InputMgr;
	InputMgr = nullptr;

	delete DebugMgr;
	DebugMgr = nullptr;

	delete Logger;
	Logger = nullptr;

	delete SceneMgr;
	SceneMgr = nullptr;

	delete TextureMgr;
	TextureMgr = nullptr;
}

void Globals::IncrementFrameCount()
{
	++FrameCount;
}
