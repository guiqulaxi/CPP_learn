#pragma once
#include "game/BaseGameEntity.h"
#include "fsm/StateMachine.h"
#include "msg/Telegram.h"
#include"Locations.h"
#include"MinerOwnedStates.h"


//the amount of gold a miner must have before he feels comfortable
const int ComfortLevel = 5;
//the amount of nuggets a miner can carry
const int MaxNuggets = 3;
//above this value a miner is thirsty
const int ThirstLevel = 5;
//above this value a miner is hungry
const int HsungerLevel = 5;
//above this value a miner is sleepy
const int TirednessThreshold = 5;
//above this value a miner is sleepy


class Miner :
	public BaseGameEntity
{
public:
	Miner::Miner(int id) : BaseGameEntity(id),
		m_Location(shack),
		m_iGoldCarried(0),
		m_iMoneyInBank(0),
		m_iThirst(0),
		m_iFatigue(0)
	{

			m_pStateMachine = new StateMachine<Miner>(this);

		m_pStateMachine->SetCurrentState(GoHomeAndSleepTillRested::Instance());
	}


	Miner::~Miner()
	{
		delete m_pStateMachine;
	}

	void Update();
	
	location_type Location()const{ return m_Location; }
	void ChangeLocation(const location_type loc){ m_Location = loc; }

	int  GoldCarried()const{ return m_iGoldCarried; }
	void SetGoldCarried(const int val){ m_iGoldCarried = val; }
	void AddToGoldCarried(const int val);
	bool PocketsFull()const{ return m_iGoldCarried >= MaxNuggets; }
 
	bool Fatigued()const;
	void DecreaseFatigue(){ m_iFatigue -= 1; }
	void IncreaseFatigue(){ m_iFatigue += 1; }

	int Wealth()const{ return m_iMoneyInBank; }
	void SetWealth(const int val){ m_iMoneyInBank = val; }
	void AddToWealth(const int val);

	bool Thirsty()const;
	bool Poverty()const;

	void BuyAndDrinkAWhiskey(){ m_iThirst = 0; m_iMoneyInBank -= 2; }
	//休息也要花钱
	void Rest();

	StateMachine<Miner>*  GetFSM()const{ return m_pStateMachine; }

	//处理消息
	virtual bool  HandleMessage(const Telegram& msg);
private:
	StateMachine<Miner>*  m_pStateMachine;
	
	location_type m_Location;
	int m_iGoldCarried;
	int m_iMoneyInBank;
	//越高，越口渴
	int m_iThirst;
	//越高，矿工越累
	int m_iFatigue;
	//越高 ，越饿
	int m_iHunger;
};













