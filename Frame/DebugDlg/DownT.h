#if !defined(AFX_DOWNT_H__C09D3C4D_EE17_4FA9_88B2_D06325D0E8C9__INCLUDED_)
#define AFX_DOWNT_H__C09D3C4D_EE17_4FA9_88B2_D06325D0E8C9__INCLUDED_

extern "C" void __declspec(dllimport) SamdrawUsb_init(void);

extern "C" int __declspec(dllimport) SamdrawUsb_isconnected(void);

extern "C" void __declspec(dllimport) SamdrawUsb_connect(void);

extern "C" void __declspec(dllimport) SamdrawUsb_disconnect(void);

extern "C" int __declspec(dllimport)  SamdrawUsb_readRaw(void * buffer, int length);

extern "C" int __declspec(dllimport)  SamdrawUsb_writeRaw(const void * buffer, int length);

extern "C" void __declspec(dllimport)  SamdrawUsb_clear_outbuffer(void);

#endif
