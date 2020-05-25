// ../Code/ObjectTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "../Code/ObjectTool.h"
#include "afxdialogex.h"
#include "DirectoryMgr.h"
#include "MainFrm.h"
#include "ToolView.h"
#include "MyForm.h"
#include "StaticObject.h"
#include "TestStage.h"
#include "DynamicCamera.h"
// CObjectTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CObjectTool, CDialogEx)

CObjectTool::CObjectTool(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CObjectTool::~CObjectTool()
{
	//for_each(m_pGameObjectMap.begin(), m_pGameObjectMap.end(), Engine::CDeleteMap());
	//m_pGameObjectMap.clear();

	//Engine::Safe_Release(m_pDevice);
	//Engine::Safe_Release(m_pDeviceClass);

}

void CObjectTool::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_CONTROL,	m_StaticTree);
	DDX_Control(pDX, IDC_StCreateBT,	m_StaticCreateButton);
	DDX_Control(pDX, IDC_StDeleteBT,	m_StaticDeleteButton);
	DDX_Control(pDX, IDC_InstanceTree,	m_InstanceTree);
	DDX_Control(pDX, IDC_EditScaleX,	m_EditScaleX);
	DDX_Control(pDX, IDC_EditScaleY,	m_EditScaleY);
	DDX_Control(pDX, IDC_EditScaleZ,	m_EditScaleZ);
	DDX_Control(pDX, IDC_EditRotationX, m_EditRotationX);
	DDX_Control(pDX, IDC_EditRotationY, m_EditRotationY);
	DDX_Control(pDX, IDC_EditRotationZ, m_EditRotationZ);
	DDX_Control(pDX, IDC_EditPositionX, m_EditPositionX);
	DDX_Control(pDX, IDC_EditPositionY, m_EditPositionY);
	DDX_Control(pDX, IDC_EditPositionZ, m_EditPositionZ);
}

HRESULT CObjectTool::Update(const _float & fTimeDelta)
{
	if (m_pScene != nullptr)
	{
		m_pGameObjectMap = dynamic_cast<CTestStage*>(m_pScene)->Get_Layer(L"GameLogic")->Get_ObjectMap();
		int iMapSize = m_pGameObjectMap.size();
		if (0 < iMapSize)
			m_pCamera = dynamic_cast<CDynamicCamera*>((m_pGameObjectMap.find(L"DynamicCamera")->second));
	}


	if (m_pCamera != nullptr)
	{
		if (m_pCamera->IsPick())
		{
			m_pTransform = m_pCamera->Get_PickTransform();

			m_csScale[0].Format(_T("%f"), m_pTransform->m_vScale.x);
			SetDlgItemTextW(IDC_EditScaleX, m_csScale[0]);

			m_csScale[1].Format(_T("%f"), m_pTransform->m_vScale.y);
			SetDlgItemTextW(IDC_EditScaleY, m_csScale[1]);

			m_csScale[2].Format(_T("%f"), m_pTransform->m_vScale.z);
			SetDlgItemTextW(IDC_EditScaleZ, m_csScale[2]);

			m_csRotation[0].Format(_T("%f"), D3DXToDegree(m_pTransform->m_vAngle.x));
			SetDlgItemTextW(IDC_EditRotationX, m_csRotation[0]);

			m_csRotation[1].Format(_T("%f"), D3DXToDegree(m_pTransform->m_vAngle.y));
			SetDlgItemTextW(IDC_EditRotationY, m_csRotation[1]);

			m_csRotation[2].Format(_T("%f"), D3DXToDegree(m_pTransform->m_vAngle.z));
			SetDlgItemTextW(IDC_EditRotationZ, m_csRotation[2]);

			m_csPosition[0].Format(_T("%f"), m_pTransform->m_vInfo[Engine::INFO_POS].x);
			SetDlgItemTextW(IDC_EditPositionX, m_csPosition[0]);

			m_csPosition[1].Format(_T("%f"), m_pTransform->m_vInfo[Engine::INFO_POS].y);
			SetDlgItemTextW(IDC_EditPositionY, m_csPosition[1]);

			m_csPosition[2].Format(_T("%f"), m_pTransform->m_vInfo[Engine::INFO_POS].z);
			SetDlgItemTextW(IDC_EditPositionZ, m_csPosition[2]);
		}
	}

	return S_OK;
}



BEGIN_MESSAGE_MAP(CObjectTool, CDialogEx)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_StCreateBT, &CObjectTool::OnBnClickedMeshCreate)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_CONTROL, &CObjectTool::OnSelectMesh)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SpinScaleX, &CObjectTool::OnDeltaposSpinScaleX)
	ON_NOTIFY(TVN_SELCHANGED, IDC_InstanceTree, &CObjectTool::OnTvnSelchangedInstancetree)
	ON_EN_CHANGE(IDC_EditScaleX, &CObjectTool::OnEnChangeEditScaleX)
	ON_EN_CHANGE(IDC_EditScaleY, &CObjectTool::OnEnChangeEditScaleY)
	ON_EN_CHANGE(IDC_EditScaleZ, &CObjectTool::OnEnChangeEditScaleZ)
	ON_EN_CHANGE(IDC_EditRotationX, &CObjectTool::OnEnChangeEditRotationX)
	ON_EN_CHANGE(IDC_EditRotationY, &CObjectTool::OnEnChangeEditRotationY)
	ON_EN_CHANGE(IDC_EditRotationZ, &CObjectTool::OnEnChangeEditRotationZ)
	ON_EN_CHANGE(IDC_EditPositionX, &CObjectTool::OnEnChangeEditPositionX)
	ON_EN_CHANGE(IDC_EditPositionY, &CObjectTool::OnEnChangeEditPositionY)
	ON_EN_CHANGE(IDC_EditPositionZ, &CObjectTool::OnEnChangeEditPositionZ)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN5, &CObjectTool::OnDeltaposSpinScaleY)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN6, &CObjectTool::OnDeltaposSpinScaleZ)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN7, &CObjectTool::OnDeltaposSpinRotationX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN8, &CObjectTool::OnDeltaposSpinRotationY)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN9, &CObjectTool::OnDeltaposSpinRotationZ)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN10, &CObjectTool::OnDeltaposSpinPositionX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN11, &CObjectTool::OnDeltaposSpinPositionY)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN12, &CObjectTool::OnDeltaposSpinPositionZ)
END_MESSAGE_MAP()


// CObjectTool 메시지 처리기입니다.


BOOL CObjectTool::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_hStaticMesh = m_StaticTree.InsertItem(TEXT("StaticMesh"), 0, 0, TVI_ROOT, TVI_LAST);
	m_hDynamicMesh = m_StaticTree.InsertItem(TEXT("DynamicMesh"), 0, 0, TVI_ROOT, TVI_LAST);
	
	if (m_pDeviceClass == nullptr)
	{
		CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
		NULL_CHECK(pFrameWnd);

		m_pMyform = dynamic_cast<CMyForm*>(pFrameWnd->m_MainSplitter.GetPane(0, 0));
		m_pDeviceClass = m_pMyform->Get_DeviceClass();
		m_pDevice = m_pMyform->Get_Device();
		m_pScene = m_pMyform->Get_Scene();
	}
	m_hStaticRoot = m_InstanceTree.InsertItem(TEXT("StaticObject"), 0, 0, TVI_ROOT, TVI_LAST);
	m_hDynamicRoot = m_InstanceTree.InsertItem(TEXT("DynamicObject"), 0, 0, TVI_ROOT, TVI_LAST);

	TCHAR szFileName[MAX_STR] = L"../../Client/Bin/Resource/Mesh";

	CDirectoryMgr::ExtractPathInfo(szFileName, m_pMeshList);

	wstring wstrCombined = L"";
	TCHAR szCount[MIN_STR] = L"";

	for (auto pPathInfo : m_pMeshList)
	{
		if (pPathInfo->wstrMeshType.compare(L"StaticMesh") == 0)
		{
			m_hMap = m_StaticTree.InsertItem(pPathInfo->wstrMap.c_str(), 0, 0, m_hStaticMesh, TVI_LAST);
			if (pPathInfo->wstrGroup.find(L"Terrain") != wstring::npos)
				m_hFloor = m_StaticTree.InsertItem(pPathInfo->wstrObjectType.c_str(), 0, 0, m_hMap, TVI_LAST);

			wstring temp =pPathInfo->wstrObjectType + L".X";
			if (Engine::Ready_Meshes(m_pDevice,
				RESOURCE_STAGE,
				pPathInfo->wstrObjectType.c_str(),
				Engine::TYPE_STATIC,
				pPathInfo->wstrRelative.c_str(),
				temp.c_str()) < 0)
			{
				return false;
			}
			
		}
		else if (pPathInfo->wstrMeshType.compare(L"DynamicMesh") == 0)
		{
			m_hEtc = m_StaticTree.InsertItem(pPathInfo->wstrObjectType.c_str(), 0, 0, m_hDynamicMesh, TVI_LAST);
		}
		else
		{
			m_hEtc = m_StaticTree.InsertItem(pPathInfo->wstrObjectType.c_str(), 0, 0, m_hStaticMesh, TVI_LAST);
			if (Engine::Ready_Meshes(m_pDevice,
				RESOURCE_STAGE,
				pPathInfo->wstrObjectType.c_str(),
				Engine::TYPE_STATIC,
				pPathInfo->wstrRelative.c_str(),
				pPathInfo->wstrName.c_str()) < 0)
			{
				return false;
			}
		
		}


	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CObjectTool::OnBnClickedMeshCreate()
{
	HTREEITEM hCurITem = m_StaticTree.GetSelectedItem();
	m_csSelectMesh = m_StaticTree.GetItemText(hCurITem);
	TRANSFORM_INFO tTemp;
	ZeroMemory(&tTemp,sizeof(TRANSFORM_INFO));
	wstring wstrName=m_csSelectMesh;
	_uint uiChildCount = 0;
	wstring wstrNameIdx;

	if (m_InstanceTree.ItemHasChildren(m_hStaticRoot))
	{
		HTREEITEM hChild = m_InstanceTree.GetChildItem(m_hStaticRoot);
		CString csText = m_InstanceTree.GetItemText(hChild);
		if (csText.Find(wstrName.c_str()) != -1)
			uiChildCount++;
		while (hChild = m_InstanceTree.GetNextSiblingItem(hChild))
		{
			CString csText = m_InstanceTree.GetItemText(hChild);
			if (csText.Find(wstrName.c_str()) != -1)
				uiChildCount++;
		}

	}

	wstrNameIdx = wstrName + L"_" + to_wstring(uiChildCount);
	dynamic_cast<CTestStage*>(m_pScene)->Add_StaticObject(wstrNameIdx, tTemp);
	m_pGameObjectMap = Engine::Get_Layer(L"GameLogic")->Get_ObjectMap();

	m_hInstStatic= m_InstanceTree.InsertItem(wstrNameIdx.c_str(), 0, 0, m_hStaticRoot, TVI_LAST);


}


void CObjectTool::OnSelectMesh(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	HTREEITEM hCurITem = m_StaticTree.GetSelectedItem();
	m_csSelectMesh = m_StaticTree.GetItemText(hCurITem);

	*pResult = 0;
}

void CObjectTool::OnDeltaposSpinScaleX(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	m_vScale.x = _tstof(m_csScale[0]);
	
	if (pNMUpDown->iDelta < 0)
		m_vScale.x+=0.001f;
	else
		m_vScale.x-=0.001f;

	m_csScale[0].Format(_T("%f"), m_vScale.x);
	SetDlgItemTextW(IDC_EditScaleX, m_csScale[0]);
	if (m_pTransform)
		m_pTransform->m_vScale.x = m_vScale.x;

	*pResult = 0;
}


void CObjectTool::OnTvnSelchangedInstancetree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	HTREEITEM hCurITem = m_InstanceTree.GetSelectedItem();
	m_csSelectMesh = m_InstanceTree.GetItemText(hCurITem);
	wstring wstr = m_csSelectMesh;

	for (auto &pGameObject : m_pGameObjectMap)
	{
		if ( pGameObject.first.compare(wstr)==0)
		{

			m_pGameObject = pGameObject.second;
			m_pTransform = dynamic_cast<Engine::CTransform*>(m_pGameObject->Get_Component(L"Com_Transform", Engine::ID_DYNAMIC));

			m_csScale[0].Format(_T("%f"), m_pTransform->m_vScale.x);
			SetDlgItemTextW(IDC_EditScaleX, m_csScale[0]);

			m_csScale[1].Format(_T("%f"), m_pTransform->m_vScale.y);
			SetDlgItemTextW(IDC_EditScaleY, m_csScale[1]);

			m_csScale[2].Format(_T("%f"), m_pTransform->m_vScale.z);
			SetDlgItemTextW(IDC_EditScaleZ, m_csScale[2]);

			m_csRotation[0].Format(_T("%f"), D3DXToDegree(m_pTransform->m_vAngle.x));
			SetDlgItemTextW(IDC_EditRotationX, m_csRotation[0]);

			m_csRotation[1].Format(_T("%f"), D3DXToDegree(m_pTransform->m_vAngle.y));
			SetDlgItemTextW(IDC_EditRotationY, m_csRotation[1]);

			m_csRotation[2].Format(_T("%f"), D3DXToDegree(m_pTransform->m_vAngle.z));
			SetDlgItemTextW(IDC_EditRotationZ, m_csRotation[2]);

			m_csPosition[0].Format(_T("%f"), m_pTransform->m_vInfo[Engine::INFO_POS].x);
			SetDlgItemTextW(IDC_EditPositionX, m_csPosition[0]);

			m_csPosition[1].Format(_T("%f"), m_pTransform->m_vInfo[Engine::INFO_POS].y);
			SetDlgItemTextW(IDC_EditPositionY, m_csPosition[1]);

			m_csPosition[2].Format(_T("%f"), m_pTransform->m_vInfo[Engine::INFO_POS].z);
			SetDlgItemTextW(IDC_EditPositionZ, m_csPosition[2]);


		}
	}
	*pResult = 0;
}


void CObjectTool::OnEnChangeEditScaleX()
{
	GetDlgItemText(IDC_EditScaleX, m_csScale[0]);
	if (m_pTransform)
		m_pTransform->m_vScale.x= _tstof(m_csScale[0]);


}


void CObjectTool::OnEnChangeEditScaleY()
{
	GetDlgItemText(IDC_EditScaleY, m_csScale[1]);
	if (m_pTransform)
		m_pTransform->m_vScale.y = _tstof(m_csScale[1]);
}


void CObjectTool::OnEnChangeEditScaleZ()
{
	GetDlgItemText(IDC_EditScaleZ, m_csScale[2]);
	if (m_pTransform)
		m_pTransform->m_vScale.z = _tstof(m_csScale[2]);
}


void CObjectTool::OnEnChangeEditRotationX()
{
	GetDlgItemText(IDC_EditRotationX, m_csRotation[0]);
	if (m_pTransform)
		m_pTransform->m_vAngle.x = D3DXToRadian(_tstof(m_csRotation[0]));
}


void CObjectTool::OnEnChangeEditRotationY()
{
	GetDlgItemText(IDC_EditRotationY, m_csRotation[1]);
	if (m_pTransform)
		m_pTransform->m_vAngle.y = D3DXToRadian(_tstof(m_csRotation[1]));
}


void CObjectTool::OnEnChangeEditRotationZ()
{
	GetDlgItemText(IDC_EditRotationZ, m_csRotation[2]);
	if (m_pTransform)
		m_pTransform->m_vAngle.z = D3DXToRadian(_tstof(m_csRotation[2]));

}


void CObjectTool::OnEnChangeEditPositionX()
{
	GetDlgItemText(IDC_EditPositionX, m_csPosition[0]);
	if (m_pTransform)
		m_pTransform->m_vInfo[Engine::INFO_POS].x = _tstof(m_csPosition[0]);
}


void CObjectTool::OnEnChangeEditPositionY()
{
	GetDlgItemText(IDC_EditPositionY, m_csPosition[1]);
	if (m_pTransform)
		m_pTransform->m_vInfo[Engine::INFO_POS].y = _tstof(m_csPosition[1]);
}


void CObjectTool::OnEnChangeEditPositionZ()
{
	GetDlgItemText(IDC_EditPositionZ, m_csPosition[2]);
	if (m_pTransform)
		m_pTransform->m_vInfo[Engine::INFO_POS].z = _tstof(m_csPosition[2]);
}


void CObjectTool::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}


void CObjectTool::OnCancel()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnCancel();
}


void CObjectTool::OnDeltaposSpinScaleY(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	m_vScale.y = _tstof(m_csScale[1]);

	if (pNMUpDown->iDelta < 0)
		m_vScale.y += 0.001f;
	else
		m_vScale.y -= 0.001f;

	m_csScale[1].Format(_T("%f"), m_vScale.y);
	SetDlgItemTextW(IDC_EditScaleY, m_csScale[1]);
	if (m_pTransform)
		m_pTransform->m_vScale.y = m_vScale.y;

	*pResult = 0;
}


void CObjectTool::OnDeltaposSpinScaleZ(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	m_vScale.z = _tstof(m_csScale[2]);

	if (pNMUpDown->iDelta < 0)
		m_vScale.z += 0.001f;
	else
		m_vScale.z -= 0.001f;

	m_csScale[2].Format(_T("%f"), m_vScale.z);
	SetDlgItemTextW(IDC_EditScaleZ, m_csScale[2]);
	if (m_pTransform)
		m_pTransform->m_vScale.z = m_vScale.z;

	*pResult = 0;
}


void CObjectTool::OnDeltaposSpinRotationX(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	m_vRotation.x = _tstof(m_csRotation[0]);

	if (pNMUpDown->iDelta < 0)
		m_vRotation.x += 0.1f;
	else
		m_vRotation.x -= 0.1f;

	m_csRotation[0].Format(_T("%f"), m_vRotation.x);
	SetDlgItemTextW(IDC_EditRotationX, m_csRotation[0]);
	if (m_pTransform)
		m_pTransform->m_vAngle.x = m_vRotation.x;

	*pResult = 0;
}


void CObjectTool::OnDeltaposSpinRotationY(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	m_vRotation.y = _tstof(m_csRotation[1]);

	if (pNMUpDown->iDelta < 0)
		m_vRotation.y += 0.1f;
	else
		m_vRotation.y -= 0.1f;

	m_csRotation[1].Format(_T("%f"), m_vRotation.y);
	SetDlgItemTextW(IDC_EditRotationY, m_csRotation[1]);
	if (m_pTransform)
		m_pTransform->m_vAngle.y = m_vRotation.y;

	*pResult = 0;
}


void CObjectTool::OnDeltaposSpinRotationZ(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	m_vRotation.z = _tstof(m_csRotation[2]);

	if (pNMUpDown->iDelta < 0)
		m_vRotation.z += 0.1f;
	else
		m_vRotation.z -= 0.1f;

	m_csRotation[2].Format(_T("%f"),m_vRotation.z);
	SetDlgItemTextW(IDC_EditRotationZ, m_csRotation[2]);
	if (m_pTransform)
		m_pTransform->m_vAngle.z = m_vRotation.z;
	*pResult = 0;
}


void CObjectTool::OnDeltaposSpinPositionX(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	m_vPosition.x = _tstof(m_csPosition[0]);

	if (pNMUpDown->iDelta < 0)
		m_vPosition.x += 0.1f;
	else
		m_vPosition.x -= 0.1f;

	m_csPosition[0].Format(_T("%f"), m_vPosition.x);
	SetDlgItemTextW(IDC_EditPositionX, m_csPosition[0]);
	if (m_pTransform)
		m_pTransform->m_vInfo[Engine::INFO_POS].x = m_vPosition.x;
	*pResult = 0;
}


void CObjectTool::OnDeltaposSpinPositionY(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	m_vPosition.y = _tstof(m_csPosition[1]);

	if (pNMUpDown->iDelta < 0)
		m_vPosition.y += 0.1f;
	else
		m_vPosition.y -= 0.1f;

	m_csPosition[1].Format(_T("%f"), m_vPosition.y);
	SetDlgItemTextW(IDC_EditPositionY, m_csPosition[1]);
	if (m_pTransform)
		m_pTransform->m_vInfo[Engine::INFO_POS].y = m_vPosition.y;
	*pResult = 0;
}


void CObjectTool::OnDeltaposSpinPositionZ(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	m_vPosition.z = _tstof(m_csPosition[2]);

	if (pNMUpDown->iDelta < 0)
		m_vPosition.z += 0.1f;
	else
		m_vPosition.z -= 0.1f;

	m_csPosition[2].Format(_T("%f"), m_vPosition.z);
	SetDlgItemTextW(IDC_EditPositionZ, m_csPosition[2]);
	if (m_pTransform)
		m_pTransform->m_vInfo[Engine::INFO_POS].z = m_vPosition.z;
	*pResult = 0;
}
