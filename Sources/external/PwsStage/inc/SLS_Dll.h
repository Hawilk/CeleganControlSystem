#ifdef SLS_DLL_EXPORTS
#define SLS_DLL_API extern "C"_declspec(dllexport)
#else
#define SLS_DLL_API extern "C"_declspec(dllimport)
#endif

/********m_handle为串口句柄 m_Axis表示运动轴ID*******/
//串口初始化 COM_Num表示串口数 返回串口句柄
SLS_DLL_API int InitCom(int COM_Num);

//初始化函数
SLS_DLL_API bool InitStage(int m_handle, int m_Axis, float m_Coe[]);

//去初始化函数 m_Axis表示运动轴ID
SLS_DLL_API void UnInitStage(int m_handle, int m_Axis);

//串口关闭
SLS_DLL_API void UnInitCom(int m_handle);

//运动函数（相对距离） m_MoveRelative 单位mm
SLS_DLL_API void MoveRelative(int m_handle, float m_MoveRelative, int m_Axis);
SLS_DLL_API void MoveRelative2(int m_handle, float m_MoveRelative, int m_Axis, int m_Axis2);

//运动函数（绝对距离） m_MoveAbsolute 单位mm
SLS_DLL_API void MoveAbsolute(int m_handle, float m_MoveAbsolute, int m_Axis);
SLS_DLL_API void MoveAbsolute2(int m_handle, float m_MoveAbsolute, int m_Axis, int m_Axis2);

//运动函数 等待完成（绝对距离）m_MoveAbsolute 单位mm
SLS_DLL_API void MoveAbsoluteWait(int m_handle, float m_MoveAbsolute, int m_Axis);

//运动函数 等待完成（相对距离）m_MoveRelative 单位mm
SLS_DLL_API void MoveRelativeWait(int m_handle, float m_MoveRelative, int m_Axis);

//速度设置函数 m_SpeedSet 单位mm/s
SLS_DLL_API void SpeedSet(int m_handle, float m_SpeedSet, int m_Axis);

//加减速设置函数 m_AcDecSet mm/s^2
SLS_DLL_API void AcDecSet(int m_handle, float m_AcDecSet, int m_Axis);

//设置脉冲+方向模式
SLS_DLL_API bool SetPulse(int m_handle, int m_Axis);

//立即停止
SLS_DLL_API void Stop(int m_handle, int m_Axis);

//获得当前位置函数 m_GetPosition[0]单位mm 返回true表示获取成功，false表示获取失败
SLS_DLL_API bool GetPosition(int m_handle, int m_Axis, double m_GetPosition[1]);

//回零函数
SLS_DLL_API void Home(int m_handle, int m_Axis);
//回零函数
SLS_DLL_API void HomeNew(int m_handle, int m_Axis);
//切换函数
SLS_DLL_API void Switch(int m_handle, int m_Axis, int m_Len);
//切换函数2 1 2 3 4 5表示对应的孔位 m_direction=true表示顺时针 false表示逆时针
SLS_DLL_API void Switch2(int m_handle, int m_Axis, int m_Len, bool m_direction);
//切换函数 1 2 3 4表示对应的孔位 m_direction=true表示顺时针 false表示逆时针
SLS_DLL_API void Switch_4(int m_handle, int m_Axis, int m_Len, bool m_direction);
//滤光轮切换函数
SLS_DLL_API void SwitchFilter(int m_handle, int m_Axis, int m_Filter);
//滤光轮切换函数
SLS_DLL_API void SwitchFilterOld(int m_handle, int m_Axis, int m_Filter);
//切换函数
SLS_DLL_API void SwitchLen(int m_handle, int m_Axis);

//切换函数
SLS_DLL_API void SwitchLenOld(int m_handle, int m_Axis);
//获取运动状态 m_GetStation[0]=true 表示在运动中 m_GetStation[0]=false表示运动完成 返回true表示获取成功，false表示获取失败
SLS_DLL_API bool GetStation(int m_handle, int m_Axis, bool m_GetStation[1]);
//获取运动状态 m_GetStation[0]=true 表示在运动中 m_GetStation[0]=false表示运动完成 返回true表示获取成功，false表示获取失败
SLS_DLL_API bool GetStation2(int m_handle, int m_Axis, bool m_GetStation[1]);

//设置当前位置 m_SetPosition单位mm
SLS_DLL_API bool SetPosition(int m_handle, double m_SetPosition, int m_Axis);

//电机去电
SLS_DLL_API bool Qudian(int m_handle, int m_Axis);

//设置IO口输出 m_IO=0或1 b_IO=true表示高电平 false表示低电平
SLS_DLL_API bool SetIO(int m_handle, int m_Axis, int m_IO, bool b_IO);

//获取回零状态 m_GetCall[0]=true 表示在运动中 m_GetCall[0]=false表示运动完成 m_Axis表示运动轴ID 返回true表示获取成功，false表示获取失败
SLS_DLL_API bool GetCall(int m_handle, int m_Axis, bool m_GetCall[1]);

//获取正限位开关状态 m_GetP[0]=true 高电平 m_GetP[0]=false低电平 m_Axis表示运动轴ID 返回true表示获取成功，false表示获取失败
SLS_DLL_API bool GetP(int m_handle, int m_Axis, bool m_GetP[1]);

//获取负限位开关状态 m_GetN[0]=true 高电平 m_GetN[0]=false低电平 m_Axis表示运动轴ID 返回true表示获取成功，false表示获取失败
SLS_DLL_API bool GetN(int m_handle, int m_Axis, bool m_GetN[1]);

//获取Dir状态 m_GetDir[0]=true 高电平 m_GetDir[0]=false低电平 m_Axis表示运动轴ID 返回true表示获取成功，false表示获取失败
SLS_DLL_API bool GetDir(int m_handle, int m_Axis, bool m_GetDir[1]);

//获取m_GetPulse状态 m_GetPulse[0]=true 高电平 m_GetPulse[0]=false低电平 m_Axis表示运动轴ID 返回true表示获取成功，false表示获取失败
SLS_DLL_API bool GetPulse(int m_handle, int m_Axis, bool m_GetPulse[1]);

//获得5孔当前孔位函数  m_GetLen[0]=1 2 3 4 5表示对应的孔位 返回true表示获取成功，false表示获取失败
SLS_DLL_API bool GetLen(int m_handle, int m_Axis, int m_GetLen[1]);
//获得4孔当前孔位函数  m_GetLen[0]=1 2 3 4表示对应的孔位 返回true表示获取成功，false表示获取失败
SLS_DLL_API bool GetLen_4(int m_handle, int m_Axis, int m_GetLen[1]);
//获得当前滤光轮孔位函数  m_GetFilter[0]=1 2 3 4 5 6表示对应的滤光轮孔位 返回true表示获取成功，false表示获取失败
SLS_DLL_API bool GetFilter(int m_handle, int m_Axis, int m_GetFilter[1]);

//获得当前速度函数 m_GetSpeed[0] 返回true表示获取成功，false表示获取失败
SLS_DLL_API bool GetSpeed(int m_handle, int m_Axis, double m_GetSpeed[1]);

//获得当前加速度函数 m_Axis表示运动轴ID m_GetAcDec[0] 返回true表示获取成功，false表示获取失败
SLS_DLL_API bool GetAcDec(int m_handle, int m_Axis, double m_GetAcDec[1]);

//限位开关是否起作用 enable=true表示起作用 false表示失效
SLS_DLL_API bool LimitEnable(int m_handle, int m_Axis, bool enable);

//滤光轮切换函数 1 2 3 4 5 6表示对应的孔位
SLS_DLL_API void SwitchFilter(int m_handle, int m_Axis, int m_Filter);

//获得当前滤光轮孔位函数  m_GetFilter[0]=1 2 3 4 5 6表示对应的滤光轮孔位 返回true表示获取成功，false表示获取失败
SLS_DLL_API bool GetFilter(int m_handle, int m_Axis, int m_GetFilter[1]);

//获取仓库信号 返回true表示获取成功，false表示获取失败
SLS_DLL_API bool GetSingle(int m_handle, int m_Axis, int m_GetSingle[1]);

//获取上电状态 ?srl m_GetPowerOnOff[0]=true 表示在上电 m_GetPowerOnOff[0]=false表示处于断电 m_Axis表示运动轴ID 返回true表示获取成功，false表示获取失败
SLS_DLL_API bool GetPowerOnOff(int m_handle, int m_Axis, int GetPowerOnOff[1]);