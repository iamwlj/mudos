		Mudos V22pre11 for WIN95/NT with COM extension Version 1.1
				Copyright (C) 1998,1999 
				      wwj,kcn
		
��һ�� ϵͳ��鼰���ָ����Ĵ���

�ڶ��� LPC�ϵ���ǿ

������ LPC��COM extension��ϱ��

��¼һ Mudos v22pre11 with COM extension�е�COM����


--------------------------------------------------------------------------------


��һ�� ϵͳ��鼰���ָ����Ĵ���


    Mudos V22pre11 for WIN95/NT with COM extension ( ���¼��
pre11 with COM)���廪��ѧ�����ϵ���ľ���������Mudos V22pre11�Ļ�
���Ͽ������ɡ��Ƚ�ԭ�汾��Mudos V22pre11��˵������汾��Mudos����
��һЩ���������˶�COM�����֧�֡�
    COM( Component Object Model )��Microsoft��˾�����һ������
���������������Mudos�м���COM��֧�֣���Ҫ��Ϊ��������һЩ���е�
���켼������Դ���ֲ�Mudos����Ĺ��ܲ��㡣����COM�ľ���˵����ο�OLE
��̵����ϡ�
    
    Mudos V22pre11�Ѿ�������V21���еĲ��ٴ���pre11 with COM������
�����������д����ĸĶ���Ӧ��˵��һ���ܳ���İ汾���Ѿ����廪�����ϵ
¥��MUD�������а�����ʱ�䣩�������ǸĶ������
    
ϵͳ���֣�
1. �޸� random ����ʹ֮����32λֵ��������WIN32ƽ̨�е�16λ
2. �޸��˲���ռ��CPUʱ���������
3. �޸��� locatime �еĴ���ʹ��������һ����ѭ��
4. �޸�lex.c ʹ����ʱ��ʶ 8 ������
5. �޸��� debug_error ������ʹ���ܱ��� socket ����
6. ������ set_this_player() efun
7. ������ rusage() efun������ֵ���£�
   NT��
        int   ver     WINAPI GetVersion()�ķ���ֵ
	int   utime   MUDOS�û�̬ʱ�䣬��λ��msec
	int   stime   MUDOS����̬ʱ��
	int   load1   ��ȥһ����MUDOSռ�û���ʱ��ı��ʣ�
	 	      ����57% -> 5000 , 57.42% -> 5742
	int   load10  ��ȥʮ����MUDOSռ�û���ʱ��ı���
	int   load15  ��ȥʮ�����MUDOSռ�û���ʱ��ı���
   95/98:
        int   ver     WINAPI GetVersion()�ķ���ֵ
	int   utime   ��������ʱ�䣬��λ��msec
	int   stime   0
	int   load1   ��ȥһ����CPU������
	int   load10  ��ȥʮ����CPU������
	int   load15  ��ȥʮ�����CPU������
8. �޸���get_dir��ʹ�����ļ���ΪСд
9. ���������ý��档������Ҫ�����ļ�mudos.ini�����øĵ�registry
   HKEY_LOCAL_MACHINE\\wwj\\MudOS��
10.NT/95��֧�ֶ��MudOS Serviceʵ����ֻҪ���mudos.exe���ڲ�ͬ��
   Ŀ¼�£�����exe�ļ�����ͬ��
11.ͬʱ֧�����ģ�Ӣ��NT/95�����������Ӣ�Ĳ���ϵͳ�����ó������
   �����
12.����>64�˵ĵ�¼��������1024�������������ӻ�û����ô���
   ʱ��MUDOS�͵��ˣ�

COM���֣�
1. �Ľ���LPC��COM class�Ķ��壬����������˵����
2. �޸���MString�����еĴ���ʹ֮�������ڴ�й¶�������
3. COM��Ա�������Է���array,mapping,class�ȸ������͡�

	�����õ�Mudos v22pre11 for WIN95/NT with COM extension Version 1.1ʱ��
����һ��zip�ļ�������winzipչ�������������ִ���ļ���Դ�룬��ʹ�á��ַ���
�޸�����ʱ��������GPLЭ����С�
	Mudos.exe       ����õ�ִ���ļ���ʹ��ǰ��ɱ������ֹ�����и�Ⱦ����
	                �����������⻹��û�ж��ģ���
	                
	Readme.txt      �����˵���ĵ�
	
	GPL.txt         GNU GENERAL PUBLIC LICENSE
	
	Mudos\*.*       MudOS��Դ�룬��VC6.0����ͨ��
	
	BBS\lpc\*.*     һ��LPC�汾��BBS��û��д�꣬�����˭Ը�������д�����
			wwj@www.telekbird.com.cnȥ�š�
					
	BBS\bbscom\*.*  ����LPC�汾BBSʱһ����Ҫģ���Դ�롣
	
        BBS\FB270\*.*   Firebird BBS 2.70��Դ��
    
        testmud\*.*     һ���������ߵĳ���
    
        xyj\*.*         һ�����ڲ���mudos��MUD�����μǡ�
    
    ����Ҫ����mudos.exeʱ����ֱ������mudos.exe�����ᵯ��һ���Ի�����������
config�ļ�λ�ã�address server�Ķ˿ڣ��Լ�heart_beatʱ�䡣�������service
ʹ���´����������ʱmud���Զ����У����ڸöԻ����ϵ㡰ע����񡱡���������
���˺�mudos����ʽ�����ˡ�

    ����ʱ����explorer���Ǹ�״̬�����Ҷ˼���һ��"С����"��ICON���Դ˱�����
�������С�����������������һ���˵�������ѡ��  About,Setup,Restart��
Shutdown��ѡSetup�ͻ����ǰ����Ǹ����öԻ���

    ��������������汾��mudos������ʲô����ʱ����������ĵ�ַ��ϵ�����ǻ�
����������ġ�


    wwj    wwj@telekbird.com.cn
    kcn    mudos@126.com

 

--------------------------------------------------------------------------------


�ڶ��� LPC�ϵ���ǿ



        Mudos v22pre11 with COM extension version 1.1 �汾���ԭV21����ԣ�LPC��
������class���ͣ�������һЩefunc������һһ˵����

class����������C��class,LPC�ľ䷨���£�

class class_name {
    type member_name1;
    type member_name2;
    ...
    
    type member_func(type var...);
};

����һ��class����ʱ�䷨��

	class class_name object_name;

ʹ�ö���֮ǰӦ���ȶԶ����ʼ����
    
	object_name = new ( class class_name );

������class����ĳ�ԱʱӦ��ʹ�� -> ���š�

	object_name -> member_name1 = 0;

������һ��LPC���ӣ�

class ab
{
	int a;
	int add();
}

int ab::add() // ab�ĳ�Ա���� add()
{
	return a++; // ab�ĳ�Ա���� a++
}

class ab b;

useab()
{
	b=new(class ab);
	b->a=0; // b->a is 0
	b->add(); // then b->a is 1
}

	���ڳ�Ա�����ĳ��֣��б�Ҫ֧���ڳ�Ա�����з��ʱ�class�����������
һ��this�ؼ��֣�������ָʾ��ǰ��class��������int ab::add()�Ϳ���д��
int ab::add()
{
	return this->a++;
}
	��Ȼthis��Ҫ�������ǽ�class�Լ�������ĺ�����

	���Ҫ����COM����Ӧ��ʹ�����¸�ʽ��
class class_name {
	member and member function ...
} = " com ";

	com����Ҫ���õ�com�����CLSID����ProgID����DLL��MUD�е�ȫ·��������
Microsoft IE��HTML Viewer�ؼ���CLSID��
        {EAB22AC3-30C1-11CF-A7EB-0000C05BAE0B}
ProgID�� 
        Microsoft Web Browser Control
        
	class_name������ʹ�õ�Interface�����֣���HTML Viewer�ؼ���һ���ӿ��� 
IWebBrowser��
	class ��member��member function��Ӧ��������ӿڵ����Ժͷ�����ͨ��
VC�д���OLE/COM Viewer���Կ���Microsoft Web Browser Control��IWebBrowser
�Ķ����������ģ����֣�������

[
	uuid(EAB22AC1-30C1-11CF-A7EB-0000C05BAE0B), // ������Ǹ�CLSID
	helpstring("Web Browser interface"), 
	hidden,
	dual
]

dispinterface IWebBrowser {
methods:

[id(0xfffffdda), helpstring("Refresh the currently viewed page.")]
void Refresh(); // һ������ 

[id(0x00000068), helpstring("Navigates to a URL or file.")]
void Navigate( // ��һ������ 
[in] BSTR URL, 
[in] VARIANT* Flags, 
[in] VARIANT* TargetFrameName, 
[in] VARIANT* PostData, 
[in] VARIANT* Headers);

[id(0x000000ce), propget, helpstring("The horizontal position (pixels) of the frame window relative to the screen/container.")]
long Left(); 
    // ��Ȼд��methods�������progget���ԣ�ʵ���ϻ�����Ϊ�����ԣ�
    // ���Ƕ�����ֵ�ķ���

[id(0x000000ce), propput, helpstring("The horizontal position (pixels) of the frame window relative to the screen/container.")]
void Left([in] long rhs); 
    // ��Ȼд��methods�������progput���ԣ�ʵ���ϻ�����Ϊ�����ԣ�
    // ����д����ֵ�ķ���

    // �ȵȡ�����
}

���LPC�п����õ�class�͸ö���ɣ�

class IWebBrowser {
	void Refresh();
	int Left;
} = "{EAB22AC1-30C1-11CF-A7EB-0000C05BAE0B}"; 
����ַ���������дΪ Microsoft Web Browser Control
    
��������������壬���׼��C++������ûʲô��Ĳ�𡣳�ԱRefresh
������������MIDL�Ķ���ûʲô�仯��Left���Ե����ͱ����int��Navigate
����û�ӽ�����������Ϊ��LPC��COM������ת��ʱ�����������͵Ĳ�����������
�ġ�

Ŀǰ��pre11 with COM extension֧����������ת����

	LPC�� int     ��   COM�� int,long ����ת����
	LPC�� string  ��   COM�� BSTR     ����ת����
	LPC�� float   ��   COM�� float    ����ת����
	LPC�� void    ��   COM�� void     ����ת����
	LPC�� array   ת�� COM�� IMValue * ��
	LPC�� class   ת�� COM�� IMValue * ��
	LPC�� object  ת�� COM�� IMValue * ��
	LPC�� mapping ת�� COM�� IMValue * ��

IMValue �ӿ���Mudos.exe���ж��塣����"����ת��"����˼��֧�ָ�������Ϊ
�������Դ��ݣ�Ҳ������Ϊ����ֵ�������Ե����͡������޷�ת���ķ�������
�ԣ���Ҫд��class�Ķ����С�

ʹ��COM�����class����ͨ��class��ͬ������ʹ������IWebBrowser�����ӣ�

int UseIt()
{
	class IWebBrowser web;
	web=new (class IWebBrowser);
	web.Left=10;
	web.Refresh();
}

������IWebBrowser�����ӵ�Ŀ����˵�����ʹ��COM������ʵ��IWebBrowser
������Mudos��ʹ��(Mudos��һ��telnet���������ò���һ�������)��������
��һ�����ӣ�

class IBbs {         // ������һ���ӿ�������Сд����
    class IBbs QueryInterface(string);
    int  GetPlayerID(object);
    void SetEcho(int,int);
    void EnableKey(int,int);
    int  ThisPlayer();
}="/bin/obj/bbscom.dll";   // Ҳ������ "{xxxx-xx...}" coclass GUID
   �����"/bin/obj/bbscom.dll"�����COM�������ڵ�DLL��OCX������
�����巽�������������м���com=...��˵��(��ԭpre11 with COM extension
˵��)������Ԥ��ע�ᣬ�����Ǳ�����ȫ·����

   QueryInterface��һ��Ԥ��������Ա������������໹�б�Ľӿ�
��ʱ������������������ȡ��ͬһʵ������һ�ӿڣ�ȥ����ԭ����
AssignInstance������������
class IBbs2 {
    int Test();
}="/bin/obj/bbscom.dll";
   ����������µ�LPC����
   IBbs  bbs;
   IBbs2 p;
   bbs=new(class IBbs);
   p=bbs->QueryInterface("IBbs2");
   ��p��bbs��ָ��COMʵ������һ���ӿڡ�


--------------------------------------------------------------------------------

������ LPC��COM extension��ϱ��


pre11 with COM extension�����ṩ�˼���COM��������������ĳ���ͨѶ��
���嶨���뿴��¼һ�����Ժ��˵�����ҽ����ᵽ IMudos,IMValue,IMNumber,
IMString,IMReal,IMClass,IMObject,IMArray,IMMapping,IMProgram,
IMFunction�⼸���ӿڡ�

	������ý���һ��ATL com dll�Ĺ��̣�Ȼ��������һ��ATL Class�������
���classȡ��ΪCTestʱ�������õ��Ľӿ�(Interface)���ͳ���ITest��Ȼ����
�Ϳ��������Interface��������Ժͷ�����

ע��������ӵ���������ֻ���ǣ������ж��������
    int,BSTR,float
������ӵķ�����������ֻ����
    int,BSTR,float,IDispatch *
��������ֻ����
    int,BSTR,float,IDispatch *
��int,BSTR,float�Ĵ����һ���COMһ�¡���IDispatch *�Ĵ���Ӧ�ý���
����IMValue����Ȼ�����IMValue��Type()��GetExtend()ȡ����Ӧ���͵Ķ���
����LPC�ж����class��Ա����

	int Test(int i,class CTest c);

	��Ӧ��COM�����Ա�����͸��ǣ�
	
MIDL interface:
	HRESULT Test([in] int i,[in] IDispatch *p,[out,retval] int *pVal);

MIDL dispinterface:
	int Test([in] int i,[in] IDispatch *p);
	
C++:
	STDMETHOD(Test)(int i,IDispatch *p,int *pVal);
	
	��Test�е�ʵ��ʱӦ���������ģ�

STDMETHODIMP CTest::Test(int i,IDispatch *p,int *pVal)
{
	// ��Щ�ӿڵĺ�����鿴���ɵ�mudos.h
	if(!pVal)return S_FALSE;
	IMValue v(p);
	if(v.GetType()!=VP_CLASS)return S_FALSE; 
	IMClass c(v.GetExtend());

	// now use i,c
	// ...
	// return val in pVal
	return S_OK;
}

	��Ķ��������������������Ϊ�¼���Ӧ��
MIDL interface: 
	HRESULT OnNewObject(IDispatch *p);
	HRESULT OnFreeObject();
	
��C++�е�ʵ���ǣ�
	STDMETHODIMP CTest::OnNewObject(IDispatch *p)
	{
		m_os=new IMudos(p); // m_os��CTest��һ������ΪIMudos *�ĳ�Ա����
		return S_OK;
	}
	
	STDMETHODIMP CTest::OnFreeObject()
	{
		delete m_os;
		return S_OK;
	}
	������COM�о���ʹ��IMudos�����й��ܡ�
	
	����ʵ����ο�������BBSCOM��LPC BBS


--------------------------------------------------------------------------------


��¼һ Mudos v22pre11 with COM extension�е�COM����


mudos.idl�ļ�
// Generated .IDL file (by the OLE/COM Object Viewer)
// 
// typelib filename: MUDOS.DLL
// Forward declare all types defined in this typelib
interface IMValue;
interface IMNumber;
interface IMString;
interface IMReal;
interface IMObject;
interface IMClass;
interface IMMapping;
interface IMArray;
interface IMBuffer;
interface IMProgram;
interface IMFunction;
interface IMudos;

[
uuid(F64617C2-EA5A-11D1-B962-0080AD1480B3),
version(1.0),
helpstring("mudos v22pre11 Type Library")
]
library MUDOSLib
{
// TLib : OLE Automation : {00020430-0000-0000-C000-000000000046}
importlib("STDOLE2.TLB");

[
uuid(1B6ED8C0-EB38-11D1-BF0B-0000B4560A15),
helpstring("MValue Class")
]
coclass MValue {
[default] interface IMValue;
interface IMNumber;
interface IMString;
interface IMReal;
interface IMObject;
interface IMClass;
interface IMMapping;
interface IMArray;
interface IMBuffer;
};

[
odl,
uuid(1B6ED7C8-EB38-11D1-BF0B-0000B4560A15),
helpstring("IMValue Interface"),
dual,
oleautomation
]
interface IMValue : IDispatch {
[id(0x00000051), propget, helpstring("property Name")]
HRESULT _stdcall Name([out, retval] BSTR* pVal);
[id(0x00000052), propget, helpstring("property Type")]
HRESULT _stdcall Type([out, retval] eVALUETYPE* pVal);
[id(0x00000053), helpstring("method CreateNumber")]
HRESULT _stdcall CreateNumber();
[id(0x00000054), helpstring("method CreateString")]
HRESULT _stdcall CreateString();
[id(0x00000055), helpstring("method CreateReal")]
HRESULT _stdcall CreateReal();
[id(0x00000056), helpstring("method CreateArray")]
HRESULT _stdcall CreateArray([in] int size);
[id(0x00000057), helpstring("method CreateMapping")]
HRESULT _stdcall CreateMapping();
[id(0x00000058), propget, helpstring("property Extend")]
HRESULT _stdcall Extend([out, retval] IDispatch** pVal);
};

typedef enum {
VP_UNKNOW = 0,
VP_NUMBER = 1,
VP_STRING = 2,
VP_REAL = 3,
VP_OBJECT = 4,
VP_ARRAY = 5,
VP_MAPPING = 6,
VP_CLASS = 7,
VP_BUFFER = 8,
VP_FUNCTION = 9
} eVALUETYPE;

[
odl,
uuid(1B6ED7C0-EB38-11D1-BF0B-0000B4560A15),
helpstring("IMNumber Interface"),
dual,
oleautomation
]
interface IMNumber : IDispatch {
[id(0x00000001), propget, helpstring("property Number")]
HRESULT _stdcall Number([out, retval] int* pVal);
[id(0x00000001), propput, helpstring("property Number")]
HRESULT _stdcall Number([in] int pVal);
};

[
odl,
uuid(1B6ED7C1-EB38-11D1-BF0B-0000B4560A15),
helpstring("IMString Interface"),
dual,
oleautomation
]
interface IMString : IDispatch {
[id(0x0000000b), propget, helpstring("property String")]
HRESULT _stdcall String([out, retval] BSTR* pVal);
[id(0x0000000b), propput, helpstring("property String")]
HRESULT _stdcall String([in] BSTR pVal);
};

[
odl,
uuid(1B6ED7C2-EB38-11D1-BF0B-0000B4560A15),
helpstring("IMReal Interface"),
dual,
oleautomation
]
interface IMReal : IDispatch {
[id(0x00000015), propget, helpstring("property Real")]
HRESULT _stdcall Real([out, retval] single* pVal);
[id(0x00000015), propput, helpstring("property Real")]
HRESULT _stdcall Real([in] single pVal);
};

[
odl,
uuid(1B6ED7C3-EB38-11D1-BF0B-0000B4560A15),
helpstring("IMObject Interface"),
dual,
oleautomation
]
interface IMObject : IDispatch {
[id(0x0000001f), propget, helpstring("property ObjectName")]
HRESULT _stdcall ObjectName([out, retval] BSTR* pVal);
[id(0x00000020), propget, helpstring("property ObjectLoadTime")]
HRESULT _stdcall ObjectLoadTime([out, retval] int* pVal);
[id(0x00000021), propget, helpstring("property Environment")]
HRESULT _stdcall Environment([out, retval] IMObject** pVal);
[id(0x00000022), propget, helpstring("property ValueCount")]
HRESULT _stdcall ValueCount([out, retval] int* pVal);
[id(0x00000023), propget, helpstring("property Value")]
HRESULT _stdcall Value(
[in] int id, 
[out, retval] IMValue** pVal);
};

[
odl,
uuid(1B6ED7C5-EB38-11D1-BF0B-0000B4560A15),
helpstring("IMClass Interface"),
dual,
oleautomation
]
interface IMClass : IDispatch {
[id(0x00000033), propget, helpstring("property MemberCount")]
HRESULT _stdcall MemberCount([out, retval] int* pVal);
[id(0x00000034), propget, helpstring("property Member")]
HRESULT _stdcall Member(
[in] int id, 
[out, retval] IMValue** pVal);
};

[
odl,
uuid(1B6ED7C6-EB38-11D1-BF0B-0000B4560A15),
helpstring("IMMapping Interface"),
dual,
oleautomation
]
interface IMMapping : IDispatch {
[id(0x0000003d), propget, helpstring("property MappingCount")]
HRESULT _stdcall MappingCount([out, retval] int* pVal);
[id(0x0000003e), propget, helpstring("property MappingKeys")]
HRESULT _stdcall MappingKeys([out, retval] IMArray** pVal);
[id(0x0000003f), helpstring("method Query")]
HRESULT _stdcall Query(
[in] BSTR sKey, 
[out, retval] IMValue** pVal);
[id(0x00000040), helpstring("method Map")]
HRESULT _stdcall Map(
[in] BSTR sKey, 
[in] IMValue* pVal);
};

[
odl,
uuid(1B6ED7C4-EB38-11D1-BF0B-0000B4560A15),
helpstring("IMArray Interface"),
dual,
oleautomation
]
interface IMArray : IDispatch {
[id(0x00000029), propget, helpstring("property ItemCount")]
HRESULT _stdcall ItemCount([out, retval] int* pVal);
[id(0x0000002a), propget, helpstring("property Item")]
HRESULT _stdcall Item(
[in] int id, 
[out, retval] IMValue** pVal);
};

[
odl,
uuid(1B6ED7C7-EB38-11D1-BF0B-0000B4560A15),
helpstring("IMBuffer Interface"),
dual,
oleautomation
]
interface IMBuffer : IDispatch {
};

[
uuid(1B6ED8C1-EB38-11D1-BF0B-0000B4560A15),
helpstring("MProgram Class")
]
coclass MProgram {
[default] interface IMProgram;
};

[
odl,
uuid(1B6ED7C9-EB38-11D1-BF0B-0000B4560A15),
helpstring("IMProgram Interface"),
dual,
oleautomation
]
interface IMProgram : IDispatch {
[id(0x00000001), propget, helpstring("property FunctionCount")]
HRESULT _stdcall FunctionCount([out, retval] int* pVal);
[id(0x00000002), propget, helpstring("property Function")]
HRESULT _stdcall Function(
[in] int id, 
[out, retval] IMFunction** pVal);
[id(0x00000005), propget, helpstring("property FileName")]
HRESULT _stdcall FileName([out, retval] BSTR* pVal);
};

[
odl,
uuid(1B6ED7CA-EB38-11D1-BF0B-0000B4560A15),
helpstring("IMFunction Interface"),
dual,
oleautomation
]
interface IMFunction : IDispatch {
[id(0x00000001), propget, helpstring("property Name")]
HRESULT _stdcall Name([out, retval] BSTR* pVal);
[id(0x00000002), propget, helpstring("property ParamCount")]
HRESULT _stdcall ParamCount([out, retval] int* pVal);
[id(0x00000003), helpstring("method AddParam")]
HRESULT _stdcall AddParam([in] IMValue* pVal);
[id(0x00000004), helpstring("method ClearParam")]
HRESULT _stdcall ClearParam();
[id(0x00000005), propget, helpstring("property Ret")]
HRESULT _stdcall Ret([out, retval] IMValue** pVal);
[id(0x00000006), helpstring("method Apply")]
HRESULT _stdcall Apply();
};

[
uuid(1B6ED8C2-EB38-11D1-BF0B-0000B4560A15),
helpstring("MFunction Class")
]
coclass MFunction {
[default] interface IMFunction;
};

[
uuid(1B6ED8C3-EB38-11D1-BF0B-0000B4560A15),
helpstring("Mudos Class")
]
coclass Mudos {
[default] interface IMudos;
};

[
odl,
uuid(1B6ED7CB-EB38-11D1-BF0B-0000B4560A15),
helpstring("IMudos Interface"),
dual,
oleautomation
]
interface IMudos : IDispatch {
[id(0x00000001), propget, helpstring("property CurrentObject")]
HRESULT _stdcall CurrentObject([out, retval] IMObject** pVal);
[id(0x00000002), propget, helpstring("property CurrentProgram")]
HRESULT _stdcall CurrentProgram([out, retval] IMProgram** pVal);
[id(0x00000003), helpstring("method SetCommHook, pFunc is the function address.
int commhook(char *buf,int cursize,int maxsize,int user_id)")]
HRESULT _stdcall SetCommHook([in] int pFunc);
[id(0x00000004), helpstring("method Shutdown")]
HRESULT _stdcall Shutdown();
[id(0x00000005), propget, helpstring("property Users")]
HRESULT _stdcall Users([out, retval] IMArray** pVal);
[id(0x00000006), helpstring("method GetUser")]
HRESULT _stdcall GetUser(
[in] int UserId, 
[out, retval] IMObject** pVal);
[id(0x00000007), propget, helpstring("property HeartBeat")]
HRESULT _stdcall HeartBeat([out, retval] int* pVal);
[id(0x00000007), propput, helpstring("property HeartBeat")]
HRESULT _stdcall HeartBeat([in] int pVal);
};
};



����VC5��classwizardѡ��MUDOSԴ���µ�Mcon.tlb���Զ�����Mcon.h �� 
Mcon.cpp��Ȼ����mudos.h�м������¶��壨��Щֵ��IMValue::Type()��
����ֵ��
typedef enum eVALUETYPE
{	VP_UNKNOW	= 0,
	VP_NUMBER	= VP_UNKNOW + 1,
	VP_STRING	= VP_NUMBER + 1,
	VP_REAL	=	VP_STRING + 1,
	VP_OBJECT	= VP_REAL + 1,
	VP_ARRAY	= VP_OBJECT + 1,
	VP_MAPPING	= VP_ARRAY + 1,
	VP_CLASS	= VP_MAPPING + 1,
	VP_BUFFER	= VP_CLASS + 1,
	VP_FUNCTION	= VP_BUFFER + 1
}	VALUETYPE;

const IID IID_IMNumber = {0x1B6ED7C0,0xEB38,0x11D1,{0xBF,0x0B,0x00,0x00,0xB4,0x56,0x0A,0x15}};


const IID IID_IMString = {0x1B6ED7C1,0xEB38,0x11D1,{0xBF,0x0B,0x00,0x00,0xB4,0x56,0x0A,0x15}};


const IID IID_IMReal = {0x1B6ED7C2,0xEB38,0x11D1,{0xBF,0x0B,0x00,0x00,0xB4,0x56,0x0A,0x15}};


const IID IID_IMObject = {0x1B6ED7C3,0xEB38,0x11D1,{0xBF,0x0B,0x00,0x00,0xB4,0x56,0x0A,0x15}};


const IID IID_IMArray = {0x1B6ED7C4,0xEB38,0x11D1,{0xBF,0x0B,0x00,0x00,0xB4,0x56,0x0A,0x15}};


const IID IID_IMClass = {0x1B6ED7C5,0xEB38,0x11D1,{0xBF,0x0B,0x00,0x00,0xB4,0x56,0x0A,0x15}};


const IID IID_IMMapping = {0x1B6ED7C6,0xEB38,0x11D1,{0xBF,0x0B,0x00,0x00,0xB4,0x56,0x0A,0x15}};


const IID IID_IMBuffer = {0x1B6ED7C7,0xEB38,0x11D1,{0xBF,0x0B,0x00,0x00,0xB4,0x56,0x0A,0x15}};


const IID IID_IMValue = {0x1B6ED7C8,0xEB38,0x11D1,{0xBF,0x0B,0x00,0x00,0xB4,0x56,0x0A,0x15}};


const IID IID_IMProgram = {0x1B6ED7C9,0xEB38,0x11D1,{0xBF,0x0B,0x00,0x00,0xB4,0x56,0x0A,0x15}};


const IID IID_IMFunction = {0x1B6ED7CA,0xEB38,0x11D1,{0xBF,0x0B,0x00,0x00,0xB4,0x56,0x0A,0x15}};


const IID IID_IMudos = {0x1B6ED7CB,0xEB38,0x11D1,{0xBF,0x0B,0x00,0x00,0xB4,0x56,0x0A,0x15}};

const CLSID CLSID_MValue = {0x1B6ED8C0,0xEB38,0x11D1,{0xBF,0x0B,0x00,0x00,0xB4,0x56,0x0A,0x15}};


const CLSID CLSID_MProgram = {0x1B6ED8C1,0xEB38,0x11D1,{0xBF,0x0B,0x00,0x00,0xB4,0x56,0x0A,0x15}};


const CLSID CLSID_MFunction = {0x1B6ED8C2,0xEB38,0x11D1,{0xBF,0x0B,0x00,0x00,0xB4,0x56,0x0A,0x15}};


const CLSID CLSID_Mudos = {0x1B6ED8C3,0xEB38,0x11D1,{0xBF,0x0B,0x00,0x00,0xB4,0x56,0x0A,0x15}};
