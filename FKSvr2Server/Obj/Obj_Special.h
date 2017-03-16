// Obj_Special.h
//
////////////////////////////////////////////////////////

#ifndef __OBJ_SPECIAL_H__
#define __OBJ_SPECIAL_H__

#include "Obj_Dynamic.h"
#include "DataRecords.h"

using namespace Combat_Module::Special_Obj_Module;

struct _OBJ_SPECIAL_INIT : public _OBJ_DYNAMIC_INIT
{
	_OBJ_SPECIAL_INIT( VOID )
	{
		m_nDataID=INVALID_ID;

	}

	virtual VOID CleanUp( VOID )
	{
		_OBJ_DYNAMIC_INIT::CleanUp();
		m_nDataID=INVALID_ID;
	}
	INT m_nDataID;
	ObjID_t m_nOwnerID;
};

class Obj_Special : public Obj_Dynamic
{
public :
	enum
	{
		NUM_OF_PARAMS = 8,
	};
	Obj_Special( VOID );
	virtual ~Obj_Special( VOID );

	virtual VOID	CleanUp( VOID );
	virtual BOOL	Init( const _OBJ_INIT *pInit );

	virtual ObjType	GetObjType( VOID )const{ return OBJ_TYPE_SPECIAL; }

	virtual BOOL	HeartBeat( UINT uTime = 0 );
	virtual BOOL	HeartBeat_OutZone( UINT uTime=0 );
	VOID			OnTick(VOID);
	VOID 			OnTimeOver(VOID);
	virtual BOOL	IsCanViewMe( const Obj *pObj );

public : //Accessor
	virtual Packet	*CreateNewObjPacket( VOID );
	virtual VOID	DestroyNewObjPacket( Packet *pPacket );
	Time_t			GetContinuance(void) const {return m_nContinuance;}
	VOID			SetContinuance(Time_t nTime){m_nContinuance=nTime;}
	Time_t			GetInterval(VOID) const {return m_nInterval;}
	VOID			SetInterval(Time_t nInterval) {m_nInterval=nInterval;}
	Time_t			GetElapsedInterval(VOID) const {return m_nInterval;}
	VOID			SetElapsedInterval(Time_t nTime) {m_nElapsedInterval=nTime;}
	Time_t			GetDelayTime(VOID) const {return m_nDelayTime;}
	VOID			SetDelayTime(Time_t nTime) {m_nDelayTime=nTime;}
	ObjID_t			GetOwnerID(VOID) const {return m_nOwner;}
	VOID			SetOwnerID(ObjID_t nID) {m_nOwner=nID;}
	INT				GetPowerRefixByValue(VOID) const {return m_nPowerRefixByValue;}
	VOID			SetPowerRefixByValue(INT nValue) {m_nPowerRefixByValue=nValue;};
	INT				GetPowerRefixByRate(VOID) const {return m_nPowerRefixByRate;}
	VOID			SetPowerRefixByRate(INT nRate) {m_nPowerRefixByRate=nRate;};
	BOOL			IsFadeOut(VOID) const {return m_bFadeOut;}
	VOID			MarkFadeOutFlag(VOID) {m_bFadeOut=TRUE;}
	VOID			ClearFadeOutFlag(VOID) {m_bFadeOut=FALSE;}
	INT				GetDataID(VOID) const {return m_nDataID;}
	VOID			SetDataID(INT nID) {m_nDataID=nID;}
	INT				GetStealthLevel(VOID) const {return m_nStealthLevel;}
	VOID			SetStealthLevel(INT nLevel) {m_nStealthLevel = nLevel;}
	ID_t			GetClass(VOID) const {return m_nClass;}
	VOID			SetClass(ID_t nClass){m_nClass=nClass;}
	INT				GetActiveTimes(VOID) {return m_nActiveTimes;}
	VOID			SetActiveTimes(INT nTimes) {m_nActiveTimes=nTimes;}
	SpecialObjData_T const* GetDataRecord(VOID) const;
public : //Interface
	VOID 			OnTrigger(ObjID_List const& rTargetList);
	VOID 			OnFadeOut(VOID);
	INT				GetParamByIndex(INT nIdx) const;
	VOID			SetParamByIndex(INT nIdx, INT nParam);
protected:
	BOOL			InitFromData();
private:
	Time_t	m_nContinuance;
	Time_t	m_nInterval;
	Time_t	m_nElapsedInterval;
	Time_t	m_nDelayTime;
	ObjID_t	m_nOwner;
	INT		m_nPowerRefixByValue;
	INT		m_nPowerRefixByRate;
	//INT		m_nOwnerLogicCount;
	INT		m_nDataID;
	INT		m_nStealthLevel;
	ID_t	m_nClass;
	BOOL	m_bActived;
	BOOL	m_bFadeOut;
	INT		m_nActiveTimes;
	INT		m_aParams[NUM_OF_PARAMS];
};
typedef struct _SPECIAL_OBJ_LIST
{
	enum
	{
		LIST_SIZE = 128,
	};
	Obj_Special*	m_aObj[LIST_SIZE] ;
	BYTE			m_Count ;
	VOID CleanUp(VOID)
	{
		memset((VOID*)m_aObj, NULL, sizeof(m_aObj));
		m_Count = 0;
	}
	_SPECIAL_OBJ_LIST( )
	{
		CleanUp();
	};
} SPECIAL_OBJ_LIST;
#endif	// __OBJ_SPECIAL_H__
