#pragma once
#include "EBlackboard.h"
#include "IExamPlugin.h"
#include "Exam_HelperStructs.h"
#include "SteeringBehaviors.h"
#include "Behaviors.h"
#include "MyGlobals.h"

class IBaseInterface;
class IExamInterface;
class SteeringBehavior;
class MyGlobals;

class Plugin :public IExamPlugin
{
public:

	Plugin() {};
	virtual ~Plugin() {};

	void Initialize(IBaseInterface* pInterface, PluginInfo& info) override;
	void DllInit() override;
	void DllShutdown() override;

	void InitGameDebugParams(GameDebugParams& params) override;
	void Update(float dt) override;

	SteeringPlugin_Output UpdateSteering(float dt) override;
	void Render(float dt) const override;

private:
	//Interface, used to request data from/perform actions with the AI Framework
	IExamInterface* m_pInterface = nullptr;
	std::vector<HouseInfo> GetHousesInFOV() const;
	std::vector<EntityInfo> GetEntitiesInFOV() const;

	Elite::Vector2 m_Target = {};
	bool m_CanRun = false; //Demo purpose
	bool m_GrabItem = false; //Demo purpose
	bool m_UseItem = false; //Demo purpose
	bool m_RemoveItem = false; //Demo purpose
	float m_AngSpeed = 0.f; //Demo purpose
	Elite::Vector2 m_nextTargetPos;

	UINT m_InventorySlot = 0;

	Elite::Blackboard* m_pBlackboard = nullptr;

	SteeringBehavior* m_pSteeringBehavior = nullptr;
	SteeringPlugin_Output* m_pSteeringOutputData = nullptr;

	Elite::BehaviorTree* m_pBehaviorTree = nullptr;

	std::vector<EntityInfo>* m_pEntitiesInFOV = nullptr;
	std::vector<HouseInfo>* m_pHousesInFOV = nullptr;

	std::vector<HouseInfo>* m_pHousesChecked = nullptr;

	HouseInfo* m_pCurrentHouse = nullptr;

	GlobalsStruct* m_pMyGlobals = nullptr;
};

//ENTRY
//This is the first function that is called by the host program
//The plugin returned by this function is also the plugin used by the host program
extern "C"
{
	__declspec (dllexport) IPluginBase* Register()
	{
		return new Plugin();
	}
}