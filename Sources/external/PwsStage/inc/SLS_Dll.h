#ifdef SLS_DLL_EXPORTS
#define SLS_DLL_API extern "C"_declspec(dllexport)
#else
#define SLS_DLL_API extern "C"_declspec(dllimport)
#endif

/********m_handleΪ���ھ�� m_Axis��ʾ�˶���ID*******/
//���ڳ�ʼ�� COM_Num��ʾ������ ���ش��ھ��
SLS_DLL_API int InitCom(int COM_Num);

//��ʼ������
SLS_DLL_API bool InitStage(int m_handle, int m_Axis, float m_Coe[]);

//ȥ��ʼ������ m_Axis��ʾ�˶���ID
SLS_DLL_API void UnInitStage(int m_handle, int m_Axis);

//���ڹر�
SLS_DLL_API void UnInitCom(int m_handle);

//�˶���������Ծ��룩 m_MoveRelative ��λmm
SLS_DLL_API void MoveRelative(int m_handle, float m_MoveRelative, int m_Axis);
SLS_DLL_API void MoveRelative2(int m_handle, float m_MoveRelative, int m_Axis, int m_Axis2);

//�˶����������Ծ��룩 m_MoveAbsolute ��λmm
SLS_DLL_API void MoveAbsolute(int m_handle, float m_MoveAbsolute, int m_Axis);
SLS_DLL_API void MoveAbsolute2(int m_handle, float m_MoveAbsolute, int m_Axis, int m_Axis2);

//�˶����� �ȴ���ɣ����Ծ��룩m_MoveAbsolute ��λmm
SLS_DLL_API void MoveAbsoluteWait(int m_handle, float m_MoveAbsolute, int m_Axis);

//�˶����� �ȴ���ɣ���Ծ��룩m_MoveRelative ��λmm
SLS_DLL_API void MoveRelativeWait(int m_handle, float m_MoveRelative, int m_Axis);

//�ٶ����ú��� m_SpeedSet ��λmm/s
SLS_DLL_API void SpeedSet(int m_handle, float m_SpeedSet, int m_Axis);

//�Ӽ������ú��� m_AcDecSet mm/s^2
SLS_DLL_API void AcDecSet(int m_handle, float m_AcDecSet, int m_Axis);

//��������+����ģʽ
SLS_DLL_API bool SetPulse(int m_handle, int m_Axis);

//����ֹͣ
SLS_DLL_API void Stop(int m_handle, int m_Axis);

//��õ�ǰλ�ú��� m_GetPosition[0]��λmm ����true��ʾ��ȡ�ɹ���false��ʾ��ȡʧ��
SLS_DLL_API bool GetPosition(int m_handle, int m_Axis, double m_GetPosition[1]);

//���㺯��
SLS_DLL_API void Home(int m_handle, int m_Axis);
//���㺯��
SLS_DLL_API void HomeNew(int m_handle, int m_Axis);
//�л�����
SLS_DLL_API void Switch(int m_handle, int m_Axis, int m_Len);
//�л�����2 1 2 3 4 5��ʾ��Ӧ�Ŀ�λ m_direction=true��ʾ˳ʱ�� false��ʾ��ʱ��
SLS_DLL_API void Switch2(int m_handle, int m_Axis, int m_Len, bool m_direction);
//�л����� 1 2 3 4��ʾ��Ӧ�Ŀ�λ m_direction=true��ʾ˳ʱ�� false��ʾ��ʱ��
SLS_DLL_API void Switch_4(int m_handle, int m_Axis, int m_Len, bool m_direction);
//�˹����л�����
SLS_DLL_API void SwitchFilter(int m_handle, int m_Axis, int m_Filter);
//�˹����л�����
SLS_DLL_API void SwitchFilterOld(int m_handle, int m_Axis, int m_Filter);
//�л�����
SLS_DLL_API void SwitchLen(int m_handle, int m_Axis);

//�л�����
SLS_DLL_API void SwitchLenOld(int m_handle, int m_Axis);
//��ȡ�˶�״̬ m_GetStation[0]=true ��ʾ���˶��� m_GetStation[0]=false��ʾ�˶���� ����true��ʾ��ȡ�ɹ���false��ʾ��ȡʧ��
SLS_DLL_API bool GetStation(int m_handle, int m_Axis, bool m_GetStation[1]);
//��ȡ�˶�״̬ m_GetStation[0]=true ��ʾ���˶��� m_GetStation[0]=false��ʾ�˶���� ����true��ʾ��ȡ�ɹ���false��ʾ��ȡʧ��
SLS_DLL_API bool GetStation2(int m_handle, int m_Axis, bool m_GetStation[1]);

//���õ�ǰλ�� m_SetPosition��λmm
SLS_DLL_API bool SetPosition(int m_handle, double m_SetPosition, int m_Axis);

//���ȥ��
SLS_DLL_API bool Qudian(int m_handle, int m_Axis);

//����IO����� m_IO=0��1 b_IO=true��ʾ�ߵ�ƽ false��ʾ�͵�ƽ
SLS_DLL_API bool SetIO(int m_handle, int m_Axis, int m_IO, bool b_IO);

//��ȡ����״̬ m_GetCall[0]=true ��ʾ���˶��� m_GetCall[0]=false��ʾ�˶���� m_Axis��ʾ�˶���ID ����true��ʾ��ȡ�ɹ���false��ʾ��ȡʧ��
SLS_DLL_API bool GetCall(int m_handle, int m_Axis, bool m_GetCall[1]);

//��ȡ����λ����״̬ m_GetP[0]=true �ߵ�ƽ m_GetP[0]=false�͵�ƽ m_Axis��ʾ�˶���ID ����true��ʾ��ȡ�ɹ���false��ʾ��ȡʧ��
SLS_DLL_API bool GetP(int m_handle, int m_Axis, bool m_GetP[1]);

//��ȡ����λ����״̬ m_GetN[0]=true �ߵ�ƽ m_GetN[0]=false�͵�ƽ m_Axis��ʾ�˶���ID ����true��ʾ��ȡ�ɹ���false��ʾ��ȡʧ��
SLS_DLL_API bool GetN(int m_handle, int m_Axis, bool m_GetN[1]);

//��ȡDir״̬ m_GetDir[0]=true �ߵ�ƽ m_GetDir[0]=false�͵�ƽ m_Axis��ʾ�˶���ID ����true��ʾ��ȡ�ɹ���false��ʾ��ȡʧ��
SLS_DLL_API bool GetDir(int m_handle, int m_Axis, bool m_GetDir[1]);

//��ȡm_GetPulse״̬ m_GetPulse[0]=true �ߵ�ƽ m_GetPulse[0]=false�͵�ƽ m_Axis��ʾ�˶���ID ����true��ʾ��ȡ�ɹ���false��ʾ��ȡʧ��
SLS_DLL_API bool GetPulse(int m_handle, int m_Axis, bool m_GetPulse[1]);

//���5�׵�ǰ��λ����  m_GetLen[0]=1 2 3 4 5��ʾ��Ӧ�Ŀ�λ ����true��ʾ��ȡ�ɹ���false��ʾ��ȡʧ��
SLS_DLL_API bool GetLen(int m_handle, int m_Axis, int m_GetLen[1]);
//���4�׵�ǰ��λ����  m_GetLen[0]=1 2 3 4��ʾ��Ӧ�Ŀ�λ ����true��ʾ��ȡ�ɹ���false��ʾ��ȡʧ��
SLS_DLL_API bool GetLen_4(int m_handle, int m_Axis, int m_GetLen[1]);
//��õ�ǰ�˹��ֿ�λ����  m_GetFilter[0]=1 2 3 4 5 6��ʾ��Ӧ���˹��ֿ�λ ����true��ʾ��ȡ�ɹ���false��ʾ��ȡʧ��
SLS_DLL_API bool GetFilter(int m_handle, int m_Axis, int m_GetFilter[1]);

//��õ�ǰ�ٶȺ��� m_GetSpeed[0] ����true��ʾ��ȡ�ɹ���false��ʾ��ȡʧ��
SLS_DLL_API bool GetSpeed(int m_handle, int m_Axis, double m_GetSpeed[1]);

//��õ�ǰ���ٶȺ��� m_Axis��ʾ�˶���ID m_GetAcDec[0] ����true��ʾ��ȡ�ɹ���false��ʾ��ȡʧ��
SLS_DLL_API bool GetAcDec(int m_handle, int m_Axis, double m_GetAcDec[1]);

//��λ�����Ƿ������� enable=true��ʾ������ false��ʾʧЧ
SLS_DLL_API bool LimitEnable(int m_handle, int m_Axis, bool enable);

//�˹����л����� 1 2 3 4 5 6��ʾ��Ӧ�Ŀ�λ
SLS_DLL_API void SwitchFilter(int m_handle, int m_Axis, int m_Filter);

//��õ�ǰ�˹��ֿ�λ����  m_GetFilter[0]=1 2 3 4 5 6��ʾ��Ӧ���˹��ֿ�λ ����true��ʾ��ȡ�ɹ���false��ʾ��ȡʧ��
SLS_DLL_API bool GetFilter(int m_handle, int m_Axis, int m_GetFilter[1]);

//��ȡ�ֿ��ź� ����true��ʾ��ȡ�ɹ���false��ʾ��ȡʧ��
SLS_DLL_API bool GetSingle(int m_handle, int m_Axis, int m_GetSingle[1]);

//��ȡ�ϵ�״̬ ?srl m_GetPowerOnOff[0]=true ��ʾ���ϵ� m_GetPowerOnOff[0]=false��ʾ���ڶϵ� m_Axis��ʾ�˶���ID ����true��ʾ��ȡ�ɹ���false��ʾ��ȡʧ��
SLS_DLL_API bool GetPowerOnOff(int m_handle, int m_Axis, int GetPowerOnOff[1]);